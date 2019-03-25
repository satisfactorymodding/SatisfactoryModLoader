#include "stdafx.h"
#include "Reflection.h"
#include <string>

template <typename O>
bool get_function_value(HMODULE module, const char* procName, O& value) {
	FARPROC proc = GetProcAddress(module, procName);
	if (!proc) {
		return false;
	}

	auto f = (O(WINAPI*)())proc;

	value = (O)f();
	return true;
}

FARPROC get_function(HMODULE module, const char* procName) {
	FARPROC proc = GetProcAddress(module, procName);
	if (!proc) {
		return NULL;
	}

	return proc;
}

template <typename O>
bool get_field_value(HMODULE module, const char* procName, O& value) {
	FARPROC proc = get_function(module, procName);
	if (!proc) {
		return false;
	}

	auto n1 = (O(WINAPI*))proc;
	value = (O)n1;
	return true;
}