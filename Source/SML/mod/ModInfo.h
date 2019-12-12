#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "mod/version.h"
#include "util/json.hpp"

using json = nlohmann::json;
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

			static FModInfo createFromJson(json& object);
			static FModInfo createDummyInfo(const std::wstring& modid);
		};
	}
}
