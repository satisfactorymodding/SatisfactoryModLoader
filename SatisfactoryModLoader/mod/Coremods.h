#pragma once
#include <string>
#include <vector>

namespace SML {
	namespace Mod {
		extern std::vector<std::string> coremodList;

		extern std::vector<std::string> delayedCoremods;

		void startLoadingCoremods(const char* currentPath);

		void loadCoremodsInternal(std::string path);

	};
};