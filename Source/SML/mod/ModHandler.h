#pragma once

#include "mod/ModInfo.h"
#include "CoreTypes.h"

class ABasicModInit;
class AInitGameWorld;
class AInitMenuWorld;
class UInitGameInstance;
class AFGPlayerController;
class UClass;
class IModuleInterface;
class AFGGameMode;
struct BootstrapAccessors;

struct FModPakFileEntry {
	FString PakFilePath;
	int32 LoadingPriority;
};

struct FModLoadingEntry {
	bool bIsValid;
	FModInfo ModInfo;
	FString VirtualModFilePath;
	FString DLLFilePath;
	TMap<FString, FString> CustomFilePaths;
	TArray<FModPakFileEntry> PakFiles;
	bool bIsRawMod = false;
};

struct FModContainer {
	const FModInfo ModInfo;
	IModuleInterface* ModuleInterface;
	TMap<FString, FString> CustomFilePaths;
};

struct FModPakLoadEntry {
	FString ModReference;
	TSubclassOf<UInitGameInstance> InitGameInstanceClass;
	TSubclassOf<AInitGameWorld> InitGameWorldClass;
	TSubclassOf<AInitMenuWorld> InitMenuWorldClass;
	UClass* LegacyInitModClass;
};

enum class ELifecyclePhase : uint8 {
	/** Dispatched right after mod actor is spawned */
	CONSTRUCTION,
	/** Dispatched when all mod actors are spawned in dependency order */
    INITIALIZATION,
	/** Dispatched when world is initialized in dependency order */
    POST_INITIALIZATION
};

/**
 * Holds information about loaded mods and their references
 * Manages mod loading and initialization
 */
SML_API class FModHandler {
private:
    TArray<FModLoadingEntry> SortedModLoadList;
	TMap<FString, FModLoadingEntry> LoadingEntries;
	TArray<FModPakLoadEntry> ModPakInitializers;
	TArray<FString> LoadingProblems;

	TMap<FString, FModContainer*> LoadedMods;
	TArray<FModContainer*> LoadedModsList;
	TArray<FString> LoadedModReferences;
	TArray<TWeakObjectPtr<AActor>> ModInitializerActorList;
public:
    //we shouldn't be able to copy FModHandler, or move it
    FModHandler(FModHandler&) = delete; //delete copy constructor
	FModHandler(FModHandler&&) = delete; //delete move constructor
	FModHandler();
			
	bool IsModLoaded(const FString& ModId) const;

	/**
	* Returns a module definition for the specified modid
	* Shuts down if mod with specified ID is not loaded
	*/
	const FModContainer& GetLoadedMod(const FString& ModId) const;

	/**
	* Returns a map of all loaded mod ids
	*/
	const TArray<FString>& GetLoadedMods() const;
private:
    FModLoadingEntry& CreateRawModLoadingEntry(const FString& ModId, const FString& FilePath);
	FModLoadingEntry& CreateLoadingEntry(const FModInfo& ModInfo, const FString& FilePath);
			
	bool CheckAndNotifyRawMod(const FString& FilePath);
	void ReportBrokenZipMod(const FString& FilePath, const FString& Reason);
	void CheckStageErrors(const  TCHAR* StageName);
			
	void ConstructZipMod(const FString& FilePath);
	void ConstructPakMod(const FString& FilePath);
	void ConstructDllMod(const FString& FilePath);

	void MountModPaks();
	void LoadModLibraries(const BootstrapAccessors& Accessors, TMap<FString, IModuleInterface*>& LoadedModules);
	void PopulateModList(const TMap<FString, IModuleInterface*>& LoadedModules);
    static void FindModActors(UWorld* World, TMap<FString, ABasicModInit*>& OutActorMap);
	void SpawnModActors(UWorld* World, bool bIsMenuWorld, TMap<FString, ABasicModInit*>& OutActorMap);
public:
    /**
	* Load all mods from the given FString.
	*/
    void DiscoverMods();

	/**
	* Ensure that all dependencies of mods exist.
	*/
	void CheckDependencies();

	/**
	* Loads the mods into the game
	*/
	void LoadMods(const BootstrapAccessors& Accessors);

	/**
	* Loads the dll mods into memory
	*/
	void LoadDllMods(const BootstrapAccessors& Accessors);

	/**
	 * Subscribes to engine/world lifetime events
	 */
	void SubscribeToLifecycleEvents();

	/**
	 * Performs InitGameInstance objects loading and initialization
	 * Call only after mods have been loaded
	 */
	void InitializeGameInstance();
};;