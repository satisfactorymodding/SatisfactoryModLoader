#include <stdafx.h>
#include "ModInfo.h"

// File providing info about the mod.
// Do not change the function names or the return values
EXTERN_DLL_EXPORT std::string ModName = "BaseMod";
EXTERN_DLL_EXPORT std::string ModVersion = "1.0.0";
EXTERN_DLL_EXPORT std::string ModDescription = "A base mod made for easy mod creation.";
EXTERN_DLL_EXPORT std::string ModAuthors = "SuperCoder79, Nomnom";

EXTERN_DLL_EXPORT void recieve_hooked_functions(std::map<EventType, PVOID> functions) {
	hookedFunctions = functions;
}