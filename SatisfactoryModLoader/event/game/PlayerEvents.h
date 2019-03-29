#pragma once
#include <Windows.h>
#include <event/FunctionHolder.h>
#include <util/Reflection.h>
#include <util/Utility.h>

// ; void __fastcall AFGPlayerController::BeginPlay(AFGPlayerController *this)
EXTERN_DLL_EXPORT void player_begin_play(void* controller) {
	log(LogType::Normal, __FUNCSIG__);
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerBeginPlay];
	localPlayerController = controller;
	auto args = std::vector<void*>{
		controller
	};
	get_mod_values(modList, "player_begin_play_event", args);
	pointer(controller);
}

//; void __fastcall AFGPlayerController::Suicide(AFGPlayerController *this)
EXTERN_DLL_EXPORT void player_suicide(void* player) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerSuicide];
	pointer(player);
}

// ; void __fastcall AFGPlayerController::EnterChatMessage(AFGPlayerController *this, FString *inMessage)
EXTERN_DLL_EXPORT void player_sent_message(void* player, void* message) {
	auto pointer = (void(WINAPI*)(void*, void*))hookedFunctions[EventType::PlayerSentMessage];
	auto args = std::vector<void*>{};
	get_mod_values(modList, "player_sent_message_event", args);
	pointer(player, message);
}