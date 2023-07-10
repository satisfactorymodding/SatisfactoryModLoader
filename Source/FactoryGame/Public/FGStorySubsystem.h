// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FactoryGame.h"
#include "FGSubsystem.h"
#include "CoreMinimal.h"
#include "FGSaveInterface.h"
#include "UObject/NoExportTypes.h"
#include "FGSchematic.h"
#include "FGResearchRecipe.h"
#include "FGStoryQueue.h"
#include "FGRemoteCallObject.h"
#include "FGStorySubsystem.generated.h"

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

UCLASS()
class FACTORYGAME_API UFGStorySubsystemRemoteCallObject : public UFGRemoteCallObject
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
		
	UFUNCTION( Reliable, Client )
	void Client_PlayMessages( const TArray<class UFGMessage*>& newMessages );
	
	UPROPERTY( Replicated, Meta = ( NoAutoJson ) )
	bool mForceNetField_UFGStorySubsystemRemoteCallObject = false;
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
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override {}
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override {}
	virtual bool NeedTransform_Implementation() override { return false; }
	virtual bool ShouldSave_Implementation() const override { return true; }
	// End IFSaveInterface

	//~ Begin AActor interface
	virtual void BeginPlay() override;
	//~ End AActor interface
	
	/** A player was added to the game */
	UFUNCTION()
	void OnPlayerAdded( class AFGCharacterPlayer* inPlayer );

	/** Called when a player gets an item in its inventory */
	UFUNCTION()
	void OnItemAddedToPlayerInventory( TSubclassOf< class UFGItemDescriptor > itemClass, int32 numAdded );

	/** Called when a schematic is unlocked */
	UFUNCTION()
	void OnSchematicPurchased( TSubclassOf< UFGSchematic > newSchematic );

	/** Called when a new research tree in unlocked */
	UFUNCTION()
	void OnResearchTreeUnlocked( TSubclassOf<UFGResearchTree> researchTree );

	/** Triggered when an audio message has finished playing. */
    void OnAudioMessageFinishedPlaying( TSubclassOf< class UFGMessageBase > messageClass );

	void PlayMessages( TArray<class UFGMessage*> messages );
	
	void GetStoryDebugData( TArray<FString>& out_debugData );

private:
	UFUNCTION()
	void SetupDelegates();
	
	UFUNCTION()
	void TryPlayNewMessage();	
	
private:
	/** array of schematic/message pairs */
	UPROPERTY( VisibleDefaultsOnly, Category = "Gameplay Narrative" )
	TArray< FSchematicMessagePair > mSchematicMessageData;

	/** array of item descriptor class/message and if they have been found already */
	UPROPERTY( SaveGame, VisibleDefaultsOnly, Category = "Gameplay Narrative" )
	TArray< FItemFoundData > mItemFoundData;

	UPROPERTY( VisibleDefaultsOnly, Category = "Gameplay Narrative" )
	TArray<FResearchTreeMessageData> mResearchTreeMessageData;

	UPROPERTY( Transient )
	TArray< class UFGMessage* > mUnplayedMessages;
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