#pragma once
#include <map>
#include <string>
#include <iostream>
#include <event/Event.h>
#include <event/FunctionHolder.h>
#include <util/Reflection.h>
#include <util/Utility.h>

#define GLOBAL extern "C" __declspec(dllexport)

GLOBAL std::string ModName;
GLOBAL std::string ModVersion;
GLOBAL std::string ModDescription;
GLOBAL std::string ModAuthors;