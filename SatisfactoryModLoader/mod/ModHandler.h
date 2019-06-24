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

		// holds important information about the loaded mods. It should never be accessed by mods directly.
		class ModHandler {
		public:
			std::vector<std::unique_ptr<Mod>> mods;

			std::vector<Registry> commandRegistry;
			std::vector<Registry> APIRegistry;

			std::map<std::string, std::vector<PVOID>> eventRegistry;

			std::map<const wchar_t*, SDK::UObject*> assetCache;

			std::map<int, const wchar_t*> assetIdRegistry;

			GameStage currentStage = GameStage::PRE_CONSTRUCT;

			void loadMods(const char* startingPath);
			void setupMods();
			void checkDependencies();
			void postSetupMods();
		private:
			std::vector<std::string> modNameDump;
			void recursiveDependencyLoad(Mod& mod, int i);
			void getFiles(std::string path);
			void findMods(std::string path);
		};
	}
}