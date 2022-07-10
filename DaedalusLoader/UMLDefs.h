#pragma once

//Easy To Manage, keeping it in one place.
#define MODLOADER_VERSION "2.2.0"

#ifdef UNREALENGINEMODLOADER_EXPORTS
#define LOADER_API __declspec(dllexport)
#else
#define LOADER_API __declspec(dllimport)
#endif

#define BPFUNCTION(Function) void Function(UE4::UObject* ContextObject, UE4::FFrame* stack, void* const ret)

#define REGISTER_FUNCTION(Function) Global::GetGlobals()->AddBPFunctionWrapper(#Function, Function);