#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "mod/version.h"
#include <filesystem>
#include "Json.h"

using namespace std::experimental::filesystem;

using namespace SML::Versioning;

namespace SML {
	namespace Mod {
		struct FModInfo {
			std::wstring modid;
			std::wstring name;
			FVersion version;
			std::wstring description;
			std::vector<std::wstring> authors;
			std::unordered_map<std::wstring, FVersionRange> dependencies;
			std::unordered_map<std::wstring, FVersionRange> optionalDependencies;

			static bool isValid(const FJsonObject& object, const path& filePath);
			static FModInfo createFromJson(const FJsonObject& object);
			static FModInfo createDummyInfo(const std::wstring& modid);
		};
	}
}
