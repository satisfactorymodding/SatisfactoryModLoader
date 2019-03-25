#pragma once
#include "dllmain.h"
#include <vector>
#include <map>
#include <detours.h>

class Hook {
public:
	Event Event;
	const char* FunctionName;
	std::vector<PVOID> HookFunctions;
};

class OriginalFunction {
public:
	PVOID Func;
	const char* Name;
};

typedef void(*voidFunc)();

void UFGFoliageLibrary_CheckInventorySpaceAndGetStacks();

PVOID hook_event(Event event, PVOID hook);