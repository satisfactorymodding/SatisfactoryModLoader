#include "mod/ModInfo.h"
#include "SatisfactoryModLoader.h"
#include "util/Logging.h"
#include "util/Utility.h"

using ModInfo = SML::Mod::FModInfo;

void readDependencies(std::unordered_map<std::wstring, FVersionRange>& result, const FJsonObject& dependencies) {
	for (auto& dependency : dependencies.Values) {
		FString resultValue;
		if (dependency.Value.Get()->TryGetString(resultValue)) {
			result.insert({ *dependency.Key, FVersionRange(*resultValue) });
		}
	}
};

std::vector<std::wstring> readAuthors(const TArray<TSharedPtr<FJsonValue>>& arr) {
	std::vector<std::wstring> resultVec;
	for (const TSharedPtr<FJsonValue>& element : arr) {
		if (element.IsValid()) {
			resultVec.push_back(*element.Get()->AsString());
		}
	}
	return resultVec;
}

bool ModInfo::isValid(const FJsonObject& object, const path& filePath) {
	bool isInfoValid = true;
	if (!object.HasTypedField<EJson::String>("mod_reference")) {
		SML::Logging::error("\"mod_reference\" not found in mod ", filePath);
		isInfoValid = false;
	}
	if (!object.HasTypedField<EJson::String>("name")) {
		SML::Logging::warning("\"name\" not found in mod ", filePath);
	}
	if (!object.HasTypedField<EJson::String>("version")) {
		SML::Logging::error("\"version\" not found in mod ", filePath);
		isInfoValid = false;
	}
	if (!object.HasTypedField<EJson::String>("description")) {
		SML::Logging::warning("\"description\" not found in mod ", filePath);
	}
	if (!object.HasTypedField<EJson::Array>("authors")) {
		SML::Logging::warning("\"authors\" not found in mod ", filePath);
	}
	if (!object.HasTypedField<EJson::Object>("objects")) {
		SML::Logging::error("\"objects\" not found in mod ", filePath);
		isInfoValid = false;
	}
	return isInfoValid;
}

ModInfo ModInfo::createFromJson(const FJsonObject& object) {
	FModInfo modInfo = FModInfo{
		*object.GetStringField(TEXT("mod_reference")),
		*object.GetStringField(TEXT("name")),
		FVersion(*object.GetStringField(TEXT("version"))),
		*object.GetStringField(TEXT("description")),
		readAuthors(object.GetArrayField(TEXT("authors")))
	};
	const TSharedPtr<FJsonObject>& dependencies = object.GetObjectField(TEXT("dependencies"));
	if (dependencies.IsValid()) {
		readDependencies(modInfo.dependencies, *dependencies.Get());
	}
	const TSharedPtr<FJsonObject>& optionalDependencies = object.GetObjectField(TEXT("optional_dependencies"));
	if (optionalDependencies.IsValid()) {
		readDependencies(modInfo.optionalDependencies, *optionalDependencies.Get());
	}
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

