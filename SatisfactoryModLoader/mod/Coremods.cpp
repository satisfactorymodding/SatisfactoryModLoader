#include <stdafx.h>
#include "Coremods.h"
#include <Windows.h>
#include <string>
#include <filesystem>
#include <util/Utility.h>
#include "zip/MemoryModule.h"
#include <util/EnvironmentValidity.h>

namespace SML {
	namespace Mod {
		std::vector<std::string> coremodList;
		std::vector<std::string> delayedCoremods;

		void startLoadingCoremods() {
			loadCoremodsInternal(Utility::getCoreModPath());
			loadCoremodsInternal(Utility::getHiddenCoreModPath());
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

		void loadMemoryCoreMod(void *data, size_t size, std::string name) {
			HMEMORYMODULE hLib = MemoryLoadLibrary(data, size);

			if (hLib == NULL) {
				Utility::error("Error loading library from memory: ", GetLastError());
				return;
			}

			// TODO Support ZIP loaded memory mods
			/*
			if (MemoryGetProcAddress(hLib, "DELAYED_LOAD")) {
				Utility::warning("Warning: Coremod loaded -> ", entry.path().filename(), " (DELAYED_LOAD). Please remove coremods before submitting bug reports!");
				MemoryFreeLibrary(hLib);
				delayedMemoryCoremods.push_back(hLib);
				return;
			}
			*/

			Utility::warning("Warning: Coremod loaded -> ", name, ". Please remove coremods before submitting bug reports!");
			coremodList.push_back(name);
		}
	}
}