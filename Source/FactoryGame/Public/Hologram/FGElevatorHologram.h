// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGBuildableHologram.h"
#include "FGElevatorTypes.h"
#include "FGElevatorHologram.generated.h"


class AFGBuildableElevator;

UCLASS()
class FACTORYGAME_API AFGElevatorHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
public:
	AFGElevatorHologram();

	//Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//End AActor Interface
	
	//Begin Hologram Interface
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual bool TrySnapToActor(const FHitResult& hitResult) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual void SetHologramNudgeLocation() override;
	virtual void PostHologramPlacement(const FHitResult& hitResult, bool callForChildren) override;
	virtual bool DoMultiStepPlacement(bool isInputFromARelease) override;
	virtual int32 GetBaseCostMultiplier() const override;
	virtual void SpawnChildren(AActor* hologramOwner, FVector spawnLocation, APawn* hologramInstigator) override;
	virtual void PreConfigureActor(AFGBuildable* inBuildable) override;
	virtual void ConfigureActor(AFGBuildable* inBuildable) const override;
	virtual int32 GetRotationStep() const override;
	virtual void GetClearanceData( TArray<const FFGClearanceData*>& out_ClearanceData ) const override;
	virtual bool IsHologramIdenticalToActor( AActor* actor, const FTransform& hologramTransform ) const override;
	virtual void RefreshHologramInstanceInstigators() override;
	virtual void GetIgnoredClearanceActors( TSet<AActor*>& ignoredActors ) const override;
	virtual bool CanNudgeHologram() const override;
	//End Hologram Interface

	// Gets the world space transform for a given child index. Called from the child floor stop SetHologramPositionAndRotation
	FTransform GetTransformForChildStop( int32 childIndex );

	// Builds a floor stop array so we can use the core Elevator Mesh logic to build meshes for this hologram
	void BuildFloorStopInfos();

private:
	UFUNCTION()
	void OnRep_TopTransform();
	
	void UpdateTopTransform( const FHitResult& hitResult, FRotator rotation );

	void UpdateClearance();
	
public:
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf< UFGRecipe > mFloorStopHologramRecipe;


private:
	UPROPERTY()
	TObjectPtr< UInstancedStaticMeshComponent > mHeight1mISMC;

	UPROPERTY()
	TObjectPtr< UInstancedStaticMeshComponent > mHeight4mISMC;

	UPROPERTY()
	TArray< int32 > mHeight1mInstanceIds;

	UPROPERTY()
	TArray< int32 > mHeight4mInstanceIds;
	
	UPROPERTY()
	UStaticMesh* mHeightMesh1m;

	UPROPERTY()
	UStaticMesh* mHeightMesh4m;

	UPROPERTY()
	UStaticMesh* mBottomMesh;

	UPROPERTY()
	UStaticMesh* mTopMesh;
	
	UPROPERTY()
	class AFGElevatorFloorStopHologram* mChildFloorStops[2];

	UPROPERTY( CustomSerialization )
	int32 mActivePointIdx;

	UPROPERTY()
	FTransform mPlacedTransform;

	/** Transform of the top part of the lift, in actor local space. */
	UPROPERTY( ReplicatedUsing = OnRep_TopTransform, CustomSerialization )
	FTransform mTopTransform;

	// Just the height without worrying about direction from placement (ease of access to avoid converting the mTopTransform each time we want to disregard direction)
	UPROPERTY()
	float mHeight;

	// Info about the floor stops used when building the mesh array
	TArray< FElevatorFloorStopInfo > mFloorStopInfos;

	// Clearance Info
	FFGClearanceData mClearanceData;

	UPROPERTY()
	bool mIsReversed;

	UPROPERTY()
	AFGBuildableElevator* mSnappedToElevator;

	UPROPERTY()
	bool mSnappedTop;

	UPROPERTY()
	TArray< AActor* > mHeightInstanceInstigators;

};