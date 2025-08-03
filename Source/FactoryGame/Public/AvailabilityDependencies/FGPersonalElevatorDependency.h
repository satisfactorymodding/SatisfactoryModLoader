// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
#include "FGPersonalElevatorDependency.generated.h"

UENUM( BlueprintType, Meta = ( Bitflags, UseEnumValuesAsMaskValuesInEditor = "true" ) )
enum class EElevatorDependencyEvent : uint8
{
	None		= 0x0	UMETA( DisplayName = "None" ),
	BeginMove	= 0x1	UMETA( DisplayName = "Begin Move" ),
	EndMove		= 0x2	UMETA( DisplayName = "End Move" ),
};

ENUM_CLASS_FLAGS( EElevatorDependencyEvent );

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGPersonalElevatorDependency : public UFGAvailabilityDependency
{
	GENERATED_BODY()

public:
	UFGPersonalElevatorDependency();

	bool ShouldTriggerOnEvents( EElevatorDependencyEvent eventTypeFlags ) const;

	FORCEINLINE float GetMinimumTravelTime() const { return mMinimumRequiredTravelTime; }

#if WITH_EDITOR
	virtual FString ToString() const override;
	virtual void FromString( const FString& inString ) override;
#endif

private:
	/** What type of events this dependency should trigger on. */
	UPROPERTY( EditDefaultsOnly, Category = "Dependency", meta = ( Bitmask, BitmaskEnum = "EElevatorDependencyEvent" ) )
	uint8 mEvents;

	/** How long the estimated travel time needs to be when using the Begin Move and End Move events. */
	UPROPERTY( EditDefaultsOnly, Category = "Dependency" )
	float mMinimumRequiredTravelTime;
};
