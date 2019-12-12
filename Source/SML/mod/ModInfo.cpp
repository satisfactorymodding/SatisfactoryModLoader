#include "mod/ModInfo.h"
#include "SatisfactoryModLoader.h"

using ModInfo = SML::Mod::FModInfo;

void readDependencies(std::unordered_map<std::wstring, FVersionRange>& result, json& dependencies) {
	if (!dependencies.is_null()) {
		for (auto& dependency : dependencies.items()) {
			FVersionRange version(dependency.value().get<std::wstring>());
			result.insert({ convertStr(dependency.key().c_str()), version });
		}
	}
};

ModInfo ModInfo::createFromJson(json& object) {
	FModInfo modInfo = FModInfo{
		object["mod_reference"].get<std::wstring>(),
		object["name"].get<std::wstring>(),
		FVersion(object["version"].get<std::wstring>()),
		object["description"].get<std::wstring>(),
		object["authors"].get<std::vector<std::wstring>>()
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
		{TEXT("Unknown")}
	};
};

