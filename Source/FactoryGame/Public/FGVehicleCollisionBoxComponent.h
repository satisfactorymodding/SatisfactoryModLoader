// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "Components/BoxComponent.h"
#include "FGWheeledVehicle.h"
#include "FGVehicleCollisionBoxComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FACTORYGAME_API UFGVehicleCollisionBoxComponent : public UBoxComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFGVehicleCollisionBoxComponent();

public:	

	UFUNCTION()
	void OnOverlapBegin( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );

private:
	void PushCharacter( AActor* OtherActor );
	
public:
	/** Multiplier for velocity change with all impacts. */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Collision", meta = (ClampMin = "0.1", ClampMax = "10.0", UIMin = "0.1", UIMax = "10.0"))
	float mFudgeFactor;

	/** Added Z Velocity multiplier. DOES NOT specify how much velocity. This number should be small 0.0-1.0 range */
	UPROPERTY(EditDefaultsOnly, Category = "Vehicle Collision", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float mAddedZVelocityFactor;
	
	/** The maximum Z velocity that can be added on a collision. */
	UPROPERTY(EditDefaultsOnly, Category = "Vehicle Collision")
	float mMaxAddedZVelocity;

	/** The maximum velocity that can be added on a collision. */
	UPROPERTY(EditDefaultsOnly, Category = "Vehicle Collision")
	float mMaxCollisionVelocity;

	/** The minimum velocity required for any fudged Z values to take effect. This helps when player just runs against the vehicle. */
	UPROPERTY(EditDefaultsOnly, Category = "Vehicle Collision")
	float mMinVelocityForAddedZ;

private:
	class AFGWheeledVehicle* OwnerVehicle;

public:
	FORCEINLINE ~UFGVehicleCollisionBoxComponent() = default;
};
