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
	static bool loadConsole = true;
	static bool debugOutput = true;
	static bool supressErrors = false;
	static bool chatCommands = true;

	extern Mod::ModHandler modHandler;

	void initializeConsole();
	void extractZips();
	void startSML();
	void readConfig();
	void cleanup();
}
