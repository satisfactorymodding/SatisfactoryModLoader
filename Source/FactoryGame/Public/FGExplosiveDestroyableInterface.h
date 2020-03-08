// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FGExplosiveDestroyableInterface.generated.h"

UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGExplosiveDestroyableInterface : public UInterface
{
	GENERATED_BODY()

public:
	FORCEINLINE ~UFGExplosiveDestroyableInterface() = default;
};

/**
 * Interface for retrieving destruction effects from Actors destroyed by explosives
 */
class FACTORYGAME_API IFGExplosiveDestroyableInterface
{
	GENERATED_BODY()

public:
	/** Particle System to be played when destroyed */
	UFUNCTION( BlueprintNativeEvent, Category = "Explosive Destroy Interface" )
	class UParticleSystem* GetDestroyEffect();

	/** Blueprint event for modifying BP objects when they are exploded */
	UFUNCTION( BlueprintNativeEvent, Category = "Explosive Destroy Interface" )
	bool NotifyExploded();


public:
	FORCEINLINE IFGExplosiveDestroyableInterface() = default;
};
