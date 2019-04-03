#pragma once
#include <map>
#include <string>
#include <iostream>
#include <event/Event.h>
#include <event/FunctionHolder.h>
#include <util/Reflection.h>
#include <util/Utility.h>

#define GLOBAL extern "C" __declspec(dllexport)

GLOBAL void recieve_hooked_functions(std::map<EventType, PVOID> functions);