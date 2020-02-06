// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Camera/CameraModifier.h"
#include "FGCameraModifierLimitLook.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGCameraModifierLimitLook : public UCameraModifier
{
	GENERATED_BODY()
public:
	virtual bool ProcessViewRotation( class AActor* ViewTarget, float DeltaTime, FRotator& OutViewRotation, FRotator& OutDeltaRot );

	/** Sets the default rotation */
	UFUNCTION( BlueprintCallable, Category = "Limited Look" )
	void SetDefaultLookRotator( FRotator inRotator ) { mLookRotator = inRotator; }

	/** Gets the default rotation */
	UFUNCTION( BlueprintPure, Category = "Limited Look" )
	FORCEINLINE FRotator GetDefaultLookRotator() { return mLookRotator; }
public:
	/** The look rotation we use as base point */
	FRotator mLookRotator;

	/** The max rotation in pitch ( abs value ) */
	UPROPERTY( EditDefaultsOnly, Category = "Limited Look" )
	float mMaxPitch;

	/** The max rotation in yaw ( abs value ) */
	UPROPERTY( EditDefaultsOnly, Category = "Limited Look" )
	float mMaxYaw;
};
