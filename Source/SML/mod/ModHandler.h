#pragma once

#include <string>
#include "mod/ModInfo.h"
#include "CoreTypes.h"
#include "actor/SMLInitMod.h"
#include "actor/SMLInitMenu.h"

class AFGPlayerController;
class UClass;
class IModuleInterface;
class AFGGameMode;
struct BootstrapAccessors;


namespace SML {
	namespace Mod {
		struct FModPakFileEntry {
			FString pakFilePath;
			int32 loadingPriority;
		};
		
		struct FModLoadingEntry {
			bool isValid;
			FModInfo modInfo;
			FString virtualModFilePath;
			FString dllFilePath;
			TArray<FModPakFileEntry> pakFiles;
			bool isRawMod = false;
		};

		struct FModContainer {
			const FModInfo modInfo;
			IModuleInterface* moduleInterface;
		};

		struct FModPakLoadEntry {
			FString modid;
			TSubclassOf<ASMLInitMod> modInitClass;
			TSubclassOf<ASMLInitMenu> menuInitClass;
		};
		
		/**
		* Holds important information about the loaded mods.
		* It should never be accessed by mods directly.
		*/ 
		SML_API class FModHandler {
		private:
			TArray<FModLoadingEntry> sortedModLoadList;
			TMap<FString, FModLoadingEntry> loadingEntries;
			TArray<FModPakLoadEntry> modPakInitializers;
			TArray<FString> loadingProblems;

			TMap<FString, FModContainer*> loadedMods;
			TArray<FModContainer*> loadedModsList;
			TArray<FString> loadedModsModIDs;
			TArray<AActor*> modInitializerActorList;
		public:
			//we shouldn't be able to copy FModHandler, or move it
			FModHandler(FModHandler&) = delete; //delete copy constructor
			FModHandler(FModHandler&&) = delete; //delete move constructor
			FModHandler();
			
			bool isModLoaded(const FString& modId) const;

			/**
			* Returns a module definition for the specified modid
			* Shuts down if mod with specified ID is not loaded
			*/
			const FModContainer& getLoadedMod(const FString& modId) const;

			/**
			* Returns a map of all loaded mod ids
			*/
			const TArray<FString>& getLoadedMods() const;
		private:
			FModLoadingEntry& createRawModLoadingEntry(const FString& modId, const FString& filePath);
			FModLoadingEntry& createLoadingEntry(const FModInfo& modInfo, const FString& filePath);
			
			bool checkAndNotifyRawMod(const FString& filePath);
			void reportBrokenZipMod(const FString& filePath, const FString& reason);
			void checkStageErrors(const  TCHAR* stageName);
			
			void constructZipMod(const FString& filePath);
			void constructPakMod(const FString& filePath);
			void constructDllMod(const FString& filePath);

			void MountModPaks();
			void LoadModLibraries(const BootstrapAccessors& accessors, TMap<FString, IModuleInterface*>& loadedModules);
			void PopulateModList(const TMap<FString, IModuleInterface*>& loadedModules);

			void initializeModActors();
			void postInitializeModActors();
			void handlePlayerJoin(AFGPlayerController* PlayerController);
		public:
			/**
			* Load all mods from the given FString.
			*/
			void discoverMods();

			/**
			* Ensure that all dependencies of mods exist.
			*/
			void checkDependencies();

			/**
			* Loads the mods into the game
			*/
			void loadMods(const BootstrapAccessors& accessors);

			/**
			* Loads the dll mods into memory
			*/
			void loadDllMods(const BootstrapAccessors& accessors);

			static void attachLoadingHooks();

			void onMapLoadComplete(UWorld* world, bool isMenuWorld);
		};
	};
};