#include "stdafx.h"
#include "Utility.h"
#include <Windows.h>
#include <iostream>
#include <string>

static constexpr const char* _header = "SML";

void log(std::string msg, bool endLine, bool showHeader, const char* event) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 10);
	if (showHeader) {
		std::cout << "[" << _header;

		if (std::strlen(event) > 0) {
			std::cout << " | " << event;
		}

		std::cout << "] ";
	}

	std::cout << msg;
	if (endLine) {
		std::cout << std::endl;
	}
	SetConsoleTextAttribute(hConsole, 15);
}

void logError(std::string msg, bool endLine, bool showHeader, const char* event) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 12);
	if (showHeader) {
		std::cout << "[" << _header;

		if (std::strlen(event) > 0) {
			std::cout << " | " << event;
		}

		std::cout << "] ";
	}

	std::cout << msg;
	if (endLine) {
		std::cout << std::endl;
	}
	SetConsoleTextAttribute(hConsole, 15);
}