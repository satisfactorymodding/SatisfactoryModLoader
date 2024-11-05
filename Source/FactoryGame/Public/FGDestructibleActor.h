// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGClearanceInterface.h"
#include "FGSaveInterface.h"
#include "GeometryCollection/GeometryCollectionActor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Replication/FGStaticReplicatedActor.h"
#include "FGDestructibleActor.generated.h"

class UGeometryCollection;

UENUM(BlueprintType)
enum class EDestructibleActorState : uint8
{
	/** The actor is intact, normal static mesh is visible, geometry collection is hidden */
	DSS_Intact UMETA(DisplayName = "Intact"),
	/** The actor is fracturing right now and can have forces applied to it */
	DSS_Fracturing UMETA(DisplayName = "Fracturing"),
	/** The actor is destroyed and is no longer visible */
	DSS_Destroyed UMETA(DisplayName = "Destroyed")
};

/**
 * This is an actor that should be able to be destroyed by explosions and stuff. Can block cave entrances and stuff.
 * If you make a new rock that should be destructible, then you should make a data only blueprint of this
 */
UCLASS(abstract)
class FACTORYGAME_API AFGDestructibleActor : public AActor, public IFGSaveInterface, public IFGClearanceInterface
{
	GENERATED_BODY()

public:
	AFGDestructibleActor();
	// Begin AActor
	virtual void BeginPlay() override;
	virtual float TakeDamage( float damage, struct FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser ) override;
	// End AActor
	
	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	// Begin IFGClearanceInterface
	virtual void GetClearanceData_Implementation( TArray< FFGClearanceData >& out_data ) const override;
	// End IFGClearanceInterface

	/** Called on server and client when we destruct this actor */
	UFUNCTION( BlueprintImplementableEvent, Category = "Destructible" )
	void PlayDestructEffects();

	UFUNCTION( BlueprintPure, Category="Destructible")
	FVector GetForceLocation() const { return mDestroyedByForceLocation; }

	UFUNCTION( BlueprintImplementableEvent, Category="Destructible" )
	void OnChaosPhysicsCollision(const FChaosPhysicsCollisionInfo& CollisionInfo );

	virtual UStaticMeshComponent* GetStaticMeshComponent() { return mStaticMeshProxy; }

	UFUNCTION(BlueprintCallable)
	bool IsMeshChainSawable(UStaticMesh* Mesh) const;

protected:
	/** Updates the state, flushes net dormancy */
	UFUNCTION(BlueprintCallable)
	void SetDestructibleActorState(EDestructibleActorState newState);
	
	/** Applies destructible actor state to the meshes */
	void ApplyDestructibleActorState();

	UFUNCTION()
	virtual void OnDestructibleFractured();

	/** Destructibles are no longer fully destroyed so here is a moment when any cleanup can be run on child classes for component removal etc. */
	UFUNCTION()
	virtual void OnDesctructibleDestroyed() {}
	
	/** Called when this actor has been fractured and the remnants have been removed */
	void OnFracturingFinished();

	UFUNCTION()
	void OnRep_DestructibleActorState();
	
	/** The mesh that should be rendered before we start going destructible. Used for optimization as it has less triangles */
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "Destructible" )
	UStaticMeshComponent* mStaticMeshProxy;

	/** Geometry collection to use for when this actor is being fractured */
	UPROPERTY( EditAnywhere, Category = "Destructible" )
	UGeometryCollection* mGeometryCollection;

	/** Amount of time the destructible actor should stay in a fractured state before being forcefully removed */
	UPROPERTY( EditAnywhere, Category = "Destructible" )
	float mDestructibleActorFractureTime;
	
	/** State of the actor */
	UPROPERTY( EditAnywhere, SaveGame, ReplicatedUsing=OnRep_DestructibleActorState, Category = "Destructible" )
	EDestructibleActorState mDestructibleActorState;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Transient, Category = "Destructible" )
	UGeometryCollectionComponent* mGeometryCollectionComponent;

	UPROPERTY( VisibleAnywhere, Transient, Category = "Destructible" )
	FTimerHandle mDestructibleRemovalTimerHandle;

	/** Scalar for how much force is applied on fracture */
	UPROPERTY( EditDefaultsOnly, Category = "Destructible" )
	float mDestructionImpulseScale = 1.f;

	/** Bind Chaos Physics Collisions to blueprint event (if false, delegate will not be bound) */
	UPROPERTY( EditDefaultsOnly, Category= "Destructible" )
	bool mBindChaosPhysicsCollisionEvent = false;
	
	/** Location of the boom that killed us (used to apply a general force to the desctruction mesh) */
	UPROPERTY( Replicated )
	FVector mDestroyedByForceLocation;

	// The Radial Force that destroyed this Destructible (set by take damage). Is the radius of the RadialForceComp. Used as a base to change the force of fracturing for visuals
	UPROPERTY( Replicated )
	float mRadialForceDestruction = 0.f;

	UPROPERTY()
	AActor* mDestroyedByActor;
	
private:
	/** Clearance data of this destructible */
	UPROPERTY( EditDefaultsOnly, Category = "Destructible" )
	TArray< FFGClearanceData > mClearanceData;
	
	/** Deprecated, left for savegame compatibility */
	UPROPERTY( SaveGame )
	bool mHasBeenFractured;
public:
	/** Returns the current state of the actor */
	UFUNCTION( BlueprintPure, Category = "Destructible" )
	FORCEINLINE EDestructibleActorState GetDestructibleActorState() const { return mDestructibleActorState; }
};
