#pragma once
#include <Windows.h>
#include <event/FunctionHolder.h>
#include <util/Reflection.h>
#include <util/Utility.h>

// ; UWorld *__fastcall UGameInstance::GetWorld(UGameInstance *this)
EXTERN_DLL_EXPORT void* game_instance_get_world(void* game) {
	auto pointer = (void*(WINAPI*)(void*))hookedFunctions[EventType::GameInstanceGetWorld];
	worldInstance = pointer(game);
	return worldInstance;
}

// ; APawn *__fastcall UGameplayStatics::GetPlayerPawn(UObject *WorldContextObject, int PlayerIndex)
EXTERN_DLL_EXPORT void* game_get_player(void* world, int playerIndex) {
	auto pointer = (void*(WINAPI*)(void*, int))DetourFindFunction("FactoryGame-Win64-Shipping.exe", "UGameplayStatics::GetPlayerPawn");
	void* player = pointer(world, playerIndex);
	return player;
}