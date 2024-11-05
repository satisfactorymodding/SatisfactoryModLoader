// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "UI/FGInteractWidget.h"
#include "FGPhotoModeWidget.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGPhotoModeWidget : public UFGInteractWidget
{
	GENERATED_BODY()

public:
	UFGPhotoModeWidget( const FObjectInitializer& ObjectInitializer );
		
	UFUNCTION(BlueprintImplementableEvent, Category = "Photo Mode")
	void ToggleSequencer();
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void ListenForInput( FInputChord inputkeyChord, TEnumAsByte<EInputEvent> eventType, bool consume, FOnInputAction callback );
	void StopListeningForAllInputs();

	UFUNCTION()
	void ToggleMouseControl();

	UFUNCTION()
	void ToggleAdvancedPhotoMode();

	UFUNCTION()
	void TogglePhotoModeDebug();

	UFUNCTION(BlueprintImplementableEvent, Category = "Photo Mode")
	void TakePhoto();

	/** Input Actions */
	void Input_ToggleAdvancedPhotoMode( const FInputActionValue& actionValue );
	void Input_TogglePhotoModeDebug( const FInputActionValue& actionValue );
	void Input_ToggleSequencer( const FInputActionValue& actionValue );
	void Input_ToggleMouseControl( const FInputActionValue& actionValue );
	void Input_TakePhoto( const FInputActionValue& actionValue );
};
