#include "stdafx.h"
#include "ModInfo.h"
#include "Utility.h"
#include <iostream>
#include <map>
#include <cstdint>

// Custom Events
// - Create events you want to hook into the game here
// - To find out when events are called, please check the Event enum.
void OnPreInitializeEvent(void* args) {
	log("Mod Pre initialized!");
}

// Utility
// - Register events you want to hook into the game here
EXTERN_DLL_EXPORT extern std::map<Event, FUNC> functions = {
	{ Event::OnPreInit, OnPreInitializeEvent }
};

// Don't edit
EXTERN_DLL_EXPORT FUNC get_event(Event event) {
	auto iterator = functions.find(event);
	if (iterator != functions.end()) {
		return (*iterator).second;
	}
	return NULL;
}