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
const int _consoleMod = 11;

static bool _usingConsole;
static bool _firstLogLine = true;

void set_console_color(int color);

void check_version(std::string target);

void log();

void log(LogType type);

void mod_log(std::string modname);

// logs a message of <T> with various modifiers
template<typename First, typename ...Args>
void log(LogType type, First&& arg0, Args&& ...args) {
	set_console_color(type == LogType::Normal ? _consoleNormal : type == LogType::Warning ? _consoleWarning : _consoleError);

	if (!_usingConsole) {
		std::cout << _header;
		_usingConsole = true;
	}

	if (_firstLogLine) {
		if (type == LogType::Warning) {
			_logFile << "[WARN]";
		}
		if (type == LogType::Error) {
			_logFile << "[ERROR]";
		}
		_firstLogLine = false;
	}
	std::cout << std::forward<First>(arg0);
	_logFile << std::forward<First>(arg0);
	log(type, std::forward<Args>(args)...);

	if (sizeof...(args) == 0) {
		_firstLogLine = true;
		_logFile << "\n";
		std::cout << std::endl;
		set_console_color(_consoleDefault);
		_usingConsole = false;
	}
}

template<typename First, typename ...Args>
void log(First&& arg0, Args&& ...args) {
	set_console_color(_consoleNormal);

	if (!_usingConsole) {
		std::cout << _header;
		_usingConsole = true;
	}

	std::cout << std::forward<First>(arg0);
	_logFile << std::forward<First>(arg0);
	log(std::forward<Args>(args)...);

	if (sizeof...(args) == 0) {
		_logFile << "\n";
		std::cout << std::endl;
		set_console_color(_consoleDefault);
		_usingConsole = false;
	}
}

template<typename First, typename ...Args>
void mod_log(std::string modname, First&& arg0, Args&& ...args) {
	set_console_color(_consoleMod);

	if (!_usingConsole) {
		std::cout << _header;
		_usingConsole = true;
	}

	if (_firstLogLine) {
		std::cout << "[" + modname + "] ";
		_logFile << "[" + modname + "] ";
		_firstLogLine = false;
	}

	std::cout << std::forward<First>(arg0);
	_logFile << std::forward<First>(arg0);
	mod_log(modname, std::forward<Args>(args)...);

	if (sizeof...(args) == 0) {
		_firstLogLine = true;
		_logFile << "\n";
		std::cout << std::endl;
		set_console_color(_consoleDefault);
		_usingConsole = false;
	}
}