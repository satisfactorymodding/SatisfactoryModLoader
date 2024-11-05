// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FGExplosiveDestroyableInterface.generated.h"

/**
 * Interface for retrieving destruction effects from Actors destroyed by explosives
 */
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGExplosiveDestroyableInterface : public UInterface
{
	GENERATED_BODY()
};

class FACTORYGAME_API IFGExplosiveDestroyableInterface
{
	GENERATED_BODY()

public:
	/** Particle System to be played when destroyed */
	UFUNCTION( BlueprintNativeEvent, Category = "Explosive Destroy Interface" )
	class UParticleSystem* GetExplosiveDestroyEffect();

	/** Blueprint event for modifying BP objects when they are exploded */
	UFUNCTION( BlueprintNativeEvent, Category = "Explosive Destroy Interface" )
	bool NotifyExploded();

	/** Notify the destroyed actor where the destruction event originate (where did the boom come from) */
	UFUNCTION( BlueprintNativeEvent, Category = "Explosive Destroy Interface" )
	void SetDestructionInfo( AActor* dmgCauser, const FVector& location );

};
