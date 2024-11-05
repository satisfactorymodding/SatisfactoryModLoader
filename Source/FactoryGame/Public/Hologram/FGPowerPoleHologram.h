// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildableHologram.h"
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
	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	// End AActor interface
	
	//Begin AFGHologram interface
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void PostHologramPlacement( const FHitResult& hitResult ) override;
	virtual void SpawnChildren( AActor* hologramOwner, FVector spawnLocation, APawn* hologramInstigator ) override;
	virtual USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName, const FName& attachSocketName ) override;
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual AActor* GetUpgradedActor() const override;
	virtual bool TryUpgrade( const FHitResult& hitResult ) override;
	virtual bool DoMultiStepPlacement( bool isInputFromARelease ) override;
	virtual AActor* Construct( TArray< AActor* >& out_children, FNetConstructionID constructionID ) override;
	virtual void OnInvalidHitResult() override;
	virtual void CheckValidPlacement() override;
	virtual float GetBuildGunRangeOverride_Implementation() const override;
	virtual bool ShouldBuildGunHitWireMeshes() const override;
	//End AFGHologram interface

	/** Get the connections the wires snap to. */
	FORCEINLINE UFGCircuitConnectionComponent* GetSnapConnection() const { return mSnapConnection; }

protected:
	bool AlignWithWire( const class AFGBuildableWire* wire, FVector& locationToAlign, FRotator& out_rotation ) const;

protected:
	UPROPERTY()
	class UStaticMeshComponent* mPowerConnectionMesh;

	EBreakWireState mBreakingWireState = EBreakWireState::Initial;
private:
	void ResetByproductHolograms();
	
	/** The connection wires snap to, used when placing a pole automatically. */
	UPROPERTY()
	class UFGCircuitConnectionComponent* mSnapConnection;

	UPROPERTY()
	class UFGCircuitConnectionComponent* mPowerTowerSnapConnection;

	UPROPERTY( CustomSerialization, Replicated )
	class AFGBuildableWire* mSnapWire = nullptr;

	UPROPERTY( Replicated )
	class AFGWireHologram* mWireHologramIn = nullptr;

	UPROPERTY( Replicated )
	class AFGWireHologram* mWireHologramOut = nullptr;

	/** Recipe to use for the automatically spawned wires, can be null. */
	UPROPERTY( EditDefaultsOnly, Category = "Wire" )
	TSubclassOf< class UFGRecipe > mDefaultPowerLineRecipe;

	UPROPERTY()
	class AFGBuildablePowerPole* mUpgradeTarget = nullptr;
};
