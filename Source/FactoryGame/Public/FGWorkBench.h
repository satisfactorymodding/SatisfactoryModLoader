
#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "Components/SceneComponent.h"
#include "FGSaveInterface.h"
#include "FGVehicle.h"
#include "FGRecipeProducerInterface.h"
#include "FGWorkBench.generated.h"

/**
 * Component attachable to things that should have a workbench, i.e. vehicles and of course the workbench building.
 */
UCLASS( Blueprintable )
class FACTORYGAME_API UFGWorkBench : public USceneComponent, public IFGRecipeProducerInterface
{
	GENERATED_BODY()
public:
	UFGWorkBench();

	// Begin ActorComponent
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void TickComponent( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction ) override;
	// End ActorComponent

	void TickProducing( float dt );

	/** Set the active recipe to produce. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Workbench" )
	void SetRecipe( TSubclassOf< class UFGRecipe > recipe );

	/** Can we produce the given recipe, using the inventory passed for payment and output. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Workbench" )
	bool CanProduce( TSubclassOf< UFGRecipe > recipe, UFGInventoryComponent* inventory ) const;

	/** Checks if our owner has authority, and assumes that if they have, then so do we */
	bool HasAuthority() const;

	/** Are we currently producing. */
	UFUNCTION( BlueprintPure, BlueprintCallable, Category = "FactoryGame|Workbench" )
	bool IsProducing();

	/** Produce one step */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Workbench" )
	void Produce( float dt = 1.0f );

	/** Called when a craft have been completed. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Workbench" )
	void CraftComplete();

	/** Manufacturing progress in range [0,1]. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Workbench" )
	FORCEINLINE float GetManufacturingProgress(){ return mCurrentManufacturingProgress; }

	/** The recipe we're currently running. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Workbench" )
	FORCEINLINE TSubclassOf< class UFGRecipe > GetCurrentRecipe(){ return mCurrentRecipe; }

	/** Returns current workbench user */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Workbench" )
	FORCEINLINE class AFGCharacterPlayer* GetWorkBenchUser(){ return mPlayerWorkingAtBench; }

	/** sets current inventory we want */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Workbench" )
	void SetInventory( class UFGInventoryComponent* newInventory );

	/** @return The inventory for the player working at bench; nullptr if no one is working. */
	class UFGInventoryComponent* GetPlayerInventory() const;

	/** @return The inventory this workbench is set to work with */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Workbench" )
	class UFGInventoryComponent* GetInventory() const;

	/** sets current workbench user */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Workbench" )
	void SetWorkBenchUser( class AFGCharacterPlayer*  newUser );

	/** Called when we finish a product and wants to give it to the inventory passed */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Workbench" )
	void RemoveIngredientsAndAwardRewards( UFGInventoryComponent* inventory, TSubclassOf< class UFGRecipe > recipe );

	/** The speed of which we manufacture stuff */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Workbench" )
	FORCEINLINE float GetManufacturingSpeed() const { return mManufacturingSpeed; }

	/** Returns the player that is working at this workbench. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Workbench" )
	FORCEINLINE AFGCharacterPlayer* GetPlayerWorkingAtBench(){ return mPlayerWorkingAtBench; }

	/** Called when a craft has completed */
	void UpdateFatigueMultiplier( bool useLeftOvers = false );

	/** Returns how much worse the workbench is currently performing. 0.2 means it's 20% worse currently */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Workbench" )
	FORCEINLINE float GetCurrentFatigue() { return mCurrentFatigue; }

	/** Gets recipes duration. Including fatigue */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Workbench" )
	FORCEINLINE float GetCurrentDuration() { return mRecipeDuration * mCurrentFatigue; }

	/** Gets the active time we spent manufacturing */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Workbench" )
	FORCEINLINE float GetActiveManufacturingTime() { return mActiveManufacturingTime; }

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Workbench" )
	void SetupManufacturingButton( class UFGManufacturingButton* inButton );
private:
	/** A recipe should take longer to produce after you have produced a certain amount in a row */
	float GetRecipeFatigueMultiplier();
public:
	/** The recipe we're currently running. */
	UPROPERTY()
	TSubclassOf< class UFGRecipe > mCurrentRecipe;

	/** Manufacturing progress in range [0,1]. */
	UPROPERTY()
	float mCurrentManufacturingProgress;

	/** The speed of which this manufacturer manufactures stuff. Slower for Work Bench */
	UPROPERTY( EditDefaultsOnly, Category = "Workbench" )
	float mManufacturingSpeed;

private:
	UPROPERTY( Replicated )
	class AFGCharacterPlayer* mPlayerWorkingAtBench;

	/** Manufacturing rate in product per second. */
	UPROPERTY()
	float mRecipeRate;

	/** Are we producing? */
	UPROPERTY()
	bool mIsProducing;

	/** The inventory this workbench is set to work with */
	UPROPERTY()
	class UFGInventoryComponent* mInventory;

	/** Actual time spent producing ( holding button ) */
	float mActiveManufacturingTime;

	/** Work bench efficiency decrease per interval. 0.2 means 20% */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Workbench" )
	float mFatigueMultiplier;

	/** Fatigue we are currently at */
	float mCurrentFatigue;

	/** Multiplier for mFatigueUpdaterInterval, shows how long it takes to go down one step in fatigue */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Workbench" )
	float mFatigueDecreaseSpeedMultiplier;

	/** How long it takes to produce one cycle */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Workbench" )
	float mHoldProduceTime;

	UPROPERTY()
	class UFGManufacturingButton* mManufacturingButton;

	/** at what interval should the fatigue multiplier be applied? */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Workbench" )
	int32 mFatigueUpdaterInterval;

	/** Indicates how many times the fatigue has been multiplied */
	int32 mCounter;

	/** DUration it takes to make a recipe with added multipliers of manufacturingspeed and manufacturingmultiplier */
	UPROPERTY()
	float mRecipeDuration;

	/** How long to wait before applying cooldown */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Workbench" )
	float mCooldownDelay;

	float mCurrentCooldown;

	/** Should fatigue be used on this component */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Workbench" )
	bool mIsFatigueEnabled;

	/** Fatigue added based on how much of the fatigue interval we are currently in */
	float mAdditionalFatigue;

public:
	FORCEINLINE ~UFGWorkBench() = default;
};