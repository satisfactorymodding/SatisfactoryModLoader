// Copyright 2016-2021 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "GameFramework/Actor.h"
#include "Equipment/FGEquipment.h"
#include "Equipment/FGAmmoType.h"

#include "Equipment/FGWeaponState.h"

#include "FGWeapon.generated.h"

class AFGHUD;

extern TAutoConsoleVariable< int32 > CVarWeaponDebug;

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FAmmoSwitchingDelegate );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FWeaponStateChangedDelegate, EWeaponState, oldState, EWeaponState, newState );

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
	virtual bool ReplicateSubobjects( class UActorChannel* channel, class FOutBunch* bunch, FReplicationFlags* repFlags ) override;

	AFGWeapon();

	virtual void Tick( float DeltaSeconds ) override;

	// Begin AFGEquipment interface
	virtual bool ShouldSaveState() const override;
	bool InitializeMagazineObject();

	/**
	 * Put the weapon away.
	 */
	virtual void UnEquip() override;

	/**
	 * bring up weapon and assign hud if local player
	 */
	virtual void Equip( class AFGCharacterPlayer* character ) override;

	UFUNCTION(BlueprintPure, Category="Weapon")
	FORCEINLINE EWeaponState GetWeaponState() const { return mWeaponState; }

	/**to be called when equipping a weapon on a local player. Enabling weapons to affect the hud. */
	void AssignHud( AFGHUD* associatedHud = nullptr );

	/** Called on the owner, client or server but not both. */
	virtual void OnPrimaryFirePressed();

	/** Called by client to start fire on server. */
	UFUNCTION( Server, Reliable )
	void Server_StartPrimaryFire();

	/** Called on both client and server when firing. */
	UFUNCTION( NetMulticast, Reliable )
	void Multicast_BeginPrimaryFire();

	/** Called on the owner, client or server but not both. */
	virtual void OnPrimaryFireReleased();

	/** Called by client to start fire on server. */
	UFUNCTION( Server, Reliable )
	void Server_EndPrimaryFire();

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_EndPrimaryFire();

	/** Called on both client and server when firing. */
	virtual void EndPrimaryFire();

	/** Called when reload button is pressed */
	void OnReloadPressed();

	/** Actual reload implementation */
	UFUNCTION(NetMulticast, Reliable)
	void Multicast_Reload();

	/** Return true if we currently can reload with the weapon */
	UFUNCTION( BlueprintPure, Category = "Weapon" )
	bool CanReload() const;

	/** Returns -1 if not reloading, else, returns the time left on our reload */
	UFUNCTION( BlueprintPure, Category = "Weapon" )
	float GetReloadTimeLeft() const;

	/** Implementable event to do things when the current ammo type has changed */
	UFUNCTION( BlueprintImplementableEvent, Category="Weapon" )
	void OnCurrentAmmoTypeChanged( UFGAmmoType* AmmoType );

	/** Will return the location of the specified socket on the weapon mesh. Will use weapon mesh if locally controlled, otherwise it will grab the socket on the attachment mesh. */
	UFUNCTION( BlueprintPure, BlueprintNativeEvent, Category = "Weapon" )
	FVector GetWeaponMeshSocketLocation( FName socketName ) const;

	/** When the CycleAmmunition action is triggered */
	void OnCycleAmmunitionTypePressed();

	/** When the CycleAmmunition action is released */
	void OnCycleAmmunitionTypeReleased();

	UFUNCTION( Server, Reliable )
	void Server_CycleDesiredAmmunitionType();

	/** Does the actual ammo type cycling */
	void CycleDesiredAmmunitionType();

	UFUNCTION(BlueprintCallable, Server, Reliable, Category="Weapon")
	void Server_SetDesiredAmmoClass( TSubclassOf< UFGAmmoType > newDesiredAmmoClass );

	UFUNCTION( BlueprintCallable, Category="Weapon" )
	void SetDesiredAmmoClass( TSubclassOf< UFGAmmoType > newDesiredAmmoClass );

	/** Returns true if we have ammunition loaded */
	UFUNCTION( BlueprintPure, Category = "Weapon" )
	bool HasAmmunition() const;

	/** How much ammunition do our owner have in their inventory */
	UFUNCTION( BlueprintPure, Category = "Weapon" )
	int32 GetSpareAmmunition( TSubclassOf< UFGAmmoType > AmmunitionType ) const;

	void ApplyDispersion();
	
	/** Called on server, will call FireAmmunition on the ammo. */
	void FireAmmunition();

	/** Returns whether we are reloading or not */
	UFUNCTION( BlueprintPure, Category = "Weapon" )
	FORCEINLINE bool GetIsReloading() const { return mWeaponState == EWeaponState::EWS_Reloading; }

	/** Returns if that weapon will automatically reload when the magazine is empty */
	UFUNCTION( BlueprintPure, Category = "Weapon" )
	FORCEINLINE bool GetIsAutomaticallyReloading() const { return mAutomaticallyReload; }

	/** Returns the delay between the firing and the auto-reload. */
	UFUNCTION( BlueprintPure, Category = "Weapon" )
	FORCEINLINE float GetAutoReloadDelay() const { return mAutoReloadDelay; }

	/** Returns how much ammo we have in current clip */
	UFUNCTION( BlueprintPure, Category = "Weapon" )
	FORCEINLINE int32 GetCurrentAmmo() const { return mCurrentAmmoCount; }

	/** Returns mIsFiring */
	UFUNCTION( BlueprintPure, Category = "Weapon" )
	FORCEINLINE bool GetIsFiring() const { return mWeaponState == EWeaponState::EWS_Firing; }

	/** Returns the weapon's base damage multiplier */
	UFUNCTION( BlueprintPure, Category= "Weapon" )
	FORCEINLINE float GetWeaponDamageMultiplier() const { return mWeaponDamageMultiplier; }

	UFUNCTION( BlueprintPure, Category="Weapon" )
	FORCEINLINE float GetWeaponCurrentDispersion() const { return mCurrentDispersion; }

	/** Gets a 0-1 value representing the current dispersion between resting and firing level. */
	UFUNCTION( BlueprintPure, Category = "Weapon" )
	float GetNormalizedDispersionValue() const;

	/** Returns mMagSize */
	UFUNCTION( BlueprintPure, Category = "Weapon" )
	FORCEINLINE int32 GetMagSize() const
	{
		return IsValid( mCurrentAmmunitionClass ) ? mCurrentAmmunitionClass.GetDefaultObject()->GetMagazineSize() : -1;
	}

	/** Returns an object with all the of the current ammo type's values */
	UFUNCTION( BlueprintPure, Category= "Weapon" )
	FORCEINLINE UFGAmmoType* GetAmmoTypeDescriptor() const { return mCurrentMagazineObject; }

	UFUNCTION( BlueprintPure, Category="Weapon" )
	static FORCEINLINE UFGAmmoType* GetDefaultObjectForAmmoType( TSubclassOf< UFGAmmoType > ammoType )
	{
		return ammoType.GetDefaultObject();
	}

	/** Called when you tried to fire and CanFire returned false. You will have to check the reason yourself and play effects accordingly */
	UFUNCTION( BlueprintImplementableEvent, Category = "Projectile" )
	void PlayFailedToFireEffects();

	/** Called when the player releases the primary fire so that special animations can be triggered from this. The neccesity is rare, use PlayFireEffect() in most cases */
	UFUNCTION( BlueprintImplementableEvent, Category = "Weapon" )
	void PlayFireReleasedEffects();

	/** Called by the server in order to play fire effects on the clients. */
	UFUNCTION( NetMulticast, Reliable )
	void Multicast_PlayFireEffect( UFGAmmoType* AmmoTypeObject );

	/** Handles playing of effects both on server and on client. */
	UFUNCTION( BlueprintNativeEvent, Category = "Weapon" )
	void PlayFireEffect( UFGAmmoType* AmmoTypeObject );

	/** Is sprinting allowed when firing this weapon */
	FORCEINLINE virtual bool ShouldBlockSprintWhenFiring() { return mBlockSprintWhenFiring; }

	/** Returns the assosiated hud object if there is one assigned */
	UFUNCTION( BlueprintPure, Category = "Hud" )
	FORCEINLINE AFGHUD* GetAssociatedHud() const { return mAssociatedHud; }

public:
	UPROPERTY( BlueprintAssignable )
	FWeaponStateChangedDelegate mOnWeaponStateChanged;

protected:
	// Begin AFGEquipment interface
	virtual void AddEquipmentActionBindings() override;
	// End AFGEquipment interface

	void SetWeaponState(EWeaponState newState);

	virtual void UpdateDispersion( float DeltaSeconds );

	void SetMagazineMeshMaterials(USkeletalMeshComponent* skelMeshComp, UFGAmmoType* ammoTypeObject);

	/** Try to refire */
	void RefireCheckTimer();

	/** Consumes our current ammo */
	void ConsumeAmmunition();

	/** Return true if we can fire */
	bool CanFire() const;

	/** When we "actually" has reloaded (reload logic goes here), need to be UFUNCTION as it used as a delegate */
	UFUNCTION()
	void ActualReload();

	UFUNCTION( BlueprintNativeEvent, Category = "Weapon" )
	void PlayReloadEffects( bool hadAmmoLeft );

	/** Client tells server to reload */
	UFUNCTION( Server, Reliable )
	void Server_Reload();

	/** Try to auto-reload, if conditions are met */
	UFUNCTION()
	void TryAutoReload();

	UFUNCTION(BlueprintPure, Category="Weapon")
	bool GetFireRate( float& fireRate );

	UFUNCTION()
	void TriggerRefireTimer();

	/** Ability for different classes to get ammo from different places */
	virtual class UFGInventoryComponent* GetOwnersInventoryComponent() const;

	/** Delegate. Broadcasted by the current ammo type object when an ammo is fired.
	 * Used to react and do what needs to be done post-firing. */
	UFUNCTION()
	virtual void OnAmmoFired( AActor* SpawnedActor );
	
	UFUNCTION()
	void OnRep_CurrentMagazineObject( class UFGAmmoType* oldMagazineObject );

	UFUNCTION()
	void OnRep_WeaponState( EWeaponState oldState );

	UFUNCTION()
	void OnRep_CurrentAmmoCount();

	virtual void OnRep_Instigator() override;

	UPROPERTY()
	AFGHUD* mAssociatedHud = nullptr;
	//[DavalliusA:Wed/20-03-2019] the base hud object will never get invalid during use, so we can use anormal pointer here to access it.

	/** Refire timer */
	FTimerHandle mRefireCheckHandle;

	bool mPrimaryFireHold;

	/** Multicast_Reload timer */
	FTimerHandle mReloadHandle;

	/** State the weapon is in. Never set this manually. Always use SetWeaponState */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_WeaponState )
	EWeaponState mWeaponState;

	/** Does this weapon automatically reload when the magazine is empty and there are ammo available? */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	bool mAutomaticallyReload = false;

	/** Delay that's added between the time the ammo is fired and the auto-reload starts to account for animations. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	float mAutoReloadDelay = 0.5f;

	/** Timer handler to know whether an auto-reload is planned. */
	UPROPERTY()
	FTimerHandle mAutoReloadTimerHandle;

	/** How much ammo is loaded into the weapon */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_CurrentAmmoCount )
	int32 mCurrentAmmoCount;

	/** Ammo classes this weapons allows to switch between */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	TArray< TSubclassOf< class UFGAmmoType > > mAllowedAmmoClasses;

	/** The ammo class that we want to use upon next reload */
	UPROPERTY( BlueprintReadOnly, SaveGame, Replicated )
	TSubclassOf< class UFGAmmoType > mDesiredAmmoClass;

	/** The item we shoot */
	UPROPERTY( BlueprintReadOnly, SaveGame, Replicated )
	TSubclassOf< class UFGAmmoType > mCurrentAmmunitionClass;

	/** Attaches the mesh to a bone of the mesh character 1P/3P instead of the weapon. */
	UPROPERTY( EditDefaultsOnly )
	bool mAttachMagazineToPlayer = false;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	FName mMuzzleSocketName;
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	FName mCurrentMagazineBoneName;

	/** Reference to the weapon's mesh. Set it in construction script of BP. */
	UPROPERTY( BlueprintReadWrite)
	USkeletalMeshComponent* mWeaponMesh;
	
	UPROPERTY( BlueprintReadOnly )
	USkeletalMeshComponent* mCurrentMagazineMesh;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly )
	FName mEjectMagazineBoneName;

	UPROPERTY( BlueprintReadOnly )
	USkeletalMeshComponent* mEjectMagazineMesh;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Stats" )
	float mDispersionOnNoMagazine = 5.0f;
	
	/** Multiplier applied to ammo damages */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Stats" )
	float mWeaponDamageMultiplier = 1.0f;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Stats" )
	bool mFiringBlocksDispersionReduction = false;

	/** Current dispersion in degrees */
	UPROPERTY( BlueprintReadOnly, Category = "Stats" )
	float mCurrentDispersion;

	/** In seconds, how long time does it take to reload the weapon */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Stats" )
	float mReloadTime;

	/** Sound played when reloading */
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Sound" )
	UAkAudioEvent* mReloadSound;

	/** Object created from the ammo class, required to call ammo types functionalities */
	UPROPERTY( ReplicatedUsing = OnRep_CurrentMagazineObject )
	UFGAmmoType* mCurrentMagazineObject;

	UPROPERTY( BlueprintReadWrite, Category = "AmmoSwitching" )
	bool mAmmoSwitchUsedRadialMenu = false;

	UPROPERTY( BlueprintAssignable )
	FAmmoSwitchingDelegate mOnAmmoCyclingPressed;

	UPROPERTY( BlueprintAssignable )
	FAmmoSwitchingDelegate mOnAmmoCyclingReleased;

private:
	/** Indicates if this weapon will block character from sprinting when fired */
	UPROPERTY( EditDefaultsOnly )
	bool mBlockSprintWhenFiring;
};
