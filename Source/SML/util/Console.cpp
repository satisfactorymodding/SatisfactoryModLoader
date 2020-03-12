#include "Console.h"
#include "SatisfactoryModLoader.h"
#define WIN32_LEAN_AND_MEAN
#include "Windows.h"
#include "Logging.h"

void SML::initConsole() {
	const SML::FSMLConfiguration& config = getSMLConfig();
	if (config.consoleWindow) {
		enableConsole();
	}
}

void SML::enableConsole() {
	SML::Logging::info(TEXT("Enabling Console Window..."));
	AllocConsole();
	ShowWindow(GetConsoleWindow(), SW_SHOW);
	FILE* fp;
	freopen_s(&fp, "CONOIN$", "r", stdin);
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);
	SML::Logging::info(TEXT("Console Window enabled!"));
}
