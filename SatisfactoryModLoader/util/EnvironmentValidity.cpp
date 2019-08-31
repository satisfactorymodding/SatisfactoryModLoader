#include <stdafx.h>
#include "EnvironmentValidity.h"
#include <string>
#include <Windows.h>
#include <filesystem>
#include <fstream>
#include <util/Utility.h>

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
			std::string rootpath = path;
			path = path + "\\Content\\Paks";
			std::string pakfilepath = path;
			info(path);
			std::string originalSigLoc = path.append("\\FactoryGame-WindowsNoEditor.sig");
			std::filesystem::path originalSigPath(originalSigLoc);
			if (std::filesystem::exists(originalSigPath)) {
				info("Sig file in place!");
			}
			else {
				displayCrash("Satisfactory Install Error", "SatisfactoryModLoader has detected an error with your Satisfactory installation.\nPlease click 'verify' in the Epic Games Launcher and reinstall Satisfactory.");
			}
			//generate the sig
			generateSigFiles(pakfilepath, originalSigLoc);
			//disable the crashreporter
			disableCrashReporter(rootpath);
		}

		void generateSigFiles(std::string pakfilepath, std::string originalSigPath) {
			bool didGenerate = false;
			for (auto &entry : std::filesystem::directory_iterator(std::filesystem::path(pakfilepath))) {
				//info(entry.path().string());
				if (entry.path().extension().string() == ".pak") {
					std::string sigfile = entry.path().string();
					sigfile.replace(sigfile.find(".pak"), 4, ".sig");
					if (std::filesystem::exists(std::filesystem::path(sigfile))) {
						continue; //skip sigfiles that exist
					}
					else {
						info("Making sig: ", sigfile);
						std::filesystem::path newSigPath(sigfile);
						std::filesystem::path originalSig(originalSigPath);
						std::filesystem::copy_file(originalSig, newSigPath); //copy original sig to the new sig
						didGenerate = true;
					}
				}
			}
			if (didGenerate) {
				warning("If satisfactory crashes, please reload it to make it run.");
			}
		}

		void disableCrashReporter(std::string rootPath) {
			rootPath = rootPath.substr(0, rootPath.find_last_of("/\\")); // ../
			rootPath = rootPath + "\\Engine\\Binaries\\Win64";
			if (std::filesystem::exists(std::filesystem::path(rootPath + "\\CrashReportClient.exe"))) {
				std::filesystem::rename(std::filesystem::path(rootPath + "\\CrashReportClient.exe"), std::filesystem::path(rootPath + "\\CrashReportClient-Disabled.exe"));
			} else if (std::filesystem::exists(std::filesystem::path(rootPath + "\\CrashReportClient-Disabled.exe"))) {
				warning("Skipping already disabled crash reporter");
			} else {
				displayCrash("Satisfactory Install Error", "SatisfactoryModLoader has detected an error with your Satisfactory installation.\nPlease click 'verify' in the Epic Games Launcher and reinstall Satisfactory.");
			}
		}

		void enableCrashReporter(std::string rootPath) {
			rootPath = rootPath.substr(0, rootPath.find_last_of("/\\")); // ../
			rootPath = rootPath + "\\Engine\\Binaries\\Win64";
			if (std::filesystem::exists(std::filesystem::path(rootPath + "\\CrashReportClient-Disabled.exe"))) {
				std::filesystem::rename(std::filesystem::path(rootPath + "\\CrashReportClient-Disabled.exe"), std::filesystem::path(rootPath + "\\CrashReportClient.exe"));
			}
			else {
				displayCrash("Satisfactory Install Error", "SatisfactoryModLoader has detected an error with your Satisfactory installation.\nPlease click 'verify' in the Epic Games Launcher and reinstall Satisfactory.");
			}
		}
	};
};