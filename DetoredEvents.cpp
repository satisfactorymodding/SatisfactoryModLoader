#include "stdafx.h"
#include "DetoredEvents.h"
#include "DLLMain.h"
#include "timer.h"
#include "config.h"
#include <iostream>
#include <Windows.h>
#include <map>
#include <vector>
#include <detours.h>

void hook_player_begin_play(Event event, PVOID hook);

const char* module = "FactoryGame-Win64-Shipping.exe";

static std::map<Event, OriginalFunction> functionList = {
	//{ HookEvent::UpdateMainMenu, "UpdateMainMenu" }
	{Event::OnPickupFoliage, OriginalFunction { NULL, "UFGFoliageLibrary::CheckInventorySpaceAndGetStacks" }},
	{Event::OnPlayerBeginPlay, OriginalFunction { NULL, "APlayerController::BeginPlay" }}
};


int8_t UFGFoliageLibrary_CheckInventorySpaceAndGetStacks(void* character, void* meshComponent, void* out_validStacks) {
	if (debugOutput) {
		log("UFGFoliageLibrary::CheckInventorySpaceAndGetStacks");
	}

	// run mod functions
	run_event(Event::OnPickupFoliage);

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
	run_event(Event::OnPlayerBeginPlay);

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

	DetourAttach(&(PVOID&)onHook, hook);

	DetourTransactionCommit();

	if (functionList[event].Func == NULL) {
		functionList[event].Func = onHook;
		log("Assigned FUNC for event: ", false);
		log(functionList[event].Name, true, false);
	}

	//DetourRestoreAfterWith(); // might not need
	//DetourTransactionBegin();
	//DetourUpdateThread(GetCurrentThread());

	//// hooks
	//PVOID onHook = DetourFindFunction(module, functionList[event].Name);
	//if (!onHook) {
	//	log("Invalid function");
	//	return;
	//}
	//DetourAttach(&(PVOID&)onHook, hook);

	//if (functionList[event].Func == NULL) {
	//	functionList[event].Func = onHook;
	//	log("Assigned FUNC for event: " + std::to_string(event));
	//}

	//DetourTransactionCommit();
}