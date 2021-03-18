// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildable.h"

#include "FGBuildableHubTerminal.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildableHubTerminal : public AFGBuildable
{
	GENERATED_BODY()
public:
	/** Get the trading post */
	UFUNCTION( BlueprintPure, Category = "Hub Terminal" )
	FORCEINLINE class AFGBuildableTradingPost* GetTradingPost() { return mTradingPost; }

	//~ Begin AFGBuildable interface
	virtual bool CanBeSampled_Implementation() const{ return false; }
	//~ End AFGBuildable interface
public:
	UPROPERTY()
	class AFGBuildableTradingPost* mTradingPost;
	
};
