#include <stdafx.h>
#include "ModInfo.h"

// File providing info about the mod.
// Do not change the function names or the return values
GLOBAL std::string ModName = "BaseMod";
GLOBAL std::string ModVersion = "1.0.0";
GLOBAL std::string ModDescription = "A base mod made for easy mod creation.";
GLOBAL std::string ModAuthors = "SuperCoder79, Nomnom";

GLOBAL void recieve_hooked_functions(std::map<EventType, PVOID> functions) {
	hookedFunctions = functions;
}