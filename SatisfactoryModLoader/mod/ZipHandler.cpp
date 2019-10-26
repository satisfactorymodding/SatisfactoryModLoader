#include <stdafx.h>
#include <filesystem>
#include <util/Utility.h>
#include <SatisfactoryModLoader.h>
#include "ZipHandler.h"
#include "ModHandler.h"
#include <util/json.hpp>
#include <mod/Coremods.h>
#include <util/EnvironmentValidity.h>
#include <detours.h>

#include <cstdio>
#include "zip/MemoryModule.h"

namespace SML {
	namespace Mod {

		void ZipHandler::extractZips() {
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
						Utility::displayCrash("Invalid zip mod: " + entry.path().filename().string(),
							"Mod '" + entry.path().filename().string() + "' is not a valid zip mod."
							"\n\nPlease make sure you are using the most up to date mod version."
							"\n\nIf you are on the latest version, please notify the mod author that they are missing 'objects' in 'data.json'");
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

		void ZipHandler::loadMemoryDLL(void *data, size_t size, std::string file, ModHandler modHandler) {
			HMEMORYMODULE dll = MemoryLoadLibrary(data, size);

			if (dll == NULL) {
				Utility::error("Error loading library from memory: ", GetLastError());
				return;
			}

			Mod* (*modCreate)() = (decltype(modCreate))MemoryGetProcAddress(dll, "ModCreate");

			if (!modHandler.createMod(modCreate, file)) {
				MemoryFreeLibrary(dll);
			}
		}

		void ZipHandler::destroy() {
			Utility::debug("Cleaning up ZipHandler");

			Utility::debug("Deleting extracted files");
			for (auto&& file : cleanupPaths) {
				Utility::debug("Deleting: ", file);
				if (!std::filesystem::remove(file)) {
					Utility::error("Failed to delete: ", file);
				}
			}

			Utility::debug("Cleaning up ZipHandler... done");
		}

		void ZipHandler::extractFile(ttvfs::Dir* archive, std::string objPath, std::string outFilePath, std::string archiveName, bool cleanup) {
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