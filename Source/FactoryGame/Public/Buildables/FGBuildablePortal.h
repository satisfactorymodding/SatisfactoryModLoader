// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildableFactory.h"
#include "FGBuildablePortalBase.h"
#include "FGCharacterPlayer.h"
#include "FGBuildablePortal.generated.h"

/**
 * Portal building allows teleportation between two linked portals
 */
UCLASS( Blueprintable )
class FACTORYGAME_API AFGBuildablePortal : public AFGBuildablePortalBase
{
	GENERATED_BODY()
public:
	AFGBuildablePortal();
	
	// Begin AActor interface
	virtual void PostInitProperties() override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void GetConditionalReplicatedProps(TArray<FFGCondReplicatedProperty>& outProps) const override;
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin AFGBuildable interface
	virtual void Factory_Tick(float dt) override;
	virtual void Factory_CollectInput_Implementation() override;
	// End AFGBuildable interface

	// Begin AFGBuildableFactory interface
	virtual bool CanProduce_Implementation() const override;
	virtual float GetDefaultProductionCycleTime() const override;
	virtual float GetProductionCycleTime() const override;
	virtual float CalcProductionCycleTimeForPotential(float potential) const override;
	virtual float GetProductionProgress() const override;
	virtual void Factory_StartProducing() override;
	virtual void Factory_StopProducing() override;
	virtual void Factory_TickProducing(float dt) override;
	virtual void Factory_ProductionCycleCompleted(float overProductionRate) override;
	// End AFGBuildableFactory interface
	
	/** Returns the current progress of the heat up animation, in a normalized 0.0f-1.0f form */
	UFUNCTION( BlueprintPure, Category = "Portal" )
	float GetCurrentHeatUpProgress() const { return mCurrentHeatUpProgress; }

	/** Returns true if our heat up animation is complete */
	UFUNCTION( BlueprintPure, Category = "Portal" )
	FORCEINLINE bool IsHeatUpComplete() const { return mHeatUpComplete; }
	
	/** Returns the active fuel inventory pointer */
	UFUNCTION( BlueprintPure, Category = "Portal" )
	FORCEINLINE UFGInventoryComponent* GetFuelInventory() const { return mFuelInventory; }

	/**
	 * Returns the production progress of the current fuel item burn
	 * Will only return valid values on the client when the UI is open
	 */
	UFUNCTION( BlueprintPure, Category = "Portal" )
	FORCEINLINE float GetCurrentProductionProgress() const { return mCurrentProductionProgress; }

	/**
	 * Returns the duration of current item fuel burn
	 * Will only return valid values on the client when the UI is open
	 */
	UFUNCTION( BlueprintPure, Category = "Portal" )
	FORCEINLINE float GetCurrentProductionCycleTime() const { return mCurrentProductionCycleTime; }
protected:
	bool Factory_TryConsumeFuel();
	bool Factory_StartProductionCycle( float overProduction = 0.0f );
	void Factory_UpdateCachedHasFuelForProduction();
	void Factory_HeatUpCycleCompleted();
	
	virtual EFGPortalLinkCandidateState CanLinkToPortal(AFGBuildablePortalBase* otherPortal) const override;
	virtual float GetMaximumPowerConsumption() const override;
	virtual void FillCachedFactoryTickData(FFGPortalCachedFactoryTickData& out_cachedData) const override;
	virtual float GetProducingPowerConsumptionBase_ForPortal() const override;
	virtual void OnLinkedPortalDisconnected() override;

	UFUNCTION()
	void OnFuelInventorySlotUpdated( const int32 index );
	
	void StopProducing_MainThread();
	void HeatUpCycleCompleted_MainThread();
	
	UFUNCTION()
	void OnRep_HeatUpComplete();
private:
	/** Fuel type for the portal */
	UPROPERTY( EditDefaultsOnly, Category = "Portal" )
	TSubclassOf<UFGItemDescriptor> mFuelItemClass;

	/** Size of the fuel slot in the inventory */
	UPROPERTY( EditDefaultsOnly, Category = "Portal" )
	int32 mFuelSlotSize;

	/** Minimum amount of fuel that should be available before we start the heat up */
	UPROPERTY( EditDefaultsOnly, Category = "Portal" )
	int32 mMinFuelToStartProducing;

	/** Minimum amount of fuel that should be available before we attempt to initiate the power up again after running out of fuel */
	UPROPERTY( EditDefaultsOnly, Category = "Portal" )
	int32 mMinFuelToStartProducingAfterAbruptStop;

	/** Cool down time to wait before we start warm up sequence after the link with another portal has been severed */
	UPROPERTY( EditDefaultsOnly, Category = "Portal" )
	float mPortalDisconnectedCooldownTime;
	
	/** Inventory holding the fuel item used for the teleportation */
	UPROPERTY( SaveGame )
	UFGInventoryComponent* mFuelInventory;
	
	/** Cached input connections */
	UPROPERTY()
	TArray<UFGFactoryConnectionComponent*> mCachedInputConnections;
	
	/** True if we have completed our heat up phase and are ready to open a portal connection now */
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_HeatUpComplete, VisibleInstanceOnly, Category = "Portal" )
	bool mHeatUpComplete;
	
	/** Length of the "heat up" phase */
	UPROPERTY( EditDefaultsOnly, Category = "Portal" )
	float mHeatUpCycleTime;
	
	/** Fuel consumption curve used for "heat up" phase, in a form of units of fuel consumed per minute */
	UPROPERTY( EditDefaultsOnly, Category = "Portal" )
	UCurveFloat* mHeatUpFuelConsumptionCurve;

	/** Power consumption curve used for "heat up" phase */
	UPROPERTY( EditDefaultsOnly, Category = "Portal" )
	UCurveFloat* mHeatUpPowerConsumptionCurve;
	
	// TODO @Nick: I really don't like replicating it as during the heat up it's changed every frame, but it's needed to animate the model so
	/** Current heat up progress, scales from 0 (cool) to 1.0f (active) */
	UPROPERTY( SaveGame, Replicated, VisibleInstanceOnly, Category = "Portal" )
	float mCurrentHeatUpProgress;

	UPROPERTY( SaveGame, meta = ( FGReplicated ) )
	float mCurrentProductionProgress;
	UPROPERTY( SaveGame )
	float mLinkedPortalDisconnectCooldownTimeLeft;

	/** Length of the current production cycle, depends on the desired consumption rate */
	UPROPERTY( SaveGame, meta = ( FGReplicated ) )
	float mCurrentProductionCycleTime;

	/** If true, we have run out of fuel, and will not attempt to start the production until we have minimal amount of fuel available */
	UPROPERTY( SaveGame )
	bool mTrippedProductionStop;
	
	UPROPERTY( SaveGame )
	bool mCachedHasEnoughFuelForProduce;
};
