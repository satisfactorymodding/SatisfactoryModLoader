// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGSubsystem.h"
#include "ItemAmount.h"
#include "FGRadioactivitySubsystem.generated.h"


/** Description of a radioactive emitter. */
struct FRadioactiveEmitter
{
public:
	FRadioactiveEmitter() :
		UID( INDEX_NONE ),
		ItemDecay( 0.0f ),
		ItemAmount( 0 )
	{
	}

public:
	/** Optional unique ID for this emitter (unique per source). INDEX_NONE for set and forget emitters. */
	int32 UID;

	/** Decays per second for one item. */
	float ItemDecay;
	/** Number of items. */
	int32 ItemAmount;

	/** Location where radiation is emitted. */
	FVector LocalLocation;
	FVector CachedWorldLocation;
};


/** Description of a radioactive source. */
USTRUCT()
struct FRadioactiveSource
{
	GENERATED_BODY()
public:
	/** Where the emitters are attached. */
	UPROPERTY()
	USceneComponent* AttachRoot;


	TArray< FRadioactiveEmitter > Emitters;
};


/**
 * Actor for handling the radioactive items.
 */
UCLASS( Blueprintable, abstract, hidecategories = ( Actor, Input, Replication, Rendering, "Actor Tick" ) )
class FACTORYGAME_API AFGRadioactivitySubsystem : public AFGSubsystem
{
	GENERATED_BODY()
public:
	AFGRadioactivitySubsystem();

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void Tick( float dt ) override;
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;
	// End AActor interface

	UFUNCTION()
	void OnActorSpawned( AActor* spawnedActor );
	UFUNCTION()
	void OnActorDestroyed( AActor* destroyedActor );

	/** Get the radioactivity subsystem, this should always return something unless you call it really early. */
	static AFGRadioactivitySubsystem* Get( UWorld* world );

	/** Get the radioactivity subsystem from a world context, this should always return something unless you call it really early. */
	UFUNCTION( BlueprintPure, Category = "Radioactivity", DisplayName = "GetRadioactivitySubsystem", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGRadioactivitySubsystem* Get( UObject* worldContext );

	/**
	 * Adds/Updates an radioactive emitter.
	 * If emitter has an UID we'll look for an existing emitter to update before adding a new one.
	 * Calling AddSource multiple times adds multiple emitters.
	 *
	 * @param owner				The object the emitter is located at.
	 * @param attachRoot		root to attach the radiation to. Can be nullptr, @see location.
	 * @param attachLocation	The location of the radioactive item. Local location if root is set; otherwise a world location is assumed.
	 * @param itemClass			The radioactive item.
	 * @param itemAmount		The amount of the radioactive item.
	 * @param UID				(optional) unique identifier for later update the emitter, INDEX_NONE
	 */
	void SetEmitter( UObject* owner,
					 USceneComponent* attachRoot,
					 const FVector& attachLocation,
					 TSubclassOf< UFGItemDescriptor > itemClass,
					 int32 itemAmount,
					 int32 UID = INDEX_NONE );

	/**
	 * @see overload
	 *
	 * @param decay     Decays per second for this source.
	 */
	void SetEmitter( UObject* owner,
					 USceneComponent* attachRoot,
					 const FVector& attachLocation,
					 float decay,
					 int32 UID = INDEX_NONE );

	/** Removes a specific emitter. */
	void RemoveEmitter( UObject* owner, int32 UID );
	
	/** Remove all the emitters but preserves the memory allocations. */
	void ResetEmitters( UObject* owner );

	/** Remove all emitters and free the memory allocations. */
	void RemoveEmitters( UObject* owner );

	/** Calculates the radiation intensity at a given distance */
	static float calculateIntensity( int32 itemAmount, float itemDecay, float distance, float radiationFalloffByDistance );

private:
	FRadioactiveSource& FindOrAddSource( UObject* owner );
	FRadioactiveSource* FindSource( UObject* owner );
	FRadioactiveEmitter& FindOrAddEmitter( TArray< FRadioactiveEmitter >& emitters, int32 UID );
	int32 FindEmitter( TArray< FRadioactiveEmitter >& emitters, int32 UID );

private:
	/** Radiation levels lower than this are ignored. (A good number is around 0.0001) */
	float mMinRadiationThreshold;

	/** How much radiation falls off during distance. (A good number is around 0.08) */
	float mRadiationFalloffByDistance;

	/** The closest we can get to any radiation source. This can greatly limit the radiation received from items in the players inventory.. */
	float mMinDistanceToSource;

	/** The type of damage radiation deals. */
	TSubclassOf< class UFGDamageType > mRadiationDamageType;

	//@todooptimize This can be optimized with an array if profiler says anything.
	/** All the radioactive sources. */
	UPROPERTY()
	TMap< UObject*, FRadioactiveSource > mSources;

	/** All actors that can take damage from radiation. */
	UPROPERTY()
	TArray< class AActor* > mAffectedActors;

	/** All actors cached locations and exposures to radiation, this becomes invalid when a pawn is added/removed. */
	TArray< FVector > mCachedLocations;
	TArray< float > mCachedExposures;

	/** The max accumulated intensity that can be registered from radioactive emitters */
	float mMaxIntensity;
};
