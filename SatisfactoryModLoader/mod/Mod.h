#pragma once
#include <Windows.h>
#include <string>

struct Mod {
	std::string fileName;
	HMODULE fileModule;
	std::string name;
	std::string version;
	std::string description;
	std::string authors;
	std::vector<std::string> dependencies;
};