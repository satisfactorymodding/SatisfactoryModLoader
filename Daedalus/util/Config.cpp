#include <stdafx.h>
#include <string>
#include <iostream>
#include <fstream>
#include "Config.h"
#include "Utility.h"
#include "json.hpp"

// https://github.com/nlohmann/json
using json = nlohmann::json;

bool loadConsole = true;
bool debugOutput = false;

extern void readConfig() {
	log(LogType::Normal, "Finding config file...");
	std::ifstream config("config.cfg");
	std::string line;
	// see if a config file exists
	if (config.good()) {
		if (config.is_open()) {
			log(LogType::Normal, "Reading the config file");
			
			std::string contents;
			// read the config file line by line
			while (getline(config, line)) {
				contents += line;
			}

			auto j = json::parse(contents);
			loadConsole = j["Console"];
			debugOutput = j["Debug"];
		}
	}
	// create a config file if does not exist
	else {
		log(LogType::Error, "No config file found!");
		log(LogType::Normal, "Creating new config file...");
		std::ofstream configOut("config.cfg");
		if (configOut.is_open()) {
			auto j = R"(
{
	"Console": true,
	"Debug": false
}
				)";
			configOut << j;
			loadConsole = true;
			debugOutput = false;
		}
	}
}