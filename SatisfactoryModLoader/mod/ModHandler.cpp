#include <stdafx.h>
#include <filesystem>
#include <util/Utility.h>
#include <util/Reflection.h>
#include <util/Config.h>
#include "ModHandler.h"

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
		auto pointer = (void(WINAPI*)())get_dll_function(mod.name, "setup");
		pointer();
	}
}

// find all valid mods
void ModHandler::find_mods(std::string path) {
	std::string pathExact = path + "\\";

	log(LogType::Normal, "Looking for mods in: ", path);

	ModHandler::mods = std::vector<Mod>();

	for (const auto & entry : std::experimental::filesystem::directory_iterator(path)) {
		if (entry.path().extension().string() == ".dll") {
			std::string file = pathExact + entry.path().filename().string();
			std::wstring stemp = std::wstring(file.begin(), file.end());
			if (debugOutput) {
				log(LogType::Normal, "Attempting to load mod: ", file);
			}

			LPCWSTR sw = stemp.c_str();

			HMODULE dll = LoadLibrary(sw);

			std::string modName;
			std::string modVersion;
			std::string modDescription;
			std::string modAuthors;

			if (!get_field_value(dll, "ModName", modName) ||
				!get_field_value(dll, "ModVersion", modVersion) ||
				!get_field_value(dll, "ModDescription", modDescription) ||
				!get_field_value(dll, "ModAuthors", modAuthors)) {

				log(LogType::Error, "Mod DLL ", file, " does not have the required information!");
				FreeLibrary(dll);
				continue;
			}

			// check if the mod has already been loaded
			bool isDuplicate = false;
			for (Mod existingMod : ModHandler::mods) {
				if (existingMod.name == modName) {
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
				sw,
				dll,
				modName,
				modVersion,
				modDescription,
				modAuthors
			};

			ModHandler::mods.push_back(mod);
			if (debugOutput) {
				log(LogType::Normal, "Loaded [", mod.name, "@", mod.version, "]");
			}
		}
	}

}