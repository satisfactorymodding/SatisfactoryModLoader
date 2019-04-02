#include <stdafx.h>
#include <string>
#include <iostream>
#include <fstream>
#include "Config.h"
#include "Utility.h"
#include "json.hpp"

// https://github.com/nlohmann/json
using json = nlohmann::json;

extern void readConfig() {
	info("Finding config file...");
	std::ifstream config("config.cfg");
	std::string line;
	// see if a config file exists
	if (config.good()) {
		if (config.is_open()) {
			info("Reading the config file");
			
			std::string contents;
			// read the config file line by line
			while (getline(config, line)) {
				contents += line;
			}
			try {
				auto j = json::parse(contents);
				loadConsole = j["Console"];
				debugOutput = j["Debug"];
				supressErrors = j["SupressErrors"];
			} catch (std::exception& e) {
				std::string err = e.what();
				std::string msg = "There was a fatal error parsing the config file! Please make sure your config file is proper JSON.\nIf you cannot find the issue, simply delete the config file and SML will make a new one with the default values.\nDetailed Error:\n\n" + err + "\n\nPress Ok to exit.";
				int ret = MessageBoxA(NULL, msg.c_str(), "SatisfactoryModLoader Fatal Error", MB_ICONERROR);
				exit(0);
			}
		}
	}
	// create a config file if does not exist
	else {
		error("No config file found!");
		info("Creating new config file...");
		std::ofstream configOut("config.cfg");
		if (configOut.is_open()) {
			auto j = R"({
	"Console": true,
	"Debug": false,
	"SupressErrors": false
})";
			configOut << j;
			loadConsole = true;
			debugOutput = false;
			supressErrors = false;
		}
	}
}