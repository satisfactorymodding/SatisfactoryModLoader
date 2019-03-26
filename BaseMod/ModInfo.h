#pragma once
#include <string>
#define EXTERN_DLL_EXPORT extern "C" __declspec(dllexport)

EXTERN_DLL_EXPORT std::string ModName;
EXTERN_DLL_EXPORT std::string ModVersion;
EXTERN_DLL_EXPORT std::string ModDescription;
EXTERN_DLL_EXPORT std::string ModAuthors;