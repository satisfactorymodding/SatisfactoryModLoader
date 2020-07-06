#include "mod/ModInfo.h"

#include <regex>

#include "SatisfactoryModLoader.h"
#include "util/Logging.h"
#include "util/Utility.h"

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

bool FModInfo::IsValid(const FJsonObject& object, const FString& filePath) {
	bool isInfoValid = true;
	if (!object.HasTypedField<EJson::String>(TEXT("mod_reference"))) {
		SML::Logging::error(*FString::Printf(TEXT("\"mod_reference\" not found in mod %s"), *filePath));
		isInfoValid = false;
	}
	if (!IsModIdValid(object.GetStringField(TEXT("mod_reference")))) {
		SML::Logging::error(*FString::Printf(TEXT("\"mod_reference\" doesn't match the pattern for mod %s"), *filePath));
		isInfoValid = false;
	}
	if (!object.HasTypedField<EJson::String>("name")) {
		SML::Logging::warning(*FString::Printf(TEXT("\"name\" not found in mod %s"), *filePath));
	}
	if (!object.HasTypedField<EJson::String>(TEXT("version"))) {
		SML::Logging::error(*FString::Printf(TEXT("\"version\" not found in mod %s"), *filePath));
		isInfoValid = false;
	}
	if (!object.HasTypedField<EJson::String>(TEXT("description"))) {
		SML::Logging::warning(*FString::Printf(TEXT("\"description\" not found in mod %s"), *filePath));
	}
	if (!object.HasTypedField<EJson::Array>(TEXT("authors"))) {
		SML::Logging::warning(*FString::Printf(TEXT("\"authors\" not found in mod %s"), *filePath));
	}
	if (!object.HasTypedField<EJson::Array>(TEXT("objects"))) {
		SML::Logging::error(*FString::Printf(TEXT("\"objects\" not found in mod %s"), *filePath));
		isInfoValid = false;
	}
	return isInfoValid;
}

FModInfo FModInfo::CreateFromJson(const FJsonObject& object) {
	FModInfo modInfo = FModInfo{
		*object.GetStringField(TEXT("mod_reference")),
		*object.GetStringField(TEXT("name")),
		FVersion(*object.GetStringField(TEXT("version"))),
		*object.GetStringField(TEXT("description")),
		readAuthors(object.GetArrayField(TEXT("authors")))
	};
	
	//By default, we require mod to be installed on client side with version >=ServerVersion
	modInfo.RemoteVersion.bAcceptAnyRemoteVersion = false;
	modInfo.RemoteVersion.RemoteVersion = FVersionRange(modInfo.Version, EVersionComparisonOp::GREATER_EQUALS);
	
	if (object.HasField(TEXT("credits"))) {
		modInfo.Credits = object.GetStringField(TEXT("credits"));
	}
	
	if (object.HasField(TEXT("remote_version"))) {
		const FString RemoteVersion = object.GetStringField(TEXT("remote_version"));
		if (RemoteVersion == TEXT("*")) {
			modInfo.RemoteVersion.bAcceptAnyRemoteVersion = true;
		} else {
			modInfo.RemoteVersion.bAcceptAnyRemoteVersion = false;
			modInfo.RemoteVersion.RemoteVersion = FVersionRange(RemoteVersion);
		}
	}
	
	if (object.HasField(TEXT("resources"))) {
		FModResources ModResources{};
		const TSharedPtr<FJsonObject>& ResourcesObject = object.GetObjectField(TEXT("resources"));
		if (ResourcesObject->HasField(TEXT("icon")))
			ModResources.ModIconPath = ResourcesObject->GetStringField(TEXT("icon"));
		modInfo.ModResources = ModResources;
	}
	if (object.HasField(TEXT("dependencies"))) {
		const TSharedPtr<FJsonObject>& dependencies = object.GetObjectField(TEXT("dependencies"));
		if (dependencies.IsValid()) {
			readDependencies(modInfo.Dependencies, *dependencies.Get());
		}
	}
	if (object.HasField(TEXT("optional_dependencies"))) {
		const TSharedPtr<FJsonObject>& optionalDependencies = object.GetObjectField(TEXT("optional_dependencies"));
		if (optionalDependencies.IsValid()) {
			readDependencies(modInfo.OptionalDependencies, *optionalDependencies.Get());
		}
	}
	return modInfo;
};

FModInfo FModInfo::CreateDummyInfo(const FString& modid) {
	return FModInfo{
		modid, modid,
		FVersion(TEXT("1.0.0")),
		TEXT("No description provided"),
		{TEXT("Unknown")},
		TEXT("No credits provided"),
		FModRemoteVersion{FVersionRange{}, true}	
	};
}

std::wregex ModReferenceRegex(TEXT("^([a-zA-Z][a-zA-Z0-9_]*)$"));

bool FModInfo::IsModIdValid(const FString& ModId) {
	std::wsmatch Match;
	const std::wstring WideString(*ModId);
	return std::regex_match(WideString, Match, ModReferenceRegex);
};

