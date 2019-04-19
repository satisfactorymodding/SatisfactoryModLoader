#pragma once
#include <Windows.h>
#include <string>

struct Mod {
	//values from mod dll
	std::string fileName;
	HMODULE fileModule;
	std::string name;
	std::string version;
	std::string targetVarsion;
	std::string description;
	std::string authors;
	std::vector<std::string> dependencies;
	//values for modloader use
	bool postInitialized = false;
};