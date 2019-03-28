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
#include <functional>

// Main DLL for loading mod DLLs
void freeObserver(const Event& event) {
	std::cout << __FUNCSIG__ << ": DemoEvent" << std::endl;
}

void mod_loader_entry() {

	//readConfig();

	// Allocate console
	if (loadConsole) {
		AllocConsole();
		FILE* fp;
		freopen_s(&fp, "CONOIN$", "r", stdin);
		freopen_s(&fp, "CONOUT$", "w", stdout);
		freopen_s(&fp, "CONOUT$", "w", stderr);
	}
	log("Attached SatisfactoryModLoader to Satisfactory");
	
	// load mods
	char p[MAX_PATH];
	GetModuleFileNameA(NULL, p, MAX_PATH);

	ModHandler modHandler;
	modHandler.load_mods(p);

	// log mod size
	size_t listSize = modHandler.Mods.size();
	log("Loaded " + std::to_string(listSize) + " mod" + (listSize > 1 ? "s" : ""));
	
	// assign events
	EventLoader eventLoader;
	eventLoader.load_events(modHandler.Mods);

	for (Mod mod : modHandler.Mods) {
		eventLoader.subscribe_mod(mod);
	}

	log("SatisfactoryModLoader Initialization complete. Launching Satisfactory...");
}

//void run_event(Event event, void* args) {
//	for (Mod mod : modList) {
//		FARPROC func = get_function(mod.fileModule, "get_event");
//		auto pointer = (PVOID(WINAPI*)(Event))func;
//		auto rType = (void(WINAPI*)(void* args))pointer(event);
//		rType(args);
//	}
//}
//
//void run_pre_init() {
//	log("Pre Initializing all mods", true, true);
//	run_event(Event::OnPreInit, NULL);
//	return;
//}
//
//void run_post_init() {
//	log("Post Initializing!", true, true, "POSTINIT");
//	return;
//}