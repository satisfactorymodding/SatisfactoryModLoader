#pragma once
#include "CoreMinimal.h"

namespace SML {
	/**
	* Used at engine boot to check SML config if the console should get opened.
	* If so, open the console.
	*
	* !WARNING! Only call it after the SML config has loaded
	*/
	void InitConsole();

	/**
	* Used by initConsole to allocate and show the console.
	* All standard output streams will get cloned to the console.
	*/
	void EnableConsole();

	/**
	 * Notify fatal error has occured to the user UI outside of the game
	 * On Win32 it will show message box
	 */
	SML_API void NotifyFatalError(const FString& Message);
}