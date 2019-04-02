#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <mod/Mod.h>
#include <event/Event.h>
#include <detours.h>

#define GLOBAL extern "C" __declspec(dllexport)

static const char* gameModule = "FactoryGame-Win64-Shipping.exe";
static long long modLoaderModule = 0x180000000;

PVOID get_function(std::string module, const char* procName);
PVOID get_address_function(long long module, const char* procName);
PVOID get_mod_loader_function(const char* procName);
bool run_mods(std::vector<Mod> mods, EventType type, std::vector<void*>& args);

// gets a field's value
template <typename O>
bool get_field_value(HMODULE module, const char* procName, O& value) {
	FARPROC proc = GetProcAddress(module, procName);
	if (proc == NULL) {
		return false;
	}

	//typedef O(funcN);
	O* n1 = (O*)proc;
	value = *n1;
	return true;
}