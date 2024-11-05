// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Buildables/FGBuildableFactory.h"
#include "FGBuildablePowerBooster.generated.h"

/**
 * A factory that boosts the power production in the whole grid by a percentage.
 */
UCLASS()
class FACTORYGAME_API AFGBuildablePowerBooster : public AFGBuildableFactory
{
	GENERATED_BODY()
public:
	AFGBuildablePowerBooster();
	
	// Begin Actor interface
	virtual void PostInitProperties() override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void GetConditionalReplicatedProps(TArray<FFGCondReplicatedProperty>& outProps) const override;
	virtual void BeginPlay() override;
	// End Actor interface
	
	// Begin AFGBuildableFactory interface
	virtual bool CanProduce_Implementation() const override;
	virtual float GetProductionProgress() const override;
	virtual float GetProductionCycleTime() const override;
	virtual float GetDefaultProductionCycleTime() const override;
	virtual float GetProductivity() const override;
	// End AFGBuildableFactory interface

	/** The base power this booster produces. [MW] */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetBasePowerProduction() const { return mBasePowerProduction; };
	
	/** The current boost that is applied, default + dynamic from alien fuel. */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetBoostPercentage() const { return mBaseBoostPercentage + mCurrentFuelBoostPercentage; }

	/**
	 * Check if a resource is valid as fuel for this booster.
	 * @param resource Resource class to check.
	 * @return true if resource valid as fuel; false if not valid.
	 */
	UFUNCTION( BlueprintPure, Category = "Power" )
	bool IsValidFuel( TSubclassOf< class UFGItemDescriptor > resource ) const;
	
	/**
	 * @return a valid pointer to the inventory. Can be nullptr on client.
	 */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE class UFGInventoryComponent* GetFuelInventory() const { return mFuelInventory; };
	
	/**
	 * Check if this booster has additional fuel.
	 * Fuel is optional and provides and additional boost from the default boost.
	 * @return true if this booster has fuel; false if it has no fuel.
	 */
	UFUNCTION( BlueprintPure, Category = "Power" )
	bool HasFuel() const;
	
protected:
	// Begin AFGBuildableFactory interface
	virtual bool Factory_HasPower() const override;
	virtual void Factory_CollectInput_Implementation() override;
	virtual void Factory_TickProducing( float dt ) override;
	// End AFGBuildableFactory interface

	/** Try load fuel. */
	virtual void LoadFuel();

private:
	/**
	 * Filter out what we consider as fuel for our fuel inventory.
	 * @see IsValidFuel
	 */
	UFUNCTION()
	bool FilterFuelClasses( TSubclassOf< UObject > object, int32 idx ) const;

private:
	/** Base amount of power this booster always produces. [MW] */
	UPROPERTY( EditDefaultsOnly, Category = "Power" )
	float mBasePowerProduction;
	
	/**
	 * Amount this booster should boost the power production in the network.
	 * Example: 0.1 is a boost of 10%, 1.0 is a boost of 100%.
	 * If multiple boosters are added, the percentages are accumulated linearly.
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Power", Meta = ( UIMin = 0, UIMax = 1, ClampMin = 0 ) )
	float mBaseBoostPercentage;

	/** The boost percentage of the currently loaded fuel. This is on top of the default boost percentage.  */
	UPROPERTY( meta = ( FGReplicated ) )
	float mCurrentFuelBoostPercentage;

	/** Fuel classes this machine can run on. Leave empty if it does not run on fuel. */
	UPROPERTY( EditDefaultsOnly, Category = "Power", meta = ( MustImplement = "FGInventoryInterface" ) )
	TArray< TSoftClassPtr< class UFGItemDescriptorPowerBoosterFuel > > mDefaultFuelClasses;

	/** Current fuel classes of the generator, useful for runtime adding of fuel classes */
	UPROPERTY( meta = ( FGReplicated ) )
	TArray< TSubclassOf< class UFGItemDescriptorPowerBoosterFuel > > mAvailableFuelClasses;
	
	/** Inventory where fuel is loaded into. */
	UPROPERTY( SaveGame )
	class UFGInventoryComponent* mFuelInventory;

	/** Cached input connections */
	UPROPERTY()
	TArray< class UFGFactoryConnectionComponent* > mCachedInputConnections;

	/** Input inventory index to store the fuel */
	int32 mFuelInventoryIndex;
	
	/** Used so clients know how if they have available fuel or not. Could be removed later if we start syncing the production indicator state */
	UPROPERTY( SaveGame, Replicated, Meta = ( NoAutoJson = true ) )
	mutable bool mHasFuelCached;

	/** Type of the currently burned piece of fuel. */
	UPROPERTY( SaveGame, Meta = ( FGReplicated, NoAutoJson = true ) )
	TSubclassOf< class UFGItemDescriptor > mCurrentFuelClass;

	/** Duration for the current piece of fuel. */
	UPROPERTY( meta = ( FGReplicated ) )
	float mCurrentFuelDuration;
	
	/** Duration left for the current piece of fuel. */
	UPROPERTY( meta = ( FGReplicated ) )
	float mCurrentFuelDurationLeft;
};
