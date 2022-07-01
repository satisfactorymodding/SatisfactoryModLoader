#pragma once

#include <vector>

// Some utilities with mods, including a mod struct definition and a mod list

struct Mod {
	LPCWSTR fileName;
	HMODULE fileModule;
	std::string name;
	std::string version;
	std::string description;
	std::string authors;
};

extern std::vector<Mod> ModList;