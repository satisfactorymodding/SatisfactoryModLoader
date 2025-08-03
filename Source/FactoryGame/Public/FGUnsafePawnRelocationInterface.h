// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "UObject/Interface.h"

#include "FGUnsafePawnRelocationInterface.generated.h"

/**
 * Interface for flagging actors as in an unsafe location. This was used by the elevators to relocate pawns if loading inside a cabin.
 * This is no longer the case but is still used there to not update the last safe location.
 *
 * @TODO A better method would be to track the reason
 * the actor is "unsafe" by saving the reason. This could be a good idea for a refactor since a bool doesn't have a way of evaluating
 * if its still unsafe or if it was flagged for a different reason. Currently there is no need for this but it would be a smart change 
 */
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGUnsafePawnRelocationInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()	
};

class FACTORYGAME_API IFGUnsafePawnRelocationInterface
{
	GENERATED_IINTERFACE_BODY()

	virtual void SetIsInUnsafeLoadLocation( bool isUnsafe ) {}
	virtual void SetLastSafeLocation( const FVector& location ) {}
	virtual FVector GetLastSafeLoadLocation() { return FVector::ZeroVector; } 
};