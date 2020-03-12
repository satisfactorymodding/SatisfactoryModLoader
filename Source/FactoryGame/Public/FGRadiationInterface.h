// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Interface.h"
#include "SubclassOf.h"

#include "FGRadiationInterface.generated.h"


UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGRadiationInterface : public UInterface
{
	
 GENERATED_BODY()
	UFGRadiationInterface(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {} 

public:
	FORCEINLINE ~UFGRadiationInterface() = default;
};

/**
 * @brief Interface for all actors that can take damage by radiation.
 */
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

public:
	FORCEINLINE IFGRadiationInterface() = default;
};
