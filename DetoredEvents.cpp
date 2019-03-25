#include "stdafx.h"
#include "DetoredEvents.h"
#include "DLLMain.h"
#include <iostream>
#include <Windows.h>
#include <map>
#include <vector>
#include <detours.h>

const char* module = "FactoryGame-Win64-Shipping.exe";

int8_t UFGFoliageLibrary_CheckInventorySpaceAndGetStacks(void* character, void* meshComponent, void* out_validStacks) {
	log("UFGFoliageLibrary::CheckInventorySpaceAndGetStacks");

	std::cout << character << std::endl;

	// run mod functions
	void* data[] = {
		character
	};

	run_event(Event::OnPickupFoliage, data);

	// TODO: run original function
	auto pointer = (int8_t(WINAPI*)(VOID*, VOID*, VOID*))functionList[Event::OnPickupFoliage].Func;
	return pointer(character, meshComponent, out_validStacks);
}

void APlayerController_BeginPlay() {
	/*if (!functionList[Event::OnPlayerBeginPlay].Usable) {
		return;
	}*/

	log("APlayerController::BeginPlay");

	// run mod functions
	run_event(Event::OnPlayerBeginPlay, NULL);

	// run original function
	auto pointer = (void(WINAPI*)())functionList[Event::OnPlayerBeginPlay].Func;
	pointer();

	/*Timer timer = Timer();
	timer.setTimeout([&]() {
		functionList[Event::OnPlayerBeginPlay].Usable = true;
	}, 1000);*/
}

void hook_event (Event event, PVOID hook) {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	PVOID onHook = DetourFindFunction(module, functionList[event].Name);
	if (!onHook) {
		log("Invalid function");
		return;
	}

	long address = DetourAttach(&(PVOID&)onHook, hook);

	DetourTransactionCommit();

	if (functionList[event].Func == NULL) {
		functionList[event].Func = onHook;
		log("Assigned event [", false);
		log(functionList[event].Name, false, false);
		log("]", true, false);
	}
}