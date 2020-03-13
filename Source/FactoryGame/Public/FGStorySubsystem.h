// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGSubsystem.h"
#include "CoreMinimal.h"
#include "FGSaveInterface.h"
#include "UObject/NoExportTypes.h"
#include "FGSchematic.h"
#include "FGMapArea.h"
#include "FGResearchRecipe.h"
#include "FGStorySubsystem.generated.h"

USTRUCT( BlueprintType )
struct FACTORYGAME_API FMapAreaVisitedData
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

public:
	FORCEINLINE ~FMapAreaVisitedData() = default;
};

struct FACTORYGAME_API FFindByMapAreFound
{
	TSubclassOf< UObject > MapAreaFound;

	FFindByMapAreFound( TSubclassOf< UObject > InMapAreaFound ) : MapAreaFound( InMapAreaFound ) { }

	bool operator() ( const FMapAreaVisitedData Element ) const
	{
		return ( MapAreaFound == Element.MapAreaClass );
	}

public:
	FORCEINLINE ~FFindByMapAreFound() = default;
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FItemFoundData
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

public:
	FORCEINLINE ~FItemFoundData() = default;
};

struct FACTORYGAME_API FFindByItemFound
{
	TSubclassOf< UObject > ItemFound;

	FFindByItemFound( TSubclassOf< UObject > InItemFound ) : ItemFound( InItemFound ) { }

	bool operator() ( const FItemFoundData Element ) const
	{
		return ( ItemFound == Element.GetItemDescriptor() && !Element.WasFound );
	}

public:
	FORCEINLINE ~FFindByItemFound() = default;
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FSchematicMessagePair
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

public:
	FORCEINLINE ~FSchematicMessagePair() = default;
};

USTRUCT(BlueprintType)
struct FACTORYGAME_API FResearchTreeMessageData
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

public:
	FORCEINLINE ~FResearchTreeMessageData() = default;
};

/**
 * 
 */
UCLASS( abstract, Blueprintable )
class FACTORYGAME_API AFGStorySubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()
public:
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
	//~ End AActor interface

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
protected:
	/** Sets up initial delegates */
	UFUNCTION()
	void SetupDelegates();
public:
	UPROPERTY()
	TArray< class AFGCharacterPlayer* > mActivePlayers;
private:
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

public:
	FORCEINLINE ~AFGStorySubsystem() = default;
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
	// MODDING EDIT
	//checkDev(SchematicClass.IsValid());
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
	// MODDING EDIT
	//checkDev(SchematicClass.IsValid());
	return SchematicClass.Get();
}