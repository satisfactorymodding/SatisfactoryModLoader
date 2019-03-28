#pragma once
#include <string>
#include <iostream>

static constexpr const char* _header = "SML";

// logs a message of <T> with various modifiers
template<typename T>
void log(T msg, bool endLine = true, bool showHeader = true, const char* event = "") {
	// grabs the console
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// sets the console color
	SetConsoleTextAttribute(hConsole, 10);

	// draw the header information
	if (showHeader) {
		std::cout << "[" << _header;

		if (std::strlen(event) > 0) {
			std::cout << " | " << event;
		}

		std::cout << "] ";
	}

	// draw the message
	std::cout << msg;
	if (endLine) {
		std::cout << std::endl;
	}

	// reset the console color
	SetConsoleTextAttribute(hConsole, 15);
}

// logs an error message of <T> with various modifiers
template<typename T>
void logError(T msg, bool endLine = true, bool showHeader = true, const char* event = "") {\
	// grabs the console
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// sets the console color
	SetConsoleTextAttribute(hConsole, 12);

	// draw the header information
	if (showHeader) {
		std::cout << "[" << _header;

		if (std::strlen(event) > 0) {
			std::cout << " | " << event;
		}

		std::cout << "] ";
	}

	// draw the message
	std::cout << msg;
	if (endLine) {
		std::cout << std::endl;
	}

	// reset the console color
	SetConsoleTextAttribute(hConsole, 15);
}