#pragma once
#include <string>

namespace SML {
	namespace Mod {
		void startLoadingCoremods(const char* currentPath);

		void loadCoremodsInternal(std::string path);
	};
};