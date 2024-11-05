// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "FGAmmoTypeHomingBase.h"

#include "Engine/EngineTypes.h"

#include "FGAmmoTypeHoming.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGAmmoTypeHoming : public UFGAmmoTypeHomingBase
{
	GENERATED_BODY()
	
public:
	UFGAmmoTypeHoming();
	
	virtual void FireAmmunition_Implementation() override;
	
protected:
	/** Called on both server and client whenever we hit something. */
	UFUNCTION( BlueprintNativeEvent, Category = "Ammunition|Homing" )
    void ProcessHit( const FHitResult& hitResult );
	
	UFUNCTION( NetMulticast, Unreliable )
	void NetMulticast_PlayEffects( const FHitResult& hitResult );

	/** Called on both server and client whenever we hit something. */
    UFUNCTION( BlueprintNativeEvent, Category = "Ammunition|Homing" )
    void PlayEffects( const FHitResult& hitResult );
};
