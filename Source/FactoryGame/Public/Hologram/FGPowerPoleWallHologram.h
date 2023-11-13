// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGWallAttachmentHologram.h"
#include "FGPowerPoleWallHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGPowerPoleWallHologram : public AFGWallAttachmentHologram
{
	GENERATED_BODY()
public:
	AFGPowerPoleWallHologram();

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface
	
	// Begin AFGHologram interface
	virtual USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName, const FName& attachSocketName ) override;
	virtual void PostHologramPlacement( const FHitResult& hitResult ) override;
	virtual bool IsValidHitResult(const FHitResult& hitResult) const override;
	virtual bool TryUpgrade(const FHitResult& hitResult) override;
	virtual AActor* GetUpgradedActor() const override;
	// End AFGHologram interface

	/** Get the connections the wires snap to. */
	FORCEINLINE UFGCircuitConnectionComponent* GetSnapConnection() const { return mSnapConnection; }

protected:
	UPROPERTY()
	class UStaticMeshComponent* mPowerConnectionMesh;

private:
	/** The connection wires snap to, used when placing a pole automatically. */
	UPROPERTY()
	class UFGCircuitConnectionComponent* mSnapConnection;

	/** Power pole we are upgrading */
	UPROPERTY()
	class AFGBuildablePowerPole* mUpgradeTarget;
};
