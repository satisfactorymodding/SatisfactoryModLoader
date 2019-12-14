#include "mod/ModInfo.h"
#include "SatisfactoryModLoader.h"
#include "util/Logging.h"

using ModInfo = SML::Mod::FModInfo;

void readDependencies(std::unordered_map<std::wstring, FVersionRange>& result, json& dependencies) {
	if (!dependencies.is_null()) {
		for (auto& dependency : dependencies.items()) {
			FVersionRange version(convertStr(dependency.value().get<std::string>().c_str()));
			result.insert({ convertStr(dependency.key().c_str()), version });
		}
	}
};

ModInfo ModInfo::createFromJson(json& object) {
	FModInfo modInfo = FModInfo{
		convertStr(object["mod_reference"].get<std::string>().c_str()),
		convertStr(object["name"].get<std::string>().c_str()),
		FVersion(convertStr(object["version"].get<std::string>().c_str())),
		convertStr(object["description"].get<std::string>().c_str()),
		convertStr(object["authors"].get<std::string>().c_str())
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

