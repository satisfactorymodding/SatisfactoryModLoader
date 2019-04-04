#include "stdafx.h"
#include "ModInfo.h"

GLOBAL const std::string ModName = "BaseMod";
GLOBAL const std::string ModVersion = "0.2";
GLOBAL const std::string ModDescription = "Description";
GLOBAL const std::string ModAuthors = "Nomnom, SuperCoder79";

GLOBAL void recieve_hooked_functions(std::map<EventType, PVOID> functions) {
	hookedFunctions = functions;
}