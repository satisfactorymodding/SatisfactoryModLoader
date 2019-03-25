#pragma once
#include <string>

void log(std::string msg, bool endLine = true, bool showHeader = true, const char* event = "");

void logError(std::string msg, bool endLine = true, bool showHeader = true, const char* event = "");