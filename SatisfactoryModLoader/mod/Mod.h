#pragma once
#include <string>
#include <Windows.h>

struct Mod {
	LPCWSTR fileName;
	HMODULE fileModule;
	std::string name;
	std::string version;
	std::string description;
	std::string authors;
};