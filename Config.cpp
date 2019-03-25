#include "stdafx.h"
#include "Config.h"
#include "DllMain.h"
#include <string>
#include <iostream>
#include <fstream>

bool loadConsole = true;

void readConfig() {
	log("Finding config file...");
	std::ifstream config("config.cfg");
	std::string line;
	if (config.good()) { // see if a config file exists
		if (config.is_open()) {
			log("Reading the config file!");
			while (getline(config, line)) { // read the config file line by linee
				size_t seperator = line.find(":"); // separate string into a id/value pair
				std::string id = line.substr(0, seperator);
				std::string value = line.substr(seperator + 1, std::string::npos);
				if (id == "Console") {
					if (value == "false") { //see if console is false
						loadConsole = false;
						log("You are free to close this window now.");
					}
					else {
						loadConsole = true;
					}
				}
			}
		}
	}
	else { // create a config file if does not exist
		log("No config file found!");
		log("Creating new config file...");
		std::ofstream configOut("config.cfg");
		if (configOut.is_open()) {
			configOut << "Console:true";
			loadConsole = true;
		}
	}
}