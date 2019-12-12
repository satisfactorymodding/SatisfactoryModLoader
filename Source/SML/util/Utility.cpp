#include "Utility.h"
#include "util/Logging.h"
#include <fstream>
#include <regex>

namespace SML {
	nlohmann::json parseJsonLenient(const std::wstring& input) {
		static std::wregex stripCommentsRegex(TEXT("/\\*([^*]|[\r\n]|(\\*+([^*/]|[\r\n])))*\\*+/"), std::regex::optimize | std::regex::extended);
		std::wstring result = std::regex_replace(input, stripCommentsRegex, TEXT(""));
		return nlohmann::json::parse(result);
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
}
