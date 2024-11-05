// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildablePipePart.h"
#include "FGPipeHyperStart.generated.h"


/**
 * Pipeline for transferring liquid and gases to factory buildings.
 */
UCLASS()
class FACTORYGAME_API AFGPipeHyperStart : public AFGBuildablePipeHyperPart
{
	GENERATED_BODY()
	public:

	// Begin AFGBuildableFactory interface
	virtual bool CanProduce_Implementation() const override;
	// End AFGBuildableFactory interface

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Hyper Tube" )
	float mOpeningOffset = 350.0f;

	/**Set value to above 1 to give the player a small boost when entering pipes in slow speed. 
	   Could be exploited if made too big, but it felt better and clearer feedback about slowdowns if it was a little above the usual min speed when doing initial tests.*/
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Hyper Tube" )
	float mInitialMinSpeedFactor = 1.4f;
};



