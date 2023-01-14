// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Hologram/FGBuildableHologram.h"
#include "FGCircuitConnectionComponent.h"
#include "FGPowerPoleHologram.generated.h"

enum class EBreakWireState : int8 
{
	Initial,
	Snapped,
	Built
};
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
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void SpawnChildren( AActor* hologramOwner, FVector spawnLocation, APawn* hologramInstigator ) override;
	virtual USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName ) override;
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual AActor* GetUpgradedActor() const override;
	virtual bool TryUpgrade( const FHitResult& hitResult ) override;
	virtual bool DoMultiStepPlacement( bool isInputFromARelease ) override;
	virtual AActor* Construct(TArray<AActor*>& out_children, FNetConstructionID constructionID) override;
	virtual void OnInvalidHitResult() override;
	//End AFGHologram interface

	virtual void Destroyed() override;
	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	
	/** Get the connections the wires snap to. */
	FORCEINLINE UFGCircuitConnectionComponent* GetSnapConnection() const { return mSnapConnection; }

protected:
	class UStaticMeshComponent* mPowerConnectionMesh;

	EBreakWireState mBreakingWireState = EBreakWireState::Initial;
private:
	void ResetByproductHolograms();
	
	/** The connection wires snap to, used when placing a pole automatically. */
	UPROPERTY()
	class UFGCircuitConnectionComponent* mSnapConnection;

	UPROPERTY()
	class AFGBuildable* mSnapWire = nullptr;

	UPROPERTY( Replicated )
	class AFGWireHologram* mWireHologramIn = nullptr;

	UPROPERTY( Replicated )
	class AFGWireHologram* mWireHologramOut = nullptr;

	/** Recipe to use for the automatically spawned wires, can be null. */
	UPROPERTY( EditDefaultsOnly, Replicated, Category = "Wire" )
	TSubclassOf< class UFGRecipe > mDefaultPowerLineRecipe;

	class AFGBuildablePowerPole* mUpgradeTarget = nullptr;
};
