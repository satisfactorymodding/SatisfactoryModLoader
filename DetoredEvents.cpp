#include "stdafx.h"
#include "DetoredEvents.h"
#include "DLLMain.h"
#include <iostream>
#include <Windows.h>
#include <map>
#include <vector>
#include <detours.h>

const char* module = "FactoryGame-Win64-Shipping.exe";

std::map<Event, Hook> hookList = {};

static std::map<Event, OriginalFunction> functionList = {
	//{ HookEvent::UpdateMainMenu, "UpdateMainMenu" }
	{Event::OnPickupFoliage, OriginalFunction{ NULL, "UFGFoliageLibrary::CheckInventorySpaceAndGetStacks" }}
};

void UFGFoliageLibrary_CheckInventorySpaceAndGetStacks() {
	//log("UFGFoliageLibrary::CheckInventorySpaceAndGetStacks");

	// run mod functions
	run_event(Event::OnPickupFoliage);

	// TODO: run original function
}

// so far confirmed to work with function names
//void add_event(Event event, PVOID hook) {
//	auto iterator = hookList.find(event);
//	if (iterator != hookList.end()) {
//		Hook h = (*iterator).second;
//		h.HookFunctions.push_back(hook);
//		log("Added new hook to " + std::to_string(event));
//		return;
//	}
//
//	hookList.insert(std::pair<Event, Hook>(
//		event, 
//		Hook {
//			event,
//			functionList[event].Name,
//			std::vector<PVOID>{ hook }
//	}));
//
//	log("(New Event Created) Added new hook to " + std::to_string(event));
//}

PVOID hook_event (Event event, PVOID hook) {
	DetourRestoreAfterWith(); // might not need
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	// hooks
	PVOID onHook = DetourFindFunction(module, functionList[event].Name);
	if (!onHook) {
		log("Invalid function");
		return NULL;
	}
	DetourAttach(&(PVOID&)onHook, hook);

	if (functionList[event].Func == NULL) {
		functionList[event].Func = onHook;
	}

	DetourTransactionCommit();

	//add_event(event, hook);

	return onHook;
}