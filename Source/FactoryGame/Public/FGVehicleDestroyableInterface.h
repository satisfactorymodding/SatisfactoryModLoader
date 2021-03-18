// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGVehicleDestroyableInterface.generated.h"

/**
 * Actors that implement this interface can be destroyed by a vehicle running over it.
 */
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGVehicleDestroyableInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class FACTORYGAME_API IFGVehicleDestroyableInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	/* @returns the force required (if any) to destroy this object */
	UFUNCTION( BlueprintNativeEvent, Category = "Vehicle Destroy Interface" )
	float GetForceThreshold();
	
	/** Audio event to be posted when destroyed */
	UFUNCTION( BlueprintNativeEvent, Category = "Vehicle Destroy Interface" )
	class UAkAudioEvent* GetDestroyAudioEvent();

	/** Particle System to be played when destroyed */
	UFUNCTION( BlueprintNativeEvent, Category = "Vehicle Destroy Interface" )
	class UParticleSystem* GetDestroyEffect();
};
