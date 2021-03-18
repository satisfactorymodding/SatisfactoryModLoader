// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGInventoryComponent.h"
#include "FGChainsawableInterface.generated.h"

/**
 * Actors that implement this interface will be considered by the chainsaw to be chainsawable.
 */
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGChainsawableInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class FACTORYGAME_API IFGChainsawableInterface
{
	GENERATED_IINTERFACE_BODY()

	/* @returns true if this thing is chainsawable */
	UFUNCTION( BlueprintNativeEvent, Category = "Chainsaw" )
	bool IsChainsawable();

	/* @returns true if this thing is chainsawable */
	UFUNCTION( BlueprintNativeEvent, Category = "Chainsaw" )
	UStaticMeshComponent* GetMeshComponent();

	/* @returns the items you get for chainsawing this actor */
	UFUNCTION( BlueprintNativeEvent, Category = "Chainsaw" )
	FInventoryStack GetActorChainsawReturn();
};
