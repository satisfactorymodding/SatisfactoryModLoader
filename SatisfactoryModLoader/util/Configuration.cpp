#include <stdafx.h>
#include "Configuration.h"
#include <util/Utility.h>

Configuration::Configuration(const char* name) {
	_name = std::string(name);
	_name.append(".cfg");
}

Configuration::~Configuration() {
	_fileInput.close();
	_fileOutput.close();
}

void Configuration::save() {
	_fileOutput.open(_name);

	try {
		if (_fileOutput.is_open()) {
			_fileOutput << _data.dump(4);
		}
	}
	catch (std::exception& e) {
		std::string err = e.what();
		int ret = MessageBoxA(NULL, err.c_str(), "SatisfactoryModLoader Config Saving Error", MB_ICONERROR);
		exit(0);
	}

	_fileOutput.close();
}

void Configuration::load() {
	_fileInput.open(_name);
	_contents = "";

	std::string line;
	try {
		while (getline(_fileInput, line)) {
			_contents += line;
		}

		info(_contents);

		_data = json::parse(_contents);
	}
	catch (std::exception& e) {
		std::string err = e.what();
		int ret = MessageBoxA(NULL, err.c_str(), "SatisfactoryModLoader Config Loading Error", MB_ICONERROR);
		exit(0);
	}

	_fileInput.close();
}

bool Configuration::exists() {
	std::ifstream config(_name);
	bool good = config.good();
	config.close();
	return good;
}