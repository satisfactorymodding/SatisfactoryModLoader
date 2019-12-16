#include "ModHandler.h"
#include <filesystem>
#include "util/Utility.h"
#include "util/json.hpp"
#include "util/Logging.h"
#include "util/picosha2.h"
#include "zip/ttvfs/ttvfs.h"
#include "zip/ttvfs_zip/ttvfs_zip.h"
#include "util/TopologicalSort.h"
#include <algorithm>
#include "util/Internal.h"
#include "util/bootstrapper_exports.h"
#include "Engine/World.h"
#include "SMLModule.h"
#include "PlatformFilemanager.h"
#include "IPlatformFilePak.h"
#include "FGGameMode.h"
#include "CoreDelegates.h"
#include "hooking.h"
#include "component/ModInitializerComponent.h"
#include "FGPlayerController.h"

using namespace SML;
using namespace SML::Mod;

typedef std::string FileHash;

std::wstring getModIdFromFile(const path& filePath) {
	std::wstring modId = filePath.filename().generic_wstring();
	//remove extension from file name
	modId.erase(modId.find_last_of(TEXT('.')));
	if (filePath.extension() == TEXT(".dll")) {
		//UE4-SML-Win64-Shipping, Mod ID is the second piece - name of the module
		if (modId.find(TEXT("UE4-")) == 0 && modId.find(TEXT("-Win64-Shipping")) == modId.size() - 15) {
			return modId.substr(4, modId.size() - 15);
		}
		//otherwise load it straight with the same name as file name
		return modId;
	}
	if (filePath.extension() == TEXT(".pak")) {
		//FactoryGame_p.pak, clean priority suffix if it is there
		if (modId.find_last_of(TEXT("_P")) == modId.size() - 2 ||
			modId.find_last_of(TEXT("_p")) == modId.size() - 2) {
			return modId.substr(0, modId.size() - 2);
		}
		//return normal mod id if it doesn't contain suffix
		return modId;
	}
	return modId;
}

//creates module name from file name
//these names should equal the names used in linking phase in UnrealBuildTool
//for cross-mod DLL references to work
//For example, if mod ExampleMod has dependency of FooBarMod,
//linker generates import entries in UE4-ExampleMod-Win64-Shipping.dll from UE4-FooBarMod-Win64-Shipping.dll
//so for importing to succeed, bootstrapper should have module named UE4-ExampleMod-Win64-Shipping.dll loaded
//into the memory and associated with that module name
std::string createModuleNameFromModId(const std::wstring& modId) {
	//TODO platform-independent way
	//linker uses names with the following schema during linkage
	return convertStr(formatStr(TEXT("UE4-"), modId, TEXT("-Win64-Shipping.dll")).c_str());
}

FileHash hashFileContents(const path& path) {
	std::ifstream f(path.generic_string(), std::ios::binary);
	std::vector<unsigned char> hash(picosha2::k_digest_size);
	picosha2::hash256(f, hash.begin(), hash.end());
	return picosha2::bytes_to_hex_string(hash);
}

path generateTempFilePath(const FileHash& fileHash, const char* extension) {
	path result = SML::getCacheDirectory();
	return path(result / fileHash).replace_extension(extension);
}

bool extractArchiveFile(path& outFilePath, ttvfs::File* obj) {
	std::ofstream outFile(outFilePath, std::ofstream::binary);
	auto buffer_size = 4096;
	if (!obj->open("rb")) {
		throw std::invalid_argument("Failed opening archive object");
	}
	char* buf = new char[buffer_size];
	do {
		size_t bytes = obj->read(buf, buffer_size);
		outFile.write(buf, bytes);
	} while (obj->getpos() < obj->size());
	outFile.close();
	obj->close();
	return true;
}

nlohmann::json readArchiveJson(ttvfs::File* obj) {
	if (!obj->open("rb")) {
		throw std::invalid_argument("Failed opening archive object");
	}
	std::vector<char> buffer(obj->size());
	obj->read(buffer.data(), obj->size());
	obj->close();
	const std::wstring string(buffer.begin(), buffer.end());
	return parseJsonLenient(string);
}

FileHash hashArchiveFileContents(ttvfs::File* obj) {
	if (!obj->open("rb")) {
		throw std::invalid_argument("Failed opening archive object");
	}
	std::vector<char> buffer(obj->size());
	obj->read(buffer.data(), obj->size());
	obj->close();

	std::vector<unsigned char> hash(picosha2::k_digest_size);
	picosha2::hash256(buffer.begin(), buffer.end(), hash.begin(), hash.end());
	return picosha2::bytes_to_hex_string(hash);
}

void extractArchiveObject(ttvfs::Dir& root, const std::string& objectType, const std::string& archivePath, SML::Mod::FModLoadingEntry& loadingEntry, const json& metadata) {
	ttvfs::File* objectFile = root.getFile(archivePath.c_str());
	if (objectFile == nullptr) {
		throw std::invalid_argument("object specified in data.json is missing in zip file");
	}

	//extract configuration
	if (objectType == "config") {
		//extract mod configuration into the predefined folder
		path configFilePath = getModConfigFilePath(loadingEntry.modInfo.modid);
		if (!exists(configFilePath)) {
			//only extract it if it doesn't exist already
			extractArchiveFile(configFilePath, objectFile);
		}
		return;
	}

	//extract other files into caches folder
	const FileHash fileHash = hashArchiveFileContents(objectFile);
	
	path filePath = generateTempFilePath(fileHash, objectType.c_str());
	//if cached file doesn't exist, or file hashes don't match, unpack file and copy it
	if (!exists(filePath) || fileHash != hashFileContents(filePath)) {
		//in case of broken cache file, remove old file
		remove(filePath);
		//unpack file in the temporary directory
		extractArchiveFile(filePath, objectFile);
	}
	if (objectType == "pak") {
		int32 loadingPriority = 0;
		if (metadata.is_object()) {
			metadata["loading_priority"].get_to(loadingPriority);
		}
		const std::wstring pakFilePath = filePath.generic_wstring();
		loadingEntry.pakFiles.push_back(FModPakFileEntry{ pakFilePath, loadingPriority });
	} else if (objectType == "sml_mod") {
		if (!loadingEntry.dllFilePath.empty())
			throw std::invalid_argument("mod can only have one DLL module at a time");
		loadingEntry.dllFilePath = filePath.generic_wstring();
	} else if (objectType == "core_mod") {
		throw std::invalid_argument("core mods are not supported by this version of SML");
	} else {
		throw std::invalid_argument("Unknown archive object type encountered");
	}
}

void extractArchiveObjects(ttvfs::Dir& root, const nlohmann::json& dataJson, SML::Mod::FModLoadingEntry& loadingEntry) {
	const nlohmann::json& objects = dataJson["objects"];
	if (!objects.is_array()) {
		throw std::invalid_argument("missing `objects` array in data.json");
	}
	for (auto& value : objects.items()) {
		const nlohmann::json object = value.value();
		if (!object.is_object() ||
			!object["type"].is_string() ||
			!object["path"].is_string()) {
			throw std::invalid_argument("one of object entries in data.json has invalid format");
		}
		std::string objType = object["type"].get<std::string>();
		std::string path = object["path"].get<std::string>();
		extractArchiveObject(root, objType, path, loadingEntry, object["metadata"]);
	}
}

void iterateDependencies(std::unordered_map<std::wstring, FModLoadingEntry>& loadingEntries,
	std::unordered_map<std::wstring, uint64_t>& modIndices,
	const FModInfo& selfInfo,
	std::vector<std::wstring>& missingDependencies,
	SML::TopologicalSort::DirectedGraph<uint64_t>& sortGraph,
	const std::unordered_map<std::wstring, FVersionRange>& dependencies,
	bool optional) {

	for (auto& pair : dependencies) {
		FModLoadingEntry& dependencyEntry = loadingEntries[pair.first];
		FModInfo& depInfo = dependencyEntry.modInfo;
		if (!dependencyEntry.isValid || !pair.second.matches(depInfo.version)) {
			const std::wstring reason = dependencyEntry.isValid ? formatStr(TEXT("unsupported version: "), depInfo.version.string()) : TEXT("not installed");
			const std::wstring message = formatStr(selfInfo.modid, " requires ", pair.first, "(", pair.second.string(), "): ", reason);
			if (!optional) missingDependencies.push_back(message);
			continue;
		}
		sortGraph.addEdge(modIndices[selfInfo.modid], modIndices[depInfo.modid]);
	}
}

void finalizeSortingResults(std::unordered_map<uint64_t, std::wstring>& modByIndex,
	std::unordered_map<std::wstring, FModLoadingEntry>& loadingEntries,
	std::vector<uint64_t>& sortedIndices) {
	std::vector<uint64_t> modsToMoveInTheEnd;
	for (uint64_t i = 0; i < sortedIndices.size(); i++) {
		uint64_t modIndex = sortedIndices[i];
		const FModLoadingEntry& loadingEntry = loadingEntries[modByIndex[modIndex]];
		auto dependencies = loadingEntry.modInfo.dependencies;
		if (dependencies.find(TEXT("@ORDER:LAST")) != dependencies.end())
			modsToMoveInTheEnd.push_back(i);
	}
	for (auto& modIndex : modsToMoveInTheEnd) {
		sortedIndices.erase(std::remove(sortedIndices.begin(), sortedIndices.end(), modIndex), sortedIndices.end());
		sortedIndices.push_back(modIndex);
	}
}

void populateSortedModList(std::unordered_map<uint64_t, std::wstring>& modByIndex,
	std::unordered_map<std::wstring, FModLoadingEntry>& loadingEntries,
	std::vector<uint64_t>& sortedIndices,
	std::vector<FModLoadingEntry>& sortedModLoadingList) {
	for (auto& modIndex : sortedIndices) {
		FModLoadingEntry& entry = loadingEntries[modByIndex[modIndex]];
		sortedModLoadingList.push_back(entry);
	}
}

FModLoadingEntry createSMLLoadingEntry() {
	FModLoadingEntry entry;
	entry.isValid = true;
	entry.modInfo = FModInfo::createDummyInfo(TEXT("SML"));
	entry.modInfo.name = TEXT("Satisfactory Mod Loader");
	entry.modInfo.version = getModLoaderVersion();
	entry.modInfo.description = TEXT("Mod Loading & Compatibility layer for Satisfactory");
	entry.modInfo.authors = TEXT("TODO");
	return entry;
}

IModuleInterface* InitializeSMLModule() {
	return new FSMLModule();
}

FModLoadingEntry INVALID_ENTRY{ false };

//needed here because FModuleInfo constructor references it
int32 FModuleManager::FModuleInfo::CurrentLoadOrder = 1;

//We override FModuleManager to access it's protected data members
class FModuleManagerHack : FModuleManager {
public:
	static IModuleInterface* LoadModuleFromInitializerFunc(FName moduleName, const FInitializeModuleFunctionPtr& moduleInitializer) {
		FModuleManager& moduleManager = FModuleManager::Get();
		if (moduleManager.IsModuleLoaded(moduleName)) {
			return moduleManager.GetModule(moduleName);
		}
		ModuleInfoRef moduleInfo(new FModuleInfo());
		moduleInfo->Module = TUniquePtr<IModuleInterface>(moduleInitializer());
		moduleInfo->Module->StartupModule();
		moduleManager.AddModuleToModulesList(moduleName, moduleInfo);
		//TODO: this one is not exported in PDB; not sure if it is needed
		//moduleManager.OnModulesChanged().Broadcast(moduleName, EModuleChangeReason::ModuleLoaded);
		return moduleInfo->Module.Get();
	}
};

namespace SML {
	namespace Mod {
		FModHandler::FModHandler() {}

		const std::vector<std::wstring>& FModHandler::getLoadedMods() const {
			return loadedModsModIDs;
		}

		bool FModHandler::isModLoaded(const std::wstring& modId) const {
			return loadedMods.find(modId) != loadedMods.end();
		}

		const FModContainer& FModHandler::GetLoadedMod(const std::wstring& modId) const {
			const auto loadedModWrapped = loadedMods.find(modId);
			if (loadedModWrapped == loadedMods.end()) {
				throw std::invalid_argument("Mod with provided ID is not loaded");
			}
			return *loadedModWrapped->second;
		}

		void FModHandler::loadMods(const BootstrapAccessors& accessors) {
			SML::Logging::info("Loading mods into the process address space...");
			std::map<std::wstring, HLOADEDMODULE> loadedModuleDlls;

			for (auto& loadingEntry : sortedModLoadList) {
				const std::wstring& modid = loadingEntry.modInfo.modid;
				if (!loadingEntry.dllFilePath.empty()) {
					try {
						std::string moduleName = createModuleNameFromModId(loadingEntry.modInfo.modid);
						HLOADEDMODULE module = accessors.LoadModule(moduleName.c_str(), loadingEntry.dllFilePath.c_str());
						if (module == nullptr) throw std::invalid_argument("Module not loaded");
						loadedModuleDlls.insert({ modid, module });
					} catch (std::exception& ex) {
						std::wstring message = formatStr(TEXT("Failed to load module "), modid, ": ", convertStr(ex.what()));
						SML::Logging::error(message);
						loadingProblems.push_back(message);
					}
				}
			}
			SML::Logging::info("Loading mods...");
			FModuleManager& moduleManager = FModuleManager::Get();
			std::map<std::wstring, FName> registeredModules;

			std::map<std::wstring, IModuleInterface*> loadedModules;
			//register SML module manually as it is already loaded into the process
			FName smlModuleName = FName(TEXT("SML"));
			IModuleInterface* smlModule = FModuleManagerHack::LoadModuleFromInitializerFunc(smlModuleName, &InitializeSMLModule);
			loadedModules.insert({ TEXT("SML"), smlModule });

			for (auto& pair : loadedModuleDlls) {
				const std::wstring& modid = pair.first;
				const HLOADEDMODULE loadedModule = pair.second;
				void* rawInitPtr = accessors.GetModuleProcAddress(loadedModule, "InitializeModule");
				const FInitializeModuleFunctionPtr initModule = static_cast<FInitializeModuleFunctionPtr>(rawInitPtr);
				if (initModule == nullptr) {
					std::wstring message = formatStr(TEXT("Failed to initialize module "), modid, ": InitializeModule() function not found");
					SML::Logging::error(message);
					loadingProblems.push_back(message);
					continue;
				}
				FName moduleName = FName(modid.c_str());
				IModuleInterface* moduleInterface = FModuleManagerHack::LoadModuleFromInitializerFunc(moduleName, initModule);
				loadedModules.insert({ modid, moduleInterface });
			}

			//we populate mod list here because paks can reference these lists
			//so we need to make them available prior to pak mounting
			SML::Logging::info("Populating mod list...");
			for (auto& loadingEntry : sortedModLoadList) {
				auto moduleInterface = loadedModules.find(loadingEntry.modInfo.modid);
				FModContainer* modContainer;
				if (moduleInterface != loadedModules.end()) {
					//mod has DLL, so we reference module loaded from it here
					IModuleInterface* interface = moduleInterface->second;
					modContainer = new FModContainer{ loadingEntry.modInfo, interface };
				} else {
					//mod has no DLL, it is pak-only mod, construct default mode implementation
					IModuleInterface* interface = new FDefaultModuleImpl();
					modContainer = new FModContainer{ loadingEntry.modInfo, interface };
				}
				loadedModsList.push_back(modContainer);
				loadedMods.insert({ loadingEntry.modInfo.modid, modContainer });
				loadedModsModIDs.push_back(loadingEntry.modInfo.modid);
			}

			FPakPlatformFile* pakPlatformFile = static_cast<FPakPlatformFile*>(FPlatformFileManager::Get().FindPlatformFile(TEXT("PakFile")));
			TArray<FString> mountedPakNames;
			pakPlatformFile->GetMountedPakFilenames(mountedPakNames);
			path platformPakFileName = GetData(mountedPakNames[0]);
			path pakSignatureFilePath = platformPakFileName.replace_extension(".sig");

			SML::Logging::info("Mounting mod paks...");
			for (auto& loadingEntry : sortedModLoadList) {
				for (auto& pakFileDef : loadingEntry.pakFiles) {
					std::wstring pakFilePathStr = pakFileDef.pakFilePath;
					path pakFileSystemPath(pakFilePathStr);
					path pakFileSignaturePath = pakFileSystemPath.replace_extension(".sig");
					//make sure we have signature file in place before mounting pak
					if (!exists(pakFileSignaturePath)) {
						copy_file(pakSignatureFilePath, pakFileSignaturePath);
					}
					FString filePathString(pakFilePathStr.c_str());
					FCoreDelegates::OnMountPak.Execute(filePathString, pakFileDef.loadingPriority, nullptr);
				}
				if (!loadingEntry.pakFiles.empty()) {
					//L"/Game/FactoryGame/" + modNameW + L"/InitMenu.InitMenu_C";
					const std::wstring baseInitPath = formatStr(TEXT("/Game/FactoryGame/"), loadingEntry.modInfo.modid);
					const std::wstring modInitPath = formatStr(baseInitPath, TEXT("/InitMod.InitMod_C"));
					const std::wstring menuInitPath = formatStr(baseInitPath, TEXT("/InitMenu.InitMenu_C"));
					UClass* modInitializerClass = LoadClass<AActor>(nullptr, modInitPath.c_str());
					UClass* menuInitializerClass = LoadClass<AActor>(nullptr, menuInitPath.c_str());
					if (modInitializerClass != nullptr || menuInitializerClass != nullptr) {
						//push our loader entry to the initializers list which will be called later
						modPakInitializers.push_back(FModPakLoadEntry{ loadingEntry.modInfo.modid, modInitializerClass, menuInitializerClass });
					}
				}
			}
			checkStageErrors(TEXT("mod initialization"));
		}

		UModInitializerComponent* GetOrCreateComponent(AFGGameMode* gameMode) {
			auto components = gameMode->GetComponentsByClass(UActorComponent::StaticClass());
			UActorComponent** firstComponent = components.GetData();
			uint64 arraySize = components.Num();
			for (uint64 i = 0; i < arraySize; i++) {
				UActorComponent* otherComponent = firstComponent[i];
				if (otherComponent->IsA<UModInitializerComponent>()) {
					SML::Logging::info(TEXT("Mod initializer found at "), (void*)otherComponent);
					return static_cast<UModInitializerComponent*>(otherComponent);
				}
			}
			UModInitializerComponent* component = static_cast<UModInitializerComponent*>(StaticAllocateObject(UModInitializerComponent::StaticClass(), gameMode, NAME_None, EObjectFlags::RF_Transient));
			gameMode->AddInstanceComponent(component);
			component->RegisterComponent();
			SML::Logging::info(TEXT("Created mod initializer at "), (void*)component);
			return component;
		}

		void FModHandler::attachLoadingHooks() {
			SUBSCRIBE_METHOD(AFGGameMode::InitGameState, [](CallResult<void>, AFGGameMode* gameMode) {
				//only call initializers on host worlds
				SML::Logging::info(TEXT("GAME MODE IDENTIFIER "), static_cast<void*>(gameMode), TEXT(" MAP NAME "), GetData(gameMode->GetWorld()->GetMapName()));
				if (gameMode->HasAuthority()) {
					UModInitializerComponent* component = GetOrCreateComponent(gameMode);
					SML::Logging::info(TEXT("Awesome component: "), (void*)component);
					//SML::getModHandler().onGameModePostLoad(gameMode, component);
					component->InitializeModActors();
					SML::Logging::info(TEXT("FINISHED"));
				}
			});
			SUBSCRIBE_METHOD(AFGPlayerController::BeginPlay, [](CallResult<void>, AFGPlayerController* controller) {
				SML::Logging::info(TEXT("ControllerBeginPlay "), GetData(controller->GetWorld()->GetMapName()));
				//only call initializers on host worlds
				AFGGameMode* gameMode = static_cast<AFGGameMode*>(controller->GetWorld()->GetGameState<AGameStateBase>()->AuthorityGameMode);
				if (gameMode != nullptr && gameMode->HasAuthority()) {
					UModInitializerComponent* component = GetOrCreateComponent(gameMode);
					SML::Logging::info(TEXT("COMPONENT 2: "), (void*)component);
					component->PostInitializeModActors();
				}
			});
		}

		void FModHandler::onGameModePostLoad(AFGGameMode* gameMode, UModInitializerComponent* component) {
			UWorld* world = gameMode->GetWorld();
			const bool isMenuWorld = gameMode->IsMainMenuGameMode();
			for (auto& initializer : modPakInitializers) {
				UClass* targetClass = isMenuWorld ? initializer.menuInitClass : initializer.modInitClass;
				if (targetClass != nullptr) {
					FVector position = FVector::ZeroVector;
					FRotator rotation = FRotator::ZeroRotator;
					FActorSpawnParameters spawnParams{};
					//AActor* actor = world->SpawnActor(targetClass, &position, &rotation, spawnParams);
					//component->ModInitializerActorList.Add(actor);
				}
			}
		}

		void FModHandler::checkDependencies() {
			std::vector<FModLoadingEntry> allLoadingEntries;
			std::unordered_map<std::wstring, uint64_t> modIndices;
			std::unordered_map<uint64_t, std::wstring> modByIndex;
			SML::TopologicalSort::DirectedGraph<uint64_t> sortGraph;
			uint64_t currentIdx = 1;
			//construct initial mod list, assign indices, add mod nodes
			for (auto& pair : loadingEntries) {
				allLoadingEntries.push_back(pair.second);
				uint64_t index = currentIdx++;
				modIndices.insert({ pair.first, index });
				modByIndex.insert({ index, pair.first });
				sortGraph.addNode(index);
			}

			std::vector<std::wstring> missingDependencies;
			//setup node dependencies
			for (const FModLoadingEntry& loadingEntry : allLoadingEntries) {
				const FModInfo& selfInfo = loadingEntry.modInfo;
				iterateDependencies(loadingEntries, modIndices, selfInfo, missingDependencies, sortGraph, selfInfo.dependencies, false);
				iterateDependencies(loadingEntries, modIndices, selfInfo, missingDependencies, sortGraph, selfInfo.optionalDependencies, true);
			}
			//check for missing dependencies
			if (!missingDependencies.empty()) {
				loadingProblems.push_back(TEXT("Found missing dependencies:"));
				SML::Logging::fatal(TEXT("Found missing dependencies:"));
				for (auto& dependencyLine : missingDependencies) {
					loadingProblems.push_back(dependencyLine);
					SML::Logging::fatal(dependencyLine);
				}
				return;
			}
			//perform initial dependency sorting
			std::vector<uint64_t> sortedIndices;
			try {
				sortedIndices = SML::TopologicalSort::topologicalSort(sortGraph);
			} catch (SML::TopologicalSort::cycle_detected<uint64_t>& ex) {
				std::wstring message = formatStr(TEXT("Cycle dependency found in sorting graph at modid: "), modByIndex[ex.cycleNode]);
				loadingProblems.push_back(message);
				SML::Logging::error(message);
				return;
			}
			finalizeSortingResults(modByIndex, loadingEntries, sortedIndices);
			populateSortedModList(modByIndex, loadingEntries, sortedIndices, sortedModLoadList);
			loadingEntries.clear();
			checkStageErrors(TEXT("dependency resolution"));
		};

		void FModHandler::discoverMods() {
			loadingEntries.insert({ TEXT("SML"), createSMLLoadingEntry() });
			path modsPath = SML::getModDirectory();
			for (auto& file : directory_iterator(modsPath)) {
				if (is_regular_file(file.path())) {
					if (file.path().extension() == ".smod" ||
						file.path().extension() == ".zip") {
						constructZipMod(file.path());
					} else if (file.path().extension() == ".dll") {
						constructDllMod(file.path());
					} if (file.path().extension() == ".pak") {
						constructPakMod(file.path());
					}
				}
			}
			checkStageErrors(TEXT("mod discovery"));
		};

		void FModHandler::constructZipMod(const path& filePath) {
			SML::Logging::debug(TEXT("Constructing zip mod from "), filePath);
			ttvfs::Root vfs;
			vfs.AddLoader(new ttvfs::DiskLoader);
			vfs.AddArchiveLoader(new ttvfs::VFSZipArchiveLoader);
			auto modArchive = vfs.AddArchive(filePath.generic_string().c_str());
			if (modArchive == nullptr) {
				reportBrokenZipMod(filePath, TEXT("corrupted zip file"));
				return;
			}
			ttvfs::File* dataJson = modArchive->getFile("data.json");
			if (dataJson == nullptr) {
				reportBrokenZipMod(filePath, TEXT("data.json entry is missing in zip"));
				return;
			}
			FModInfo modInfo;
			nlohmann::json dataJsonObj;
			try {
				dataJsonObj = readArchiveJson(dataJson);
				modInfo = FModInfo::createFromJson(dataJsonObj);
			} catch (std::exception& ex) {
				const std::wstring message = formatStr(TEXT("couldn't parse data.json: "), convertStr(ex.what()));
				reportBrokenZipMod(filePath, message);
				return;
			}
			FModLoadingEntry& loadingEntry = createLoadingEntry(modInfo, filePath);
			if (!loadingEntry.isValid) return;
			try {
				extractArchiveObjects(*modArchive, dataJsonObj, loadingEntry);
			} catch (std::exception& ex) {
				std::wstring message = formatStr(TEXT("Failed to extract data objects: "), convertStr(ex.what()));
				reportBrokenZipMod(filePath, message.c_str());
			}
		}

		void FModHandler::constructDllMod(const path& filePath) {
			if (!checkAndNotifyRawMod(filePath)) return;
			auto modId = getModIdFromFile(filePath);
			auto& loadingEntry = createRawModLoadingEntry(modId, filePath);
			if (!loadingEntry.isValid) return;
			loadingEntry.dllFilePath = filePath.generic_wstring();
		}

		void FModHandler::constructPakMod(const path& filePath) {
			if (!checkAndNotifyRawMod(filePath)) return;
			auto modId = getModIdFromFile(filePath);
			auto& loadingEntry = createRawModLoadingEntry(modId, filePath);
			if (!loadingEntry.isValid) return;
			loadingEntry.pakFiles.push_back(FModPakFileEntry{ filePath.generic_wstring(), 0 });
		}

		void FModHandler::checkStageErrors(const TCHAR* stageName) {
			if (!loadingProblems.empty()) {
				std::wstring message = formatStr(TEXT("Errors occurred during mod loading stage '"), stageName, TEXT("'. Loading cannot continue:\n"));
				for (auto& message : loadingProblems)
					message.append(message).append(TEXT("\n"));
				SML::Logging::fatal(message);
				SML::shutdownEngine(message);
				loadingProblems.clear();
			}
		}

		void FModHandler::reportBrokenZipMod(const path& filePath, const std::wstring& reason) {
			std::wstring message = formatStr(TEXT("Failed to load zip mod from "), filePath.generic_wstring(), reason);
			SML::Logging::fatal(message);
			loadingProblems.push_back(message);
		}

		bool FModHandler::checkAndNotifyRawMod(const path& filePath) {
			if (!SML::getSMLConfig().debugLogOutput) {
				SML::Logging::error(TEXT("Found raw mod in mods directory: "), filePath.generic_wstring());
				SML::Logging::error(TEXT("Raw mods are not supported in production mode and can be used only for development"));
				this->loadingProblems.push_back(formatStr(TEXT("Found unsupported raw mod file: "), filePath.generic_wstring()));
				return false;
			}
			SML::Logging::warning(TEXT("Loading development raw mod: "), filePath.generic_wstring());
			SML::Logging::warning(TEXT("Dependencies and versioning won't work!"));
			return true;
		}

		FModLoadingEntry& FModHandler::createLoadingEntry(const FModInfo& modInfo, const path& filePath) {
			FModLoadingEntry& loadingEntry = loadingEntries[modInfo.modid];
			if (loadingEntry.isValid) {
				std::wstring message = formatStr(TEXT("Found duplicate mods with same mod ID "), modInfo.modid, TEXT(": "),
					filePath.generic_wstring(), TEXT(" and "), loadingEntry.virtualModFilePath);
				SML::Logging::fatal(message);
				loadingProblems.push_back(message);
				return INVALID_ENTRY;
			}
			loadingEntry.isValid = true;
			loadingEntry.modInfo = modInfo;
			loadingEntry.virtualModFilePath = filePath.generic_wstring();
			return loadingEntry;
		}


		FModLoadingEntry& FModHandler::createRawModLoadingEntry(const std::wstring& modId, const path& filePath) {
			FModLoadingEntry& loadingEntry = loadingEntries[modId];
			if (!loadingEntry.isValid) {
				loadingEntry.isValid = true;
				loadingEntry.modInfo = SML::Mod::FModInfo::createDummyInfo(modId);
				loadingEntry.modInfo.dependencies.insert({ TEXT("@ORDER:LAST"), FVersionRange(TEXT("1.0.0")) });
				loadingEntry.virtualModFilePath = filePath.generic_wstring();
				loadingEntry.isRawMod = true;
			}
			if (!loadingEntry.isRawMod) {
				SML::Logging::fatal(TEXT("Found raw mod file conflicting with packed mod: "), filePath.generic_string());
				loadingProblems.push_back(formatStr(TEXT("Found raw mod file conflicting with packed mod: "), filePath.generic_string()));
				return INVALID_ENTRY;
			}
			return loadingEntry;
		}
	};
};