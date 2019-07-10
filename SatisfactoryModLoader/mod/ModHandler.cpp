#include <stdafx.h>
#include <filesystem>
#include <util/Utility.h>
#include <util/Reflection.h>
#include <SatisfactoryModLoader.h>
#include "ModHandler.h"

namespace SML {
	namespace Mod {
		// load all mods from the given path
		void ModHandler::loadMods(const char* startingPath) {
			this->currentStage = GameStage::CONSTRUCT;
			// split the path
			std::string appPath(startingPath);
			size_t pos = appPath.find_last_of('\\');
			CreateDirectoryA((appPath.substr(0, pos) + "\\mods").c_str(), NULL); //create the directory if it doesn't exist
			std::string path = appPath.substr(0, pos) + "\\mods";

			ModHandler::findMods(path);
		}

		//call the setup function of every loaded mod
		void ModHandler::setupMods() {
			Utility::info("Starting mod Setup!");
			this->currentStage = GameStage::SETUP;
			for (auto&& mod : mods) {
				mod->setup();
			}
		}

		//call the post setup function of every mod through recursive calling, ensuring the post setups of mod dependencies loaded before the original mod's post setup
		void ModHandler::postSetupMods() {
			this->currentStage = GameStage::POST_SETUP;
			Utility::info("Starting mod Post Setup!");
			for (int i = 0; i < mods.size(); i++) {
				modNameDump.push_back(mods[i]->info.name);
			}
			for (int i = 0; i < mods.size(); i++) {
				recursiveDependencyLoad(*mods[i], i);
			}
		}

		//recustively load mod dependencies
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
				int loc = std::distance(modNameDump.begin(), iterator);
				recursiveDependencyLoad(*mods[loc], loc);
			}
			mod.callPostSetup();
		}

		// ensure that all dependencies of mods exist
		void ModHandler::checkDependencies() {
			std::vector<std::string> names;
			for (auto&& mod : mods) {
				names.push_back(mod->info.name);
			}
			for (auto&& mod : mods) {
				for (std::string dep : mod->info.dependencies) {
					Utility::info("Parsing dependency " + dep);
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
			Utility::info("Verifyied dependencies");
		}

		//get the mod files and load them
		void ModHandler::getFiles(std::string path) {
			std::string pathExact = path + "\\";

			for (const auto & entry : std::experimental::filesystem::directory_iterator(path)) {
				/*
				if (!entry.path().has_extension()) {
					getFiles(entry.path().string());
					continue;
				}
				*/

				if (entry.path().extension().string() == ".dll") {
					std::string file = pathExact + entry.path().filename().string();
					std::wstring stemp = std::wstring(file.begin(), file.end());
					if (debugOutput) {
						Utility::info("Attempting to load mod: ", file);
					}

					LPCWSTR sw = stemp.c_str();

					HMODULE dll = LoadLibraryW(sw);

					Mod* (*modCreate)();

					modCreate = (decltype(modCreate))GetProcAddress(dll, "ModCreate");

					if (modCreate == nullptr) {
						Utility::error("Mod DLL ", file, " does not have the required information!");
						FreeLibrary(dll);
						continue;
					}

					std::unique_ptr<Mod> mod{ modCreate() };

					if (mod == nullptr) {
						Utility::error("Mod DLL ", file, " returned nullptr from modCreate()!");
						FreeLibrary(dll);
						continue;
					}

					// check if the mod has already been loaded
					bool isDuplicate = false;
					for (auto&& existingMod : mods) {
						if (existingMod->info.name == mod->info.name) {
							Utility::warning("Skipping duplicate mod [", existingMod->info.name, "]");
							FreeLibrary(dll);
							isDuplicate = true;
							break;
						}
					}

					//continue if the mod is loaded already
					if (isDuplicate) {
						continue;
					}

					//check if modloader's version is the same as the mod's target version
					size_t modTVOffset = mod->info.loaderVersion.find_last_of(".");
					size_t SMLOffset = modLoaderVersion.find_last_of(".");
					if (!(mod->info.loaderVersion.substr(0, modTVOffset) == modLoaderVersion.substr(0, SMLOffset))) {
						std::string msg = "Mod " + mod->info.name + " does not match SML's version! Please ask the mod developer (" + mod->info.authors + ") to update their mod. Press OK to continue mod loading.";
						MessageBoxA(NULL, msg.c_str(), "SatisfactoryModLoader Warning", MB_ICONWARNING);
						FreeLibrary(dll);
						continue;
					}

					std::string s = entry.path().filename().string();
					size_t namePos = s.find_last_of('.');
					std::string fileName = s.substr(0, namePos);

					if (debugOutput) {
						Utility::info("Loaded [", mod->info.name, "@", mod->info.version, "]");
					}
					ModHandler::mods.emplace_back(std::move(mod));
				}
			}
		}

		// find all valid mods
		void ModHandler::findMods(std::string path) {
			std::string pathExact = path + "\\";

			Utility::info("Looking for mods in: ", path);

			ModHandler::mods.clear();

			getFiles(path);
		}
	}
}