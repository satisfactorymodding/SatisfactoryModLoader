// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGPhotoModeWidget.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGPhotoModeWidget : public UUserWidget
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

private:
	void ListenForInputActionHelper( FInputChord inputkeyChord, bool consume, FOnInputAction pressedCallback, FOnInputAction releasedCallback, FOnInputAction doubleClickCallback );
	UFUNCTION()
	void DiscardInput(){};
};
