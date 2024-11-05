// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "FGAmmoType.h"
#include "FGAmmoTypeSpreadshot.generated.h"

/**
 * Ammo type used for spreading out multiple shots at once
 */
UCLASS()
class FACTORYGAME_API UFGAmmoTypeSpreadshot : public UFGAmmoType
{
	GENERATED_BODY()
	
public:
	UFGAmmoTypeSpreadshot();

	virtual void FireAmmunition_Implementation() override;

	UFUNCTION( BlueprintNativeEvent, Category = "Ammunition|Spreadshot" )
	void ProcessHit( const FHitResult& hitResult );

protected:
	UFUNCTION( NetMulticast, Unreliable )
	void NetMulticast_PlayEffects( const TArray< FHitResult >& traceResults );

	UFUNCTION( BlueprintNativeEvent, Category = "Ammunition|Spreadshot")
	void PlayEffects( const TArray< FHitResult >& traceResults );

protected:
	/** How many shots to fire. */
	UPROPERTY( EditDefaultsOnly, Category = "Ammunition|Spreadshot" )
	FInt32Interval mNumShots;

	/** How much to spread the shots. */
	UPROPERTY( EditDefaultsOnly, Category = "Ammunition|Spreadshot" )
	float mSpreadAngleDegrees;
};
