#include "mod/ModInfo.h"
#include <regex>
#include "SatisfactoryModLoader.h"
#include "util/Logging.h"
#include "util/Utility.h"

bool ReadDependenciesInfo(TMap<FString, FVersionRange>& ResultDependenciesMap, const FJsonObject& DependenciesObject, const FString& ModReference, FString& OutFailureReason) {
	for (auto& DependencyPair : DependenciesObject.Values) {
		const FString& DependencyModReference = DependencyPair.Key;
		//Disallow sorting dependencies to be specified from data.json, they are internal only.
		if (!FModInfo::IsModIdValid(DependencyModReference)) {
			OutFailureReason = TEXT("Invalid ModReference format in dependency");
			return false;
		}
		//Value if dependency should always be a string
		if (DependencyPair.Value.Get()->Type == EJson::String) {
			const FString VersionRangeString = DependencyPair.Value.Get()->AsString();
			FVersionRange DependencyVersionRange{};
			const bool bVersionRangeParsed = DependencyVersionRange.ParseVersionRange(VersionRangeString, OutFailureReason);
			if (!bVersionRangeParsed) {
				return false;
			}
			ResultDependenciesMap.Add(DependencyModReference, DependencyVersionRange);
		} else {
			OutFailureReason = TEXT("Expected String in \"dependencies\" object value");
			return false;
		}
	}
	return true;
};

TArray<FString> ReadAuthorsArray(const TArray<TSharedPtr<FJsonValue>>& Array, const FString& ModReference) {
	TArray<FString> ResultAuthorsArray;
	for (const TSharedPtr<FJsonValue>& Element : Array) {
		if (Element.Get()->Type == EJson::String) {
			ResultAuthorsArray.Add(Element.Get()->AsString());
		} else {
			SML::Logging::warning(TEXT("Found non-string element in \"authors\" array for mod "), *ModReference);
		}
	}
	return ResultAuthorsArray;
}

#define DEFINE_JSON_STRING_FIELD(VariableName, Name) CHECK_JSON_FIELD_TYPE(Name, String, FString, VariableName);

#define CHECK_JSON_FIELD_TYPE(Name, TypeExpected, VariableType, VariableName)\
	FString VariableName;\
	if (!Object.HasTypedField<EJson::TypeExpected>(TEXT(#Name))) {\
		OutFailureReason = TEXT(#Name " not found or has incorrect type (expected: " #TypeExpected ")");\
		return false;\
	}\
	VariableName = Object.Get##TypeExpected##Field(TEXT(#Name));

bool FModInfo::CreateFromJson(const FJsonObject& Object, FModInfo& ModInfo, FString& OutFailureReason) {
	//Ensure that we have all basic attributes
	DEFINE_JSON_STRING_FIELD(ModReference, mod_reference);
	DEFINE_JSON_STRING_FIELD(ModDisplayName, name);
	DEFINE_JSON_STRING_FIELD(ModVersionString, version);

	if (!Object.HasTypedField<EJson::Array>(TEXT("objects"))) {
		OutFailureReason = TEXT("\"objects\" field not found in data json");
		return false;
	}

	ModInfo.Name = ModDisplayName;
	ModInfo.Modid = ModReference;
	if (!IsModIdValid(ModReference)) {
		OutFailureReason = TEXT("Invalid ModReference (only alphanumerical characters and underscores are allowed)");
		return false;
	}
	
	FVersion ModVersion{};
	const bool bVersionParsed = ModVersion.ParseVersion(ModVersionString, OutFailureReason);
	ModInfo.Version = ModVersion;
	if (!bVersionParsed) {
		return false;
	}

	if (Object.HasTypedField<EJson::Object>(TEXT("dependencies"))) {
		const TSharedPtr<FJsonObject>& Dependencies = Object.GetObjectField(TEXT("dependencies"));
		const bool bParseSuccess = ReadDependenciesInfo(ModInfo.Dependencies, *Dependencies.Get(), ModReference, OutFailureReason);
		if (!bParseSuccess) {
			return false;
		}
	}
	
	if (Object.HasTypedField<EJson::Object>(TEXT("optional_dependencies"))) {
		const TSharedPtr<FJsonObject>& OptionalDependencies = Object.GetObjectField(TEXT("optional_dependencies"));
		const bool bParseSuccess = ReadDependenciesInfo(ModInfo.OptionalDependencies, *OptionalDependencies.Get(), ModReference, OutFailureReason);
		if (!bParseSuccess) {
			return false;
		}
	}
	
	if (Object.HasTypedField<EJson::String>(TEXT("description"))) {
		ModInfo.Description = Object.GetStringField(TEXT("description"));
	} else {
		SML::Logging::warning(TEXT("Description is missing for mod "), *ModReference);
	}

	if (Object.HasTypedField<EJson::Array>(TEXT("authors"))) {
		const TArray<TSharedPtr<FJsonValue>> AuthorsArray = Object.GetArrayField(TEXT("authors"));
		ModInfo.Authors = ReadAuthorsArray(AuthorsArray, ModReference);
	} else {
		SML::Logging::warning(TEXT("Authors list is missing for mod "), *ModReference);
	}
	
	if (Object.HasTypedField<EJson::String>(TEXT("credits"))) {
		ModInfo.Credits = Object.GetStringField(TEXT("credits"));
	}
	
	//By default, we require mod to be installed on client side with version >=ServerVersion
	ModInfo.RemoteVersion.bAcceptAnyRemoteVersion = false;
	ModInfo.RemoteVersion.RemoteVersion = FVersionRange::CreateRangeWithMinVersion(ModInfo.Version);

	//True if we can accept any remote version, even if mod doesn't exist on remote
	if (Object.HasTypedField<EJson::Boolean>(TEXT("accept_any_remote_version"))) {
		ModInfo.RemoteVersion.bAcceptAnyRemoteVersion = Object.GetBoolField(TEXT("accept_any_remote_version"));
	}
	//Remote version overrides accept any remote version and allows any predicate for remote version
	if (Object.HasTypedField<EJson::String>(TEXT("remote_version"))) {
		const FString RemoteVersion = Object.GetStringField(TEXT("remote_version"));
		FVersionRange RemoteVersionRange{};
		const bool bRemoteVersionParsed = RemoteVersionRange.ParseVersionRange(RemoteVersion, OutFailureReason);
		if (!bRemoteVersionParsed) {
			return false;
		}
		ModInfo.RemoteVersion.bAcceptAnyRemoteVersion = false;
		ModInfo.RemoteVersion.RemoteVersion = RemoteVersionRange;
	}
	
	if (Object.HasTypedField<EJson::Object>(TEXT("resources"))) {
		FModResources ModResources{};
		const TSharedPtr<FJsonObject>& ResourcesObject = Object.GetObjectField(TEXT("resources"));
		if (ResourcesObject->HasTypedField<EJson::String>(TEXT("icon"))) {
			ModResources.ModIconPath = ResourcesObject->GetStringField(TEXT("icon"));
		}
		ModInfo.ModResources = ModResources;
	}
	return true;
};

FModInfo FModInfo::CreateDummyInfo(const FString& modid) {
	return FModInfo{
		modid, modid,
		FVersion(1, 0, 0),
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

