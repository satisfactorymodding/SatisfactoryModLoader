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

void run_mods(std::vector<Mod> mods, EventType type, std::vector<void*>& args) {
	for (Mod mod : mods) {
		auto pointer = (void(WINAPI*)(EventType, std::vector<void*>&))get_function(mod.name, "run");
		pointer(type, args);
	}
}