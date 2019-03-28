#pragma once
#include <Windows.h>
#include <string>

FARPROC get_function(HMODULE module, const char* procName);

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