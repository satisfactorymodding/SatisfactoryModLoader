#include "stdafx.h"
#include "ModInfo.h"
#include <string>

EXTERN_DLL_EXPORT void isMod() {}

// File providing info about the mod.
// Do not change the function names or the return values
EXTERN_DLL_EXPORT std::string ModName() {
	return "TestMod";
}

EXTERN_DLL_EXPORT std::string ModVersion() {
	return "1.0.0";
}

EXTERN_DLL_EXPORT std::string ModDescription() {
	return "A mod made for testing the mod loader.";
}

EXTERN_DLL_EXPORT std::string ModAuthors() {
	return "SuperCoder79, Nomnom";
}