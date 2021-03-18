// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildableResourceExtractorBase.h"
#include "Resources/FGResourceNodeFrackingCore.h"
#include "FGBuildableFrackingActivator.generated.h"

/**
 * Factory building that must be placed on an AFGResourceNodeFrackingCore node.
 * Its purpose is then to activate the AFGResourceNodeFrackingSatellite nodes that depend on said core node.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableFrackingActivator : public AFGBuildableResourceExtractorBase
{
	GENERATED_BODY()
	
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnCurrentPotentialChanged, float, currentPotentialChanged );
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnConnectedExtractorCountChanged, int, connectedExtractorCount );

public:
	AFGBuildableFrackingActivator();

	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	/** Invoked when overclocking has changed on this activator */
	UPROPERTY( BlueprintAssignable, Category = "Fracking" )
	FOnCurrentPotentialChanged CurrentPotentialChangedDelegate;

	/** @returns the number of satellites nodes connected to this activator */
	UFUNCTION( BlueprintPure, Category = "Fracking" )
	int GetSatelliteNodeCount() const { return mSatelliteNodeCount; }

	/** @returns the number of extractors connected to this activator */
	UFUNCTION( BlueprintPure, Category = "Fracking" )
	int GetConnectedExtractorCount() const { return mConnectedExtractorCount; }

	/** Invoked when the number of extractors connected to this activator has changed */
	UPROPERTY( BlueprintAssignable, Category = "Fracking" )
	FOnConnectedExtractorCountChanged ConnectedExtractorCountChangedDelegate;

	/** @returns the non-overclocked potential per-minute rate of extraction of all the extractors connected to this activator combined */
	UFUNCTION( BlueprintPure, Category = "Fracking" )
	float GetDefaultPotentialExtractionPerMinute() const { return mDefaultPotentialExtractionPerMinute; }

	/** @returns the potential per-minute rate of extraction of all the extractors connected to this activator combined */
	UFUNCTION( BlueprintPure, Category = "Fracking" )
	float GetPotentialExtractionPerMinute() const;

	/** One of the connected satellite nodes has had an extractor placed or removed */
	void OnExtractorSet();

protected:
	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin Factory_ Interface
	virtual void Factory_StartProducing() override;
	virtual void Factory_TickProducing( float dt ) override;
	virtual void Factory_StopProducing() override;
	// End Factory_ Interface

	// Begin AFGBuildableFactory interface
	virtual void SetPendingPotential( float newPendingPotential ) override;
	virtual void OnRep_CurrentPotential() override;
	// End AFGBuildableFactory interface

	// Begin AFGBuildableResourceExtractorBase interface
	virtual void OnExtractableResourceSet() override;
	// End AFGBuildableResourceExtractorBase interface

private:
	void CalculateConnectedExtractorCount();
	void CalculateDefaultPotentialExtractionPerMinute();

	bool AreAllNodesActivated() const;

	UFUNCTION()
	void OnRep_ConnectedExtractorCount();

private:
	/** Time it takes for this activator to activate the satellite nodes, from production start, in seconds. */
	UPROPERTY( EditDefaultsOnly, Category = "Extraction" )
	float mActivationStartupTime;

	/** Time left until the satellite-activation process is complete. */
	UPROPERTY()
	float mActivationStartupTimer;

	/** True if the satellite-activation process is complete, false otherwise. */
	UPROPERTY( SaveGame )
	bool mSatelliteActivationComplete = false;

	TWeakObjectPtr< AFGResourceNodeFrackingCore > mCoreNode;

	UPROPERTY( Replicated )
	int mSatelliteNodeCount;

	UPROPERTY( ReplicatedUsing = OnRep_ConnectedExtractorCount )
	int mConnectedExtractorCount;
	
	UPROPERTY( Replicated )
	float mDefaultPotentialExtractionPerMinute;

	UPROPERTY( EditDefaultsOnly, Category = "Extraction" )
	const TSubclassOf< class AFGBuildableFrackingExtractor > mExtractorClass;

	UPROPERTY()
	const class AFGBuildableFrackingExtractor* mDefaultExtractor;
};
