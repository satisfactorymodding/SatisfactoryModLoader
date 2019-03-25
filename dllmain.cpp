// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "mod.h"
#include "dllmain.h"
#include "config.h"
#include "detoredevents.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <tuple>

typedef void(*FUNC)(void);

// Main DLL for loading mod DLLs
void mod_loader_entry() {

	// Allocate console
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOIN$", "r", stdin);
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);

	log("Attached SatisfactoryModLoader to Satisfactory");

	readConfig(); // read the config file

	if (!loadConsole) { // destroy the console if stated by the config file
		ShowWindow(GetConsoleWindow(), SW_HIDE);
	}

	// get application path
	char p[MAX_PATH];
	GetModuleFileNameA(NULL, p, MAX_PATH);

	// split the path
	std::string appPath(p);
	size_t pos = appPath.find_last_of('\\');
	std::string path = appPath.substr(0, pos) + "\\mods";
	std::string pathExact = path + "\\";

	log("Looking for mods in: " + path);

	// iterate through the directory to find mods
	for (const auto & entry : std::experimental::filesystem::directory_iterator(path)) {
		if (entry.path().extension().string() == ".dll") { // check if the file has a .dll extension
			std::string file = pathExact + entry.path().filename().string();
			std::wstring stemp = std::wstring(file.begin(), file.end());

			log("Attempting to load mod: " + file);

			LPCWSTR sw = stemp.c_str();

			HMODULE dll = LoadLibrary(sw); // load the dll

			FARPROC valid = GetProcAddress(dll, "isMod");
			if (!valid) { //check validity of the mod dll
				logError("Unloading non-mod DLL " + file);
				FreeLibrary(dll);
				continue;
			}

			std::tuple<bool, std::string> modName = get_field_value<std::string>(dll, "ModName");
			std::tuple<bool, std::string> modVersion = get_field_value<std::string>(dll, "ModVersion");
			std::tuple<bool, std::string> modDescription = get_field_value<std::string>(dll, "ModDescription");
			std::tuple<bool, std::string> modAuthors = get_field_value<std::string>(dll, "ModAuthors");
			
			if (!std::get<0>(modName) || !std::get<0>(modVersion) || !std::get<0>(modDescription) || !std::get<0>(modAuthors)) {
				logError("Mod DLL " + file + " does not have the required information!");
				FreeLibrary(dll);
				continue;
			}

			//check if the mod has already been loaded
			bool isDuplicate = false;
			for (Mod existingMod : modList) {
				if (existingMod.name == std::get<1>(modName)) {
					logError("Skipping duplicate mod " + existingMod.name);
					FreeLibrary(dll);
					isDuplicate = true;
					break;
				}
			}

			if (isDuplicate) {
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

			modList.push_back(mod);

			log("Loaded " + mod.name);
		}
	}

	size_t listSize = modList.size();
	log("Loaded " + std::to_string(listSize), false);
	if (listSize > 1) {
		log(" mods", true, false);
	}
	else {
		log(" mod", true, false);
	}

	// assign test event
	hook_event(Event::OnPickupFoliage, UFGFoliageLibrary_CheckInventorySpaceAndGetStacks);

	run_pre_init();

	log("SatisfactoryModLoader Initialization complete. Launching Satisfactory...");
}

template<typename T>
void log(T msg, bool endLine, bool showHeader, const char* event) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);
	if (showHeader) {
		std::cout << "[SML";
	
		if (std::strlen(event) > 0) {
			std::cout << " | " << event;
		}

		std::cout << "] ";
	}

	std::cout << msg;
	if (endLine) {
		std::cout << std::endl;
	}
	SetConsoleTextAttribute(hConsole, 15);
}

template<typename T>
void logError(T msg, bool endLine, bool showHeader, const char* event) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	if (showHeader) {
		std::cout << "[SML";

		if (std::strlen(event) > 0) {
			std::cout << " | " << event;
		}

		std::cout << "] ";
	}

	std::cout << msg;
	if (endLine) {
		std::cout << std::endl;
	}
	SetConsoleTextAttribute(hConsole, 15);
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

void run_event(Event event, void* args) {
	for (Mod mod : modList) {
		FARPROC func = get_function(mod.fileModule, "get_event");
		auto pointer = (PVOID(WINAPI*)(Event))func;
		auto rType = (void(WINAPI*)(void* args))pointer(event);
		rType(args);

		//typedef FUNC GETFUNC(Event);
		/*auto pointer = (PVOID(WINAPI*)(Event))func;
		auto iterator = functionList.find(event);
		auto rType = (void(WINAPI*)(PVOID))pointer(event);
		if (iterator != functionList.end()) {
			rType((*iterator).second.Func);
		}
		else {
			rType(NULL);
		}*/
	}
}

void run_pre_init() {
	log("Pre Initializing all mods", true, true);
	run_event(Event::OnPreInit, NULL);
	return;
}

void run_post_init() {
	log("Post Initializing!", true, true, "POSTINIT");
	return;
}