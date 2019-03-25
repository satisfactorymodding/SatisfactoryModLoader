#pragma once
#include <Windows.h>
#include <string>

template <typename O>
bool get_function_value(HMODULE module, const char* procName, O& value);

template <typename O>
bool get_field_value(HMODULE module, const char* procName, O& value);

FARPROC get_function(HMODULE module, const char* procName);