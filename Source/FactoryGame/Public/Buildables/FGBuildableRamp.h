// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Buildables/FGBuildableFoundation.h"
#include "FGBuildableRamp.generated.h"

/**
 * Base class for all kinds of ramps.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableRamp : public AFGBuildableFoundation
{
	GENERATED_BODY()
public:
	AFGBuildableRamp();

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
};
