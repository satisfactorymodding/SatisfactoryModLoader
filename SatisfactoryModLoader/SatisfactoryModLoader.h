#pragma once
#include <tuple>
#include <string>
#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <mod/ModHandler.h>

namespace SML {
	static const std::string modLoaderVersion = "1.0.0"; // SML's version
	static const int targetVersion = 103400; //CL of Satisfactory
	extern bool loadConsole;
	extern bool debugOutput;
	extern bool supressErrors;
	extern bool chatCommands;
	extern bool crashReporter;

	extern Mod::ModHandler modHandler;

	void startSML();
	void readConfig();
	void cleanup();
}
