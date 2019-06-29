#include <stdafx.h>
#include <filesystem>
#include <util/Utility.h>
#include <util/Reflection.h>
#include <SatisfactoryModLoader.h>
#include "ModHandler.h"
#include <util/json.hpp>

#include <cstdio>
#include <ttvfs.h>
#include <ttvfs_zip.h>

#include "zip/MemoryModule.h"

namespace SML {
	namespace Mod {

		void ModHandler::loadMods(const char* startingPath) {
			this->currentStage = GameStage::CONSTRUCT;
			// split the path
			std::string appPath(startingPath);
			size_t pos = appPath.find_last_of('\\');
			CreateDirectoryA((appPath.substr(0, pos) + "\\mods").c_str(), NULL); //create the directory if it doesn't exist
			std::string path = appPath.substr(0, pos) + "\\mods";

			ModHandler::findMods(path);
		}

		void ModHandler::setupMods() {
			Utility::info("Starting mod Setup!");
			this->currentStage = GameStage::SETUP;
			for (auto&& mod : mods) {
				mod->setup();
			}
		}

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
							std::string msg = "Mod " + mod->info.name + " is missing dependency " + dep + "!\nPlease install " + dep + " or remove " + mod->info.name + ".\nPress Ok to exit.";
							MessageBoxA(NULL, msg.c_str(), "SatisfactoryModLoader Fatal Error", MB_ICONERROR);
							abort();
						}
					}
				}
			}
			Utility::info("Verifyied dependencies");
		}

		bool ModHandler::createMod(Mod* (*modCreate)()) {
			if (modCreate == nullptr) {
				Utility::error("Mod is missing modCreate() function!");
				return false;
			}

			std::unique_ptr<Mod> mod{ modCreate() };

			if (mod == nullptr) {
				Utility::error("Mod returned nullptr from modCreate()!");
				return false;
			}

			// check if the mod has already been loaded
			bool isDuplicate = false;
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
				std::string msg = "Mod " + mod->info.name + " does not match SML's version! Please ask the mod developer (" + mod->info.authors + ") to update their mod. Press OK to continue mod loading.";
				MessageBoxA(NULL, msg.c_str(), "Mod Loading Warning", MB_ICONWARNING);
				return false;
			}

			Utility::debug("Loaded [", mod->info.name, "@", mod->info.version, "]");

			ModHandler::mods.emplace_back(std::move(mod));

			return true;
		}

		void ModHandler::loadDLL(LPCWSTR sw) {
			HMODULE dll = LoadLibraryW(sw);

			Mod* (*modCreate)() = (decltype(modCreate))GetProcAddress(dll, "ModCreate");

			if (!createMod(modCreate)) {
				FreeLibrary(dll);
			}
		}

		void ModHandler::loadMemoryDLL(void *data, size_t size) {
			HMEMORYMODULE dll = MemoryLoadLibrary(data, size);
			
			if (dll == NULL) {
				Utility::error("Error loading library from memory: ", GetLastError());
				return;
			}

			Mod* (*modCreate)() = (decltype(modCreate))MemoryGetProcAddress(dll, "ModCreate");

			if (!createMod(modCreate)) {
				// TODO Figure out why this crashes the game
				MemoryFreeLibrary(dll);
			}
		}

		void ModHandler::getFiles(std::string path) {
			std::string pathExact = path + "\\";

			for (const auto & entry : std::experimental::filesystem::directory_iterator(path)) {

				if (std::filesystem::is_directory(entry.path().string())) {
					getFiles(entry.path().string());
					continue;
				}

				if (entry.path().extension().string() == ".dll") {
					std::string file = pathExact + entry.path().filename().string();
					Utility::debug("Attempting to load mod: ", file);

					std::wstring stemp = std::wstring(file.begin(), file.end());

					loadDLL(stemp.c_str());
				} else if(entry.path().extension().string() == ".zip") {
					std::string archive = pathExact + entry.path().filename().string();
					Utility::debug("Attempting to load mod: ", archive);

					ttvfs::Root vfs;

					vfs.AddLoader(new ttvfs::DiskLoader);
					vfs.AddArchiveLoader(new ttvfs::VFSZipArchiveLoader);

					auto modArchive = vfs.AddArchive(archive.c_str());

					ttvfs::File *vf = modArchive->getFile("data.json");
					if (!vf || !vf->open("r")) {
						Utility::error("Failed loading mod data.json in ", archive);
						continue;
					}

					std::vector<char> buffer(vf->size());
					size_t bytes = vf->read(buffer.data(), vf->size());
					vf->close();

					nlohmann::json dataJson;

					try {
						dataJson = nlohmann::json::parse(buffer.data());
					}
					catch (...) {}

					auto objects = dataJson["objects"];

					for (auto it = objects.begin(); it != objects.end(); ++it) {
						std::string objType = it.value()["type"].get<std::string>();
						std::string objPath = it.value()["path"].get<std::string>();

						Utility::debug("[", entry.path().filename(), "] ", "Loading \"", objType, "\" ", objPath);

						if (objType == "sml_mod") {
							auto obj = modArchive->getFile(objPath.c_str());

							if (!obj || !obj->open("rb")) {
								Utility::error("Failed loading object: ", objPath, " in ", archive);
								continue;
							}

							void* result = (unsigned char *)malloc(obj->size());
							size_t bytes = obj->read(result, obj->size());
							obj->close();

							loadMemoryDLL(result, obj->size());
						} else {
							Utility::error("Unkown object type: ", objType);
						}
					}
				}
			}
		}

		void ModHandler::findMods(std::string path) {
			std::string pathExact = path + "\\";

			Utility::info("Looking for mods in: ", path);

			ModHandler::mods.clear();

			getFiles(path);
		}
	}
}