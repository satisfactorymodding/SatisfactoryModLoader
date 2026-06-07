// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FGSignificanceInterface.generated.h"

/** Tick rate management settings for significance */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FFGSignificanceTickRateSettings
{
	GENERATED_BODY()

	/** Determines whenever object tick rate should be managed by the significance system */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Tick Settings" )
	bool bTickRateManagedBySignificance{false};

	/** Number of tick levels this actor has for distance-based tick throttle. Each level exponentially reduces the tick rate */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Tick Settings" )
	int32 NumTickLevels{1};
};

/**
 * Interface for actors that are handled by UFGSignificanceManager
 * Significance is handled only for local players and does not run on dedicated servers
 * Objects must be registered to the significance manager to receive significance via UFGBlueprintFunctionLibrary::AddStaticSignificance
 * and removed on EndPlay via UFGBlueprintFunctionLibrary::RemoveStaticSignificance
 */
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGSignificanceInterface : public UInterface
{
	GENERATED_BODY()
};

class FACTORYGAME_API IFGSignificanceInterface
{
	GENERATED_BODY()
public:
	/** Called to determine the object significance for local player. Range Defaults to 10000.0 if zero is provided in this function, or to the value provided to the registration functions in UFGBlueprintFunctionLibrary */
	UFUNCTION( BlueprintNativeEvent, Category = "Significance" )
	float GetSignificanceRange() const;

	/** Called to notify the actor of the initial significance state it has after a call to USignificanceManagerAccelerated::RegisterStaticObject during BeginPlay */
	UFUNCTION( BlueprintNativeEvent, Category = "Significance" )
	void SetInitialSignificanceState( bool bIsInitiallySignificant );

	/** Call when actor gained significance for the local player. Will not be fired for dedicated servers. Actor must be registered via USignificanceManagerAccelerated::RegisterStaticObject */
	UFUNCTION( BlueprintNativeEvent, Category = "Significance" )
	void GainedSignificance();

	/** Call when actor gained significance for the local players. Will not be fired for dedicated servers */
	UFUNCTION( BlueprintNativeEvent, Category = "Significance" )
	void LostSignificance();

	/** Returns the significance tick rate settings for this object. It allows throttling object tick rate based on significance */
	UFUNCTION( BlueprintNativeEvent, Category = "Significance" )
	FFGSignificanceTickRateSettings GetSignificanceTickRateSettings() const;

	/** Will be called to update the object with the throttled tick rate and enable/disable tick based on the local player proximity and number of tick levels */
	UFUNCTION( BlueprintNativeEvent, Category = "Significance" )
	void UpdateSignificanceTickRate( float NewTickRate, bool bTickEnabled );
};
