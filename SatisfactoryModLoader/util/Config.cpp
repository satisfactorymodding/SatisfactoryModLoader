#include "stdafx.h"
#include "Config.h"
#include "Utility.h"
#include <string>
#include <iostream>
#include <fstream>

bool loadConsole = true;
bool debugOutput = false;

extern void readConfig() {
	log(LogType::Normal, "Finding config file...");
	std::ifstream config("config.cfg");
	std::string line;
	if (config.good()) { // see if a config file exists
		if (config.is_open()) {
			log(LogType::Normal, "Reading the config file!");
			while (getline(config, line)) { // read the config file line by linee
				if (!(line.substr(0, 1) == "#")) {
					size_t seperator = line.find(":"); // separate string into a id/value pair
					std::string id = line.substr(0, seperator);
					std::string value = line.substr(seperator + 1, std::string::npos);
					if (id == "Console") {
						if (value == "false") { //see if console is false
							loadConsole = false;
						}
						else {
							loadConsole = true;
						}
					}
					else if (id == "Debug") {
						if (value == "true") { //see if debug output is true
							debugOutput = true;
						}
						else {
							debugOutput = false;
						}
					}
				}
			}
		}
	}
	else { // create a config file if does not exist
		log(LogType::Error, "No config file found!");
		log(LogType::Normal, "Creating new config file...");
		std::ofstream configOut("config.cfg");
		if (configOut.is_open()) {
			configOut << "# SatisfactoryModLoader config file" << "\n\n";
			configOut << "# Toggles the console's visibility after launching Satisfactory." << "\n";
			configOut << "Console:true" << "\n";
			configOut << "# Enable debug output for SML to display extra info in the console." << "\n";
			configOut << "Debug:false" << "\n";
			loadConsole = true;
			debugOutput = false;
		}
	}
}