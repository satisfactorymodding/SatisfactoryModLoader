#include <stdafx.h>
#include <string>
#include <util/Utility.h>
#include "Reflection.h";

PVOID get_function(std::string module, const char* procName) {
	return DetourFindFunction((LPCSTR)&(module), procName);
}

PVOID get_address_function(long long module, const char* procName) {
	return GetProcAddress((HMODULE)module, procName);
}

PVOID get_mod_loader_function(const char* procName) {
	return GetProcAddress((HMODULE)modLoaderModule, procName);
}

bool run_mods(std::vector<Mod> mods, EventType type, std::vector<void*>& args) {
	bool run = true;
	//runs the function from each mod
	for (Mod mod : mods) {
		try {
			auto pointer = (bool(WINAPI*)(EventType, std::vector<void*>&))get_function(mod.fileName, "run");
			if (!pointer(type, args)) {
				run = false;
			}
		} catch(std::exception& e) {
			//if an error is caught in the process of running the function, throw a message to the user and end the program before the crash reporter client can open
			std::string msg = "Fatal Exception cought from " + mod.name + "!\nMore detailed information:\n" + e.what() + "\n\nPlease contact " + mod.name + "'s authors (" + mod.authors + ") to resolve this issue.\nPress Ok to close Satisfactory.";
			error("Fatal Exception cought from " + mod.name + "! More detailed information: " + e.what() + " Please contact " + mod.name + "'s authors (" + mod.authors + ") to resolve this issue.");
			MessageBoxA(NULL, msg.c_str(), "SatisfactoryModLoader Fatal Exception", MB_ICONERROR);
			abort();
		}
	}
	return run;
}