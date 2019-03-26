#include "stdafx.h"
#include "EventLoader.h"
#include "Utility.h"
#include "Reflection.h"
#include <detours.h>
#include <algorithm>

void EventLoader::load_events() {
	FoliagePickupEvent e;
	hook_event(e.name(), FoliagePickupEvent::use);
}

void EventLoader::subscribe_mod(Mod mod) {
	for (int i = 0; i < EventType::END; i++) {
		EventType event = (EventType)i;
		FARPROC func = get_function(mod.fileModule, "get_event");
		auto pointer = (PVOID(WINAPI*)(EventType))func;
		//auto rType = (void(WINAPI*)(void* args))pointer(event);
		auto rType = (void(WINAPI*)(Event&))pointer(event);
		// TODO: get arg list to send
		if (rType == NULL) {
			continue;
		}

		//dispatcher.subscribe(event, EventLoader::use_mod);
		log("Subscribed [" + std::to_string(event) + "] to " + mod.name);
	}
}

void EventLoader::hook_event(const char* name, PVOID hook) {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	PVOID func = DetourFindFunction(_module, name);
	if (!func) {
		log("Invalid function: ", false);
		log(name, true, false);
		return;
	}

	DetourAttach(&(PVOID&)func, hook);

	DetourTransactionCommit();
}

void EventLoader::use_mod(const Event& event) {

}