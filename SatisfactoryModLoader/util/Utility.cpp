#include <stdafx.h>
#include "Utility.h"

void log(LogType type) {}

void set_console_color(int color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// sets the console color
	SetConsoleTextAttribute(hConsole, color);
}