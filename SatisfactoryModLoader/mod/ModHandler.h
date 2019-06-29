#pragma once
#include "Mod.h"
#include <../SatisfactorySDK/SDK.hpp>
#include "Registry.h"
#include <string>
#include <vector>
#include <map>
#include <memory>

namespace SML {
	namespace Mod {
		enum GameStage {
			//Before any mods are loaded
			PRE_CONSTRUCT,
			//When the mods are loaded from the file
			CONSTRUCT,
			//When the mods' setup functions are being called
			SETUP,
			//When the mods' post setup functions are being called
			POST_SETUP,
			//When SML has finished but assets haven't been loaded yet
			INITIALIZING,
			//When SML has finished loading and assets have started loading
			RUN
		};

		/**
		* Holds important information about the loaded mods.
		* It should never be accessed by mods directly.
		*/
		class ModHandler {
		public:
			std::vector<std::unique_ptr<Mod>> mods;

			std::vector<Registry> commandRegistry;
			std::vector<Registry> APIRegistry;

			std::map<std::string, std::vector<PVOID>> eventRegistry;

			std::map<const wchar_t*, SDK::UObject*> assetCache;

			std::map<int, const wchar_t*> assetIdRegistry;

			GameStage currentStage = GameStage::PRE_CONSTRUCT;

			/**
			* Load all mods from the given path.
			*/
			void loadMods(const char* startingPath);

			/**
			* Call the setup function of every loaded mod.
			*/
			void setupMods();

			/**
			* Ensure that all dependencies of mods exist.
			*/
			void checkDependencies();

			/**
			* Call the post setup function of every mod through recursive calling, ensuring 
			* the post setups of mod dependencies loaded before the original mod's post setup.
			*/
			void postSetupMods();
		private:
			std::vector<std::string> modNameDump;

			/**
			* Recustively load mod dependencies
			*/
			void recursiveDependencyLoad(Mod& mod, int i);

			/**
			* Create mod instance and check for validity.
			*
			* Returns true if mod is valid.
			*/
			bool createMod(Mod* (*modCreate)());

			/**
			* Load mod DLL from given path
			*/
			void loadDLL(LPCWSTR sw);

			/**
			* Load mod DLL from memory
			*/
			void loadMemoryDLL(void *data, size_t size);

			/**
			* Get the mod files and load them
			*/
			void getFiles(std::string path);

			/**
			* Find all valid mods
			*/
			void findMods(std::string path);
		};
	}
}