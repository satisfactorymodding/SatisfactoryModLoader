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

	nlohmann::json readModConfig(std::wstring modid) {
		path configPath = getModConfigFilePath(modid);
		if (!exists(configPath))
			return nlohmann::json(nullptr);
		std::wifstream fileStream(configPath);
		try {
			auto iterator = std::istreambuf_iterator<TCHAR>(fileStream);
			auto endIterator = std::istreambuf_iterator<TCHAR>();
			std::wstring contents{iterator, endIterator};
			return parseJsonLenient(contents);
		} catch (std::exception& ex) {
			SML::Logging::warning("Failed to read mod ", modid, " configuration: ", convertStr(ex.what()));
			return nlohmann::json(nullptr);
		}
	}

	void writeModConfig(std::wstring modid, const nlohmann::json& config) {
		path configPath = getModConfigFilePath(modid);
		std::wofstream fileStream(configPath, std::ios::out);
		try {
			fileStream << config.dump();
			fileStream.close();
		} catch (std::exception& ex) {
			SML::Logging::warning("Failed to write mod ", modid, " configuration: ", convertStr(ex.what()));
		}
	}
}
