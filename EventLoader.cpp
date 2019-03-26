#include "stdafx.h"
#include "EventLoader.h"
#include "Utility.h"
#include "Reflection.h"
#include "ModHandler.h"
#include <detours.h>
#include <algorithm>

// events
#include "FoliagePickupEvent.h"
#include "InventoryHasAuthorityEvent.h"
#include "TakeDamageEvent.h"

std::vector<Mod> _modList;

void EventLoader::load_events(std::vector<Mod> mods) {
	_modList = mods;

	FoliagePickupEvent e;
	hook_event(e, FoliagePickupEvent::use);

	/*InventoryHasAuthorityEvent e2;
	hook_event(e2, InventoryHasAuthorityEvent::use);*/

	TakeDamageEvent e3;
	hook_event(e3, TakeDamageEvent::use);
}

void EventLoader::subscribe_mod(Mod mod) {
	FARPROC func = get_function(mod.fileModule, "setup");
	auto pointer = (PVOID(WINAPI*)(void))func;
	pointer();
}

void hook_mod(const Event& e, std::vector<void*>& args) {
	for (Mod mod : _modList) {
		FARPROC func = get_function(mod.fileModule, "run_event");
		auto pointer = (void(WINAPI*)(const Event&, std::vector<void*>&))func;
		pointer(e, args);
	}
}

void EventLoader::hook_event(const Event& e, PVOID hook) {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	PVOID func = DetourFindFunction(_module, e.name());
	if (!func) {
		log("Invalid function: ", false);
		log(e.name(), true, false);
		return;
	}

	DetourAttach(&(PVOID&)func, hook);

	DetourTransactionCommit();

	originalFunctions[e.type()] = OriginalFunction {
		func,
		hook_mod
	};
}