#include "stdafx.h"
#include "ModInfo.h"
#include "Utility.h"
#include "ModEvents.h"
#include <iostream>
#include <cstdint>

#include <event/game/FoliagePickupEvent.h>
#include <event/game/TakeDamageEvent.h>

// Custom Events
// - Create events you want to hook into the game here
// - To find out when events are called, please check the Event enum.
void OnPreInitializeEvent(std::vector<void*>& args) {
	log_mod("Mod Pre initialized!");
}

void OnPlayerPickupFoliage(std::vector<void*>& args) {
	log_mod("Picked up foliage");
	log_mod(args.size());
}

void OnPlayerTakenDamage(std::vector<void*>& args) {
	log_mod("Taken damage");
	float base = *(float*)args[2];
	*(float*)args[2] = base + 10.f;
}

EXTERN_DLL_EXPORT void setup() {
	dispatcher.subscribe(FoliagePickupEvent::descriptor, OnPlayerPickupFoliage);
	dispatcher.subscribe(TakeDamageEvent::descriptor, OnPlayerTakenDamage);
}

EXTERN_DLL_EXPORT std::vector<void*> run_event(const Event& event, std::vector<void*>& args) {
	dispatcher.post(event, args);
	return args;
}