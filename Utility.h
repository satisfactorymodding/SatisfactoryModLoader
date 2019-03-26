#pragma once
#include <string>
#include <iostream>

static constexpr const char* _header = "SML";

template<typename T>
void log(T msg, bool endLine = true, bool showHeader = true, const char* event = "") {
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

template<typename T>
void logError(T msg, bool endLine = true, bool showHeader = true, const char* event = "") {
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