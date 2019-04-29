#pragma once
#include <Windows.h>
#include <Lib.h>
#include <util/FString.h>
#include "Registry.h"

SML_API void registerCommand(std::string name, PVOID func);

SML_API void registerAPIFunction(std::string name, PVOID func);

SML_API PVOID getAPIFunction(std::string name);

SML_API bool isModLoaded(std::string name);