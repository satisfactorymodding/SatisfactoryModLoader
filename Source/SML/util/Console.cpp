#include "Console.h"

void SML::initConsole() {
	auto config = getSMLConfig();
	if (config.consoleWindow) {
		enableConsole();
	}
	if (config.fullLog) {
		enableFullLog();
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

void SML::enableFullLog() {
	SML::Logging::info(TEXT("Enable Full Log"));
	freopen("game.log", "r", stdin);
	freopen("game.log", "w", stdout);
	freopen("game.log", "w", stderr);
}
