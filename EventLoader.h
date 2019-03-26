#pragma once
#include "Connection.h"
#include "Dispatcher.h"
#include "Mod.h"
// events
#include "FoliagePickupEvent.h"

class EventLoader {
public:
	void load_events();
	void subscribe_mod(Mod mod);
	
	Dispatcher dispatcher;
private:
	void hook_event(const char* name, PVOID hook);
	void use_mod(const Event& event);
	const char* _module = "FactoryGame-Win64-Shipping.exe";
};

//FoliagePickupEvent foliagePickupEvent;