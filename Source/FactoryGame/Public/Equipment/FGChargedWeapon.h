// Copyright 2016-2021 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"

#include "FGDestructiveProjectile.h"
#include "Equipment/FGWeapon.h"
#include "FGChargedWeapon.generated.h"

/**
 * Class for weapons requiring a charge & throw logic (i.e snowballs/Nobelisk)
 * Inherits: FGWeapon
 */
UCLASS()
class FACTORYGAME_API AFGChargedWeapon : public AFGWeapon
{
	GENERATED_BODY()

public:
	AFGChargedWeapon();

	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	// Begin AFGEquipment interface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual bool ShouldSaveState() const override;
	// End

	/** Called on both client and server */
	virtual void BeginPrimaryFire() override;

	/** Called on both client and server */
	virtual void EndPrimaryFire() override;

	/** Equip / UnEquip */
	virtual void Equip( class AFGCharacterPlayer* character ) override;
	virtual void UnEquip() override;

	/** Return the current charge in percent */
	UFUNCTION( BlueprintPure, Category = "ChargedWeapon" )
	float GetChargePct() const;

protected:
	/** Executes on Server, Spawns and throws out a charged projectile*/
	void SpawnChargedProjectile( FTransform spawnTransform, int32 throwForce );

	/** Called from client to Spawn Explosive on server */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_SpawnChargedProjectile( FTransform spawnTransform, int32 throwForce );

	/** Called by Client or Server, sets the lifetime on charged projectiles so they expire after a certain time */
	void StartChargedProjectileSecondary();

	UFUNCTION( Server, Reliable )
	void Server_StartChargedProjectileSecondary();

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_PrimaryFireStarted();

	UFUNCTION( BlueprintNativeEvent, Category = "ChargedWeapon" )
	void OnPrimaryFireStarted();

	UFUNCTION( BlueprintNativeEvent, Category = "ChargedWeapon" )
	void OnPrimaryFireEnded();

	/** Called by an anim notify to actually trigger the spawn of the projectile*/
	UFUNCTION( BlueprintCallable, Category = "ChargedWeapon" )
	void ExecutePrimaryFire( FVector spawnLocation );

	/** Called by client to start throw on server. */
	UFUNCTION( Server, Reliable )
	void Server_ExecutePrimaryFire( FVector spawnLocation );

	UFUNCTION( NetMulticast, Reliable )
	void Multicast_ResetPressTimestamp();

	/** Called when the player presses secondary fire */
	void SecondaryFirePressed();

	/** Call animation from blueprint that will contain notify to trigger actual projectile secondary*/
	UFUNCTION( BlueprintNativeEvent, Category = "ChargedWeapon" )
	void OnSecondaryFirePressed();

	/** Called by an anim notify to actually trigger the projectile's secondary sequence*/
	UFUNCTION( BlueprintCallable, Category = "ChargedWeapon" )
	void ExecuteSecondaryFire();

	/** Called by client to start fire on server. */
	UFUNCTION( Server, Reliable )
	void Server_ExecuteSecondaryFire();

	/** Called from Hotbar status change, to indicate we have change SceneViewport Focus */
	UFUNCTION()
	void OnViewportFocusChanged( bool isOpen, TSubclassOf< class UUserWidget > interactionClass );

	// Begin AFGEquipment interface
	virtual void AddEquipmentActionBindings() override;
	// End AFGEquipment interface

	virtual void ApplyDispersionReduction( float DeltaSeconds ) override;

	virtual void OnAmmoFired( AActor* SpawnedActor ) override;

	/** Keeps track of the projectiles we have dispensed */
	UPROPERTY( SaveGame )
	TArray< AFGProjectile* > mDispensedProjectiles;

	/** Tracks waiting for execute fire */
	UPROPERTY( BlueprintReadOnly, Category ="ChargedWeapon" )
	bool mIsPendingExecuteFire;

	/** If we charge the throw for this amount of time we will get max throw velocity */
	UPROPERTY( EditDefaultsOnly, Category = "ChargedWeapon" )
	float mMaxChargeTime;

	/** If we charge the throw to the max we will throw with this force*/
	UPROPERTY( EditDefaultsOnly, Category = "ChargedWeapon" )
	int32 mMaxThrowForce;

	/** If we tap the throw, this is the minimum force to throw with */
	UPROPERTY( EditDefaultsOnly, Category = "ChargedWeapon" )
	int32 mMinThrowForce;

	int32 mThrowForce;

	/** When we trigger projectile's secondaries we want a small delay in between each trigger */
	UPROPERTY( EditDefaultsOnly, Category = "ChargedWeapon" )
	float mDelayBetweenSecondaryTriggers;

	/** Handles delay between projectile secondaries trigger */
	FTimerHandle mSecondaryTriggerTimerHandle;

private:
	/** The time when we press the fire button */
	float mPressTimestamp;
};
