// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGBuildableHologram.h"
#include "FGCircuitConnectionComponent.h"
#include "FGPowerPoleHologram.generated.h"

/**
* Hologram for power poles.
*/
UCLASS()
class FACTORYGAME_API AFGPowerPoleHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	//Begin AFGHologram interface
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName ) override;
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual AActor* GetUpgradedActor() const override;
	virtual bool TryUpgrade( const FHitResult& hitResult ) override;
	virtual bool DoMultiStepPlacement( bool isInputFromARelease ) override;
	//End AFGHologram interface

	/** Get the connections the wires snap to. */
	FORCEINLINE UFGCircuitConnectionComponent* GetSnapConnection() const { return mSnapConnection; }

protected:
	class UStaticMeshComponent* mPowerConnectionMesh;

private:
	/** The connection wires snap to, used when placing a pole automatically. */
	UPROPERTY()
	class UFGCircuitConnectionComponent* mSnapConnection;

	class AFGBuildablePowerPole* mUpgradeTarget = nullptr;
};
