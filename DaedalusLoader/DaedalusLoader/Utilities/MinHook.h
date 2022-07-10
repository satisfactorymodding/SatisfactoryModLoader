#pragma once
#include <string>
#include "Logger.h"
#include "include/MinHook.h"
#include "Globals.h"
#ifdef UNREALENGINEMODLOADER_EXPORTS //Stops dumb errors from the ExampleMod shit
#pragma comment(lib,"../../Minhook/lib/libMinHook-x64-v141-mtd.lib")
#endif

namespace MinHook
{
	static void Init()
	{
		if (MH_Initialize() != MH_OK)
		{
			Log::Error("Failed to initialize MinHook");
		}
	}

	template <typename T>
	static void Add(DWORD_PTR pTarget, LPVOID pDetour, T** ppOriginal, std::string displayName = "")
	{
		if (MH_CreateHook((LPVOID)pTarget, pDetour, reinterpret_cast<LPVOID*>(ppOriginal)) != MH_OK)
		{
			Log::Error("Failed to create hook: %s", displayName.c_str());
			return;
		}

		if (MH_EnableHook((LPVOID)pTarget) != MH_OK)
		{
			Log::Error("Failed to enable hook: %s", displayName.c_str());
			return;
		}
		Log::Info("Added hook: %s", displayName.c_str());
	}
}