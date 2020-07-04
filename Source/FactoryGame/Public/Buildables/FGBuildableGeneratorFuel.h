// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/CoreNet.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGBuildableGenerator.h"
#include "../Replication/FGReplicationDetailInventoryComponent.h"
#include "../Replication/FGReplicationDetailActorOwnerInterface.h"
#include "../Replication/FGReplicationDetailActor_GeneratorFuel.h"
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
	virtual void PreReplication( IRepChangedPropertyTracker& ChangedPropertyTracker ) override;
	virtual void BeginPlay() override;
	// End AACtor interface

	// Begin UObject interface
	virtual void PostLoad() override;
	// End UObject interface

	// Begin Factory_ interface
	virtual void Factory_Tick( float dt ) override;
	// End Factory_ interface

	// Begin IFGReplicationDetailActorOwnerInterface
	virtual UClass* GetReplicationDetailActorClass() const override { return AFGReplicationDetailActor_GeneratorFuel::StaticClass(); };
	// End IFGReplicationDetailActorOwnerInterface

	// Begin IFGDismantleInterface
	virtual void GetDismantleRefund_Implementation( TArray< FInventoryStack >& out_refund ) const override;
	// End IFGDismantleInterface

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
	FORCEINLINE class UFGInventoryComponent* GetFuelInventory() const { return mFuelInventoryHandler->GetActiveInventoryComponent(); };

	/**
	 * Check if this generator has fuel.
	 * @return - true if this generator has fuel; false if it has no fuel.
	 */
	UFUNCTION( BlueprintPure, Category = "Power" )
	bool HasFuel() const;

	/**
	 * Get the specified resource form for Fuel allowed to be used in this generator.
	 */
	UFUNCTION( BlueprintPure, Category = "Power" )
	FORCEINLINE EResourceForm GetFuelResourceForm() const { return mFuelResourceForm; }

	/**
	* Check if this generator has the required supplemental resource available
	* @return - true if the resource is present OR if a supplemental resource is not needed. False otherwise.
	*/
	UFUNCTION( BlueprintPure, Category = "Power" )
	bool HasSuppleentalResource() const;

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
	UFUNCTION( BlueprintPure, Category = "Power" )
	FORCEINLINE TArray< TSubclassOf< class UFGItemDescriptor > > GetAvailableFuelClasses() const { return mAvailableFuelClasses; }

	/** Returns the class of the supplemental resource required (can be null) */
	UFUNCTION( BlueprintPure, Category = "Power" )
	FORCEINLINE TSubclassOf< class UFGItemDescriptor > GetSupplementalResourceClass() const { return mSupplementalResourceClass; }

protected:
	/** Try to collect fuel from an input. */
	void Factory_CollectFuel( float dt );

	/** Try to collect secondary resource from an input ( if one is specified ) */
	void Factory_CollectSupplimentalResource( float dt );

	/** Try load fuel into the burner. */
	virtual void LoadFuel();

	/** Try to load supplemental resource needed for generating */
	virtual void LoadSupplemental();

	// Begin AFGBuildableGenerator interface
	virtual bool CanStartPowerProduction_Implementation() const override;
	virtual void Factory_StartPowerProduction_Implementation() override;
	virtual void Factory_StopPowerProduction_Implementation() override;
	virtual void Factory_TickPowerProduction_Implementation( float dt ) override;
	// End AFGBuildableGenerator interface

	/** Can we load fuel in to the generator */
	virtual bool CanLoadFuel( ) const;

	/** Can we load supplemental resources into the generator */
	virtual bool CanLoadSupplenmental() const;

	virtual void OnRep_ReplicationDetailActor() override;


private:
	/**
	 * Filter out what we consider as fuel for our fuel inventory.
	 * @see IsValidFuel
	 */
	UFUNCTION()
	bool FilterFuelClasses( TSubclassOf< UObject > object, int32 idx ) const;

	/** Set up the fuel inventory when replicated */
	UFUNCTION()
	void OnRep_FuelInventory();


	class AFGReplicationDetailActor_GeneratorFuel* GetCastRepDetailsActor() const;

public:
	friend class AFGReplicationDetailActor_GeneratorFuel;

	/** Maintainer of the active storage component for this actor. Use this to get the active inventory component. */
	UPROPERTY()
	class UFGReplicationDetailInventoryComponent* mFuelInventoryHandler;

	/** Fuel classes this machine can run on. Leave empty if it does not run on fuel. */
	UPROPERTY()
	TArray< TSubclassOf< class UFGItemDescriptor > > mFuelClasses_DEPRECATED;

	/** Fuel classes this machine can run on. Leave empty if it does not run on fuel. */
	UPROPERTY( EditDefaultsOnly, Category = "Power", meta = ( MustImplement = "FGInventoryInterface" ) )
	TArray< TSoftClassPtr< class UFGItemDescriptor > > mDefaultFuelClasses;

	/** Current fuel classes of the generator, useful for runtime adding of fuel classes */
	UPROPERTY( Replicated )
	TArray< TSubclassOf< class UFGItemDescriptor > > mAvailableFuelClasses;

	/** The form of resource this generator is allowed to accept. ie. SOLID or LIQUID */
	UPROPERTY( EditDefaultsOnly, Category = "Power" )
	EResourceForm mFuelResourceForm;

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

	/** @todo: Cleanup, this shouldn't need to be replicated, clients should be able to fetch this anyway. Static index of fuel slot? */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_FuelInventory )
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
	UPROPERTY( SaveGame, Replicated, Meta = (NoAutoJson = true) )
	float mCurrentFuelAmount;

	/** Amount left of the currently loaded supplemental resource. In Liters ( 1 Liquid inventory item = 1 Liter ) */
	UPROPERTY( SaveGame, Replicated, Meta = ( NoAutoJson = true ) )
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

public:
	FORCEINLINE ~AFGBuildableGeneratorFuel() = default;
};
