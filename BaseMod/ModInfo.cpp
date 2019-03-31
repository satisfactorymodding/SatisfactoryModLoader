#include <stdafx.h>
#include <string>
#include "ModInfo.h"

// File providing info about the mod.
// Do not change the function names or the return values

GLOBAL const std::string ModName = "BaseMod";
GLOBAL const std::string ModVersion = "1.0.0";
GLOBAL const std::string ModDescription = "A base mod made for easy mod creation.";
GLOBAL const std::string ModAuthors = "SuperCoder79, Nomnom";

GLOBAL void recieve_hooked_functions(std::map<EventType, PVOID> functions) {
	hookedFunctions = functions;
}