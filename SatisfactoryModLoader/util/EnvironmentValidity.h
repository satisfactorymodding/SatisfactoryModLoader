#pragma once
#include <string>

namespace SML {
	namespace Utility {
		// Get the root game path
		std::string getRootPath();

		// Get the pak path
		std::string getPakPath();

		// Get the mod path
		std::string getModPath();

		// Get the coremod path
		std::string getCoreModPath();

		// Get the hidden mod path
		std::string getHiddenModPath();

		// Get the hidden core mod path
		std::string getHiddenCoreModPath();

		// Cleanup all hidden directories (hiddenmod, hiddencoremod)
		void cleanupHiddenDirectories();

		// Delete directory recursively
		void deleteDirectoryRecursive(std::string path);

		// Create an optionally hidden directory
		void createDirectory(std::string path, bool hidden);

		//Checks to make sure that the sig and crash report client are in place
		void checkForValidEnvironment();

		//Generates sigs automatically for stupid people, i mean misguided individuals
		void generateSigFiles(std::string pakfilepath, std::string originalSigPath);

		//Disables the crash reporter by renaming it so Coffee Stain aren't bombarded by crashes
		void disableCrashReporter(std::string rootPath);
		
		//Enables the crash reporter when the game is closed to ensure that CSS get reports if SML is uninstalled
		void enableCrashReporter(std::string rootPath);
	};
};