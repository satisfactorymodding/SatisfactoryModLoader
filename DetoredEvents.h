#pragma once
#include "dllmain.h"
#include <vector>
#include <map>
#include <detours.h>

class OriginalFunction {
public:
	//registerFunc RegisterFunc;
	PVOID Func;
	const char* Name;
};

int8_t UFGFoliageLibrary_CheckInventorySpaceAndGetStacks(void* character, void* meshComponent, void* out_validStacks);

void APlayerController_BeginPlay();

void hook_event(Event event, PVOID hook);