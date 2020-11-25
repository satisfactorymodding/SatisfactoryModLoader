#pragma once
#include "CoreMinimal.h"
#include "ModInfo.h"
#include "SubclassOf.h"

class ABasicModInit;
typedef class IModuleInterface* ( *FInitializeModuleFunctionPtr )( void );

DECLARE_LOG_CATEGORY_EXTERN(LogModLoading, Log, Log);

/** true when we are are calling StartupModule() on native mod libraries as the part of mod initialization routine */
extern SML_API bool GIsStartingUpModules;

/** Describes mod package loading entry with mod reference associated to initializer classes */
struct FModPakLoadEntry {
	FString ModReference;
	TSubclassOf<class UInitGameInstance> InitGameInstanceClass;
	TSubclassOf<class AInitGameWorld> InitGameWorldClass;
	TSubclassOf<class AInitMenuWorld> InitMenuWorldClass;
	UClass* LegacyInitModClass;
};

/** Describes information about mod package required for mod loading */
struct FModLoadingEntry {
	FModInfo ModInfo;
	FString VirtualModFilePath;
	FString DLLFilePath;
	TMap<FString, FString> CustomFilePaths;
	TArray<struct FModPakFileEntry> PakFiles;
	bool bIsRawMod;
};

/** Holds information about single mod pak file and it's loading priority */
struct FModPakFileEntry {
	FString PakFilePath;
	int32 LoadingPriority;
};

/**
 * Describes loaded and active mod package
 * Contains mod information parsed from data json, pointer to module interface
 * created automatically from contained DLL file (or default module pointer if mod doesn't contain C++ code)
 * CustomFilePaths can be used to retrieve file system paths for files in the mod package marked
 * with attribute "custom" in objects section of data json. Key is the archive file path, value is filesystem path
 * Note that icon will be contained here too, even though it's not a custom file object
 */
struct SML_API FModContainer {
	FModInfo ModInfo;
	class IModuleInterface* ModuleInterface;
	TMap<FString, FString> CustomFilePaths;
};

/**
 * Holds information about loaded mods and their references
 * Manages mod loading and initialization
 */
class SML_API FModHandler {
private:
    TArray<FModLoadingEntry> SortedModLoadList;
	TMap<FString, FModLoadingEntry> LoadingEntries;
	TArray<FModPakLoadEntry> ModPakInitializers;
	TArray<FString> LoadingProblems;
	TSharedPtr<struct BootstrapAccessors> BootstrapperAccessors;
	TMap<FString, IModuleInterface*> InitializedNativeModModules;
	TMap<FString, void*> LoadedNativeModLibraries;

	TMap<FString, TSharedPtr<FModContainer>> LoadedMods;
	TArray<TSharedPtr<FModContainer>> LoadedModsList;
	TArray<TWeakObjectPtr<AActor>> ModInitializerActorList;
public:
	/** Returns true if mod with provided mod reference is loaded, false otherwise */
	FORCEINLINE bool IsModLoaded(const FString& ModReference) const;

	/** Returns a module definition for the specified mod reference, or NULL if mod is not loaded */
	FORCEINLINE const FModContainer* GetLoadedMod(const FString& ModReference) const;

	/** Returns an array of all loaded mods */
	FORCEINLINE TArray<const FModContainer*> GetLoadedMods() const;
private:
	/** Private constructor to avoid external creation of mod handler */
	FModHandler() = default;

	/** Creates basic "raw mod" loading entry from raw .pak or .dll file, also checking that it doesn't conflict with normal mod packages */
    FModLoadingEntry* CreateRawModLoadingEntry(const FString& ModId, const FString& FilePath);
	/** Creates basic loading entry for normal mod package file, e.g .zip or .smod */
	FModLoadingEntry* CreateLoadingEntry(const FModInfo& ModInfo, const FString& FilePath);

	/** Checks whenever we can load raw mod (e.g we are in development mode), and warns the user about dependencies */
	bool CheckAndNotifyRawMod(const FString& FilePath);
	/** Checks for problems inside loading problems list, and crashes if we have some */
	void CheckStageErrors(const TCHAR* StageName);

	/** Constructs mod loading entry for provided normal zip mod package. Adds registered entry to load list */
	void ConstructZipMod(const FString& FilePath);
	/** Constructs mod loading entry for provided raw mod pak file. Joins it with DLL if they have same inferred mod reference */
	void ConstructPakMod(const FString& FilePath);
	/** Constructs mod loading entry for provided raw mod DLL file. Joins it with pak if they have same inferred mod reference */
	void ConstructDllMod(const FString& FilePath);

	/** Mounts mod content packages into the engine, and loads Initializer classes for each mod after that */
	void MountModPaks();
	/** Populates runtime mod list from loading entries sorted list, also combining it with loaded modules map passed */
	void PopulateModList();
	/** Initializes native modules prior to mounting any packages */
	void InitializeNativeModules();
	/** Performs loading of the native mod libraries into the process address space. Needs to happen earlier than actual mod loading due to UE reasons */
	void LoadNativeModLibraries();
	
	/** Iterates world actor list and finds initializer actor for each mod reference loaded */
    static void FindModActors(UWorld* World, TMap<FString, ABasicModInit*>& OutActorMap);
	/** Spawns initializer actors for every loaded mod reference, deciding actor type from bIsMenuWorld and passing loaded actor pointers to OutActorMap */
	void SpawnModActors(UWorld* World, bool bIsMenuWorld, TMap<FString, ABasicModInit*>& OutActorMap);
	
private:
	friend class FSatisfactoryModLoader;
	friend class FSatisfactoryModLoaderInternal;

	/** Setups mod handler with accessors needed for loading DLL mods */
	void SetupWithAccessors(const BootstrapAccessors& Accessors);

	/** Loads module into module manager and initializes it */
	static IModuleInterface* LoadModuleChecked(FName ModuleName, const FInitializeModuleFunctionPtr& ModuleInitializer);
	
    /** Scans file system for mod package files and populates loading entries map with basic information for mod loading */
    void DiscoverMods();
	/** Performs sorting of the loading entries and population of final list prior to mod loading */
	void PerformModListSorting();
	/** Performs mods pre-initialization, which in our context means loading mod DLLs into process address space */
	void PreInitializeMods();
	
	/** Subscribes to engine/world lifecycle events required for allocation and triggering of world-related Initializer mod actors */
	void SubscribeToLifecycleEvents();
	/** Actually performs loading of the mods. It initializes mod modules, populates mod list and then mounts mod packages */
	void InitializeMods();
	/** Initializes GameInstance mod Initializers at the start of the game, before any world has been loaded */
	void InitializeGameInstance();
	
private:
	FModHandler(FModHandler&) = delete; //delete copy constructor 
	FModHandler(FModHandler&&) = delete; //delete move constructor
	FNoncopyable& operator=(const FNoncopyable&) = delete; //delete copy assignment operator
};