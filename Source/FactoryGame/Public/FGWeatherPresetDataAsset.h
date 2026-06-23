// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "FGWeatherPresetDataAsset.generated.h"

class AFGWeatherReaction;

USTRUCT( BlueprintType )
struct FWeatherChance
{
	GENERATED_BODY()
	
public:
	UPROPERTY( EditDefaultsOnly )
	FName EntryName;
	
	UPROPERTY( EditDefaultsOnly )
	float mProbability;
	
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf<AFGWeatherReaction> mWeatherBehaviour;

	/* Number of days that must pass before the weather can start.*/
	UPROPERTY( EditDefaultsOnly )
	int32 mWeatherStartupDelayDays;
	
	///* Can this weather effect repeat itself? */
	//UPROPERTY( EditDefaultsOnly )
	//bool bAllowedToRunInSequence;

	UPROPERTY( EditDefaultsOnly )
	TArray<TSubclassOf<AFGWeatherReaction>> DisallowedFollowupReactions;

	UPROPERTY( EditDefaultsOnly )
	FFloatInterval mWeatherEffectDuration;

	FWeatherChance()
		: mProbability( 1.f )
		, mWeatherStartupDelayDays(0)
		, mWeatherEffectDuration(120,300)
	{ };
};

/**
 * Describes a weather preset, which is a collection of weather behaviors with their probabilities and requirements
 */
UCLASS(BlueprintType)
class FACTORYGAME_API UFGWeatherPresetDataAsset : public UDataAsset
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere )
	TArray<FWeatherChance> Entry;

	UPROPERTY( EditAnywhere )
	int32 FallBackEntry = 0;
public:
	static TSubclassOf<AFGWeatherReaction> RollNewWeatherState(	TSubclassOf<AFGWeatherReaction> CurrentReaction,
																UFGWeatherPresetDataAsset* Preset,
																int32 DayNumber,
																float& OutDuration);

	UFUNCTION(BlueprintCallable)
	static void LogWeatherChance(UFGWeatherPresetDataAsset* Preset);

	UFUNCTION(BlueprintCallable)
	static bool IsWeatherPresetValid(UFGWeatherPresetDataAsset* PresetAsset);
};
