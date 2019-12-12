#pragma once

#include "CoreMinimal.h"
#include "FSplinePointData.generated.h"

USTRUCT(BlueprintType)
struct FSplinePointData
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SplinePoint)
		struct FVector Location;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SplinePoint)
		struct FVector ArriveTangent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SplinePoint)
		struct FVector LeaveTangent;
};