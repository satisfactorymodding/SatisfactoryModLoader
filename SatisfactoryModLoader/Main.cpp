// dllmain.cpp : Defines the entry point for the DLL application.
#include <stdafx.h>
#include <Main.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <functional>
#include <chrono>
#include <thread>
#include <util/Utility.h>
#include <util/Config.h>
#include <util/Reflection.h>
#include <mod/ModHandler.h>
#include <event/EventLoader.h>
#include <event/FunctionHolder.h>

// Main DLL for loading mod DLLs
void mod_loader_entry() {
	// launch the game's internal console and hook into it
	AllocConsole();
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	FILE* fp;
	freopen_s(&fp, "CONOIN$", "r", stdin);
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);

	log(LogType::Normal, "Attached SatisfactoryModLoader to Satisfactory");

	// load up all of the configuration information
	readConfig();

	if (loadConsole) {
		ShowWindow(GetConsoleWindow(), SW_SHOW);
	}
	
	// load mods
	// get path
	char p[MAX_PATH];
	GetModuleFileNameA(NULL, p, MAX_PATH);

	// load mods
	ModHandler modHandler;
	modHandler.load_mods(p);
	modHandler.setup_mods();

	// log mod size
	size_t listSize = modHandler.mods.size();
	log(LogType::Normal, "Loaded ", listSize, " mod", (listSize > 1 || listSize == 0 ? "s" : ""));

	//display condensed form of mod information
	std::string modList = "[";
	for (Mod mod : modHandler.mods) {
		modList.append(mod.name + "@" + mod.version + ", ");
	}

	if (listSize > 0) {
		log(LogType::Normal, "Loaded mods: ", modList.substr(0, modList.length() - 2), "]");
	}

	// hook original functions
	EventLoader eventLoader(modHandler.mods);
	eventLoader.hook_events();

	check_version(targetVersion);

	log(LogType::Normal, "SatisfactoryModLoader Initialization complete. Launching Satisfactory...");
}

//cleans up when the program is killed
void cleanup() {
	log(LogType::Normal, "SML shutting down...");
	_logFile.close();
}