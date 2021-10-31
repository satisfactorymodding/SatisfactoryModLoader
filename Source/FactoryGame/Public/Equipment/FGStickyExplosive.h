// Copyright 2016-2021 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGDestructiveProjectile.h"
#include "GameFramework/Actor.h"
#include "FGStickyExplosive.generated.h"

/**
 * Sticky projectile that explode when its lifespan expires or when triggered.
 */
UCLASS()
class FACTORYGAME_API AFGStickyExplosive : public AFGDestructiveProjectile
{
	GENERATED_BODY()

public:
	AFGStickyExplosive();

	/** Replication. */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	/** Override to modify rotation behaviour */
	virtual void OnImpact( const FHitResult& hitResult ) override;

	// Start AActor interface
	virtual float TakeDamage( float DamageAmount, const struct FDamageEvent& DamageEvent,
							class AController* EventInstigator,
							AActor* DamageCauser ) override;

	//** Save Game Interface */
	virtual bool ShouldSave_Implementation() const override;
	virtual bool NeedTransform_Implementation() override;
	//** End Save Game Interface */

	virtual void TriggerSecondary() override;
	virtual void TriggerSecondaryWithDelay( float delayTime ) override;

	/** Explode this actor */
	void SetToDetonate( float timeUntilDetonate );

	/** Called when the server has blown this explosive */
	UFUNCTION()
	void OnRep_DetonateIn();

protected:
	/** Tells client to mark this to explode after a certain time */
	UPROPERTY( ReplicatedUsing = OnRep_DetonateIn )
	float mDetonateIn;

	UPROPERTY( EditDefaultsOnly )
	class USphereComponent* mEnvironmentDestructionSphere;
};
