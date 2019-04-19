#pragma once
#include "Mod.h"
#include <string>
#include <vector>

class ModHandler {
public:
	std::vector<Mod> mods;

	void load_mods(const char* startingPath);
	void setup_mods();
	void check_dependencies();
	void post_setup_mods();
private:
	std::vector<std::string> modNameDump;
	void recursive_dependency_load(Mod mod, int i);
	void get_files(std::string path);
	void find_mods(std::string path);
};