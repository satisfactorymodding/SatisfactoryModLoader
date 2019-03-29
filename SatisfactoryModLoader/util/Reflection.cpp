#include <stdafx.h>
#include <string>
#include <util/Utility.h>
#include "Reflection.h";

// gets a function from a module by name
FARPROC get_function(HMODULE module, const char* procName) {
	FARPROC proc = GetProcAddress(module, procName);
	if (!proc) {
		return NULL;
	}

	return proc;
}

void get_mod_values(std::vector<Mod> mods, const char* procName, std::vector<void*>& value) {
	for (Mod mod : mods) {
		//log(LogType::Normal, "Checking Mod: ", mod.name);
		auto proc = GetProcAddress(mod.fileModule, procName);
		if (!proc) {
			//log(LogType::Normal, procName, " not found for mod: ", mod.name);
			continue;
		}

		//log(LogType::Normal, procName, " was found for mod: ", mod.name);
		auto pointer = (void(WINAPI*)(std::vector<void*>&))proc;
		pointer(value);
	}
}