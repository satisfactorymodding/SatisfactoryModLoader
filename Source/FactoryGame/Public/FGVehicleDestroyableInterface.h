// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "../../Plugins/Wwise/Source/AkAudio/Classes/AkAudioEvent.h"
#include "UObject/Interface.h"
#include "UObject/Class.h"

#include "FGVehicleDestroyableInterface.generated.h"

/**
* For blueprint support of the interface, we will never add anything to it, just use it to
* have a UCLASS to be able to access
*/
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGVehicleDestroyableInterface : public UInterface
{
	
 GENERATED_BODY()
	UFGVehicleDestroyableInterface(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {} 

public:
	FORCEINLINE ~UFGVehicleDestroyableInterface() = default;
};

/**
 * Actors attached that implement this interface can be destroyed by a vehicle running over it.
 */
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

public:
	FORCEINLINE IFGVehicleDestroyableInterface() = default;
};
