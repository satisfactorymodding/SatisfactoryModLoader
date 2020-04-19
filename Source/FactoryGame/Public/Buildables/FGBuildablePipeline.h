// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "../../Plugins/Wwise/Source/AkAudio/Classes/AkAudioEvent.h"
#include "Array.h"
#include "UnrealString.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "../FGFluidIntegrantInterface.h"
#include "FGBuildablePipeBase.h"
#include "FGBuildablePipeline.generated.h"


/**
 * Struct containing quantized fluid content for a more optimized replication.
 */
USTRUCT()
struct FACTORYGAME_API FQuantizedPipelineIndicatorData
{
	GENERATED_BODY()
public:
	void SetFlowPct( float pct );
	float GetFlowPct() const;

	void SetContentPct( float pct );
	float GetContentPct() const;

private:
	/** See setters for how this data is packed. */
	UPROPERTY()
	int8 PackedFlow = 0;
	UPROPERTY()
	uint8 PackedContent = 0;

public:
	FORCEINLINE ~FQuantizedPipelineIndicatorData() = default;
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FStringPair
{
	GENERATED_BODY()
public:
	FStringPair() :
		WwiseSafeName( TEXT( "N/A" ) ),
		ActualName( TEXT( "N/A" ) )
	{}

	UPROPERTY( EditDefaultsOnly, Category = "String Pair" )
	FString WwiseSafeName;

	UPROPERTY( EditDefaultsOnly, Category = "String Pair" )
	FString ActualName;

public:
	FORCEINLINE ~FStringPair() = default;
};

/**
 * Pipeline for transferring liquid and gases to factory buildings.
 */
UCLASS()
class FACTORYGAME_API AFGBuildablePipeline : public AFGBuildablePipeBase, public IFGFluidIntegrantInterface
{
	GENERATED_BODY()
public:
	AFGBuildablePipeline();

	// Begin Actor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	virtual void Tick( float dt ) override;
	// End Actor Interface 

	// Begin AFGBuildable interface
	virtual void Factory_Tick( float dt ) override;
	virtual void Native_OnMaterialInstancesUpdated() override;
	// End AFGBuildable interface

	// Begin Significance
	virtual void GainedSignificance_Implementation() override;
	virtual void LostSignificance_Implementation() override;
	// End Significance

	// Begin AFGBuildablePipeBase Interface
	virtual TSubclassOf< UFGPipeConnectionComponentBase > GetConnectionType_Implementation() override;
	// End AFGBuildablePipeBase Interface

	// Begin FluidIntegrant Interface
	virtual FFluidBox* GetFluidBox() override;
	virtual TArray< class UFGPipeConnectionComponent* > GetPipeConnections() override;
	virtual void OnFluidDescriptorSet() override;
	// End FluidIntegrant Interface

	/**
	 * Split this pipeline in two.
	 * Copied from the conveyor splitting, some modifications
	 * First part [0,offset] and second part [offset,length].
	 * @note Callee is responsible for not creating snakes or 'zero belts'.
	 *       I.e. Do not split to close to the beginning or end.
	 *		 Will dismantle the current pipeline on successful split
	 * @param connectNewPipelines - Should the new pipelines be connected to each other after the split
	 * @return The second part of the splitted pipeline; nullptr on failure to split.
	 */
	static TArray< AFGBuildablePipeline* > Split( AFGBuildablePipeline* pipeline, float offset, bool connectNewPipelines, AActor* instigator = nullptr  );

	/**
	 * Merge two pipelines.
	 * Copied from conveyor splitting, some modifications
	 * @return The merged pipeline; nullptr on failure to merge.
	 */
	static AFGBuildablePipeline* Merge( TArray< AFGBuildablePipeline* > pipelines, AActor* instigator = nullptr );

	/** Get this pipes first connection, can be assumed to not be null. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Pipeline" )
	class UFGPipeConnectionComponent* GetPipeConnection0() const { return mPipeConnections[ 0 ]; }
	/** Get this pipes first connection, can be assumed to not be null. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Pipeline" )
	class UFGPipeConnectionComponent* GetPipeConnection1()  const { return mPipeConnections[ 1 ]; }

	/** Get the replicated content of the pipe in the range [0, 1] and then 1+ if the pipe is over-pressurized. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Pipeline" )
	float GetIndicatorContentPct() const;

	/** Get the replicated flow of the pipe in the range [-1, 1] */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Pipeline" )
	float GetIndicatorFlowPct() const;

	/** Get the replicated content [m^3] of the pipe in the range [0, MAX]. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Pipeline" )
	float GetIndicatorContent() const;

	/** Get the maximum content [m^3]. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Pipeline" )
	float GetMaxContent() const { return mFluidBox.MaxContent; }

	/** Get the replicated flow [m^3/s] of the pipe in the range [-LIMIT, LIMIT]. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Pipeline" )
	float GetIndicatorFlow() const;

	/** Get the maximum flow of the pipe [m^3/s]. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Pipeline" )
	float GetFlowLimit() const { return mFlowLimit; }

	/** Get fluid descriptor for this pipe. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Pipeline" )
	TSubclassOf< UFGItemDescriptor > GetFluidDescriptor() const;

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Pipes|Pipeline" )
	class UFGPipelineFlowIndicatorComponent* GetFlowIndicatorComponent() const;

	/** 
	* @todoPipes DEPRICATED - Invoke server call on Remote Call Object instead. 
	* Call this to flush the network.
	*/
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Pipes|Pipeline", meta=( DeprecatedFunction, DeprecationMessage = "Invoke server call on Remote Call Object instead." ) )
	void FlushPipeNetwork();

	/** Adds an actor to ignore when determining indicator placement in begin play. This needs to be called BEFORE begin play to have any effect */
	void AddIgnoredActorForIndicator( AActor* ignoredActor ) { mIgnoreActorsForIndicator.Add( TWeakObjectPtr< const AActor>( ignoredActor ) ); }

	/** Updates sounds depending on liquid in pipe */
	void UpdateSounds();
private:
	/** Attempts to find a suitable location to place the indicator
	*	@param out_transform Transform of the suitable location to place the indicator
	*	@return True if a suitable location was found. False otherwise.
	*/
	bool FindBestInidicatorPlacement( FTransform& out_transform );
public:
	/** Inner Radius of this pipe. Used for flow calculations. [cm] */
	UPROPERTY( EditDefaultsOnly, Category = "Pipeline" )
	float mRadius;

	/** Maximum flow through this pipe in cubic meters. [m^3/s] */
	UPROPERTY( EditDefaultsOnly, Category = "Pipeline" )
	float mFlowLimit;

	/** Type of indicator to spawn on this pipe. */
	UPROPERTY( EditDefaultsOnly, Category = "Pipeline" )
	TSubclassOf< class UFGPipelineFlowIndicatorComponent > mFlowIndicatorClass;

	/** Smaller pipes than this will not get a flow indicator. [cm] */
	UPROPERTY( EditDefaultsOnly, Category = "Pipeline" )
	float mFlowIndicatorMinimumPipeLength;

	/** The indicator spawned for this pipe, this is optional and can be null. */
	TWeakObjectPtr< UFGPipelineFlowIndicatorComponent > mFlowIndicator;

	/** 
	* FNames for pipeline connection components. These must match the component names of the components that are added via blueprint 
	* The reason they are added in BP and not natively is some support for HyperTubes and Pipelines ( Gafgar would have a better idea why so I won't attempt to remember here )
	* They are used for detecting reversal when merging two pipelines to check if the components were hooked in reverse order (Tex. the pump was flipped )
	*/
	static FName mConnectionName0;
	static FName mConnectionName1;
	
protected:
	UPROPERTY( BlueprintReadOnly, Category = "Audio" )
	class UFGSoundSplineComponent* mSoundSplineComponent;

	/** The ak event to post for the sound spline */
	UPROPERTY( EditDefaultsOnly, Category = "Audio" )
	class UAkAudioEvent* mSplineAudioEvent;

private:
	/** Cached array of pipe connections. */
	UPROPERTY()
	TArray< class UFGPipeConnectionComponent* > mPipeConnections;

	/** Simulation data. */
	UPROPERTY( SaveGame )
	FFluidBox mFluidBox;

	/** Quantized data used by the indicators. */
	UPROPERTY( Replicated )
	FQuantizedPipelineIndicatorData mIndicatorData;

	/** Smoothed values used by the indicators/UI. */
	float mIndicatorFlowPct;
	float mIndicatorContentPct;

	UPROPERTY( EditDefaultsOnly, Category = "Pipeline" )
	float mMaxIndicatorTurnAngle;

	UPROPERTY()
	TSubclassOf< UFGItemDescriptor > mCachedFluidDescriptor; 

	// Array of objects to ignore when performing the collision check in the indicator placement. This is needed during merge / split creation of new pipelines
	UPROPERTY()
	TArray< TWeakObjectPtr< const AActor > > mIgnoreActorsForIndicator;

	/** struct with both wwise safe names and their item names */
	UPROPERTY( EditDefaultsOnly, Category = "Pipeline" )
	TArray< FStringPair > mFluidNames;

	/** current fluid that is in the pipe */
	UPROPERTY()
	FString mCurrentFluid;

	/** how filled is the pipe */
	UPROPERTY()
	float mQuantiziedContent;

	/** flow rate in the pipe */
	UPROPERTY()
	float mQuantiziedFlow;

	/** at what flow should we play rattle */
	UPROPERTY( EditDefaultsOnly, Category = "Pipeline" )
	float mRattleLimit;

	/** are we playing rattling sound? */
	UPROPERTY()
	bool mIsRattling;

	/** Start rattle sound */
	UPROPERTY( EditDefaultsOnly, Category = "Pipeline" )
	class UAkAudioEvent* mStartRattleSoundEvent;

	/** Stop rattle sound */
	UPROPERTY( EditDefaultsOnly, Category = "Pipeline" )
	class UAkAudioEvent* mStopRattleSoundEvent;

public:
	FORCEINLINE ~AFGBuildablePipeline() = default;
};
