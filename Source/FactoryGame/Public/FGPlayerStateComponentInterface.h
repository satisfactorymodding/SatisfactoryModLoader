// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FGPlayerStateComponentInterface.generated.h"

/**
* Implement this on Actor Components that are attached to the Player State actors to have them correctly handle player state copying when players are logging in
 * Note that components using this interface must haver Player State as an outer to function correctly, and must have a stable name across different instances of player state.
 */
UINTERFACE(MinimalAPI, Blueprintable)
class UFGPlayerStateComponentInterface : public UInterface
{
	GENERATED_BODY()
};
class FACTORYGAME_API IFGPlayerStateComponentInterface
{
	GENERATED_BODY()
public:
	/** Implementation should copy the data **from** this object **into** the provided component */
	UFUNCTION(BlueprintNativeEvent, Category = "Player State")
	void CopyComponentProperties( UActorComponent* intoComponent );
};