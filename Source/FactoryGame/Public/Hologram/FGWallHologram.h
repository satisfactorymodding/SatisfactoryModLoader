// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGFactoryBuildingHologram.h"
#include "FGWallHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGWallHologram : public AFGFactoryBuildingHologram
{
	GENERATED_BODY()
public:
	AFGWallHologram();

	// Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	// End AActor Interface

	// Begin AFGHologram interface
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual AActor* GetUpgradedActor() const override;
	virtual bool TryUpgrade( const FHitResult& hitResult ) override;
	virtual bool DoMultiStepPlacement( bool isInputFromARelease ) override;
	virtual void ConfigureActor( AFGBuildable* inBuildable ) const override;
	virtual void ScrollRotate( int32 delta, int32 step ) override;
	// End AFGHologram interface

protected:
	// Begin AFGHologram interface
	virtual int32 GetRotationStep() const override;
	virtual void CheckValidPlacement() override;
	// End of AFGHologram interface

	// Begin AFGFactoryBuildingHologram Interface
	virtual void UpdateZoop() override;
	virtual void ConstructZoop( TArray<AActor*>& out_children ) override;
	virtual FVector ConvertZoopToWorldLocation( const FIntVector& zoop ) const override;
	// End AFGFactoryBuildingHologram Interface

	// Begin AFGBuildableHologram interface
	virtual bool IsHologramIdenticalToActor( AActor* actor, const FVector& hologramLocationOffset ) const override;
	// End AFGBuildableHologram interface

	/** Changes what buildable we're constructing based on an angle. */
	void SelectWallVariantForElevation( float NewAngle );

private:
	void ApplyFoundationFloorSnapping( const FTransform& floorTransform, const FHitResult& hitResult, const FVector& floorSize, const FVector& foundationSize, FVector& out_Location, FRotator& inout_Rotation );

private:	
	/** Width of the wall, from the default buildable. */
	float mWidth;

	/** Height of the wall, from the default buildable. */
	float mHeight;

	/** Elevation of the wall, from the default buildable. */
	float mElevation;

	/** Angular depth of the wall, from the default buildable. */
	float mAngularDepth;

	/** Type of the wall, from the default buildable. */
	uint8 mWallType;

	/** Local vertical snap offset of the hologram, calculated from the wall's angular depth. */
	FVector mHologramVerticalSnapOffset;

	/** Ratios for the snapping zones, how much of the wall to hit for snap to either direction. */
	float mSnapSidesHitZoneRatio;

	/** Whether or not we should use 180 degrees for our rotation step. */
	bool mUse180RotationStep;

	/** Index used to scroll between angled variants of a wall. */
	int32 mAngledVariantIndex;

	TSubclassOf<class AFGBuildableWall> mOriginalWallBuildClass;

	UPROPERTY( CustomSerialization, Replicated )
	class AFGBuildableWall* mUpgradeTarget;

	/** Limits zooping to only lines */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram" )
	bool mOnlyAllowLineZoop;
};
