#pragma once
enum Event {
	None, Test
};

typedef void(*FUNC)();

template <typename O>
std::tuple<bool, O> get_function_value(HMODULE module, const char* procName);

template <typename O>
std::tuple<bool, O> get_field_value(HMODULE module, const char* procName);

FARPROC get_function(HMODULE module, const char* procName);

void run_event(Event event);