#pragma once
#include <string>
#include <Windows.h>
#include <Lib.h>
#include <util/FString.h>

struct Registry {
	std::string name;
	PVOID func;
};

extern PVOID chatFunc;

void hookCommandRegistry();

void player_sent_message(void* player, FString* message);