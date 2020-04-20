#include "mod/ModInfo.h"
#include "SatisfactoryModLoader.h"
#include "util/Logging.h"
#include "util/Utility.h"

using ModInfo = SML::Mod::FModInfo;

void readDependencies(TMap<FString, FVersionRange>& result, const FJsonObject& dependencies) {
	for (auto& dependency : dependencies.Values) {
		FString resultValue;
		if (dependency.Value.Get()->TryGetString(resultValue)) {
			result.Add(dependency.Key, FVersionRange(resultValue));
		}
	}
};

TArray<FString> readAuthors(const TArray<TSharedPtr<FJsonValue>>& arr) {
	TArray<FString> resultVec;
	for (const TSharedPtr<FJsonValue>& element : arr) {
		if (element.IsValid()) {
			resultVec.Add(element.Get()->AsString());
		}
	}
	return resultVec;
}

bool ModInfo::isValid(const FJsonObject& object, const FString& filePath) {
	bool isInfoValid = true;
	if (!object.HasTypedField<EJson::String>("mod_reference")) {
		SML::Logging::error(*FString::Printf(TEXT("\"mod_reference\" not found in mod %s"), *filePath));
		isInfoValid = false;
	}
	if (!object.HasTypedField<EJson::String>("name")) {
		SML::Logging::warning(*FString::Printf(TEXT("\"name\" not found in mod %s"), *filePath));
	}
	if (!object.HasTypedField<EJson::String>("version")) {
		SML::Logging::error(*FString::Printf(TEXT("\"version\" not found in mod %s"), *filePath));
		isInfoValid = false;
	}
	if (!object.HasTypedField<EJson::String>("description")) {
		SML::Logging::warning(*FString::Printf(TEXT("\"description\" not found in mod %s"), *filePath));
	}
	if (!object.HasTypedField<EJson::Array>("authors")) {
		SML::Logging::warning(*FString::Printf(TEXT("\"authors\" not found in mod %s"), *filePath));
	}
	if (!object.HasTypedField<EJson::Array>("objects")) {
		SML::Logging::error(*FString::Printf(TEXT("\"objects\" not found in mod %s"), *filePath));
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
	if (object.HasField(TEXT("dependencies"))) {
		const TSharedPtr<FJsonObject>& dependencies = object.GetObjectField(TEXT("dependencies"));
		if (dependencies.IsValid()) {
			readDependencies(modInfo.dependencies, *dependencies.Get());
		}
	}
	if (object.HasField(TEXT("optional_dependencies"))) {
		const TSharedPtr<FJsonObject>& optionalDependencies = object.GetObjectField(TEXT("optional_dependencies"));
		if (optionalDependencies.IsValid()) {
			readDependencies(modInfo.optionalDependencies, *optionalDependencies.Get());
		}
	}
	return modInfo;
};

ModInfo ModInfo::createDummyInfo(const FString& modid) {
	return FModInfo{
		modid, modid,
		FVersion(TEXT("1.0.0")),
		TEXT("No description provided"),
		{TEXT("Unknown")}
	};
};

