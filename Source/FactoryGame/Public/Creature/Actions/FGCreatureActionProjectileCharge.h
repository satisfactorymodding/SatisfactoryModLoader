// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGCreatureActionCharge.h"

#include "FGProjectile.h"

#include "FGCreatureActionProjectileCharge.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGCreatureActionProjectileCharge : public UFGCreatureActionCharge
{
	GENERATED_BODY()

public:
	UFGCreatureActionProjectileCharge( const FObjectInitializer& ObjectInitializer );

	// Begin UObject Interface
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// End UObject interface
	
	// Begin UFGAction Interface
	virtual bool InitializeAction( AController* controller, APawn* pawn ) override;
	// End UFGAction Interface

protected:
	// Begin UFGAction Interface
	virtual void InternalActionCleanup( bool actionSuccess ) override;
	virtual void BeginCharge_Implementation() override;
	virtual void EndCharge_Implementation() override;
	// End UFGAction Interface

	/** Used to fire a single projectile. */
	UFUNCTION( BlueprintCallable, Category = "Charge|Projectile" )
	void FireProjectile();

	/** Called whenever we want to fire a projectile from actively charging. */
	UFUNCTION( BlueprintNativeEvent, Category = "Charge|Projectile" )
	void FireActiveChargeProjectile();

	void StartActiveChargeProjectiles();
	void StopActiveChargeProjectiles();

protected:
	/** What kind of ammo to use when firing. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Charge|Projectile" )
	TSubclassOf< class UFGAmmoType > mAmmoType;
	
	/** If specified, will spawn the projectile using the transform of any of the specified sockets. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Charge|Projectile" )
	TArray< FName > mProjectileFiringSocketNames;

	/** Used to offset the spawn location of the projectile. Local space of the creature. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Charge|Projectile" )
	FVector mLocalFiringOffsetLocation;

	/** Used to offset the spawn location of the projectile by a random sphere offset using this value as the max radius. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Charge|Projectile", Meta = ( UIMin = "0.0", ClampMin = "0.0" ) )
	float mProjectileSpawnLocationOffsetRadius;

	/** What vertical launch angle to use for the projectile launch direction. */
	UPROPERTY( EditDefaultsOnly, Category = "Charge|Projectile" )
	FFloatInterval mProjectileVerticalAngle;

	/** How much horizontal spread to apply to the projectile launch direction. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Charge|Projectile" )
	float mProjectileSpreadAngle;

	/** Rate of fire while the charge is active. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Charge|Projectile" )
	float mActiveChargeFiringRate;
	
	/** Magazine object of our ammo type. */
	UPROPERTY( BlueprintReadOnly, Category = "Charge|Projectile" )
	UFGAmmoType* mMagazineObject;

private:
	FTimerHandle mActiveChargeProjectileTimerHandle;
};
