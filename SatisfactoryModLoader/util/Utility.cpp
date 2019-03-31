#include <stdafx.h>
#include "Utility.h"

void log() {}

void log(LogType type) {}

void mod_log(std::string modname) {}

void set_console_color(int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// sets the console color
	SetConsoleTextAttribute(hConsole, color);
}