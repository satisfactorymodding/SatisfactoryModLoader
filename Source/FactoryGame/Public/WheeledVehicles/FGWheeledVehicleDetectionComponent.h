// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Components/BoxComponent.h"
#include "FGWheeledVehicleDetectionComponent.generated.h"

// TODO: migrate from PhysX to Chaos; in the meantime, stfu
#pragma warning( disable : 4996 )


UCLASS()
class FACTORYGAME_API UFGWheeledVehicleDetectionComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UFGWheeledVehicleDetectionComponent();

	void Init( class AFGWheeledVehicle* vehicle, UWheeledVehicleMovementComponent* movement );

private:
	//~ Begin UActorComponent Interface
	virtual void OnCreatePhysicsState() override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason );
	virtual void TickComponent( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	//~ End UActorComponent Interface

	UFUNCTION()
	void OnOverlapBegin( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );

	UFUNCTION()
	void OnOverlapEnd( UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex );

private:
	TWeakObjectPtr< class AFGWheeledVehicle > mVehicle;
	TWeakObjectPtr< class UWheeledVehicleMovementComponent > mMovement;

	float mMaxDistanceToGhost = 0.0f;

	float mWheelRadius = 0.0f;

	FVector mLocalOrigin;
	float mLocalZOffset;

	TWeakObjectPtr < class USkeletalMeshComponent > mGhost;
};
