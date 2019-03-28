// dllmain.cpp : Defines the entry point for the DLL application.
#include <stdafx.h>
#include <util/Utility.h>
#include <util/Config.h>
#include <util/Reflection.h>
#include <mod/ModHandler.h>
#include <event/EventLoader.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <functional>

// Main DLL for loading mod DLLs
void mod_loader_entry() {
	

	// launch the game's internal console and hook into it
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOIN$", "r", stdin);
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);
	remove("SatisfactoryModLoader.log");
	

	log("Attached SatisfactoryModLoader to Satisfactory");

	// load up all of the configuration information
	readConfig();

	if (!loadConsole) {
		ShowWindow(GetConsoleWindow(), SW_HIDE);
	}
	
	// load mods
	// get path
	char p[MAX_PATH];
	GetModuleFileNameA(NULL, p, MAX_PATH);

	// load mods
	ModHandler modHandler;
	modHandler.load_mods(p);

	// log mod size
	size_t listSize = modHandler.Mods.size();
	log("Loaded " + std::to_string(listSize) + " mod" + (listSize > 1 ? "s" : ""));

	//display condensed form of mod information
	std::string modList = "[";
	for (Mod mod : modHandler.Mods) {
		modList.append(mod.name + "@" + mod.version + ", ");
	}

	if (listSize > 0) {
		log("Loaded mods: " + modList.substr(0, modList.length()-2) +"]");
	}
	
	// assign events
	EventLoader eventLoader;
	eventLoader.load_events(modHandler.Mods);

	// hook mods up and run their 'setup' functions
	for (Mod mod : modHandler.Mods) {
		eventLoader.subscribe_mod(mod);
	}

	log("SatisfactoryModLoader Initialization complete. Launching Satisfactory...");
}

//cleans up when the program is killed
void cleanup() {
	logFile.close();
}