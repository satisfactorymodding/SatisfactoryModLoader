#include <stdafx.h>
#include "Hooks.h"
#include <detours.h>
#include <functional>
#include <SatisfactoryModLoader.h>
#include <game/Global.h>
#include <util/Utility.h>

PVOID chatFunc;
PVOID pakFunc;

using namespace std::placeholders;

// parse commands when the player sends a message
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

//void get_signing_keys(ModReturns* modReturns, void* outKey) {
//	info("Test");
//	modReturns->use_original_function = false;
//}

void hookFunctions() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	// find the function by name
	chatFunc = DetourFindFunction("FactoryGame-Win64-Shipping.exe", "AFGPlayerController::EnterChatMessage");
	DetourAttach(&(PVOID&)chatFunc, player_sent_message);
	info("Hooked Command Registry!");

	//pakFunc = DetourFindFunction("FactoryGame-Win64-Shipping.exe", "FPakPlatformFile::GetPakSigningKeys");
	//DetourAttach(&(PVOID&)pakFunc, get_signing_keys);
	//subscribe<&FPakPlatformFile::GetPakSigningKeys>(std::bind(get_signing_keys, _1, _2));

	//info("Hooked Paks!");

	DetourTransactionCommit();
}