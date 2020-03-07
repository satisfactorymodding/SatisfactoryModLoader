#pragma once

#include "mod/version.h"
#include "Json.h"

using namespace SML::Versioning;

namespace SML {
	namespace Mod {
		struct FModInfo {
			FString modid;
			FString name;
			FVersion version;
			FString description;
			TArray<FString> authors;
			TMap<FString, FVersionRange> dependencies;
			TMap<FString, FVersionRange> optionalDependencies;

			static bool isValid(const FJsonObject& object, const FString& filePath);
			static FModInfo createFromJson(const FJsonObject& object);
			static FModInfo createDummyInfo(const FString& modid);
		};
	}
}
