#pragma once
#include "CoreMinimal.h"

/**
 * Small wrapper class to handle debugger support in shipping builds
 * Will break into the debugger on windows or fallback to default UE functions on other platforms
 */
class SML_API FDebuggerHelper {
public:
	static bool IsDebuggerPresent();
	static void DebugBreak();
	static bool IsDebuggerHelperSupported();
};