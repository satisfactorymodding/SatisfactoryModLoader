#pragma once
#include <Windows.h>
#include <Lib.h>
#include <util/FString.h>
#include "Registry.h"

SML_API void registerCommand(std::string name, PVOID func);