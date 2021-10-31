// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGSequencerWidget.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGSequencerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void ListenForInput( FInputChord inputkeyChord, TEnumAsByte<EInputEvent> eventType, bool consume, FOnInputAction callback );
	void StopListeningForAllInputs();

protected:
	UFUNCTION( BlueprintCallable, Category="Sequencer" )
	void MoveCursorForward();
	UFUNCTION( BlueprintCallable, Category="Sequencer" )
	void MoveCursorBackward();
	UFUNCTION(BlueprintImplementableEvent)
	void OnCursorMoved();
	UFUNCTION(BlueprintImplementableEvent)
	void OnSequencerUpdated();
	UFUNCTION( BlueprintImplementableEvent )
	void DeleteSelectedNodes();
	UFUNCTION()
	void AddCurrentPlayerLocation();
	UFUNCTION()
	void AddCurrentPlayerRotation();
	UFUNCTION()
	void AddCurrentPlayerFOV();
	UFUNCTION()
	void AddCurrentPlayerLocRotFOV();
	
	UFUNCTION()
	void ToggleMouseControl();

	UFUNCTION( BlueprintPure )
	FORCEINLINE FFrameTime GetCurrentFrameTime() const { return mCurrentFrameTime; }

	UFUNCTION( BlueprintCallable )
	void SetCurrentFrameTime( FFrameTime newFrameTime ) { mCurrentFrameTime = newFrameTime; }

private:
	void ListenForInputActionHelper( FInputChord inputkeyChord, bool consume, FOnInputAction pressedCallback, FOnInputAction releasedCallback, FOnInputAction doubleClickCallback, bool listenForRepeatedPressed = false  );
	UFUNCTION()
	void DiscardInput(){};
	
	FFrameTime mCurrentFrameTime;

	UPROPERTY()
	class AFGPhotoModeManager* mCachedPhotoModeManager;
};
