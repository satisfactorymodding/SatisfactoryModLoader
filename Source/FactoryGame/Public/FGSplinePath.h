// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "FGSplinePath.generated.h"

UCLASS()
class FACTORYGAME_API AFGSplinePath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGSplinePath();

public:	
	UPROPERTY( BlueprintReadOnly, Category = "Spline" )
	class USplineComponent* mSpline;
};
