#include <stdafx.h>
#include <string>
#include <event/Event.h>
#include <event/game/PlayerEvents.h>
#include "ModEvents.h"
#include "ModInfo.h"

void* playerController;

void get_player_controller(std::vector<void*>& args) {
	playerController = args[0];
	log(LogType::Normal, *(float*)args[1]);
}

void send_test_message(std::vector<void*>& args) {
	log(LogType::Normal, "Got Test Message");
	auto pointer = (void(WINAPI*)(void*, std::string))get_address_function(modLoaderModule, "player_send_message");
	if (pointer == NULL) {
		log(LogType::Error, "Invalid pointer");
		return;
	}
	*(bool*)args[0] = false;
	pointer(playerController, "Test Event");
}

void setup() {
	dispatcher.subscribe(EventType::PlayerControllerBeginPlay, get_player_controller);
	dispatcher.subscribe(EventType::PlayerSentMessage, send_test_message);

	log(LogType::Normal, "Setup completed for ", ModName);
}

void run(EventType type, std::vector<void*>& args) {
	dispatcher.post(type, args);
}