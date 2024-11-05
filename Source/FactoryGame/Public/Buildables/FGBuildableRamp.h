// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildableFoundation.h"
#include "FGBuildableRamp.generated.h"

/**
 * Base class for all kinds of ramps.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableRamp : public AFGBuildableFoundation
{
	GENERATED_BODY()
public:
	AFGBuildableRamp(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Begin IFGSaveInterface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End IFGSaveInterface

	/** Calculates the expected angle of the ramp, based on Elevation and Size. */
	float CalculateRampAngle() const;

public:

	/** Whether or not this is a double ramp. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Ramp" )
	bool mIsDoubleRamp;

	/** Whether or not this is a roof. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Ramp" )
	bool mIsRoof;

	/** Whether or not this ramp is inverted. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Ramp" )
	bool mIsInverted;
};

UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableRampLightweight : public AFGBuildableRamp
{
	GENERATED_BODY()
	AFGBuildableRampLightweight( const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get() );
};
