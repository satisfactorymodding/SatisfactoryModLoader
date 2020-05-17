#include "Console.h"
#include "SatisfactoryModLoader.h"
#include "Logging.h"

void SML::InitConsole() {
	const SML::FSMLConfiguration& config = GetSmlConfig();
	if (config.bConsoleWindow) {
		EnableConsole();
	}
}

#ifdef PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include "Windows.h"
void SML::EnableConsole() {
	SML::Logging::info(TEXT("Enabling Console Window..."));
	AllocConsole();
	ShowWindow(GetConsoleWindow(), SW_SHOW);
	FILE* fp;
	freopen_s(&fp, "CONOIN$", "r", stdin);
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);
	SML::Logging::info(TEXT("Console Window enabled!"));
}

void SML::NotifyFatalError(const FString& Message) {
	MessageBoxA(NULL, TCHAR_TO_ANSI(*FString::Printf(TEXT("%s\nClick OK to exit."), *Message)), "SatisfactoryModLoader", MB_ICONERROR);
}
#else
void SML::EnableConsole() {
	//TODO: Implementation for other platforms
}
void SML::NotifyFatalError(const FString& Message) {
}
#endif