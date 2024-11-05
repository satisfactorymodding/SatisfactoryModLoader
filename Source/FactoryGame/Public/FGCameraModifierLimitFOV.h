// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraModifier.h"
#include "FGCameraModifierLimitFOV.generated.h"

UCLASS( NotBlueprintable )
class FACTORYGAME_API UFGCameraModifierLimitFOV : public UCameraModifier
{
	GENERATED_BODY()
public:
	UFGCameraModifierLimitFOV();

	// Begin UCameraModifier interface
	virtual void ModifyCamera(float DeltaTime, FVector ViewLocation, FRotator ViewRotation, float FOV, FVector& NewViewLocation, FRotator& NewViewRotation, float& NewFOV) override;
	// End UCameraModifier interface

	/** Allows camera modifier to modify the FOV scaling applied by the FG game settings */
	float ModifyFOVScaling( float FOVScale ) const;

	/** Sets the target FOV for this camera modifier. Will automatically engage the FOV lock. */
	UFUNCTION( BlueprintCallable, Category = "Camera Modifier Limit FOV" )
	void SetTargetFOV( float NewFOV );

	/** Resets the target FOV. The camera FOV will automatically fade out to the default FOV */
	UFUNCTION( BlueprintCallable, Category = "Camera Modifier Limit FOV" )
	void ResetTargetFOV();
	
	/** Checks if the camera modifier is currently active. It being present does not mean that it is active. */
	FORCEINLINE bool IsCameraModifierActive() const { return mCameraModifierActive; }
public:
	/** Amount of time (in seconds) it takes to fade out from the FOV */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Camera Modifier Limit FOV" )
	float mFadeOutDuration;
private:
	/** True if we currently should have an effect on player FOV */
	bool mCameraModifierActive{false};
	/** FOV that we should have when this modifier is engaged */
	float mTargetFOV{0.0f};
	/** True if we are currently fading out the FOV */
	bool mFadingOutFOV{false};
	/** How much time we have already spent fading out */
	float mFadeOutProgressTime{0.0f};
};
