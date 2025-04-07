// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "UObject/Interface.h"

#include "FGUnsafePawnRelocationInterface.generated.h"

/**
 * Interface for actors that should be colorable with the colorgun.
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
