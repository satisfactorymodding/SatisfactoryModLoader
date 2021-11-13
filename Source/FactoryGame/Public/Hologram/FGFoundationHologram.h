// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Hologram/FGFactoryBuildingHologram.h"
#include "FGFoundationHologram.generated.h"

/**
 * Base hologram for foundation type buildables.
 */
UCLASS()
class FACTORYGAME_API AFGFoundationHologram : public AFGFactoryBuildingHologram
{
	GENERATED_BODY()
public:
	AFGFoundationHologram();

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin AFGHologram interface
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void GetSupportedBuildModes_Implementation( TArray<TSubclassOf<UFGHologramBuildModeDescriptor>>& out_buildmodes ) const override;
	virtual int32 GetRotationStep() const override;
	// End AFGHologram interface

protected:
	bool CanSnapVertically( class AFGBuildableFoundation* toFoundation, float dirZ ) const;

	// Begin AFGFactoryBuildingHologram interface
	virtual void UpdateZoop() override;
	virtual void ConstructZoop( TArray<AActor*>& out_children ) override;
	virtual FVector ConvertZoopToWorldLocation( const FIntVector& zoop ) const override;
	// End AFGFactoryBuildingHologram interface

	// Begin AFGHologram Interface
	virtual void CheckValidPlacement() override;
	// End AFGHologram Interface
	
	// Begin AFGBuildableHologram Interface
	virtual bool IsHologramIdenticalToBuildable( class AFGBuildable* buildable, const FVector& hologramLocationOffset ) const override;
	// End AFGBuildableHologram Interface

	virtual void SetZoopFromHitresult( const FHitResult& hitResult );

	void CreateDefaultFoundationZoop( const FHitResult& hitResult );
	void CreateVerticalFoundationZoop( const FHitResult& hitResult );

protected:
	/** Defaults from the default buildable. */
	float mSize;
	float mHeight;
	float mElevation;
	bool mIsFrame;
	FFoundationSideSelectionFlags mDisableSnapOn;

	bool mIsSnappedVertically;

	/** The rotation step to use when fine tuning. Currently used when holding SnapToGuidelines. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram" )
	int32 mFineTuneRotationStep;
	
	/** Will snap to the top / bottom of other foundations when aiming at the side and above / below this ratio * height. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram" )
	float mSnapVerticalHitZoneRatio;
	
	/** Will snap to the side of foundations when aiming at the top / bottom within this distance from the edge. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram" )
	float mSideSnapDistanceFromEdgeThreshold;

	/** Limits zooping to only lines */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram" )
	bool mOnlyAllowLineZoop;

	// TODO: Prototype, maybe remove
	/** !PROTOTYPE! - Enables / Disables the corner rotation mode which is accessed by holding ctrl when snapping to certain buildables. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram" )
	bool mAllowCornerRotationMode;

	UPROPERTY( EditDefaultsOnly, Category = "Hologram|BuildMode" )
	TSubclassOf< class UFGHologramBuildModeDescriptor > mBuildModeVerticalZoop;
};
