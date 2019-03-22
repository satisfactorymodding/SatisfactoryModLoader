#include "stdafx.h"
#include <string>

//File providing info about the mod.
#define EXTERN_DLL_EXPORT extern "C" __declspec(dllexport)
EXTERN_DLL_EXPORT void isMod() {}

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