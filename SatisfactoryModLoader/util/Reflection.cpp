#include <stdafx.h>
#include <string>
#include <util/Utility.h>
#include "Reflection.h";

// gets a function from a module by name
//FARPROC get_function(HMODULE module, const char* procName) {
//	FARPROC proc = GetProcAddress(module, procName);
//	if (!proc) {
//		return NULL;
//	}
//
//	return proc;
//}

PVOID get_function(std::string module, const char* procName) {
	return DetourFindFunction((LPCSTR)&(module), procName);
}

PVOID get_address_function(long long module, const char* procName) {
	return GetProcAddress((HMODULE)module, procName);
}

PVOID get_dll_function(std::string module, const char* procName) {
	return get_function(module + ".dll", procName);
}

void run_mods(std::vector<Mod> mods, EventType type, std::vector<void*>& args) {
	for (Mod mod : mods) {
		auto pointer = (void(WINAPI*)(EventType, std::vector<void*>&))get_dll_function(mod.name, "run");
		pointer(type, args);
	}
}