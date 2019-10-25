#pragma once
#include <tuple>
#include <string>
#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <mod/ModHandler.h>
#include <Lib.h>

namespace SML {
	SML_API extern const std::string modLoaderVersion;
	SML_API extern const int targetVersion;
	extern bool loadConsole;
	extern bool debugOutput;
	extern bool supressErrors;
	extern bool chatCommands;
	extern bool crashReporter;
	extern bool unsafeMode;

	extern Mod::ModHandler modHandler;

	void startSML();
	void readConfig();
	void cleanup();
}
