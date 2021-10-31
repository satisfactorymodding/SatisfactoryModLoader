// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FactoryGame.h"
#include "FGSubsystem.h"
#include "CoreMinimal.h"
#include "FGSaveInterface.h"
#include "UObject/NoExportTypes.h"
#include "FGSchematic.h"
#include "FGMapArea.h"
#include "FGResearchRecipe.h"
#include "FGStoryQueue.h"
#include "FGGamePhaseManager.h"
#include "FGStorySubsystem.generated.h"

USTRUCT( BlueprintType )
struct FMapAreaVisitedData
{
	GENERATED_BODY()

	/** return true if the schematic is valid */
	FORCEINLINE bool IsSchematicValid() const;

	/** returns nullptr if the schematic isn't loaded */
	FORCEINLINE TSubclassOf< UFGSchematic > GetSchematic() const;

	/** Map area class we are looking for */
	UPROPERTY( EditDefaultsOnly, Category = "Story" )
	TSubclassOf< class UFGMapArea > MapAreaClass;

	/** Message that should be added when MapAreaClass is found for the first time */
	UPROPERTY( EditDefaultsOnly, Category = "Story" )
	TArray< TSubclassOf< class UFGMessageBase > > Messages;
private:
	/** Schematic to unlock ( if any ) */
	UPROPERTY( EditDefaultsOnly, Category = "Story" )
	TSoftClassPtr< class UFGSchematic > SchematicClass;
};

USTRUCT( BlueprintType )
struct FItemFoundData
{
	GENERATED_BODY()

	/** Already found or not? */
	UPROPERTY( SaveGame )
	bool WasFound;

	/** return true if the schematic is valid */
	FORCEINLINE bool IsSchematicValid() const;

	/** returns nullptr if the schematic isn't loaded */
	FORCEINLINE TSubclassOf< class UFGSchematic > GetSchematic() const;

	/** returns nullptr if the item isn't loaded */
	FORCEINLINE TSubclassOf< class UFGItemDescriptor > GetItemDescriptor() const;

	/** Message that should be added when Class is found for the first time */
	UPROPERTY( EditDefaultsOnly, Category = "Story" )
	TArray< TSubclassOf< class UFGMessageBase > > Messages;
private:
	/** Schematic to unlock ( if any ) */
	UPROPERTY( EditDefaultsOnly, Category = "Story" )
	TSoftClassPtr< class UFGSchematic > SchematicClass;

	/** Item descriptor we are looking for */
	UPROPERTY( EditDefaultsOnly, Category = "Story" )
	TSoftClassPtr< class UFGItemDescriptor > ItemClass;
};

USTRUCT( BlueprintType )
struct FSchematicMessagePair
{
	GENERATED_BODY()

	/** returns nullptr if the schematic isn't loaded */
	FORCEINLINE TSubclassOf< UFGSchematic > GetSchematic() const;

	/** Message to display */
	UPROPERTY( EditDefaultsOnly, Category = "Story" )
	TArray< TSubclassOf< class UFGMessageBase > > Messages;
private:
	/** Associated schematic */
	UPROPERTY( EditDefaultsOnly, Category = "Story" )
	TSoftClassPtr< UFGSchematic > SchematicUnlocked;
};

USTRUCT(BlueprintType)
struct FResearchTreeMessageData
{
	GENERATED_BODY()

	/** return false if research tree isn't loaded */
	FORCEINLINE bool IsValid() const;

	/** returns nullptr if the tree isn't loaded */
	FORCEINLINE TSubclassOf<class UFGResearchTree> GetResearchTree() const;

	/** Message to display */
	UPROPERTY( EditDefaultsOnly, Category = "Story" )
	TArray<TSubclassOf<class UFGMessageBase>> Messages;

private:
	/** Associated research tree */
	UPROPERTY( EditDefaultsOnly, Category = "Story" )
	TSoftClassPtr<class UFGResearchTree> ResearchTree;
};

// Proptype struct for active story queue. @todok2 Clean Up.
USTRUCT( BlueprintType )
struct FActiveStoryQueue
{
	GENERATED_BODY()
	
	FActiveStoryQueue() :
    StoryQueueClass( nullptr ),
    MessageIndex( 0 ),
    PendingMessageFromMilestone( false ),
    PendingMessageFromMilestoneTimer( 0.0f ),
    TimeSinceLastQueueMessage( 0.0f ),
	LastPoppedMessage( nullptr )
	{};

	FActiveStoryQueue( TSubclassOf<class UFGStoryQueue> storyQueueClass ) :
    StoryQueueClass( storyQueueClass ),
    MessageIndex( 0 ),
    PendingMessageFromMilestone( false ),
    PendingMessageFromMilestoneTimer( 0.0f ),
    TimeSinceLastQueueMessage( 0.0f ),
	LastPoppedMessage( nullptr )
	{};

	FORCEINLINE bool IsValid() const
	{
		return StoryQueueClass != nullptr;
	}

	void ResetStoryQueue();

	FORCEINLINE bool ContainsUnplayedMessages() const;

	FORCEINLINE bool CanPlayMessage() const;

	TSubclassOf< class UFGMessageBase > PopMessage();

	bool DeclineCall( TSubclassOf< class UFGAudioMessage > messageToDecline );

	void UpdateTimers( float dt );
	
	UPROPERTY(SaveGame, BlueprintReadOnly, EditDefaultsOnly, Category = "Story" )
	TSubclassOf<class UFGStoryQueue> StoryQueueClass;

	UPROPERTY( SaveGame )
	int32 MessageIndex;

	UPROPERTY( SaveGame )
	bool PendingMessageFromMilestone;

	UPROPERTY( SaveGame )
	float PendingMessageFromMilestoneTimer;

	UPROPERTY( SaveGame )
	float TimeSinceLastQueueMessage;

	TSubclassOf< class UFGMessageBase > LastPoppedMessage;

};

/**
* Simple container class so we can have an array of event triggered messages stored in an asset instead of working with it inline.
* Helps with organisation of story subsystem
*/
UCLASS( Abstract, Blueprintable )
class FACTORYGAME_API UFGEventTriggeredMessages: public UObject
{
	GENERATED_BODY()
public:
	static TArray< FEventTriggeredMessage > GetEventTriggeredMessages( TSubclassOf< UFGEventTriggeredMessages > inClass );
protected:
	UPROPERTY( EditDefaultsOnly, Category = "Event Triggered Messages" )
	TArray< FEventTriggeredMessage > mEventTriggeredMessages;
};

/**
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
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override {}
	virtual bool NeedTransform_Implementation() override { return false; }
	virtual bool ShouldSave_Implementation() const override { return true; }
	// End IFSaveInterface

	//~ Begin AActor interface
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	//~ End AActor interface
	
	UFUNCTION( BlueprintCallable, Category = "Story" )
	float GetMaximumDelayForCall( TSubclassOf< class UFGAudioMessage > messageClass ) const;

	UFUNCTION( BlueprintCallable, Category = "Story" )
	bool IsPriorityCall( TSubclassOf< class UFGAudioMessage > messageClass ) const;

	/** Called when a schematic is unlocked */
	UFUNCTION()
	void OnSchematicPurchased( TSubclassOf< UFGSchematic > newSchematic );
	
	/** A player was added to the game */
	UFUNCTION()
	void AddPlayer( class AFGCharacterPlayer* inPlayer );

	/** Called when a player gets an item in its inventory */
	UFUNCTION()
	void OnPlayerAddedItemToInventory( TSubclassOf< class UFGItemDescriptor > itemClass, int32 numAdded );

	/** Called when a schematic has completed is research in the MAM */
	UFUNCTION()
	void OnResearchRecipeTimerComplete( TSubclassOf<class UFGSchematic> schematic );

	/** Called when a new research tree in unlocked */
	UFUNCTION()
	void OnResearchTreeUnlocked( TSubclassOf<UFGResearchTree> researchTree );

	/** Delegate for when a map area is visited for the first time by anyone */
	UFUNCTION()
	void OnMapAreaVisited( TSubclassOf< class UFGMapArea > mapArea );

	/** Triggered when an audio message has finished playing. */
    void OnAudioMessageFinishedPlaying( TSubclassOf< class UFGMessageBase > messageClass );

	/** Called when we want to decline a call with the given message */
	void DeclineCall( TSubclassOf< class UFGAudioMessage > messageToDecline );

	/** Send the given message to all players */
	void SendMessageToAllPlayers( TSubclassOf< UFGMessageBase > message );

	/** Trigger the next story message in given queue. If no story message is left in the queue nothing will happen */
	void TriggerNextStoryMessageInQueue( FActiveStoryQueue& storyQueue );

	/** Trigger the next story message in primary queue if there is any left */
	void Cheat_TriggerNextPrimaryStoryMessageInQueue();
	/** Trigger the next story message in the secondary queue with the given index if there is any left */
	void Cheat_TriggerNextSecondaryStoryMessageInQueue( int32 storyQueueIndex );
	/** Trigger the next floating message in primary queue if there is any left */
	void Cheat_TriggerNextFloatingMessageInPrimaryQueue();
	/** Trigger a random triggered barks message if there is any left */
	void Cheat_TriggerRandomTriggeredBarksMessage();
	/** Only for cheat menu. Starts the next story queue in the list if there is one available. Doesn't take into account for depencies or if the current queue is finished */
	void Cheat_StartNextStoryQueue();
	/** Only for cheat menu. Resets all story queues and start from the begining */
	void Cheat_ResetAllStoryQueues();
	/** Only for cheat menu. Reset the current story queue */
	void Cheat_ResetCurrentStoryQueue();
	
	void GetStoryDebugData( TArray<FString>& out_debugData );
	
protected:
	/** Sets up initial delegates */
	UFUNCTION()
	void SetupDelegates();

private:
	UFUNCTION()
	void OnGamePhaseUpdated( EGamePhase gamePhase );
	
	UFUNCTION()
	void UpdateStoryQueues();

	void UpdatePrimaryStoryQueue();

	void TickStoryQueues( float dt );
	
public:
	
	UPROPERTY()
	TArray< class AFGCharacterPlayer* > mActivePlayers;
private:
	/** array of schematic/message pairs */
	UPROPERTY( EditDefaultsOnly, Category = "Gameplay Narrative" )
	TArray< FSchematicMessagePair > mSchematicMessageData;

	/** array of item descriptor class/message and if they have been found already */
	UPROPERTY( SaveGame, EditDefaultsOnly, Category = "Gameplay Narrative" )
	TArray< FItemFoundData > mItemFoundData;

	UPROPERTY( EditDefaultsOnly, Category = "Gameplay Narrative" )
	TArray<FResearchTreeMessageData> mResearchTreeMessageData;

	UPROPERTY( EditDefaultsOnly, Category = "Gameplay Narrative" )
	TSubclassOf<class UFGMessageBase> mResearchTimerCompleteMessage;
	
	UPROPERTY( EditDefaultsOnly, Category = "Primary Story Narrative" )
	TArray< TSubclassOf< class UFGStoryQueue > > mPrimaryStoryQueues;

	UPROPERTY( EditDefaultsOnly, Category = "Secondary Story Narrative" )
	TArray< TSubclassOf< class UFGStoryQueue > > mSecondaryStoryQueues;

	UPROPERTY( EditDefaultsOnly, Category = "Triggered Barks" )
	TArray< TSubclassOf< class UFGEventTriggeredMessages > > mTriggeredBarks;

	UPROPERTY( SaveGame )
	FActiveStoryQueue mActivePrimaryStoryQueue;

	UPROPERTY( SaveGame )
	TArray<FActiveStoryQueue> mActiveSecondaryStoryQueues;

	UPROPERTY( SaveGame )
	int32 mNextPrimaryStoryQueueIndex;

	/** How long has it been since we played any narrative message */
	UPROPERTY( SaveGame )
	float mTimeSinceLastGlobalMessage;

	/** Minimum time we wait between story queue messages. i.e those that are triggered by time passed */
	UPROPERTY( EditDefaultsOnly, Category = "Narrative timer" )
	float mMinimumDelayBetweenStoryQueueMessages;

	TSubclassOf< class UFGMessageBase > mCallWaitingToBeAnswered;

	UPROPERTY( Transient )
	TArray< FEventTriggeredMessage > mPendingFloatingMessages;

	UPROPERTY( Transient )
	TArray< FEventTriggeredMessage > mPendingTriggeredBarks;
	
};

FORCEINLINE TSubclassOf< UFGSchematic > FSchematicMessagePair::GetSchematic() const
{
	return SchematicUnlocked.Get();
}

FORCEINLINE bool FItemFoundData::IsSchematicValid() const
{
	return SchematicClass.IsValid();
}

FORCEINLINE TSubclassOf< UFGSchematic > FItemFoundData::GetSchematic() const
{
	checkDev(SchematicClass.IsValid());
	return SchematicClass.Get();
}

FORCEINLINE TSubclassOf< class UFGItemDescriptor > FItemFoundData::GetItemDescriptor() const
{
	return ItemClass.Get();
}

FORCEINLINE bool FMapAreaVisitedData::IsSchematicValid() const
{
	return SchematicClass.IsValid();
}

FORCEINLINE TSubclassOf< UFGSchematic > FMapAreaVisitedData::GetSchematic() const
{
	checkDev(SchematicClass.IsValid());
	return SchematicClass.Get();
}