#pragma once
#include "GameFramework/Actor.h"
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "../FGSchematic.h"
#include "../FGTutorialIntroManager.h"
#include "FGBaseUI.h"
#include "FGGameUI.generated.h"

class UFGInteractWidget;

/** Delegate for when mouse button is pressed in Game UI. 
This should be handle by a proper focus/UI system and this is a temporary workaround */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnMouseButtonDown, const FGeometry&, InGeometry, const FPointerEvent&, InMouseEvent );

/**
* Base class for all inventory widgets, contains a lot of helper functions to extract
* interesting information buildings
*/
UCLASS()
class FACTORYGAME_API UFGGameUI : public UFGBaseUI
{
	GENERATED_BODY()
public:
	/** Closes down all interact widgets */
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "UI" )
	void PopAllWidgets(); 

	/** Tick tock */
	virtual void NativeTick( const FGeometry& MyGeometry, float InDeltaTime );

	/** Adds the cheat widget */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "UI" )
	class UFGPopupWidget* AddCheatWidget( FPopupData popupData );

	/** Event received when the focus has been lost to the viewport. Probably because a mouse button was pressed in "nothing" */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "UI" )
	void HandleFocusLost();

	/** Returnswidget stack */
	UFUNCTION( BlueprintPure, Category = "UI" )
	FORCEINLINE TArray< UFGInteractWidget * > GetInteractWidgetStack() { return mInteractWidgetStack; }

	/** Removes from the stack */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	void RemoveInteractWidget( UFGInteractWidget* widgetToRemove );

	/** Adds to the stack */
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "UI" )
	void AddInteractWidget( UFGInteractWidget* widgetToAdd );

	/* Pushes widget */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "UI")
	void PushWidget(UFGInteractWidget* Widget);

	/* Removes widget */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable , Category = "UI")
	bool PopWidget(UFGInteractWidget* WidgetToRemove );

	/** Returnswidget array with pending messages */
	UFUNCTION( BlueprintPure, Category = "UI" )
	FORCEINLINE	TArray< TSubclassOf< class UFGMessageBase > > GetPendingMessages() { return mPendingMessages; }

	/** Adds a new message to the pending message array */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	void AddPendingMessage( TSubclassOf< class UFGMessageBase > newMessage ) { mPendingMessages.Add( newMessage ); }

	/** Handle message. Usually grabbed from the pending message list at appropriate time */
	UFUNCTION( BlueprintImplementableEvent, Category = "UI" )
	void ReceivedMessage( TSubclassOf< class UFGMessageBase > inMessage );

	/** Handle pending messages and push them at appropriate time */
	UFUNCTION( BlueprintNativeEvent, Category = "UI" )
	void HandlePendingMessages();

	/**  Is this a good time to get a message? */
	UFUNCTION( BlueprintNativeEvent, Category = "UI" )
	bool CanReceiveMessage( TSubclassOf< class UFGMessageBase > inMessage );

	/** Sets the current audio message being played */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	void SetCurrentAudioMessage( class UFGAudioMessage* newMessage ){ mCurrentAudioMessage = newMessage; }

	/** Gets the current audio message being played ( can be null ) */
	UFUNCTION( BlueprintPure, Category = "UI" )
	FORCEINLINE class UFGAudioMessage* GetCurrentAudioMessage(){ return mCurrentAudioMessage; }

	/** Called from ingame when the cancel key ( escape ) was pressed when no widget has focus */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	void CancelPressed();

	/** Removes the audio message */
	UFUNCTION( BlueprintNativeEvent, Category = "UI" )
	void RemoveAudioMessage();

	/** Returns the owning fgpawn by looking at ower and vehicle driver */
	class AFGCharacterPlayer* GetFGCharacter();

	/** Adds new tutorial info to be displayed */
	UFUNCTION( BlueprintImplementableEvent, Category = "Tutorial" )
	void AddIntroTutorialInfo( FTutorialHintData tutorialHintData );

	/** Called when we update our current objective but are waiting to show the next */
	UFUNCTION( BlueprintImplementableEvent, Category = "Tutorial" )
	void ClearHintOnTutorialStepCompleted();

	/** Setter for show inventory */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	void SetShowInventory( bool doShow ) { mShowInventory = doShow; }

	/** Getter for mShowInventory */
	UFUNCTION( BlueprintPure, Category = "UI" )
	FORCEINLINE bool GetShowInventory(){ return mShowInventory; }

	/** Setter form WindowWantInventoryAddon */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	void SetWindowWantsInventoryAddon( bool doWantAddon ) { mWindowWantInventoryAddon = doWantAddon; }

	/** Getter for mWindowWantInventoryAddon */
	UFUNCTION( BlueprintPure, Category = "UI" )
	FORCEINLINE bool GetWindowWantsInventoryAddon(){ return mWindowWantInventoryAddon; }

	/** Allow the gameUI to add pawn specific HUD */
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "UI" )
	void AddPawnHUD( UUserWidget* newContent );

	/** Allow the gameUI to remove pawn specific HUD */
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "UI" )
	void RemovePawnHUD();

	/** Temp Solution to remove depenencies*/
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "UI" )
	void ShowDirectionalSubtitle(const FText& Subtitle, AActor* Instigator, float Duration , bool bUseDuration );
	
	/** Temp Solution to remove depenencies*/
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "UI" )
	void StopSubtitle(AActor* Instigator);

	/** Called when we start receiving radiation. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Radiation" )
	void OnReceiveRadiationStart();

	/** Called when we stop receiving radiation. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Radiation" )
	void OnReceiveRadiationStop();

	/** Called when we have updated radiation intensity. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Radiation" )
	void OnRadiationIntensityUpdated( float radiationIntensity, float radiationImmunity );

	/** Play a audio message in the UI */
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category ="FactoryGame|Message")
	void PlayAudioMessage( TSubclassOf<UFGAudioMessage> messageClass );

	/** Finds a widget in the interact widget stack, returns null if not found */
	UFUNCTION( BlueprintPure, Category="FactoryGame|UI")
	UFGInteractWidget* FindWidgetByClass( TSubclassOf<UFGInteractWidget> widgetClass );

	/** Call this to setup the hud for resuming the game */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|HUD")
	void ResumeGame();

	/** Blueprint event called when resuming the game */
	UFUNCTION( BlueprintImplementableEvent, Category="FactoryGame|HUD")
	void OnResumeGame();

	/** Called when we want to show the quick search */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Quick Search" )
	void ShowQuickSearch();

protected:
	// Begin UUserwidget interface
	virtual FReply NativeOnPreviewMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
	// End UUserwidget interface

public:
	/** Array with messages that the player has stocked up */
	TArray< TSubclassOf< class UFGMessageBase > > mPendingMessages;

	/** Delegate for when mouse button is pressed. The event will not be handled 
	so if you already are listening for mouse input you might get this and your own event */
	UPROPERTY( BlueprintAssignable, Category = "Mouse Event" )
	FOnMouseButtonDown mOnMouseButtonDown;

protected:
	/** Do we want the inventory to be shown? */
	bool mShowInventory;

	/** Do we want a player inventory to be created */
	bool mWindowWantInventoryAddon;
private:
	/** A stack with widgets that are currently open */
	UPROPERTY()
	TArray< UFGInteractWidget* > mInteractWidgetStack;

	/** Message that is being played now ( can be null ) */
	UPROPERTY()
	class UFGAudioMessage* mCurrentAudioMessage;

	/** How much time must pass between receiving audio messages at least? */
	UPROPERTY( EditDefaultsOnly, Category = "UI" )
	float mMinTimeBetweenAudioMessage;

	/** Timer value used so that we don't push audio message direct after another */
	float mAudioMessageCooldown;

public:
	FORCEINLINE ~UFGGameUI() = default;
};