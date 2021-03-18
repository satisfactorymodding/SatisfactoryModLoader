// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGBuildableHologram.h"
#include "FGFloodlightHologram.generated.h"


UENUM()
enum class EFloodlightHologramBuildStep : uint8
{
	FHBS_PlacementAndRotation,
    FHBS_AdjustAngle
};

UENUM()
enum class EFloodlightHologramMountingType : uint8
{
	FHMT_Ground,
    FHMT_Wall
};


/**
 * Hologram for the adjustable flood lights, wall or pole mounted.
 */
UCLASS()
class FACTORYGAME_API AFGFloodlightHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
public:
	AFGFloodlightHologram();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin AFGHologram Interface
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual void ScrollRotate( int32 delta, int32 step ) override;
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual bool DoMultiStepPlacement( bool isInputFromARelease ) override;
	virtual void SerializeConstructMessage( FArchive& ar, FNetConstructionID id ) override;
	// End AFGHologram Interface

protected:
	// Begin AFGHologram Interface
	virtual int32 GetRotationStep() const override;
	// End AFGHologram Interface

	// Begin AFGBuildableHologram Interface
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	// End AFGBuildableHologram Interface

private:
	// Updates the rotation of the fixture mesh.
	UFUNCTION()
	void OnRep_FixtureAngle();

protected:
	/** How is this floodligth mounted. */
	UPROPERTY( EditDefaultsOnly, Category = "FloodlightHologram" )
	EFloodlightHologramMountingType mMountingType = EFloodlightHologramMountingType::FHMT_Ground;

private:
	EFloodlightHologramBuildStep mBuildStep = EFloodlightHologramBuildStep::FHBS_PlacementAndRotation;
	
	/** Current angle of the fixture. */
	UPROPERTY( ReplicatedUsing = OnRep_FixtureAngle )
	int32 mFixtureAngle;

	/** Scene component. */
	UPROPERTY()
	USceneComponent* mLightFixtureComponent;
};
