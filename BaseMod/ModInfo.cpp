#include "stdafx.h"
#include <string>

//File providing info about the mod.
#define EXTERN_DLL_EXPORT extern "C" __declspec(dllexport)
EXTERN_DLL_EXPORT void isMod() {}

// Change the return values but do not change the function names!

std::string ModName() {
	return "TestMod";
}

std::string ModVersion() {
	return "1.0.0";
}

std::string ModDescription() {
	return "A mod made for testing the mod loader.";
}

std::string ModAuthor() {
	return "SuperCoder79";
}