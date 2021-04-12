// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	StoryQueueIndex( 0 ),
	MessageIndex( 0 ),
	BarkMessageIndex( 0 ),
	PendingMessageFromMilestone( false ),
    PendingMessageTimer( 0.0f ),
    TimeSinceLastMessage( 0.0f ),
	StoryMessageCurrentlyPlaying( nullptr )
	{};

	FActiveStoryQueue( TSubclassOf<class UFGStoryQueue> storyQueueClass, int32 storyQueueIndex ) :
	StoryQueueClass( storyQueueClass ),
	StoryQueueIndex( storyQueueIndex ),
	MessageIndex( 0 ),
	BarkMessageIndex( 0 ),
	PendingMessageFromMilestone( false ),
	PendingMessageTimer( 0.0f ),
	TimeSinceLastMessage( 0.0f ),
	StoryMessageCurrentlyPlaying( nullptr )
	{};

	FORCEINLINE bool IsValid() const
	{
		return StoryQueueClass != nullptr;
	}

	void ResetStoryQueue();

	FORCEINLINE bool ContainsUnplayedMessages() const;

	FORCEINLINE bool ContainsUnplayedBarkMessages() const;

	TSubclassOf< class UFGMessageBase > PopMessage();

	TSubclassOf< class UFGMessageBase > PopBarkMessage();

	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Story" )
	TSubclassOf<class UFGStoryQueue> StoryQueueClass;

	int32 StoryQueueIndex;

	int32 MessageIndex;

	int32 BarkMessageIndex;

	bool PendingMessageFromMilestone;

	float PendingMessageTimer;

	float TimeSinceLastMessage;

	// The message we are waiting for to finish playing. This is used so we don't start ticking TimeSinceLastMessage until we actually played the message.
	UPROPERTY()
	TSubclassOf< class UFGMessageBase > StoryMessageCurrentlyPlaying;

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

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	// End AActor interface
	
	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	//~ Begin AActor interface
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	//~ End AActor interface

	UFUNCTION( BlueprintPure, Category = "Story" )
	TSubclassOf< class UFGStoryQueue > GetActiveStoryQueueClass() const { return mActiveStoryQueueClass; } 

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

	/** Trigger the next story message in queue. If no story message is left in the queue nothing will happen*/
	void TriggerNextStoryMessageInQueue();

	/** Trigger the next story message in queue. If we still have story messages left in the queue nothing will happen*/
	void TriggerNextBarkMessageInQueue();

	void GetStoryDebugData( TArray<FString>& out_debugData );

	/** Only for cheat menu. Starts the next story queue in the list if there is one available. Doesn't take into account for depencies or if the current queue is finished */
	void StartNextStoryQueue();

	/** Only for cheat menu. Resets all story queues and start from the begining */
	void ResetAllStoryQueues();

	/** Only for cheat menu. Reset the current story queue */
	void ResetCurrentStoryQueue();
	
protected:
	/** Sets up initial delegates */
	UFUNCTION()
	void SetupDelegates();

private:
	UFUNCTION()
	void OnGamePhaseUpdated( EGamePhase gamePhase );
	
	UFUNCTION()
	void UpdateStoryQueue();
	
public:
	
	UPROPERTY()
	TArray< class AFGCharacterPlayer* > mActivePlayers;
private:
	UPROPERTY( EditDefaultsOnly, Category = "Story" )
	TArray< TSubclassOf< class UFGStoryQueue > > mStoryQueues;

	UPROPERTY( SaveGame )
	FActiveStoryQueue mActiveStoryQueue;

	/** Part of mActiveStoryQueue but we only need the class replicated */ 
	UPROPERTY( Replicated )
	TSubclassOf< class UFGStoryQueue > mActiveStoryQueueClass;
	
	/** array of schematic/message pairs */
	UPROPERTY( EditDefaultsOnly, Category = "Story|Schematic" )
	TArray< FSchematicMessagePair > mSchematicMessageData;

	/** array of item descriptor class/message and if they have been found already */
	UPROPERTY( SaveGame, EditDefaultsOnly, Category = "Story|Item" )
	TArray< FItemFoundData > mItemFoundData;

	UPROPERTY( EditDefaultsOnly, Category = "Story|Research" )
	TArray<FResearchTreeMessageData> mResearchTreeMessageData;

	UPROPERTY( EditDefaultsOnly, Category = "Story|Research" )
	TSubclassOf<class UFGMessageBase> mResearchTimerCompleteMessage;
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