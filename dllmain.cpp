// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "Mod.h"
#include "DllMain.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <tuple>

// Main DLL for loading mod DLLs
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

				//std::tuple<bool, std::string> modName = get_value<std::string>(dll, "ModName");
				std::tuple<bool, std::string> modName = get_field_value<std::string>(dll, "ModName");
				std::tuple<bool, std::string> modVersion = get_field_value<std::string>(dll, "ModVersion");
				std::tuple<bool, std::string> modDescription = get_field_value<std::string>(dll, "ModDescription");
				std::tuple<bool, std::string> modAuthors = get_field_value<std::string>(dll, "ModAuthors");

				if (!std::get<0>(modName) || !std::get<0>(modVersion) || !std::get<0>(modDescription) || !std::get<0>(modAuthors)) {
					FreeLibrary(dll);
					continue;
				}

				// run test event
				run_tick_event(dll, TickEvent::Test);

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

template <typename O>
std::tuple<bool, O> get_function_value(HMODULE module, const char* procName) {
	FARPROC proc = GetProcAddress(module, procName);
	if (!proc) {
		return std::make_tuple(false, "");
	}

	typedef O TFUNC();
	TFUNC* f = (TFUNC*)proc;

	return std::make_tuple(true, f());
}

FARPROC get_function(HMODULE module, const char* procName) {
	FARPROC proc = GetProcAddress(module, procName);
	if (!proc) {
		return NULL;
	}

	return proc;
}

template <typename O>
std::tuple<bool, O> get_field_value(HMODULE module, const char* procName) {
	FARPROC proc = get_function(module, procName);
	if (!proc) {
		return std::make_tuple(false, "");
	}

	typedef O (funcN);
	funcN* n1 = (funcN*)proc;
	return std::make_tuple(true, *n1);
}

void run_tick_event(HMODULE module, TickEvent event) {
	FARPROC func = get_function(module, "GetTickEvent");

	typedef FUNC GETFUNC(TickEvent);
	GETFUNC* f = (GETFUNC*)func;
	FUNC returnFunc = (*f)(event);
	if (returnFunc != NULL) {
		returnFunc();
	}
}