// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildableGenerator.h"
#include "FGBuildableGeneratorFuel.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildableGeneratorFuel : public AFGBuildableGenerator
{
	GENERATED_BODY()
public:
	AFGBuildableGeneratorFuel();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void GetConditionalReplicatedProps(TArray<FFGCondReplicatedProperty>& outProps) const override;
	virtual void BeginPlay() override;
	// End AACtor interface

	// Begin UObject interface
	virtual void PostLoad() override;
	// End UObject interface

	// Begin Factory_ interface
	virtual void Factory_Tick( float dt ) override;
	// End Factory_ interface
	
	/**
	 * Check if a resource is valid as fuel for this generator.
	 * @param resource - Resource class to check.
	 * @return - true if resource valid as fuel; false if not valid or if generator does not run on fuel.
	 */
	UFUNCTION( BlueprintPure, Category = "Power" )
	bool IsValidFuel( TSubclassOf< class UFGItemDescriptor > resource ) const;

	/**
	* Check if an item class is a required supplemental resource
	* @param resource - Item or Resource class to check if it matches the set Supplemental Resouce Class
	* @return - true if they're the same item / resource; otherwise false
	*/
	UFUNCTION( BlueprintPure, Category = "Power" )
	bool IsValidSupplementalResource( TSubclassOf< class UFGItemDescriptor > resource ) const;

	/**
	 * @return a valid pointer to the inventory if this machine runs on fuel. Can be nullptr on client.
	 */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE class UFGInventoryComponent* GetFuelInventory() const { return mFuelInventory; };

	/**
	 * Check if this generator has fuel.
	 * @return - true if this generator has fuel; false if it has no fuel.
	 */
	UFUNCTION( BlueprintPure, Category = "Power" )
	bool HasFuel() const;

	/**
	* Check if this generator has the required supplemental resource available
	* @return - true if the resource is present OR if a supplemental resource is not needed. False otherwise.
	*/
	UFUNCTION( BlueprintPure, Category = "Power" )
	bool HasSupplementalResource() const;

	/**
	 * Returns true if this generator requires a supplemental resource to run
	 */
	UFUNCTION( BlueprintPure, Category = "Power" )
	FORCEINLINE bool GetRequiresSupplementalResource() const { return mRequiresSupplementalResource; }

	/**
	 * Get the current Supplemental resource consumption rate in M^3/s (Cubic Meters per Second)
	 */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetSupplementalConsumptionRateCurrent() const;

	/**
	 * Get the maximum Supplemental resource consumption rate in M^3/s (Cubic Meters per Second)
	 */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetSupplementalConsumptionRateMaximum() const;

	/**
	 * How much of the fuel have we burned? In range [0,1].
	 */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetFuelAmount() const;

	/** How much of the supplemental resource is remaining? In range [0,1] */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetSupplementalAmount() const;

	/** We want to change the potential instantly on generators ? */
	virtual void SetPendingPotential( float newPendingPotential ) override;

	/** Returns the currently used fuel class */
	UFUNCTION( BlueprintPure, Category = "Power" )
	FORCEINLINE TSubclassOf< class UFGItemDescriptor > GetCurrentFuelClass() const { return mCurrentFuelClass; }

	/** Returns all fuel classes this generator can use */
	UFUNCTION( BlueprintCallable, Category = "Power" )
	TArray< TSubclassOf< UFGItemDescriptor > > GetAvailableFuelClasses( const UFGInventoryComponent* instigatorInventory );

	/** Returns the class of the supplemental resource required (can be null) */
	UFUNCTION( BlueprintPure, Category = "Power" )
	FORCEINLINE TSubclassOf< class UFGItemDescriptor > GetSupplementalResourceClass() const { return mSupplementalResourceClass; }

	/** Returns all fuel classes this generator can run on. Exposed for AutoJSonExportCommandlet */
	FORCEINLINE TArray< TSoftClassPtr< class UFGItemDescriptor > > GetDefaultFuelClasses() const { return mDefaultFuelClasses; }

	FORCEINLINE int32 GetFuelInventoryIndex() const { return mFuelInventoryIndex; }
	FORCEINLINE int32 GetSupplementalResourceInventoryIndex() const { return mSupplementalInventoryIndex; }
protected:
	// Begin AFGBuildableGenerator interface
    virtual bool CanStartPowerProduction_Implementation() const override;
    virtual void Factory_StartPowerProduction_Implementation() override;
    virtual void Factory_StopPowerProduction_Implementation() override;
    virtual void Factory_TickPowerProduction_Implementation( float dt ) override;
    // End AFGBuildableGenerator interface
	
	/** Try to collect fuel from an input. */
	void Factory_CollectFuel( float dt );
	/** Try to collect secondary resource from an input ( if one is specified ) */
	void Factory_CollectSupplementalResource( float dt );

	/** Try load fuel into the burner. */
	virtual void LoadFuel();
	/** Try to load supplemental resource needed for generating */
	virtual void LoadSupplemental();

	/** Can we load fuel in to the generator. Only call this on server. */
	virtual bool CanLoadFuel() const;
	/** Can we load supplemental resources into the generator. Only call this on server. */
	virtual bool CanLoadSupplemental() const;

private:
	/**
	 * Filter out what we consider as fuel for our fuel inventory.
	 * @see IsValidFuel
	 */
	UFUNCTION()
	bool FilterFuelClasses( TSubclassOf< UObject > object, int32 idx ) const;
	
	void UpdateInInventoryFuelTypes( const UFGInventoryComponent* instigatorInventory );
	TArray< TSubclassOf< UFGItemDescriptor > > UpdateUnlockedFuelTypes();

protected:
	/** Kept for save game compatibility. @see mDefaultFuelClasses */
	UPROPERTY()
	TArray< TSubclassOf< class UFGItemDescriptor > > mFuelClasses_DEPRECATED;

	/** Fuel classes this machine can run on. */
	UPROPERTY( EditDefaultsOnly, Category = "Power", meta = ( MustImplement = "FGInventoryInterface" ) )
	TArray< TSoftClassPtr< UFGItemDescriptor > > mDefaultFuelClasses;

	/** Current fuel classes of the generator, useful for runtime adding of fuel classes */
	UPROPERTY( Replicated )
	TArray< TSubclassOf< UFGItemDescriptor > > mAvailableFuelClasses;

	/** Fuel types we can use because they are in our inventory. */
	UPROPERTY( Replicated )
	TArray< TSubclassOf< UFGItemDescriptor > > mFuelClassesInInventory;
	
	/** True if this class runs on fluids, i.e. liquids or gases. False if it runs on solids. */
	bool mUsesFluidsAsFuel;

	/** 
	*	The quantity of inventory to be loaded for use during generation.
	*	Any quantity less than this will fail to load and halt generation of electricity.
	*	This is used for fuels so 1 liter isn't loaded constantly which makes the progress bar worthless
	*	@note - 1 unit equates to 1 Liter. So 1000 units would be 1 Cubic Meter.
	*/
	UPROPERTY( EditDefaultsOnly, Category = "Power" )
	int32 mFuelLoadAmount;

	/** Does this generator require a secondary NON fuel source to generate power? */
	UPROPERTY( EditDefaultsOnly, Category = "Power" )
	bool mRequiresSupplementalResource;

	/** Required secondary resource class to continue with generation. Tex. Water. Leave empty if none is desired */
	UPROPERTY( EditDefaultsOnly, Category = "Power", meta = ( EditCondition = mRequiresSupplementalResource ) )
	TSubclassOf< class UFGItemDescriptor > mSupplementalResourceClass;

	/** The quantity of supplemental inventory to be loaded for use during generation.
	*	Any quantity less than this will fail to load and halt generation. This acts as a buffer against constant starting and stopping
	*	of generation of electricity. 
	*	@note - 1 unit equates to 1 Liter. So 1000 units would be 1 Cubic Meter.
	*/
	UPROPERTY( EditDefaultsOnly, Category = "Power", meta = ( EditCondition = mRequiresSupplementalResource ) )
	int32 mSupplementalLoadAmount;
	
	/** The quantity of supplemental resource to consume per megawatt of power produced */
	UPROPERTY( EditDefaultsOnly, Category = "Power", meta = ( EditCondition = mRequiresSupplementalResource ) )
	float mSupplementalToPowerRatio;

	/** If true, the generator always produces at full capacity; if false, it only produces on-demand */
	UPROPERTY( EditDefaultsOnly, Category = "Power" )
	bool mIsFullBlast;

	/** Inventory where fuel is loaded into. */
	UPROPERTY( SaveGame )
	class UFGInventoryComponent* mFuelInventory;

	/** Cached input connections */
	UPROPERTY()
	TArray<class UFGFactoryConnectionComponent*> mCachedInputConnections;

	/** Cached pipe input connections */
	UPROPERTY()
	TArray< class UFGPipeConnectionComponent* > mCachedPipeInputConnections;

	/** Input inventory index to store the fuel */
	int32 mFuelInventoryIndex;

	/** Input inventory index to store the supplemental resource */
	int32 mSupplementalInventoryIndex;

	/** Amount left of the currently burned piece of fuel. In megawatt seconds (MWs). */
	UPROPERTY( SaveGame, Meta = ( NoAutoJson = true, FGReplicated ) )
	float mCurrentFuelAmount;

	/** Amount left of the currently loaded supplemental resource. In Liters ( 1 Liquid inventory item = 1 Liter ) */
	UPROPERTY( SaveGame, Meta = ( NoAutoJson = true, FGReplicated ) )
	float mCurrentSupplementalAmount;

	/** Used so clients know how if they have available fuel or not. Could be removed later if we start syncing the production indicator state */
	UPROPERTY( SaveGame, Replicated, Meta = ( NoAutoJson = true ) )
	mutable bool mHasFuelCached;

	/** Like the mHasFuelCached - Used to notify clients if there is enough supplemental resource available */
	UPROPERTY( SaveGame, Replicated, Meta = ( NoAutoJson = true ) )
	mutable bool mHasSupplementalCached;

	/** Type of the currently burned piece of fuel. */
	UPROPERTY( SaveGame, Replicated, Meta = (NoAutoJson = true) )
	TSubclassOf< class UFGItemDescriptor > mCurrentFuelClass;
};
