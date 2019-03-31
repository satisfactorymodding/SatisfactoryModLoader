#pragma once
#include <map>
#include <string>
#include <iostream>
#include <event/Event.h>
#include <event/FunctionHolder.h>
#include <util/Reflection.h>
#include <util/Utility.h>

#define GLOBAL extern "C" __declspec(dllexport)

GLOBAL const std::string ModName;
GLOBAL const std::string ModVersion;
GLOBAL const std::string ModDescription;
GLOBAL const std::string ModAuthors;