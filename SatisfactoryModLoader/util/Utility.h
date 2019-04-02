#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <utility>

static std::ofstream _logFile("SatisfactoryModLoader.log", std::ios_base::app);

enum LogType {
	Info,
	Warning,
	Error,
	ModInfo,
	ModWarning,
	ModError
};

static bool _usingConsole;

enum ConsoleColor {
	DarkBlue,
	DarkGreen,
	DarkCyan,
	DarkRed,
	DarkMagenta,
	DarkYellow,
	DarkWhite,
	Grey,
	Blue,
	Green,
	Cyan,
	Red,
	Magenta,
	Yellow,
	White
};

void set_console_color(ConsoleColor color);

void check_version(std::string target);

void log();

void log(std::string header, LogType type);

void mod_log(std::string modname);

// logs a message of <T> with various modifiers
template<typename First, typename ...Args>
void log(std::string header, LogType type, First&& arg0, Args&& ...args) {
	if (!_usingConsole) {
		_usingConsole = true;

		std::string logType;

		switch (type) {
		case Info:
		case ModInfo:
			logType = "Info]    ";
			break;
		case Warning:
		case ModWarning:
			logType = "Warning] ";
			break;
		case Error:
		case ModError:
			logType = "Error]   ";
			break;
		}

		// log line
		_logFile << "[" + header + "::" + logType;

		// cout line
		set_console_color(type > 2 && type <= 5 ? ConsoleColor::Cyan : ConsoleColor::White);
		std::cout << "[" << header << "] ";

		set_console_color(
			type == LogType::Info || type == LogType::ModInfo ? ConsoleColor::Green :
			type == LogType::Warning || type == LogType::ModWarning ? ConsoleColor::Yellow :
			ConsoleColor::Red);
	}

	std::cout << std::forward<First>(arg0);
	_logFile << std::forward<First>(arg0);
	log(header, type, std::forward<Args>(args)...);

	if (sizeof...(args) == 0) {
		std::cout << std::endl;
		_logFile << std::endl;
		set_console_color(ConsoleColor::White);
	}
}

template<typename First, typename ...Args>
void info(First&& arg0, Args&& ...args) {
	_usingConsole = false;
	log("SML", LogType::Info, arg0, args...);
}

template<typename First, typename ...Args>
void warning(First&& arg0, Args&& ...args) {
	_usingConsole = false;
	log("SML", LogType::Warning, arg0, args...);
}

template<typename First, typename ...Args>
void error(First&& arg0, Args&& ...args) {
	_usingConsole = false;
	log("SML", LogType::Error, arg0, args...);
}

template<typename First, typename ...Args>
void info_mod(std::string mod, First&& arg0, Args&& ...args) {
	_usingConsole = false;
	log(mod, LogType::ModInfo, arg0, args...);
}

template<typename First, typename ...Args>
void warning_mod(std::string mod, First&& arg0, Args&& ...args) {
	_usingConsole = false;
	log(mod, LogType::ModWarning, arg0, args...);
}

template<typename First, typename ...Args>
void error_mod(std::string mod, First&& arg0, Args&& ...args) {
	_usingConsole = false;
	log(mod, LogType::ModError, arg0, args...);
}