#include "Console.h"

void SML::initConsole() {
	auto config = getSMLConfig();
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
