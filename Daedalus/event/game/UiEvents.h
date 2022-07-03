#pragma once
#include <Windows.h>
#include <event/FunctionHolder.h>
#include <util/Reflection.h>
#include <util/Utility.h>

// ; bool __fastcall UButton::IsPressed(UButton *this)
GLOBAL bool u_button_pressed(void* button) {
	auto pointer = (bool(WINAPI*)(void*))hookedFunctions[EventType::UButtonPressed];
	return pointer(button);
}

// ; bool __fastcall UCheckBox::IsPressed(UCheckBox *this)
GLOBAL bool u_check_box_pressed(void* checkBox) {
	auto pointer = (bool(WINAPI*)(void*))hookedFunctions[EventType::UCheckBoxPressed];
	return pointer(checkBox);
}