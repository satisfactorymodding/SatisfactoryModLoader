#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <utility>
#include <util/Logging.h>

#include "../Lib.h"

namespace SML {
	namespace Objects {
		/*
		* initializes the BPI Objects
		*/
		SML_API void initObjects();
	}

	namespace Utility {

		void displayCrash(std::string crashText);

		void displayCrash(std::string header, std::string crashText);

		void closeGame();

		void SML_API checkVersion(const int target);		

		template <class T>
		T * offset(T * ptr, size_t offset) {
			return (T *)(reinterpret_cast<unsigned char*>(ptr) + offset);
		}

		// Get the pak path
		std::string getPakPath();

		// Get the mod path
		std::string getModPath();

		// Get the coremod path
		std::string getCoreModPath();

		// Get the hidden pak path
		std::string getHiddenPakPath();

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
	}
}