#include <stdafx.h>
#include <string>
#include <event/Event.h>
#include <event/game/PlayerEvents.h>
#include "BaseMod.h"
#include "ModInfo.h"

void setup() {
	mod_log(ModName, "Setup completed for ", ModName);
}

void run(EventType type, std::vector<void*>& args) {
	dispatcher.post(type, args);
}