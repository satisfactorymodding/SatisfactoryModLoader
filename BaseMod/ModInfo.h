#pragma once
#define EXTERN_DLL_EXPORT extern "C" __declspec(dllexport)

enum TickEvent {
	None, Test
};

typedef void(*FUNC)();