#pragma once

#include <vector>

// Some utilities with mods, including a mod struct definition and a mod list

struct Mod {
	LPCWSTR fileName;
	HMODULE fileModule;
};

extern std::vector<Mod> ModList;