// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "../../Plugins/Wwise/Source/AkAudio/Classes/AkAudioEvent.h"
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "GameFramework/Actor.h"
#include "FGEquipment.h"
#include "FGEquipmentAttachment.h"
#include "FGWeapon.generated.h"


/**
 * Base class for a weapon in the game, this provides basic firing logic only and does not specify if it's a instant hit or projectile weapon.
 */
UCLASS()
class FACTORYGAME_API AFGWeapon : public AFGEquipment
{
	GENERATED_BODY()
	
public:
	/** Replication. */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	/** Ctor */
	AFGWeapon();

	// Begin AFGEquipment interface
	virtual bool ShouldSaveState() const override;
	// End

	/**
	* Put the weapon away.
	*/
	virtual void UnEquip();

	/**
	* bring up weapon and assign hud if local player
	*/
	virtual void Equip( class AFGCharacterPlayer* character ) override;

	/**to be called when equipping a weapon on a local player. Enabling weapons to affect the hud. */
	void AssignHud( AFGHUD * assoiatedHud = nullptr );

	/** Called on the owner, client or server but not both. */
	virtual void OnPrimaryFirePressed();

	/** Called by client to start fire on server. */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_StartPrimaryFire();

	/** Called on both client and server when firing. */
	virtual void BeginPrimaryFire();

	/** Called on the owner, client or server but not both. */
	virtual void OnPrimaryFireReleased();

	/** Called by client to start fire on server. */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_EndPrimaryFire();

	/** Called on both client and server when firing. */
	virtual void EndPrimaryFire();

	/** Called when reload button is pressed */
	void OnReloadPressed();

	/** Actual reload implementation */
	void Reload();

	/** Return true if we currently can reload with the weapon */
	UFUNCTION( BlueprintPure, Category = "Weapon" )
	bool CanReload() const;

	/** Returns -1 if not reloading, else, returns the time left on our reload */
	UFUNCTION( BlueprintPure, Category = "Weapon" )
	float GetReloadTimeLeft() const;

	/** Returns true if we have ammunition loaded */
	UFUNCTION( BlueprintPure, Category = "Weapon" )
	bool HasAmmunition() const;

	/** How much ammunition do our owner have in their inventory */
	UFUNCTION( BlueprintPure, Category = "Weapon" )
	int32 GetSpareAmmunition() const;

	/** Checks what type of fire modes and call corresponding fire function */
	UFUNCTION( BlueprintNativeEvent, Category = "Weapon" )
	void FireAmmunition();

	virtual void FireAmmunition_Implementation();

	/** Returns whether we are reloading or not */
	UFUNCTION( BlueprintPure, Category = "Weapon" )
	FORCEINLINE bool GetIsReloading() const { return mIsReloading; }

	/** Returns how much ammo we have in current clip */
	UFUNCTION( BlueprintPure, Category = "Weapon" )
	FORCEINLINE int32 GetCurrentAmmo() { return mCurrentAmmo; }

	/** Returns mIsFiring */
	UFUNCTION( BlueprintPure, Category = "Weapon" )
	FORCEINLINE bool GetIsFiring() const { return mIsFiring; }

	/** Returns mMagSize */
	UFUNCTION( BlueprintPure, Category = "Weapon" )
	FORCEINLINE int32 GetMagSize() const { return mMagSize; }

	/** Called when you tried to fire and CanFire returned false. You will have to check the reason yourself and play effects accordingly */
	UFUNCTION( BlueprintImplementableEvent, Category = "Projectile" )
	void PlayFailedToFireEffects();

	/** Called when the player releases the primary fire so that special animations can be triggered from this. The neccesity is rare, use PlayFireEffect() in most cases */
	UFUNCTION( BlueprintImplementableEvent, Category = "Weapon" )
	void PlayFireReleasedEffects();

protected:
	// Begin AFGEquipment interface
	virtual void AddEquipmentActionBindings();
	// End AFGEquipment interface

	/** Try to refire */
	void RefireCheckTimer();

	/** Handles playing of effects both on server and on client. */
	UFUNCTION( BlueprintNativeEvent, Category = "Weapon" )
	void PlayFireEffect();

	/** Consumes our current ammo */
	void ConsumeAmmunition();

	/** Return true if we can fire */
	bool CanFire() const;

	/** When we "actually" has reloaded (reload logic goes here), need to be UFUNCTION as it used as a delegate */
	UFUNCTION()
	void ActualReload();

	UFUNCTION( BlueprintNativeEvent, Category = "Weapon" )
	void PlayReloadEffects();

	/** Client tells server to reload */
	UFUNCTION( Server, Unreliable, WithValidation )
	void Server_Reload();

	/** Ability for different classes to get ammo from different places */
	virtual class UFGInventoryComponent* GetOwnersInventoryComponent() const;

	/** Returns the assosiated hud object if there is one assigned */
	UFUNCTION( BlueprintPure, Category = "Hud" )
	FORCEINLINE AFGHUD* GetAssosiatedHud() const { return mAssosiatedHud; }

protected:
	UPROPERTY()
	AFGHUD* mAssosiatedHud = nullptr; //[DavalliusA:Wed/20-03-2019] the base hud object will never get invalid during use, so we can use anormal pointer here to access it.

	/** Refire timer */
	FTimerHandle mRefireCheckHandle;

	/** Reload timer */
	FTimerHandle mReloadHandle;

	/** How much ammo does a magazine cover */
	UPROPERTY( EditDefaultsOnly )
	int32 mMagSize;

	/** How much ammo is loaded into the weapon */
	UPROPERTY( SaveGame, Replicated )
	int32 mCurrentAmmo;

	/** The item we shoot */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TSubclassOf< class UFGItemDescriptor > mAmmunitionClass;

	/** Damage type to use when hitting others */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TSubclassOf< class UFGDamageType > mDamageTypeClass;

	/** In seconds, how long time does it take to reload the weapon */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	float mReloadTime;

	/** How many seconds between between shots */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	float mFireRate;
	
	/** Are we firing? */
	UPROPERTY( BlueprintReadOnly, meta = (NoAutoJson = true) )
	bool mIsFiring;

	/** The player wants to shoot */
	UPROPERTY( BlueprintReadOnly, meta = (NoAutoJson = true) )
	bool mIsPendingFire;

	/** True if we are currently reloading */
	UPROPERTY( meta = (NoAutoJson = true) )
	bool mIsReloading;

	/** Sound played when reloading */
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Sound" )
	UAkAudioEvent* mReloadSound;

	/** A cast reference to the spawned child equipment, if it exists*/
	class AFGWeaponChild* mChildWeapon;


public:
	FORCEINLINE ~AFGWeapon() = default;
};



