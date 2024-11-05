// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FGWorldHeightData.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGWorldHeightData : public UDataAsset
{
	GENERATED_BODY()
public:
#if WITH_EDITOR
	void SetWorldHeightData( const TArray<float> heightData, const int32 heightDataResolution );
#endif

	float GetZValueFromNormalizedPosition( const FVector2D normalizedLocation );
	
	UPROPERTY( VisibleAnywhere )
	TArray<float> mHeightData;

	UPROPERTY( VisibleAnywhere )
	int32 mHeightDataResolution;
	
};
