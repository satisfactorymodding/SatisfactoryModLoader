// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGWallAttachmentHologram.h"
#include "FGPowerPoleWallHologram.generated.h"

enum class EBreakWireState : int8;

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
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void Destroyed() override;
	// End AActor interface
	
	// Begin AFGHologram interface
	virtual USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName, const FName& attachSocketName ) override;
	virtual AActor* Construct( TArray< AActor* >& out_children, FNetConstructionID constructionID ) override;
	virtual void SpawnChildren( AActor* hologramOwner, FVector spawnLocation, APawn* hologramInstigator ) override;
	virtual void PostHologramPlacement( const FHitResult& hitResult ) override;
	virtual bool IsValidHitResult(const FHitResult& hitResult) const override;
	virtual bool TryUpgrade(const FHitResult& hitResult) override;
	virtual AActor* GetUpgradedActor() const override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual float GetBuildGunRangeOverride_Implementation() const override;
	virtual void CheckValidPlacement() override;
	virtual void OnInvalidHitResult() override;
	virtual bool DoMultiStepPlacement( bool isInputFromARelease ) override;
	virtual bool ShouldBuildGunHitWireMeshes() const override;
	// End AFGHologram interface

	/** Get the connections the wires snap to. */
	FORCEINLINE UFGCircuitConnectionComponent* GetSnapConnection() const { return mSnapConnection; }

protected:
	bool AlignWithWire( const class AFGBuildableWire* wire, FVector& locationToAlign, FRotator& out_rotation ) const;

private:
	void ResetByproductHolograms();
	
protected:
	UPROPERTY()
	class UStaticMeshComponent* mPowerConnectionMesh;

	EBreakWireState mBreakingWireState;

private:
	/** The connection wires snap to, used when placing a pole automatically. */
	UPROPERTY()
	class UFGCircuitConnectionComponent* mSnapConnection;
	
	UPROPERTY()
	class UFGCircuitConnectionComponent* mPowerTowerSnapConnection;

	/** Power pole we are upgrading */
	UPROPERTY( Replicated, CustomSerialization )
	class AFGBuildablePowerPole* mUpgradeTarget;

	UPROPERTY( Replicated, CustomSerialization )
	class AFGBuildableWire* mSnapWire;

	UPROPERTY( Replicated )
	class AFGWireHologram* mWireHologramIn = nullptr;
    
	UPROPERTY( Replicated )
	class AFGWireHologram* mWireHologramOut = nullptr;

	/** Recipe to use for the automatically spawned wires, can be null. */
    UPROPERTY( EditDefaultsOnly, Category = "Wire" )
    TSubclassOf< class UFGRecipe > mDefaultPowerLineRecipe;
};
