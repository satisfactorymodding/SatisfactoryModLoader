// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Perception/AIPerceptionTypes.h"

#include "FGStimulusAccumulator.generated.h"

enum class ECreatureState : uint8;

/** Used to accumulate a float value for a creature when it perceives a stimulus. */
UCLASS( Blueprintable, BlueprintType, Abstract, DefaultToInstanced, EditInlineNew )
class FACTORYGAME_API UFGStimulusAccumulator : public UObject
{
	GENERATED_BODY()
public:
	UFGStimulusAccumulator();

	/** Whether or not this accumulator should accumulate for the specified stimulus. */
	UFUNCTION( BlueprintPure, Category = "Stimulus Accumulator" )
	virtual bool ShouldAccumulateForStimulus( const class AFGCreatureController* controller, const FAIStimulus& stimulus, const AActor* sourceActor ) const;

	/** Gets the value accumulation for the specified stimulus. */
	UFUNCTION( BlueprintPure, Category = "Stimulus Accumulator" )
	virtual float GetAccumulation( const FAIStimulus& stimulus, const AActor* sourceActor ) const;

protected:
	/** Only consider stimuli created from these kinds of actors. */
	UPROPERTY( EditDefaultsOnly, Category = "Stimulus Accumulator" )
	TArray< TSubclassOf< AActor > > mSourceActorFilter;

	/** States for which the accumulator will be blocked for: Default = none */
	UPROPERTY( EditDefaultsOnly, meta = ( Bitmask, BitmaskEnum = "ECreatureState" ), Category = "Stimulus Accumulator" )
	uint8 mBlockedStates;

	/** Base amount to accumulate when stimuli is perceived. */
	UPROPERTY( EditDefaultsOnly, Category = "Stimulus Accumulator" )
	float mBaseGain;

	/** Amount to accumulate when a stimulus is perceived, based on the strength of the stimulus multiplied by this. */
	UPROPERTY( EditDefaultsOnly, Category = "Stimulus Accumulator" )
	float mStimulusStrengthMultiplierGain;

	/** If the stimulus strength outside this range, it will be ignored. If Min > Max then Max is ignored. */
	UPROPERTY( EditDefaultsOnly, Category = "Stimulus Accumulator" )
	FFloatInterval mStimulusStrengthRange;

	/** If the distance to the stimulus is outside this range, it will be ignored. If Min > Max then Max is ignored. */
	UPROPERTY( EditDefaultsOnly, Category = "Stimulus Accumulator" )
	FFloatInterval mStimulusDistanceRange;
};

/** Stimulus accumulator for noise. */
UCLASS( Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew )
class FACTORYGAME_API UFGStimulusAccumulatorNoise : public UFGStimulusAccumulator
{
	GENERATED_BODY()
public:
	// Begin UFGStimulusAccumulator Interface
	virtual bool ShouldAccumulateForStimulus( const class AFGCreatureController* controller, const FAIStimulus& stimulus, const AActor* sourceActor ) const override;
	// End UFGStimulusAccumulator Interface
	
protected:
	/** If specified, will only accumulate for these noise types. */
	UPROPERTY( EditDefaultsOnly, Category = "Stimulus Accumulator" )
	TArray< TSubclassOf< class UFGNoise > > mNoiseTypes;
};

/** Stimulus accumulator for senses. */
UCLASS( Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew )
class FACTORYGAME_API UFGStimulusAccumulatorSense : public UFGStimulusAccumulator
{
	GENERATED_BODY()
public:
	// Begin UFGStimulusAccumulator Interface
	virtual bool ShouldAccumulateForStimulus( const class AFGCreatureController* controller, const FAIStimulus& stimulus, const AActor* sourceActor ) const override;
	// End UFGStimulusAccumulator Interface
	
	protected:
	/** If specified, will only accumulate for these sense types. */
	UPROPERTY( EditDefaultsOnly, Category = "Stimulus Accumulator" )
	TArray< TSubclassOf< class UAISense > > mSenseTypes;
};