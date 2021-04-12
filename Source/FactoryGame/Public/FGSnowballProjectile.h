// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGDestructiveProjectile.h"
#include "GameFramework/Actor.h"
#include "FGSnowballProjectile.generated.h"

UCLASS()
class FACTORYGAME_API AFGSnowballProjectile : public AFGDestructiveProjectile
{
	GENERATED_BODY()
	
public:
	AFGSnowballProjectile();

	/** Replication. */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	/** Override to modify rotation behaviour */
	virtual void OnImpact( const FHitResult& hitResult ) override;

	// Start AActor interface
	virtual float TakeDamage( float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser );

	//** Save Game Interface */
	virtual bool ShouldSave_Implementation() const override;
	virtual bool NeedTransform_Implementation() override;
	//** End Save Game Interface */
	
	/** Explode this actor */
	void SetToDetonate( float timeUntilDetonate );

	/** Called when the server has blown this explosive */
	UFUNCTION()
	void OnRep_DetonateIn();

	/** Assigns the rotation rate to rotating movement component, scaling the mThrowRotation by the scale parameter*/
	void SetAndEnableRotation( float scale );

protected:
	UPROPERTY( EditDefaultsOnly, Category = "Snowball" )
	class URotatingMovementComponent* mRotatingMovementComp;
	
	/** Tells client to mark this to explode after a certain time */
	UPROPERTY( ReplicatedUsing = OnRep_DetonateIn )
	float mDetonateIn;

	UPROPERTY( EditDefaultsOnly )
	class USphereComponent* mEnvironmentDestructionSphere;
	
	UPROPERTY( EditDefaultsOnly, Category = "Snowball" )
	FRotator mThrowRotation;

};
