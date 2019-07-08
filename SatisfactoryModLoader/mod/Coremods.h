#pragma once
#include <string>
#include <vector>

namespace SML {
	namespace Mod {
		std::vector<const wchar_t*> delayedCoremods;

		void startLoadingCoremods(const char* currentPath);

		void loadCoremodsInternal(std::string path);

	};
};