// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Hologram/FGSplineHologram.h"
#include "FGFactoryConnectionComponent.h"
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
	// End AActor Interface

	// Begin AFGHologram Interface
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual bool DoMultiStepPlacement(bool isInputFromARelease) override;
	virtual bool TryUpgrade( const FHitResult& hitResult ) override;
	virtual AActor* GetUpgradedActor() const override;
	virtual int32 GetBaseCostMultiplier() const override;
	virtual float GetHologramHoverHeight() const override;
	virtual void GetIgnoredClearanceActors( TArray< AActor* >& ignoredActors ) const override;
	virtual void GetSupportedBuildModes_Implementation( TArray< TSubclassOf< UFGHologramBuildModeDescriptor > >& out_buildmodes ) const override;
	virtual void PostHologramPlacement() override;
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

	void UpdateConnectionDirections();

	virtual void CheckValidPlacement() override;

private:
	void UpdateTopTransform( const FHitResult& hitResult, FRotator rotation );

	UFUNCTION()
	void OnRep_TopTransform();

	void UpdateClearance();

	UFUNCTION()
	void OnRep_ArrowDirection();

	UFUNCTION()
	void OnRep_SnappedPassthroughs();

	bool CanConnectToConnection( UFGFactoryConnectionComponent* from, UFGFactoryConnectionComponent* to ) const;

protected:
	// Forced direction resulting from a snap to a passthrough
	FVector mForcedNormalDirection;

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
	UPROPERTY( ReplicatedUsing = OnRep_TopTransform, CustomSerialization )
	FTransform mTopTransform;

	/** Some snap and height restrictions */
	float mStepHeight;
	float mMinimumHeight;
	float mMaximumHeight;
	float mMinimumHeightWithPassthrough;

	/** Cached variables fetched and calculated from the buildable. */
	float mMeshHeight;
	UPROPERTY()
	class UStaticMesh* mBottomMesh;
	UPROPERTY()
	class UStaticMesh* mMidMesh;
	UPROPERTY()
	class UStaticMesh* mHalfMidMesh;
	UPROPERTY()
	class UStaticMesh* mTopMesh;
	UPROPERTY()
	class UStaticMesh* mJointMesh;
	UPROPERTY( EditDefaultsOnly )
	class UStaticMesh* mPassthroughBottomMesh;

	UPROPERTY( EditDefaultsOnly )
	class UStaticMesh* mPassthroughTopMesh;

	/** All the meshes along this lift. */
	TArray< UStaticMeshComponent* > mMeshes;

	/** The Fog planes for this lift. So that we can hide them when snapping to passthroughs */
	UStaticMeshComponent* mFogPlaneComp0;
	UStaticMeshComponent* mFogPlaneComp1;

	UPROPERTY( ReplicatedUsing = OnRep_SnappedPassthroughs )
	TArray< class AFGBuildablePassthrough* > mSnappedPassthroughs;

	/** Used to replicate the direction arrow. */
	UPROPERTY( ReplicatedUsing = OnRep_ArrowDirection )
	EFactoryConnectionDirection mArrowDirection;

	/** Arrow to indicate the direction of the lift while placing it. */
	UPROPERTY()
	class UStaticMeshComponent* mArrowComponent;
	
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|BuildMode" )
	TSubclassOf< class UFGHologramBuildModeDescriptor > mBuildModeReverse;
};

