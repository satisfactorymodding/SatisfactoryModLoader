// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGFactoryColoringTypes.h"
#include "Engine/StaticMeshActor.h"
#include "FGWheeledVehicleProxyActor.generated.h"

class AFGWheeledVehicleIdentifier;

/** Vehicle proxy actors are used to represent vehicles moving along their automated path when no players are nearby to reduce the cost of fully simulating vehicle movement */
UCLASS( Abstract, Blueprintable )
class FACTORYGAME_API AFGWheeledVehicleProxyActor : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	AFGWheeledVehicleProxyActor();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnRep_ReplicatedMovement() override;
	// End AActor interface

	/** Applies currently set customization data to the proxy actor */
	void ApplyCustomizationData();
protected:
	UFUNCTION()
	void OnRep_VehicleCustomizationData();
public:
	/** Vehicle that owns this proxy actor */
	UPROPERTY( BlueprintReadOnly, Replicated, Category = "Vehicle Proxy Actor" )
	TObjectPtr<AFGWheeledVehicleIdentifier> mOwnerVehicle;

	/** Customization data to apply to the proxy actor */
	UPROPERTY( BlueprintReadOnly, ReplicatedUsing = OnRep_VehicleCustomizationData, Category = "Vehicle Proxy Actor" )
	FFactoryCustomizationData mVehicleCustomizationData;

	/** Linear velocity of the vehicle. Used for network smoothing */
	FVector mLinearVelocity{ForceInit};
protected:
	// Replicated data used for network smoothing of proxy actor movement
	UPROPERTY( Replicated )
	FVector mAuthoritativeLocation{ForceInit};
	UPROPERTY( Replicated )
	FQuat mAuthoritativeRotation{ForceInit};
	UPROPERTY( Replicated )
	FVector mAuthoritativeLinearVelocity{ForceInit};
	UPROPERTY( Replicated )
	bool mHasAuthoritativeMovementData{false};
	float mTimeSinceAccurateVehicleLocation{0.0f};
};
