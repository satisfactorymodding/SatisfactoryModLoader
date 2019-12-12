// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGWeapon.h"
#include "FGC4Dispenser.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGC4Dispenser : public AFGWeapon
{
	GENERATED_BODY()
public:

	AFGC4Dispenser();

	// Begin AFGEquipment interface
	virtual bool ShouldSaveState() const override;
	// End

	/** Called on both client and server when firing. */
	virtual void OnPrimaryFirePressed() override;

	/** Called on both client and server when firing. */
	virtual void OnPrimaryFireReleased() override;

	/** Return the current charge in percent */
	UFUNCTION( BlueprintPure, Category = "C4" )
	float GetChargePct();

protected:
	/** Spawns and throws out a C4 charge */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_SpawnC4( int32 throwForce );

	/** Makes the explosives go boom */
	void DetonateNextCharge();

	/** Called on the owner, client or server but not both. */
	void OnDetonatePressed();

	/** Called by client to start fire on server. */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_DetonatePressed();

	// Begin AFGEquipment interface
	virtual void AddEquipmentActionBindings();
	// End AFGEquipment interface

protected:
	/** What types of bombs we should spawn */
	UPROPERTY( EditDefaultsOnly, Category = "C4" )
	TSubclassOf< class AFGC4Explosive > mC4ExplosiveClass;	

	/** Keeps track of the explosives we have dispensed */
	UPROPERTY( SaveGame )
	TArray< AFGC4Explosive* > mDispensedExplosives;
	
	/** If we charge the throw for this amount of time we will get max throw velocity */
	UPROPERTY( EditDefaultsOnly, Category = "C4" )
	float mMaxChargeTime;

	/** If we charge the throw to the max we will throw with this force*/
	UPROPERTY( EditDefaultsOnly, Category = "C4" )
	int32 mMaxThrowForce;

	/** When we blow shit up we want a small delay in between each explosion */
	UPROPERTY( EditDefaultsOnly, Category = "C4" )
	float mDelayBetweenExplosions;

	/** Handles delay between explosions */
	FTimerHandle mDetonateTimerHandle;

private:
	/** The time when we press the fire button */
	float mPressTimestamp;

};
