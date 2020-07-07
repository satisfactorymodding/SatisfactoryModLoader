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
	freopen_s(&fp, "CONOIN$", "r", stdin);
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);
	SML::Logging::info(TEXT("Console Window enabled!"));
}
#else
void SML::EnableConsole() {
}
#endif