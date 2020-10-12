#include "ModHandler.h"
#include "util/Utility.h"
#include "util/Logging.h"
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
#include "FGGameState.h"
#include "GameInstanceInitSubsystem.h"
#include "actor/SMLInitMod.h"
#include "SML/registry/ModContentRegistry.h"

using namespace SML;

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

void FModHandler::LoadDllMods(const BootstrapAccessors& accessors) {
	for (auto& loadingEntry : SortedModLoadList) {
		const FString& modid = loadingEntry.ModInfo.Modid;
		if (loadingEntry.DLLFilePath.Len() > 0) {
			HLOADEDMODULE module = accessors.LoadModule("", *loadingEntry.DLLFilePath);
			if (module == nullptr) SML::ShutdownEngine(FString::Printf(TEXT("Module failed to load: %s"), *loadingEntry.DLLFilePath));
			loadedModuleDlls.Add(modid, module);
		}
	}
}

void FModHandler::LoadModLibraries(const BootstrapAccessors& accessors, TMap<FString, IModuleInterface*>& loadedModules) {
	TMap<FString, FName> RegisteredModules;
	
	//register SML module manually as it is already loaded into the process
	const FName SmlModuleName = FName(TEXT("SML"));
	IModuleInterface* SmlModule = FModuleManagerHack::LoadModuleFromInitializerFunc(SmlModuleName, &InitializeSMLModule);
	loadedModules.Add(TEXT("SML"), SmlModule);

	//Populate loaded modules map
	for (auto& pair : loadedModuleDlls) {
		const FString& modid = pair.Key;
		const HLOADEDMODULE loadedModule = pair.Value;
		void* rawInitPtr = accessors.GetModuleProcAddress(loadedModule, "InitializeModule");
		const FInitializeModuleFunctionPtr initModule = static_cast<FInitializeModuleFunctionPtr>(rawInitPtr);
		if (initModule == nullptr) {
			FString message = FString::Printf(TEXT("Failed to initialize module %s: InitializeModule() function not found"), *modid);
			SML::Logging::error(*message);
			LoadingProblems.Add(message);
			continue;
		}
		const FName ModuleName = FName(*modid);
		IModuleInterface* moduleInterface = FModuleManagerHack::LoadModuleFromInitializerFunc(ModuleName, initModule);
		loadedModules.Add(modid, moduleInterface);
	}
}

void FModHandler::PopulateModList(const TMap<FString, IModuleInterface*>& loadedModules) {
	for (auto& loadingEntry : SortedModLoadList) {
		const auto moduleInterface = loadedModules.Find(loadingEntry.ModInfo.Modid);
		FModContainer* modContainer;
		if (moduleInterface != nullptr) {
			//mod has DLL, so we reference module loaded from it here
			IModuleInterface* interface = *moduleInterface;
			modContainer = new FModContainer{ loadingEntry.ModInfo, interface, loadingEntry.CustomFilePaths };
		} else {
			//mod has no DLL, it is pak-only mod, construct default module implementation
			IModuleInterface* interface = new FDefaultModuleImpl();
			modContainer = new FModContainer{ loadingEntry.ModInfo, interface };
		}
		LoadedModsList.Add(modContainer);
		LoadedMods.Add(loadingEntry.ModInfo.Modid, modContainer);
		LoadedModReferences.Add(loadingEntry.ModInfo.Modid);
	}
}

void FModHandler::MountModPaks() {
	FPakPlatformFile* PakPlatformFile = static_cast<FPakPlatformFile*>(FPlatformFileManager::Get().FindPlatformFile(TEXT("PakFile")));
	TArray<FString> mountedPakNames;
	PakPlatformFile->GetMountedPakFilenames(mountedPakNames);
	const FString PlatformPakFileName = GetData(mountedPakNames[0]);
	const FString gamePakSignaturePath = FPaths::ChangeExtension(PlatformPakFileName, TEXT("sig"));

	//Mount all paks in the order specified by dependencies, but don't actually load anything from them
	for (auto& loadingEntry : SortedModLoadList) {
		for (auto& pakFileDef : loadingEntry.PakFiles) {
			FString pakFilePathStr = pakFileDef.PakFilePath;
			FString modPakSignaturePath = FPaths::ChangeExtension(pakFilePathStr, TEXT("sig"));
			//make sure we have signature file in place before mounting pak
			if (!FPaths::FileExists(modPakSignaturePath)) {
				FPlatformFileManager::Get().GetPlatformFile().CopyFile(*modPakSignaturePath, *gamePakSignaturePath);
			}
			FCoreDelegates::OnMountPak.Execute(pakFilePathStr, pakFileDef.LoadingPriority, nullptr);
		}
	}

	//Initialize overwrite lists for mods prior to loading anything
	for (auto& loadingEntry : SortedModLoadList) {
		AModContentRegistry::DiscoverOverwriteListForModReference(loadingEntry.ModInfo.Modid);
	}

	//Initialize UClasses for InitMod and InitMenu for each mod, preload their contents on the start and pin them in GC Root
	for (auto& loadingEntry : SortedModLoadList) {
		if (loadingEntry.PakFiles.Num() > 0) {
			const FModPakLoadEntry pakEntry = CreatePakLoadEntry(loadingEntry.ModInfo.Modid);
			ModPakInitializers.Add(pakEntry);
		}
	}
}

void FModHandler::LoadMods(const BootstrapAccessors& accessors) {
	TMap<FString, IModuleInterface*> loadedModules;
	
	SML::Logging::info("Loading mods...");
	LoadModLibraries(accessors, loadedModules);
	
	SML::Logging::info("Populating mod list...");
	PopulateModList(loadedModules);

	SML::Logging::info("Mounting mod paks...");
	MountModPaks();
	
	CheckStageErrors(TEXT("mod initialization"));
}

#define FOR_EACH_MOD_INITIALIZER_ORDERED(ActorMap, Action) \
	for (const FString& ModReference : LoadedModReferences) { \
		ABasicModInit* const* ModInitializer = ActorMap.Find(ModReference); \
		if (ModInitializer != nullptr) { \
			Action(*ModInitializer); \
		} \
	}

UClass* GetActiveInitializerClass(const FModPakLoadEntry& Initializer, const bool bIsMenuWorld) {
	UClass* TargetActorClass;
	if (!bIsMenuWorld) {
		TargetActorClass = Initializer.InitGameWorldClass;
		if (TargetActorClass == NULL) {
			TargetActorClass = Initializer.LegacyInitModClass;
		}
	} else {
		TargetActorClass = Initializer.InitMenuWorldClass;
	}
	return TargetActorClass;
}

FString FormatModActorName(const FString& ModReference, const bool bIsMenuWorld) {
	if (!bIsMenuWorld) {
		return FString::Printf(TEXT("InitGameWorld_%s"), *ModReference);
	}
	return FString::Printf(TEXT("InitMenuWorld_%s"), *ModReference);
}

bool IsMenuWorldObject(UWorld* World) {
	return IsMenuMapName(World->GetMapName());
}

void FModHandler::SubscribeToLifecycleEvents() {
	//Spawn mod actors as soon as world actors are initialized (e.g static map objects are spawned)
	FWorldDelegates::OnWorldInitializedActors.AddLambda([this](const UWorld::FActorsInitializedParams Params){
		UWorld* World = Params.World;
		const bool bIsMenuWorld = IsMenuWorldObject(World);
		TMap<FString, ABasicModInit*> SpawnedActorMap;
		//Construct mod actors and dispatch CONSTRUCTION on them immediately
		Logging::info(TEXT("Constructing mod actors on map "), *World->GetMapName());
		SpawnModActors(World, bIsMenuWorld, SpawnedActorMap);
		//Initialize mod actors and dispatch INITIALIZATION on them
		Logging::info(TEXT("Initializing mod actors"));
		FOR_EACH_MOD_INITIALIZER_ORDERED(SpawnedActorMap, [](ABasicModInit* ModInit) {
			ModInit->DispatchLifecyclePhase(ELifecyclePhase::INITIALIZATION);
		});
		Logging::info(TEXT("Finished initializing mod actors"));
	});

	//Post initialize mod actors when world is fully loaded and is ready to be used
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddLambda([this](UWorld* World){
		//Find spawned mod actors and dispatch POST_INITIALIZATION on them
		TMap<FString, ABasicModInit*> SpawnedActorMap;
		FindModActors(World, SpawnedActorMap);
		Logging::info(TEXT("Post-initializing mod actors"));
		FOR_EACH_MOD_INITIALIZER_ORDERED(SpawnedActorMap, [](ABasicModInit* ModInit) {
            ModInit->DispatchLifecyclePhase(ELifecyclePhase::POST_INITIALIZATION);
        });
		Logging::info(TEXT("Finished post-initializing mod actors"));
	});
}

void FModHandler::InitializeGameInstance() {
	UGameEngine* GameEngine = Cast<UGameEngine>(GEngine);
	checkf(GameEngine, TEXT("Attempt to call FModHandler::InitializeGameInstance() in editor. This is not supported."));
	UFGGameInstance* GameInstance = Cast<UFGGameInstance>(GameEngine->GameInstance);
	checkf(GameInstance, TEXT("GameInstance set is not UFGGameInstance"));
	UGameInstanceInitSubsystem* InitSubsystem = GameInstance->GetSubsystem<UGameInstanceInitSubsystem>();
	check(InitSubsystem);
	for (const FModPakLoadEntry& LoadEntry : ModPakInitializers) {
		const FString& ModReference = LoadEntry.ModReference;
		UClass* InitClass = LoadEntry.InitGameInstanceClass;
		if (InitClass != nullptr) {
			InitSubsystem->CreateInitObjectForMod(ModReference, InitClass);
		}
	}
	InitSubsystem->InitializeInitObjects();

	//Pre-Initialize old SMLInitMod content that should be registered prior to world loading
	for (const FModPakLoadEntry& LoadEntry : ModPakInitializers) {
		if (LoadEntry.LegacyInitModClass != NULL) {
			UObject* DefaultObject = LoadEntry.LegacyInitModClass->GetDefaultObject();
			ASMLInitMod* InitMod = Cast<ASMLInitMod>(DefaultObject);
			if (InitMod) {
				InitMod->RegisterEarlyLoadContent(LoadEntry.ModReference);
			}
		}
	}
}


void FModHandler::SpawnModActors(UWorld* World, bool bIsMenuWorld, TMap<FString, ABasicModInit*>& OutActorMap) {
	for (const FModPakLoadEntry& Initializer : ModPakInitializers) {
		UClass* SpawnActorClass = GetActiveInitializerClass(Initializer, bIsMenuWorld);
		if (SpawnActorClass == nullptr) {
			continue;
		}
		FActorSpawnParameters SpawnParams{};
		SpawnParams.Name = *FormatModActorName(Initializer.ModReference, bIsMenuWorld);
		ABasicModInit* SpawnedActor = Cast<ABasicModInit>(World->SpawnActor(SpawnActorClass, &FTransform::Identity, SpawnParams));
		checkf(SpawnedActor, TEXT("Couldn't spawn InitActor for mod %s"), *Initializer.ModReference);
		SpawnedActor->OwnerModReference = Initializer.ModReference;
		SpawnedActor->DispatchLifecyclePhase(ELifecyclePhase::CONSTRUCTION);
		OutActorMap.Add(Initializer.ModReference, SpawnedActor);
	}
}

void FModHandler::FindModActors(UWorld* World, TMap<FString, ABasicModInit*>& OutActorMap) {
	for(TActorIterator<ABasicModInit> Iterator(World); Iterator; ++Iterator) {
		ABasicModInit* BasicModInit = *Iterator;
		OutActorMap.Add(BasicModInit->GetOwnerModReference(), BasicModInit);
	}
}

void FModHandler::CheckDependencies() {
	TArray<FModLoadingEntry> allLoadingEntries;
	TMap<FString, uint64_t> modIndices;
	TMap<uint64_t, FString> modByIndex;
	SML::TopologicalSort::DirectedGraph<uint64_t> sortGraph;
	uint64_t currentIdx = 1;
	//construct initial mod list, assign indices, add mod nodes
	for (auto& pair : LoadingEntries) {
		allLoadingEntries.Add(pair.Value);
		uint64_t index = currentIdx++;
		modIndices.Add(pair.Key, index);
		modByIndex.Add(index, pair.Key);
		sortGraph.addNode(index);
	}

	TArray<FString> missingDependencies;
	//setup node dependencies
	for (const FModLoadingEntry& loadingEntry : allLoadingEntries) {
		const FModInfo& selfInfo = loadingEntry.ModInfo;
		IterateDependencies(LoadingEntries, modIndices, selfInfo, missingDependencies, sortGraph, selfInfo.Dependencies, false);
		IterateDependencies(LoadingEntries, modIndices, selfInfo, missingDependencies, sortGraph, selfInfo.OptionalDependencies, true);
	}
	//check for missing dependencies
	if (missingDependencies.Num() > 0) {
		LoadingProblems.Add(TEXT("\nFound missing dependencies:"));
		SML::Logging::error(TEXT("Found missing dependencies:"));
		for (auto& dependencyLine : missingDependencies) {
			SML::Logging::error(*dependencyLine);
			LoadingProblems.Add(dependencyLine);
		}
		FString out = "Cannot continue loading without dependencies \n";
		out = out.Append(FString::Join(LoadingProblems, TEXT("\n"))).Append("\n");
		SML::ShutdownEngine(*out);
		return;
	}
	//perform initial dependency sorting
	TArray<uint64_t> sortedIndices;
	try {
		sortedIndices = SML::TopologicalSort::topologicalSort(sortGraph);
	} catch (SML::TopologicalSort::cycle_detected<uint64_t>& ex) {
		FString message = FString::Printf(TEXT("Cycle dependency found in sorting graph at modid: %s"), *modByIndex[ex.cycleNode]);
		LoadingProblems.Add(message);
		SML::Logging::error(*message);
		return;
	}
	FinalizeSortingResults(modByIndex, LoadingEntries, sortedIndices);
	PopulateSortedModList(modByIndex, LoadingEntries, sortedIndices, SortedModLoadList);
	LoadingEntries.Empty();
	CheckStageErrors(TEXT("dependency resolution"));
};



void FModHandler::DiscoverMods() {
	LoadingEntries.Add(TEXT("SML"), CreateSmlLoadingEntry());
	const FString modsPath = SML::GetModDirectory();
	auto directoryVisitor = MakeDirectoryVisitor([this](const TCHAR* filepath, bool isDir) {
		if (!isDir) {
			if (FPaths::GetExtension(filepath) == TEXT("smod") ||
				FPaths::GetExtension(filepath) == TEXT("zip")) {
				ConstructZipMod(filepath);
			}
			else if (FPaths::GetExtension(filepath) == TEXT("dll")) {
				ConstructDllMod(filepath);
			} if (FPaths::GetExtension(filepath) == TEXT("pak")) {
				ConstructPakMod(filepath);
			}
		}
		return true;
	});
	FPlatformFileManager::Get().GetPlatformFile().IterateDirectory(*modsPath, directoryVisitor);
	CheckStageErrors(TEXT("mod discovery"));
};

void FModHandler::ConstructZipMod(const FString& FilePath) {
	SML::Logging::debug(TEXT("Constructing zip mod from "), *FilePath);

	const TSharedPtr<FZipFile> ModArchive = CreateZipArchiveReader(FilePath);
	if (!ModArchive.IsValid()) {
		ReportBrokenZipMod(FilePath, TEXT("corrupted zip file"));
		return;
	}
	const TSharedPtr<FJsonObject> DataJsonObj = ReadArchiveDataJson(*ModArchive);
	if (!DataJsonObj.IsValid()) {
		ReportBrokenZipMod(FilePath, TEXT("Invalid data.json: Malformed JSON file"));
		return;
	}
	FModInfo ResultModInfo;
	FString FailureReason;
	const bool bModInfoSucceed = FModInfo::CreateFromJson(*DataJsonObj.Get(), ResultModInfo, FailureReason);
	if (!bModInfoSucceed) {
		const FString ReasonText = FString::Printf(TEXT("Invalid data.json: %s"), *FailureReason);
		ReportBrokenZipMod(FilePath, ReasonText);
		return;
	}
	FModLoadingEntry& LoadingEntry = CreateLoadingEntry(ResultModInfo, FilePath);
	if (!LoadingEntry.bIsValid) return;
	if (!ExtractArchiveObjects(*ModArchive, *DataJsonObj, LoadingEntry)) {
		const FString Message = TEXT("Failed to extract data objects");
		ReportBrokenZipMod(FilePath, Message);
	}
}

void FModHandler::ConstructDllMod(const FString& filePath) {
	if (!CheckAndNotifyRawMod(filePath)) return;
	const auto ModId = GetModIdFromFile(filePath);
	auto& LoadingEntry = CreateRawModLoadingEntry(ModId, filePath);
	if (!LoadingEntry.bIsValid) return;
	LoadingEntry.DLLFilePath = filePath;
}

void FModHandler::ConstructPakMod(const FString& filePath) {
	if (!CheckAndNotifyRawMod(filePath)) return;
	const auto ModId = GetModIdFromFile(filePath);
	auto& LoadingEntry = CreateRawModLoadingEntry(ModId, filePath);
	if (!LoadingEntry.bIsValid) return;
	LoadingEntry.PakFiles.Add(FModPakFileEntry{ filePath, 0 });
}

const TArray<FString>& FModHandler::GetLoadedMods() const {
	return LoadedModReferences;
}

bool FModHandler::IsModLoaded(const FString& ModId) const {
	return LoadedMods.Find(ModId) != nullptr;
}

const FModContainer& FModHandler::GetLoadedMod(const FString& ModId) const {
	const auto LoadedModWrapped = LoadedMods.Find(ModId);
	if (LoadedModWrapped == nullptr) {
		SML::ShutdownEngine(FString::Printf(TEXT("Mod with provided ID is not loaded: %s"), *ModId));
	}
	return **LoadedModWrapped;
}

void FModHandler::CheckStageErrors(const TCHAR* stageName) {
	if (LoadingProblems.Num() > 0) {
		FString Message = FString::Printf(TEXT("Errors occurred during mod loading stage '%s'. Loading cannot continue:\n"), stageName);
		for (auto& Problem : LoadingProblems)
			Message.Append(Problem).Append(TEXT("\n"));
		SML::ShutdownEngine(*Message);
		LoadingProblems.Empty();
	}
}

void FModHandler::ReportBrokenZipMod(const FString& filePath, const FString& reason) {
	const FString Message = FString::Printf(TEXT("Failed to load zip mod from %s(%s)"), *filePath, *reason);
	LoadingProblems.Add(Message);
	SML::Logging::error(*Message);
}

bool FModHandler::CheckAndNotifyRawMod(const FString& filePath) {
	if (!SML::GetSmlConfig().bDevelopmentMode) {
		SML::Logging::error(TEXT("Found raw mod in mods directory: "), *filePath);
		SML::Logging::error(TEXT("Raw mods are not supported in production mode and can be used only for development"));
		this->LoadingProblems.Add(FString::Printf(TEXT("Found unsupported raw mod file: %s"), *filePath));
		return false;
	}
	SML::Logging::warning(TEXT("Loading development raw mod: "), *filePath);
	SML::Logging::warning(TEXT("Dependencies and versioning won't work!"));
	return true;
}

FModLoadingEntry& FModHandler::CreateLoadingEntry(const FModInfo& modInfo, const FString& filePath) {
	if (LoadingEntries.Find(modInfo.Modid) == nullptr)
		LoadingEntries.Add(modInfo.Modid);
	FModLoadingEntry& loadingEntry = LoadingEntries[modInfo.Modid];
	if (loadingEntry.bIsValid) {
		const FString Message = FString::Printf(TEXT("Found duplicate mods with same mod ID %s: %s and %s"), *modInfo.Modid, *filePath, *loadingEntry.VirtualModFilePath);
		LoadingProblems.Add(Message);
		SML::Logging::fatal(*Message);
		return INVALID_ENTRY;
	}
	loadingEntry.bIsValid = true;
	loadingEntry.ModInfo = modInfo;
	loadingEntry.VirtualModFilePath = filePath;
	return loadingEntry;
}


FModLoadingEntry& FModHandler::CreateRawModLoadingEntry(const FString& modId, const FString& filePath) {
	if (LoadingEntries.Find(modId) == nullptr)
		LoadingEntries.Add(modId);
	FModLoadingEntry& loadingEntry = LoadingEntries[modId];
	if (!loadingEntry.bIsValid) {
		loadingEntry.bIsValid = true;
		loadingEntry.ModInfo = FModInfo::CreateDummyInfo(modId);
		loadingEntry.ModInfo.Dependencies.Add(TEXT("@ORDER:LAST"), FVersionRange::CreateAnyVersionRange());
		loadingEntry.VirtualModFilePath = filePath;
		loadingEntry.bIsRawMod = true;
	}
	if (!loadingEntry.bIsRawMod) {
        const FString Message = FString::Printf(TEXT("Found raw mod file conflicting with packed mod: %s"), *filePath);
		SML::Logging::fatal(*Message);
		LoadingProblems.Add(Message);
		return INVALID_ENTRY;
	}
	return loadingEntry;
}