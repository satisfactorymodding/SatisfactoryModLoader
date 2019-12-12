// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Equipment/FGEquipment.h"
#include "Equipment/FGEquipmentAttachment.h"
#include "FGJumpingStilts.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGJumpingStilts : public AFGEquipment
{
	GENERATED_BODY()

public:

	AFGJumpingStilts();

	virtual void Equip( class AFGCharacterPlayer* character ) override; 
	virtual void UnEquip() override;

	/** Is called by the MovementComponent to determine a new maximum speed */
	UFUNCTION( BlueprintCallable, Category = "Jumping Stilts" )
	float GetAdjustedMaxSpeed( float defaultMaxSpeed );

	/** Called by the MovementComponent to determine a new JumpZ scalar */
	UFUNCTION( BlueprintCallable, Category = "Jumping Stilts" )
	float GetAdjustedZJumpSpeed( float defaultJumpZ );

	/** Returns the speed at which a player will now take damage when falling */
	UFUNCTION( BlueprintCallable, Category = "Jumping Stilts" )
	float GetMaxFallSpeedBeforeDamage();

	/** Returns the current movement components Z velocity */
	UFUNCTION( BlueprintCallable, Category = "Jumping Stilts" )
	float GetCurrentFallSpeed();

	UFUNCTION( BlueprintCallable, Category = "Jumping Stilts" )
	float GetNormalizedFallSpeedUntilDamaged();

protected:

	/** The UCurveFloat to use to override the default fall damage curve */
	UPROPERTY( EditDefaultsOnly, Category = "Jumping Stilts" )
	UCurveFloat* mFallDamageCurveOverride;

	/** The factor by which the default sprint speed is multiplied while equipped */
	UPROPERTY( EditDefaultsOnly, Category = "Jumping Stilts" )
	float mSprintSpeedFactor;

	/** The factor by which the default JumpZ is multiplied while equipped */
	UPROPERTY( EditDefaultsOnly, Category = "Jumping Stilts" )
	float mJumpSpeedFactor;

private:
	/** A cached reference to the Character that has equipped this item */
	class UFGCharacterMovementComponent* mCachedMovementComponent;

	float mMaxFallSpeedBeforeDamage;
};


UCLASS()
class FACTORYGAME_API AFGJumpingStiltsAttachment : public AFGEquipmentAttachment
{
	GENERATED_BODY()


};