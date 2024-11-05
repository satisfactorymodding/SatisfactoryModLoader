// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FGProjectileMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGProjectileMovementComponent : public UProjectileMovementComponent
{
	GENERATED_BODY()

public:
	UFGProjectileMovementComponent();

	UFUNCTION( BlueprintCallable, Category = "Homing" )
	void SetHomingTargetLocation( const FVector& targetLocation );

	UFUNCTION( BlueprintCallable, Category = "Homing" )
	void ClearHomingTargetLocation();

	bool HasHomingTargetLocation() const { return mHasHomingTargetLocation; }

	UFUNCTION( BlueprintCallable, Category = "Homing" )
	void SetHomingTargetDirection( const FVector& targetDirection );

	UFUNCTION( BlueprintCallable, Category = "Homing" )
	void ClearHomingTargetDirection();
	
	virtual FVector ComputeAcceleration( const FVector& InVelocity, float DeltaTime ) const override;

protected:
	/** Can be used instead of the HomingTargetComponent if the targetcomponent is null and this value has been set. */
	UPROPERTY( BlueprintReadOnly, Category = "Homing" )
	FVector mHomingTargetLocation;

	/** Can be used instead of the HomingTargetComponent or HomingTargetLocation if we want the projectile to try to follow a specific direction instead. */
	UPROPERTY( BlueprintReadOnly, Category = "Homing" )
	FVector mHomingTargetDirection;

	/** Whether or not HomingTargetLocation has been set. */
	UPROPERTY( BlueprintReadOnly, Category = "Homing" )
	bool mHasHomingTargetLocation;
};
