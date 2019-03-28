#include "stdafx.h"

#include "event/EventLoader.h"
#include "mod/ModHandler.h"
#include "util/Utility.h"
#include "util/Config.h"
#include "util/Reflection.h"

#include <functional>
#include <iostream>
#include <string>
#include <Windows.h>

// Main DLL for loading mod DLLs
void mod_loader_entry() {
	// load up all of the configuration information
	// readConfig();

	// launch the game's internal console and hook into it
	if (loadConsole) {
		AllocConsole();
		FILE* fp;
		freopen_s(&fp, "CONOIN$", "r", stdin);
		freopen_s(&fp, "CONOUT$", "w", stdout);
		freopen_s(&fp, "CONOUT$", "w", stderr);
	}

	log("Attached SatisfactoryModLoader to Satisfactory");
	
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
	
	// assign events
	EventLoader eventLoader;
	eventLoader.load_events(modHandler.Mods);

	// hook mods up and run their 'setup' functions
	for (Mod mod : modHandler.Mods) {
		eventLoader.subscribe_mod(mod);
	}

	log("SatisfactoryModLoader Initialization complete. Launching Satisfactory...");
}