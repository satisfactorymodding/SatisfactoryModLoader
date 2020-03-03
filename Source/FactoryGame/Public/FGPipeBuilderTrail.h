// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGPipeBuilderTrail.generated.h"

UCLASS( Config = Engine )
class FACTORYGAME_API AFGPipeBuilderTrail : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFGPipeBuilderTrail();

	/** Adds a pipeline that the trail should traverse */
	void AddPipeline( class AFGBuildablePipeline* inPipe );

	/** Stars moving if we have any pipes to traverse */
	void StartSplineMovement();

	/** Starts the effect */
	void PlayBuildEffect();

	/** Called when one build effect has completed */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|PipeBuilderTrail" )
	void EffectDone();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	/** Saved pipelines we have to traverse */
	UPROPERTY()
	TArray< class AFGBuildablePipeline* > mPipesToTraverse;
	
	/** Pipeline we are currently traversing */
	UPROPERTY()
	class AFGBuildablePipeline* mCurrentPipeline;

	/** Cached spline to traverse */
	UPROPERTY()
	class USplineComponent* mSpline;

	/** Current distance along spline 0-1 */
	float mCurrentDistance; 

	/** Max distance of current spline being traversed */
	float mMaxSplineDistance;

	/** How long it should take for trail to complete the spline movement in seconds */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|PipeBuilderTrail" )
	float mSpeed;

	/** Indicates if we are currently moving along a spline */
	bool mDoSplineMovement;

public:
	FORCEINLINE ~AFGPipeBuilderTrail() = default;
};
