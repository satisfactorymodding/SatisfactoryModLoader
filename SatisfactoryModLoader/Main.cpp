// dllmain.cpp : Defines the entry point for the DLL application.
#include <stdafx.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <functional>
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
	remove("SatisfactoryModLoader.log");

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

	// log mod size
	size_t listSize = modHandler.Mods.size();
	log(LogType::Normal, "Loaded ", listSize, " mod", (listSize > 1 || listSize == 0 ? "s" : ""));

	//display condensed form of mod information
	std::string modList = "[";
	for (Mod mod : modHandler.Mods) {
		modList.append(mod.name + "@" + mod.version + ", ");
	}

	if (listSize > 0) {
		log(LogType::Normal, "Loaded mods: ", modList.substr(0, modList.length() - 2), "]");
	}

	// hook original functions
	EventLoader eventLoader(modHandler.Mods);
	eventLoader.hook_events();

	log(LogType::Normal, "SatisfactoryModLoader Initialization complete. Launching Satisfactory...");
}

//cleans up when the program is killed
void cleanup() {
	_logFile.close();
}

EXTERN_DLL_EXPORT void* request_data_other(EventType type) {
	switch (type) {
	case EventType::PlayerControllerBeginPlay:
		return localPlayerController;
	}

	return NULL;
}

EXTERN_DLL_EXPORT void request_run_event(EventType type, std::vector<void*>& data) {
	log(LogType::Normal, "request_run_event");

	long long module = 0x180000000;

	FARPROC function;

	switch (type) {
	case EventType::PlayerSuicide:
		function = get_function((HMODULE)module, "player_suicide");
		((void(WINAPI*)(void*))function)(data[0]);
		break;
	case EventType::GameGetPlayer:
		function = get_function((HMODULE)module, "game_get_player");
		((void*(WINAPI*)(void*, int))function)(data[0], 0);
		break;
	}
}