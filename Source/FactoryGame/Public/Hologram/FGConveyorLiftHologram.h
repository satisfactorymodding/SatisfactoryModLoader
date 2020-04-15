// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGSplineHologram.h"
#include "../FGFactoryConnectionComponent.h"
#include "FGConveyorLiftHologram.generated.h"


UCLASS()
class FACTORYGAME_API AFGConveyorLiftHologram : public AFGSplineHologram
{
	GENERATED_BODY()
public:
	AFGConveyorLiftHologram();

	// Begin AActor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	// End AActor Interface

	// Begin AFGHologram Interface
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual bool DoMultiStepPlacement(bool isInputFromARelease) override;
	virtual bool TryUpgrade( const FHitResult& hitResult ) override;
	virtual AActor* GetUpgradedActor() const override;
	virtual int32 GetBaseCostMultiplier() const override;
	virtual void CheckClearance() override;
	// End AFGHologram Interface

	// Begin FGConstructionMessageInterface
	virtual void SerializeConstructMessage( FArchive& ar, FNetConstructionID id ) override;
	//virtual void ClientPreConstructMessageSerialization() override;
	virtual void ServerPostConstructMessageDeserialization() override;
	// End FGConstructionMessageInterface

	virtual void OnPendingConstructionHologramCreated_Implementation( AFGHologram* fromHologram ) override;

	/** Get the current height for this lift hologram. */
	float GetHeight() const { return FMath::Abs( mTopTransform.GetTranslation().Z ); }


protected:
	// Begin AFGBuildableHologram Interface
	virtual void CheckValidFloor() override;
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	virtual void ConfigureComponents( class AFGBuildable* inBuildable ) const override;
	// End AFGBuildableHologram Interface

	// Begin AFGHologram interface
	virtual int32 GetRotationStep() const override;
	// End of AFGHologram interface

	FTransform GetTopTransform() const { return mTopTransform; }


	virtual void CheckValidPlacement() override;

private:
	UFUNCTION()
	void OnRep_TopTransform();

	void UpdateClearance();

	UFUNCTION()
	void OnRep_ArrowDirection();

	bool CanConnectToConnection( UFGFactoryConnectionComponent* from, UFGFactoryConnectionComponent* to ) const;

protected:
	//@todonow Max height etc.

	// Get's the base location for guide lines for the hologram
	FVector GetGuideLinesBaseLocation() const;

	// Pool for Guide Lines
	TMap<class UObject*, class AFGBuildGuide*> mGuideLineBuildings;

private:
	/** The two connection components for this conveyor. */
	UPROPERTY()
	class UFGFactoryConnectionComponent* mConnectionComponents[ 2 ];

	/** The connections we've made. */
	UPROPERTY()
	class UFGFactoryConnectionComponent* mSnappedConnectionComponents[ 2 ];

	/** If we upgrade another conveyor lift this is the belt we replace. */
	UPROPERTY()
	class AFGBuildableConveyorLift* mUpgradedConveyorLift;

	/** Transform of the top part of the lift, in actor local space. */
	UPROPERTY( ReplicatedUsing = OnRep_TopTransform /*, CustomSerialization*/ )
	FTransform mTopTransform;

	/** Some snap and height restrictions */
	float mStepHeight;
	float mMinimumHeight;
	float mMaximumHeight;

	/** Cached variables fetched and calculated from the buildable. */
	float mMeshHeight;
	UPROPERTY()
	class UStaticMesh* mBottomMesh;
	UPROPERTY()
	class UStaticMesh* mMidMesh;
	UPROPERTY()
	class UStaticMesh* mTopMesh;
	UPROPERTY()
	class UStaticMesh* mJointMesh;

	/** All the meshes along this lift. */
	TArray< UStaticMeshComponent* > mMeshes;

	/** Used to replicate the direction arrow. */
	UPROPERTY( ReplicatedUsing = OnRep_ArrowDirection )
	EFactoryConnectionDirection mArrowDirection;

	/** Arrow to indicate the direction of the lift while placing it. */
	UPROPERTY()
	class UStaticMeshComponent* mArrowComponent;

public:
	FORCEINLINE ~AFGConveyorLiftHologram() = default;
};
