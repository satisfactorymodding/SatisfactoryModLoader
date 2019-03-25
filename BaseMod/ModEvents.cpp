#include "stdafx.h"
#include "modinfo.h"
#include "utility.h"
#include <iostream>
#include <map>

// Custom Events
// - Create events you want to hook into the game here
// - To find out when events are called, please check the Event enum.
void OnPickupFoliageTest(void* args) {
	log("Foliage Picked up!");
	std::cout << (&args)[0] << std::endl;
}

void OnPreInitialize(void* args) {
	log("Mod Pre initialized!");
}


// Utility
// - Register events you want to hook into the game here
EXTERN_DLL_EXPORT extern std::map<Event, FUNC> functions = {
	{ Event::OnPickupFoliage, OnPickupFoliageTest },
	{ Event::OnPreInit, OnPreInitialize }
};

// Don't edit
EXTERN_DLL_EXPORT FUNC get_event(Event event) {
	auto iterator = functions.find(event);
	if (iterator != functions.end()) {
		return (*iterator).second;
	}
	return NULL;
}