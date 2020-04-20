#pragma once

#include <iostream>
#include "util/Utility.h"
#include "SatisfactoryModLoader.h"
#include "CoreTypes.h"
#include <winuser.h>
#include <fstream>

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

		inline ELogVerbosity::Type logTypeToVerbosity(LogType logType) {
			switch (logType) {
			case Debug: return ELogVerbosity::Verbose;
			case Info: return ELogVerbosity::Log;
			case Warning: return ELogVerbosity::Warning;
			case Error: return ELogVerbosity::Error;
			case Fatal: return ELogVerbosity::Fatal;
			default: return ELogVerbosity::Log;
			}
		}
		
		const TCHAR* getLogTypeStr(LogType type);
		
		// logs a message of <T> with various modifiers
		template<typename First, typename ...Args>
		void log(LogType type, First &&arg0, Args &&...args) {
			FString message = formatStr(arg0, args...);
#if WITH_EDITOR == 0
			const FString result = FString::Printf(TEXT("[%s] %s"), getLogTypeStr(type), *message);
			std::wcout << *result << std::endl;
			getLogFile() << *result << std::endl;
#endif
			if (type == LogType::Fatal) {
				MessageBoxA(NULL, TCHAR_TO_ANSI(*FString::Printf(TEXT("%s\nClick OK to exit."), *message)), "SatisfactoryModLoader", MB_ICONERROR);
			}
			const ELogVerbosity::Type verbosity = logTypeToVerbosity(type);
			FMsg::Logf(nullptr, 0, FName(TEXT("SatisfactoryModLoader")), verbosity, TEXT("%s"), *message);
		}

		template<typename First, typename ...Args>
		void debug(First &&arg0, Args &&...args) {
			if (getSMLConfig().debugLogOutput) {
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

		inline const TCHAR* getLogTypeStr(LogType type) {
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