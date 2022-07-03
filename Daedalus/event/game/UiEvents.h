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

// ; void __fastcall UButton::SlateHandlePressed(UButton *this)
GLOBAL void u_button_slate_handle_pressed(void* button) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::UButtonSlateHandlePressed];
	pointer(button);
}

// ; bool __fastcall SButton::IsPressed(SButton *this)
GLOBAL bool s_button_pressed(void* button) {
	auto pointer = (bool(WINAPI*)(void*))hookedFunctions[EventType::SButtonPressed];
	return pointer(button);
}

// ; bool __fastcall UAkCheckBox::IsPressed(UAkCheckBox *this)
GLOBAL bool uak_check_box_pressed(void* checkBox) {
	auto pointer = (bool(WINAPI*)(void*))hookedFunctions[EventType::UAkCheckBoxPressed];
	return pointer(checkBox);
}