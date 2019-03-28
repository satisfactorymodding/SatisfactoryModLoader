#pragma once
#include "mod/Mod.h"

#include <string>
#include <vector>

class ModHandler {
public:
	std::vector<Mod> Mods;

	void load_mods(const char* startingPath);
private:
	void find_mods(std::string path);
};