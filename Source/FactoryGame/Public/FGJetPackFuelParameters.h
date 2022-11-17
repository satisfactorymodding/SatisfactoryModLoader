// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Resources/FGItemDescriptor.h"
#include "UObject/Object.h"
#include "FGJetPackFuelParameters.generated.h"

UCLASS( Blueprintable, Abstract )
class FACTORYGAME_API UFGJetPackFuelParameters : public UObject
{
	GENERATED_BODY()
protected:
	friend class AFGJetPack;
	
	/** How much to add to Z velocity when Thrusting. */
	UPROPERTY( EditDefaultsOnly, Category = "JetPack")
	float mThrustPower = 4000.0;
	/** When the Z velocity is above, or below negated value, a multiplier will dampen the added velocity. */
	UPROPERTY( EditDefaultsOnly, Category = "JetPack")
	float mVelocityZExtreme = 350.0;
	/** The damper for Z velocity when extreme values. */
	UPROPERTY( EditDefaultsOnly, Category = "JetPack")
	float mVelocityZExtremeDamper = 0.9;
	/** Time to hold thrust  before we start thrusting. */
    UPROPERTY( EditDefaultsOnly, Category = "JetPack")
	float mJumpBeforeThrustTime = 0.3f;
	/** Percentage of max fuel regen every frame not thrusting. */
	UPROPERTY( EditDefaultsOnly, Category = "JetPack")
	float mFuelRegenRate = 0.5f;
	/** How much of the tank is consumed per second of flying. */
	UPROPERTY( EditDefaultsOnly, Category = "JetPack")
	float mFuelConsumeRate = 0.2f;
	/** The Default value for Thrust Cooldown. */
	UPROPERTY( EditDefaultsOnly, Category = "JetPack" )
	float mThrustCooldownDefault = 0.4f;
	/** How much of the full tank is 1 Fuel worth. */
	UPROPERTY( EditDefaultsOnly, Category = "JetPack" )
	float mFuelWorth = 0.5f;
	/** How often to make the noise (in seconds) while the jetpack is active. */
	UPROPERTY( EditDefaultsOnly, Category = "JetPack" )
	float mActiveNoiseFrequency = 0.2f;
	/** The noise to make when the jetpack is active. */
	UPROPERTY( EditDefaultsOnly, Category = "JetPack" )
	TSubclassOf< class UFGNoise > mActiveNoise;
	/** The maximum amount of fuel in the JetPack */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "JetPack")
	float mMaxFuel = 1.0f;
	/** Adjusted air control (in character movement) while thrusting. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "JetPack" )
	float mThrustAirControl = 0.3f;


	// Reference to Fuel Type Desc class.
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "JetPack" )
	TSubclassOf< UFGItemDescriptor > mFuelTypeDesc; 
	
};
