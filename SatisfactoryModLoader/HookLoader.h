#pragma once

#include "HookLoaderInternal.h"

// Subscribe a handler to a function defined in the game binary.
template <auto HookableFunction>
void subscribe(typename HookInvoker<decltype(HookableFunction), HookableFunction>::Handler handler) {
	HookInvoker<decltype(HookableFunction), HookableFunction>::subscribe(handler);
}

// Directly call a function defined in the game binary.
template <auto HookableFunction, typename... A>
typename HookInvoker<decltype(HookableFunction), HookableFunction>::ReturnType
call(A... args) {
	return HookInvoker<decltype(HookableFunction), HookableFunction>::get_original()(args...);
}