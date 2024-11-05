// Copyright 2016-2021 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveLinearColor.h"
#include "Curves/CurveFloat.h"
#include "FGCyclicCurve.generated.h"

USTRUCT(BlueprintType)
struct FACTORYGAME_API FCyclicRuntimeFloatCurve
{
	GENERATED_USTRUCT_BODY()

	using ValueType = float;

	FCyclicRuntimeFloatCurve() = default;
	
	UPROPERTY( EditInstanceOnly )
	FRuntimeFloatCurve mCurveData;
};

USTRUCT(BlueprintType)
struct FACTORYGAME_API FCyclicRuntimeColorCurve
{
	GENERATED_USTRUCT_BODY()
	using ValueType = FLinearColor;
	
	FCyclicRuntimeColorCurve() = default;
	
	UPROPERTY( EditInstanceOnly )
	FRuntimeCurveLinearColor mCurveData;
};
