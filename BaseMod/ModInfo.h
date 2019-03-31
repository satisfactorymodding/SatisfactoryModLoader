#pragma once
#include <map>
#include <string>
#include <iostream>
#include <event/Event.h>
#include <event/FunctionHolder.h>
#include <util/Reflection.h>
#include <util/Utility.h>

#define GLOBAL extern "C" __declspec(dllexport)

GLOBAL const char* ModName = "BaseMod";
GLOBAL const char* ModVersion = "1.0.0";
GLOBAL const char* ModDescription = "A base mod made for easy mod creation.";
GLOBAL const char* ModAuthors = "SuperCoder79, Nomnom";

GLOBAL void recieve_hooked_functions(std::map<EventType, PVOID> functions) {
	hookedFunctions = functions;
}