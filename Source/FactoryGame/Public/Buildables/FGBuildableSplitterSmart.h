// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildableConveyorAttachment.h"
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
};

USTRUCT()
struct FConveyorSpaceData
{
	GENERATED_BODY()
public:
	FConveyorSpaceData() :
		AvailableSpace( 0.f ),
		HasNewItem( false )
	{}

	FConveyorSpaceData( float availableSpace ) :
		AvailableSpace( availableSpace ),
		HasNewItem( false )
	{}

	// The last cached available space on the belt
	float AvailableSpace;

	// if the conveyor has a new item on it.
	bool HasNewItem;
};

/**
 * A smart splitter which you can tell where stuff should go!
 */
UCLASS()
class FACTORYGAME_API AFGBuildableSplitterSmart : public AFGBuildableConveyorAttachment
{
	GENERATED_BODY()
public:
	AFGBuildableSplitterSmart();

	//~ Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	// End AActor interface
	
	/** Begin Save Interface */
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	/** End Save Interface */

	//~ Begin IFGDismantleInterface
	virtual void GetDismantleRefund_Implementation( TArray< FInventoryStack >& out_refund, bool noBuildCostEnabled ) const override;
	// End IFGDismantleInterface
	
	// Begin Factory_ interface
	virtual void Factory_Tick( float deltaTime ) override;
	// End Factory_ interface

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

	UFUNCTION( BlueprintCallable, Category = "Sort" )
	TArray< FSplitterSortRule > GetSortRules() const { return mSortRules; }

	UFUNCTION( BlueprintCallable, Category = "Sort" )
	void SetSortRules( TArray< FSplitterSortRule > newSortRules );
	
protected:
	// Begin Factory_ interface
	virtual bool Factory_GrabOutput_Implementation( class UFGFactoryConnectionComponent* connection, FInventoryItem& out_item, float& out_OffsetBeyond, TSubclassOf< UFGItemDescriptor > type ) override;
	// End Factory_ interface

private:
	UFUNCTION()
	void OnRep_SortRules();

	/** Returns all connections that this item could be placed onto. It excludes wildcard outputs if there is a rule specifically set for this item type */
	TArray<UFGFactoryConnectionComponent*> GetAllOutputConnectionsForItem( const FInventoryItem& item, float deltaTime ) const;

	/**
	 * Populate the elements of the distribution table. The algorithm vaires between normal splitters and smart splitters. 
	 * The goal is to get all possible items assigned to an output while maintaining throughput and evenly splitting items between belts.
	 */
	void FillDistributionTable(float deltaTime);

	/** Returns an estimate of how many items the conveyor connected to the given component can grab. If no conveyor is connected it returns 0  */
	uint8 EstimatedMaxNumGrabFromConveyor( UFGFactoryConnectionComponent* factoryConnection, float dt ) const;

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
	
	/** Cycles through the outputs, stores the output we want to put mItem on. Index is for the mOutputs array. */
	UPROPERTY( SaveGame, Meta = (NoAutoJson) )
	int32 mCurrentOutputIndex;
	
	UPROPERTY( SaveGame )
	int32 mLastOutputIndex;
	
	bool mOnSortRulesChangedBlocker = false;
	
	UPROPERTY( SaveGame, Meta = ( NoAutoJson ) )
	int32 mCurrentInventoryIndex;

	/** Table of all items in the inventory mapped to a desired output. The array is filled from a call to FillDistributionTable which runs in factory tick */
	UPROPERTY()
	TArray< FConnectionItemStruct > mDistributionTable;
	
	/** Store last cached available space and if an item have been grabbed by the connected components  */
	UPROPERTY( Transient )
	TMap< UFGFactoryConnectionComponent*, FConveyorSpaceData > mConveyorSpaceData;
};
