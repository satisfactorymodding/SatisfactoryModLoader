// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"

#include "OnlineStatData.generated.h"

/** Base implementation for an online stat. */
USTRUCT(BlueprintType)
struct FOnlineStatDataBase : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=OnlineStat)
	FString StatId;
};

/** Generic online stat tied to a gameplay event. */
USTRUCT(BlueprintType)
struct FOnlineStatData : public FOnlineStatDataBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=OnlineStat)
	FGameplayTag GameplayEvent;
};

/** Aggregated gameplay stat, will increment for every stat with a value above 0. */
USTRUCT(BlueprintType)
struct FOnlineStatDataAggregated : public FOnlineStatDataBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=OnlineStat)
	TArray<FGameplayTag> AggregatedStatList;
};
