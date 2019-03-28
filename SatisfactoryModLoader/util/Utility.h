#pragma once
#include <string>
#include <iostream>
#include <fstream>

static constexpr const char* _header = "SML";

extern std::ofstream logFile;

// logs a message of <T> with various modifiers
template<typename T>
void log(T msg, bool endLine = true, bool showHeader = true, const char* event = "") {
	// grabs the console
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// sets the console color
	SetConsoleTextAttribute(hConsole, 10);

	// send the header information
	if (showHeader) {
		std::cout << "[" << _header;

		if (std::strlen(event) > 0) {
			std::cout << " | " << event;
		}

		std::cout << "] ";
	}

	// send the message
	std::cout << msg;
	if (endLine) {
		std::cout << std::endl;
	}

	logFile << msg << "\n";

	// reset the console color
	SetConsoleTextAttribute(hConsole, 15);
}

// logs an error message of <T> with various modifiers
template<typename T>
void logError(T msg, bool endLine = true, bool showHeader = true) {
	// grabs the console
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// sets the console color
	SetConsoleTextAttribute(hConsole, 12);

	// send the header information
	if (showHeader) {
		std::cout << "[" << _header << "|ERROR] ";
	}

	// send the message
	std::cout << msg;
	if (endLine) {
		std::cout << std::endl;
	}

	logFile << "[ERROR] " << msg << "\n";

	// reset the console color
	SetConsoleTextAttribute(hConsole, 15);
}