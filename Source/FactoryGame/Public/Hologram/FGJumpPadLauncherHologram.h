// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGJumpPadHologram.h"
#include "Buildables/FGBuildableJumppad.h"

#include "FGJumpPadLauncherHologram.generated.h"

UENUM()
enum class EJumpPadHologramBuildStep : uint8
{
	JPHBS_PlacementAndRotation,
	JPHBS_AdjustAngle
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGJumpPadLauncherHologram : public AFGJumpPadHologram
{
	GENERATED_BODY()
	
public:
	AFGJumpPadLauncherHologram();

	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin AFGHologram Interface
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual void SetMaterial( class UMaterialInterface* material ) override;
	// End AFGHologram Interface

	// Begin AFGHologram Interface
	virtual void ScrollRotate( int32 delta, int32 step ) override;
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual bool DoMultiStepPlacement( bool isInputFromARelease ) override;
	// End AFGHologram Interface

	/** Net Construction Messages */
	virtual void SerializeConstructMessage( FArchive& ar, FNetConstructionID id ) override;

protected:
	UFUNCTION( BlueprintImplementableEvent, Category = "JumpPad" )
	void OnLaunchAngleAdjusted();

	// Begin AFGHologram Interface
	virtual int32 GetRotationStep() const override;
	// End AFGHologram Interface

	// Begin AFGBuildableHologram Interface
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	// End AFGBuildableHologram Interface

	void SimulateTrajectory();

private:
	UFUNCTION()
	void OnRep_LaunchAngle();

protected:
	UPROPERTY()
	EJumpPadHologramBuildStep mBuildStep = EJumpPadHologramBuildStep::JPHBS_PlacementAndRotation;

	UPROPERTY( VisibleAnywhere, ReplicatedUsing = OnRep_LaunchAngle )
	int32 mLaunchAngle;

	/** The part of the jump pad that angles up and down. */
	UPROPERTY( VisibleAnywhere, Category = "Jump Pad" )
	class UStaticMeshComponent* mLauncherMeshComponent;

	/** The spline component for the trajectory. */
	UPROPERTY( VisibleAnywhere, Category = "Trajectory" )
	class USplineComponent* mSplineComponent;

	/** The instanced spline meshes for the trajectory. */
	UPROPERTY( VisibleAnywhere, Category = "Trajectory" )
	class UFGInstancedSplineMeshComponent* mInstancedSplineMeshComponent;

	/** The scale used for the instances in the spline mesh. */
	UPROPERTY( EditDefaultsOnly, Category = "Trajectory" )
	FVector mTrajectoryMeshScale;

	/** The mesh that shows where launched objects will land. */
	UPROPERTY( VisibleAnywhere, Category = "Trajectory" )
	class UStaticMeshComponent* mDestinationMeshComponent;

	/** How high above the impact location the destination mesh will be. */
	UPROPERTY( EditDefaultsOnly, Category = "Trajectory" )
	float mDestinationMeshHeightOffset;

	/** The distance between meshes on the trajectory spline. */
	UPROPERTY( EditDefaultsOnly, Category = "Trajectory" )
	float mTrajectoryMeshSeparationDistance;

	/** The distance between meshes on the trajectory spline. */
	UPROPERTY( EditDefaultsOnly, Category = "Trajectory" )
    FRotator mDestinationMeshRotation;

	/* Number of arrows used in the instance spline mesh.*/
	UPROPERTY( EditDefaultsOnly, Category = "Trajectory" )
	int32 mNumArrows;
};
