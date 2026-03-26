// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGIntRange.generated.h"

/** Simple closed integer range */
USTRUCT(BlueprintType)
struct FACTORYGAME_API FFGIntRange
{
	GENERATED_BODY()

	/** Minimum value in this range, inclusive */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Int Range" )
	int32 MinimumValue{0};

	/** Maximum value in this range, inclusive */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Int Range" )
	int32 MaximumValue{0};

	friend bool operator==(const FFGIntRange& RangeA, const FFGIntRange& RangeB)
	{
		return RangeA.MinimumValue == RangeB.MinimumValue && RangeA.MaximumValue == RangeB.MaximumValue;
	}

	friend uint32 GetTypeHash(const FFGIntRange Value)
	{
		return HashCombine(GetTypeHash(Value.MinimumValue), GetTypeHash(Value.MaximumValue));
	}
};

template<> struct TStructOpsTypeTraits<FFGIntRange> : TStructOpsTypeTraitsBase2<FFGIntRange>
{
	enum 
	{
		WithZeroConstructor = true,
		WithIdenticalViaEquality = true,
	};
};
