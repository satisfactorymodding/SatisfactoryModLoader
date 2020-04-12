#include "ModHandler.h"
#include "util/Utility.h"
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
#include "FGGameInstance.h"

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

TMap<FString, HLOADEDMODULE> loadedModuleDlls;

void FModHandler::loadDllMods(const BootstrapAccessors& accessors) {
	for (auto& loadingEntry : sortedModLoadList) {
		const FString& modid = loadingEntry.modInfo.modid;
		if (loadingEntry.dllFilePath.Len() > 0) {
			HLOADEDMODULE module = accessors.LoadModule("", *loadingEntry.dllFilePath);
			if (module == nullptr) SML::shutdownEngine(FString::Printf(TEXT("Module failed to load: %s"), *loadingEntry.dllFilePath));
			loadedModuleDlls.Add(modid, module);
		}
	}
}

void FModHandler::LoadModLibraries(const BootstrapAccessors& accessors, TMap<FString, IModuleInterface*>& loadedModules) {
	TMap<FString, FName> registeredModules;
	
	//register SML module manually as it is already loaded into the process
	FName smlModuleName = FName(TEXT("SML"));
	IModuleInterface* smlModule = FModuleManagerHack::LoadModuleFromInitializerFunc(smlModuleName, &InitializeSMLModule);
	loadedModules.Add(TEXT("SML"), smlModule);

	//Populate loaded modules map
	for (auto& pair : loadedModuleDlls) {
		const FString& modid = pair.Key;
		const HLOADEDMODULE loadedModule = pair.Value;
		void* rawInitPtr = accessors.GetModuleProcAddress(loadedModule, "InitializeModule");
		const FInitializeModuleFunctionPtr initModule = static_cast<FInitializeModuleFunctionPtr>(rawInitPtr);
		if (initModule == nullptr) {
			FString message = FString::Printf(TEXT("Failed to initialize module %s: InitializeModule() function not found"), *modid);
			SML::Logging::error(*message);
			loadingProblems.Add(message);
			continue;
		}
		FName moduleName = FName(*modid);
		IModuleInterface* moduleInterface = FModuleManagerHack::LoadModuleFromInitializerFunc(moduleName, initModule);
		loadedModules.Add(modid, moduleInterface);
	}
}

void FModHandler::PopulateModList(const TMap<FString, IModuleInterface*>& loadedModules) {
	for (auto& loadingEntry : sortedModLoadList) {
		auto moduleInterface = loadedModules.Find(loadingEntry.modInfo.modid);
		FModContainer* modContainer;
		if (moduleInterface != nullptr) {
			//mod has DLL, so we reference module loaded from it here
			IModuleInterface* interface = *moduleInterface;
			modContainer = new FModContainer{ loadingEntry.modInfo, interface };
		} else {
			//mod has no DLL, it is pak-only mod, construct default mode implementation
			IModuleInterface* interface = new FDefaultModuleImpl();
			modContainer = new FModContainer{ loadingEntry.modInfo, interface };
		}
		loadedModsList.Add(modContainer);
		loadedMods.Add(loadingEntry.modInfo.modid, modContainer);
		loadedModsModIDs.Add(loadingEntry.modInfo.modid);
	}
}

void FModHandler::MountModPaks() {
	FPakPlatformFile* pakPlatformFile = static_cast<FPakPlatformFile*>(FPlatformFileManager::Get().FindPlatformFile(TEXT("PakFile")));
	TArray<FString> mountedPakNames;
	pakPlatformFile->GetMountedPakFilenames(mountedPakNames);
	FString platformPakFileName = GetData(mountedPakNames[0]);
	const FString gamePakSignaturePath = FPaths::ChangeExtension(platformPakFileName, TEXT("sig"));
	
	for (auto& loadingEntry : sortedModLoadList) {
		for (auto& pakFileDef : loadingEntry.pakFiles) {
			FString pakFilePathStr = pakFileDef.pakFilePath;
			FString modPakSignaturePath = FPaths::ChangeExtension(pakFilePathStr, TEXT("sig"));
			//make sure we have signature file in place before mounting pak
			if (!FPaths::FileExists(modPakSignaturePath)) {
				FPlatformFileManager::Get().GetPlatformFile().CopyFile(*modPakSignaturePath, *gamePakSignaturePath);
			}

			FCoreDelegates::OnMountPak.Execute(pakFilePathStr, pakFileDef.loadingPriority, nullptr);
		}
		if (loadingEntry.pakFiles.Num() > 0) {
			const FModPakLoadEntry pakEntry = CreatePakLoadEntry(loadingEntry.modInfo.modid);
			modPakInitializers.Add(pakEntry);
		}
	}
}

void FModHandler::loadMods(const BootstrapAccessors& accessors) {
	TMap<FString, IModuleInterface*> loadedModules;
	
	SML::Logging::info("Loading mods...");
	LoadModLibraries(accessors, loadedModules);
	
	SML::Logging::info("Populating mod list...");
	PopulateModList(loadedModules);

	SML::Logging::info("Mounting mod paks...");
	MountModPaks();
	
	checkStageErrors(TEXT("mod initialization"));
}

void FModHandler::attachLoadingHooks() {
	SUBSCRIBE_METHOD("?ReceivedGameModeClass@AGameState@@UEAAXXZ", AGameStateBase::ReceivedGameModeClass, [](auto& scope, AGameStateBase* gameMode) {
		UWorld* World = gameMode->GetWorld();
		const FString MapName = World->GetPathName();
		SML::Logging::info(TEXT("Initializing on map "), *MapName, TEXT(". Is Menu? "), SML::IsMenuMapName(MapName));
		SML::getModHandler().onMapLoadComplete(World, SML::IsMenuMapName(MapName));
		SML::getModHandler().initializeModActors();
		SML::Logging::info(TEXT("Finished initializing mod actors"));
	});
	SUBSCRIBE_METHOD("?LoadComplete@UFGGameInstance@@MEAAXMAEBVFString@@@Z", UFGGameInstance::LoadComplete, [](auto& scope, UFGGameInstance* thisPtr, const float, const FString& MapName) {
		SML::getModHandler().postInitializeModActors();
		SML::Logging::info(TEXT("Finished post initializing mod actors"));
	});
	SUBSCRIBE_METHOD("?BeginPlay@AFGPlayerController@@UEAAXXZ", AFGPlayerController::BeginPlay, [](auto& scope, AFGPlayerController* controller) {
		SML::getModHandler().handlePlayerJoin(controller);
	});
}

UClass* GetActiveLoadClass(const FModPakLoadEntry& entry, bool isMenuWorld) {
	return isMenuWorld ? static_cast<UClass*>(entry.menuInitClass) : static_cast<UClass*>(entry.modInitClass);
}

void FModHandler::onMapLoadComplete(UWorld* World, bool isMenuWorld) {
	modInitializerActorList.Empty();
	for (auto& initializer : modPakInitializers) {
		UClass* targetClass = GetActiveLoadClass(initializer, isMenuWorld);
		if (targetClass == nullptr) {
			continue;
		}
		FVector position = FVector::ZeroVector;
		FRotator rotation = FRotator::ZeroRotator;
		FActorSpawnParameters spawnParams{};
		AActor* actor = World->SpawnActor(targetClass, &position, &rotation, spawnParams);
		modInitializerActorList.Add(actor);
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

void FModHandler::initializeModActors() {
	SML::Logging::info(TEXT("Initializing mod content packages..."));
	for (AActor* Actor : this->modInitializerActorList) {
		if (Actor->IsValidLowLevel()) {
			if (ASMLInitMod* InitMod = Cast<ASMLInitMod>(Actor)) {
				SML::Logging::info(TEXT("Initializing mod "), *Actor->GetClass()->GetPathName());
				InitMod->Init();
				SML::Logging::debug(TEXT("Done initializing mod "), *Actor->GetClass()->GetPathName());
			}
			if (ASMLInitMenu* InitMenu = Cast<ASMLInitMenu>(Actor)) {
				SML::Logging::info(TEXT("Initializing menu of mod "), *Actor->GetClass()->GetPathName());
				InitMenu->Init();
				SML::Logging::debug(TEXT("Done initializing menu of mod "), *Actor->GetClass()->GetPathName());
			}
		}
	}
	SML::Logging::debug(TEXT("Done initializing mod content packages"));
}

void FModHandler::postInitializeModActors() {
	SML::Logging::info(TEXT("Post-initializing mod content packages..."));
	for (AActor* Actor : this->modInitializerActorList) {
		if (Actor->IsValidLowLevel()) {
			if (ASMLInitMod* InitMod = Cast<ASMLInitMod>(Actor)) {
				SML::Logging::info(TEXT("Post-initializing mod "), *Actor->GetClass()->GetPathName());
				InitMod->LoadModContent();
				InitMod->PostInit();
				SML::Logging::debug(TEXT("Done post-initializing mod "), *Actor->GetClass()->GetPathName());
			}
		}
	}
	SML::Logging::debug(TEXT("Done post-initializing mod content packages"));
}

void FModHandler::handlePlayerJoin(AFGPlayerController* PlayerController) {
	SML::Logging::info(TEXT("HandlePlayerJoin "), *PlayerController->PlayerState->GetPlayerName());
	for (AActor* Actor : this->modInitializerActorList) {
		if (Actor->IsValidLowLevel()) {
			if (ASMLInitMod* InitMod = Cast<ASMLInitMod>(Actor)) {
				InitMod->PlayerJoined(PlayerController);
			}
		}
	}
}

void FModHandler::checkDependencies() {
	TArray<FModLoadingEntry> allLoadingEntries;
	TMap<FString, uint64_t> modIndices;
	TMap<uint64_t, FString> modByIndex;
	SML::TopologicalSort::DirectedGraph<uint64_t> sortGraph;
	uint64_t currentIdx = 1;
	//construct initial mod list, assign indices, add mod nodes
	for (auto& pair : loadingEntries) {
		allLoadingEntries.Add(pair.Value);
		uint64_t index = currentIdx++;
		modIndices.Add(pair.Key, index);
		modByIndex.Add(index, pair.Key);
		sortGraph.addNode(index);
	}

	TArray<FString> missingDependencies;
	//setup node dependencies
	for (const FModLoadingEntry& loadingEntry : allLoadingEntries) {
		const FModInfo& selfInfo = loadingEntry.modInfo;
		iterateDependencies(loadingEntries, modIndices, selfInfo, missingDependencies, sortGraph, selfInfo.dependencies, false);
		iterateDependencies(loadingEntries, modIndices, selfInfo, missingDependencies, sortGraph, selfInfo.optionalDependencies, true);
	}
	//check for missing dependencies
	if (missingDependencies.Num() > 0) {
		loadingProblems.Add(TEXT("Found missing dependencies:"));
		SML::Logging::error(TEXT("Found missing dependencies:"));
		for (auto& dependencyLine : missingDependencies) {
			SML::Logging::error(*dependencyLine);
			loadingProblems.Add(dependencyLine);
		}
		SML::shutdownEngine(TEXT("Cannot continue loading without dependencies"));
		return;
	}
	//perform initial dependency sorting
	TArray<uint64_t> sortedIndices;
	try {
		sortedIndices = SML::TopologicalSort::topologicalSort(sortGraph);
	} catch (SML::TopologicalSort::cycle_detected<uint64_t>& ex) {
		FString message = FString::Printf(TEXT("Cycle dependency found in sorting graph at modid: %s"), *modByIndex[ex.cycleNode]);
		loadingProblems.Add(message);
		SML::Logging::error(*message);
		return;
	}
	finalizeSortingResults(modByIndex, loadingEntries, sortedIndices);
	populateSortedModList(modByIndex, loadingEntries, sortedIndices, sortedModLoadList);
	loadingEntries.Empty();
	checkStageErrors(TEXT("dependency resolution"));
};



void FModHandler::discoverMods() {
	loadingEntries.Add(TEXT("SML"), createSMLLoadingEntry());
	FString modsPath = SML::getModDirectory();
	auto directoryVisitor = MakeDirectoryVisitor([this](const TCHAR* filepath, bool isDir) {
		if (!isDir) {
			if (FPaths::GetExtension(filepath) == TEXT("smod") ||
				FPaths::GetExtension(filepath) == TEXT("zip")) {
				constructZipMod(filepath);
			}
			else if (FPaths::GetExtension(filepath) == TEXT("dll")) {
				constructDllMod(filepath);
			} if (FPaths::GetExtension(filepath) == TEXT("pak")) {
				constructPakMod(filepath);
			}
		}
		return true;
	});
	FPlatformFileManager::Get().GetPlatformFile().IterateDirectory(*modsPath, directoryVisitor);
	checkStageErrors(TEXT("mod discovery"));
};

void FModHandler::constructZipMod(const FString& filePath) {
	SML::Logging::debug(TEXT("Constructing zip mod from "), *filePath);
	ttvfs::Root vfs;
	vfs.AddLoader(new ttvfs::DiskLoader);
	vfs.AddArchiveLoader(new ttvfs::VFSZipArchiveLoader);
	auto modArchive = vfs.AddArchive(TCHAR_TO_ANSI(*filePath));
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
	const TSharedPtr<FJsonObject>& dataJsonObj = readArchiveJson(dataJson);
	if (!dataJsonObj.IsValid() || !FModInfo::isValid(*dataJsonObj.Get(), filePath)) {
		reportBrokenZipMod(filePath, TEXT("Invalid data.json"));
		return;
	}
	modInfo = FModInfo::createFromJson(*dataJsonObj.Get());
	FModLoadingEntry& loadingEntry = createLoadingEntry(modInfo, filePath);
	if (!loadingEntry.isValid) return;
	if (!extractArchiveObjects(*modArchive, *dataJsonObj.Get(), loadingEntry)) {
		FString message = TEXT("Failed to extract data objects");
		reportBrokenZipMod(filePath, message);
	}
}

void FModHandler::constructDllMod(const FString& filePath) {
	if (!checkAndNotifyRawMod(filePath)) return;
	auto modId = getModIdFromFile(filePath);
	auto& loadingEntry = createRawModLoadingEntry(modId, filePath);
	if (!loadingEntry.isValid) return;
	loadingEntry.dllFilePath = filePath;
}

void FModHandler::constructPakMod(const FString& filePath) {
	if (!checkAndNotifyRawMod(filePath)) return;
	auto modId = getModIdFromFile(filePath);
	auto& loadingEntry = createRawModLoadingEntry(modId, filePath);
	if (!loadingEntry.isValid) return;
	loadingEntry.pakFiles.Add(FModPakFileEntry{ filePath, 0 });
}

const TArray<FString>& FModHandler::getLoadedMods() const {
	return loadedModsModIDs;
}

bool FModHandler::isModLoaded(const FString& modId) const {
	return loadedMods.Find(modId) != nullptr;
}

const FModContainer& FModHandler::getLoadedMod(const FString& modId) const {
	const auto loadedModWrapped = loadedMods.Find(modId);
	if (loadedModWrapped == nullptr) {
		SML::shutdownEngine(FString::Printf(TEXT("Mod with provided ID is not loaded: %s"), *modId));
	}
	return **loadedModWrapped;
}

void FModHandler::checkStageErrors(const TCHAR* stageName) {
	if (loadingProblems.Num() > 0) {
		FString message = FString::Printf(TEXT("Errors occurred during mod loading stage '%s'. Loading cannot continue:\n"), stageName);
		for (auto& problem : loadingProblems)
			message.Append(problem).Append(TEXT("\n"));
		SML::shutdownEngine(*message);
		loadingProblems.Empty();
	}
}

void FModHandler::reportBrokenZipMod(const FString& filePath, const FString& reason) {
	FString message = FString::Printf(TEXT("Failed to load zip mod from %s(%s)"), *filePath, *reason);
	loadingProblems.Add(message);
	SML::Logging::error(*message);
}

bool FModHandler::checkAndNotifyRawMod(const FString& filePath) {
	if (!SML::getSMLConfig().developmentMode) {
		SML::Logging::error(TEXT("Found raw mod in mods directory: "), *filePath);
		SML::Logging::error(TEXT("Raw mods are not supported in production mode and can be used only for development"));
		this->loadingProblems.Add(FString::Printf(TEXT("Found unsupported raw mod file: %s"), *filePath));
		return false;
	}
	SML::Logging::warning(TEXT("Loading development raw mod: "), *filePath);
	SML::Logging::warning(TEXT("Dependencies and versioning won't work!"));
	return true;
}

FModLoadingEntry& FModHandler::createLoadingEntry(const FModInfo& modInfo, const FString& filePath) {
	if (loadingEntries.Find(modInfo.modid) == nullptr)
		loadingEntries.Add(modInfo.modid);
	FModLoadingEntry& loadingEntry = loadingEntries[modInfo.modid];
	if (loadingEntry.isValid) {
		FString message = FString::Printf(TEXT("Found duplicate mods with same mod ID %s: %s and %s"), *modInfo.modid, *filePath, *loadingEntry.virtualModFilePath);
		loadingProblems.Add(message);
		SML::Logging::fatal(*message);
		return INVALID_ENTRY;
	}
	loadingEntry.isValid = true;
	loadingEntry.modInfo = modInfo;
	loadingEntry.virtualModFilePath = filePath;
	return loadingEntry;
}


FModLoadingEntry& FModHandler::createRawModLoadingEntry(const FString& modId, const FString& filePath) {
	if (loadingEntries.Find(modId) == nullptr)
		loadingEntries.Add(modId);
	FModLoadingEntry& loadingEntry = loadingEntries[modId];
	if (!loadingEntry.isValid) {
		loadingEntry.isValid = true;
		loadingEntry.modInfo = SML::Mod::FModInfo::createDummyInfo(modId);
		loadingEntry.modInfo.dependencies.Add(TEXT("@ORDER:LAST"), FVersionRange(TEXT("1.0.0")));
		loadingEntry.virtualModFilePath = filePath;
		loadingEntry.isRawMod = true;
	}
	if (!loadingEntry.isRawMod) {
        FString message = FString::Printf(TEXT("Found raw mod file conflicting with packed mod: %s"), *filePath);
		SML::Logging::fatal(*message);
		loadingProblems.Add(message);
		return INVALID_ENTRY;
	}
	return loadingEntry;
}