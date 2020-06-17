// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "SubclassOf.h"
#include "UObject/CoreNet.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGBuildableFactory.h"
#include "Resources/FGExtractableResourceInterface.h"
#include "Resources/FGResourceDescriptor.h"
#include "Replication/FGRepDetailActor_Extractor.h"
#include "../Resources/FGItemDescriptor.h"
#include "FGBuildableResourceExtractor.generated.h"

/**
 * The base class for all resource extractors, i.e. miners and pumps.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableResourceExtractor : public AFGBuildableFactory
{
	GENERATED_BODY()

public:
	/** Decide on what properties to replicate */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void PreReplication( IRepChangedPropertyTracker& ChangedPropertyTracker ) override;

	/** Ctor */
	AFGBuildableResourceExtractor();

	// Begin IFGReplicationDetailActorOwnerInterface
	virtual UClass* GetReplicationDetailActorClass() const override { return AFGRepDetailActor_Extractor::StaticClass(); };
	// End IFGReplicationDetailActorOwnerInterface

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	bool DisconnectExtractableResource();

		// End AActor interface 

	// Begin AFGBuildableFactory interface
	virtual bool CanProduce_Implementation() const override;
	virtual float GetProductionCycleTime() const override;
	virtual float GetProductionProgress() const override;
	virtual float CalcProductionCycleTimeForPotential( float potential ) const override;
	// End AFGBuildableFactory interface

	// Begin Save Interface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End Save Interface

	/** [DEPRECATED] - Use GetExtractableResource() instead.
	*	Get the resource node this miner is mining from. */
	FORCEINLINE class AFGResourceNode* GetResourceNode() const{ return mExtractResourceNode; }

	/** Get the extractable resource interface this miner is extracting from */
	UFUNCTION( BlueprintPure, Category = "Resource" )
	FORCEINLINE TScriptInterface< IFGExtractableResourceInterface > GetExtractableResource() const { return mExtractableResource; }

	/** Get the inventory we output the extracted resources to */
	UFUNCTION( BlueprintPure, Category = "Resource" )
	class UFGInventoryComponent* GetOutputInventory() const{ return mInventoryOutputHandler->GetActiveInventoryComponent(); }

	/** Get the quantity of items mined each production cycle */
	UFUNCTION( BlueprintPure, Category = "Extraction" )
	FORCEINLINE int32 GetNumExtractedItemsPerCycle() const { return mItemsPerCycle; }

	/** Get the quantity of items extracted each cycle converted for displaying in the UI */
	UFUNCTION( BlueprintPure, Category = "Extraction" )
	float GetNumExtractedItemsPerCycleConverted() const;

	/** Set the extractable resource interface this miner is extracting from */
	void SetExtractableResource( TScriptInterface< IFGExtractableResourceInterface > extractableInterface );

	/** Set this resource node as our current, also claiming it */
	void SetResourceNode( class AFGResourceNode* resourceNode );

	/** Get all the allowed resource forms that this resource extractor is allowed to extract */
	FORCEINLINE void GetAllowedResourceForms( TArray<EResourceForm>& out_allowedForms ){ out_allowedForms.Append( mAllowedResourceForms ); }

	/** Does this Miner specify only certain resources to be gathered? */
	FORCEINLINE bool OnlyAllowSpecifiedResources() const { return mOnlyAllowCertainResources; }

	/** Get all resources that are allowed to be mined / pumped. Only relevant if mOnlyAllowCertainResources is marked true. */
	FORCEINLINE void GetAllowedResources( TArray< TSubclassOf< UFGResourceDescriptor > >& out_allowedResources ) { out_allowedResources.Append( mAllowedResources ); }

	/** Gets particle for mining */
	UFUNCTION( BlueprintPure, Category = "Resources" )
	class UParticleSystem* GetMiningParticle();

	/** Are we done with startup animation */
	UFUNCTION( BlueprintPure, Category = "Resources" )
	bool IsStartupComplete();

	/** Get the smoothed flow rate out of the extractor in m^3/s. Only valid for Liquid or Gas extractors */
	UFUNCTION( BlueprintPure, Category = "Pipes" )
	float GetFlowRateSmoothed() const { return mReplicatedFlowRate; }

	/** Return the maximum out flow from inventory to pipeline conversion in m^3/s */
	UFUNCTION( BlueprintPure, Category = "Pipes" )
	float GetMaxFlowRate() const;

	 //type names are used to match types for upgrades and such
	FName GetExtractorTypeName()
	{
		return mExtractorTypeName; 
	}

protected:
	// Begin Factory_ Interface
	virtual void Factory_StartProducing() override;
	virtual void Factory_TickProducing( float dt ) override;
	virtual void Factory_PushPipeOutput_Implementation( float dt ) override;
	// End Factory_ Interface

	virtual void OnRep_ReplicationDetailActor() override;
protected:
	friend class AFGResourceExtractorHologram;
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
	
	/** Can we mine solids, liquids, gases or many of the types. */
	UPROPERTY( EditDefaultsOnly, Category = "Extraction" )
	TArray< EResourceForm > mAllowedResourceForms;

	/**
	 * (For Hologram) Require resource at minimum depth checks? 
	 * If true, this will ensure placement is only allowed where a minimum depth trace collides with the resource class this extractor is snapped to
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Extraction" )
	bool mRequireResourceAtMinimumDepthChecks;
	
	/** (For Hologram) Minimum depth to collision this extractor requires to be placed ( tex. Water Pumps need to be at least X distance above floor ) */
	UPROPERTY( EditDefaultsOnly, Category = "Extraction", meta=( EditCondition="mRequireResourceAtMinimumDepthChecks" ) )
	float mMinimumDepthForPlacement;

	/** Offset from hologram origin to begin and end traces When performing minimum depth checks ( if enabled for this buildable ) during placement */
	UPROPERTY( EditDefaultsOnly, Category = "Extraction", meta=( EditCondition="mRequireResourceAtMinimumDepthChecks" ) )
	FVector mDepthTraceOriginOffset;

	/** Should this extractor only allow extracting from specified resources? 
	* @note - mAllowedResourceForms will still affect placement validation.*/
	UPROPERTY( EditDefaultsOnly, Category = "Extraction" )
	bool mOnlyAllowCertainResources;
	
	/** List of acceptable resources this extractor can mine / pump */
	UPROPERTY( EditDefaultsOnly, Category = "Extraction", meta=( EditCondition="mOnlyAllowCertainResources" ) )
	TArray< TSubclassOf< UFGResourceDescriptor > > mAllowedResources;

	UPROPERTY( EditDefaultsOnly, Category = "Extraction" )
	FVector mExtractionOffset;

	/** Class disqualifier to use when this resource extractor is not placed on a matching resource node ( used in the hologram ) */
	UPROPERTY( EditDefaultsOnly, Category = "Extraction" )
	TSubclassOf< class UFGConstructDisqualifier > mMustPlaceOnResourceDisqualifier;

	/** name used to mathc types of extractros for compatiblility when upgrading */
	UPROPERTY( EditDefaultsOnly, Category = "Extraction" )
	FName mExtractorTypeName = "";
	
	/** Cached property indicating that this Extractor is extracting a non-solid resource. This is used as a replication condition so FlowRate is not included for all extractors */
	bool mIsLiquidOrGasType;

	/** DEPRICATED - Only used for old save support. Use mExtractableResource instead.
	*   The resource node we want to extract from.
	*/
	UPROPERTY( SaveGame, Replicated )
	class AFGResourceNode* mExtractResourceNode;

	UPROPERTY( SaveGame, Replicated )
	AActor* mExtractableResource;

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

	/******** End Pipe Flow Output Params ********/


public:
	FORCEINLINE ~AFGBuildableResourceExtractor() = default;
};
