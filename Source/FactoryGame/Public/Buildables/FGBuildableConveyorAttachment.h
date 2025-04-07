// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGBuildable.h"
#include "FGFactoryConnectionComponent.h"
#include "FGBuildableConveyorAttachment.generated.h"

/**
 * This is a struct that will assign an item to a certain connection. Used by splitters to cycle outputs so all items dont always go to one output
 */
USTRUCT()
struct FACTORYGAME_API FConnectionItemStruct
{
	GENERATED_BODY()

	FConnectionItemStruct() :
		Connection( nullptr ),
		Item( FInventoryItem() ),
		IndexInInventory( 0 ),
		OffsetBeyond( 0.0f ),
		Grabbed( false )
	{
	}

	FConnectionItemStruct( UFGFactoryConnectionComponent* inConnection, FInventoryItem inItem, float inOffsetBeyond, int32 indexInInventory ) :
		Connection( inConnection ),
		Item( inItem ),
		IndexInInventory( indexInInventory ),
		OffsetBeyond( inOffsetBeyond ),
		Grabbed( false )
	{
	}

	/** The connection to put the item on */
	UPROPERTY()
	class UFGFactoryConnectionComponent* Connection;

	/** The item to put on the connection */
	UPROPERTY()
	FInventoryItem Item;

	/** What is our index in the inventory component */
	int32 IndexInInventory;

	/** How far past the conveyor belt length this item is */
	float OffsetBeyond;

	/** To allow this to be thread safe, this bool marks if a table element has been consumed, to remove the need to delete from the table array */
	bool Grabbed;
};

// TODO 2023-02-07 Mattias Lindblad
// Evaluate if this should be moved to where other classes can extend it besides just Conveyor Attachments.
// Hologram Override exposes a way to override a hologram based on context gathered by the current override.
// See UFGHologramOverride_ConveyorAttachment_FloorToLift && UFGHologramOverride_ConveyorAttachment_LiftToFloor for details.
UCLASS(Abstract, Const, DefaultToInstanced, EditInlineNew)
class FACTORYGAME_API UFGHologramOverride : public UObject
{
	GENERATED_BODY()
public:

	// Simply returns the hologram override without doing any conditional checks.
	virtual TSubclassOf<UFGRecipe> GetHologramOverrideWithoutChecks() const { return nullptr; }

	// If we want to override which hologram should be displayed, return a valid recipe.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	TSubclassOf<UFGRecipe> GetHologramOverride(const AFGHologram* hologram, const FHitResult& hitResult) const;
	virtual TSubclassOf<UFGRecipe> GetHologramOverride_Implementation(const AFGHologram* hologram, const FHitResult& hitResult) const { return nullptr; }
};

UCLASS(Const, DefaultToInstanced, EditInlineNew)
class FACTORYGAME_API UFGHologramOverride_ConveyorAttachment_FloorToLift : public UFGHologramOverride
{
	GENERATED_BODY()
public:

	virtual TSubclassOf<UFGRecipe> GetHologramOverrideWithoutChecks() const override { return mRecipeToOverrideWith; }
	virtual TSubclassOf<UFGRecipe> GetHologramOverride_Implementation(const AFGHologram* hologram, const FHitResult& hitResult) const override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UFGRecipe> mRecipeToOverrideWith;
};

UCLASS(Const, DefaultToInstanced, EditInlineNew)
class FACTORYGAME_API UFGHologramOverride_ConveyorAttachment_LiftToFloor : public UFGHologramOverride
{
	GENERATED_BODY()
public:

	virtual TSubclassOf<UFGRecipe> GetHologramOverrideWithoutChecks() const override { return mRecipeToOverrideWith; }
	virtual TSubclassOf<UFGRecipe> GetHologramOverride_Implementation(const AFGHologram* hologram, const FHitResult& hitResult) const override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UFGRecipe> mRecipeToOverrideWith;
};

/**
 * Base class for conveyor attachments such as the splitters and mergers.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableConveyorAttachment : public AFGBuildable
{
	GENERATED_BODY()
public:
	AFGBuildableConveyorAttachment();

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin AFGBuildable interface
	virtual bool ShouldShowCenterGuidelinesForHologram( const AFGHologram* hologram ) const override;
	// End AFGBuildable interface

	//~ Begin IFGDismantleInterface
	virtual void Dismantle_Implementation() override;
	//~ End IFGDismantleInterface

	// Begin AFGBuildable
	virtual bool CanBeSampled_Implementation() const override;
	// End AFGBuildable

	/** @return The buffer inventory for this attachment, always valid, server only. */
	FORCEINLINE class UFGInventoryComponent* GetBufferInventory() const { return mBufferInventory; }

	// If the buildable has an override for the specific buildable, we return a set optional with the overriden recipe.
	TOptional<TSubclassOf<UFGRecipe>> GetHologramOverride( const AFGHologram* const hologram, const FHitResult& hitResult ) const;

	virtual bool HasOverrideForHologram( TSubclassOf<UFGItemDescriptor> itemDescriptor ) const override;

	void SaveCurrentDirections( );
	
protected:
	/** The size of the inventory for this attachment. Used to hold a buffer of incoming items */
	UPROPERTY( EditDefaultsOnly, Category = "Conveyor Attachment" )
	int32 mInventorySize;
	
	/** The buffer inventory to store the items in transit. */
	UPROPERTY( SaveGame )
	class UFGInventoryComponent* mBufferInventory;

	//Saved direction of the connections
	UPROPERTY( SaveGame )
	TArray<EFactoryConnectionDirection> mSavedDirections;

	/** Cached input connections for faster lookup. */
	TArray< UFGFactoryConnectionComponent* > mInputs;

	/** Cached output connections for faster lookup. */
	TArray< UFGFactoryConnectionComponent* > mOutputs;

	/** Cached linear size of the inventory component*/
	int32 mCachedInventorySize;

	// If the player hovers over a buildable of a certain type, we may want to hot swap the active conveyor attachment.
	// Example: When building a normal conveyor splitter, and we hover over a conveyor lift, we want to switch to a conveyor lift splitter.
	UPROPERTY(Instanced, EditDefaultsOnly, BlueprintReadOnly, Category = "Buildable", meta = (AllowAbstract = false))
	TArray<UFGHologramOverride*> mHologramOverrides;
};

/* Lightweight class containing no components, used for abstract instances etc. */
UCLASS()
class FACTORYGAME_API AFGBuildableConveyorAttachmentLightweight : public AFGBuildableConveyorAttachment
{
	GENERATED_BODY()
	AFGBuildableConveyorAttachmentLightweight();
};
