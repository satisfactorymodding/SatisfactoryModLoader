#pragma once
#include <Windows.h>
#include <event/FunctionHolder.h>
#include <util/Reflection.h>
#include <util/Utility.h>

// ; UWorld *__fastcall UGameInstance::GetWorld(UGameInstance *this)
GLOBAL void* game_instance_get_world(void* game) {
	auto pointer = (void*(WINAPI*)(void*))hookedFunctions[EventType::GameInstanceGetWorld];
	return pointer(game);
}

// ; APawn *__fastcall UGameplayStatics::GetPlayerPawn(UObject *WorldContextObject, int PlayerIndex)
GLOBAL void* game_get_player(void* world, int playerIndex) {
	auto pointer = (void*(WINAPI*)(void*, int))DetourFindFunction("FactoryGame-Win64-Shipping.exe", "UGameplayStatics::GetPlayerPawn");
	void* player = pointer(world, playerIndex);
	return player;
}

//; void __fastcall AFGPlayerController::Suicide(AFGPlayerController *this)
GLOBAL void player_suicide(void* player) {
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::PlayerSuicide];
	auto args = std::vector<void*>{
		player
	};
	if (!run_mods(modList, EventType::PlayerSuicide, args)) {
		return;
	}
	pointer(player);
}

// ; void __fastcall AFGPlayerController::EnterChatMessage(AFGPlayerController *this, FString *inMessage)
GLOBAL void player_send_message(void* player, std::string message) {
	FString msg = message.c_str();

	auto pointer = (void(WINAPI*)(void*, FString*))hookedFunctions[EventType::PlayerSentMessage];
	pointer(player, &msg);
}

// ; void __fastcall UFGInventoryComponent::SortInventory(UFGInventoryComponent *this)
GLOBAL void inventory_sort(void* inventory) {
	auto args = std::vector<void*>{
		inventory
	};
	if (!run_mods(modList, EventType::InventorySort, args)) {
		return;
	}
	auto pointer = (void(WINAPI*)(void*))hookedFunctions[EventType::InventorySort];
	pointer(inventory);
}