// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "GameFeaturesProjectPolicies.h"
#include "FGGameFeaturesProjectPolicies.generated.h"

UCLASS()
class FACTORYGAME_API UFGGameFeaturesProjectPolicies : public UDefaultGameFeaturesProjectPolicies
{
	GENERATED_BODY()
public:
	/**
	 * Utility function to filter assets from disabled game feature plugins from the given asset data list.
	 * Unlike a function in UGameFeaturesSubsystem with the same name, this function does not remove asset paths that
	 * do not represent non-game feature plugins, such as /Game/ and /Engine/ assets
	 */
	static void FilterInactiveGameFeaturePluginAssets(TArray<FAssetData>& AssetDataList);
};

