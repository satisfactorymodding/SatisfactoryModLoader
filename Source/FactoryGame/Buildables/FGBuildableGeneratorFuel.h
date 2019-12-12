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
	 * How much of the fuel have we burned? In range [0,1].
	 */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetFuelAmount() const;

	/** We want to change the potential instantly on generators ? */
	virtual void SetPendingPotential( float newPendingPotential ) override;

	/** Returns the currently used fuel class */
	UFUNCTION( BlueprintPure, Category = "Power" )
	FORCEINLINE TSubclassOf< class UFGItemDescriptor > GetCurrentFuelClass() const { return mCurrentFuelClass; }

protected:
	/** Try to collect fuel from an input. */
	void Factory_CollectFuel();

	/** Try load fuel into the burner. */
	virtual void LoadFuel();

	// Begin AFGBuildableGenerator interface
	virtual bool CanStartPowerProduction_Implementation() const override;
	virtual void Factory_StartPowerProduction_Implementation() override;
	virtual void Factory_StopPowerProduction_Implementation() override;
	virtual void Factory_TickPowerProduction_Implementation( float dt ) override;
	// End AFGBuildableGenerator interface

	/** Can we load fuel in to the generator */
	virtual bool CanLoadFuel( ) const;

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

	virtual void OnRep_ReplicationDetailActor() override;

	class AFGReplicationDetailActor_GeneratorFuel* GetCastRepDetailsActor() const;

protected:
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

	/** @todo: Cleanup, this shouldn't need to be replicated, clients should be able to fetch this anyway. Static index of fuel slot? */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_FuelInventory )
	class UFGInventoryComponent* mFuelInventory;

	/** Cached input connections (No need for UPROPERTY as they are referenced in component array) */
	TArray<class UFGFactoryConnectionComponent*> mCachedInputConnections;

	/** Amount left of the currently burned piece of fuel. In megawatt seconds (MWs). */
	UPROPERTY( SaveGame, Replicated, Meta = (NoAutoJson = true) )
	float mCurrentFuelAmount;

	/** Used so clients know how if they have available fuel or not. Could be removed later if we start syncing the production indicator state */
	UPROPERTY( SaveGame, Replicated, Meta = ( NoAutoJson = true ) )
	mutable bool mHasFuleCached;
	

	/** Type of the currently burned piece of fuel. */
	UPROPERTY( SaveGame, Replicated, Meta = (NoAutoJson = true) )
	TSubclassOf< class UFGItemDescriptor > mCurrentFuelClass;
};
