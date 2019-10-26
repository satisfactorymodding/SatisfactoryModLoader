#pragma once
#include <tuple>
#include <string>
#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <mod/ModHandler.h>

namespace SML {
	static const std::string modLoaderVersion = "1.0.1"; // SML's version
	static const int targetVersion = 106504; //CL of Satisfactory
	extern bool loadConsole;
	extern bool debugOutput;
	extern bool supressErrors;
	extern bool chatCommands;
	extern bool crashReporter;
	extern bool unsafeMode;

	extern Mod::ModHandler modHandler;

	void initializeConsole();
	void extractZips();
	void startSML();
	void readConfig();
	void cleanup();
}
