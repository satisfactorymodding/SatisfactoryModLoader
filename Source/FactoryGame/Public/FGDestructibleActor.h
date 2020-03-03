// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "DestructibleActor.h"
#include "FGSaveInterface.h"
#include "FGDestructibleActor.generated.h"

/**
 * This is an actor that should be able to be destroyed by explosions and stuff. Can block cave entrances and stuff.
 * If you make a new rock that should be destructible, then you should make a data only blueprint of this
 */
UCLASS(abstract)
class FACTORYGAME_API AFGDestructibleActor : public ADestructibleActor, public IFGSaveInterface
{
	GENERATED_BODY()

	AFGDestructibleActor();
	
public:
	// Begin Actor Interface
	virtual void BeginPlay() override;
	// End Actor Interface

	virtual float TakeDamage( float damage, struct FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser ) override;

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	/** Called on server and client when we destruct this actor */
	UFUNCTION( BlueprintImplementableEvent, Category = "Destructible" )
	void PlayDestructEffects();

private:
	/** Turn off collision */
	void DisableCollision();
	
	/** Change our static mesh actor to the destructible actor */
	void MakeDestructible();
private:
	/** Called when this actor is fractured */
	UFUNCTION()
	void OnDestructibleFractured( const FVector& hitPoint, const FVector& hitDirection );

	/** Called on client when this is fractured */
	UFUNCTION( NetMulticast, Unreliable )
	void Multicast_OnDestructibleFractured( const FVector& hitPoint, const FVector& hitDirection );
	
	/** The mesh that should be rendered before we start going destructible. Used for optimization as it has less triangles */
	UPROPERTY( VisibleDefaultsOnly, Category = "Destructible" )
	UStaticMeshComponent* mStaticMeshProxy;

	/** So we can save if this has been fractured */
	UPROPERTY( SaveGame )
	bool mHasBeenFractured;

	/** Timer handle for delaying disableing collisison */
	FTimerHandle mSetCollisionTimerHandle;

	/** Timer handle for delaying destroy */
	FTimerHandle mDestroyTimerHandle;

public:
	FORCEINLINE ~AFGDestructibleActor() = default;
};
