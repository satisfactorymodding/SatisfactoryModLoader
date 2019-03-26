#include "stdafx.h"
#include "ModInfo.h"
#include "Utility.h"
#include "ModEvents.h"
#include <iostream>
#include <cstdint>

#include "FoliagePickupEvent.h"
#include "TakeDamageEvent.h"

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
	float dmg = 0;
	args[2] = &dmg;
	log_mod(*(float*)args[2]);
}

EXTERN_DLL_EXPORT void setup() {
	dispatcher.subscribe(FoliagePickupEvent::descriptor, OnPlayerPickupFoliage);
	dispatcher.subscribe(TakeDamageEvent::descriptor, OnPlayerTakenDamage);
}

EXTERN_DLL_EXPORT void run_event(const Event& event, std::vector<void*>& args) {
	dispatcher.post(event, args);
}