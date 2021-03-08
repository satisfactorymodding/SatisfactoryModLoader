#include "ModLoading/ModHandler.h"
#include "Engine/World.h"
#include "HAL/PlatformFilemanager.h"
#include "IPlatformFilePak.h"
#include "FGGameMode.h"
#include "Misc/CoreDelegates.h"
#include "FactoryGameModule.h"
#include "ModLoading/ModHandlerInternal.h"
#include "FGGameState.h"
#include "Module/GameInstanceModuleManager.h"
#include "Registry/ModContentRegistry.h"
#include "SatisfactoryModLoader.h"
#include "SMLModule.h"
#include "Util/TopologicalSort/TopologicalSort.h"
#include "Module/WorldModuleManager.h"
#include "Util/ZipFile/ZipFile.h"

DEFINE_LOG_CATEGORY(LogModLoading);

//No need to handle ELogVerbosity::Fatal here because it's an instant crash
#define MOD_LOADING_LOG(Verbosity, Message, ...) \
	UE_LOG(LogModLoading, Verbosity, Message, ##__VA_ARGS__); \
	if (ELogVerbosity::Verbosity == ELogVerbosity::Error) {\
		LoadingProblems.Add(FString::Printf(Message, ##__VA_ARGS__)); \
	}

bool FModHandler::IsModLoaded(const FString& ModReference) const {
	return LoadedMods.Contains(ModReference);
}

const FModContainer* FModHandler::GetLoadedMod(const FString& ModReference) const {
	TSharedPtr<FModContainer> const* ModContainer = LoadedMods.Find(ModReference);
	if (ModContainer != NULL) {
		return ModContainer->Get();
	}
	return NULL;
}

TArray<const FModContainer*> FModHandler::GetLoadedMods() const {
	TArray<const FModContainer*> OutLoadedMods;
	for (const TSharedPtr<FModContainer>& ModContainer : LoadedModsList) {
		OutLoadedMods.Add(ModContainer.Get());
	}
	return OutLoadedMods;
}

FString ConvertFailureReasonToString(EModuleLoadResult FailureReason) {
	if (FailureReason == EModuleLoadResult::FileNotFound) {
		return TEXT("Module file cannot be found");
	}
	
	if (FailureReason == EModuleLoadResult::FileIncompatible) {
		return TEXT("Module is not compatible with the current version by the engine");
	}
	
	if (FailureReason == EModuleLoadResult::CouldNotBeLoadedByOS) {
		return TEXT("Module could not be loaded by the underlying operational system");
	}
	
	if (FailureReason == EModuleLoadResult::FailedToInitialize) {
		return TEXT("Module failed to initialize properly after being loaded");
	}
	
	ensure(0);	// If this goes off, the error handling code should be updated for the new enum values!
	return TEXT("Unknown module loading failure");
}

void FModHandler::InitializeNativeModules() {
	//SML Module should be already loaded to the process at this point, because it is the one triggering mod loading
	const FString SMLModuleName = TEXT("SML");
	FSMLModule& SMLModule = FModuleManager::Get().GetModuleChecked<FSMLModule>(*SMLModuleName);
	InitializedNativeModModules.Add(SMLModuleName, &SMLModule);

	//FactoryGame module should be initialized already at this point, so we just query loaded module interface
	const FString FactoryGameModuleName = TEXT("FactoryGame");
	FFactoryGameModule& FactoryGameModule = FModuleManager::Get().GetModuleChecked<FFactoryGameModule>(*FactoryGameModuleName);
	InitializedNativeModModules.Add(FactoryGameModuleName, &FactoryGameModule);

	FModuleManager& ModuleManager = FModuleManager::Get();
	
	for (const FModLoadingEntry& LoadingEntry : SortedModLoadList) {
		const FString& ModReference = LoadingEntry.ModInfo.ModReference;
		if (!LoadingEntry.DLLFilePath.IsEmpty()) {

			//We cannot use #if IS_MONOLITHIC here because we are never building monolithic -
			//Mod modules and SML are always build for modular build, just linked differently according to game distribution
			ModuleManager.AddBinariesDirectory(*FPaths::GetPath(LoadingEntry.DLLFilePath), false);
			EModuleLoadResult LoadResult;
			IModuleInterface* ModuleInterface = ModuleManager.LoadModuleWithFailureReason(*ModReference, LoadResult);
			if (ModuleInterface == NULL) {
				const FString FailureReason = ConvertFailureReasonToString(LoadResult);
				MOD_LOADING_LOG(Error, TEXT("Failed to load module for mod %s: %s"), *ModReference, *FailureReason);
				continue;
			}
			InitializedNativeModModules.Add(ModReference, ModuleInterface);
		}
	}
}

void FModHandler::PopulateModList() {
	for (const FModLoadingEntry& LoadingEntry : SortedModLoadList) {
		IModuleInterface* const* ModuleInterface = InitializedNativeModModules.Find(LoadingEntry.ModInfo.ModReference);
		TSharedPtr<FModContainer> ModContainer = MakeShareable(new FModContainer);
		ModContainer->ModInfo = LoadingEntry.ModInfo;
		ModContainer->ModuleInterface = ModuleInterface ? *ModuleInterface : NULL;
		ModContainer->CustomFilePaths.Append(LoadingEntry.CustomFilePaths);
		
		LoadedModsList.Add(ModContainer);
		LoadedMods.Add(ModContainer->ModInfo.ModReference, ModContainer);
	}
}

void FModHandler::MountModPaks() {
	FPakPlatformFile* PakPlatformFile = static_cast<FPakPlatformFile*>(FPlatformFileManager::Get().FindPlatformFile(TEXT("PakFile")));
	TArray<FString> MountedPakNames;
	PakPlatformFile->GetMountedPakFilenames(MountedPakNames);
	const FString PlatformPakFileName = GetData(MountedPakNames[0]);
	const FString GamePakSignaturePath = FPaths::ChangeExtension(PlatformPakFileName, TEXT("sig"));

	//Mount all paks in the order specified by dependencies, but don't actually load anything from them
	for (const FModLoadingEntry& LoadingEntry : SortedModLoadList) {
		for (const FModPakFileEntry& PakFileDef : LoadingEntry.PakFiles) {
			const FString& PakFilePathStr = PakFileDef.PakFilePath;
			const FString ModPakSignaturePath = FPaths::ChangeExtension(PakFilePathStr, TEXT("sig"));
			//make sure we have signature file in place before mounting pak
			if (!FPaths::FileExists(ModPakSignaturePath)) {
				FPlatformFileManager::Get().GetPlatformFile().CopyFile(*ModPakSignaturePath, *GamePakSignaturePath);
			}
			UE_LOG(LogModLoading, Display, TEXT("Mounting mod package %s with priority %d"), *PakFilePathStr, PakFileDef.LoadingPriority);
			FCoreDelegates::OnMountPak.Execute(PakFilePathStr, PakFileDef.LoadingPriority, nullptr);
		}
	}

	//Initialize overwrite lists for mods prior to loading anything
	for (const FModLoadingEntry& LoadingEntry : SortedModLoadList) {
		AModContentRegistry::DiscoverOverwriteListForModReference(LoadingEntry.ModInfo.ModReference);
	}

	//Initialize UClasses for InitMod and InitMenu for each mod, preload their contents on the start and pin them in GC Root
	for (const FModLoadingEntry& LoadingEntry : SortedModLoadList) {
		if (LoadingEntry.PakFiles.Num() > 0) {
			const FModPakLoadEntry PakEntry = FModHandlerHelper::DiscoverModInitializers(LoadingEntry.ModInfo.ModReference);
			ModPakInitializers.Add(PakEntry);
		}
	}
}

void FModHandler::SubscribeToWorldEvents() {
	//Spawn mod actors as soon as world actors are initialized (e.g static map objects are spawned)
	FWorldDelegates::OnWorldInitializedActors.AddLambda([this](const UWorld::FActorsInitializedParams Params) {
		if (ShouldInitializeModulesOnWorld(Params.World)) {
			OnWorldActorsInitialization(Params.World);
		}
	});
	//Post initialize mod actors when world is fully loaded and is ready to be used
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddLambda([this](UWorld* World){
		if (ShouldInitializeModulesOnWorld(World)) {
			OnWorldLoadComplete(World);
		}
	});
}

void FModHandler::OnWorldActorsInitialization(UWorld* World) {
	AWorldModuleManager* ModuleManager = AWorldModuleManager::Get(World);
	check(ModuleManager);

	AFGGameMode* GameMode = Cast<AFGGameMode>(World->GetAuthGameMode());
	const bool bIsMenuGameMode = GameMode && GameMode->IsMainMenuGameMode();

	//Create modules for each world module registered
	for (const FModPakLoadEntry& LoadEntry : ModPakInitializers) {
		const FString& ModReference = LoadEntry.ModReference;
		UClass* WorldModuleClass = bIsMenuGameMode ? LoadEntry.InitMenuWorldClass : LoadEntry.InitGameWorldClass;
		if (WorldModuleClass != NULL && WorldModuleClass->IsChildOf<UWorldModule>()) {
			ModuleManager->CreateRootModule(*ModReference, WorldModuleClass);
		}
	}

	//Process construction and initialization
	ModuleManager->DispatchLifecycleEvent(ELifecyclePhase::CONSTRUCTION);
	ModuleManager->DispatchLifecycleEvent(ELifecyclePhase::INITIALIZATION);
}

void FModHandler::OnWorldLoadComplete(UWorld* World) {
	AWorldModuleManager* ModuleManager = AWorldModuleManager::Get(World);
	check(ModuleManager);

	//Just dispatch post initialization on module manager now
	ModuleManager->DispatchLifecycleEvent(ELifecyclePhase::POST_INITIALIZATION);
}

void FModHandler::InitializeGameInstanceModules(UGameInstance* GameInstance) {
	UGameInstanceModuleManager* ModuleManager = GameInstance->GetSubsystem<UGameInstanceModuleManager>();
	check(ModuleManager);

	//Create modules for each game instance module registered
	for (const FModPakLoadEntry& LoadEntry : ModPakInitializers) {
		const FString& ModReference = LoadEntry.ModReference;
		UClass* GameInstanceModuleClass = LoadEntry.InitGameInstanceClass;
		if (GameInstanceModuleClass != NULL && GameInstanceModuleClass->IsChildOf<UGameInstanceModule>()) {
			ModuleManager->CreateRootModule(*ModReference, GameInstanceModuleClass);
		}
	}

	//Run construction and initialization, post init will be run after configuration reload
	ModuleManager->DispatchLifecycleEvent(ELifecyclePhase::CONSTRUCTION);
	ModuleManager->DispatchLifecycleEvent(ELifecyclePhase::INITIALIZATION);
}

void FModHandler::PostInitializeGameInstanceModules(UGameInstance* GameInstance) {
	UGameInstanceModuleManager* ModuleManager = GameInstance->GetSubsystem<UGameInstanceModuleManager>();
	check(ModuleManager);
	ModuleManager->DispatchLifecycleEvent(ELifecyclePhase::POST_INITIALIZATION);
}

void FModHandler::DiscoverMods() {
	//Automatically add SML to loading entries list now
	LoadingEntries.Add(TEXT("SML"), FModHandlerHelper::CreateSMLLoadingEntry());
	LoadingEntries.Add(TEXT("FactoryGame"), FModHandlerHelper::CreateFactoryGameLoadingEntry());

	//Iterate mods directory and scan every file there
	const FString ModDirectory = FModHandlerHelper::GetModsDirectory();
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	//Make sure mod directory exists now
	PlatformFile.CreateDirectoryTree(*ModDirectory);
	
	PlatformFile.IterateDirectory(*ModDirectory, [&](const TCHAR* FilePath, bool bIsDirectory){
        if (!bIsDirectory) {
            const FString FileExtension = FPaths::GetExtension(FilePath);
            if (FileExtension == TEXT("smod") || FileExtension == TEXT("zip")) {
                ConstructZipMod(FilePath);
            } else if (FileExtension == TEXT("dll")) {
                ConstructDllMod(FilePath);
            } if (FileExtension == TEXT("pak")) {
                ConstructPakMod(FilePath);
            }
        }
        return true;
    });
	CheckStageErrors(TEXT("mod discovery"));
};

void FModHandler::PerformModListSorting() {
	FModSortingSet ModSortingSet{};
	FModHandlerHelper::PopulateModSortingSet(ModSortingSet, LoadingEntries);
	
	//Check for missing dependencies
	if (ModSortingSet.MissingDependencies.Num()) {
		const FString DependenciesString = FString::Join(ModSortingSet.MissingDependencies, TEXT("\n"));
		MOD_LOADING_LOG(Error, TEXT("Found missing mod dependencies: %s"), *DependenciesString);
		return;
	}

	TSet<uint64> OutCycleNodes;
	const bool bSortingSuccess = FTopologicalSort::TopologicalSort(ModSortingSet.SortGraph, ModSortingSet.SortedIndices, &OutCycleNodes);
	if (!bSortingSuccess) {
		const FString CycleListString = FString::JoinBy(OutCycleNodes, TEXT(", "), [&](uint64 ModId){
			return ModSortingSet.ModByIndex.FindChecked(ModId);
		});
		MOD_LOADING_LOG(Error, TEXT("Found cyclic dependencies during mod loading: %s"), *CycleListString);
		return;
	}

	FModHandlerHelper::FinalizeSortingResults(ModSortingSet, LoadingEntries);

	SortedModLoadList.Empty();
	for (uint64 ModIndex : ModSortingSet.SortedIndices) {
		const FString& ModReference = ModSortingSet.ModByIndex.FindChecked(ModIndex);
		SortedModLoadList.Add(LoadingEntries.FindChecked(ModReference));
	}
	LoadingEntries.Empty();
	
	CheckStageErrors(TEXT("dependency resolution"));
}

bool FModHandler::ShouldInitializeModulesOnWorld(UWorld* World) {
	return World->WorldType == EWorldType::Game || World->WorldType == EWorldType::PIE;
};

void FModHandler::InitializeMods() {
	UE_LOG(LogModLoading, Display, TEXT("Starting up native mod modules..."));
	InitializeNativeModules();
	UE_LOG(LogModLoading, Display, TEXT("Populating mod list"));
	PopulateModList();
	UE_LOG(LogModLoading, Display, TEXT("Mounting mod packages"));
	MountModPaks();
	CheckStageErrors(TEXT("initialization"));
}


void FModHandler::ConstructZipMod(const FString& FilePath) {
	UE_LOG(LogModLoading, Display, TEXT("Constructing mod file %s"), *FilePath);

	//First, create zip archive reader to unpack mod files
	FString OutArchiveOpenErrorMessage;
	const TSharedPtr<FZipFile> ModArchive = FZipFile::CreateZipArchiveReader(FilePath, OutArchiveOpenErrorMessage);
	if (!ModArchive.IsValid()) {
		MOD_LOADING_LOG(Error, TEXT("Failed to load zip mod file %s: %s"), *FilePath, *OutArchiveOpenErrorMessage);
		return;
	}
	//Then parse data.json into ModInfo and retrieve ModReference
	TArray<TSharedPtr<FJsonValue>> OutArchiveObjects;
	FModInfo ParsedModInfo;
	FString ModInfoReadErrorMessage;
	const bool bModInfo = FModHandlerHelper::ReadArchiveDataJson(ModArchive, OutArchiveObjects, ParsedModInfo, ModInfoReadErrorMessage);
	if (!bModInfo) {
		MOD_LOADING_LOG(Error, TEXT("Failed to read data.json from zip mod file %s: %s"), *FilePath, *ModInfoReadErrorMessage);
		return;
	}
	//Create loading entry and extract objects
	FModLoadingEntry* ModLoadingEntry = CreateLoadingEntry(ParsedModInfo, FilePath);
	if (ModLoadingEntry != NULL) {
		FString OutExtractObjectsErrorMessage;
		if (!FModHandlerHelper::ExtractArchiveObjects(ModArchive, OutArchiveObjects, *ModLoadingEntry, OutExtractObjectsErrorMessage)) {
			MOD_LOADING_LOG(Error, TEXT("Failed to extract mod zip file %s: %s"), *FilePath, *OutExtractObjectsErrorMessage);
		};
	}
}

void FModHandler::ConstructDllMod(const FString& FilePath) {
	UE_LOG(LogModLoading, Display, TEXT("Constructing raw DLL mod file %s"), *FilePath);
	
	if (CheckAndNotifyRawMod(FilePath)) {
		const FString ModReference = FModHandlerHelper::GetModReferenceFromFile(FilePath);
		FModLoadingEntry* LoadingEntry = CreateRawModLoadingEntry(ModReference, FilePath);
		if (LoadingEntry != NULL) {
			LoadingEntry->DLLFilePath = FilePath;
		}
	}
}

void FModHandler::ConstructPakMod(const FString& FilePath) {
	UE_LOG(LogModLoading, Display, TEXT("Constructing raw pak mod file %s"), *FilePath);
	
	if (CheckAndNotifyRawMod(FilePath)) {
		const FString ModReference = FModHandlerHelper::GetModReferenceFromFile(FilePath);
		FModLoadingEntry* LoadingEntry = CreateRawModLoadingEntry(ModReference, FilePath);
		if (LoadingEntry != NULL) {
			//Replicate UE4 default behavior, which gives loading priority to pak files with _p suffix
			const FString BaseFilename = FPaths::GetBaseFilename(FilePath);
			const bool bHasPriority = BaseFilename.EndsWith(TEXT("_p"));
			const int32 LoadingPriority = bHasPriority ? 100 : 0;
			LoadingEntry->PakFiles.Add(FModPakFileEntry{FilePath, LoadingPriority});
		}
	}
}

void FModHandler::CheckStageErrors(const TCHAR* stageName) {
	if (LoadingProblems.Num() > 0) {
		FString Message = FString::Printf(TEXT("Errors occurred during mod loading stage '%s'. Loading cannot continue:\n"), stageName);
		for (auto& Problem : LoadingProblems)
			Message.Append(Problem).Append(TEXT("\n"));
		UE_LOG(LogModLoading, Fatal, TEXT("%s"), *Message);
	}
}

bool FModHandler::CheckAndNotifyRawMod(const FString& FilePath) {
	if (!FSatisfactoryModLoader::GetSMLConfiguration().bDevelopmentMode) {
		MOD_LOADING_LOG(Error, TEXT("Found raw mod in mods directory: %s, Raw mods cannot be used without development mode enabled."), *FilePath);
		return false;
	}
	UE_LOG(LogModLoading, Warning, TEXT("Loading raw mod %s. Dependencies and versioning won't work!"), *FilePath);
	return true;
}

FModLoadingEntry* FModHandler::CreateLoadingEntry(const FModInfo& ModInfo, const FString& FilePath) {
	FModLoadingEntry* ModLoadingEntry = LoadingEntries.Find(ModInfo.ModReference);
	if (ModLoadingEntry == NULL) {
		ModLoadingEntry = &LoadingEntries.Add(ModInfo.ModReference);
		ModLoadingEntry->ModInfo = ModInfo;
		ModLoadingEntry->VirtualModFilePath = FilePath;
		ModLoadingEntry->bIsRawMod = false;
	}
	if (ModLoadingEntry->bIsRawMod) {
		UE_LOG(LogModLoading, Error, TEXT("Packed mod file %s conflicts with raw mod %s (identical Mod Reference: %s)"),
            *FilePath, *ModLoadingEntry->VirtualModFilePath, *ModInfo.ModReference);
		return NULL;
	}
	return ModLoadingEntry;
}

FModLoadingEntry* FModHandler::CreateRawModLoadingEntry(const FString& ModReference, const FString& FilePath) {
	FModLoadingEntry* ModLoadingEntry = LoadingEntries.Find(ModReference);
	if (ModLoadingEntry == NULL) {
		ModLoadingEntry = &LoadingEntries.Add(ModReference);
		ModLoadingEntry->ModInfo = FModInfo::CreateDummyInfo(ModReference);
		ModLoadingEntry->ModInfo.Dependencies.Add(TEXT("@ORDER:LAST"), FVersionRange::CreateAnyVersionRange());
		ModLoadingEntry->VirtualModFilePath = FilePath;
		ModLoadingEntry->bIsRawMod = true;
	}
	if (!ModLoadingEntry->bIsRawMod) {
		MOD_LOADING_LOG(Error, TEXT("Raw mod at %s conflicts with packed mod %s (identical Mod Reference: %s)"),
			*FilePath, *ModLoadingEntry->VirtualModFilePath, *ModReference);
		return NULL;
	}
	return ModLoadingEntry;
}
