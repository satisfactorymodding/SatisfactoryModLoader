// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DamageTypes/FGDamageType.h"
#include "GameFramework/Actor.h"
#include "FGFlyingBabyCrab.generated.h"

UCLASS()
class FACTORYGAME_API AFGFlyingBabyCrab : public AActor
{
	GENERATED_BODY()

	// Friend creature subsystem in order for it to manage our "nearby baby crabs" list.
	friend class AFGCreatureSubsystem;
public:	
	AFGFlyingBabyCrab();

	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	UFUNCTION( BlueprintPure, Category = "Movement" )
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovementComp() const { return mProjectileMovementComponent; }
	
	/** Whether or not the specified actor is a valid target. */
	UFUNCTION( BlueprintPure, Category = "Combat" )
	bool IsValidTarget( AActor* target ) const;
	
	/** Returns the current target of the baby crab. */
	UFUNCTION( BlueprintPure, Category = "Combat" )
	FORCEINLINE AActor* GetCurrentTarget() const { return mCurrentTarget; }

	/** Returns the crabs which are considered nearby. */
	FORCEINLINE const TArray< AFGFlyingBabyCrab* >& GetNearbyBabyCrabs() const { return mNearbyBabyCrabs; }

	UFUNCTION( BlueprintPure, Category = "Movement" )
	FORCEINLINE float GetSwarmViewDistance() const { return mSwarmViewDistance; }

	UFUNCTION( BlueprintPure, Category = "Combat" )
	FORCEINLINE float GetAggroRadius() const { return mAggroRadius; }

	UFUNCTION( BlueprintPure, Category = "Movement" )
	const FVector& GetHomeLocation() const { return mHomeLocation; }

	UFUNCTION( BlueprintCallable, Category = "Movement" )
	void SetHomeLocation( const FVector& Location );

	/** Explodes the baby crab. */
	UFUNCTION( BlueprintCallable, Category = "BabyCrab" )
	void Explode();

	UFUNCTION( BlueprintCallable, Category = "BabyCrab" )
	void RegisterHostilePlayer( class AFGCharacterPlayer* player );

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	virtual void Destroyed() override;

	virtual void PostNetReceiveLocationAndRotation() override;

	UFUNCTION()
	void OnClientSubsystemsValid();

	void UpdateProjectileComponentSpeed();

	/** Sets the current target of the baby crab. */
	UFUNCTION( BlueprintCallable, Category = "Combat" )
	void SetCurrentTarget( AActor* target );

	/** Called whenever we get a new target. Target can be null. */
	UFUNCTION( BlueprintNativeEvent, Category = "Combat" )
	void OnCurrentTargetChanged( AActor* newTarget );

	/** Called whenever we explode. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Combat" )
	void OnExplode();

	UFUNCTION()
	void OnOverlapBegin( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );

	UFUNCTION()
	void OnDamageReceived( AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser );
	
private:
	void RestartAggroTimer( bool initialStart );

	UFUNCTION()
	void UpdateAggro();
	AActor* SelectAggroTarget( const TArray< AActor* >& TargetCandidates ) const;

	UFUNCTION()
	void OnRep_CurrentTarget();

	UFUNCTION()
	void OnRep_MovementSpeed();

	/** Movment functions. Called by the creature subsystem. Needs to be thread-safe. */
	void TickMovement( float dt );

	/** Helper function for steering towards a direction. Assumes Direction is already normalized. */
	void SteerTowardsDirection( const FVector& Direction, float strength, FVector& out_acceleration );

	void SteerTowardsTarget( FVector& out_acceleration );
	void SteerTowardsHome( FVector& out_acceleration );
	void SteerSwarmMovement( FVector& out_acceleration );
	void SteerAvoidFloor( FVector& out_acceleration );
	void SteerErraticMovement( FVector& out_acceleration );

protected:
	/** Movement speed of the baby crab. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Movement" )
	FFloatInterval mMovementSpeedRange;
	
	/** Movement speed of the baby crab while in combat. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Movement" )
	FFloatInterval mMovementSpeedRangeCombat;
	
	/** Essentially the vision radius of the flying baby crab. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Combat" )
	float mAggroRadius;

	/** How often we want to check for and update relevant targets. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Combat" )
	float mAggroTickRate;

	/** How far away we can see other baby crabs, used for swarm behavior. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Combat" )
	float mSwarmViewDistance;

	/** What damage we should deal to whatever we hit. */
    UPROPERTY( EditDefaultsOnly, Instanced, Category= "Combat" )
    TArray < UFGDamageType* > mDamageTypes;

    /** How much force to apply to characters we hit. */
    UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category= "Combat" )
    float mCharacterLaunchForce;

	/** Used to interpolate steering weight when in combat, based on distance to target. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Combat" )
	float mCombatTurnDistance;

	/** Used to interpolate steering weight when in combat, based on distance to target. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Combat" )
	FFloatInterval mCombatSteeringWeight;

	/** Used to define how far away from the home location the flying baby crabs should move when idling. Won't be exactly the same in practice. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Home" )
	float mHomeRadius;

	/** Used to define steering weight when flying around the home location, based on distance to the home. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Home" )
	FFloatInterval mHomeSteeringWeight;
	
	/** Used to give the flying baby crabs a bit of idle forward movement. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Home" )
	float mIdleMovementWeight;

	/** The crabs will try to stay above the floor at this height. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|FloorAvoidance" )
	float mFloorAvoidanceHeight;

	/** How much the floor avoidance should influence overall movement. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|FloorAvoidance" )
	float mFloorAvoidanceWeight;

	/** How quickly the direction for erratic movement should fluctuate between min and max. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|ErraticMovement" )
	float mErraticMovementDirectionFrequency;

	/** How quickly the weight for erratic movement should fluctuate between min and max. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|ErraticMovement" )
	float mErraticMovementWeightFrequency;

	/** How much erratic movement should influence overall movement. Fluctuates between min and max over time based on noise. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|ErraticMovement" )
	FFloatInterval mErraticMovementWeight;

	/** Avoidance radius of the baby crab, will be a random value between min and max. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Swarm" )
	FFloatInterval mAvoidanceRadius;
	
	/** How much the collision avoidance should influence overall movement. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Swarm" )
	float mAvoidanceWeight;
	
	/** How much the swarm cohesion should affect overall movement. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Swarm" )
	float mCohesionWeight;

	/** How much the swarm cohesion should affect overall movement while we have a target. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Swarm" )
	float mCohesionWeightCombat;

	/** How much the swarm direction should affect overall movement. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Movement|Swarm" )
	float mCohesionDirectionWeight;
	
	/** The flying baby crabs which are considered nearby to this one, used for swarm behavior. */
	UPROPERTY( BlueprintReadOnly, Category = "Movement" )
	TArray< AFGFlyingBabyCrab* > mNearbyBabyCrabs;

	/** The home location of this baby crab. */
	UPROPERTY( BlueprintReadOnly, Category = "Movement" )
	FVector mHomeLocation;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Movement" )
	class UProjectileMovementComponent* mProjectileMovementComponent;

private:
	/** If spawned from a crab hatcher, this will be a reference to it. */
	UPROPERTY()
	class AFGCrabHatcher* mParentCrabHatcher;
	
	/** Our current target. */
	UPROPERTY( ReplicatedUsing = OnRep_CurrentTarget )
	AActor* mCurrentTarget;

	TArray< AFGCharacterPlayer* > mHostilePlayers;

	/** Used to offset the noise used for erratic movement. */
	float mErraticMovementNoiseOffset;

	/** Avoidance radius when flying with other baby crabs. */
	float mCurrentAvoidanceRadius;

	UPROPERTY( ReplicatedUsing = OnRep_MovementSpeed )
	float mMovementSpeed;

	UPROPERTY( ReplicatedUsing = OnRep_MovementSpeed )
	float mMovementSpeedCombat;

	FTimerHandle mAggroTimerHandle;

	bool bHasExploded;
};
