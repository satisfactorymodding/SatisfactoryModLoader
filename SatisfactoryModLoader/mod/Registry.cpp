#include <stdafx.h>
#include "Registry.h"
#include <detours.h>
#include <SatisfactoryModLoader.h>
#include <util/Utility.h>

PVOID chatFunc;

void player_sent_message(void* player, FString* message) {

	auto pointer = (void(WINAPI*)(void*, void*))chatFunc;

	char* chars = new char[message->length];

	for (size_t i = 0; i < message->length; i++) {
		chars[i] = message->data[i];
	}

	std::string str(chars);
	bool found = false;
	for (Registry r : modHandler.commandRegistry) {
		if (str == "/" + r.name) {
			auto commandFunc = (void(WINAPI*)())r.func;
			commandFunc();
			found = true;
		}
	}
	if (!found) {
		pointer(player, message);
	}

}

void hookCommandRegistry(){
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	// find the function by name
	chatFunc = DetourFindFunction("FactoryGame-Win64-Shipping.exe", "AFGPlayerController::EnterChatMessage");

	DetourAttach(&(PVOID&)chatFunc, player_sent_message);
	DetourTransactionCommit();
	info("Hooked Command Registry!");
} 