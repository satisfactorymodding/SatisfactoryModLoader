// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildableFactory.h"
#include "FGFactoryClipboard.h"
#include "FGRecipeProducerInterface.h"
#include "FGBuildableManufacturer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnNewRecipeDelegate, TSubclassOf< class UFGRecipe >, newRecipe );

UCLASS()
class FACTORYGAME_API UFGManufacturerClipboardSettings : public UFGFactoryClipboardSettings
{
	GENERATED_BODY()
public:
	
	UPROPERTY( BlueprintReadWrite )
	TSubclassOf< UFGRecipe > mRecipe;

	/** The potential we would like to apply */
	UPROPERTY( BlueprintReadWrite )
	float mTargetPotential;

	/** The production boost we would like to apply */
	UPROPERTY( BlueprintReadWrite )
	float mTargetProductionBoost;

	/** The calculated potential we can apply with the shards/crystals we have. Used to simulate UI changes */
	UPROPERTY( BlueprintReadWrite )
	float mReachablePotential;

	/** The calculated production we can apply with the shards we have */
	UPROPERTY( BlueprintReadWrite )
	float mReachableProductionBoost;

	/** Descriptor for the overclocking shard item */
	UPROPERTY( BlueprintReadWrite )
	TSubclassOf<UFGPowerShardDescriptor> mOverclockingShardDescriptor;

	/** Descriptor for the production boost shard item */
	UPROPERTY( BlueprintReadWrite )
	TSubclassOf<UFGPowerShardDescriptor> mProductionBoostShardDescriptor;
};

UCLASS()
class FACTORYGAME_API UFGManufacturerClipboardRCO : public UFGRemoteCallObject
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	UFUNCTION( Server, Reliable )
	void Server_PasteSettings( class AFGBuildableManufacturer* manufacturer, AFGCharacterPlayer* player, TSubclassOf< class UFGRecipe > recipe, float overclock, float productionBoost, TSubclassOf<UFGPowerShardDescriptor> overclockingShard, TSubclassOf<UFGPowerShardDescriptor> productionBoostShard );

private:
	UPROPERTY( Replicated, Meta = ( NoAutoJson ) )
	bool mForceNetField_UFGManufacturerClipboardRCO = false;

};

/**
 * Base class for all buildings that are producing something out of something, i.e. constructors, smelters, refinery etc.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableManufacturer : public AFGBuildableFactory, public IFGRecipeProducerInterface
{
	GENERATED_BODY()
public:
	// Replication
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void GetConditionalReplicatedProps(TArray<FFGCondReplicatedProperty>& outProps) const override;

	/** Constructor */
	AFGBuildableManufacturer();

	// Begin AActor interface
	virtual void BeginPlay() override; 
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason );
	// End AActor interface

	// Begin AFGBuildableFactory interface
	virtual bool IsConfigured() const override;
	virtual float GetProductionCycleTime() const override;
	virtual float GetDefaultProductionCycleTime() const override;
	virtual float GetProductionCycleTimeForRecipe( TSubclassOf< UFGRecipe > recipe ) const override;
	virtual float CalcProductionCycleTimeForPotential( float potential ) const override;
	virtual void SetCurrentProductionBoost(float newProductionBoost) override;
	// End AFGBuildableFactory interface
	
	//~ Begin IFGFactoryClipboardInterface
	bool CanUseFactoryClipboard_Implementation() override { return true; }
	UFGFactoryClipboardSettings* CopySettings_Implementation() override;
	bool PasteSettings_Implementation( UFGFactoryClipboardSettings* settings ) override;
	//~ End IFGFactoryClipboardInterface

	// Begin IFGRecipeProducerInterface
	virtual TSubclassOf<UFGItemDescriptor> GetRecipeProducerItemDescriptor_Implementation(UObject* WorldContext) const override;
	// End IFGRecipeProducerInterface
	
	/**
	 * Move all items in the input inventory to the given inventory.
	 * @return true if successful; false if the given inventory is full or does not support the given type of item.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Inventory" )
	virtual bool MoveOrDropInputInventory( AFGCharacterPlayer* pawn );

	/**
	 * Move all items in the input output to the given inventory.
	 * @return true if successful; false if the given inventory is full or does not support the given type of item.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Inventory" )
	virtual bool MoveOrDropOutputInventory( AFGCharacterPlayer* pawn );

	/**
	 * Get the progress of the current production.
	 * @return - Percent in range [0,1] of the current production progress.
	 */	
	virtual float GetProductionProgress() const override;

	/** Checks whether or not this manufacturer contains any inputs. If false, this shouldn't contain an input component. Will be null on client. */
	FORCEINLINE bool HasAnyInputConnetions() const { return mFactoryInputConnections.Num() > 0 || mPipeInputConnections.Num() > 0; }

	/**
	 * Gets all the recipes that can be produced.
	 * @note This is an expensive operation so cache the result.
	 * @param out_recipes Returns all recipes available to this machine.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Recipe" )
	void GetAvailableRecipes( TArray< TSubclassOf< class UFGRecipe > >& out_recipes ) const;

	/** Returns the speed of which this building manufacture recipes */
	UFUNCTION(BlueprintPure, Category="FactoryGame|Factory|Production")
	FORCEINLINE float GetManufacturingSpeed() const{ return mManufacturingSpeed; }

	/** Get the input inventory from this manufacturer. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Inventory" )
	FORCEINLINE class UFGInventoryComponent* GetInputInventory() const { return mInputInventory; }

	/** Get the output inventory from this manufacturer. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Inventory" )
	FORCEINLINE class UFGInventoryComponent* GetOutputInventory() const { return mOutputInventory; }

	/** Get the current recipe for manufacturing. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Recipe" )
	FORCEINLINE TSubclassOf< class UFGRecipe > GetCurrentRecipe() const { return mCurrentRecipe; }

	/**
	 * Set the current recipe for manufacturing.
	 * @note It is up to the caller to make sure input and output inventories are empty before changing recipe.
	 *       This is so the case when players inventory is full can be handled correctly.
	 * @param recipe - The new recipe.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Recipe" )
	void SetRecipe( TSubclassOf< class UFGRecipe > recipe );

protected:
	// Begin AFGBuildableFactory interface
	virtual bool CanProduce_Implementation() const override;
	virtual void Factory_CollectInput_Implementation() override;
	virtual void Factory_PullPipeInput_Implementation( float dt ) override;
	virtual void Factory_PushPipeOutput_Implementation( float dt ) override;
	virtual void Factory_TickProducing( float dt ) override;
	// End AFGBuildableFactory interface

	// Begin IFGSaveInterface
	virtual void PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion) override;
	// End IFGSaveInterface

	UFUNCTION()
	void InvalidateCacheCanProduce_InputItemAdded( TSubclassOf< UFGItemDescriptor > itemClass, const int32 numAdded, UFGInventoryComponent* sourceInventory = nullptr );
	
	UFUNCTION()
	void InvalidateCacheCanProduce_InputItemRemoved( TSubclassOf< UFGItemDescriptor > itemClass, const int32 numAdded, UFGInventoryComponent* targetInventory = nullptr );
	
	UFUNCTION()
	void InvalidateCacheCanProduce_OutputItemAdded( TSubclassOf< UFGItemDescriptor > itemClass, const int32 numAdded, UFGInventoryComponent* sourceInventory = nullptr );
	
	UFUNCTION()
	void InvalidateCacheCanProduce_OutputItemRemoved( TSubclassOf< UFGItemDescriptor > itemClass, const int32 numAdded, UFGInventoryComponent* targetInventory = nullptr );

	/** Creates inventories needed for the manufacturer */
	virtual void CreateInventories();

	/** Called when NewRecipe is replicated */
	UFUNCTION()
	virtual void OnRep_CurrentRecipe();

	/** Read the items in the input inventory. */
	void GetInputInventoryItems( TArray< FInventoryStack >& out_items ) const;

	/** Clear the items in the input inventory. */
	void ClearInputInventoryItems();

	/** Read the items in the Output inventory. */
	void GetOutputInventoryItems( TArray< FInventoryStack >& out_items );

	/** Clear the items in the Output inventory. */
	void ClearOutputInventoryItems();

	/** This function sets the filters on the input and output inventories. */
	virtual void SetUpInventoryFilters();

	/** This function assigns an inventory index to each input connection to add ingredients to
	 *  @return - True if the ingredients did not exceed the availble connections possible. False otherwise. The Recipe should not be set if this fails.
	 */
	virtual bool AssignInputAccessIndices( TSubclassOf< UFGRecipe > recipe );

	/** This function assigns an inventory index to each output connection to pull from */
	virtual bool AssignOutputAccessIndices( TSubclassOf< UFGRecipe > recipe );

	/** 
	 * Helper function that actually removes ingredients from the manufacturers input. 
	 * This can differ between buildings (e.g. Converters), so override if you need something special. 
	 * @note this function assumes the available ingredients are there and have been checked with CanProduce()
	 */
	virtual void Factory_ConsumeIngredients();

	/**
	 * Returns true if the required ingredients are in the input slots.
	 * How this is checked can differ between buildings (e.g. Converters), so override if you need something special. 
	 */
	virtual bool HasRequiredIngredients() const;
protected:
	/** Called when a new recipe has been set. */
	UPROPERTY( BlueprintAssignable, Category = "Recipe" )
	FOnNewRecipeDelegate mCurrentRecipeChanged;

	/** The speed of which this building manufacture recipes, this is a multiplier to the recipe speed */
	UPROPERTY( EditDefaultsOnly, Category = "Production" )
	float mManufacturingSpeed;

	/** Manufacturing progress in range [0,1]. */
	UPROPERTY( SaveGame, Meta = ( NoAutoJson = true, FGReplicated ) )
	float mCurrentManufacturingProgress;

	/** Our input inventory, shared for all input connections. */
	UPROPERTY( SaveGame )
	class UFGInventoryComponent* mInputInventory;

	/** Cached factory input connections */
	UPROPERTY()
	TArray<class UFGFactoryConnectionComponent*> mFactoryInputConnections;

	/** Cached input pipe connections */
	UPROPERTY()
	TArray< class UFGPipeConnectionComponent* > mPipeInputConnections;

	/** Cached factory output connections */
	UPROPERTY()
	TArray<class UFGFactoryConnectionComponent*> mFactoryOutputConnections;

	/** Cached output pipe connections */
	UPROPERTY()
	TArray< class UFGPipeConnectionComponent* > mPipeOutputConnections;

	/** Our output inventory, shared for all output connections. */
	UPROPERTY( SaveGame )
	class UFGInventoryComponent* mOutputInventory;
	
	/** The recipe we're currently running. */
	UPROPERTY( SaveGame, Replicated, ReplicatedUsing = OnRep_CurrentRecipe, Meta = (NoAutoJson = true) )
	TSubclassOf< class UFGRecipe > mCurrentRecipe;

	/** The partial outputs carried over from the previous production cycles, used for production boost */
	UPROPERTY( SaveGame, Meta = (NoAutoJson = true) )
	TArray< float > mCurrentRecipeRemnants;

	/** Cached Recipe CDO to reduce calls.*/
	UPROPERTY()
	const UFGRecipe* mCachedRecipe;

	/* Updated once an item is removed from the input inventory.*/
	bool mCachedCanProduce;

	bool bCachedHasOutputSpace;
};
