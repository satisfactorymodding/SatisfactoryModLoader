// Copyright 2016-2021 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"

#include "Resources/FGItemDescriptor.h"
#include "FGItemDescAmmoType.generated.h"

class AFGWeapon;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnAmmoFired, AActor*, SpawnedActor );

/**
 *  Descriptor for all types of ammunition magazines and their effects.
 */
UCLASS()
class FACTORYGAME_API UFGItemDescAmmoType : public UFGItemDescriptor
{
	GENERATED_BODY()

public:
	/** Initialize the internals of the ammo type, to call first upon creation */
	UFUNCTION( BlueprintNativeEvent )
	void InitializeAmmoType( AFGWeapon* Weapon );

	UFUNCTION( BlueprintCallable, Category="Ammunition" )
	virtual void SetFiringTransform( FTransform firingTransform );

	UFUNCTION( BlueprintCallable, Category="Ammunition" )
	FORCEINLINE FTransform GetFiringTransform() { return mFiringTransform; }

	/** Called by firing actor to trigger main behavior of the ammo type. Overriden to implement specialized behaviors */
	UFUNCTION( BlueprintNativeEvent )
	void FireAmmunition();

	/** Called by firing actor to trigger secondary behaviors of the ammo type. Overriden to implement specialized behaviors */
	UFUNCTION( BlueprintNativeEvent )
	void FireSecondary();

	/** Has ammo type been initialized properly and successfully? If not, I'd avoid doing anything with it */
	UFUNCTION( BlueprintPure, Category="Ammunition" )
	FORCEINLINE bool HasBeenInitialized() const { return mHasBeenInitialized; }

	UFUNCTION( BlueprintPure, Category="Ammunition" )
	FORCEINLINE float GetWeaponDamageMultiplier() const { return mWeaponDamageMultiplier; }

	/** Returns magazine size */
	UFUNCTION( BlueprintPure, Category="Ammunition" )
	FORCEINLINE int GetMagazineSize() const { return mMagazineSize; }

	UFUNCTION( BlueprintPure, Category="Ammunition" )
	FORCEINLINE float GetMaxAmmoEffectiveRange() const { return mMaxAmmoEffectiveRange; }

	UFUNCTION( BlueprintPure, Category="Ammunition" )
	FORCEINLINE FRuntimeFloatCurve GetAmmoDamageFalloffCurve() const { return mAmmoDamageFalloff; }

	/** Returns reload time modifier in percent (Positive = slower reload, Negative = faster reload) */
	UFUNCTION( BlueprintPure, Category="Ammunition|Modifiers" )
	FORCEINLINE float GetReloadTimeModifier() const { return mReloadTimeModifier; }

	/** Returns fire rate modifier in percent (Positive = faster firerate, Negative = slower firerate) */
	UFUNCTION( BlueprintPure, Category="Ammunition|Modifiers" )
	FORCEINLINE float GetFireRateModifier() const { return mFireRateModifier; }

	UFUNCTION( BlueprintPure, Category="Ammunition|Modifiers" )
	FORCEINLINE float GetDispersionPerShotChangeModifier() const { return mDispersionPerShotChangeModifier; }

	UFUNCTION( BlueprintPure, Category="Ammunition|Modifiers" )
	FORCEINLINE float GetMinWeaponDispersionModifier() const { return mMinWeaponDispersionModifier; }

	UFUNCTION( BlueprintPure, Category="Ammunition|Modifiers" )
	FORCEINLINE float GetMaxWeaponDispersionModifier() const { return mMaxWeaponDispersionModifier; }

	UFUNCTION( BlueprintPure, Category="Ammunition|Modifiers" )
	FORCEINLINE float GetWeaponAimTimeModifier() const { return mWeaponAimTimeModifier; }

	/** Called when an ammunition has been fired. Actor can be null. */
	UPROPERTY()
	FOnAmmoFired AmmoFiredDelegate;

protected:
	/** Weapon owning this ammo type descriptor and most likely the firing actor */
	UPROPERTY()
	AFGWeapon* mWeapon = nullptr;

	/** The actor responsible for dealing the damage of the weapon */
	UPROPERTY()
	APawn* mInstigator = nullptr;

	/** The transform used for spawning the projectile */
	UPROPERTY()
	FTransform mFiringTransform;

private:
	/** Initialization flag */
	UPROPERTY()
	bool mHasBeenInitialized = false;

	UPROPERTY()
	float mWeaponDamageMultiplier = 1.0f;

	/** Maximum amount of ammunition held by this magazine type */
	UPROPERTY( EditDefaultsOnly, Category = "Ammunition" )
	int mMagazineSize = 0;

	/** Maximum distance in cm beyond which the effective range of the weapon will be considered minimal */
	UPROPERTY( SaveGame, EditDefaultsOnly, Category="Ammunition" )
	float mMaxAmmoEffectiveRange = 5000.0f;

	/** Horizontal axis drives the damage falloff between 0-1 (1 = max effective range).
	 * Up axis controls how much damage attenuation/amplification we get at said distance.*/
	UPROPERTY( SaveGame, EditDefaultsOnly, Category="Ammunition" )
	FRuntimeFloatCurve mAmmoDamageFalloff;

	/** Unused for now */
	UPROPERTY( EditDefaultsOnly, Category= "Ammunition" )
	UParticleSystem* mMuzzleFlashVFX = nullptr;

	/** Multiplicative modifier to the reload time, between 0 and the moon (1 = 100%) */
	UPROPERTY( EditDefaultsOnly, Category="Ammunition|Modifiers", meta = (ClampMin = "0.0", UIMin = "0.0") )
	float mReloadTimeModifier = 1.0f;

	/** Multiplicative modifier to the fire rate, in percent, between 0 and the moon (1 = 100%) */
	UPROPERTY( EditDefaultsOnly, Category="Ammunition|Modifiers", meta = (ClampMin = "0.0", UIMin = "0") )
	float mFireRateModifier = 1.0f;

	/** Additive flat change to applied weapon dispersion on each shot */
	UPROPERTY( EditDefaultsOnly, Category="Ammunition|Modifiers" )
	float mDispersionPerShotChangeModifier = 0.0f;

	/** Additive modifier modifying the minimum (resting) dispersion of the weapon */
	UPROPERTY( EditDefaultsOnly, Category="Ammunition|Modifiers" )
	float mMinWeaponDispersionModifier = 0.0f;

	/** Additive modifier modifying the maximum (firing) dispersion of the weapon */
	UPROPERTY( EditDefaultsOnly, Category="Ammunition|Modifiers" )
	float mMaxWeaponDispersionModifier = 0.0f;

	/** Additive modifier applying to the time the weapon takes to go from firing to resting dispersion */
	UPROPERTY( EditDefaultsOnly, Category="Ammunition|Modifiers" )
	float mWeaponAimTimeModifier = 0.0f;
};
