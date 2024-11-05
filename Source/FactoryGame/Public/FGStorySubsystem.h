// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FGSubsystem.h"
#include "CoreMinimal.h"
#include "FGGamePhaseManager.h"
#include "FGPlayerController.h"
#include "FGSaveInterface.h"
#include "UObject/NoExportTypes.h"
#include "FGSchematic.h"
#include "FGResearchRecipe.h"
#include "FGRemoteCallObject.h"
#include "FGStorySubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnMessageFinishedForPlayer, class AFGPlayerController*, player, class UFGMessage*, message );

UCLASS()
class FACTORYGAME_API UFGStorySubsystemRemoteCallObject : public UFGRemoteCallObject
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
		
	UFUNCTION( Reliable, Client )
	void Client_ForwardMessagesToGameUI( const TArray<class UFGMessage*>& newMessages );
	
	UFUNCTION( Reliable, Server )
	void Server_MessageFinishedForPlayer( class AFGPlayerController* player, class UFGMessage* message );
	
	UPROPERTY( Replicated, Meta = ( NoAutoJson ) )
	bool mForceNetField_UFGStorySubsystemRemoteCallObject = false;
};

/**
 * Manages triggering and handling of game messages. Below are the key elements that drive the system:
 *
 * Each game message, created as a UFGMessage asset, comes with its own set of triggers and conditions.
 * This subsystem listens for specific events from other systems to find matching triggers (UFGAvailabilityDependency).
 * Note: This system is designed to listen for events exclusively on the server, ensuring that all messages are initiated server-side.
 *
 * Upon an event, we check for messages with corresponding triggers. If multiple messages are found, they're queued up based on priority.
 * Certain events might have a player state as an instigator. For global actions, we find the first available player state.
 * This approach, though not the cleanest, works for global messages. If there are no players in the world when a global message is triggered,
 * we don't play it. This is unlikely but possible with an indirect trigger on an empty dedicated server.
 *
 * When it's time to play a message, we first ensure it hasn't been played for the instigating player and that all conditions (UFGAvailabilityDependency) are met.
 * This includes both global and player-specific dependencies for the instigating player state. If these checks pass,
 * we play the message and then broadcast it to other relevant player controllers through an RPC (UFGStorySubsystemRemoteCallObject).
 *
 * The RCO then calls back to this subsystem for the relevant player controllers, and we forward the message to UFGGameUI.
 * The division here allows GameUI to decide when to show a message and if special handling is needed for certain messages.
 * It also has a queue and decision-making process regarding whether a message should be shown or not. This means a message
 * triggered by Player A and forwarded to Player B can be discarded if Player B is already listening to another message of higher or equal priority,
 * or if the queue is full. Similarly, Player B might interrupt their current message if they receive one of higher priority.
 * The relevant functions are UFGGameUI::AddPendingMessage and UFGGameUI::HandlePendingMessages.
 *
 * When a message is displayed on the screen, it's presented as a Widget_AudioMessage (UFGAudioMessage) that is created and populated with the message data.
 *
 * We store all played messages by any player in mAllPlayedMessages in this subsystem, and each player state checks this array on begin play
 * to see if it has missed any important messages. This is done to populate the codex with important messages, which is useful when a player joins late in a game.
 *
 * I added a lot of logs in this subsystem, and raising the verbosity of LogNarrative (log lognarrative veryverbose) is very helpful when debugging.
 *
 * Summary:
 * UFGMessage: Represents the individual messages with their own triggers and conditions.
 * UFGAvailabilityDependency: Used for evaluating if a message's conditions are met.
 * UFGGameUI: Handles the UI aspects of message display and queuing.
 * Widget_AudioMessage: The widget that is used to display a message on screen.
 *
 * Tools: There are 4 tools for narrative
 *
 * BEUW_EditMessageTool: This is used to preview and tweak a message in the editor so you don't have to start a game and trigger the message
 * every time you change something.
 * 
 * BPEW_NarrativeTSVImporter: Import messages from Excel. The TSV format is what you get when just copying from an Excel sheet.
 * You basically copy in a whole Excel sheet, and it then creates or updates already existing messages from that.
 * See UFGEditorBlueprintFunctionLibrary::ImportMessagesFromString for the import/parsing code.
 * 
 * BPEW_MessageTriggerTool: This is a simple tool created to allow importing and exporting an array of UFGAvailabilityDependency to/from a string.
 * This was added to help define triggers and conditions as text.
 * 
 * BPEW_MatchAudioEventForMessages: A super simple tool that basically just calls UFGEditorBlueprintFunctionLibrary::MatchAudioEventsToMessages,
 * which in turn tries to find audio events for messages that don't have any. This is useful after we've imported new audio from Wwise.
 *
 */
UCLASS( abstract )
class FACTORYGAME_API AFGStorySubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGStorySubsystem();

	/** Get the Story Subsystem, this should always return something unless you call it really early. */
	static AFGStorySubsystem* Get( UWorld* world );

	/** Get the Story Subsystem from a world context, this should always return something unless you call it really early. */
	UFUNCTION( BlueprintPure, Category = "Story", DisplayName = "GetStorySubsystem", Meta = ( DefaultToSelf = "worldContext" ) )
    static AFGStorySubsystem* Get( UObject* worldContext );
	
	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override {}
	virtual bool NeedTransform_Implementation() override { return false; }
	virtual bool ShouldSave_Implementation() const override { return true; }
	// End IFSaveInterface

	//~ Begin AActor interface
	virtual void BeginPlay() override;
	//~ End AActor interface

	// Begin trigger functions
	UFUNCTION()
	void OnOnboardingStepUpdated( class UFGOnboardingStep* newOnboardingStep );
	UFUNCTION()
	void OnSchematicsPurchased( TArray< TSubclassOf< UFGSchematic > > newSchematics, class AFGCharacterPlayer* purchaseInstigator );
	UFUNCTION()
	void OnGamePhaseChanged( UFGGamePhase* currentGamePhase );
	UFUNCTION()
	void OnGameCompleted();
	UFUNCTION()
	void OnLocalPlayerMessageFinished( class UFGMessage* message );
	void OnItemPickuped( AFGPlayerState* playerState, const FItemAmount& totalAmountPickuped );
	void OnItemManuallyCrafted( AFGPlayerState* playerState, const FItemAmount& totalAmountCrafted );
	void OnBuildingBuilt( AFGPlayerState* playerState, TSubclassOf< class AActor > builtActor, int64 totalBuildCount );
	void OnBuildingDismantled( AFGPlayerState* playerState, TSubclassOf< class AActor > builtActor, int64 totalDismantledCount );
	void OnFirstItemSinkFailure( TSubclassOf<UFGItemDescriptor> itemFailedToSink );
	// Not bound to the space elevator delegate since we don't always have a space elevator built. So the space elevator calls this instead
	void OnSpaceElevatorShipmentLockedIn( AFGPlayerState* playerState, class UFGGamePhase* gamePhase );
	// Not bound to any delegate since we don't always have a space elevator built. The Build_SpaceElevator calls this
	UFUNCTION( BlueprintCallable, Category = "Story" )
	void OnSpaceElevatorFullyBuilt();
	// End trigger functions

	/* This forwards the give messages to the game UI where they are locally processed and played */
	void ForwardMessagesToGameUI( const TArray<class UFGMessage*>& messages );

	/*
	 * Returns a playable interrupt message for the given player state. This is used when we interrupt a message with another high prio message
	 * We then want a message to add in between to notify the player we interrupted the first one. 
	 */
	class UFGMessage* GetPlayableInterruptMessage( AFGPlayerState* instigatingPlayerState ) const;

	/* DEBUG */
	void GetStoryDebugData( TArray<FString>& out_debugData );

	/* Returns all messages that have been played, regardless of trigger conditions or the triggering player.*/
	TArray<class UFGMessage*> GetAllPlayedMessages() const { return mAllPlayedMessages; }

	/** Delegates */
	UPROPERTY( BlueprintAssignable, Category = "Story" )
	FOnMessageFinishedForPlayer mOnMessageFinishedForPlayerDelegate;

private:
	/** Listen for events in various subsystems so we know when to trigger messages */
	UFUNCTION()
	void SetupDelegates();

	/**
	 * Attempts to play a set of given messages by sorting them based on priority and then calling TryPlayMessage for each of them
	 * This function can handle an empty message array
	 * @param messages The messages to attempt to play
	 * @param instigatingPlayerState The player state that triggered the message.
	 */
	void TryPlayMessages( const TArray< class UFGMessage*>& messages, const AFGPlayerState* instigatingPlayerState );

private:
	/**
	 * This contains all available messages in the game that can be played.
	 * Messages are never removed from this list once they are triggered, as we want to ensure they can be played for all players.
	 * Technically, we could discard some messages that we know will never be triggered again, especially the ones with unique triggers.
	 * Usually, if not always, these are the global ones. This is probably not an issue but is noteworthy.
	 **/
	UPROPERTY( Transient )
	TArray< class UFGMessage* > mAllMessages;
	
	/**
	 * Stores a collection of all messages that have been played, regardless of trigger conditions or the triggering player.
	 * Primarily used to update player states with important messages they missed, particularly useful for players who join mid-game.
	 * Also serves as a reference to check if a specific message has ever been played.
	 */
	UPROPERTY( SaveGame )
	TArray< class UFGMessage* > mAllPlayedMessages;

	/** Local session purchase history. Used to trigger messages */
	TMap<ESchematicType, TArray<double> > mSchematicTypePurchaseHistory;
	
};

