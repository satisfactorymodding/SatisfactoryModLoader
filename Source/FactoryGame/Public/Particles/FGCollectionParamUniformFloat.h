// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Distributions/DistributionVector.h"
#include "Runtime/Engine/Classes/Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "FGCollectionParamUniformFloat.generated.h"

///**
// * 
// */
UCLASS()
class FACTORYGAME_API UFGCollectionParamUniformFloat : public UDistributionVector
{
	GENERATED_BODY()

	UFGCollectionParamUniformFloat();

public:
	virtual bool IsPostLoadThreadSafe() const override;
	virtual FVector	GetValue( float F = 0.f, UObject* Data = NULL, int32 LastExtreme = 0, struct FRandomStream* InRandomStream = NULL ) const;

public:
	UPROPERTY(EditAnywhere)
	UMaterialParameterCollection* Collection;

	UPROPERTY(EditAnywhere)
	FName WindDirectionParamName;

	UPROPERTY(EditAnywhere)
	FName WindIntensityParamName;

	UPROPERTY(EditAnywhere)
	float IntensityMin;

	UPROPERTY(EditAnywhere)
	float IntensityMax;

public:
	FORCEINLINE ~UFGCollectionParamUniformFloat() = default;
};
