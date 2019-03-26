#include "stdafx.h"
#include "DetoredEvents.h"
#include "DLLMain.h"
#include <iostream>
#include <Windows.h>
#include <map>
#include <vector>
#include <detours.h>

const char* module = "FactoryGame-Win64-Shipping.exe";

// EVENTS

// (AFGCharacterPlayer character, UHierarchicalInstancedStaticMeshComponent meshComponent, TArray<FInventoryStack,FDefaultAllocator> out_validStacks)
int8_t UFGFoliageLibrary_CheckInventorySpaceAndGetStacks(void* character, void* meshComponent, void* out_validStacks) {
	log("UFGFoliageLibrary::CheckInventorySpaceAndGetStacks");

	std::cout << character << std::endl;

	// run mod functions
	void* data[] = {
		character,
		meshComponent,
		out_validStacks
	};

	run_event(Event::OnPickupFoliage, data);

	// run original function
	auto pointer = (int8_t(WINAPI*)(VOID*, VOID*, VOID*))functionList[Event::OnPickupFoliage].Func;
	return pointer(character, meshComponent, out_validStacks);
}

// (void)
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

// (AActor damagedActor, FLOAT damageAmount, UDamageType damageType, AController instigatedBy, AController instigatedBy, AActor damageCauser, AActor damageCauser)
void UFGHealthComponent_TakeDamage(void* healthComponent, void* actor, FLOAT damageAmount, void* damageType, void* instigatedByA, void* instigatedByB, void* damageCauserA, void* damageCauserB) {
	log("UFGHealthComponent::TakeDamage");

	// run mod functions
	void* data[] = {
		healthComponent,
		actor,
		damageAmount,
		damageType,
		instigatedByA,
		instigatedByB,
		damageCauserA,
		damageCauserB
	};

	run_event(Event::OnPlayerTakeDamage, data);

	// run original function
	auto pointer = (void(WINAPI*)(VOID*, VOID*, FLOAT, VOID*, VOID*, VOID*, VOID*, VOID*))functionList[Event::OnPlayerTakeDamage].Func;
	pointer(healthComponent, actor, damageAmount, damageType, instigatedByA, instigatedByB, damageCauserA, damageCauserB);
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
		log("Assigned event [", false);
		log(functionList[event].Name, false, false);
		log("]", true, false);
	}
}