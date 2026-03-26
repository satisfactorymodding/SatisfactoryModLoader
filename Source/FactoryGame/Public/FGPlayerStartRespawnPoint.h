// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "FGPlayerStartRespawnPoint.generated.h"

class AFGCharacterPlayer;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPlayerRespawnFromRespawnPointDelegate, AFGCharacterPlayer*, character );

UCLASS(Blueprintable)
class FACTORYGAME_API AFGPlayerStartRespawnPoint : public APlayerStart
{
	GENERATED_BODY()
public:
	AFGPlayerStartRespawnPoint();

	static const FName STATIC_PLAYER_START_TAG;

	/** Called by the server when the player finishes respawning using this respawn point */
	UPROPERTY( BlueprintAssignable, Category = "Respawn Point" )
	FOnPlayerRespawnFromRespawnPointDelegate OnPlayerRespawnFromRespawnPoint;
};
