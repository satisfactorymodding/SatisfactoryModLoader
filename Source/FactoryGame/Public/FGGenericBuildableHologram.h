// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"

#include "Hologram/FGBuildableHologram.h"
#include "FGGenericBuildableHologram.generated.h"

UENUM()
enum class EBeamSnappingMode : uint8
{
	BSM_None				UMETA( DisplayName = "None" ),
	BSM_Center				UMETA( DisplayName = "Center" ),
	BSM_KeepUpright			UMETA( DisplayName = "Snapping allowed, but kept upright" ),
	BSM_AllSides			UMETA( DisplayName = "All sides" )
};

UENUM()
enum class EPillarSnappingMode : uint8
{
	PSM_None				UMETA( DisplayName = "None" ),
	PSM_KeepUpright			UMETA( DisplayName = "Snapping allowed, but kept upright" ),
	PSM_AllSides			UMETA( DisplayName = "All sides" )
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGGenericBuildableHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
public:
	AFGGenericBuildableHologram();

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface
	
	// Begin AFGHologram interface
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual int32 GetRotationStep() const override;
	// End AFGHologram interface
	
protected:
	// Begin AFGBuildableHologram interface
	virtual bool IsHologramIdenticalToBuildable( AFGBuildable* buildable, const FVector& hologramLocationOffset ) const override;
	// End AFGBuildableHologram interface
	
protected:
	/** Are you allowed to rotate this attachment on the walls surface. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Snapping" )
	bool mIsWallRotationAllowed;

	/** Whether or not it is possible to snap to the floor. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Snapping" )
	bool mCanSnapToFoundationFloor;
	
	/** Whether or not it is possible to snap to the ceiling. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Snapping" )
	bool mCanSnapToFoundationCeiling;

	/** Whether or not it is possible to snap to the side of foundations. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Snapping" )
	bool mCanSnapToFoundationSide;

	/** Whether or not it is possible to snap to walls. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Snapping" )
	bool mCanSnapToWalls;

	/** Whether or not it is possible to snap to angular walls. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Snapping" )
	bool mCanSnapToAngularWalls;

	/** Whether or not it is possible to snap to beams. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Snapping" )
	EBeamSnappingMode mBeamSnappingMode;

	/** Whether or not it is possible to snap to pillars. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Snapping" )
	EPillarSnappingMode mPillarSnappingMode;

	/** The rotation step for when rotating, if 0 then use the default granularity. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram" )
	int32 mRotationStep;

	/** Snapping offset of this attachment on the walls surface. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Snapping" )
	FVector2D mWallSnapOffset;

	/** What axis to snap with when snapping to foundations and walls. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Snapping" )
	TEnumAsByte<EAxis::Type> mSnapAxis;

	/** Distance to inset the hologram when attaching to a foundation. */
	UPROPERTY( EditDefaultsOnly, Category = "Hologram|Snapping" )
	float mFoundationSnappingInset;
};
