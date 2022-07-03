#include <stdafx.h>
#include <detours.h>
#include <util/Utility.h>
#include <event/game/EtcEvents.h>
#include <event/game/GlobalEvents.h>
#include <event/game/UiEvents.h>
#include "EventLoader.h"
#include "FunctionHolder.h"

EventLoader::EventLoader(std::vector<Mod> mods) {
	modList = mods;
}

void EventLoader::hook_events() {
	// ui events
	hook_event(u_button_pressed, EventType::UButtonPressed, "UButton::IsPressed");
	hook_event(u_check_box_pressed, EventType::UCheckBoxPressed, "UCheckBox::IsPressed");
	// global events
	hook_event(game_instance_get_world, EventType::GameInstanceGetWorld, "UGameInstance::GetWorld");

	// non-hook events
	insert_event(EventType::ActorGetWorld, "AActor::GetWorld");
}

// hooks an event into an original function
void EventLoader::hook_event(PVOID hook, EventType type, const char* function) {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	// find the function by name
	PVOID func = DetourFindFunction(gameModule, function);
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

void EventLoader::insert_event(EventType type, const char* function) {
	hookedFunctions.insert(std::pair<EventType, PVOID>(type, DetourFindFunction(gameModule, function)));
}