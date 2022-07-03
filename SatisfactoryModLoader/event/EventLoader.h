#pragma once
#include <vector>
#include <mod/Mod.h>
#include <event/Event.h>

class EventLoader {
public:
	EventLoader(std::vector<Mod> mods);

	void hook_events();
private:
	void hook_event(PVOID hook, EventType type, const char* function);
	void insert_event(EventType type, const char* function);
};