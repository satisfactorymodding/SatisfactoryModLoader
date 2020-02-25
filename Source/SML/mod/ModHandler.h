#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <unordered_map>
#include "mod/ModInfo.h"
#include "CoreTypes.h"
#include "actor/SMLInitMod.h"
#include "actor/SMLInitMenu.h"

class UClass;
class IModuleInterface;
class AFGGameMode;
struct BootstrapAccessors;

using namespace std::experimental::filesystem;

std::string createModuleNameFromModId(const std::wstring& modId);

namespace SML {
	namespace Mod {
		struct FModPakFileEntry {
			std::wstring pakFilePath;
			int32 loadingPriority;
		};
		
		struct FModLoadingEntry {
			bool isValid;
			FModInfo modInfo;
			std::wstring virtualModFilePath;
			std::wstring dllFilePath;
			std::vector<FModPakFileEntry> pakFiles;
			bool isRawMod = false;
		};

		struct FModContainer {
			const FModInfo modInfo;
			IModuleInterface* moduleInterface;
		};

		struct FModPakLoadEntry {
			std::wstring modid;
			TSubclassOf<ASMLInitMod> modInitClass;
			TSubclassOf<ASMLInitMenu> menuInitClass;
		};
		
		/**
		* Holds important information about the loaded mods.
		* It should never be accessed by mods directly.
		*/ 
		SML_API class FModHandler {
		private:
			std::vector<FModLoadingEntry> sortedModLoadList;
			std::unordered_map<std::wstring, FModLoadingEntry> loadingEntries;
			std::vector<FModPakLoadEntry> modPakInitializers;
			std::vector<std::wstring> loadingProblems;

			std::unordered_map<std::wstring, FModContainer*> loadedMods;
			std::vector<FModContainer*> loadedModsList;
			std::vector<std::wstring> loadedModsModIDs;
			std::vector<AActor*> modInitializerActorList;
		public:
			FModHandler();
			
			bool isModLoaded(const std::wstring& modId) const;

			/**
			* Returns a module definition for the specified modid
			* Shuts down if mod with specified ID is not loaded
			*/
			const FModContainer& getLoadedMod(const std::wstring& modId) const;

			/**
			* Returns a map of all loaded mod ids
			*/
			const std::vector<std::wstring>& getLoadedMods() const;
		private:
			FModLoadingEntry& createRawModLoadingEntry(const std::wstring& modId, const path& filePath);
			FModLoadingEntry& createLoadingEntry(const FModInfo& modInfo, const path& filePath);
			
			bool checkAndNotifyRawMod(const path& filePath);
			void reportBrokenZipMod(const path& filePath, const std::wstring& reason);
			void checkStageErrors(const  TCHAR* stageName);
			
			void constructZipMod(const path& filePath);
			void constructPakMod(const path& filePath);
			void constructDllMod(const path& filePath);

			void MountModPaks();
			void LoadModLibraries(const BootstrapAccessors& accessors, std::map<std::wstring, IModuleInterface*>& loadedModules);
			void PopulateModList(const std::map<std::wstring, IModuleInterface*>& loadedModules);

			void initializeMenuActors();
			void initializeModActors();
			void postInitializeModActors();
		public:
			/**
			* Load all mods from the given path.
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

			void onGameModePostLoad(AFGGameMode* gameMode);
		};
	};
};