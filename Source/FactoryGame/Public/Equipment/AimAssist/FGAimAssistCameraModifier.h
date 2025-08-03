// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Camera/CameraModifier.h"
#include "FGAimAssistCameraModifier.generated.h"

class UFGAimTargetComponent;


// <FL> [MartinC] Camera modifier to apply the gamepad aim assist magnetism feature
UCLASS()
class FACTORYGAME_API UFGAimAssistCameraModifier : public UCameraModifier
{
	GENERATED_BODY()
public:
	// <FL> [MartinC] Finds an existing aim assist camera modifier or creates a new one for the given player controller
	static UFGAimAssistCameraModifier* FindOrCreate( APlayerController* PlayerController );

	// <FL> [MartinC] Modifies the camera's view rotation applying the aim assist adjustments
	virtual bool ProcessViewRotation( class AActor* ViewTarget, float DeltaTime, FRotator& OutViewRotation,
									  FRotator& OutDeltaRot ) override;

	// <FL> [MartinC] Sets the currently active aim assist client to apply thoose specific aim assit settings
	UFUNCTION( BlueprintCallable, Category = "Aim Assist" )
	void SetClient( TScriptInterface< IFGAimAssistClient > AimAssistClient );

	static void DisplayDebugAimAssist( UCanvas* canvas, const FDebugDisplayInfo& debugDisplay, float& YL, float& YPos );

	UFUNCTION()
	void OnAimAssistStrengthSettingUpdated( FString cvar );

protected:
	// <FL> [MartinC] Currently active aim assist client
	UPROPERTY()
	TScriptInterface< IFGAimAssistClient > CurrentClient;

	// <FL> [MartinC] Variables that store values relevant to the debug displayed information
	FRotator LastViewRotation;
	UFGAimTargetComponent* LastBestTarget = nullptr;
	float LastBestStrength;
	//<FL>[VilagosD] reads value from US_AimAssistStrength
	float AssistMultiplyerSetting = 1.0f;

};
