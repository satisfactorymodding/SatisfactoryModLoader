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
	for (Mod mod : mods) {
		auto pointer = (bool(WINAPI*)(EventType, std::vector<void*>&))get_function(mod.fileName, "run");
		if (!pointer(type, args)) {
			run = false;
		}
	}
	return run;
}