#pragma once
#include <windows.h>
#include <vector>
#include <string>

#include "../UMLDefs.h"

#define APP_NAME "Daedalus"
#define LOG_STREAM stdout

class LOADER_API Log
{
private:
	enum MsgType
	{
		INFO_MSG = 0,
		WARNING_MSG = 1,
		ERROR_MSG = 2,
		INFO_PRINTCONSOLE = 3
	};

	template <typename ...Args>
	static void LogMsg(MsgType type, const std::string& format, Args&& ...args)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		fprintf(LOG_STREAM, "[");
		SetConsoleTextAttribute(hConsole, 11);
		fprintf(LOG_STREAM, APP_NAME);
		SetConsoleTextAttribute(hConsole, 7);
		fprintf(LOG_STREAM, "][");

		switch (type)
		{
		case INFO_MSG:
			SetConsoleTextAttribute(hConsole, 10);
			fprintf(LOG_STREAM, "INFO");
			break;
		case WARNING_MSG:
			SetConsoleTextAttribute(hConsole, 14);
			fprintf(LOG_STREAM, "WARNING");
			break;
		case ERROR_MSG:
			SetConsoleTextAttribute(hConsole, 12);
			fprintf(LOG_STREAM, "ERROR");
			break;
		case INFO_PRINTCONSOLE:
			SetConsoleTextAttribute(hConsole, 13);
			fprintf(LOG_STREAM, "PRINT");
			break;
		}

		auto size = std::snprintf(nullptr, 0, format.c_str(), std::forward<Args>(args)...);
		std::string output(size + 1, '\0');
		std::sprintf(&output[0], format.c_str(), std::forward<Args>(args)...);

		SetConsoleTextAttribute(hConsole, 7);
		fprintf(LOG_STREAM, "] %s\n", output.c_str());
		LogArray.push_back(output);
		Log::DumpLog();
	}

public:
	template <typename ...Args>
	static void Info(const std::string& format, Args&& ...args)
	{
		LogMsg(INFO_MSG, format, std::forward<Args>(args)...);
	}

	template <typename ...Args>
	static void Warn(const std::string& format, Args&& ...args)
	{
		LogMsg(WARNING_MSG, format, std::forward<Args>(args)...);
	}

	template <typename ...Args>
	static void Error(const std::string& format, Args&& ...args)
	{
		LogMsg(ERROR_MSG, format, std::forward<Args>(args)...);
	}

	template <typename ...Args>
	static void Print(const std::string& format, Args&& ...args)
	{
		LogMsg(INFO_PRINTCONSOLE, format, std::forward<Args>(args)...);
	}

	static void SetupErrorMessage(std::string Message) 
	{
		MessageBoxA(NULL, (Message + "\nPress OK to exit.").c_str(), "Error", MB_ICONERROR);
		abort();
	}

	static void SetupMessage(std::string Info, std::string Message)
	{
		MessageBoxA(NULL, (Message).c_str(), Info.c_str(), MB_OK | MB_SYSTEMMODAL);
	}

	static bool DumpLog()
	{
		FILE* Log = NULL;
		fopen_s(&Log, "Daedalus-Log.txt", "w+");
		for (size_t i = 0; i < LogArray.size(); i++)
		{
			auto currentstring = LogArray[i];
			fprintf(Log, "%s\n", currentstring.c_str());
		}
		fclose(Log);
	}

private:
	static std::vector<std::string> LogArray;
};