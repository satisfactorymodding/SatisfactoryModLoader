
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
*
*/
UCLASS( Blueprintable )
class FACTORYGAME_API UFGWorkBench : public USceneComponent, public IFGRecipeProducerInterface
{
	GENERATED_BODY()
public: 
	/** Ctor */
	UFGWorkBench();
	
	/** Decide on what properties to replicate */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	
	/** Tick the workbench. */
	virtual void TickComponent( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction );

	void TickProducing( float dt );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Workbench" )
	void SetRecipe( TSubclassOf< class UFGRecipe > recipe );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Workbench" )
	bool CanProduce( TSubclassOf< UFGRecipe > recipe, UFGInventoryComponent* inventory ) const;

	/** Checks if our owner has authority, and assumes that if they have, then so do we */
	bool HasAuthority() const;

	UFUNCTION( BlueprintPure, BlueprintCallable, Category = "FactoryGame|Workbench" )
	bool IsProducing(); 

	/** Set the mIsPressingProduce */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Workbench" )
	void SetIsPressingProduce( bool isPressingProduce ); 

	/** Produce one step */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Workbench" )
	void Produce( float produceSpeed = 1.0f );

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

	/** The speed of wich we manufacture stuff */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Workbench" )
	FORCEINLINE float GetManufacturingSpeed() const { return mManufacturingSpeed; }

	/** Returns the player that is working at this workbench. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Workbench" )
	FORCEINLINE AFGCharacterPlayer* GetPlayerWorkingAtBench(){ return mPlayerWorkingAtBench; }

	/** Returns the player that is working at this workbench. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Workbench" )
	FORCEINLINE bool GetHoldToProduce(){ return mHoldToProduce; }

	/** Change holdToProduce status from blueprint */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Workbench" )
	void SetHoldToProduce( bool newHold ) { mHoldToProduce = newHold; }

	/** Returns the click speed for producing */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Workbench" )
	FORCEINLINE float GetProduceClickSpeed(){ return mProduceClickSpeed; }
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

	/** To keep track if we started producing this production cycle */	
	bool mDidProduceThisCycle;

	/** True if the player at the workbench is currently pressing produce/craft */
	bool mIsPressingProduce;

	/** The inventory this workbench is set to work with */
	UPROPERTY()
	class UFGInventoryComponent* mInventory;

	/** How much produce time a mouse click should represent */
	UPROPERTY( EditDefaultsOnly, Category = "Workbench" )
	float mProduceClickSpeed;

	/** Should we use hold to produce */
	UPROPERTY( EditDefaultsOnly, Category = "Workbench" )
	bool mHoldToProduce;
};