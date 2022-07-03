#pragma once
#include <util/Reflection.h>
#include <Windows.h>
#include <event/FunctionHolder.h>
#include <util/FKey.h>
#include <util/FString.h>
#include <inttypes.h>
#include <conio.h>

void int64ToChar(char a[], int64_t n) {
	memcpy(a, &n, 8);
}

void* playerInventory;

// ; bool __fastcall UPlayerInput::InputKey(UPlayerInput *this, FKey Key, EInputEvent Event, float AmountDepressed, bool bGamepad)
bool input_key(void* input, void* key, void* event, float amountDepressed, bool gamepad) {
	auto args = std::vector<void*>{
		input,
		key,
		event,
		&amountDepressed,
		&gamepad
	};
	run_mods(modList, EventType::InputKey, args);
	auto pointer = (bool(WINAPI*)(void*, void*, void*, float, bool))hookedFunctions[EventType::InputKey];
	bool down = pointer(input, key, event, amountDepressed, gamepad);
	return down;
}


// ; FString *__fastcall FKey::ToString(FKey *this, FString *result)
//void* input_key_down(void* key, void* result) {
//	log(LogType::Warning, "Key ToString");
//	auto pointer = (void*(WINAPI*)(void*, void*))hookedFunctions[EventType::InputKeyDown];
//	return pointer(key, result);
//}