// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "UI/FGUserWidget.h" // <FL> [WuttkeP] Changed base type of UFGInteractWidget to UFGUserWidget to allow assigning keybindings to it.
#include "FGInteractWidget.generated.h"

// Simple object wrapper for a hit result so we can put it as the interact object for an interact widget
UCLASS( Blueprintable )
class FACTORYGAME_API UFGHitResultWrapper : public UObject
{
	GENERATED_BODY()
public:

	UFUNCTION( BlueprintPure, Category = "Hit Result" )
	FVector_NetQuantize GetMapMarkerLocation() const
	{
		return mHitResult.Location;
	};
	
	FHitResult mHitResult;
};

/**
 * Base class for stackable widgets in the game such as building interaction windows.
 */
UCLASS( config = Game )
class FACTORYGAME_API UFGInteractWidget : public UFGUserWidget // <FL> [WuttkeP] Changed base type of UFGInteractWidget to UFGUserWidget to allow assigning keybindings to it.
{
	GENERATED_BODY()
public:
	UFGInteractWidget( const FObjectInitializer& ObjectInitializer );

	UFUNCTION()
	void Native_Init();
	
	UFUNCTION( BlueprintNativeEvent, Category = "UI" )
	void Init();

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "UI" )
	void SetInputMode();
	
	void PassThroughKeybindings();

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "UI" )
	void UpdateIgnoreMoveInput();

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "UI" )
	void UpdateIgnoreLookInput();

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "UI" )
	void OnEscapePressed();

	UFUNCTION( BlueprintCallable, Category = "Input" )
	void OnConsume();

	UFUNCTION( BlueprintCallable, Category = "Input" )
	void OnPushedToGameUI();

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

	// Let's this interact widget hijack shortcut pressed. Return true if the shortcut should be consumed. Otherwise it will pass it on.
	UFUNCTION( BlueprintImplementableEvent, Category = "Shortcut" )
	bool OnShortcutPressed( int32 index );

	// Let's this interact widget hijack ping pressed. Return true if the ping should be consumed. Otherwise it will pass it on.
	UFUNCTION( BlueprintImplementableEvent, Category = "Ping" )
	bool OnAttentionPingPressed();

	/** Copies the interact object settings to the factory clipboard */
	UFUNCTION( BlueprintCallable, Category = "Factory Clipboard" )
	void CopyFactoryClipboard();

	// Called when we copied a factory clipboard setting.
	UFUNCTION( BlueprintImplementableEvent, Category = "Factory Clipboard" )
	void OnFactoryClipboardCopied( UObject* interactObject, class UFGFactoryClipboardSettings* factoryClipboardSettings );

	/** Pastes the currently stored factory clipboard settings to the interact object */
	UFUNCTION( BlueprintCallable, Category = "Factory Clipboard" )
	void PasteFactoryClipboard();

	// Called when we pasted a factory clipboard setting. Only called if actually could paste settings to interact object.
	UFUNCTION( BlueprintImplementableEvent, Category = "Factory Clipboard" )
	void OnFactoryClipboardPasted( UObject* interactObject, class UFGFactoryClipboardSettings* factoryClipboardSettings );

	// <FL> KajtaziT added to support hotbar page switching for radial menu, otherwise OnDestruct would trigger build mode
	UFUNCTION( BlueprintImplementableEvent, Category = "Input" )
	void ClearRadialMenuSelection();

	// <FL> KohnhorstT added to support on the fly update of items on hotbar page switching for radial menu
	UFUNCTION(BlueprintImplementableEvent, Category = "Radial Menu")
	void RefreshRadialMenuItems();

protected:
	// Begin UUserWidget interface
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	// End UUserWidget interface

	// Requirement check to verify before calling blueprint Init
	virtual bool NativeCanCallInit();

private: 
	/** Internal function that checks for requirements being met before calling init */
	void NativeTestAndQueueInit();

	/** Clears the focus restore gate that blocks widget from claiming focus more than once a frame */
	UFUNCTION()
	void ClearRestoreFocusGate();

public:
	/** If we should block the keyboard input from the player. If true the player won't be able to move around. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Input", meta=(DisplayName = "Block Movement") )
	bool mUseKeyboard;

	/** If we should block the mouse input from the player. If true the player won't be able to look around. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Input", meta=(DisplayName = "Block Mouse Look") )
	bool mUseMouse;

	/** Sets the mouse locking behavior of the viewport when this widget is active */
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Input", meta=(EditCondition="mUseKeyboard||mUseMouse") )
	EMouseLockMode mMouseLockMode;

	/** Whether to hide the cursor during temporary mouse capture caused by a mouse down */
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Input", meta=(EditCondition="mUseKeyboard||mUseMouse") )
	bool mHideCursorDuringCapture;

	//@todo Some widgets do not want to eat any input so this list is filled manually with all actions in the game...
	// There need to be a clear hierarchy of how input is handled and what to pass and not pass and if the default is pass all or pass none.
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Input", meta=(EditCondition="mUseKeyboard||mUseMouse") )
	TArray< FName > mInputToPassThrough;

	/** This will add all shortcuts 1,2,3...0 to mInputToPassThrough when we setup passthrough keybindings. Used with OnShortcutPressed
	 * Just an easy way instead of adding 10 entries to mInputToPassThrough
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Input" )
	bool mListenForShortcutPressed;

	/** Decides if the widget should restore focus when it looses it. (e.g. when the user clicks outside of the widget) */
	UPROPERTY( EditDefaultsOnly, Category = "Input" )
	bool mRestoreFocusWhenLost = true;

	/** Whether or not to we want to disable Player Actions while this widget is open. */
	UPROPERTY( EditDefaultsOnly, Category = "Input" )
	bool mDisablePlayerActions;

	/** Whether or not to we want to disable BuildGun Actions while this widget is open. */
	UPROPERTY( EditDefaultsOnly, Category = "Input" )
	bool mDisableBuildGunActions;
	
	/** Whether or not to we want to disallow the player from managing their equipment while this widget is open. */
	UPROPERTY( EditDefaultsOnly, Category = "Input" )
	bool mDisablePlayerEquipmentManagement;

	/** Whether or not to flush mouse button input when opening the widget. */
	UPROPERTY( EditDefaultsOnly, Category = "Input" )
	bool mFlushMouseKeysOnOpen;

	/** Whether or not to clear bindings on NativeDestruct. */
	UPROPERTY( EditDefaultsOnly, Category = "Input" )
	bool mClearBindingsOnDestruct;
	
	// Begin Deprecated Input
	/** Decides if we should share input with game or capture it completely */
	UPROPERTY( VisibleDefaultsOnly, Category = "Input Deprecated" )
	bool mCaptureInput;
	// End Deprecated Input

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

private:
	/** Bool to make sure we only try to restore focus once per frame.
		Ugly solution but the whole greedy focus system is ugly and should be looked at instead */
	bool mRestoreFocusGate;
};
