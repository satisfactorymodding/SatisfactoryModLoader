// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FGFactoryConnectionStateOwner.generated.h"

class UFGFactoryConnectionComponent;

/** Connected state of an actor's factory connections. Bit N is the Nth connection sorted by name. */
USTRUCT()
struct FACTORYGAME_API FFGFactoryConnectionStates
{
	GENERATED_BODY()

	/** @return true if the state changed. */
	bool SetConnected( const UFGFactoryConnectionComponent* connection, bool isConnected );

	void ApplyToConnections( const AActor* owner ) const;

private:
	UPROPERTY()
	uint64 ConnectedMask = 0;
};

UINTERFACE( MinimalAPI, meta = ( CannotImplementInterfaceInBlueprint ) )
class UFGFactoryConnectionStateOwner : public UInterface
{
	GENERATED_BODY()
};

/** Actors that replicate their factory connections' connected state, so the connection components don't replicate. */
class FACTORYGAME_API IFGFactoryConnectionStateOwner
{
	GENERATED_BODY()
public:
	virtual void SetFactoryConnectionConnected( const UFGFactoryConnectionComponent* connection, bool isConnected ) = 0;
};
