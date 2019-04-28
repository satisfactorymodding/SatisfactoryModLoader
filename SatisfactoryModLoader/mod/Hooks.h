#pragma once
#include <Windows.h>
#include <Lib.h>
#include <util/FString.h>
#include <HookLoader.h>
#include <HookLoaderInternal.h>

extern PVOID chatFunc;
extern PVOID pakFunc;

void hookFunctions();

void get_signing_keys(ModReturns* modReturns, void* outKeys);

void player_sent_message(void* player, FString* message);