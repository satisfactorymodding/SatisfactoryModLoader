#include "mod/ModInfo.h"
#include "SatisfactoryModLoader.h"
#include "util/Logging.h"
#include "util/Utility.h"

using ModInfo = SML::Mod::FModInfo;

void readDependencies(std::unordered_map<std::wstring, FVersionRange>& result, json& dependencies) {
	if (!dependencies.is_null()) {
		for (auto& dependency : dependencies.items()) {
			FVersionRange version(convertStr(dependency.value().get<std::string>().c_str()));
			result.insert({ convertStr(dependency.key().c_str()), version });
		}
	}
};

bool ModInfo::isValid(json & object, const path& filePath) {
	bool isInfoValid = true;
	if (object.find("mod_reference") == object.end()) {
		SML::Logging::error("\"mod_reference\" not found in mod ", filePath);
		isInfoValid = false;
	}
	if (object.find("name") == object.end()) {
		SML::Logging::warning("\"name\" not found in mod ", filePath);
	}
	if (object.find("version") == object.end()) {
		SML::Logging::error("\"version\" not found in mod ", filePath);
		isInfoValid = false;
	}
	if (object.find("description") == object.end()) {
		SML::Logging::warning("\"description\" not found in mod ", filePath);
	}
	if (object.find("authors") == object.end()) {
		SML::Logging::warning("\"authors\" not found in mod ", filePath);
	}
	if (object.find("objects") == object.end()) {
		SML::Logging::error("\"objects\" not found in mod ", filePath);
		isInfoValid = false;
	}
	return isInfoValid;
}

ModInfo ModInfo::createFromJson(json& object) {
	FModInfo modInfo = FModInfo{
		convertStr(SML::safe_get<std::string>(object, "mod_reference").c_str()),
		convertStr(SML::safe_get<std::string>(object, "name").c_str()),
		FVersion(convertStr(SML::safe_get<std::string>(object, "version").c_str())),
		convertStr(SML::safe_get<std::string>(object, "description").c_str()),
		convertStr(SML::safe_get<std::string>(object, "authors").c_str())
	};
	readDependencies(modInfo.dependencies, object["dependencies"]);
	readDependencies(modInfo.optionalDependencies, object["optional_dependencies"]);
	return modInfo;
};

ModInfo ModInfo::createDummyInfo(const std::wstring& modid) {
	return FModInfo{
		modid, modid,
		FVersion(TEXT("1.0.0")),
		TEXT("No description provided"),
		TEXT("Unknown")
	};
};

