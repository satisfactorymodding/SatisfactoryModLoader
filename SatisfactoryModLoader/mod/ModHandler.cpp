#include <stdafx.h>
#include <filesystem>
#include <util/Utility.h>
#include <util/Reflection.h>
#include <SatisfactoryModLoader.h>
#include "ModHandler.h"
#include "util/json.hpp"

// https://github.com/nlohmann/json
using json = nlohmann::json;

// load all mods from the given path
void ModHandler::load_mods(const char* startingPath) {
	// split the path
	std::string appPath(startingPath);
	size_t pos = appPath.find_last_of('\\');
	CreateDirectoryA((appPath.substr(0, pos) + "\\mods").c_str(), NULL); //create the directory if it doesn't exist
	std::string path = appPath.substr(0, pos) + "\\mods";

	ModHandler::find_mods(path);
}

void ModHandler::setup_mods() {
	for (auto&& mod : mods) {
		info("Setting up ", mod->info.name);
		mod->setup();
	}
}

void ModHandler::post_setup_mods() {
	info("Starting Post Setup!");
	for (int i = 0; i < mods.size(); i++) {
		modNameDump.push_back(mods[i]->info.name);
	}
	for (int i = 0; i < mods.size(); i++) {
		recursive_dependency_load(*mods[i], i);
	}
}

void ModHandler::recursive_dependency_load(Mod& mod, int i) { // this code is a massive hack, TODO: refactor this mess
	for (std::string name : mod.info.dependencies) {
		auto iterator = std::find(modNameDump.begin(), modNameDump.end(), name);
		int loc = std::distance(modNameDump.begin(), iterator);
		recursive_dependency_load(*mods[loc], loc);
	}
	mod.call_post_setup();
}

void ModHandler::check_dependencies() {
	info("Verifying dependencies...");
	std::vector<std::string> names;
	for (auto&& mod : mods) {
		names.push_back(mod->info.name);
	}
	for (auto&& mod : mods) {
		for (std::string dep : mod->info.dependencies) {
			info("Parsing dependency " + dep);
			if (dep.substr(0, 1) == "*") {
				auto it = std::find(names.begin(), names.end(), dep.substr(1));
				if (it == names.end()) {
					warning(mod->info.name + " is missing optional dependency " + dep.substr(1));
				}
			} else {
				auto it = std::find(names.begin(), names.end(), dep);
				if (it == names.end()) {
					std::string msg = "Mod " + mod->info.name + " is missing dependency " + dep + "!\nPlease install " + dep + " or remove " + mod->info.name + ".\nPress Ok to exit.";
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

			HMODULE dll = LoadLibraryW(sw);

			Mod* (*modCreate)();

			modCreate = (decltype(modCreate))GetProcAddress(dll, "ModCreate");

			if (modCreate == nullptr) {
				error("Mod DLL ", file, " does not have the required information!");
				FreeLibrary(dll);
				continue;
			}

			std::unique_ptr<Mod> mod{ modCreate() };

			if(mod == nullptr) {
				error("Mod DLL ", file, " returned nullptr from modCreate()!");
				FreeLibrary(dll);
				continue;
			}

			// check if the mod has already been loaded
			bool isDuplicate = false;
			for (auto&& existingMod : mods) {
				if (existingMod->info.name == mod->info.name) {
					warning("Skipping duplicate mod [", existingMod->info.name, "]");
					FreeLibrary(dll);
					isDuplicate = true;
					break;
				}
			}

			if (isDuplicate) {
				continue;
			}

			//check if modloader's version is the same as the mod's target version
			size_t modTVOffset = mod->info.loaderVersion.find_last_of(".");
			size_t SMLOffset = modLoaderVersion.find_last_of(".");
			if (!(mod->info.loaderVersion.substr(0, modTVOffset) == modLoaderVersion.substr(0, SMLOffset))) {
				std::string msg = "Mod " + mod->info.name + " does not match SML's version! Please ask the mod developer (" + mod->info.authors + ") to update their mod. Press OK to continue mod loading.";
				MessageBoxA(NULL, msg.c_str(), "Mod Loading Warning", MB_ICONWARNING);
				FreeLibrary(dll);
				continue;
			}

			std::string s = entry.path().filename().string();
			size_t namePos = s.find_last_of('.');
			std::string fileName = s.substr(0, namePos);

			if (debugOutput) {
				info("Loaded [", mod->info.name, "@", mod->info.version, "]");
			}
			ModHandler::mods.emplace_back(std::move(mod));
		}
	}
}

// find all valid mods
void ModHandler::find_mods(std::string path) {
	std::string pathExact = path + "\\";

	info("Looking for mods in: ", path);

	ModHandler::mods.clear();

	get_files(path);
}