// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGFactoryHologram.h"
#include "FGTrainPlatformHologram.generated.h"

/**
 *	Base Hologram class for constructing train platform buildings (Stations, Cargo, Empty etc.) as they all require a child RailroadTrack hologram
 */
UCLASS()
class FACTORYGAME_API AFGTrainPlatformHologram : public AFGFactoryHologram
{
	GENERATED_BODY()
	
public:
	//Ctor
	AFGTrainPlatformHologram();

	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	// Begin Actor Interface
	virtual void BeginPlay() override;
	// End Actor Interface

	// Begin AFGHologram interface
	void ScrollRotate( int32 delta, int32 step ) override;
	virtual void SpawnChildren( class UFGBuildGunStateBuild* state ) override;
	virtual AActor* Construct( TArray< AActor* >& out_children ) override;
	// End AFGHologram interface

protected:
	// Begin AFGHologram interface
	virtual USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName ) override;
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	virtual void ConfigureComponents( class AFGBuildable* inBuildable ) const override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual int32 GetRotationStep() const override;
	// End AFGHologram interface

	/** Check for platform connections to snap to */
	class UFGTrainPlatformConnection* FindOverlappingConnectionComponent( const FVector& location, float actorOverlapRadius, float toleranceRadius, bool ignoreSelf, bool ignoreIsConnected ) const;

protected:
	/** Overrides floor snapping and forces platforms to only snap to other platforms (not true for stations, true for other platforms) */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram" )
	bool mRequireSnapToPlatform;

	UPROPERTY( EditDefaultsOnly, Category = "Hologram" )
	TSubclassOf< class UFGRecipe > mRailroadTrackRecipe;

	/** The Railroad hologram */
	UPROPERTY( Replicated )
	class AFGRailroadTrackHologram* mRailroadTrackHologram;

	/** The components of this hologram used for detecting platform snapping */
	UPROPERTY()
	class UFGTrainPlatformConnection* mPlatformConnectionComponents[ 2 ]; 

	/** Stores a reference to the other platforms this hologram is connecting to */
	UPROPERTY()
	class UFGTrainPlatformConnection* mConnectedPlatformComponents[ 2 ];


private:
	/** radius to allow snapping to occur*/
	float mSnapDistance;

	/** radius to check for potential actors (platforms) containing connection components */
	float mActorOverlapCheckRadius;

	/** radius to allow component overlap checks to succeed after snapping */
	float mStrictOverlapDistance;

	/** Distance from hitlocation to break snap, used to eliminate wibbily wobbily where holograms snap, and then alter their snap next frame the new location */
	float mBreakSnapDistance;

	/** Track whether this platform is flipped, is only assigned to snapped buildings */
	bool mIsOrientationReversed;

	/** Track whether this object is scrolled (flipped) while snapped */
	int32 mScrollTrackDirection;

	/** Track changes to the scroll direction */
	int32 mPreviousScrollTrackDirection;

};
