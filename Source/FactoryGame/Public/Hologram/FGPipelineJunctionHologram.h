// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGPipelineAttachmentHologram.h"
#include "FGPipelineJunctionHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGPipelineJunctionHologram : public AFGPipelineAttachmentHologram
{
	GENERATED_BODY()
	
public:
	AFGPipelineJunctionHologram();

protected:
	// Begin AFGHologram interface
	virtual int32 GetRotationStep() const override;
	// End of AFGHologram interface
	
};
