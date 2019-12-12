// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGProjectile.h"
#include "FGDestructiveProjectile.generated.h"

/** Holds the information necessary for spawning destroyed effects after all overlap calculations */
USTRUCT()
struct FDestroyedFoliageEffectData
{
	GENERATED_BODY()

	FDestroyedFoliageEffectData() :
		SpawnLocation( FVector::ZeroVector ),
		DestroyedEffect( nullptr ),
		Priority( 0 )
	{}
	
	FDestroyedFoliageEffectData( FVector spawnLocation, UParticleSystem* destroyedEffect, int32 priority ) :
		SpawnLocation( spawnLocation ),
		DestroyedEffect( destroyedEffect ),
		Priority( priority )
	{}

	bool operator<( const FDestroyedFoliageEffectData& other ) const { return Priority > other.Priority; };

	UPROPERTY()
	FVector SpawnLocation;
	UPROPERTY()
	class UParticleSystem* DestroyedEffect;
	UPROPERTY()
	int32 Priority;
};


/**
 *  Base class for any projectile that should destroy foliage or actors
 *	@todo: Optimize to collect overlapped foliage if attached to a static actor so that we don't need to populate on detonate
 */
UCLASS()
class FACTORYGAME_API AFGDestructiveProjectile : public AFGProjectile
{
	GENERATED_BODY()

public:
	AFGDestructiveProjectile();

	// Actor initialization
	//MODDING EDIT PostInitialize crashed  when creating a blueprint child
	//virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	// End Actor Initialization

	/** handle hit override, calls super */
	virtual void OnImpact( const FHitResult& hitResult ) override;

	FORCEINLINE class USphereComponent* GetDesctructionCollisionComponent() const { return mDestructionCollisionComp; }

	virtual void PopulateDestructionContainers();

protected:
	/** trigger explosion */
	virtual void DealExplosionDamage( const FHitResult& impact ) override;

	/** Handle the destruction and removal of foliage */
	virtual void HandleFoliageDestruction( );

	/** Handle the destruction of actors that meet the criteria */
	virtual void HandleActorDestruction( );

	/** [client] explosion has happened, called by OnRep_Exploded will spawn client side particle effects */
	/*	This removes the need for the server to broadcast all transforms and particle systems on detonation */
	virtual void OnNotifiedExploded() override;

protected:
	/** Collision Component used to determine which objects should be considered for destruction */
	UPROPERTY( EditDefaultsOnly, Category = "Desctruction" )
	class USphereComponent* mDestructionCollisionComp;

	/** Should actors implementing destructable interfaces be considered for destruction */
	UPROPERTY( EditDefaultsOnly, Category = "Destruction" )
	bool mDestroysRelevantActors;

	/** Should foliage be considered for destruction */
	UPROPERTY( EditDefaultsOnly, Category = "Destruction" )
	bool mDestroysFoliage;

	/** Any amount of particle systems over this limit will not be spawned */
	UPROPERTY( EditDefaultsOnly, Category = "Destruction" )
	int32 mMaxParticleSpawnsPerDetonation;

private:
	/** Holds a list of all overlapped foliage mesh components (HierarchicalInstancedStaticMesh) with the blast radius */
	TArray< class UHierarchicalInstancedStaticMeshComponent* > mOverlappedHISMComponents;

	/** Holds a list of all actors within the blast radius implementing IFGExplosiveDestructableInterface */
	TArray< AActor* > mRelevantOverlappedActors;
};
