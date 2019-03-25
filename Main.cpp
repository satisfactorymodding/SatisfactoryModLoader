// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "Utility.h"
#include "Config.h"
#include "Reflection.h"
#include "ModHandler.h"
#include "Connection.h"
#include "Dispatcher.h"
#include "Events.h"
#include <string>
#include <iostream>
#include <Windows.h>
#include <functional>

// Main DLL for loading mod DLLs
void freeObserver(const Event& event) {
	if (event.type() == DemoEvent::descriptor) {
		std::cout << __FUNCSIG__ << ": DemoEvent" << std::endl;
	}
}

void mod_loader_entry() {

	// Allocate console
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOIN$", "r", stdin);
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);

	log("Attached SatisfactoryModLoader to Satisfactory");

	readConfig();
	
	// load mods
	char p[MAX_PATH];
	GetModuleFileNameA(NULL, p, MAX_PATH);

	ModHandler modHandler;
	modHandler.load_mods(p);

	// log mod size
	size_t listSize = modHandler.Mods.size();
	log("Loaded " + std::to_string(listSize) + " mod" + (listSize > 1 ? "" : "s"));
	
	// assign events
	Dispatcher dispatcher;

	FoliagePickupEvent e;
	auto onFoliagePickup = dispatcher.subscribe(FoliagePickupEvent::descriptor, freeObserver);

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