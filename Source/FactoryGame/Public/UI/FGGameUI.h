// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGSchematic.h"
#include "FGTutorialIntroManager.h"
#include "UI/FGBaseUI.h"
#include "UI/Message/FGAudioMessage.h"
#include "FGGameUI.generated.h"

class UFGInteractWidget;

/**
 * Delegate for when mouse button is pressed in Game UI.
 * This should be handle by a proper focus/UI system and this is a temporary workaround.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnMouseButtonDown, const FGeometry&, InGeometry, const FPointerEvent&, InMouseEvent );

/**
 * Base class for the game UI located in the HUD.
 * 
 * This handles for example:
 *	Handling on screen audio messages.
 *	Handling pawn specific HUDs.
 *	Handling building interaction windows.
 */
UCLASS()
class FACTORYGAME_API UFGGameUI : public UFGBaseUI
{
	GENERATED_BODY()
public:
	/** Closes down all interact widgets */
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "UI" )
	void PopAllWidgets(); 

	// Begin UUserWidget interface
	virtual void NativeTick( const FGeometry& MyGeometry, float InDeltaTime ) override;
	// End UUserWidget interface

	/** Adds the cheat widget */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "UI" )
	class UFGPopupWidget* AddCheatWidget( FPopupData popupData );

	/** Event received when the focus has been lost to the viewport. Probably because a mouse button was pressed in "nothing" */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "UI" )
	void HandleFocusLost();

	/** Returns widget stack */
	UFUNCTION( BlueprintPure, Category = "UI" )
	FORCEINLINE TArray< UFGInteractWidget * > GetInteractWidgetStack() { return mInteractWidgetStack; }

	/** Returns the first widget of the given class in the interact stack */
	UFUNCTION( BlueprintPure, Category = "UI" )
	UFGInteractWidget* GetInteractWidgetOfClass( TSubclassOf< UFGInteractWidget > interactWidgetClass ) const;

	/** Returns true if we have a widget of the given class in the interact stack */
	UFUNCTION( BlueprintPure, Category = "UI" )
	bool ContainsInteractWidgetOfClass( TSubclassOf< UFGInteractWidget > interactWidgetClass ) const;

	/** Removes from the stack */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	void RemoveInteractWidget( UFGInteractWidget* widgetToRemove );

	/** Adds to the stack */
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "UI" )
	void AddInteractWidget( UFGInteractWidget* widgetToAdd );

	/* Pushes widget */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "UI")
	void PushWidget(UFGInteractWidget* Widget);

	/* Pushes a notification widget */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "UI")
	void PushNotificationWidget( class UFGPushNotificationWidget* Widget );

	/* Removes widget */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable , Category = "UI")
	bool PopWidget(UFGInteractWidget* WidgetToRemove );

	/** Adds a new message to the pending message array */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	void AddPendingMessage( FPendingMessageQueue message );

	/** Handle message. Usually grabbed from the pending message list at appropriate time */
	UFUNCTION( BlueprintImplementableEvent, Category = "UI" )
	void ReceivedMessage( TSubclassOf< class UFGMessageBase > inMessage );

	/** Answer a call that is shown on the screen */
    void AnswerCall( TSubclassOf< class UFGAudioMessage > inMessage );

	/** Decline a call that is shown on the screen */
    void DeclineCall( TSubclassOf< class UFGAudioMessage > inMessage );

	/** Handle pending messages and push them at appropriate time */
	void HandlePendingMessages( float InDeltaTime );

	void PlayMessageQueue( FPendingMessageQueue newMessageQueue );

	void UpdateActiveMessageQueue();

	UFUNCTION()
	void PlayNextMessageInActiveMessageQueue();

	/**  Is this a good time to start the given message queue? */
	bool CanReceiveMessageQueue( FPendingMessageQueue inMessageQueue );

	/**  Is this a good time to play the given message? */
	bool CanReceiveMessage( TSubclassOf< class UFGMessageBase > inMessage );

	/** Sets the active audio message being played */
	UFUNCTION( BlueprintCallable, Category = "UI" )
    void SetActiveAudioMessage( class UFGAudioMessage* newMessage ){ mActiveAudioMessage = newMessage; }

	/** Gets the active audio message being played ( can be null ) */
	UFUNCTION( BlueprintPure, Category = "UI" )
    FORCEINLINE class UFGAudioMessage* GetActiveAudioMessage(){ return mActiveAudioMessage; }

	/** Called from in-game when the cancel key ( escape ) was pressed when no widget has focus */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	void CancelPressed();

	/** Triggered when we have finished playing the active audio message */
	UFUNCTION()
    void AudioMessageFinishedPlayback();

	/** Removes the audio message */
	UFUNCTION( BlueprintNativeEvent, Category = "UI" )
	void RemoveAudioMessage();

	/** Returns the owning pawn by looking at owner and vehicle driver */
	class AFGCharacterPlayer* GetFGCharacter();

	/** Adds new tutorial info to be displayed */
    void AddIntroTutorialInfo( FTutorialHintData tutorialHintData );

	/** Called when we update our current objective but are waiting to show the next */
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

	/** Temp Solution to remove dependencies */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "UI" )
	void ShowDirectionalSubtitle(const FText& Subtitle, AActor* Instigator, float Duration , bool bUseDuration );
	
	/** Temp Solution to remove dependencies */
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

	/** Called when we go from connected to disconnected or vice versa with a hoverpack. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|HUD|HoverPack" )
    void OnHoverPackConnectionStatusUpdated( const bool HasConnection );

	/** Play a audio message in the UI */
	UFUNCTION( BlueprintCallable, Category ="FactoryGame|Message")
	void PlayAudioMessage( TSubclassOf<UFGAudioMessage> messageClass );

	/** Finds a widget in the interact widget stack, returns null if not found */
	UFUNCTION( BlueprintPure, Category="FactoryGame|UI")
	UFGInteractWidget* FindWidgetByClass( TSubclassOf<UFGInteractWidget> widgetClass );

	/** Get the on screen call widget */
	UFUNCTION( BlueprintImplementableEvent, Category = "UI" )
    class UFGOnScreenCallWidget* GetOnScreenCallWidget() const;

	/** Call this to setup the hud for resuming the game */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|HUD")
	void ResumeGame();

	/** Blueprint event called when resuming the game */
	UFUNCTION( BlueprintImplementableEvent, Category="FactoryGame|HUD")
	void OnResumeGame();

	/** Called when we want to show the quick search */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Quick Search" )
	void ShowQuickSearch();

	/** Show attention ping in the HUD */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "FactoryGame|HUD" )
	void ShowAttentionPing( AFGPlayerState* playerState, FVector worldLocation );

	/** Trigger an inventory notification when inventory updates */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "FactoryGame|HUD" )
	void PushInventoryNotification( UFGInventoryComponent* source, UFGInventoryComponent* destination, FItemAmount ItemAmount );

protected:
	// Begin UUserWidget interface
	virtual FReply NativeOnPreviewMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
	// End UUserWidget interface

	/** Event triggered when we have updated the current tutorial info */
	UFUNCTION( BlueprintImplementableEvent, Category = "UI" )
    void OnUpdateTutorialInfo();

	/** Event triggered when we want to show tutorial hint */
	void ShowTutorialHint();

	UFUNCTION( BlueprintImplementableEvent, Category = "UI", meta = (DisplayName = "ShowTutorialHint") )
	void ReceiveShowTutorialHint();

	UFUNCTION( BlueprintImplementableEvent, Category = "UI" )
	UNamedSlot* GetTutorialInfoSlot();

	UFUNCTION( BlueprintImplementableEvent, Category = "UI" )
	UNamedSlot* GetAudioMessageSlot();

public:
	/** Array with messages that the player has stocked up */
	TArray< FPendingMessageQueue > mPendingMessageQueues;

	/** Delegate for when mouse button is pressed. The event will not be handled 
	so if you already are listening for mouse input you might get this and your own event */
	UPROPERTY( BlueprintAssignable, Category = "Mouse Event" )
	FOnMouseButtonDown mOnMouseButtonDown;

protected:
	/** Do we want the inventory to be shown? */
	bool mShowInventory;

	/** Do we want a player inventory to be created */
	bool mWindowWantInventoryAddon;

	UPROPERTY( BlueprintReadOnly )
	FTutorialHintData mActiveTutorialHintData;
private:
	/** A stack with widgets that are currently open */
	UPROPERTY()
	TArray< UFGInteractWidget* > mInteractWidgetStack;

	/** Message that is being played now ( can be null ) */
	UPROPERTY()
	class UFGAudioMessage* mActiveAudioMessage;

	/** Message queue that the currently active audio message belongs to */
	UPROPERTY()
	FPendingMessageQueue mActiveMessageQueue;

	/** How much time must pass between receiving audio messages at least? */
	UPROPERTY( EditDefaultsOnly, Category = "UI" )
	float mMinTimeBetweenAudioMessage;

	/** Timer value used so that we don't push audio message direct after another */
	float mAudioMessageCooldown;
};
