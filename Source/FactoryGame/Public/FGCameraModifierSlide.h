// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Camera/CameraModifier.h"
#include "FGCameraModifierSlide.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGCameraModifierSlide : public UCameraModifier
{
	GENERATED_BODY()
public:
	virtual bool ProcessViewRotation( class AActor* ViewTarget, float DeltaTime, FRotator& OutViewRotation, FRotator& OutDeltaRot ) override;

	/** Sets the default rotation */
	UFUNCTION( BlueprintCallable, Category = "Limited Look" )
	void SetDefaultLookRotator( FRotator inRotator ) { mLookRotator = inRotator; }

	/** Gets the default rotation */
	UFUNCTION( BlueprintPure, Category = "Limited Look" )
	FORCEINLINE FRotator GetDefaultLookRotator() { return mLookRotator; }
public:
	/** The look rotation we use as base point */
	FRotator mLookRotator;

	/** The min rotation in pitch  */
	UPROPERTY( EditDefaultsOnly, Category = "Limited Look" )
	float mMinPitch;

public:
	FORCEINLINE ~UFGCameraModifierSlide() = default;
};
