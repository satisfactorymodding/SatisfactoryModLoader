#include "Config.h"
#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>

bool LOADCONSOLE = true;

void readConfig() {
	std::cout << "[Daedalus] Finding config file..." << std::endl;
	std::ifstream config("config.cfg");
	std::string line;
	if (config.good()) { // see if a config file exists
		if (config.is_open()) {
			std::cout << "[Daedalus] Reading found config file!" << std::endl;
			while (getline(config, line)) { // read the config file line by linee
				size_t seperator = line.find(":"); // separate string into a id/value pair
				std::string id = line.substr(0, seperator); 
				std::string value = line.substr(seperator+1, std::string::npos);
				if (id == "Console") {
					if (value == "false") { //see if console is false
						LOADCONSOLE = false;
						std::cout << "[Daedalus] You are free to close this window now." << std::endl;
					}
					else {
						LOADCONSOLE = true;
					}
				}
			}
		}
	} else { // create a config file if does not exist
		std::cout << "[Daedalus] No config file found!\nCreating new config file..." << std::endl;
		std::ofstream configOut("config.cfg");
		if (configOut.is_open()) {
			configOut << "Console:true";
			LOADCONSOLE = true;
		}
	}
}