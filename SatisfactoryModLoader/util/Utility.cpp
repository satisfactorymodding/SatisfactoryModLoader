#include <stdafx.h>
#include <detours.h>
#include <Main.h>
#include "Utility.h"

void log() {}

void log(LogType type) {}

void draw_header(std::string header, LogType type) {
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
	logFile << "[" + header + "::" + logType;

	// cout line
	set_console_color(type > 2 && type <= 5 ? ConsoleColor::Cyan : ConsoleColor::White);
	std::cout << "[" << header << "] ";
}

void set_console_color(ConsoleColor color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// sets the console color
	SetConsoleTextAttribute(hConsole, color + 1);
}

void check_version(std::string target) {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	auto pointer = (const wchar_t*(WINAPI*)())DetourFindFunction("FactoryGame-Win64-Shipping.exe", "BuildSettings::GetBuildVersion");
	DetourTransactionCommit();
	std::wstring satisVersion(pointer());
	std::string str(satisVersion.begin(), satisVersion.end());
	if (str.substr(str.length() - 5, str.length()) == target) {
		info("Version check passed!");
	} else {
		error("FATAL: Version check failed");
		if (!supressErrors) {
			int ret = MessageBoxA(NULL, "The version of SML that you are using is not compatible with your version of Satisfactory!\nIf SML is not available for the latest version of satisfactory, please yell at SuperCoder or Nomnom to compile one.\nPress Ok to continue at your own discresion or cancel to stop the program.", "SatisfactoryModLoader Fatal Error", MB_OKCANCEL | MB_DEFBUTTON2 | MB_ICONERROR);
			if (ret == IDCANCEL) {
				exit(1);
			}
		} else {
			warning("SupressErrors set to true, continuing...");
		}
	}
}