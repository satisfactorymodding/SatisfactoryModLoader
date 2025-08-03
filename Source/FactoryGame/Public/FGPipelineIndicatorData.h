// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FGPipelineIndicatorData.generated.h"

/**
 * Struct containing quantized fluid content for a more optimized replication.
 */
USTRUCT(Atomic)
struct FACTORYGAME_API FPipelineIndicatorData
{
	GENERATED_BODY()

	/** Updates the content of this indicator from the provided fluid box, usually belonging to the pipeline. Returns true if there were any changes */
	bool UpdateFromFluidBox(const struct FFluidBox& FluidBox);

	/** Returns the raw flow percentage in this flow indicator, without any smoothing */
	float GetRawFlowPct() const;
	/** Returns the raw content percentage in this flow indicator, without any smoothing */
	float GetRawContentPct() const;
	/** Returns true if this data is stale and should not be interpolated from */
	FORCEINLINE bool IsDataStale() const { return bIsDataStale; }

	/** Returns the smooth values of flow and content for this flow indicator, based on the tick delta time */
	void CalculateSmoothFlowRateAndContentPct(float& smoothFlowRate, float& content, bool& stale, float DeltaTime) const;

	/** Marks this data as stale and disables interpolation for it */
	void MarkDataStale();
private:
	/** Utility functions to pack the raw values for networking */
	static int8 PackFlowRate(float InFlowRate);
	static uint8 PackContent(float InContent);
	
	UPROPERTY()
	int8 PackedFlow{};

	UPROPERTY()
	uint8 PackedContent{};

	/** Whenever this data is considered stale, and should be interpolated from */
	bool bIsDataStale{false};
};
