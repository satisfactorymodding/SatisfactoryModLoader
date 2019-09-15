#define WIN32_LEAN_AND_MEAN

#include <stdafx.h>
#include <SatisfactoryModLoader.h>
#include "DetoursFwd.h"
#include "Utility.h"
#include <game/Utility.h>
#include <Windows.h>
#include <detours.h>

#include "Objects/UFunction.h"
#include "Objects/UClass.h"
#include "Objects/FFrame.h"
#include "Objects/FMemory.h"

namespace SML {
	namespace Objects {
		bool DataCompare(PBYTE pData, PBYTE bSig, const char* szMask) {
			for (; *szMask; ++szMask, ++pData, ++bSig) {
				if (*szMask == 'x' && *pData != *bSig)
					return false;
			}
			return (*szMask) == 0;
		}

		DWORD_PTR FindPattern(DWORD_PTR dwAddress, DWORD dwSize, const char* pbSig, const char* szMask, long offset) {
			size_t length = strlen(szMask);
			for (size_t i = NULL; i < dwSize - length; i++) {
				if (DataCompare((PBYTE)dwAddress + i, (PBYTE)pbSig, szMask))
					return dwAddress + i + offset;
			}
			return 0;
		}

		void initObjects() {
			DWORD_PTR BaseAddress = (DWORD_PTR)GetModuleHandle(NULL);

			MODULEINFO ModuleInfo;
			GetModuleInformation(GetCurrentProcess(), (HMODULE)BaseAddress, &ModuleInfo, sizeof(ModuleInfo));

			auto GNamesAddress = FindPattern(BaseAddress, ModuleInfo.SizeOfImage,
				"\x48\x8B\x05\x00\x00\x00\x03\x48\x85\xC0\x0F\x85\xB0", "xxx???xxxxxxx", 0);
			auto GNamesOffset = *reinterpret_cast<uint32_t*>(GNamesAddress + 3);
			Objects::FName::names = *reinterpret_cast<Objects::TNameEntryArray**> (GNamesAddress + 7 + GNamesOffset);

			auto GObjectsAddress = FindPattern(BaseAddress, ModuleInfo.SizeOfImage,
				"\x48\x8D\x0D\x00\x00\x00\x04\xE8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xE8\x00\x00\x00\x01", "xxx???xx???xx???xx???x", 0);
			auto GObjectsOffset = *reinterpret_cast<uint32_t*>(GObjectsAddress + 3);
			Objects::UObject::objs = reinterpret_cast<Objects::FUObjectArray*>(GObjectsAddress + 7 + GObjectsOffset);

			FName::fNameConstruct_f = (void (WINAPI*)(void*, const wchar_t*, FName::EFindName)) DetourFindFunction("FactoryGame-Win64-Shipping.exe", "FName::FName");
			UClass::findFunction_f = (UFunction* (WINAPI*)(UObject*, FName)) DetourFindFunction("FactoryGame-Win64-Shipping.exe", "UObject::FindFunction");
		
			FMemory::init();
		}
	}

	namespace Utility {
		std::ofstream logFile;

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
		void checkVersion(const int target) {
			std::wstring satisVersion{ call<&Objects::BuildSettings::GetBuildVersion>() };
			std::string str(satisVersion.begin(), satisVersion.end());
			int version = std::atoi(str.substr(str.length() - 6, str.length()).c_str());
			if (version == target) {
				info("Version check passed!");
			}
			else if (version > target) {
				warning("SML is out of date with the latest Satisfactory! Report any issues on the discord!");
			}
			else if (version < target){
				error("WARNING: Version check failed");
				if (!supressErrors) {
					int ret = MessageBoxA(NULL, "The version of Satisfactory that you are running is too old for the current version of SML! Please update Satisfactory otherwise SML may run into errors. \nPress Ok to continue at your own discresion or cancel to stop the program.", "SatisfactoryModLoader Warning", MB_OKCANCEL | MB_DEFBUTTON2 | MB_ICONEXCLAMATION);
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
			MessageBoxA(NULL, (crashText + "\nPress OK to exit.").c_str(), "SatisfactoryModLoader Crash", MB_ICONERROR);
			abort();
		}
	}
}