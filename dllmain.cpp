// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "Mod.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <tuple>

// Main DLL for loading mod DLLs
typedef std::string STRINGFUNC();

std::tuple<bool, std::string> get_string(HMODULE module, const char* procName);

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		MessageBoxA(NULL, "Attempting to load mod DLLs!", "Satisfactory Mod Loader", NULL);

		// get application path
		char p[MAX_PATH];
		GetModuleFileNameA(NULL, p, MAX_PATH);

		// split the path
		std::string appPath(p);
		size_t pos = appPath.find_last_of('\\');
		std::string path = appPath.substr(0, pos) + "\\mods";
		std::string pathExact = path + "\\";

		// iterate through the directory to find mods
		for (const auto & entry : std::experimental::filesystem::directory_iterator(path)) {
			if (entry.path().extension().string() == ".dll") { // check if the file has a .dll extension
				std::string file = pathExact + entry.path().filename().string();
				std::wstring stemp = std::wstring(file.begin(), file.end());
				LPCWSTR sw = stemp.c_str();

				HMODULE dll = LoadLibrary(sw); // load the dll

				FARPROC valid = GetProcAddress(dll, "isMod");
				if (!valid) { //check validity of the mod dll
					FreeLibrary(dll);
					continue;
				}

				std::tuple<bool, std::string> modName = get_string(dll, "ModName");
				std::tuple<bool, std::string> modVersion = get_string(dll, "ModVersion");
				std::tuple<bool, std::string> modDescription = get_string(dll, "ModDescription");
				std::tuple<bool, std::string> modAuthors = get_string(dll, "ModAuthors");

				if (!std::get<0>(modName) || !std::get<0>(modVersion) || !std::get<0>(modDescription) || !std::get<0>(modAuthors)) {
					FreeLibrary(dll);
					continue;
				}

				// if valid, initalize a mod struct and add it to the modlist
				Mod mod = {
					sw,
					dll,
					std::get<1>(modName),
					std::get<1>(modVersion),
					std::get<1>(modDescription),
					std::get<1>(modAuthors),
				};

				ModList.push_back(mod);

				std::cout << "[Name] " << mod.name;
				std::cout << " [Version] " << mod.version;
				std::cout << " [Description] " << mod.description;
				std::cout << " [Authors] " << mod.authors << std::endl;
			}
		}
	}
    return TRUE;
}

std::tuple<bool, std::string> get_string(HMODULE module, const char* procName) {
	FARPROC proc = GetProcAddress(module, procName);
	if (!proc) {
		return std::make_tuple(false, "");
	}

	STRINGFUNC* f = (STRINGFUNC*)proc;
	return std::make_tuple(true, f());
}