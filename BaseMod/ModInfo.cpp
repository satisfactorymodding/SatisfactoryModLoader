#include "stdafx.h"
#include "ModInfo.h"
GLOBAL const std::string ModName = "BaseMod"; // Name of the mod. Can contain alphanumeric characters, spaces, and underscores.
GLOBAL const std::string ModVersion = "0.2"; // Version of the mod
GLOBAL const std::string ModDescription = "A basic mod created to showcase SML's functionality."; // Short description of the mod
GLOBAL const std::string ModAuthors = "Nomnom, SuperCoder79"; //Authors of the mod
// Mods that need to be loaded before this mod. If a mod is an optional dependency, prefix the mod name with an asterisk.
// Example: {"ModOne", "*ModTwo"};
GLOBAL const std::vector<std::string> ModDependencies = {

};

GLOBAL void recieve_hooked_functions(std::map<EventType, PVOID> functions) {
	hookedFunctions = functions;
}