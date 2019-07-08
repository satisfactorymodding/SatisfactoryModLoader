#define WIN32_LEAN_AND_MEAN

#include <stdafx.h>
#include <SatisfactoryModLoader.h>
#include "DetoursFwd.h"
#include "Utility.h"
#include <game/Utility.h>
#include <windows.h>

namespace SML {
	namespace Utility {
		void log() {}

		void log(LogType type) {}

		void writeHeader(std::string header, LogType type) {
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
			logFile.flush();

			// cout line
			setConsoleColor(type > 2 && type <= 5 ? ConsoleColor::Cyan : ConsoleColor::White);
			std::cout << "[" << header << "] ";
		}

		void setConsoleColor(ConsoleColor color) {
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			// sets the console color
			SetConsoleTextAttribute(hConsole, color + 1);
		}

		//target[0] = normal CL, target [1] = experimental CL
		void checkVersion(const std::string target[2]) {
			std::wstring satisVersion{ call<&Objects::BuildSettings::GetBuildVersion>() };
			std::string str(satisVersion.begin(), satisVersion.end());
			info(str);
			if (str.substr(str.length() - 6, str.length()) == target[0]) {
				info("Version check passed!");
			}
			else if (str.substr(str.length() - 6, str.length()) == target[1]) {
				warning("SML is running on the experimental branch, issues may occur!");
			}
			else {
				error("FATAL: Version check failed");
				if (!supressErrors) {
					int ret = MessageBoxA(NULL, "The version of SML that you are using is not compatible with your version of Satisfactory!\nIf SML is not available for the latest version of satisfactory, please yell at SuperCoder to compile one.\nPress Ok to continue at your own discresion or cancel to stop the program.", "SatisfactoryModLoader Fatal Error", MB_OKCANCEL | MB_DEFBUTTON2 | MB_ICONERROR);
					if (ret == IDCANCEL) {
						exit(1);
					}
				}
				else {
					warning("SupressErrors set to true, continuing...");
				}
			}
		}

		void displayCrash(std::string crashText) {
			MessageBoxA(NULL, crashText.c_str(), "SatisfactoryModLoader Crash", MB_ICONERROR);
			abort();
		}
	}
}