// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <string>
#include <iostream>
#include <filesystem>

//Main DLL for loading mod DLLs

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		MessageBoxA(NULL, "Attempting to load mod DLLs!", "Satisfactory Mod Loader", NULL);
		std::string path = "C:\\dev\\asm\\dll";
		std::string pathExact = "C:\\dev\\asm\\dll\\";
		for (const auto & entry : std::experimental::filesystem::directory_iterator(path)) {
			if (entry.path().extension() == std::experimental::filesystem::path("test.dll").extension()) {
				std::string file = pathExact.append(entry.path().filename().string());
				std::wstring stemp = std::wstring(file.begin(), file.end());
				LPCWSTR sw = stemp.c_str();
				LoadLibrary(sw);
				//std::cout << GetLastError();
				pathExact = "C:\\dev\\asm\\dll\\";
			}
		}
	}
    return TRUE;
}