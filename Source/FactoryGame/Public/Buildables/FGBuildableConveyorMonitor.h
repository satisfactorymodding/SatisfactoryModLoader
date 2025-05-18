// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGBuildable.h"
#include "FGBuildableSplineSnappedBase.h"
#include "FGSignificanceInterface.h"
#include "FGBuildableConveyorMonitor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnAverageDataUpdated );

USTRUCT(BlueprintType)
struct FACTORYGAME_API FItemMonitorData
{
	GENERATED_BODY()

	void Reset() { UpdateTime = 0.f; NumItems = 0; }
	
	UPROPERTY( BlueprintReadOnly )
	float  UpdateTime = 0.f;

	UPROPERTY( BlueprintReadOnly )
	int32 NumItems = 0;

	UPROPERTY( BlueprintReadOnly )
	float FloatLocalAverage = 0;
};

USTRUCT( BlueprintType )
struct FACTORYGAME_API FReplicatedCoreBeltThroughputData
{
	GENERATED_BODY()

	UPROPERTY( )
	int32 Average = 0;

	UPROPERTY( )
	float Confidence = 0.f;
};

/**
 * Attaches to conveyors to monitor their effective throughput
 */
UCLASS()
class FACTORYGAME_API AFGBuildableConveyorMonitor : public AFGBuildableSplineSnappedBase, public IFGConditionalReplicationInterface, public IFGSignificanceInterface
{
	GENERATED_BODY()
public:
	AFGBuildableConveyorMonitor();

	//Begin AActor Interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//End AActor Interface

	// Begin IFGUseableInterface
	virtual void RegisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override;
	virtual void UnregisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override;
	// End IFGUseableInterface

	// Begin IFGSignificanceInterface
	virtual float GetSignificanceRange() override;
	virtual void GainedSignificance_Implementation() override;
	virtual void LostSignificance_Implementation() override;
	// End IFGSignificanceInterface
	
	// Begin FGBuildableSplineSnappedBase
	virtual void SetSnappedSplineBuildable(AFGBuildable* buildable) override;
	// End FGBuildableSplineSnappedBase

	virtual void InitializeOffset( bool forceUpdate = false );

	UFUNCTION( BlueprintPure, Category="ConveyorMonitor" )
	AFGBuildableConveyorBase* GetConveyorBase();
	
	UFUNCTION( BlueprintPure, Category="ConveyorMonitor" )
	float GetOffsetAlongConveyor() const { return mOffsetAlongConveyor; }

	UFUNCTION( BlueprintPure, Category="ConveyorMonitor" )
	TArray< FItemMonitorData > GetAverageDataForUIRepresentation();

	UFUNCTION( BlueprintPure, Category="ConveyorMonitor" )
	float GetTimePerAverageSection() const { return mTimePerAverageSectionFromBeltSpeed; }

	UFUNCTION( BlueprintPure, Category="ConveyorMonitor" )
	float GetMaxTotalAverageDuration() const { return TOTAL_AVERAGE_DURATION; }

	// Generates the averaging values to be used based on the type of belt we are on
	void SetupMonitorData();

	// Averages all available data and calculates the item througput rate
	void CalculateItemsPerMinute();

	void UpdatePassedTimeAndItems( double time, int32 numItems );

	UFUNCTION( BlueprintPure, Category="ConveyorMonitor" )
	int32 GetCalculatedAverage() const { return mCalculatedItemsPerMinute; }

	UFUNCTION( BlueprintPure, Category="ConveyorMonitor" )
	float GetConfidence() const { return mConfidence; } 
	
	
	/**
	 * Event is triggered when the calculated item throughput rate changes. The item throughput is calculated a little differently if the confidence is less than 100.
	 * This is done so that any hiccups at the initial rebuild of the belt (which is a common issue) get exclude early on. Otherwise it could take a long time
	 * for the average item rate to accurately reflect the effective rate.
	 * @param itemsPerMin Num Items per minute
	 * @param confidence A percentage of how "accurate" the data is. If 0 then we have not calculated any average data. If 100 then we have completely filled our average data array collection
	 */
	UFUNCTION( BlueprintImplementableEvent, Category="ConveyorMonitor")
	void OnItemThroughputUpdated( int32 itemsPerMin, float confidence );

	/** Can be used to trigger a data reset Tex. from UI if so desired. */
	UFUNCTION( BlueprintCallable, Category="ConveyorMonitor")
	void PlayerResetMonitorData();
	
	void ResetMonitorData( AFGConveyorChainActor* chainActor );

	UFUNCTION()
	void OnRep_ReplicatedCoreData();

	UFUNCTION()
	void OnRep_MonitorData();
	
	UFUNCTION( BlueprintImplementableEvent, Category="ConveyorMonitor" )
	void OnAverageDataUpdated();

private:
	void DebugPrintData() const;

public:
	virtual void GetConditionalReplicatedProps( TArray<FFGCondReplicatedProperty>& outProps ) const override;
	virtual bool IsPropertyRelevantForConnection( UNetConnection* netConnection, const FProperty* property ) const override;

public:
	UPROPERTY( BlueprintAssignable, Category="ConveyorMonitor")
	FOnAverageDataUpdated OnAverageDataUpdatedDelegate;
	
	UPROPERTY( BlueprintReadOnly, Category="Significance")
	bool mIsSignificant;
	
private:
	/** Transient struct handling the conditional replication of full average data */
	UPROPERTY( Replicated, Transient, meta = ( FGPropertyReplicator ) )
	FFGConditionalPropertyReplicator mPropertyReplicator;
	
	// Set by the chain actor calling reset on this monitor. We have special logic to adjust averaging times depending on chain layout
	UPROPERTY()
	AFGConveyorChainActor* mChainActor;
	
	// Cached cast ConveyorBase from parent snapped spline buildable. Not saved because the parent class saves the snapped buildable
	UPROPERTY()
	AFGBuildableConveyorBase* mConveyorBase;

	UPROPERTY( meta = ( NoAutoJson = true, FGReplicated ) )
	float mTimePerAverageSectionFromBeltSpeed;
	
	UPROPERTY( meta = ( NoAutoJson = true, FGReplicated ) )
	int32 mNumAverageSections;
	
	UPROPERTY( SaveGame )
	float mOffsetAlongConveyor = -1.f;
	
	UPROPERTY()
	int32 mCalculatedItemsPerMinute = -1;
	
	UPROPERTY()
	int32 mTotalItems = 0;
	UPROPERTY()
	float mTotalTime = 0;

#if !UE_BUILD_SHIPPING
	int32 mNumExpectedItemsPerSection;
#endif
	
	// Percentage of Average sections that have been tallied. After all sections have been filled this will be 100%
	UPROPERTY()
	float mConfidence = 0.f;

	// Struct for replicating the data so we can trigger via a single on rep
	UPROPERTY( ReplicatedUsing=OnRep_ReplicatedCoreData )
	FReplicatedCoreBeltThroughputData mReplicatedCoreData;

	UPROPERTY( meta = ( NoAutoJson = true, FGReplicated ) )
	int32 mCurrentDataIndex = 0;
	
	static constexpr float DEFAULT_TIME_PER_AVERAGE_SECTION = 2.f; // Update every 2 seconds
	static constexpr int32 TOTAL_AVERAGE_DURATION = 60; // In Seconds

	UPROPERTY( meta = ( NoAutoJson = true, FGReplicatedUsing = OnRep_MonitorData ) )
	TArray< FItemMonitorData > mMonitorData;

	UPROPERTY( EditDefaultsOnly, Category="Significance")
	float mSignificanceRange;

};