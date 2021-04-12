// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildableResourceExtractorBase.h"
#include "Replication/FGRepDetailActor_Extractor.h"
#include "FGBuildableResourceExtractor.generated.h"

/**
 * The base class for all resource extractors, i.e. miners and pumps.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableResourceExtractor : public AFGBuildableResourceExtractorBase
{
	GENERATED_BODY()

public:
	/** Decide on what properties to replicate */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void PreReplication( IRepChangedPropertyTracker& ChangedPropertyTracker ) override;
	
	AFGBuildableResourceExtractor();

	// Begin IFGReplicationDetailActorOwnerInterface
	virtual UClass* GetReplicationDetailActorClass() const override { return AFGRepDetailActor_Extractor::StaticClass(); };
	virtual void OnReplicationDetailActorRemoved() override;
	// End IFGReplicationDetailActorOwnerInterface

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin AFGBuildableFactory interface
	virtual bool CanProduce_Implementation() const override;
	virtual float GetProductionCycleTime() const override;
	virtual float GetProductionProgress() const override;
	virtual float CalcProductionCycleTimeForPotential( float potential ) const override;
	// End AFGBuildableFactory interface

	/** Get the inventory we output the extracted resources to */
	UFUNCTION( BlueprintPure, Category = "Resource" )
	class UFGInventoryComponent* GetOutputInventory() const{ return mInventoryOutputHandler->GetActiveInventoryComponent(); }

	/** Get the quantity of items mined each production cycle */
	UFUNCTION( BlueprintPure, Category = "Extraction" )
	FORCEINLINE int32 GetNumExtractedItemsPerCycle() const { return mItemsPerCycle; }

	/** Get the quantity of items extracted each cycle converted for displaying in the UI */
	UFUNCTION( BlueprintPure, Category = "Extraction" )
	float GetNumExtractedItemsPerCycleConverted() const;

	/** Get the quantity of items extracted per minute, converted per resource form for the UI */
	UFUNCTION( BlueprintPure, Category = "Extraction" )
	float GetExtractionPerMinute() const;

	/** Are we done with startup animation */
	UFUNCTION( BlueprintPure, Category = "Resources" )
	bool IsStartupComplete();

	/** Get the smoothed flow rate out of the extractor in m^3/s. Only valid for Liquid or Gas extractors */
	UFUNCTION( BlueprintPure, Category = "Pipes" )
	float GetFlowRateSmoothed() const { return mReplicatedFlowRate; }

	/** Return the maximum out flow from inventory to pipeline conversion in m^3/s */
	UFUNCTION( BlueprintPure, Category = "Pipes" )
	float GetMaxFlowRate() const;

	float GetDefaultExtractCycleTime() const { return mExtractCycleTime; }

protected:
	// Begin Factory_ Interface
	virtual void Factory_StartProducing() override;
	virtual void Factory_TickProducing( float dt ) override;
	virtual void Factory_PushPipeOutput_Implementation( float dt ) override;
	// End Factory_ Interface

	// Begin AFGBuildableFactory Interface
	virtual void OnRep_ReplicationDetailActor() override;
	virtual void OnRep_CurrentPotential() override;
	// End AFGBuildableFactory Interface

	// Begin AFGBuildableResourceExtractorBase Interface
	virtual void OnExtractableResourceSet() override;
	virtual void OnRep_ExtractableResource() override;
	// End AFGBuildableResourceExtractorBase Interface

private:
	void CalculateProductionCycleTime();

private:
	friend class AFGRepDetailActor_Extractor;

	class UFGReplicationDetailInventoryComponent* mInventoryOutputHandler;

	/** Power up time for the extraction process, e.g. the time it takes for a drill to start spinning. */
	UPROPERTY( EditDefaultsOnly, Category = "Extraction" )
	float mExtractStartupTime;

	/** How much time we have left of the start up time for the extraction process (mExtractStartupTime). */
	UPROPERTY( Replicated, SaveGame )
	float mExtractStartupTimer;

	/** How long does it take to complete one mining cycle. In seconds. */
	UPROPERTY( EditDefaultsOnly, Category = "Extraction", meta = (ClampMin = "0.0001") )
	float mExtractCycleTime;

	/** How many items are extracted per cycle */
	UPROPERTY( EditDefaultsOnly, Category = "Extraction" )
	int32 mItemsPerCycle;

	/** Cached property indicating that this Extractor is extracting a non-solid resource. This is used as a replication condition so FlowRate is not included for all extractors */
	bool mIsLiquidOrGasType;

	/** Current extract progress in the range [0, 1] */
	UPROPERTY( Replicated, SaveGame, Meta = (NoAutoJson = true) )
	float mCurrentExtractProgress;

	/** Cached pipe output connections */
	UPROPERTY()
	TArray< class UFGPipeConnectionComponent* > mPipeOutputConnections;

	/** Our output inventory, */
	UPROPERTY( SaveGame )
	class UFGInventoryComponent* mOutputInventory;

	//******* Begin Pipe Flow Output params *******/
	
	/** Last content value when updating flow rate */
	int32 mFluidMovedLastProducingTick;

	/** Current smoothed flow rate */
	float mSmoothedFlowRate;

	/** How frequently to update flow rate ( both clients and server will use the replicated value in the UI )*/
	float mUpdateReplicatedFlowFrequency;

	/** How long since the last replicated flow assignment */
	float mTimeSinceLastFlowUpdate;

	/** Replicated smoothed flow rate */
	UPROPERTY( Replicated )
	float mReplicatedFlowRate;

	float mProductionCycleTime = 0.0f;

	FInventoryStack mStandardStack;

	/******** End Pipe Flow Output Params ********/
};
