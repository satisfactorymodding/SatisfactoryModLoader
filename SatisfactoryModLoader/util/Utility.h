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

void log(LogType type);

void draw_header(std::string header, LogType type);

// logs a message of <T> with various modifiers
template<typename First, typename ...Args>
void log(LogType type, First&& arg0, Args&& ...args) {
	set_console_color(
		type == LogType::Info || type == LogType::ModInfo ? ConsoleColor::Green :
		type == LogType::Warning || type == LogType::ModWarning ? ConsoleColor::Yellow :
		ConsoleColor::Red);

	std::cout << std::forward<First>(arg0);
	_logFile << std::forward<First>(arg0);
	log(type, std::forward<Args>(args)...);

	if (sizeof...(args) == 0) {
		std::cout << std::endl;
		_logFile << std::endl;
		set_console_color(ConsoleColor::White);
	}
}

template<typename First, typename ...Args>
void info(First&& arg0, Args&& ...args) {
	draw_header("SML", LogType::Info);
	log(LogType::Info, arg0, args...);
}

template<typename First, typename ...Args>
void warning(First&& arg0, Args&& ...args) {
	draw_header("SML", LogType::Warning);
	log(LogType::Warning, arg0, args...);
}

template<typename First, typename ...Args>
void error(First&& arg0, Args&& ...args) {
	draw_header("SML", LogType::Error);
	log(LogType::Error, arg0, args...);
}

template<typename First, typename ...Args>
void info_mod(std::string mod, First&& arg0, Args&& ...args) {
	draw_header(mod, LogType::ModInfo);
	log(LogType::ModInfo, arg0, args...);
}

template<typename First, typename ...Args>
void warning_mod(std::string mod, First&& arg0, Args&& ...args) {
	draw_header(mod, LogType::ModWarning);
	log(LogType::ModWarning, arg0, args...);
}

template<typename First, typename ...Args>
void error_mod(std::string mod, First&& arg0, Args&& ...args) {
	draw_header(mod, LogType::ModError);
	log(LogType::ModError, arg0, args...);
}

template <class T>
T * offset(T * ptr, size_t offset) {
	return (T *)(reinterpret_cast<unsigned char*>(ptr) + offset);
}