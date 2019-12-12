// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "UnrealString.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "../FGUseableInterface.h"
#include "FGBuildableConveyorBase.h"
#include "Components/SplineComponent.h"
#include "../FGSplineComponent.h"
#include "../FGSignificanceInterface.h"
#include "Components/SplineComponent.h"
#include "../FSplinePointData.h"
#include "../FGSplineComponent.h"
#include "../FGRemoteCallObject.h"
#include "FGBuildableConveyorBelt.generated.h"

/**
 * Valid state for picking up conveyor belt items.
 */
UCLASS()
class UFGUseState_ConveyorBeltValid : public UFGUseState
{
	GENERATED_BODY()
public:
	UFGUseState_ConveyorBeltValid() { mIsUsableState = true; mWantAdditonalData = true; }

public:
	/** index for the looked at item in mItems */
	int32 mItemIndex;

	int8 mRepVersion;
};

UCLASS()
class UFGUseState_ConveyorBeltFullInventory : public UFGUseState
{
	GENERATED_BODY()
public:
	UFGUseState_ConveyorBeltFullInventory() { mIsUsableState = false; mWantAdditonalData = true; }

public:
	/** index for the looked at item in mItems */
	int32 mItemIndex;
};

/**
 * State for when the belt is empty.
 */
UCLASS()
class UFGUseState_ConveyorBeltEmpty : public UFGUseState
{
	GENERATED_BODY()
public:
	UFGUseState_ConveyorBeltEmpty() { mIsUsableState = false; mWantAdditonalData = false; }
};

/**
 * Base for conveyor belts.
 * Assumption: Conveyors are never rotated, rotation is always 0,0,0.
 */
UCLASS(Abstract)
class FACTORYGAME_API AFGBuildableConveyorBelt : public AFGBuildableConveyorBase
{
	GENERATED_BODY()
public:
	AFGBuildableConveyorBelt();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual bool IsComponentRelevantForNavigation( UActorComponent* component ) const override;
	// End AActor interface

	// Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( class AFGCharacterPlayer* byCharacter, const FVector& atLocation, class UPrimitiveComponent* componentHit, FUseState& out_useState ) const override;
	virtual void OnUse_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void OnUseStop_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual bool IsUseable_Implementation() const override;
	virtual void StartIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state  ) override;
	virtual void StopIsLookedAt_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual FText GetLookAtDecription_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) const override;
	// End IFGUseableInterface

	// Begin IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	// End IFGSignificanceInterface


	// Begin AFGBuildableConveyorBase interface
	virtual float FindOffsetClosestToLocation( const FVector& location ) const override;
	virtual void GetLocationAndDirectionAtOffset( float offset, FVector& out_location, FVector& out_direction ) const override;
	// End AFGBuildableConveyorBase interface

	virtual void TogglePendingDismantleMaterial( bool enabled ) override;

	/** Get the velocity of the conveyor where the based actor is. */
	FVector GetVelocityForBase( class AActor* basedActor, class UPrimitiveComponent* baseComponent ) const;

	//~ Begin IFGDismantleInterface
	virtual FVector GetRefundSpawnLocationAndArea_Implementation( const FVector& aimHitLocation, float& out_radius ) const override;
	virtual void Upgrade_Implementation( AActor* newActor ) override;
	//~ End IFGDismantleInterface

	/**
	 * Split this conveyor in two.
	 * First part [0,offset] and second part [offset,length].
	 * @note Callee is responsible for not creating snakes or 'zero belts'.
	 *       I.e. Do not split to close to the beginning or end.
	 * @return The second part of the splitted conveyor; nullptr on failure to split.
	 */
	static TArray< AFGBuildableConveyorBelt* > Split( AFGBuildableConveyorBelt* conveyor, float offset );

	/**
	 * Merge two conveyors.
	 * @return The merged conveyor; nullptr on failure to split.
	 */
	static AFGBuildableConveyorBelt* Merge( TArray< AFGBuildableConveyorBelt* > conveyors );

	/**
	 * Respline a conveyor with the given spline.
	 */
	static AFGBuildableConveyorBelt* Respline( AFGBuildableConveyorBelt* conveyor, const TArray< FSplinePointData >& newSplineData );
	
	/** Get the mesh used for this conveyor. */
	UFUNCTION( BlueprintPure, Category = "Conveyor" )
	FORCEINLINE UStaticMesh* GetSplineMesh() const { return mSplineComponent->mSplineMesh; }
	
	/** Get the spline data for this conveyor. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Conveyor" )
	FORCEINLINE TArray< FSplinePointData > GetSplineData() const { return mSplineData; };
	
	/** Set the spline data for this conveyor belt, only valid to call prior to begin play. */
	void SetSplineData( const TArray< FSplinePointData >& points ) { mSplineData = points; }

	/** Returns the spline component */
	UFUNCTION( BlueprintPure, Category = "Build" )
	FORCEINLINE class UFGSplineComponent* GetSplineComponent() { return mSplineComponent; }

	void OnUseServerRepInput( class AFGCharacterPlayer* byCharacter, int32 itemIndex, int8 repVersion );
protected:
	// Begin AFGBuildableFactory interface
	virtual bool VerifyDefaults( FString& out_message ) override;
	// End AFGBuildableFactory interface

	// Begin AFGBuildableConveyorBase interface
	virtual void TickItemTransforms( float dt ) override;
	// End AFGBuildableConveyorBase interface

private:
	void UpdateItemTransformTick( const FConveyorBeltItem& item, TMap<FName, int32>& instanceCounts, class AFGRadioactivitySubsystem* radioactiveSubsystem );

private:
	friend class AFGConveyorBeltHologram;

	/** Meshes for items. */
	UPROPERTY( Meta = ( NoAutoJson ) )
	TMap< FName, class UInstancedStaticMeshComponent* > mItemMeshMap;

	UFUNCTION()
	void OnRep_SplineData();

	/** Compact representation of mSplineComponent, used for replication and save game */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_SplineData, Meta = (NoAutoJson) )
	TArray< FSplinePointData > mSplineData;

	/** The spline component for this splined factory. */
	UPROPERTY( VisibleAnywhere, Category = "Spline" )
	class UFGSplineComponent* mSplineComponent;

	UPROPERTY( VisibleDefaultsOnly, Category="Audio" )
	class UFGSoundSplineComponent* mSoundSplineComponent;

	/** The ak event to post for the sound spline */
	UPROPERTY( EditDefaultsOnly, Category = "AkComponent" )
	class UAkAudioEvent* mSplineAudioEvent;
};
