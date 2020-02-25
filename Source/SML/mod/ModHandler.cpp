#include "ModHandler.h"
#include <filesystem>
#include "util/Utility.h"
#include "util/json.hpp"
#include "util/Logging.h"
#include "util/picosha2.h"
#include "zip/ttvfs/ttvfs.h"
#include "zip/ttvfs_zip/ttvfs_zip.h"
#include "util/TopologicalSort.h"
#include "util/Internal.h"
#include "util/bootstrapper_exports.h"
#include "Engine/World.h"
#include "PlatformFilemanager.h"
#include "IPlatformFilePak.h"
#include "FGGameMode.h"
#include "CoreDelegates.h"
#include "hooking.h"
#include "FGPlayerController.h"
#include "ModHandlerInternal.h"

using namespace SML;
using namespace Mod;

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
		{
			FScopeLock Lock(&moduleManager.ModulesCriticalSection);

			// Update hash table
			moduleManager.Modules.Add(moduleName, moduleInfo);
		}

		//TODO: this is AddModuleToModulesList. Not sure if exported, not sure if needed
		//FModuleManager::Get().ModulesChangedEvent.Broadcast(InModuleName, EModuleChangeReason::PluginDirectoryChanged);
		
		//TODO: this one is not exported in PDB; not sure if it is needed
		//moduleManager.OnModulesChanged().Broadcast(moduleName, EModuleChangeReason::ModuleLoaded);
		return moduleInfo->Module.Get();
	}
};

FModHandler::FModHandler() {}

std::map<std::wstring, HLOADEDMODULE> loadedModuleDlls;

void FModHandler::loadDllMods(const BootstrapAccessors& accessors) {
	for (auto& loadingEntry : sortedModLoadList) {
		const std::wstring& modid = loadingEntry.modInfo.modid;
		if (!loadingEntry.dllFilePath.empty()) {
			std::string moduleName = createModuleNameFromModId(loadingEntry.modInfo.modid);
			HLOADEDMODULE module = accessors.LoadModule(moduleName.c_str(), loadingEntry.dllFilePath.c_str());
			if (module == nullptr) SML::shutdownEngine(formatStr(TEXT("Module failed to load: "), moduleName));
			loadedModuleDlls.insert({ modid, module });
		}
	}
}

void FModHandler::LoadModLibraries(const BootstrapAccessors& accessors, std::map<std::wstring, IModuleInterface*>& loadedModules) {
	std::map<std::wstring, FName> registeredModules;
	
	//register SML module manually as it is already loaded into the process
	FName smlModuleName = FName(TEXT("SML"));
	IModuleInterface* smlModule = FModuleManagerHack::LoadModuleFromInitializerFunc(smlModuleName, &InitializeSMLModule);
	loadedModules.insert({ TEXT("SML"), smlModule });

	//Populate loaded modules map
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
}

void FModHandler::PopulateModList(const std::map<std::wstring, IModuleInterface*>& loadedModules) {
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
}

void FModHandler::MountModPaks() {
	FPakPlatformFile* pakPlatformFile = static_cast<FPakPlatformFile*>(FPlatformFileManager::Get().FindPlatformFile(TEXT("PakFile")));
	TArray<FString> mountedPakNames;
	pakPlatformFile->GetMountedPakFilenames(mountedPakNames);
	path platformPakFileName = GetData(mountedPakNames[0]);
	const path pakSignatureFilePath = platformPakFileName.replace_extension(".sig");
	
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
			const FModPakLoadEntry pakEntry = CreatePakLoadEntry(loadingEntry.modInfo.modid);
			modPakInitializers.push_back(pakEntry);
		}
	}
}

void FModHandler::loadMods(const BootstrapAccessors& accessors) {
	std::map<std::wstring, IModuleInterface*> loadedModules;
	
	SML::Logging::info("Loading mods...");
	LoadModLibraries(accessors, loadedModules);
	
	SML::Logging::info("Populating mod list...");
	PopulateModList(loadedModules);

	SML::Logging::info("Mounting mod paks...");
	MountModPaks();
	
	checkStageErrors(TEXT("mod initialization"));
}

//because current hooking doesn't support const instance methods properly yet
class MapFindHookProto {
public: const FString* Find(const FName&) { return nullptr; }
};

static bool shouldLogAssetFinds = false;

void FModHandler::attachLoadingHooks() {
	SUBSCRIBE_METHOD("?InitGameState@AFGGameMode@@UEAAXXZ", AFGGameMode::InitGameState, [](CallResult<void>&, AFGGameMode* gameMode) {
		//only call initializers on host worlds
		SML::Logging::debug(TEXT("AFGGameMode::InitGameState on map "), *gameMode->GetWorld()->GetMapName());
		if (gameMode->HasAuthority()) {
			SML::getModHandler().onGameModePostLoad(gameMode);
			SML::getModHandler().initializeModActors();
			SML::Logging::info(TEXT("Finished initializing mod actors"));
		}
	});
	SUBSCRIBE_METHOD("?BeginPlay@AFGPlayerController@@UEAAXXZ", AFGPlayerController::BeginPlay, [](CallResult<void>&, AFGPlayerController* controller) {
		SML::Logging::debug(TEXT("AFGPlayerController::BeginPlay on "), GetData(controller->GetWorld()->GetMapName()));
		//only call initializers on host worlds
		AFGGameMode* gameMode = static_cast<AFGGameMode*>(controller->GetWorld()->GetGameState<AGameStateBase>()->AuthorityGameMode);
		if (gameMode != nullptr && gameMode->HasAuthority()) {
			SML::getModHandler().postInitializeModActors();
		}
	});
}

UClass* GetActiveLoadClass(const FModPakLoadEntry& entry, bool isMenuWorld) {
	return isMenuWorld ? (UClass*)entry.menuInitClass : (UClass*)entry.modInitClass;
}

void FModHandler::onGameModePostLoad(AFGGameMode* gameMode) {
	shouldLogAssetFinds = true;
	UWorld* world = gameMode->GetWorld();
	const bool isMenuWorld = gameMode->IsMainMenuGameMode();
	modInitializerActorList.clear();
	for (auto& initializer : modPakInitializers) {
		SML::Logging::debug(TEXT("MENU INIT "), initializer.menuInitClass, TEXT(" MOD INIT "), initializer.modInitClass, TEXT(" IS MENU WORLD "), isMenuWorld);
		UClass* targetClass = GetActiveLoadClass(initializer, isMenuWorld);
		if (targetClass == nullptr) {
			continue;
		}
		FVector position = FVector::ZeroVector;
		FRotator rotation = FRotator::ZeroRotator;
		FActorSpawnParameters spawnParams{};
		SML::Logging::debug(TEXT("ACTOR CLASS "), GetData(targetClass->GetPathName()), TEXT(" IS AACTOR "), targetClass->IsChildOf(AActor::StaticClass()));
		AActor* actor = world->SpawnActor(targetClass, &position, &rotation, spawnParams);
		if (actor != nullptr) {
			SML::Logging::debug(TEXT("SPAWNED ACTOR "), GetData(actor->GetFullName()));
		}
		modInitializerActorList.push_back(actor);
	}
}

struct ModInitializerParams {
	FString Mods = FString(TEXT("")); // default constructor is not in the exe
};

bool CallActorFunction(AActor* actor, const FName& functionName) {
	UFunction* function = actor->FindFunction(functionName);
	if (function == nullptr) {
		return false;
	}
	ModInitializerParams params;
	actor->ProcessEvent(function, &params);
	return true;
}

void FModHandler::initializeMenuActors() {
	SML::Logging::info(TEXT("Initializing mod content packages..."));
	for (AActor* actor : this->modInitializerActorList) {
		if (actor != nullptr) {
			AInitMenu* initMenu = Cast<AInitMenu>(actor);
			if (initMenu) {
				SML::Logging::info(TEXT("Initializing menu of mod "), *actor->GetClass()->GetPathName());
				initMenu->Init();
				SML::Logging::debug(TEXT("Done initializing menu of mod "), *actor->GetClass()->GetPathName());
			}
		}
	}
	SML::Logging::debug(TEXT("Done initializing mod content packages"));
}

void FModHandler::initializeModActors() {
	SML::Logging::info(TEXT("Initializing mod content packages..."));
	for (AActor* actor : this->modInitializerActorList) {
		if (actor != nullptr) {
			AInitMod* initMod = Cast<AInitMod>(actor);
			if (initMod) {
				SML::Logging::info(TEXT("Initializing mod "), *actor->GetClass()->GetPathName());
				initMod->Init();
				SML::Logging::debug(TEXT("Done initializing mod "), *actor->GetClass()->GetPathName());
			}
		}
	}
	SML::Logging::debug(TEXT("Done initializing mod content packages"));
}

void FModHandler::postInitializeModActors() {
	SML::Logging::info(TEXT("Post-initializing mod content packages..."));
	for (AActor* actor : this->modInitializerActorList) {
		if (actor != nullptr) {
			AInitMod* initMod = Cast<AInitMod>(actor);
			if (initMod) {
				SML::Logging::info(TEXT("Post-initializing mod "), *actor->GetClass()->GetPathName());
				initMod->LoadSchematics();
				initMod->PostInit();
				SML::Logging::debug(TEXT("Done post-initializing mod "), *actor->GetClass()->GetPathName());
			}
		}
	}
	SML::Logging::debug(TEXT("Done post-initializing mod content packages"));
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
		SML::Logging::error(TEXT("Found missing dependencies:"));
		for (auto& dependencyLine : missingDependencies) {
			loadingProblems.push_back(dependencyLine);
			SML::Logging::error(dependencyLine);
		}
		SML::shutdownEngine(TEXT("Cannot continue loading without dependencies"));
		return;
	}
	//perform initial dependency sorting
	std::vector<uint64_t> sortedIndices;
	/*try {*/
		sortedIndices = SML::TopologicalSort::topologicalSort(sortGraph);
	/*} catch (SML::TopologicalSort::cycle_detected<uint64_t>& ex) {
		std::wstring message = formatStr(TEXT("Cycle dependency found in sorting graph at modid: "), modByIndex[ex.cycleNode]);
		loadingProblems.push_back(message);
		SML::Logging::error(message);
		return;
	}*/
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
	dataJsonObj = readArchiveJson(dataJson);
	if (!FModInfo::isValid(dataJsonObj, filePath)) {
		reportBrokenZipMod(filePath, TEXT("Invalid data.json"));
		return;
	}
	modInfo = FModInfo::createFromJson(dataJsonObj);
	FModLoadingEntry& loadingEntry = createLoadingEntry(modInfo, filePath);
	if (!loadingEntry.isValid) return;
	if (!extractArchiveObjects(*modArchive, dataJsonObj, loadingEntry)) {
		std::wstring message = formatStr(TEXT("Failed to extract data objects"));
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

const std::vector<std::wstring>& FModHandler::getLoadedMods() const {
	return loadedModsModIDs;
}

bool FModHandler::isModLoaded(const std::wstring& modId) const {
	return loadedMods.find(modId) != loadedMods.end();
}

const FModContainer& FModHandler::getLoadedMod(const std::wstring& modId) const {
	const auto loadedModWrapped = loadedMods.find(modId);
	if (loadedModWrapped == loadedMods.end()) {
		SML::shutdownEngine(formatStr(TEXT("Mod with provided ID is not loaded: "), modId));
	}
	return *loadedModWrapped->second;
}

void FModHandler::checkStageErrors(const TCHAR* stageName) {
	if (!loadingProblems.empty()) {
		std::wstring message = formatStr(TEXT("Errors occurred during mod loading stage '"), stageName, TEXT("'. Loading cannot continue:\n"));
		for (auto& problem : loadingProblems)
			message.append(problem).append(TEXT("\n"));
		SML::shutdownEngine(message);
		loadingProblems.clear();
	}
}

void FModHandler::reportBrokenZipMod(const path& filePath, const std::wstring& reason) {
	std::wstring message = formatStr(TEXT("Failed to load zip mod from "), filePath.generic_wstring(), TEXT(" ("), reason, TEXT(")"));
	SML::Logging::error(message);
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