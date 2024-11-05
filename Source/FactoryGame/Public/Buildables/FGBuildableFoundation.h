// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildableFactoryBuilding.h"
#include "FGBuildableFoundation.generated.h"

/**
 * A foundation to build your factory walls and floors on.
 */
UCLASS(Abstract)
class FACTORYGAME_API AFGBuildableFoundation : public AFGBuildableFactoryBuilding
{
	GENERATED_BODY()
protected:
	AFGBuildableFoundation(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	/** Width of the foundation. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Foundation" )
	float mWidth;

	/** Depth of the foundation. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Foundation" )
	float mDepth;

	/** Height of the foundation. Origo is assumed to be half way between. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Foundation" )
	float mHeight;

	/** Elevation of this foundation if ramp, assumes the ramp to go down towards a positive X. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Foundation" )
	float mElevation;

	/** Whether or not this is a frame piece. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Foundation" )
	bool mIsFrame;

	/** Disable snapping on specific sides. */
	UPROPERTY( EditDefaultsOnly, Category = "Foundation" )
	FFoundationSideSelectionFlags mDisableSnapOn;

	/** Disable attachment snapping on specific sides. */
	UPROPERTY( EditDefaultsOnly, Category = "Foundation" )
	FFoundationSideSelectionFlags mDisableAttachmentSnapOn;

	virtual FSimpleBuildingInfo GetRainOcclusionShape() override { return FSimpleBuildingInfo::DefaultSquareFoundation( this ); }
};

UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableFoundationLightweight : public AFGBuildableFoundation
{
	GENERATED_BODY()
	AFGBuildableFoundationLightweight( const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get() );
};
