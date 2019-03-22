#include "stdafx.h"
#include "ModInfo.h"
#include <iostream>
#include <map>

// Events
// - Put events you want to hook into the game here

void TestTick() {
	printf("TestTick\n");
}

// Utility

EXTERN_DLL_EXPORT extern std::map<TickEvent, FUNC> functions = {
	{ TickEvent::Test, TestTick }
};

EXTERN_DLL_EXPORT FUNC GetTickEvent(TickEvent event) {
	auto iterator = functions.find(event);
	if (iterator != functions.end()) {
		return (*iterator).second;
	}
	return NULL;
}