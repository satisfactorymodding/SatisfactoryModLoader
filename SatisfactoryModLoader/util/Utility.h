#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <utility>

#include "../Lib.h"

namespace SML {
	namespace Utility {
		static std::ofstream logFile;

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

		void displayCrash(std::string crashText);

		void SML_API setConsoleColor(ConsoleColor color);

		void SML_API checkVersion(const int target);

		void SML_API log();

		void SML_API log(LogType type);

		void SML_API writeHeader(std::string header, LogType type);

		// logs a message of <T> with various modifiers
		template<typename First, typename ...Args>
		void log(LogType type, First&& arg0, Args&& ...args) {
			setConsoleColor(
				type == LogType::Info || type == LogType::ModInfo ? ConsoleColor::Green :
				type == LogType::Warning || type == LogType::ModWarning ? ConsoleColor::Yellow :
				ConsoleColor::Red);

			std::cout << std::forward<First>(arg0);
			logFile << std::forward<First>(arg0);
			logFile.flush();
			log(type, std::forward<Args>(args)...);

			if (sizeof...(args) == 0) {
				std::cout << std::endl;
				logFile << std::endl;
				logFile.flush();
				setConsoleColor(ConsoleColor::White);
			}
		}

		template<typename First, typename ...Args>
		void info(First&& arg0, Args&& ...args) {
			writeHeader("SML", LogType::Info);
			log(LogType::Info, arg0, args...);
		}

		template<typename First, typename ...Args>
		void warning(First&& arg0, Args&& ...args) {
			writeHeader("SML", LogType::Warning);
			log(LogType::Warning, arg0, args...);
		}

		template<typename First, typename ...Args>
		void error(First&& arg0, Args&& ...args) {
			writeHeader("SML", LogType::Error);
			log(LogType::Error, arg0, args...);
		}

		template<typename First, typename ...Args>
		void infoMod(std::string mod, First&& arg0, Args&& ...args) {
			writeHeader(mod, LogType::ModInfo);
			log(LogType::ModInfo, arg0, args...);
		}

		template<typename First, typename ...Args>
		void warningMod(std::string mod, First&& arg0, Args&& ...args) {
			writeHeader(mod, LogType::ModWarning);
			log(LogType::ModWarning, arg0, args...);
		}

		template<typename First, typename ...Args>
		void errorMod(std::string mod, First&& arg0, Args&& ...args) {
			writeHeader(mod, LogType::ModError);
			log(LogType::ModError, arg0, args...);
		}

		template <class T>
		T * offset(T * ptr, size_t offset) {
			return (T *)(reinterpret_cast<unsigned char*>(ptr) + offset);
		}
	}
}