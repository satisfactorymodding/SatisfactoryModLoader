// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "../FGDriveablePawn.h"
#include "FGCreatureSeat.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGCreatureSeat : public AFGDriveablePawn
{
	GENERATED_BODY()

	/** Decide on what properties to replicate. */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin AActor Interface
	virtual void BeginPlay() override;

	/** Getter for creature */
	UFUNCTION( BlueprintPure, Category = "Creature" )
	FORCEINLINE class AFGCreature* GetMountedCreature(){ return mMountedCreature; }

	/** Setup the camera attachment */
	virtual void AttachDriver( class AFGCharacterPlayer* driver );
public:
	/** The creature this seat is on */
	UPROPERTY( SaveGame, Replicated, BlueprintReadWrite, Meta = ( ExposeOnSpawn ) )
	class AFGCreature* mMountedCreature;

public:
	FORCEINLINE ~AFGCreatureSeat() = default;
};
