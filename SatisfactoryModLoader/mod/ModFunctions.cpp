#include <stdafx.h>
#include "ModFunctions.h"
#include <SatisfactoryModLoader.h>
#include <memory>

namespace SML {

	// registers a command to the mod handler
	SML_API void registerCommand(std::string name, PVOID func) {
		Registry r = {
			name,
			func
		};
		modHandler.commandRegistry.push_back(r);
	}

	// registers an API function to the mod handler
	SML_API void registerAPIFunction(std::string name, PVOID func) {
		for (Registry reg : modHandler.APIRegistry) {
			if (reg.name == name) {
				std::string msg = "Duplicate API function " + name + " registered!\nPress Ok to exit.";
				MessageBoxA(NULL, msg.c_str(), "SatisfactoryModLoader Fatal Error", MB_ICONERROR);
				abort();
			}
		}
		Registry r = {
			name,
			func
		};
		modHandler.APIRegistry.push_back(r);
	}

	// gets an API function from the mod handler
	SML_API PVOID getAPIFunction(std::string name) {
		bool found = false;
		PVOID func = NULL;
		for (Registry reg : modHandler.APIRegistry) {
			if (reg.name == name) {
				func = reg.func;
				found = true;
			}
		}
		if (!found) {
			std::string msg = "Requested API function " + name + " not found!\nMake sure that the mod that provides this function is installed or added as a dependency to your mod.\nPress Ok to exit.";
			MessageBoxA(NULL, msg.c_str(), "SatisfactoryModLoader Fatal Error", MB_ICONERROR);
			abort();
		}
		return func;
	}

	// checks if a mod is loaded through mod name
	SML_API bool isModLoaded(std::string name) {
		bool found = false;
		for (auto&& mod : modHandler.mods) {
			if (mod->info.name == name) {
				found = true;
				break;
			}
		}
		return found;
	}
}