// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/FGWeapon.h"
#include "Equipment/FGWeaponProjectileFire.h"
#include "FGSnowballWeapon.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGSnowballWeapon : public AFGWeapon
{
	GENERATED_BODY()
	
public:
	AFGSnowballWeapon();

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
	UFUNCTION( BlueprintPure, Category = "Snowball" )
	float GetChargePct();

protected:
	/** Executes on Server, Spawns and throws out a Snowball charge */
	void SpawnExplosive( FTransform spawnTransform, int32 throwForce );

	/** Called from client to Spawn Explosive on server */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_SpawnExplosive( FTransform spawnTransform, int32 throwForce );

	/** Called by Client or Server, sets the lifetime on explosives so that they boom after a duration */
	void StartDetonations();

	UFUNCTION( Server, Reliable, WithValidation )
	void Server_StartDetonations();

	/** Explosive Data (Applied to the explosive projectile on spawn) */
	UPROPERTY( EditDefaultsOnly, Category = "Snowball" )
	FProjectileData mExplosiveData;

	/** Called by an anim notify to actually trigger the throwing of the explosive */
	UFUNCTION( BlueprintCallable, Category = "Snowball" )
	void ExecutePrimaryFire();

	/** Called by client to start throw on server. */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_ExecutePrimaryFire();

	/** Called when the player presses secondary fire */
	void SecondaryFirePressed();

	/** Call animation from blueprint that will contain notify to trigger actual detonation */
	UFUNCTION( BlueprintNativeEvent, Category = "Snowball" )
	void OnSecondaryFirePressed();

	/** Called by an anim notify to actually trigger the detonation sequence */
	UFUNCTION( BlueprintCallable, Category = "Snowball" )
	void ExecuteSecondaryFire();

	/** Called by client to start fire on server. */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_ExecuteSecondaryFire();

	/** Called from Hotbar status change, to indicate we have change SceneViewport Focus */
	UFUNCTION()
	void OnViewportFocusChanged(bool isOpen, TSubclassOf< class UUserWidget > interactionClass );

	// Begin AFGEquipment interface
	virtual void AddEquipmentActionBindings();
	// End AFGEquipment interface

protected:
	/** What types of bombs we should spawn */
	UPROPERTY( EditDefaultsOnly, Category = "Explosion" )
	TSubclassOf< class AFGSnowballProjectile > mExplosiveClass;

	/** Keeps track of the explosives we have dispensed */
	UPROPERTY( SaveGame )
	TArray< AFGSnowballProjectile* > mDispensedExplosives;

	/** Tracks waiting for execute fire */
	UPROPERTY( BlueprintReadOnly, Category ="Snowball")
	bool mIsPendingExecuteFire;
	
	/** If we charge the throw for this amount of time we will get max throw velocity */
	UPROPERTY( EditDefaultsOnly, Category = "Snowball" )
	float mMaxChargeTime;

	/** If we charge the throw to the max we will throw with this force*/
	UPROPERTY( EditDefaultsOnly, Category = "Snowball" )
	int32 mMaxThrowForce;

	/** If we tap the throw, this is the minimum force to throw with */
	UPROPERTY( EditDefaultsOnly, Category = "Snowball" )
	int32 mMinThrowForce;

	/** When we blow shit up we want a small delay in between each explosion */
	UPROPERTY( EditDefaultsOnly, Category = "Snowball" )
	float mDelayBetweenExplosions;

	/** Handles delay between explosions */
	FTimerHandle mDetonateTimerHandle;

private:
	/** The time when we press the fire button */
	float mPressTimestamp;

	/** The time when we released the fire button */
	float mPressReleaseTimestamp;
	
	
	
};
