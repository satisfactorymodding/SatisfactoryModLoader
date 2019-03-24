#include "stdafx.h"
#include "DetoredEvents.h"
#include "DLLMain.h"
#include <iostream>
#include <Windows.h>
#include <map>
#include <vector>
#include <detours.h>

const char* Module = "FactoryGame-Win64-Shipping.exe";

std::map<HookEvent, Hook> HookList = {};

static std::map<HookEvent, OriginalFunction> FunctionList = {
	//{ HookEvent::UpdateMainMenu, "UpdateMainMenu" }
	{HookEvent::OnPickupFoliage, OriginalFunction{ NULL, "UFGFoliageLibrary::CheckInventorySpaceAndGetStacks" }}
};

void UFGFoliageLibrary_CheckInventorySpaceAndGetStacks() {
	log("UFGFoliageLibrary::CheckInventorySpaceAndGetStacks");
	// TODO: run original function
}

// so far confirmed to work with function names
void add_event(HookEvent event, PVOID hook) {
	auto iterator = HookList.find(event);
	if (iterator != HookList.end()) {
		Hook h = (*iterator).second;
		h.HookFunctions.push_back(hook);
		log("Added new hook to " + std::to_string(event));
		return;
	}

	HookList.insert(std::pair<HookEvent, Hook>(
		event, 
		Hook {
			event,
			FunctionList[event].Name,
			std::vector<PVOID>{ hook }
	}));

	log("(New Event Created) Added new hook to " + std::to_string(event));
}

PVOID hook_event (HookEvent event, PVOID hook) {
	DetourRestoreAfterWith(); // might not need
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	// hooks
	PVOID onHook = DetourFindFunction(Module, FunctionList[event].Name);
	if (!onHook) {
		log("Invalid function");
		return NULL;
	}
	DetourAttach(&(PVOID&)onHook, hook);

	if (FunctionList[event].Func == NULL) {
		FunctionList[event].Func = onHook;
	}

	DetourTransactionCommit();

	add_event(event, hook);

	return onHook;
}