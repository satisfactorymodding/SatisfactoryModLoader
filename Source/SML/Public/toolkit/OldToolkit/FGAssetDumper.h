#pragma once
#include "UnrealString.h"

class SML_API FGameAssetDumper {
public:
	/**
	 * Dumps blueprint asset information for all blueprints existing on specified root path
	 * and it's subdirectories, and writes it as the json into the specified file
	 * While it is primarily used to dump satisfactory blueprint assets,
	 * it can take any root path and dump any pak content's, including SML, mods and engine itself
	 *
	 */
	static void DumpSatisfactoryAssets();

	/** Dumps single object into individual file */
	static bool DumpSingleAssetObject(class UObject* ObjectToDump);

private:
	friend class FSatisfactoryModLoader;
	
	/** Registers Unreal console commands */
	static void RegisterConsoleCommands();
};