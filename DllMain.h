#pragma once
#include <tuple>
#include <string>
enum Event {
	None, Test
};

void ModLoaderEntry();

typedef void(*FUNC)();

void FGlobalTabmanager_UpdateMainMenu();

template<typename T>
void log(T msg, bool endLine = true, bool showHeader = true);

template <typename O>
std::tuple<bool, O> getFunctionValue(HMODULE module, const char* procName);

template <typename O>
std::tuple<bool, O> getFieldValue(HMODULE module, const char* procName);

FARPROC getFunction(HMODULE module, const char* procName);

void runEvent(Event event);

void runPreInit();

void runPostInit();