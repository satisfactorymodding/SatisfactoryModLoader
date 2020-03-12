#pragma once

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
}