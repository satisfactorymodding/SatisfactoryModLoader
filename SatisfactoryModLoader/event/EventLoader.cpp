#include <stdafx.h>
#include <detours.h>
#include <util/Utility.h>
#include <event/game/PlayerEvents.h>
#include <event/game/EtcEvents.h>
#include <event/game/GlobalEvents.h>
#include "EventLoader.h";
#include "FunctionHolder.h"

EventLoader::EventLoader(std::vector<Mod> mods) {
	modList = mods;
}

void EventLoader::hook_events() {
	// player events
	hook_event(player_begin_play, EventType::PlayerBeginPlay, "AFGPlayerController::BeginPlay");
	hook_event(player_suicide, EventType::PlayerSuicide, "AFGPlayerController::Suicide");
	hook_event(player_sent_message, EventType::PlayerSentMessage, "AFGPlayerController::EnterChatMessage");
	// global events
	hook_event(game_instance_recieve_init, EventType::GameInstanceRecieveInit, "UGameInstance::ReceiveInit");
	hook_event(game_instance_get_world, EventType::GameInstanceGetWorld, "UGameInstance::GetWorld");
}

// hooks an event into an original function
void EventLoader::hook_event(PVOID hook, EventType type, const char* function) {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	// find the function by name
	PVOID func = DetourFindFunction("FactoryGame-Win64-Shipping.exe", function);
	if (!func) {
		log(LogType::Error, "Invalid function: ", function);
		return;
	}

	log(LogType::Normal, "Hooked function: ", function);

	// attach it, clearly
	DetourAttach(&(PVOID&)func, hook);
	DetourTransactionCommit();

	hookedFunctions.insert(std::pair<EventType, PVOID>(type, func));
}