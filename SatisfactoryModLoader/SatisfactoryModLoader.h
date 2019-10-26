#pragma once
#include <tuple>
#include <string>
#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <mod/ModHandler.h>
#include <Lib.h>

namespace SML {
	extern "C" const SML_API char smlVersion[]; // outside accessible SML version
	static const std::string modLoaderVersion = std::string(smlVersion); // SML's version
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
