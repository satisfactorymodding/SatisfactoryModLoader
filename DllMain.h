#pragma once
#include <tuple>
enum Event {
	None, Test
};
void ModLoaderEntry();

typedef void(*FUNC)();

template <typename O>
std::tuple<bool, O> getFunctionValue(HMODULE module, const char* procName);

template <typename O>
std::tuple<bool, O> getFieldValue(HMODULE module, const char* procName);

FARPROC getFunction(HMODULE module, const char* procName);

void runEvent(Event event);

void runPreInit();

void runPostInit();