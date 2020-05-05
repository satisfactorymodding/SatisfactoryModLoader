// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGBuildableAttachmentSplitter.h"
#include "FGBuildableSplitterSmart.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnSortRulesChanged );

USTRUCT( BlueprintType )
struct FACTORYGAME_API FSplitterSortRule
{
	GENERATED_BODY()
public:

	FSplitterSortRule() :
		ItemClass( nullptr ),
		OutputIndex( INDEX_NONE )
	{
	}

	FSplitterSortRule( TSubclassOf< class UFGItemDescriptor > itemClass, int32 outputIndex ) :
		ItemClass( itemClass ),
		OutputIndex( outputIndex )
	{
	}

	/** This is the item class to filter out. */
	UPROPERTY( SaveGame, BlueprintReadWrite, EditDefaultsOnly, Category = "Sort Rule" )
	TSubclassOf< UFGItemDescriptor > ItemClass;

	/** Which output to send this to. */
	UPROPERTY( SaveGame, BlueprintReadWrite, EditDefaultsOnly, Category = "Sort Rule" )
	int32 OutputIndex;

public:
	FORCEINLINE ~FSplitterSortRule() = default;
};

/**
 * A smart splitter which you can tell where stuff should go!
 */
UCLASS()
class FACTORYGAME_API AFGBuildableSplitterSmart : public AFGBuildableAttachmentSplitter
{
	GENERATED_BODY()
public:
	AFGBuildableSplitterSmart();

	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	/** Begin Save Interface */
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	/** End Save Interface */

	/** Get the number of sort rules this splitter has. */
	UFUNCTION( BlueprintPure, Category = "Sort" )
	FORCEINLINE int32 GetNumSortRules() const { return mSortRules.Num(); }

	/** Get number of max sort rules. */
	UFUNCTION( BlueprintPure, Category = "Sort" )
	FORCEINLINE int32 GetMaxNumSortRules() const { return mMaxNumSortRules; }

	/** Is this a valid sort rule index */
	UFUNCTION( BlueprintPure, Category = "Sort" )
	bool IsValidSortRuleAt( int32 index ) const { return mSortRules.IsValidIndex( index ); }

	/** Get the number of sort rules this splitter has. */
	UFUNCTION( BlueprintPure, Category = "Sort" )
	FSplitterSortRule GetSortRuleAt( int32 index ) const;

	/** Adds a new sort rule. */
	UFUNCTION( BlueprintCallable, Category = "Sort" )
	void AddSortRule( FSplitterSortRule rule );

	/** Removes the rule at passed index. */
	UFUNCTION( BlueprintCallable, Category = "Sort" )
	void RemoveSortRuleAt( int32 index );

	/** Updates the sort rule at the passed index. */
	UFUNCTION( BlueprintCallable, Category = "Sort" )
	void SetSortRuleAt( int32 index, FSplitterSortRule rule );

protected:
	// Begin Factory_ interface
	virtual bool Factory_GrabOutput_Implementation( class UFGFactoryConnectionComponent* connection, FInventoryItem& out_item, float& out_OffsetBeyond, TSubclassOf< UFGItemDescriptor > type ) override;
	// End Factory_ interface

	virtual void FillDistributionTable(float deltaTime) override;

private:
	UFUNCTION()
	void OnRep_SortRules();

	/** Returns all connections that this item could be placed onto. It excludes wildcard outputs if there is a rule specifically set for this item type */
	TArray<UFGFactoryConnectionComponent*> GetAllOutputConnectionsForItem( const FInventoryItem& item, float deltaTime ) const;

protected:
	UPROPERTY( BlueprintAssignable )
	FOnSortRulesChanged OnSortRulesChangedDelegate;

private:
	/** These are the sorting rules the player has entered. */
	UPROPERTY( ReplicatedUsing = OnRep_SortRules, SaveGame, EditDefaultsOnly, Category = "Sort", Meta = (NoAutoJson = true) )
	TArray< FSplitterSortRule > mSortRules;

	/** How many rules this splitter can have. */
	UPROPERTY( EditDefaultsOnly, Category = "Sort", meta = ( UIMin = "1", UIMax = "64" ) )
	int32 mMaxNumSortRules;

	UPROPERTY( SaveGame )
	FInventoryItem mLastItem;

	UPROPERTY( SaveGame )
	TMap< TSubclassOf< UFGItemDescriptor >, uint8> mItemToLastOutputMap;

	UPROPERTY( SaveGame )
	int32 mLastOutputIndex;


public:
	FORCEINLINE ~AFGBuildableSplitterSmart() = default;
};
