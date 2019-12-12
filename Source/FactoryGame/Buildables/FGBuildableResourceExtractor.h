// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/CoreNet.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGBuildableFactory.h"
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

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	// End AActor interface 

	// Begin AFGBuildableFactory interface
	virtual bool CanProduce_Implementation() const override;
	virtual float GetProductionCycleTime() const override;
	virtual float GetProductionProgress() const override;
	virtual float CalcProductionCycleTimeForPotential( float potential ) const override;
	// End AFGBuildableFactory interface

	/** Get the resource node this miner is mining from. */
	UFUNCTION( BlueprintPure, Category = "Resource" )
	FORCEINLINE class AFGResourceNode* GetResourceNode() const{ return mExtractResourceNode; }

	/** Get the inventory we output the extracted resources to */
	UFUNCTION( BlueprintPure, Category = "Resource" )
	class UFGInventoryComponent* GetOutputInventory() const{ return mOutputInventory; }

	/** Set this resource node as our current, also claiming it */
	void SetResourceNode( class AFGResourceNode* resourceNode );

	/** Get all the allowed resource forms that this resource extractor is allowed to extract */
	FORCEINLINE void GetAllowedResourceForms( TArray<EResourceForm>& out_allowedForms ){ out_allowedForms.Append( mAllowedResourceForms ); }

	/** Gets particle for mining */
	UFUNCTION( BlueprintPure, Category = "Resources" )
	class UParticleSystem* GetMiningParticle();

	/** Are we done with startup animation */
	UFUNCTION( BlueprintPure, Category = "Resources" )
	bool IsStartupComplete();
protected:
	// Begin Factory_ Interface
	virtual void Factory_StartProducing() override;
	virtual void Factory_TickProducing( float dt ) override;
	// End Factory_ Interface

protected:
	/** Power up time for the extraction process, e.g. the time it takes for a drill to start spinning. */
	UPROPERTY( EditDefaultsOnly, Replicated, Category = "Extraction" )
	float mExtractStartupTime;

	/** How long does it take to complete one mining cycle. In seconds. */
	UPROPERTY( EditDefaultsOnly, Category = "Extraction", meta = (ClampMin = "0.0001") )
	float mExtractCycleTime;

	/** Can we mine solids, liquids, gases or many of the types. */
	UPROPERTY( EditDefaultsOnly, Category = "Extraction" )
	TArray< EResourceForm > mAllowedResourceForms;

	UPROPERTY( EditDefaultsOnly, Category = "Extraction" )
	FVector mExtractionOffset;

	/** The resource node we want to extract from */
	UPROPERTY( SaveGame, Replicated )
	class AFGResourceNode* mExtractResourceNode;

	/** Current extract progress in the range [0, 1] */
	UPROPERTY( Replicated, SaveGame, Meta = (NoAutoJson = true) )
	float mCurrentExtractProgress;

	/** Our output inventory, */
	UPROPERTY( SaveGame, Replicated )
	class UFGInventoryComponent* mOutputInventory;
};
