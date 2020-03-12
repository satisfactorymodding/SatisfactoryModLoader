// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

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
	

public:
	FORCEINLINE ~AFGPipelineJunctionHologram() = default;
};
