// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGRadiationInterface.generated.h"

/**
 * Interface for actors that can take damage by radiation.
 */
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGRadiationInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class FACTORYGAME_API IFGRadiationInterface
{
	GENERATED_IINTERFACE_BODY()

	/**
	 * @param amount		How much radiation we're exposed to. [units/s]
	 * @param duration		For how long we've been exposed. [s]
	 * @param damageType	The type of damage you take from this radiation.
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "Radioactivity" )
	void ReceiveRadiation( float amount, float duration, FVector direction, TSubclassOf< class UFGDamageType > damageType );
};
