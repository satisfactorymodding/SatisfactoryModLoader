#include <stdafx.h>
#include "EnvironmentValidity.h"
#include <string>
#include <Windows.h>
#include <experimental/filesystem>

namespace SML {
	namespace Utility {
		void checkForValidEnvironment() {
			// Get the execution path (\FactoryGame\Binaries\Win64\FactoryGame.exe)
			char path_c[MAX_PATH];
			GetModuleFileNameA(NULL, path_c, MAX_PATH);
			std::string path = std::string(path_c);			 // ..\FactoryGame\Binaries\Win64\.exe
			path = path.substr(0, path.find_last_of("/\\")); // ..\FactoryGame\Binaries\Win64
			path = path.substr(0, path.find_last_of("/\\")); // ..\FactoryGame\Binaries
			path = path.substr(0, path.find_last_of("/\\")); // ..\FactoryGame
			path = path + "\\Content\\Paks";

			for(const auto &entry : std::experimental::filesystem::directory_iterator(path)) {
				if (entry.path().extension().string() == ".pak") {
					if (entry.path().filename().string() != "FactoryGame-WindowsNoEditor") {

					}
				}
			}
		}
	};
};