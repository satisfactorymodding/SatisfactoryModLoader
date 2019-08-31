#pragma once
#include <string>

namespace SML {
	namespace Utility {
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