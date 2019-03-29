#pragma once
#include <map>
#include <string>
#include <iostream>
#include <event/Event.h>
#include <event/FunctionHolder.h>
#include <util/Reflection.h>
#include <util/Utility.h>

#define EXTERN_DLL_EXPORT extern "C" __declspec(dllexport)

EXTERN_DLL_EXPORT std::string ModName;
EXTERN_DLL_EXPORT std::string ModVersion;
EXTERN_DLL_EXPORT std::string ModDescription;
EXTERN_DLL_EXPORT std::string ModAuthors;