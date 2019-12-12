#pragma once

#include <iostream>
#include "util/Utility.h"
#include "SatisfactoryModLoader.h"
#include "CoreTypes.h"

namespace SML {
	namespace Logging
	{	
		enum LogType {
			Debug,
			Info,
			Warning,
			Error,
			Fatal
		};
		
		constexpr const TCHAR* getLogTypeStr(LogType type);
		
		// logs a message of <T> with various modifiers
		template<typename First, typename ...Args>
		void log(LogType type, First &&arg0, Args &&...args) {
			std::wstring message = formatStr(arg0, args...);
			const std::wstring result = formatStr("[", getLogTypeStr(type), "] ", message);
			std::wcout << result << std::endl;
			getLogFile() << result << std::endl;
		}

		template<typename First, typename ...Args>
		void debug(First &&arg0, Args &&...args) {
			if (debugOutput) {
				log(LogType::Debug, arg0, args...);
			}
		}

		template<typename First, typename ...Args>
		void info(First &&arg0, Args &&...args) {
			log(LogType::Info, arg0, args...);
		}

		template<typename First, typename ...Args>
		void warning(First &&arg0, Args &&...args) {
			log(LogType::Warning, arg0, args...);
		}

		template<typename First, typename ...Args>
		void error(First &&arg0, Args &&...args) {
			log(LogType::Error, arg0, args...);
		}

		template<typename First, typename ...Args>
		void fatal(First &&arg0, Args &&...args) {
			log(LogType::Fatal, arg0, args...);
		}

		constexpr const TCHAR* getLogTypeStr(LogType type) {
			switch (type) {
			case Debug: return TEXT("DEBUG");
			case Info: return TEXT("INFO");
			case Warning: return TEXT("WARN");
			case Error: return TEXT("ERROR");
			case Fatal: return TEXT("FATAL");
			default: return TEXT("UNKNOWN");
			}
		}
	}
}