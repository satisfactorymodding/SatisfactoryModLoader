// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGEquipment.h"
#include "FGJetPack.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnFuelAmountChanged, int32, newFuelAmount );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnBurnPercentChanged, float, newBurnPercent );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnFuelTypeChanged, int32, newFuelIndex );

/** Item state struct for the jetpack */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FFGJetPackItemState
{
	GENERATED_BODY()

	/** The current amount of fuel in the JetPack. */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, SaveGame, Category = "ItemState|JetPack" )
	float CurrentFuel{};

	/** The actual fuel type currently being used. Can be different from mSelectedFuelType if the player can not afford it. */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, SaveGame, Category = "ItemState|JetPack" )
	int32 CurrentFuelType{};

	/** The fuel type selected to be default by the player. */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, SaveGame, Category = "ItemState|JetPack" )
	int32 SelectedFuelType{};
};

UCLASS()
class FACTORYGAME_API AFGJetPack final : public AFGEquipment
{
	GENERATED_BODY()
public:
	AFGJetPack();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void Tick( const float deltaTime ) override;
	// End AActor interface

	// Begin AFGEquipment interface
	virtual void LoadFromItemState_Implementation(const FFGDynamicStruct& itemState) override;
	virtual FFGDynamicStruct SaveToItemState_Implementation() const override;
	virtual void DisableEquipment() override;
	virtual void AddEquipmentActionBindings() override;
	virtual void Equip( AFGCharacterPlayer* character ) override;
	virtual void UnEquip() override;
	virtual void GetSupportedConsumableTypes(TArray<TSubclassOf< UFGItemDescriptor >>& out_itemDescriptors) const override;
	virtual TSubclassOf<UFGItemDescriptor> GetSelectedConsumableType() const override;
	virtual void SetSelectedConsumableType(const TSubclassOf<UFGItemDescriptor> selectedConsumableType) override;
	// End AFGEquipment interface
	
	/** Returns true if we are currently thrusting, false otherwise */
	UFUNCTION( BlueprintPure, Category = "JetPack" )
	FORCEINLINE bool IsThrusting() const { return mIsThrusting; }

	/** Returns the current fuel type */
	UFUNCTION( BlueprintPure, Category = "JetPack" )
	FORCEINLINE int32 GetCurrentFuelType() const { return mCurrentFuelType; }

	/** Returns the selected fuel type */
	UFUNCTION( BlueprintPure, Category = "JetPack" )
	FORCEINLINE int32 GetSelectedFuelType() const { return mSelectedFuelType; }

	/** This function calculates our new velocity when we are thrusting. */
	void CalculateVelocityWhenThrusting( FVector& ref_velocity, float deltaTime ) const;
	
	/** Calculate our boosted air control when jetpack is equipped*/
	float BoostAirControl( float deltaTime, float tickAirControl, const FVector& fallAcceleration ) const;

	/** Updates whenever the jetpack is currently thrusting */
	void SetIsThrusting( bool newIsThrusting );
protected:

	UFUNCTION( Server, Reliable )
	void Server_SetIsThrusting( bool newIsThrusting );
	
	void ConsumeFuel( float delta );
	void RegenerateFuel( const float delta );
	
	/** Called when we start thrusting */
	UFUNCTION( BlueprintImplementableEvent )
	void OnStartThrusting();
	
	/** Called when we stop thrusting */
	UFUNCTION( BlueprintImplementableEvent )
	void OnStopThrusting();

	/** Input Actions */
	void Input_Thrust( const FInputActionValue& actionValue );

	/** Updates the current fuel type, the cost, and triggers the relevant delegates */
	void SetCurrentFuelType( int32 newCurrentFuelType, bool bForce = false );

	/** Updates the desired fuel type for the jet pack */
	void SetSelectedFuelType( int32 newSelectedFuelType );

	/** Updates the current amount of fuel */
	void SetCurrentFuel( float newCurrentFuel );

	/** Updates the selected fuel type on the server */
	UFUNCTION( Server, Reliable )
	void Server_SetSelectedFuelType( int32 newSelectedFuelType );

	void UpdateThrustingNoiseTimer();

	/** @return true if jetpack can thrust currently, false otherwise  */
	bool CheckCanThrust() const;

	/** Attempts to pick the first available fuel type from the inventory, preferring the user selected one*/
	void PickPreferredFuelTypeFromInventory( bool bForce = false );
	int32 FindPreferredFuelTypeFromInventory();
	bool HasEnoughFuelInInventory( TSubclassOf<UFGItemDescriptor> itemClass ) const;

	/** Updates the amount of the current fuel type and fires the delegate if it changes */
	void UpdateCurrentFuelAmount();

	void SubscribeToRecipeManagerUpdates();
	void UpdateUnlockedFuelTypes();

	UFUNCTION()
	void OnRecipeUnlocked( TSubclassOf<class UFGRecipe> recipeClass );

	/** Called from delegates when the players inventory changes. Here for UI purposes. */
	UFUNCTION()
	void OnInventoryChanged( TSubclassOf< UFGItemDescriptor > itemClass, int32 numAdded, UFGInventoryComponent* targetInventory = nullptr );

	UFUNCTION()
	void OnRep_CurrentFuelType();

	UFUNCTION()
	void OnRep_IsThrusting();

	UFUNCTION()
	void OnRep_CurrentFuel();

	void UpdateAvailableFuelTypes();
public:
	/** Called when the amount of the selected fuel type in the players inventory changes. */
	UPROPERTY( BlueprintAssignable )
	FOnFuelAmountChanged mOnFuelAmountChanged;
	
	/** Called when the amount of fuel in the JetPack changes. */
	UPROPERTY( BlueprintAssignable )
	FOnBurnPercentChanged mOnBurnPercentChanged;

	/** Called when active fuel type changes. */
	UPROPERTY( BlueprintAssignable )
	FOnFuelTypeChanged mOnFuelTypeChanged;
	
protected:
	/** Default air control, used while not thrusting. */
	UPROPERTY( BlueprintReadWrite )
	float mDefaultAirControl;
	/**  */
	UPROPERTY( BlueprintReadWrite )
	float mRTPCInterval;
	
	/** Amount of time that is left before we can thrust again */
	float mThrustCooldown;
	
	/** The current amount of fuel in the JetPack. */
	UPROPERTY( VisibleInstanceOnly, BlueprintReadOnly, ReplicatedUsing = OnRep_CurrentFuel, SaveGame )
	float mCurrentFuel;
	
	/** If we are actually thrusting or not */
	UPROPERTY( VisibleInstanceOnly, BlueprintReadOnly, ReplicatedUsing = OnRep_IsThrusting )
	bool mIsThrusting;

	/** Array of Fuel Parameters that give stats to the JetPack. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "JetPack" )
	TArray<class UFGJetPackFuelParameters*> mAllowedFuelTypes;

	/** The fuel type selected to be default by the player. */
	UPROPERTY( BlueprintReadOnly, SaveGame, Replicated, Category = "JetPack" )
	int32 mSelectedFuelType{0};

	/** The actual fuel type currently being used. Can be different from mSelectedFuelType if the player can not afford it. */
	UPROPERTY( BlueprintReadOnly, SaveGame, ReplicatedUsing = OnRep_CurrentFuelType, Category = "JetPack" )
	int32 mCurrentFuelType{0};

	/** Fuel types that have actually been unlocked according to the recipe manager */
	UPROPERTY()
	TArray< TSubclassOf<UFGItemDescriptor> > mUnlockedFuelTypes;

	/** Fuel types that we can use because we have them in our inventory */
	UPROPERTY()
	TArray< TSubclassOf<UFGItemDescriptor> > mAvailableFuelTypes;
private:
	/** How much fuel that has been paid for. */
	float mPaidForFuel;
	/** The duration we've held down thrust this flight, only resets when Landed. */
	float mJumpTimeStamp;
	/** The player is holding down the thrust key and wants to thrust */
	bool mWantsToThrust;
	/** cached value indicating whenever we can currently thrust or not */
	bool mCachedCanTrust;
	/** The currently cached fuel amount */
	int32 mCurrentFuelAmount;

	/** The noise to make when the jetpack is active. */
	UPROPERTY( EditDefaultsOnly, Category = "JetPack" )
	TSubclassOf< class UFGNoise > mActiveNoise;
	
	/** How often to make the noise (in seconds) while the jetpack is active. */
	UPROPERTY( EditDefaultsOnly, Category = "JetPack" )
	float mActiveNoiseFrequency = 0.2f;
};
