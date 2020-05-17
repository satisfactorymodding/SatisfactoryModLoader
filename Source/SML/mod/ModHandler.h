#pragma once

#include "mod/ModInfo.h"
#include "CoreTypes.h"
#include "actor/SMLInitMod.h"
#include "actor/SMLInitMenu.h"

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
	FString Modid;
	TSubclassOf<ASMLInitMod> ModInitClass;
	TSubclassOf<ASMLInitMenu> MenuInitClass;
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
	TArray<FString> LoadedModsModIDs;
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

	void SpawnModActors(UWorld* World, bool bIsMenuWorld);
	void PreInitializeModActors();
	void InitializeModActors();
	void PostInitializeModActors();
	void HandlePlayerJoin(AFGPlayerController* PlayerController);
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

	static void AttachLoadingHooks();
};;