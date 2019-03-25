#include "stdafx.h"
#include "modinfo.h"
#include <iostream>
#include <map>

// Events
// - Create events you want to hook into the game here
void OnPickupFoliageTest() {
	printf("OnPickupFoliageTest\n");
}

// Utility
// - Register events you want to hook into the game here
EXTERN_DLL_EXPORT extern std::map<Event, FUNC> functions = {
	{ Event::OnPickupFoliage, OnPickupFoliageTest }
};

// Don't edit
EXTERN_DLL_EXPORT FUNC GetTickEvent(Event event) {
	auto iterator = functions.find(event);
	if (iterator != functions.end()) {
		return (*iterator).second;
	}
	return NULL;
}