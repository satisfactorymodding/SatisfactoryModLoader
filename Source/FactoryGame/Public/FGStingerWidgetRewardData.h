// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Templates/SubclassOf.h"
#include "FGStingerWidgetRewardData.generated.h"

class UTexture2D;

/**
 * Base class for holding reward data for stinger reward widgets
 */
UCLASS( Blueprintable, Abstract )
class FACTORYGAME_API UFGStingerWidgetRewardData : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintPure, Category = "FactoryGame|StingerWidgetRewardData" )
	static FText GetIconText( TSubclassOf< UFGStingerWidgetRewardData > inClass );

	UFUNCTION( BlueprintPure, Category = "FactoryGame|StingerWidgetRewardData" )
	static UTexture2D* GetIconTexture( TSubclassOf< UFGStingerWidgetRewardData > inClass );

protected:
	UPROPERTY( EditDefaultsOnly, Category = "StingerWidgetRewardData" )
	FText mIconText;

	UPROPERTY( EditDefaultsOnly, Category = "StingerWidgetRewardData" )
	UTexture2D* mIconTexture;
};
