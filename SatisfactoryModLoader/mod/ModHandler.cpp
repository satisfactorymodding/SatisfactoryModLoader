#include <stdafx.h>
#include <filesystem>
#include <util/Utility.h>
#include <util/Reflection.h>
#include <util/Config.h>
#include "ModHandler.h"
#include "util/json.hpp"

// https://github.com/nlohmann/json
using json = nlohmann::json;

// load all mods from the given path
void ModHandler::load_mods(const char* startingPath) {
	// split the path
	std::string appPath(startingPath);
	size_t pos = appPath.find_last_of('\\');
	std::string path = appPath.substr(0, pos) + "\\mods";

	ModHandler::find_mods(path);
}

void ModHandler::setup_mods() {
	for (Mod mod : mods) {
		log(LogType::Normal, "Setting up ", mod.name);
		auto pointer = (void(WINAPI*)())get_function(mod.fileName, "setup");
		if (pointer == NULL) {
			log(LogType::Error, "Setup function missing for ", mod.name);
			continue;
		}
		pointer();
	}
}

void ModHandler::get_files(std::string path) {
	std::string pathExact = path + "\\";

	for (const auto & entry : std::experimental::filesystem::directory_iterator(path)) {

		log(LogType::Normal, entry.path().string());

		if (!entry.path().has_extension()) {
			get_files(entry.path().string());
			continue;
		}

		if (entry.path().extension().string() == ".dll") {
			std::string file = pathExact + entry.path().filename().string();
			std::wstring stemp = std::wstring(file.begin(), file.end());
			if (debugOutput) {
				log(LogType::Normal, "Attempting to load mod: ", file);
			}

			LPCWSTR sw = stemp.c_str();

			HMODULE dll = LoadLibrary(sw);

			std::string s = entry.path().filename().string();
			size_t namePos = s.find_last_of('.');
			std::string fileName = s.substr(0, namePos);

			log(LogType::Normal, "Path: " + path + "\\" + fileName + ".cfg");

			std::ifstream config(path + "\\" + fileName + ".cfg");
			std::string line;
			// see if a config file exists

			if (config.good()) {
				if (config.is_open()) {
					std::string contents;
					// read the config file line by line
					while (getline(config, line)) {
						contents += line;
					}

					auto j = json::parse(contents);

					// check if the mod has already been loaded
					bool isDuplicate = false;
					for (Mod existingMod : ModHandler::mods) {
						if (existingMod.name == j["Name"]) {
							log(LogType::Warning, "Skipping duplicate mod [", existingMod.name, "]");
							FreeLibrary(dll);
							isDuplicate = true;
							break;
						}
					}

					if (isDuplicate) {
						continue;
					}

					// if valid, initalize a mod struct and add it to the modlist
					Mod mod = {
						fileName,
						dll,
						j["Name"],
						j["Version"],
						j["Description"],
						j["Authors"]
					};

					ModHandler::mods.push_back(mod);
					if (debugOutput) {
						log(LogType::Normal, "Loaded [", mod.name, "@", mod.version, "]");
					}
				}
			}
			else {
				log(LogType::Error, "Mod DLL ", fileName, " does not have the required information!");
				FreeLibrary(dll);
				continue;
			}
		}
	}
}

// find all valid mods
void ModHandler::find_mods(std::string path) {
	std::string pathExact = path + "\\";

	log(LogType::Normal, "Looking for mods in: ", path);

	ModHandler::mods = std::vector<Mod>();

	get_files(path);
}