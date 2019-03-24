#pragma once
#include <vector>
#include <map>
#include <detours.h>

enum HookEvent {
	OnPickupFoliage,
};

class Hook {
public:
	HookEvent Event;
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

PVOID hook_event(HookEvent event, PVOID hook);