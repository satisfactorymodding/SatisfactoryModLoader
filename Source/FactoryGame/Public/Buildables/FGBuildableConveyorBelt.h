// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "../../Plugins/Wwise/Source/AkAudio/Classes/AkAudioEvent.h"
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "UnrealString.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "../FGUseableInterface.h"
#include "FGBuildableConveyorBase.h"
#include "Components/SplineComponent.h"
#include "../FGSignificanceInterface.h"
#include "Components/SplineComponent.h"
#include "FGInstancedSplineMeshComponent.h"
#include "../FGRemoteCallObject.h"
#include "FGBuildableConveyorBelt.generated.h"

/**
 * Valid state for picking up conveyor belt items.
 */
UCLASS()
class FACTORYGAME_API UFGUseState_ConveyorBeltValid : public UFGUseState
{
	GENERATED_BODY()
public:
	UFGUseState_ConveyorBeltValid() { mIsUsableState = true; mWantAdditonalData = true; }

public:
	/** index for the looked at item in mItems */
	int32 mItemIndex;

	int8 mRepVersion;

public:
	FORCEINLINE ~UFGUseState_ConveyorBeltValid() = default;
};

UCLASS()
class FACTORYGAME_API UFGUseState_ConveyorBeltFullInventory : public UFGUseState
{
	GENERATED_BODY()
public:
	UFGUseState_ConveyorBeltFullInventory() { mIsUsableState = false; mWantAdditonalData = true; }

public:
	/** index for the looked at item in mItems */
	int32 mItemIndex;

public:
	FORCEINLINE ~UFGUseState_ConveyorBeltFullInventory() = default;
};

/**
 * State for when the belt is empty.
 */
UCLASS()
class FACTORYGAME_API UFGUseState_ConveyorBeltEmpty : public UFGUseState
{
	GENERATED_BODY()
public:
	UFGUseState_ConveyorBeltEmpty() { mIsUsableState = false; mWantAdditonalData = false; }

public:
	FORCEINLINE ~UFGUseState_ConveyorBeltEmpty() = default;
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
	virtual	void SetupForSignificance() override;
	// End IFGSignificanceInterface

	// Begin Buildable interface
	virtual int32 GetDismantleRefundReturnsMultiplier() const override;
	// End Buildable interface

	// Begin AFGBuildableConveyorBase interface
	virtual float FindOffsetClosestToLocation( const FVector& location ) const override;
	virtual void GetLocationAndDirectionAtOffset( float offset, FVector& out_location, FVector& out_direction ) const override;
	// End AFGBuildableConveyorBase interface

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
	 *		 Will dismantle the current conveyor belt on successful split
	 * @param connectNewConveyors - Should the new conveyors be connected to each other after the split
	 * @return The second part of the splitted conveyor; nullptr on failure to split.
	 */
	static TArray< AFGBuildableConveyorBelt* > Split( AFGBuildableConveyorBelt* conveyor, float offset, bool connectNewConveyors );

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
	FORCEINLINE UStaticMesh* GetSplineMesh() const { return mMesh; }

	/** Get the spline data for this conveyor. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "Conveyor" )
	FORCEINLINE TArray< FSplinePointData > GetSplineData() const { return mSplineData; };

	/** Returns the spline component */
	UFUNCTION( BlueprintPure, Category = "Build" )
	FORCEINLINE class USplineComponent* GetSplineComponent() { return mSplineComponent; }

	void OnUseServerRepInput( class AFGCharacterPlayer* byCharacter, int32 itemIndex, int8 repVersion );
protected:
	// Begin AFGBuildableFactory interface
	virtual bool VerifyDefaults( FString& out_message ) override;
	// End AFGBuildableFactory interface

	// Begin AFGBuildableConveyorBase interface
	virtual void TickItemTransforms( float dt ) override;
	// End AFGBuildableConveyorBase interface

private:
	/**
	 * Updates the transform of a single item only.
	 * We need to do this separately as all items are not in the same items array.
	 */
	void TickSingleItemTransform( const FConveyorBeltItem& item, TMap< FName, int32 >& instanceCounts, class AFGRadioactivitySubsystem* radioactiveSubsystem );

	/** Get the that have the "moving conveyor material" in it */
	void GetConveyorMaterials( TArray<UMaterialInterface*, TInlineAllocator<4>>& out_materials );

protected:
	/** Mesh to use for his conveyor. */
	UPROPERTY( EditDefaultsOnly, Category = "Conveyor Belt" )
	class UStaticMesh* mMesh;

	/** Length of the mesh to use for this conveyor. */
	UPROPERTY( EditDefaultsOnly, Category = "Conveyor Belt" )
	float mMeshLength;

private:
	friend class AFGConveyorBeltHologram;

	/** Meshes for items. */
	UPROPERTY( Meta = ( NoAutoJson ) )
	TMap< FName, class UInstancedStaticMeshComponent* > mItemMeshMap;

	/** Compact representation of mSplineComponent, used for replication and save game */
	UPROPERTY( SaveGame, Replicated, Meta = ( NoAutoJson ) )
	TArray< FSplinePointData > mSplineData;

	/** The spline component for this conveyor. Note that this is only the spline. */
	UPROPERTY( VisibleAnywhere, Category = "Spline" )
	class USplineComponent* mSplineComponent;

	/** The spline meshes for this train track. */
	UPROPERTY( VisibleAnywhere, Category = "Spline" )
	class UFGInstancedSplineMeshComponent* mInstancedSplineComponent;

	/** Wwise multiple position playback for the conveyor spline. */
	UPROPERTY( VisibleDefaultsOnly, Category = "Audio" )
	class UFGSoundSplineComponent* mSoundSplineComponent;

	/** The ak event to post for the sound spline */
	UPROPERTY( EditDefaultsOnly, Category = "Audio" )
	class UAkAudioEvent* mSplineAudioEvent;

public:
	FORCEINLINE ~AFGBuildableConveyorBelt() = default;
};
