#include <stdafx.h>
#include "Coremods.h"
#include <Windows.h>
#include <string>
#include <filesystem>
#include <util/Utility.h>

namespace SML {
	namespace Mod {
		std::vector<std::string> coremodList;
		std::vector<std::string> delayedCoremods;

		void startLoadingCoremods(const char* currentPath) {
			std::string appPath(currentPath);
			size_t pos = appPath.find_last_of('\\');
			CreateDirectoryA((appPath.substr(0, pos) + "\\coremods").c_str(), NULL); //create the directory if it doesn't exist
			std::string path = appPath.substr(0, pos) + "\\coremods";

			loadCoremodsInternal(path);
		}

		void loadCoremodsInternal(std::string path) {
			std::string rootPath = path + "\\";

			for (const auto & entry : std::experimental::filesystem::directory_iterator(path)) {
				if (entry.path().extension().string() == ".dll") {
					std::string libPath = rootPath + entry.path().filename().string();
					HMODULE hLib = LoadLibraryExA(libPath.c_str(), NULL, DONT_RESOLVE_DLL_REFERENCES);

					if (GetProcAddress(hLib, "DELAYED_LOAD")) {
						Utility::warning("Warning: Coremod loaded -> ", entry.path().filename(), " (DELAYED_LOAD). Please remove coremods before submitting bug reports!");
						FreeLibrary(hLib);
						delayedCoremods.push_back(libPath);
						continue;
					}

					FreeLibrary(hLib);
					LoadLibraryA(libPath.c_str());

					Utility::warning("Warning: Coremod loaded -> ", entry.path().filename(), ". Please remove coremods before submitting bug reports!");
					coremodList.push_back(entry.path().filename().string());
				}
			}
		}
	}
}