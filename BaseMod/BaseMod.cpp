#include <stdafx.h>
#include <string>
#include <event/Event.h>
#include <event/game/PlayerEvents.h>
#include "BaseMod.h"
#include "ModInfo.h"

GLOBAL void setup() {
	log(LogType::Normal, "Setup completed for ", ModName);
}

GLOBAL void run(EventType type, std::vector<void*>& args) {
	dispatcher.post(type, args);
}