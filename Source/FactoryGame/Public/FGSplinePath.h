// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "GameFramework/Actor.h"
#include "FGSplinePath.generated.h"

UCLASS()
class FACTORYGAME_API AFGSplinePath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGSplinePath();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

public:	
	UPROPERTY( BlueprintReadOnly, Category = "Spline" )
	class USplineComponent* mSpline;
};
