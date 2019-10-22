#pragma once
#include <string>
#include <vector>

namespace SML {
	namespace Mod {
		extern std::vector<std::string> coremodList;

		extern std::vector<std::string> delayedCoremods;

		void startLoadingCoremods();

		void loadCoremodsInternal(std::string path);

		void loadMemoryCoreMod(void *data, size_t size, std::string name);
	};
};