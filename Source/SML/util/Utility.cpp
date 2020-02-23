#include "Utility.h"
#include "util/Logging.h"
#include <fstream>
#include <regex>

namespace SML {
	nlohmann::json parseJsonLenient(const std::wstring& input) {
		return nlohmann::json::parse(input);
	}
	
	path getModConfigFilePath(std::wstring modid) {
		path configDirPath = getConfigDirectory();
		std::wstring fileName = formatStr(modid, TEXT(".cfg"));
		return configDirPath / fileName;
	}
	
	nlohmann::json readModConfig(std::wstring modid, const json& defaultValues) {
		path configPath = getModConfigFilePath(modid);
		if (!exists(configPath)) {
			writeModConfig(modid, defaultValues);
			return defaultValues;
		}
		std::wifstream fileStream(configPath);

		auto iterator = std::istreambuf_iterator<TCHAR>(fileStream);
		auto endIterator = std::istreambuf_iterator<TCHAR>();
		std::wstring contents{iterator, endIterator};
		nlohmann::json loadedJson = parseJsonLenient(contents);
		loadedJson = setDefaultValues(loadedJson, defaultValues);
		writeModConfig(modid, loadedJson);
		return loadedJson;
	}

	void writeModConfig(std::wstring modid, const nlohmann::json& config) {
		path configPath = getModConfigFilePath(modid);
		std::wofstream fileStream(configPath, std::ios::out);

		fileStream << config.dump(4);
		fileStream.close();
	}

	nlohmann::json setDefaultValues(nlohmann::json j, const nlohmann::json & defaultValues) {
		for (auto it : defaultValues.items()) {
			auto key = it.key();
			auto value = it.value();

			// Add if not existing
			if (j.find(key) == j.end()) {
				j[key] = value;
				continue;
			}

			if (key.length() < 1 || key[0] != '$') { // ignore type checks if key[0] == '$'
				auto jvalue = j[key];

				// number type check
				if (value.is_number_integer()) {
					if (jvalue.is_number_integer())
						continue;
				}
				else if (value.is_number() && jvalue.is_number()) {
					continue;
				}

				// Override if wrong type
				if (value.type() != j[key].type()) {
					j[key] = value;
					continue;
				}
			}

			// iterate over sub object
			if (value.is_object())
				j[key] = setDefaultValues(j[key], value);
		}

		json jduplicate = j;

		for (auto it : jduplicate.items()) {
			auto key = it.key();

			// Remove if unused
			if (!defaultValues.contains(key))
				j.erase(key);
		}

		return j;
	}
}
