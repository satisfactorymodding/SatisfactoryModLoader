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
std::tuple<bool, O> get_function_value(HMODULE module, const char* procName);

template <typename O>
std::tuple<bool, O> get_field_value(HMODULE module, const char* procName);

FARPROC getFunction(HMODULE module, const char* procName);

void runEvent(Event event);

void run_pre_init();

void run_post_init();