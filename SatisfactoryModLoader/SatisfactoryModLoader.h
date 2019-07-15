#pragma once
#include <tuple>
#include <string>
#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <mod/ModHandler.h>

namespace SML {
	static const std::string modLoaderVersion = "1.0.0-pr6"; // SML's version
	static const int targetVersion = 102023; //CLs of Satisfactory, 1st is normal CL and 2nd is experimental CL
	static bool loadConsole = true;
	static bool debugOutput = false;
	static bool supressErrors = false;
	static bool chatCommands = true;

	extern Mod::ModHandler modHandler;

	void startSML();
	void readConfig();
	void cleanup();
}
