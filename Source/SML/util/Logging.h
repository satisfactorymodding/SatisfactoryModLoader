#pragma once

#include <iostream>
#include "util/Utility.h"
#include "SatisfactoryModLoader.h"
#include "CoreTypes.h"
#include <winuser.h>
#include <fstream>

#include "Console.h"

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
			const FString Message = formatStr(arg0, args...);
#if !WITH_EDITOR
			const FString Result = FString::Printf(TEXT("[%s] %s"), getLogTypeStr(type), *Message);
			std::wcout << *Result << std::endl;
			GetLogFile() << *Result << std::endl;
#endif
			if (type == LogType::Fatal) {
				SML::NotifyFatalError(Message);
			}
			const ELogVerbosity::Type Verbosity = logTypeToVerbosity(type);
			FMsg::Logf(nullptr, 0, FName(TEXT("SatisfactoryModLoader")), Verbosity, TEXT("%s"), *Message);
		}

		template<typename First, typename ...Args>
		void debug(First &&arg0, Args &&...args) {
			if (GetSmlConfig().bDebugLogOutput) {
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
