#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <mod/Mod.h>

#define EXTERN_DLL_EXPORT extern "C" __declspec(dllexport)

FARPROC get_function(HMODULE module, const char* procName);

void get_mod_values(std::vector<Mod> mods, const char* procName, std::vector<void*>& value);

// gets a function's value
template <typename O>
bool get_function_value(HMODULE module, const char* procName, O& value) {
	FARPROC proc = GetProcAddress(module, procName);
	if (!proc) {
		return false;
	}

	typedef O TFUNC();
	TFUNC* f = (TFUNC*)proc;
	value = f();
	return true;
}

// gets a field's value
template <typename O>
bool get_field_value(HMODULE module, const char* procName, O& value) {
	FARPROC proc = get_function(module, procName);
	if (!proc) {
		return false;
	}

	typedef O(funcN);
	funcN* n1 = (funcN*)proc;
	value = *n1;
	return true;
}