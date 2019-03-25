#pragma once
#include <tuple>
#include <string>
enum Event {
	OnPickupFoliage
};

void mod_loader_entry();

typedef void(*FUNC)();

template<typename T>
void log(T msg, bool endLine = true, bool showHeader = true, const char* event = "");

template <typename O>
std::tuple<bool, O> get_function_value(HMODULE module, const char* procName);

template <typename O>
std::tuple<bool, O> get_field_value(HMODULE module, const char* procName);

FARPROC get_function(HMODULE module, const char* procName);

void run_event(Event event);

void run_pre_init();

void run_post_init();