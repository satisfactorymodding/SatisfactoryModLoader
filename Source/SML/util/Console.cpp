#include "Console.h"
#include "SatisfactoryModLoader.h"
#include "Logging.h"

void SML::InitConsole() {
	const SML::FSMLConfiguration& config = GetSmlConfig();
	if (config.bConsoleWindow) {
		EnableConsole();
	}
}

void SML::NotifyFatalError(const FString& Message) {
	FPlatformMisc::MessageBoxExt(EAppMsgType::Ok, *FString::Printf(TEXT("%s\nClick OK to exit."), *Message), TEXT("SatisfactoryModLoader"));
}

#ifdef PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include "Windows.h"
void SML::EnableConsole() {
	SML::Logging::info(TEXT("Enabling Console Window..."));
	AllocConsole();
	ShowWindow(GetConsoleWindow(), SW_SHOW);
	
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);
	freopen_s(&fp, "CONOIN$", "r", stdin);
	std::cout.clear();
	std::clog.clear();
	std::cerr.clear();
	std::cin.clear();
	
	HANDLE hConOut = CreateFile(_T("CONOUT$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE hConIn = CreateFile(_T("CONIN$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	SetStdHandle(STD_OUTPUT_HANDLE, hConOut);
	SetStdHandle(STD_ERROR_HANDLE, hConOut);
	SetStdHandle(STD_INPUT_HANDLE, hConIn);
	std::wcout.clear();
	std::wclog.clear();
	std::wcerr.clear();
	std::wcin.clear();
	
	SML::Logging::info(TEXT("Console Window enabled!"));
}
#else
void SML::EnableConsole() {
}
#endif
