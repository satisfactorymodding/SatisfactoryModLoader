#pragma once
enum TickEvent {
	None, Test
};

typedef void(*FUNC)();

template <typename O>
std::tuple<bool, O> get_value(HMODULE module, const char* procName);

FARPROC get_function(HMODULE module, const char* procName);

void run_tick_event(HMODULE module, TickEvent event);