// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "UMG.h"
#include "Blueprint/UserWidget.h"
#include "FGInteractWidget.generated.h"


/**
 * Base class for stackable widgets in the game such as building interaction windows.
 */
UCLASS( config = Engine )
class FACTORYGAME_API UFGInteractWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFGInteractWidget( const FObjectInitializer& ObjectInitializer );

	UFUNCTION( BlueprintNativeEvent, Category = "UI" )
	void Init();

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "UI" )
	void SetInputMode();

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "UI" )
	void UpdateIgnoreMoveInput();

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "UI" )
	void UpdateIgnoreLookInput();

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "UI" )
	void OnEscapePressed();

	UFUNCTION( BlueprintCallable, Category = "Input" )
	void OnConsume();

	/** Gets the alignment we want */
	UFUNCTION( BlueprintPure, Category = "UI" ) 
	FORCEINLINE EHorizontalAlignment GetDesiredHorizontalAlignment() { return mDesiredHorizontalAlignment; }

	/** Sets the alignment we want */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	void SetDesiredHorizontalAlignment( EHorizontalAlignment newAlignment ) { mDesiredHorizontalAlignment = newAlignment; }

	/** Gets the vertical alignment we want */
	UFUNCTION( BlueprintPure, Category = "UI" )
	FORCEINLINE EVerticalAlignment GetDesiredVerticalAlignment() { return mDesiredVerticalAlignment; }

	/** Sets the vertical alignment we want */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	void SetDesiredVerticalAlignment( EVerticalAlignment newAlignment ) { mDesiredVerticalAlignment = newAlignment; } 

	/** Gets the size we want */
	UFUNCTION( BlueprintPure, Category = "UI" )
	FORCEINLINE FSlateChildSize GetDesiredAlignmentSize() { return mDesiredAlignmentSize; }

	/** Sets the size we want */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	void SetDesiredAlignmentSize( FSlateChildSize newSize ) { mDesiredAlignmentSize = newSize; }

	/** Getter for gamepad cursor */
	UFUNCTION( BlueprintPure, Category = "UI" )
	FORCEINLINE bool GetUseGamepadCursor() { return mUseGamepadCursor; }

	/** Sets default focus widget */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	void SetDefaultFocusWidget( UWidget* focusWidget );

	/** Returns default focus widget */
	UFUNCTION( BlueprintPure, Category = "UI" )
	FORCEINLINE UWidget* GetDefaultFocusWidget() { return mDefaultFocusWidget; }

	/** Sets up default focus for interact widgets ( usually given to the close button in the window */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "UI" )
	void SetupDefaultFocus();

	/** Getter for mSupportsStacking */
	UFUNCTION( BlueprintPure, Category = "UI" )
	FORCEINLINE bool GetSupportsStacking() { return mSupportsStacking; }

	/** Custom tick event for updating UI that needs frequent updates. If custom tick rate <= 0.f this event will not trigger */
	UFUNCTION( BlueprintImplementableEvent, Category = "Custom Tick" )
	void OnCustomTick( float UpdateTime );

	/** Get the rate for the timer that triggers the custom tick */
	UFUNCTION( BlueprintPure, Category = "Custom Tick" )
	FORCEINLINE float GetCustomTickRate() const { return mCustomTickRate; }
	
	FORCEINLINE bool GetSupportsCaching() const { return mSupportsCaching; }

protected:
	// Begin UUserWidget interface
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnRemovedFromFocusPath( const FFocusEvent& InFocusEvent ) override;
	// End UUserWidget interface

	// Requirement check to verify before calling blueprint Init
	virtual bool NativeCanCallInit();

private: 
	/** Internal function that checks for requirements being met before calling init */
	void NativeTestAndQueueInit();

public:
	/** If we should take the keyboard input from the player. The player won't be able to move around. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Input" )
	bool mUseKeyboard;

	/** If we should take the mouse input from the player. The player won't be able to look around. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Input" )
	bool mUseMouse;

	/** Sets the mouse locking behavior of the viewport when this widget is active */
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Input" )
	EMouseLockMode mMouseLockMode;

	/** Whether to hide the cursor during temporary mouse capture caused by a mouse down, only relevant when mCaptureInput is false */
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Input" )
	bool mHideCursorDuringCapture;

	/** Decides if we should share input with game or capture it completely */
	UPROPERTY( EditDefaultsOnly, Category = "Input" )
	bool mCaptureInput;

	/** Decides if the widget should restore focus when it looses it. (e.g. when the user clicks outside of the widget) */
	UPROPERTY( EditDefaultsOnly, Category = "Input" )
	bool mRestoreFocusWhenLost = true;

	//@todo Some widgets do not want to eat any input so this list is filled manually with all actions in the game...
	// There need to be a clear hierarchy of how input is handled and what to pass and not pass and if the default is pass all or pass none.
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Input" )
	TArray< FName > mInputToPassThrough;

	/** Our desired horizontal alignment */
	UPROPERTY( EditDefaultsOnly, Category = "UI" )
	TEnumAsByte< EHorizontalAlignment > mDesiredHorizontalAlignment;

	/** Our desired vetical alignment */
	UPROPERTY( EditDefaultsOnly, Category = "UI" )
	TEnumAsByte< EVerticalAlignment > mDesiredVerticalAlignment;

	/** Our desired horizontal size */
	UPROPERTY( EditDefaultsOnly, Category = "UI" )
	FSlateChildSize mDesiredAlignmentSize;

	/** Object that we interacted with in order to show this widget ( can be nullPeter ) */
	UPROPERTY( BlueprintReadWrite, Meta = (ExposeOnSpawn) )
	UObject* mInteractObject;

	/** Class of the default widget we want to give focus to */
	UPROPERTY( config, EditDefaultsOnly, Category = "UI" ) 
	TSubclassOf< UUserWidget > mDefaultFocusWidgetClass;


protected:
	/** Should gamepad act as cursor when using this widget? */
	UPROPERTY( EditDefaultsOnly, Category = "UI" )
	bool mUseGamepadCursor;

	/** The rate for the timer that triggers the custom tick. If <= 0.f no timer will be started */
	UPROPERTY( EditDefaultsOnly, Category = "Custom Tick" )
	float mCustomTickRate;

	/** True if the custom tick event be called on construct. If <= 0.f no event will be triggered */
	UPROPERTY( EditDefaultsOnly, Category = "Custom Tick" )
	bool mCallCustomTickOnConstruct;

	/** The timer handle for the custom tick event */
	FTimerHandle mCustomTickTimerHandle;

	/** Used to give focus to an object when nothing else has focus */
	UPROPERTY()
	UWidget* mDefaultFocusWidget;

	/** Does this widget support stacking widgets on top? */
	UPROPERTY( EditDefaultsOnly, Category = "Input" )
	bool mSupportsStacking;

	/** Does this widget support us caching it to be reused? */
	UPROPERTY( EditDefaultsOnly, Category = "Custom Tick" )
	bool mSupportsCaching;
};
