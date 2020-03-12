// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGAttentionPingActor.generated.h"

UCLASS( Blueprintable )
class FACTORYGAME_API AFGAttentionPingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGAttentionPingActor();

	virtual void BeginPlay() override;

	void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	/** Set the player state of the player that spawned this actor */
	void SetOwningPlayerState( class AFGPlayerState* playerState );

	/** player state of the player that spawned this actor */
	UFUNCTION( BlueprintPure, Category = "Attention Ping" )
	FORCEINLINE AFGPlayerState* GetOwningPlayerState() const { return mOwningPlayerState; }

	UFUNCTION()
	void OnRep_OwningPlayerState();

	/** Called when we have the player state replicated so now we can spawn the effects */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic, Category = "Attention Ping" )
	void SpawnAttentionPingEffects();

protected:

	/** The player state of the pawn that spawned this actor */
	UPROPERTY( ReplicatedUsing = OnRep_OwningPlayerState )
	class AFGPlayerState* mOwningPlayerState;
	

public:
	FORCEINLINE ~AFGAttentionPingActor() = default;
};
