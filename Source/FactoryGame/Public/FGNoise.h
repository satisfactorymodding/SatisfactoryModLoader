// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HAL/IConsoleManager.h"
#include "FGNoise.generated.h"

extern TAutoConsoleVariable< int32 > CVarFGNoiseDebug;

/**
 * Wrapper object for perception system noise, instead of relying solely on strings / tags.
 */
UCLASS( BlueprintType, Abstract, Blueprintable )
class FACTORYGAME_API UFGNoise : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UFGNoise();

	/** Makes a noise for the specified actor using the specified FGNoise class. */
	UFUNCTION( BlueprintCallable, Category = "Noise" )
	static void MakeNoiseOfType( TSubclassOf< UFGNoise > noiseClass, AActor* actor, const FVector& noiseLocation );
	
	/** Makes a noise for the specified actor using this FGNoise class. */
	UFUNCTION( BlueprintCallable, Category = "Noise" )
	void MakeNoiseForActor( AActor* actor, const FVector& noiseLocation ) const;
	
protected:	
	/** Max range of the noise. */
	UPROPERTY( EditDefaultsOnly, Category = "Noise" )
	float mMaxRange;

	/** Loudness of the noise. */
	UPROPERTY( EditDefaultsOnly, Category = "Noise" )
	float mLoudness;
};
