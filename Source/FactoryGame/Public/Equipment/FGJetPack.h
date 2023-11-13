// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "FactoryGame.h"
#include "FGEquipment.h"
#include "FGEquipmentAttachment.h"
#include "FGJetPack.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnFuelAmountChanged, const int, newFuelAmount );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnBurnPercentChanged, const float, newBurnPercent );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnFuelTypeChanged, const int, newFuelIndex );

UCLASS()
class FACTORYGAME_API AFGJetPack final : public AFGEquipment
{
	GENERATED_BODY()
public:
	/** You know what this is */
	AFGJetPack();
	virtual void Tick( const float deltaTime ) override;

	// Begin AFGEquipment interface
	virtual bool ShouldSaveState() const override;
	virtual void DisableEquipment() override;
	// End AFGEquipment interface

	void SetIsThrusting( const bool newIsThrusting );
	FORCEINLINE bool GetIsThrusting() const { return mIsThrusting; }

	/** This function calculates our new velocity when we are thrusting. */
	float GetNewVelocityWhenThrusting( const float delta ) const;
	
	virtual void GetSupportedConsumableTypes(TArray<TSubclassOf< UFGItemDescriptor >>& out_itemDescriptors) const override;
	virtual int GetSelectedConsumableTypeIndex() const override;
	virtual void SetSelectedConsumableTypeIndex( const int selectedIndex ) override;

protected:
	/** @copydoc AFGEquipment::AddEquipmentActionBindings */
	virtual void AddEquipmentActionBindings() override;

	/** Replication. */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	
	UFUNCTION( BlueprintCallable )
	void ConsumeFuel( const float delta );
	UFUNCTION( BlueprintCallable )
	void RegenerateFuel( const float delta );
	
	/** Called when we start thrusting */
	UFUNCTION( BlueprintImplementableEvent )
	void OnStartThrusting();
	/** Called when we stop thrusting */
	UFUNCTION( BlueprintImplementableEvent )
	void OnStopThrusting();
	
	virtual void Equip( AFGCharacterPlayer* character ) override;
	virtual void UnEquip() override;

	/** Input Actions */
	void Input_Thrust( const FInputActionValue& actionValue );

	UFUNCTION()
	void ConsumableTypeIndexChanged_OnRep();
	
	/** Called when the amount of the selected fuel type in the players inventory changes. */
	UPROPERTY( BlueprintAssignable )
	FOnFuelAmountChanged mOnFuelAmountChanged;
	
	/** Called when the amount of fuel in the JetPack changes. */
	UPROPERTY( BlueprintAssignable )
	FOnBurnPercentChanged mOnBurnPercentChanged;

	/** Called when active fuel type changes. */
	UPROPERTY( BlueprintAssignable )
	FOnFuelTypeChanged mOnFuelTypeChanged;

private:
	/** This function checks if the JetPack can thrust. */
	bool CanThrust() const;
	
	/** Used to report a noise event for when the jetpack is active. */
	void MakeActiveNoise();

	bool CheckCurrentAvailableFuel();

	/** Called from delegates when the players inventory changes. Here for UI purposes. */
	UFUNCTION()
	void OnInventoryChanged( TSubclassOf< UFGItemDescriptor > itemClass, int32 numAdded );
	
protected:
	/** Default air control, used while not thrusting. */
	UPROPERTY( BlueprintReadWrite )
	float mDefaultAirControl;
	/**  */
	UPROPERTY( BlueprintReadWrite )
	float mRTPCInterval;
	
	/** */
	UPROPERTY( BlueprintReadWrite )
	float mThrustCooldown;
	/** The current amount of fuel in the JetPack. */
	UPROPERTY( VisibleInstanceOnly, BlueprintReadOnly, SaveGame, Replicated )
	float mCurrentFuel;
	/** If we are actually thrusting or not */
	UPROPERTY( VisibleInstanceOnly, BlueprintReadOnly )
	bool mIsThrusting;
	
	/** Array of Fuel Parameters that give stats to the JetPack. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "JetPack" )
	TArray<TSubclassOf< class UFGJetPackFuelParameters >> mFuelTypes;

	/** The fuel type selected to be default by the player. */
	UPROPERTY( BlueprintReadOnly, SaveGame, replicatedUsing=ConsumableTypeIndexChanged_OnRep, Category = "JetPack" )
	int mSelectedFuelType = 0;
	/** The actual fuel type currently being used. Can be different from mSelectedFuelType if the player can not afford it. */
	UPROPERTY( BlueprintReadOnly, SaveGame, Replicated, Category = "JetPack" )
	int mCurrentFuelType = 0;
	
private:
	/** How much fuel that has been paid for. */
	float mPaidForFuel;
	/** The duration we've held down thrust this flight, only resets when Landed. */
	float mJumpTimeStamp;
	/** The player is holding down the thrust key and wants to thrust */
	bool mWantsToThrust;
	/** A cached instance of the instigators MovementComponent */
	UPROPERTY()
	class UFGCharacterMovementComponent* mCachedMovementComponent;

	class UFGInventoryComponent* mCachedInventoryComponent;
	
	FTimerHandle mActiveNoiseTimerHandle;

	int mCurrentFuelAmount;

	/** The noise to make when the jetpack is active. */
	UPROPERTY( EditDefaultsOnly, Category = "JetPack" )
	TSubclassOf< class UFGNoise > mActiveNoise;
	
	/** How often to make the noise (in seconds) while the jetpack is active. */
	UPROPERTY( EditDefaultsOnly, Category = "JetPack" )
	float mActiveNoiseFrequency = 0.2f;
	
};

UCLASS()
class FACTORYGAME_API AFGJetPackAttachment final : public AFGEquipmentAttachment
{
	GENERATED_BODY()
public:
	/** Replication. */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	/** Called when mIsThrusting is replicated */
	UFUNCTION()
	void OnRep_IsThrusting();

	/** Called when we start thrusting */
	UFUNCTION( BlueprintImplementableEvent )
	void OnStartThrusting();

	/** Called when we stop thrusting */
	UFUNCTION( BlueprintImplementableEvent )
	void OnStopThrusting();

	/** Simple set */
	void SetIsThrusting( const bool newIsThrusting );

protected:
	UPROPERTY( ReplicatedUsing = OnRep_IsThrusting )
	bool mIsThrusting;

};
