#pragma once
#include "Connection.h"
#include "Dispatcher.h"
#include "Mod.h"
#include <map>
#include <tuple>

class EventLoader {
public:
	void load_events(std::vector<Mod> mods);

	void subscribe_mod(Mod mod);
	
	Dispatcher dispatcher;
private:
	void hook_event(const Event& e, PVOID hook);

	const char* _module = "FactoryGame-Win64-Shipping.exe";
};

class OriginalFunction {
public:
	PVOID Function;
	PVOID ModFunction;
};

static std::map<EventType, OriginalFunction> originalFunctions;