// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBaseUI.h"
#include "FGSchematic.h"
#include "FGTutorialIntroManager.h"
#include "Blueprint/UserWidgetPool.h"
#include "Message/FGAudioMessage.h"
#include "Narrative/FGMessage.h"
#include "FGGameUI.generated.h"

class UFGInteractWidget;

/**
 * Delegate for when mouse button is pressed in Game UI.
 * This should be handle by a proper focus/UI system and this is a temporary workaround.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnMouseButtonDown, const FGeometry&, InGeometry, const FPointerEvent&, InMouseEvent );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnMessageFinished, class UFGMessage*, message );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FFGOnControllerDragWidgetChanged, class UFGControllerDragWidget*, slot );

USTRUCT()
struct FQueuedMessage
{
	GENERATED_BODY()
	
	FQueuedMessage( UFGMessage* inMessage ):
	Message( inMessage ),
	TriggerDelay( inMessage->mTriggerDelay )
	{}

	FQueuedMessage(){}

	UPROPERTY( Transient )
	class UFGMessage* Message = nullptr;
	
	UPROPERTY( Transient )
	float TriggerDelay = 0;
	
};

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
	UFGGameUI( const FObjectInitializer& ObjectInitializer );

	// Begin UUserWidget interface
	virtual void NativeConstruct() override;
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	// End UUserWidget interface
	
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

	/** Returns widget stack */
	UFUNCTION( BlueprintPure, Category = "UI" )
	FORCEINLINE bool HasActiveInteractWidget() { return mInteractWidgetStack.Num() > 0; }

	/** Returns the first widget of the given class in the interact stack */
	UFUNCTION( BlueprintPure, Category = "UI", meta = ( DeterminesOutputType = "interactWidgetClass" ) )
	UFGInteractWidget* GetInteractWidgetOfClass( TSubclassOf< UFGInteractWidget > interactWidgetClass ) const;

	/** Returns all widgets on the stack belonging to the given interact object */
	UFUNCTION( BlueprintPure, Category = "UI" )
	void GetInteractWidgetsOfInteractObject( const UObject* InteractObject, TArray<UFGInteractWidget*>& OutInteractWidgets ) const;

	/** Returns true if we have a widget of the given class in the interact stack */
	UFUNCTION( BlueprintPure, Category = "UI" )
	bool ContainsInteractWidgetOfClass( TSubclassOf< UFGInteractWidget > interactWidgetClass ) const;

	/** Removes from the stack */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	void RemoveInteractWidget( UFGInteractWidget* widgetToRemove );

	/** Adds to the stack */
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable, Category = "UI" )
	void AddInteractWidget( UFGInteractWidget* widgetToAdd );

	/** Toggles a widget on and off. Useful in cases where you want to open and close the UI with the same button, like with the Locomotive UI.
	 *  Native version of BPIGameUI::ToogleInteractWidget. Calls the same BP code in BP_GameUI
	 */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "UI" )
	void OnToggleInteractWidget( TSubclassOf<UFGInteractWidget> widgetToToogle, UObject* interactObject );

	/* Pushes widget */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "UI")
	void PushWidget(UFGInteractWidget* Widget);

	/* Pushes a notification widget */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "UI")
	void PushNotificationWidget( class UFGPushNotificationWidget* Widget );

	/* Removes widget */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable , Category = "UI")
	bool PopWidget( UFGInteractWidget* WidgetToRemove );

	/**
	 * Adds new UFGMessages to the pending queue for playback.
	 * 
	 * - Validates player state and new message validity before adding.
	 * - If globally suppressed, marks the message as played and doesn't queue.
	 * - Discards the message if it doesn't meet local conditions or if it's blocked by cooldown.
	 * - Interruption and queue management based on message priority and queue limits.
	 * - Messages that cannot be queued or exceed the queue limit are discarded.
	 * 
	 * @param newMessages The new UFGMessages to add to the pending queue.
	 */
	void AddPendingMessages( const TArray< UFGMessage* >& newMessages );

	/** Handle pending messages and push them at appropriate time */
	void HandlePendingMessages( float InDeltaTime );

	/** Gets the active audio message being played ( can be null ) */
	UFUNCTION( BlueprintPure, Category = "UI" )
    FORCEINLINE class UFGAudioMessage* GetActiveAudioMessage(){ return mActiveAudioMessage; }

	/** Called from in-game when the pause game key ( escape ) was pressed */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	void Native_HandlePauseGamePressed();
	/** Allow BP implementation to handle escape pressed. Returning true will mean BP handled the call and we shouldn't process further */
	UFUNCTION( BlueprintImplementableEvent, Category = "UI" )
	bool HandlePauseGamePressed();

	/** Brings up the in game pause menu */
	UFUNCTION( BlueprintImplementableEvent, Category = "UI" )
	void OnPauseGame();

	/** Sets whether the pause menu is currently open at the moment. Does not actually open the pause menu. */
	UFUNCTION( BlueprintCallable, Category = "UI" )
	void SetPauseMenuOpen( bool isOpen );

	/** Returns whether or not the pause menu is currently open. */
	UFUNCTION( BlueprintPure, Category = "UI" )
	bool IsPauseMenuOpen() const { return mPauseMenuOpen; }

	/** Triggered when we have finished playing the active audio message */
	UFUNCTION()
    void AudioMessageFinishedPlayback();

	/** Returns the owning pawn by looking at owner and vehicle driver */
	class AFGCharacterPlayer* GetFGCharacter();

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

	/** Play a audio message in the UI
	 * @param message The message to play
	 * @param messageClass Optional audio message class to use. Will use Default Audio Message Widget in UI Settings if unspecified.
	 */
	UFUNCTION( BlueprintCallable, Category ="FactoryGame|Message")
	void PlayAudioMessage( UFGMessage* message, TSubclassOf<UFGAudioMessage> messageClass = nullptr );

	// @todok2 Temporary until we cleaned up system
	void Internal_PlayAudioMessage( class UFGAudioMessage* audioMessage );

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

	/** Show attention ping in the HUD */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "FactoryGame|HUD" )
	void ShowAttentionPing( AFGPlayerState* playerState, FVector worldLocation );

	/** Trigger an inventory notification when inventory updates */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "FactoryGame|HUD" )
	void PushInventoryNotification( UFGInventoryComponent* source, UFGInventoryComponent* destination, FItemAmount ItemAmount );

	void Native_OnFactoryClipboardCopied( UObject* object, class UFGFactoryClipboardSettings* factoryClipboardSettings );
	// Called when we copied a factory clipboard setting.
	UFUNCTION( BlueprintImplementableEvent, Category = "Factory Clipboard" )
	void OnFactoryClipboardCopied( UObject* interactObject, class UFGFactoryClipboardSettings* factoryClipboardSettings );

	void Native_OnFactoryClipboardPasted( UObject* object, class UFGFactoryClipboardSettings* factoryClipboardSettings );
	// Called when we pasted a factory clipboard setting. Only called if actually could paste settings to interact object.
	UFUNCTION( BlueprintImplementableEvent, Category = "Factory Clipboard" )
	void OnFactoryClipboardPasted( UObject* interactObject, class UFGFactoryClipboardSettings* factoryClipboardSettings );

	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "UI" )
	void ShowTextNotification( const FText& Text );

	UFUNCTION( BlueprintImplementableEvent, Category = "UI" )
	bool OnShortcutPressed( int32 shortcutIndex );

	TMap< UFGMessage*, double > GetPlayedMessages() const { return mPlayedMessages; }

	FORCEINLINE float GetMessageCooldown() const { return mMessageCooldown; }
	FORCEINLINE void ClearMessageCooldown() { mMessageCooldown = 0.f; }

	/** Request and release functions for the user widget pool */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|UI", meta = (DeterminesOutputType = "widgetClass") )
	UUserWidget* RequestWidget( TSubclassOf< UUserWidget > widgetClass );
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|UI" )
	void ReleaseWidget( UUserWidget* widgetToRelease );
	
	UFUNCTION( BlueprintPure )
	class UFGControllerDragWidget* GetControllerDragWidget() { return mControllerDragWidget; }

	UFUNCTION( BlueprintCallable )
	void SetControllerDragWidget( class UFGControllerDragWidget* widget );

	UPROPERTY( BlueprintAssignable )
	FFGOnControllerDragWidgetChanged mControllerDragWidgetChanged;

protected:
	// Begin UUserWidget interface
	virtual FReply NativeOnPreviewMouseButtonDown( const FGeometry& InGeometry, const FPointerEvent& InMouseEvent ) override;
	// End UUserWidget interface

	UFUNCTION()
	void Native_OnOnboardingStepUpdated( UFGOnboardingStep* currentOnboardingStep );

	/* previousOnboardingStep is valid when a transition from one step to another happens. Invalid if we load a game or init the first onboarding step */
	UFUNCTION( BlueprintImplementableEvent, Category = "UI" )
	void OnOnboardingStepUpdated( UFGOnboardingStep* newOnboardingStep );

	UFUNCTION( BlueprintImplementableEvent, Category = "UI" )
	UNamedSlot* GetTutorialInfoSlot();

	UFUNCTION( BlueprintImplementableEvent, Category = "UI" )
	UNamedSlot* GetAudioMessageSlot();

	UFUNCTION( BlueprintPure, Category = "UI" )
	bool ShouldShowFicsitSplashWidget() const;

	virtual bool ShouldSuppressMessage( class UFGMessage* message ) const;

private:
	void SetupDelegates();

public:
	/** This is the interrupt message we want to play in between if a message was interrupted by a higher prio message. Populated when message is interrupted */
	UPROPERTY( Transient )
	class UFGMessage* mPendingInterruptMessage;
	/** Queue of messages pending playback. The trigger delay of the queued messages does not matter for the order of the queue. The first message
	 * can be waiting for it's delay while the second isn't and that is fine. The trigger delay is just a way to make sure we don't trigger messages to early. */
	UPROPERTY(Transient)
	TArray<FQueuedMessage> mMessageQueue;

	/** Delegate for when mouse button is pressed. The event will not be handled 
	so if you already are listening for mouse input you might get this and your own event */
	UPROPERTY( BlueprintAssignable, Category = "Mouse Event" )
	FOnMouseButtonDown mOnMouseButtonDown;

	/** Called whenever a message finishes playing. */
	UPROPERTY( BlueprintAssignable, Category = "Message" )
	FOnMessageFinished mOnMessageFinishedDelegate;

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
	class UFGAudioMessage* mActiveAudioMessage = nullptr;

	/** Array with messages that have been played this session mapped to the world time */
	UPROPERTY( Transient )
	TMap< UFGMessage*, double > mPlayedMessages;

	/* Every time a message is triggered a cooldown will start running. Some message will not be played if triggered while this cooldown is active. */
	float mMessageCooldown = 0.f;

	/** Whether or not the pause menu is open. */
	bool mPauseMenuOpen;

	/** Pooled widgets that we don't want to recreate */
	UPROPERTY( Transient )
	FUserWidgetPool mUserWidgetPool;

	/** Floating inventory slot used when dragging an item with the controller. */
	UPROPERTY()
	class UFGControllerDragWidget* mControllerDragWidget;
};
