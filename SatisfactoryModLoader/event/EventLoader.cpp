#include "stdafx.h"
#include "EventLoader.h"
#include <util/Utility.h>
#include <util/Reflection.h>
#include <mod/ModHandler.h>"
#include <detours.h>
#include <algorithm>

// events
#include <event/game/FoliagePickupEvent.h>
#include <event/game/InventoryHasAuthorityEvent.h>
#include <event/game/EnterChatMessageEvent.h>
#include <event/game/TakeDamageEvent.h>
#include <event/game/SuicideEvent.h>
#include <event/game/BeginPlayEvent.h>

// holds a cache of the global mod list
std::vector<Mod> _modList;

// hooks various events to their corresponding original functions
void EventLoader::load_events(std::vector<Mod> mods) {
	_modList = mods;

	FoliagePickupEvent e;
	hook_event(e, FoliagePickupEvent::use);

	/*InventoryHasAuthorityEvent e2;
	hook_event(e2, InventoryHasAuthorityEvent::use);*/

	TakeDamageEvent e3;
	hook_event(e3, TakeDamageEvent::use);

	EnterChatMessageEvent e4;
	hook_event(e4, EnterChatMessageEvent::use);

	SuicideEvent e5;
	hook_event(e5, SuicideEvent::use);

	BeginPlayEvent e6;
	hook_event(e6, BeginPlayEvent::use);
}

// run a mod's setup function
void EventLoader::subscribe_mod(Mod mod) {
	FARPROC func = get_function(mod.fileModule, "setup");
	auto pointer = (PVOID(WINAPI*)(void))func;
	pointer();
}

// run a mod's 'run_event' which runs all available functions of the given Event
std::vector<void*> hook_mod(const Event& e, std::vector<void*>& args) {
	std::vector<void*> returns = args;
	for (Mod mod : _modList) {
		FARPROC func = get_function(mod.fileModule, "run_event");
		auto pointer = (std::vector<void*>(WINAPI*)(const Event&, std::vector<void*>&))func;
		returns = pointer(e, returns);
	}
	return returns;
}

// hooks an event into an original function
void EventLoader::hook_event(const Event& e, PVOID hook) {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	// find the function by name
	PVOID func = DetourFindFunction(_module, e.name());
	if (!func) {
		log("Invalid function: ", false);
		log(e.name(), true, false);
		return;
	}

	// attach it, clearly
	DetourAttach(&(PVOID&)func, hook);

	DetourTransactionCommit();

	originalFunctions[e.type()] = OriginalFunction {
		func,
		hook_mod
	};
}