#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <util/json.hpp>
#include <util/Utility.h>

using json = nlohmann::json;

class Configuration {
public:
	Configuration(const char* name);
	~Configuration();

	template<typename T>
	void set(const char* name, T value) {
		_data[name] = value;
	}

	template<typename T>
	T get(const char* name) {
		if (_data.contains(name)) {
			return _data[name];
		}
		else {
			error("Key does not exist: ", name);
			return NULL;
		}
	}

	void save();
	void load();
	bool exists();

private:
	std::string _defaultPath = "config\\";
	std::string _name;
	std::ifstream _fileInput;
	std::ofstream _fileOutput;
	std::string _contents;
	json _data;
};