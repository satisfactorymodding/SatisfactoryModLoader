#include "stdafx.h"
#include "ModInfo.h"

GLOBAL std::string ModName = "BaseMod";
GLOBAL std::string ModVersion = "0.1";
GLOBAL std::string ModDescription = "Description";
GLOBAL std::string ModAuthors = "Nomnom, SuperCoder79";

GLOBAL void recieve_hooked_functions(std::map<EventType, PVOID> functions) {
	hookedFunctions = functions;
}