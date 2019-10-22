#include <stdafx.h>
#include "EnvironmentValidity.h"
#include <string>
#include <Windows.h>
#include <filesystem>
#include <fstream>
#include <util/Utility.h>

namespace SML {
	namespace Utility {
		std::string getRootPath() {
			// Get the execution path (\FactoryGame\Binaries\Win64\FactoryGame.exe)
			char path_c[MAX_PATH];
			GetModuleFileNameA(NULL, path_c, MAX_PATH);
			std::string path = std::string(path_c);			 // ..\FactoryGame\Binaries\Win64\.exe
			path = path.substr(0, path.find_last_of("/\\")); // ..\FactoryGame\Binaries\Win64
			path = path.substr(0, path.find_last_of("/\\")); // ..\FactoryGame\Binaries
			path = path.substr(0, path.find_last_of("/\\")); // ..\FactoryGame
			return path;
		}

		std::string getPakPath() {
			return getRootPath() + "\\Content\\Paks";
		}

		std::string getModPath() {
			auto path = getRootPath() + "\\Binaries\\Win64\\mods";;
			createDirectory(path, false);
			return path;
		}

		std::string getCoreModPath() {
			auto path = getRootPath() + "\\Binaries\\Win64\\coremods";;
			createDirectory(path, false);
			return path;
		}

		std::string getHiddenModPath() {
			auto path = getRootPath() + "\\Binaries\\Win64\\hiddenmods";;
			createDirectory(path, true);
			return path;
		}

		std::string getHiddenCoreModPath() {
			auto path = getRootPath() + "\\Binaries\\Win64\\hiddencoremods";;
			createDirectory(path, true);
			return path;
		}

		void cleanupHiddenDirectories() {
			Utility::debug("Deleting previous hidden directories");
			deleteDirectoryRecursive(getHiddenModPath());
			deleteDirectoryRecursive(getHiddenCoreModPath());
		}

		void deleteDirectoryRecursive(std::string path) {
			for (const auto &entry : std::experimental::filesystem::directory_iterator(path)) {
				if (std::filesystem::is_directory(entry.path().string())) {
					deleteDirectoryRecursive(entry.path().string());
					continue;
				}

				Utility::debug("Deleting: ", entry.path().string());
				if (!DeleteFileA(entry.path().string().c_str())) {
					auto errorCode = GetLastError();
					Utility::error("Failed to delete: ", entry.path().string());
					Utility::error("Error: ", errorCode);
				}
			}

			Utility::debug("Deleting: ", path);
			if (!RemoveDirectoryA(path.c_str())) {
				auto errorCode = GetLastError();
				Utility::error("Failed to delete: ", path);
				Utility::error("Error: ", errorCode);
			}
		}

		void createDirectory(std::string path, bool hidden) {
			CreateDirectoryA(path.c_str(), NULL);

			if (hidden) {
				SetFileAttributesA(path.c_str(), FILE_ATTRIBUTE_HIDDEN);
			}
		}

		void checkForValidEnvironment() {
			std::string rootpath = getRootPath();
			std::string pakDirPath = getPakPath();
			info(pakDirPath);
			std::string originalSigLoc = pakDirPath + "\\FactoryGame-WindowsNoEditor.sig";
			std::filesystem::path originalSigPath(originalSigLoc);
			if (std::filesystem::exists(originalSigPath)) {
				info("Sig file in place!");
			}
			else {
				displayCrash("Satisfactory Install Error", "SatisfactoryModLoader has detected an error with your Satisfactory installation.\nPlease click 'verify' in the Epic Games Launcher and reinstall Satisfactory.");
			}

			//generate the sig
			generateSigFiles(pakDirPath, originalSigLoc);
			//disable the crashreporter
			disableCrashReporter(rootpath);
		}

		void generateSigFiles(std::string pakfilepath, std::string originalSigPath) {
			bool didGenerate = false;
			for (auto &entry : std::filesystem::directory_iterator(std::filesystem::path(pakfilepath))) {
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
				warning("If satisfactory crashes after this message, please reload it to fix it.");
			}
		}

		void disableCrashReporter(std::string rootPath) {
			rootPath = rootPath.substr(0, rootPath.find_last_of("/\\"));
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
			rootPath = rootPath.substr(0, rootPath.find_last_of("/\\"));
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