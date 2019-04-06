#include <stdafx.h>
#include <filesystem>
#include <util/Utility.h>
#include <util/Reflection.h>
#include <Main.h>
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
		info("Setting up ", mod.name);
		auto pointer = (void(WINAPI*)())get_function(mod.fileName, "setup");
		if (pointer == NULL) {
			error("Setup function missing for ", mod.name);
			continue;
		}
		pointer();
	}
}

void ModHandler::check_dependencies() {
	std::vector<std::string> names;
	for (Mod mod : mods) {
		names.push_back(mod.name);
	}
	for (Mod mod : mods) {
		for (std::string dep : mod.dependencies) {
			info("Parsing dependency " + dep);
			if (dep.substr(0, 1) == "*") {
				auto it = std::find(names.begin(), names.end(), dep.substr(1));
				if (it == names.end()) {
					warning(mod.name + " is missing optional dependency " + dep.substr(1));
				}
			} else {
				auto it = std::find(names.begin(), names.end(), dep);
				if (it == names.end()) {
					std::string msg = "Mod " + mod.name + " is missing dependency " + dep + "!\nPlease install " + dep + " or remove " + mod.name + ".\nPress Ok to exit.";
					MessageBoxA(NULL, msg.c_str(), "SatisfactoryModLoader Fatal Error", MB_ICONERROR);
					abort();
				}
			}
		}
	}
}

void ModHandler::get_files(std::string path) {
	std::string pathExact = path + "\\";

	for (const auto & entry : std::experimental::filesystem::directory_iterator(path)) {

		info(entry.path().string());

		if (!entry.path().has_extension()) {
			get_files(entry.path().string());
			continue;
		}

		if (entry.path().extension().string() == ".dll") {
			std::string file = pathExact + entry.path().filename().string();
			std::wstring stemp = std::wstring(file.begin(), file.end());
			if (debugOutput) {
				info("Attempting to load mod: ", file);
			}

			LPCWSTR sw = stemp.c_str();

			HMODULE dll = LoadLibrary(sw);

			std::string modName;
			std::string modVersion;
			std::string modDescription;
			std::string modAuthors;
			std::vector<std::string> modDependencies;

			if (!get_field_value(dll, "ModName", modName) ||
				!get_field_value(dll, "ModVersion", modVersion) ||
				!get_field_value(dll, "ModDescription", modDescription) ||
				!get_field_value(dll, "ModAuthors", modAuthors) ||
				!get_field_value(dll, "ModDependencies", modDependencies)) {

				error("Mod DLL ", file, " does not have the required information!");
				FreeLibrary(dll);
				continue;
			}

			// check if the mod has already been loaded
			bool isDuplicate = false;
			for (Mod existingMod : mods) {
				if (existingMod.name == modName) {
					warning("Skipping duplicate mod [", existingMod.name, "]");
					FreeLibrary(dll);
					isDuplicate = true;
					break;
				}
			}

			if (isDuplicate) {
				continue;
			}

			std::string s = entry.path().filename().string();
			size_t namePos = s.find_last_of('.');
			std::string fileName = s.substr(0, namePos);

			// if valid, initalize a mod struct and add it to the modlist
			Mod mod = {
				fileName,
				dll,
				modName,
				modVersion,
				modDescription,
				modAuthors,
				modDependencies
			};

			ModHandler::mods.push_back(mod);
			if (debugOutput) {
				info("Loaded [", mod.name, "@", mod.version, "]");
			}
		}
	}
}

// find all valid mods
void ModHandler::find_mods(std::string path) {
	std::string pathExact = path + "\\";

	info("Looking for mods in: ", path);

	ModHandler::mods = std::vector<Mod>();

	get_files(path);
}