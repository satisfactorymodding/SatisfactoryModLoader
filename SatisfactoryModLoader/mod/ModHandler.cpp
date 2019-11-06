#include <stdafx.h>
#include <filesystem>
#include <util/Utility.h>
#include <SatisfactoryModLoader.h>
#include "ModHandler.h"
#include <util/json.hpp>
#include <mod/Coremods.h>
#include <util/EnvironmentValidity.h>
#include <detours.h>

#include <cstdio>

namespace SML {
	namespace Mod {

		void ModHandler::loadMods() {
			this->currentStage = GameStage::CONSTRUCT;
			ModHandler::findMods(Utility::getModPath());
			ModHandler::findMods(Utility::getHiddenModPath());
		}

		void ModHandler::setupMods() {
			Utility::info("Starting mod setup!");
			this->currentStage = GameStage::SETUP;
			for (auto&& mod : mods) {
				mod->setup();
			}
		}

		void ModHandler::postSetupMods() {
			this->currentStage = GameStage::POST_SETUP;
			Utility::info("Starting mod post setup!");
			for (int i = 0; i < mods.size(); i++) {
				modNameDump.push_back(mods[i]->info.name);
			}
			for (int i = 0; i < mods.size(); i++) {
				recursiveDependencyLoad(*mods[i], i);
			}
		}

		void ModHandler::recursiveDependencyLoad(Mod& mod, int i) { // this code is a massive hack, TODO: refactor this mess
			for (std::string name : mod.info.dependencies) {
				if (name.substr(0, 1) == "*") {
					bool found = false;
					for (auto&& mod : this->mods) {
						if (mod->info.name == name.substr(1)) {
							found = true;
							break;
						}
					}
					if (!found) {
						continue;
					}
					name = name.substr(1);
				}
				auto iterator = std::find(modNameDump.begin(), modNameDump.end(), name);
				auto loc = std::distance(modNameDump.begin(), iterator);
				recursiveDependencyLoad(*mods[loc], loc);
			}
			mod.callPostSetup();
		}

		void ModHandler::checkDependencies() {
			std::vector<std::string> names;
			for (auto&& mod : mods) {
				names.push_back(mod->info.name);
			}
			for (auto&& mod : mods) {
				for (std::string dep : mod->info.dependencies) {
					Utility::debug("Parsing dependency " + dep);
					if (dep.substr(0, 1) == "*") {
						auto it = std::find(names.begin(), names.end(), dep.substr(1));
						if (it == names.end()) {
							Utility::warning(mod->info.name + " is missing optional dependency " + dep.substr(1));
						}
					}
					else {
						auto it = std::find(names.begin(), names.end(), dep);
						if (it == names.end()) {
							//quit if a required dependency isn't loaded
							Utility::displayCrash("Mod " + mod->info.name + " is missing dependency " + dep + "!\nPlease install " + dep + " or remove " + mod->info.name + ".\nPress Ok to exit.");
						}
					}
				}
			}
			Utility::info("Dependencies verified!");
		}

		bool ModHandler::createMod(Mod* (*modCreate)(), std::string file) {
			if (modCreate == nullptr) {
				Utility::error("Mod DLL ", file, " is missing modCreate()!");
				return false;
			}

			std::unique_ptr<Mod> mod{ modCreate() };
      
			if (mod == nullptr) {
				Utility::error("Mod DLL ", file, " returned nullptr from modCreate()!");
				return false;
			}

			// check if the mod has already been loaded
			for (auto&& existingMod : mods) {
				if (existingMod->info.name == mod->info.name) {
					Utility::warning("Skipping duplicate mod [", existingMod->info.name, "]");
					return false;
				}
			}

			//check if modloader's version is the same as the mod's target version
			size_t modTVOffset = mod->info.loaderVersion.find_last_of(".");
			size_t SMLOffset = modLoaderVersion.find_last_of(".");
			if (!(mod->info.loaderVersion.substr(0, modTVOffset) == modLoaderVersion.substr(0, SMLOffset))) {
				if (!supressErrors) {
					std::string msg = mod->info.name + " does not match SML's version! Please ask the mod developer (" + mod->info.authors + ") to update their mod. Press OK to continue mod loading.";
					MessageBoxA(NULL, msg.c_str(), "SatisfactoryModLoader Warning", MB_ICONWARNING);
				}
				if (!unsafeMode) {
					return false;
				}
			}

			Utility::debug("Loaded [", mod->info.name, "@", mod->info.version, "]");

			ModHandler::mods.emplace_back(std::move(mod));

			return true;
		}

		void ModHandler::loadDLL(LPCWSTR sw) {
			HMODULE dll = LoadLibraryW(sw);

			Mod* (*modCreate)() = (decltype(modCreate))GetProcAddress(dll, "ModCreate");

			std::wstring ws(sw);
			if (!createMod(modCreate, std::string(ws.begin(), ws.end()))) {
				if (!unsafeMode) {
					FreeLibrary(dll);
				}
			}
			else {
				dlls.push_back(dll);
			}
		}

		void ModHandler::getFiles(std::string path) {
			std::string pathExact = path + "\\";

			for (const auto &entry : std::experimental::filesystem::directory_iterator(path)) {
				if (std::filesystem::is_directory(entry.path().string())) {
					continue;
				}

				if (entry.path().extension().string() == ".dll") {
					std::string file = pathExact + entry.path().filename().string();
					Utility::debug("Attempting to load mod: ", file);

					std::wstring stemp = std::wstring(file.begin(), file.end());

					loadDLL(stemp.c_str());
				} else if (entry.path().extension().string() == ".zip") {
					// Ignore without warning
				} else {
					Utility::warning("Unkown mod file type: ", entry.path().filename().string());
				}
			}
		}

		void ModHandler::findMods(std::string path) {
			std::string pathExact = path + "\\";

			Utility::info("Looking for mods in: ", path);

			//ModHandler::mods.clear();

			getFiles(path);
		}

		void ModHandler::destroy() {
			Utility::debug("Cleaning up ModHandler");

			mods.clear();

			for (auto&& mod : dlls) {
				Utility::debug("Freeing: ", mod);
				if (!FreeLibrary(mod)) {
					Utility::error("Failed to free library: ", GetLastError());
				}
			}


			dlls.clear();

			Utility::debug("Cleaning up ModHandler... done");
		}
	}
}