// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "DamageTypes/FGDamageType.h"

#include "FGDamageTypeAccumulator.generated.h"

/** Used to accumulate a float value for a creature when it receives damage. */
UCLASS( Blueprintable, BlueprintType, DefaultToInstanced, EditInlineNew )
class FACTORYGAME_API UFGDamageTypeAccumulator : public UObject
{
	GENERATED_BODY()
public:
	UFGDamageTypeAccumulator();

	/** Whether or not this accumulator should accumulate for the specified stimulus. */
	UFUNCTION( BlueprintPure, Category = "Damage Type Accumulator" )
	virtual bool ShouldAccumulateForDamage( const class AFGCreatureController* controller, float damageAmount, const UFGDamageType* damageType, const AActor* sourceActor ) const;

	/** Gets the value accumulation for the specified stimulus. */
	UFUNCTION( BlueprintPure, Category = "Damage Type Accumulator" )
	virtual float GetAccumulation( float damageAmount, const UFGDamageType* damageType, const AActor* sourceActor ) const;

protected:
	/** Only consider these damage types. */
	UPROPERTY( EditDefaultsOnly, Category = "Damage Type Accumulator" )
	TArray< TSubclassOf< UFGDamageType > > mDamageTypeFilter;
	
	/** Only consider damage received from these kinds of actors. */
	UPROPERTY( EditDefaultsOnly, Category = "Damage Type Accumulator" )
	TArray< TSubclassOf< AActor > > mSourceActorFilter;

	/** Only consider damage received from these kinds of instigators. */
	UPROPERTY( EditDefaultsOnly, Category = "Damage Type Accumulator" )
	TArray< TSubclassOf< AController > > mInstigatorFilter;

	/** States for which the accumulator will be blocked for: Default = none */
	UPROPERTY( EditDefaultsOnly, meta = ( Bitmask, BitmaskEnum = "ECreatureState" ), Category = "Damage Type Accumulator" )
	uint8 mBlockedStates;

	/** Base amount to accumulate when receiving damage. */
	UPROPERTY( EditDefaultsOnly, Category = "Damage Type Accumulator" )
	float mBaseGain;

	/** Amount to accumulate based on damage received multiplied by this value. */
	UPROPERTY( EditDefaultsOnly, Category = "Damage Type Accumulator" )
	float mDamageMultiplierGain;

	/** If the damage amount is outside this range, it will be ignored. If Min > Max then Max is ignored. */
	UPROPERTY( EditDefaultsOnly, Category = "Damage Type Accumulator" )
	FFloatInterval mDamageRange;
};
