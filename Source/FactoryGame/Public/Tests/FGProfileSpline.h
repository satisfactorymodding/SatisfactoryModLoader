// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGProfileSpline.generated.h"


UCLASS()
class FACTORYGAME_API AFGProfileSpline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGProfileSpline();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void StartProfile();	

	// Runtime length of the spline in minutes.
	UPROPERTY(BlueprintReadOnly)
	float Duration;

	UFUNCTION(BlueprintImplementableEvent)
	float GetCurrentDuration() const;

	UFUNCTION(BlueprintImplementableEvent)
	FTransform GetCurrentView() const;
	
};
