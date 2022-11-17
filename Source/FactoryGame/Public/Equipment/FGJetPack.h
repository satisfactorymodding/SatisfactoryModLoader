// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "FactoryGame.h"
#include "Equipment/FGEquipment.h"
#include "Equipment/FGEquipmentAttachment.h"
#include "FGJetPack.generated.h"

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
	
	/** Player pressed thrust */
	void JetPackThrust();
	/** Player released thrust */
	void JetPackStopThrust();
	
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
	
	virtual void Equip( class AFGCharacterPlayer* character ) override;
	virtual void UnEquip() override;
	
private:
	/** This function checks if the JetPack can thrust. */
	bool CanThrust() const;
	
	/** Used to report a noise event for when the jetpack is active. */
	void MakeActiveNoise();

	bool CheckCurrentAvailableFuel();

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

	/** */
	UPROPERTY( BlueprintReadOnly, SaveGame, Replicated, Category = "JetPack" )
	int mSelectedFuelType = 0;
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
	
	FTimerHandle mActiveNoiseTimerHandle;

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
