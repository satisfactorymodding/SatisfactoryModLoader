#include <stdafx.h>
#include <filesystem>
#include <util/Utility.h>
#include <util/Reflection.h>
#include <SatisfactoryModLoader.h>
#include "ModHandler.h"
#include <util/json.hpp>
#include <mod/Coremods.h>
#include <util/EnvironmentValidity.h>
#include <detours.h>

#include <cstdio>
#include <ttvfs.h>
#include <ttvfs_zip.h>

#include "zip/MemoryModule.h"

namespace SML {
	namespace Mod {

		void ModHandler::extractZips() {
			Utility::cleanupHiddenDirectories();

			auto path = Utility::getModPath();
			std::string pathExact = path + "\\";

			for (const auto &entry : std::experimental::filesystem::directory_iterator(path)) {
				if (std::filesystem::is_directory(entry.path().string())) {
					continue;
				}

				if (entry.path().extension().string() == ".zip") {
					std::string archive = pathExact + entry.path().filename().string();
					Utility::debug("Processing archive: ", archive);

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

					if (!dataJson.contains("objects")) {
						Utility::error("data.json missing objects in ", archive);
						continue;
					}

					auto objects = dataJson["objects"];

					for (auto it = objects.begin(); it != objects.end(); ++it) {
						std::string objType = it.value()["type"].get<std::string>();
						std::string objPath = it.value()["path"].get<std::string>();

						Utility::debug("[", entry.path().filename(), "] ", "Loading \"", objType, "\" ", objPath);

						if (objType == "sml_mod") {
							auto fileName = objPath;

							auto lastSlash = objPath.find_last_of("/\\");
							if (lastSlash != std::string::npos) {
								fileName = fileName.substr(lastSlash + 1);
							}

							extractFile(modArchive, objPath, Utility::getHiddenModPath() + "\\" + fileName, archive, false);
						}
						else if (objType == "core_mod") {
							auto fileName = objPath;

							auto lastSlash = objPath.find_last_of("/\\");
							if (lastSlash != std::string::npos) {
								fileName = fileName.substr(lastSlash + 1);
							}

							extractFile(modArchive, objPath, Utility::getHiddenCoreModPath() + "\\" + fileName, archive, false);
						}
						else if (objType == "pak") {
							auto pakName = objPath;

							auto lastSlash = objPath.find_last_of("/\\");
							if (lastSlash != std::string::npos) {
								pakName = pakName.substr(lastSlash + 1);
							}

							extractFile(modArchive, objPath, Utility::getPakPath() + "\\" + pakName, archive, true);

							auto sigName = pakName;
							auto extension = sigName.find_last_of(".");
							if (extension != std::string::npos) {
								sigName = sigName.substr(0, extension);
							}
							cleanupPaths.push_back(Utility::getPakPath() + "\\" + sigName + ".sig");
						}
						else {
							Utility::warning("Unkown object type: ", objType);
						}
					}
				}
				else {
					Utility::warning("Unkown mod file type: ", entry.path().filename().string());
				}
			}
		}

		void ModHandler::loadMods() {
			this->currentStage = GameStage::CONSTRUCT;
			ModHandler::findMods(Utility::getModPath());
			ModHandler::findMods(Utility::getHiddenModPath());
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
							Utility::displayCrash("Mod " + mod->info.name + " is missing dependency " + dep + "!\nPlease install " + dep + " or remove " + mod->info.name + ".\nPress Ok to exit.");
						}
					}
				}
			}
			Utility::info("Verified dependencies");
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
			else {
				dlls.push_back(dll);
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
				MemoryFreeLibrary(dll);
			}
		}

		void ModHandler::getFiles(std::string path) {
			std::string pathExact = path + "\\";

			for (const auto &entry : std::experimental::filesystem::directory_iterator(path)) {

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
					// Disable zip processing
					continue;

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

					if (!dataJson.contains("objects")) {
						Utility::error("data.json missing objects in ", archive);
						continue;
					}

					auto objects = dataJson["objects"];

					for (auto it = objects.begin(); it != objects.end(); ++it) {
						std::string objType = it.value()["type"].get<std::string>();
						std::string objPath = it.value()["path"].get<std::string>();

						Utility::debug("[", entry.path().filename(), "] ", "Loading \"", objType, "\" ", objPath);

						if (objType == "sml_mod") {
							/*
							auto obj = modArchive->getFile(objPath.c_str());

							if (!obj || !obj->open("rb")) {
								Utility::error("Failed loading object: ", objPath, " in ", archive);
								continue;
							}

							void* result = (unsigned char *)malloc(obj->size());
							size_t bytes = obj->read(result, obj->size());
							obj->close();

							loadMemoryDLL(result, obj->size());
							*/
						} else if (objType == "core_mod") {
							// SHIT BROKEN
							/*
							auto obj = modArchive->getFile(objPath.c_str());

							if (!obj || !obj->open("rb")) {
								Utility::error("Failed loading object: ", objPath, " in ", archive);
								continue;
							}

							void* result = (unsigned char *)malloc(obj->size());
							size_t bytes = obj->read(result, obj->size());
							obj->close();

							loadMemoryCoreMod(result, obj->size(), objPath)
							*/
						} else if (objType == "pak") {
							// Do nothing
						} else {
							Utility::warning("Unkown object type: ", objType);
						}
					}
				} else {
					Utility::warning("Unkown mod file type: ", entry.path().filename().string());
				}
			}

			Utility::checkForValidEnvironment();
		}

		void ModHandler::findMods(std::string path) {
			std::string pathExact = path + "\\";

			Utility::info("Looking for mods in: ", path);

			ModHandler::mods.clear();

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

			Utility::debug("Deleting extracted files");
			for (auto&& file : cleanupPaths) {
				Utility::debug("Deleting: ", file);
				if (!std::filesystem::remove(file)) {
					Utility::error("Failed to delete: ", file);
				}
			}

			Utility::debug("Cleaning up ModHandler... done");
		}

		void ModHandler::extractFile(ttvfs::Dir* archive, std::string objPath, std::string outFilePath, std::string archiveName, bool cleanup) {
			if (std::filesystem::exists(outFilePath)) {
				if (cleanup) {
					cleanupPaths.push_back(outFilePath);
				}
				Utility::error("File already exists: ", outFilePath);
				return;
			}

			std::ofstream outFile(outFilePath, std::ofstream::binary);

			if (!outFile.is_open()) {
				Utility::error("Failed writing to file: ", outFilePath);
				return;
			}

			auto obj = archive->getFile(objPath.c_str());

			if (!obj || !obj->open("rb")) {
				Utility::error("Failed loading object: ", objPath, " in ", archiveName);
				return;
			}

			Utility::debug("Extracting: ", objPath, " -> ", outFilePath);

			auto buffer_size = 4096;
			char* buf = new char[buffer_size];
			auto total = 0;
			do {
				size_t bytes = obj->read(buf, buffer_size);
				outFile.write(buf, bytes);
				total += bytes;
			} while (obj->getpos() < obj->size());

			outFile.close();

			if (cleanup) {
				cleanupPaths.push_back(outFilePath);
			}
		}
	}
}