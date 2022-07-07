// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Creature/Actions/FGCreatureActionAnimated.h"

#include "FGProjectile.h"
#include "Curves/CurveFloat.h"

#include "FGCreatureActionAmmoAttack.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class FACTORYGAME_API UFGCreatureActionAmmoAttack : public UFGCreatureActionAnimated
{
	GENERATED_BODY()
public:
	UFGCreatureActionAmmoAttack( const FObjectInitializer& ObjectInitializer );

	// Begin UFGAction Interface
	virtual bool InitializeAction( AController* controller, APawn* pawn ) override;
	virtual void PerformAction_Implementation() override;
	// End UFGAction Interface

protected:
	// Begin UFGCreatureActionAnimated Interface
	virtual void OnAnimNotify_Implementation( const UFGAnimNotify* Notify ) override;
	virtual void InternalActionCleanup( bool actionSuccess ) override;
	// End UFGCreatureActionAnimated interface

	/** Called when we want to fire a projectile. */
	virtual void FireProjectile();

	UFUNCTION()
	virtual void OnProjectileFired(AActor* spawnedProjectile);

protected:
	/** Ammunition type to fire. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile" )
	TSubclassOf< class UFGAmmoType > mAmmoType = nullptr;

	/** Should we try to predict where the target will be when this projectile reaches it? */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile" )
	bool mPredictTargetLocation = false;

	/** Adjustement for the prediction so we can "shortcut" or "overshoot" the prediction */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile" )
	float mPredictionDistanceMultiplier = 1.0f;
	
	/** Used to multiplied the dispersion set in the ammo. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile" )
	float mFiringDispersionMultiplier = 1.0f;

	/** Socket or bone name that's used on the creature's skeleton to fire from */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile" )
	FName mProjectileFiringSocketName = "None";
	
	/** Used to offset the spawn location of the projectile. Local space of the creature. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile" )
	FVector mLocalFiringOffsetLocation = FVector::ZeroVector;

	/** Used to offset the local launch angle of the projectile. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile" )
	FRotator mLaunchAngleOffset = FRotator::ZeroRotator;

	/** Magazine object of our ammo type. */
	UPROPERTY( BlueprintReadOnly, Category = "Projectile" )
	UFGAmmoType* mMagazineObject = nullptr;
};
