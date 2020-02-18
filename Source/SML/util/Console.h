#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <fstream>

#include "SatisfactoryModLoader.h"
#include "Logging.h"

namespace SML {
	/**
	* Used at engine boot to check SML config if the console should get opened.
	* If so, open the console.
	*
	* !WARNING! Only call it after the SML config has loaded
	*/
	void initConsole();

	/**
	* Used by initConsole to allocate and show the console.
	* All standard output streams will get cloned to the console.
	*/
	void enableConsole();

	/**
	* Enables the full log which basically writes all of the standard output streams to one file.
	* This allows for better debugging and crash analyzes.
	*/
	void enableFullLog();
}