// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGFactoryHologram.h"
#include "FGDockingStationHologram.generated.h"

struct FVehiclePathVisualizationHandle;
class AFGVehiclePathNode;

UCLASS()
class FACTORYGAME_API AFGDockingStationHologram : public AFGFactoryHologram
{
	GENERATED_BODY()
public:
	AFGDockingStationHologram();

	// Begin AFGBuildableHologram interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual bool ShouldBuildGunHitVehiclePaths() const override;
	virtual bool TrySnapToActor(const FHitResult& hitResult) override;
	virtual void PostHologramPlacement(const FHitResult& hitResult, bool callForChildren = true) override;
	virtual void PreConfigureActor(class AFGBuildable* inBuildable) override;
	virtual void CheckValidPlacement() override;
	virtual void ScrollRotate(int32 delta, int32 step) override;
	// End AFGBuildableHologram interface
protected:
	AFGVehiclePathNode* GetPathNodeFromHitResult( const FHitResult& hitResult ) const;

	/** Maximum elevation of the path point above the terrain. Placement will be invalid for larger elevation */
	UPROPERTY( EditDefaultsOnly, Category = "Docking Station" )
	float mMaxPathPointElevation{100.0f};

	/** Snap distance at which the docking station will be snapped to the end or the start of the path segment, as opposed to splitting the segment */
	UPROPERTY( EditDefaultsOnly, Category = "Docking Station" )
	float mSegmentEndPointSnapDistance{800.0f};

	/** Z offset of the path point from its default location */
	UPROPERTY( CustomSerialization )
	float mPathPointElevationOffset{0.0f};

	FVector mPathPointRelativeLocation{ForceInit};
	int32 mSnapVehiclePathDirectionIndex{0};

	/** Active handle to the path visualization, valid only for locally instigated holograms */
	TSharedPtr<FVehiclePathVisualizationHandle> mActivePathVisualizationHandle;
};
