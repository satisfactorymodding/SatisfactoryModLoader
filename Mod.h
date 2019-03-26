#pragma once
#include <Windows.h>
#include <string>

struct Mod {
	LPCWSTR fileName;
	HMODULE fileModule;
	std::string name;
	std::string version;
	std::string description;
	std::string authors;
};