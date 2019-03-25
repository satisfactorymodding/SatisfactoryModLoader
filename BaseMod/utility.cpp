#include "stdafx.h"
#include "utility.h"
#include "ModInfo.h"

// Provides a colored log with the mod's name
void log(std::string msg) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 11);
	std::cout << "[" + ModName + "] ";

	std::cout << msg;
	std::cout << std::endl;
	SetConsoleTextAttribute(hConsole, 15);
}

