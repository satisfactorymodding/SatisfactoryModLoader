#pragma once
#include <map>
#include <vector>
#include <Windows.h>
#include <event/Event.h>
#include <mod/Mod.h>

static std::map<EventType, PVOID> hookedFunctions;
static std::vector<Mod> modList;
static void* localPlayerController;
static void* gameInstance;
static void* worldInstance;
static void* hookshotInstance;
static void* playerInstance;