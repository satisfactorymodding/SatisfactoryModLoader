#pragma once
#include <string>
#include <sstream>
#include "util/json.hpp"
#include "SatisfactoryModLoader.h"

namespace SML {

	path getModConfigFilePath(std::wstring modid);

	/**
	 * Parses given json string into a valid json object
	 * Strips json syntax extensions like commentaries prior to parsing
	 */
	SML_API nlohmann::json parseJsonLenient(const std::wstring& input);

	/**
	 * Parses mod configuration file and returns json object
	 * returns json.null() if config file is missing, unreadable or corrupted
	 * It also supports comments in mod configs
	 */
	SML_API nlohmann::json readModConfig(std::wstring modid);
	
	template<typename First, typename ...Args>
	std::wstring formatStr(First &&arg0, Args &&...args) {
		std::wostringstream stringStream;
		formatInternal(stringStream, arg0, args...);
		return stringStream.str();
	}

	inline void formatInternal(std::wostringstream& stream) {}

	template<typename First, typename ...Args>
	void formatInternal(std::wostringstream& stream, First &&arg0, Args &&...args) {
		stream << std::forward<First>(arg0);
		formatInternal(stream, std::forward<Args>(args)...);
	}
};