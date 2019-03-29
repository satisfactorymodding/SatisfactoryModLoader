#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <utility>

static constexpr const char* _header = "[SML] ";
static std::ofstream _logFile("SatisfactoryModLoader.log");

enum LogType {
	Normal,
	Warning,
	Error
};

const int _consoleDefault = 15;
const int _consoleNormal = 10;
const int _consoleWarning = 14;
const int _consoleError = 12;

static bool _usingConsole;

void set_console_color(int color);

void log(LogType type);

// logs a message of <T> with various modifiers
template<typename First, typename ...Args>
void log(LogType type, First&& arg0, Args&& ...args) {
	set_console_color(type == LogType::Normal ? _consoleNormal : type == LogType::Warning ? _consoleWarning : _consoleError);

	if (!_usingConsole) {
		std::cout << _header;
		_usingConsole = true;
	}

	std::cout << std::forward<First>(arg0);
	log(type, std::forward<Args>(args)...);

	if (sizeof...(args) == 0) {
		std::cout << std::endl;
		set_console_color(_consoleDefault);
		_usingConsole = false;
	}
}