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
// - To find out what events you can use, check SatisfactoryModLoader/event/game.
void OnPreInitializeEvent() {
	log_mod("Mod Pre initialized!");
	//Add code which needs to be run when the mod starts here
}

// Called when leaves or sticks are picked up
void OnPlayerPickupFoliage(std::vector<void*>& args) {
	log_mod("Picked up foliage");
	log_mod(args.size());
}

// Called when the player takes damage
void OnPlayerTakenDamage(std::vector<void*>& args) {
	log_mod("Taken damage");
	float base = *(float*)args[0];
	*(float*)args[0] = base + 10.f;
}

EXTERN_DLL_EXPORT void setup() {
	OnPreInitializeEvent();
	dispatcher.subscribe(FoliagePickupEvent::descriptor, OnPlayerPickupFoliage);
	dispatcher.subscribe(TakeDamageEvent::descriptor, OnPlayerTakenDamage);
}

EXTERN_DLL_EXPORT std::vector<void*> run_event(const Event& event, std::vector<void*>& args) {
	dispatcher.post(event, args);
	return args;
}