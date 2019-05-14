// dllmain.cpp : Defines the entry point for the DLL application.
#define WIN32_LEAN_AND_MEAN
#include <stdafx.h>
#include <SatisfactoryModLoader.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <functional>
#include <chrono>
#include <thread>
#include <util/Utility.h>
#include <util/Reflection.h>
#include <util/JsonConfig.h>
#include <mod/Hooks.h>

namespace SML {
	static const char* logName = "SatisfactoryModLoader.log";
	Mod::ModHandler modHandler;

	// Main DLL for loading mod DLLs
	void mod_loader_entry() {
		// launch the game's internal console and hook into it
		Utility::logFile = std::ofstream(logName, std::ios_base::trunc);
		Utility::logFile.close();
		Utility::logFile = std::ofstream(logName, std::ios_base::app);
		AllocConsole();
		ShowWindow(GetConsoleWindow(), SW_HIDE);
		FILE* fp;
		freopen_s(&fp, "CONOIN$", "r", stdin);
		freopen_s(&fp, "CONOUT$", "w", stdout);
		freopen_s(&fp, "CONOUT$", "w", stderr);
		Utility::logFile.clear();

		ShowWindow(GetConsoleWindow(), SW_SHOW);

		Utility::info("Attached SatisfactoryModLoader to Satisfactory");

		// load up all of the configuration information
		read_config();

		//make sure that SML's target and satisfactory's versions are the same
		Utility::check_version(targetVersion);
		if (loadConsole) {
			ShowWindow(GetConsoleWindow(), SW_SHOW);
		}

		// get path
		char p[MAX_PATH];
		GetModuleFileNameA(NULL, p, MAX_PATH);

		// load mods
		modHandler.load_mods(p);
		modHandler.setup_mods();
		modHandler.check_dependencies();
		modHandler.post_setup_mods();
		Mod::Hooks::hookFunctions();

		// log mod size
		size_t listSize = modHandler.mods.size();
		Utility::info("Loaded ", listSize, " mod", (listSize > 1 || listSize == 0 ? "s" : ""));

		//Display info about registries
		Utility::info("Registered ", modHandler.commandRegistry.size(), " Command", (modHandler.commandRegistry.size() > 1 || modHandler.commandRegistry.size() == 0 ? "s" : ""));
		Utility::info("Registered ", modHandler.APIRegistry.size(), " API function", (modHandler.APIRegistry.size() > 1 || modHandler.APIRegistry.size() == 0 ? "s" : ""));

		//display condensed form of mod information
		std::string modList = "[";
		for (auto&& mod : modHandler.mods) {
			modList.append(mod->info.name + "@" + mod->info.version + ", ");
		}

		if (listSize > 0) {
			Utility::info("Loaded mods: ", modList.substr(0, modList.length() - 2), "]");
		}

		Utility::info("SatisfactoryModLoader Initialization complete. Launching Satisfactory...");
	}

	//read the config file
	void read_config() {
		Utility::info("Finding config file...");
		json config = Utility::JsonConfig::load("SatisfactoryModLoader", {
			{"Console", true},
			{"Debug" , false},
			{"Supress Errors", false}
		}, false);

		loadConsole = config["Console"].get<bool>();
		debugOutput = config["Debug"].get<bool>();
		supressErrors = config["Supress Errors"].get<bool>();
	}

	//cleans up when the program is killed
	void cleanup() {
		modHandler.mods.clear();

		Utility::info("SML shutting down...");
		Utility::logFile.close();
	}
}