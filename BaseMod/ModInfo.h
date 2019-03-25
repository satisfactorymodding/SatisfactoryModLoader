#pragma once
#define EXTERN_DLL_EXPORT extern "C" __declspec(dllexport)

enum Event {
	OnPickupFoliage,
	OnPlayerBeginPlay
};

typedef void(*FUNC)();