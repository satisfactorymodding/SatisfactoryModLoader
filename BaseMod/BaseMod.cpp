#include <stdafx.h>
#include <string>
#include <event/Event.h>
#include <event/game/PlayerEvents.h>
#include <util/Configuration.h>
#include "BaseMod.h"
#include "ModInfo.h"

/*

	[Tips]
	Pointers passed from the original function to the mod loader are not
		able to be used in a mod. They are fake pointers, so you need to
		send it back to the mod loader when you call a function from there

	Here is an example of getting a value from the args:
	float value							  : float f = *(float*)args[0];
	float pointer						  : float* fPtr = (float*)args[0];

	[Useful functions]
	get_mod_loader_function(functionName) - runs a modloader event by name
	dispatcher.subscribe(type, function)  - subscribes a function to an event
	GetAsyncKeyState(key)				  - checks a key press
	mod_log(modName, msg)				  - logs a message to the console

*/

/// config
Configuration config("BaseMod");
bool testValue;

void* player;

void killing_player() {
	if (player != NULL) {
		info_mod("BaseMod", "Attempting to kill the player");
		auto pointer = (void(WINAPI*)(void*))get_mod_loader_function("player_suicide");
		pointer(player);
	}
}

bool check_g_key(std::vector<void*>& args) {
	if (GetAsyncKeyState('G')) {
		info_mod("BaseMod", "G key pressed");
		killing_player();
	}
	return true;
}

bool getting_player(std::vector<void*>& args) {
	info_mod("BaseMod", "Got player");
	player = args[0];
	return true;
}

GLOBAL void setup() {
	// setup config file
	if (!config.exists()) {
		error("Config does not exist for mod. Creating one.");
		config.set("TestValue", true);
		config.save();
	}

	config.load();

	testValue = config.get<bool>("TestValue");
	warning("Test Value: ", testValue);

	// hook events
	dispatcher.subscribe(EventType::InputKey, check_g_key);
	dispatcher.subscribe(EventType::PlayerControllerBeginPlay, getting_player);
}

GLOBAL bool run(EventType type, std::vector<void*>& args) {
	return dispatcher.post(type, args);
}

GLOBAL void cleanup() {
	// do things
}