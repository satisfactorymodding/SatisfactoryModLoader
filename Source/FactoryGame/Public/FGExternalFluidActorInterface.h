// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "UObject/Interface.h"
#include "FGExternalFluidActorInterface.generated.h"

class UFGPipeConnectionComponentBase;

/**
 * Interface to identify actors that interface with the fluid networks, but that are not fluid integrants themselves
 * Integrants must not implement this interface, and instead stick to just IFGFluidIntegrantInterface
 */
UINTERFACE( meta = (CannotImplementInterfaceInBlueprint) )
class FACTORYGAME_API UFGExternalFluidActorInterface : public UInterface
{
	GENERATED_BODY()
};

class FACTORYGAME_API IFGExternalFluidActorInterface
{
	GENERATED_BODY()
public:
	/**
	 * Called to request the external fluid actor to flush it's internal fluid buffer connected to the provided connection
	 * because the connected pipe network has been flushed.
	 * The connection provided is on this actor, not on the connected pipe.
	 */
	virtual void FlushPipeNetworkConnection(UFGPipeConnectionComponentBase* fromConnection) {}
};
