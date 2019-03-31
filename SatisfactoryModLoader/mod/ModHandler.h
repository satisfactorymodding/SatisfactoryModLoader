#pragma once
#include "Mod.h"
#include <string>
#include <vector>

class ModHandler {
public:
	std::vector<Mod> mods;

	void load_mods(const char* startingPath);
	void setup_mods();
private:
	void get_files(std::string path);
	void find_mods(std::string path);
};