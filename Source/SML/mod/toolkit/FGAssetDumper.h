#pragma once
#include "UnrealString.h"

namespace SML {
	/**
	 * Dumps blueprint asset information for all blueprints existing on specified root path
	 * and it's subdirectories, and writes it as the json into the specified file
	 * While it is primarily used to dump satisfactory blueprint assets,
	 * it can take any root path and dump any pak content's, including SML, mods and engine itself
	 *
	 * Example Usage:
	 * SML::dumpSatisfactoryAssets(TEXT("/Game/FactoryGame/"), TEXT("FGBlueprints.json"));
	 */
	void dumpSatisfactoryAssets(const FName& rootPath, const FString& fileName);
}