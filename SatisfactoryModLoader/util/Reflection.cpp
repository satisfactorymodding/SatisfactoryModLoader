#include "stdafx.h"
#include "Reflection.h"
#include <string>

// gets a function from a module by name
FARPROC get_function(HMODULE module, const char* procName) {
	FARPROC proc = GetProcAddress(module, procName);
	if (!proc) {
		return NULL;
	}

	return proc;
}