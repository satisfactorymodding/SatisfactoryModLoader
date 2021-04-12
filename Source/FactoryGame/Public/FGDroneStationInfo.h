// Copyright 2020 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "GameFramework/Info.h"
#include "FGSaveInterface.h"
#include "FGBuildingTagInterface.h"
#include "FGDroneVehicle.h"

#include "FGDroneStationInfo.generated.h"

UENUM( BlueprintType )
enum class EDroneStatus : uint8
{
	EDS_NO_DRONE				UMETA( displayName = "No Drone" ),
	EDS_DOCKED					UMETA( displayName = "Docked" ),
	EDS_LOADING					UMETA( displayName = "Loading" ),
	EDS_TAKEOFF					UMETA( displayName = "Takeoff" ),
	EDS_EN_ROUTE				UMETA( displayName = "En Route" ),
	EDS_DOCKING					UMETA( displayName = "Docking" ),
	EDS_UNLOADING				UMETA( displayName = "Unloading" ),
	EDS_NOT_ENOUGH_BATTERIES	UMETA( displayName = "Not Enough Batteries" ),
	EDS_CANNOT_UNLOAD			UMETA( displayName = "Cannot Unload" )
};

USTRUCT( BlueprintType )
struct FFGDroneTripStatistics
{
	GENERATED_BODY()

public:
	void Clear();

	// Latest RTT
	UPROPERTY( BlueprintReadOnly )
	float LatestRoundTripTime;

	// Latest incoming item amount
	UPROPERTY( BlueprintReadOnly )
	int32 LatestIncomingItemAmount;

	// Latest outgoing item amount
	UPROPERTY( BlueprintReadOnly )
	int32 LatestOutgoingItemAmount;

	// Latest incoming item stacks
	UPROPERTY( BlueprintReadOnly )
	float LatestIncomingItemStacks;

	// Latest outgoing item stacks
	UPROPERTY( BlueprintReadOnly )
	float LatestOutgoingItemStacks;

	// Latest incoming item stack rate
	UPROPERTY( BlueprintReadOnly )
	float LatestIncomingItemStackRate;

	// Latest outgoing item stack rate
	UPROPERTY( BlueprintReadOnly )
	float LatestOutgoingItemStackRate;

	// Average RTT
	UPROPERTY( BlueprintReadOnly )
	float AverageRoundTripTime;

	// Average incoming item amount
	UPROPERTY( BlueprintReadOnly )
	float AverageIncomingItemAmount;

	// Average outgoing item amount
	UPROPERTY( BlueprintReadOnly )
	float AverageOutgoingItemAmount;

	// Average incoming item stacks
	UPROPERTY( BlueprintReadOnly )
	float AverageIncomingItemStacks;

	// Average outgoing item stacks
	UPROPERTY( BlueprintReadOnly )
	float AverageOutgoingItemStacks;

	// Average incoming item rate
	UPROPERTY( BlueprintReadOnly )
	float AverageIncomingItemRate;

	// Average outgoing item rate
	UPROPERTY( BlueprintReadOnly )
	float AverageOutgoingItemRate;

	// Average incoming item stack rate
	UPROPERTY( BlueprintReadOnly )
	float AverageIncomingItemStackRate;

	// Average outgoing item stack rate
	UPROPERTY( BlueprintReadOnly )
	float AverageOutgoingItemStackRate;

	// Median RTT
	UPROPERTY( BlueprintReadOnly )
	float MedianRoundTripTime;

	// Median incoming item amount
	UPROPERTY( BlueprintReadOnly )
	float MedianIncomingItemAmount;

	// Median outgoing item amount
	UPROPERTY( BlueprintReadOnly )
	float MedianOutgoingItemAmount;

	// Median incoming item stacks
	UPROPERTY( BlueprintReadOnly )
	float MedianIncomingItemStacks;

	// Median outgoing item stacks
	UPROPERTY( BlueprintReadOnly )
	float MedianOutgoingItemStacks;
};

/**
 * The part of a drone station that is always available on server and clients.
 */
UCLASS()
class FACTORYGAME_API AFGDroneStationInfo : public AInfo, public IFGSaveInterface, public IFGBuildingTagInterface
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnDroneStatusChanged, EDroneStatus, droneStatus );
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnEstimatedRoundTripTimeChanged, float, estimatedRoundTripTime );
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnEstimatedTransportRateChanged, int32, estimatedTransportRate );
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnDroneTripStatisticsChanged, FFGDroneTripStatistics, droneTripStatistics );

public:
	AFGDroneStationInfo();

	// Begin AActor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	// End AActor Interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface
	
	//~ Begin FGBuildingTagInterface
	virtual bool HasBuildingTag_Implementation() const override { return true; }
	virtual void SetHasBuildingTag_Implementation( bool hasBuildingTag ) override { }
	virtual FString GetBuildingTag_Implementation() const override { return mBuildingTag; }
	virtual void SetBuildingTag_Implementation( const FString& buildingTag ) override;
	//~ End FGBuildingTagInterface

	/** @returns the status of the drone attached to this station */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info" )
	EDroneStatus GetDroneStatus() const { return mDroneStatus; }

	UFUNCTION( BlueprintPure, Category = "Drone Station|Info" )
	AFGDroneStationInfo* GetPairedStation() const { return mPairedStation; }

	/** @returns all the stations connected to this one. */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info" )
    TArray< AFGDroneStationInfo* > GetConnectedStations() const { return mConnectedStations; }

	UFUNCTION( BlueprintCallable, Category = "Drone Station|Info" )
    void PairStation( AFGDroneStationInfo* otherStation );

	UFUNCTION( BlueprintCallable, Category = "Drone Station|Info" )
	void ClearLatestDroneTrips();

	/** @returns the estimated number of batteries required per minute in order to cover the roundtrips without stalling. Actual requirement will be lower than this. */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info" )
    float GetEstimatedBatteryRequirementRate() const;
	
	/** @returns the number of batteries a trip between this station and the paired station will cost. */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info" )
	int32 GetTripCostInBatteries() const;

	/** Invoked when the status of the drone attached to this station has changed */
	UPROPERTY( BlueprintAssignable, Category = "Drone Station|Info" )
	FOnDroneStatusChanged DroneStatusChangedDelegate;

	/** Invoked when the estimated round-trip time of the drone attached to this station has changed */
	UPROPERTY( BlueprintAssignable, Category = "Drone Station|Info" )
	FOnEstimatedRoundTripTimeChanged EstimatedRoundTripTimeChangedDelegate;

	/** Invoked when the estimated round-trip time of the drone attached to this station has changed */
	UPROPERTY( BlueprintAssignable, Category = "Drone Station|Info" )
	FOnEstimatedTransportRateChanged EstimatedTransportRateChangedDelegate;

	/** Invoked when the drone trip statistics have changed. */
	UPROPERTY( BlueprintAssignable, Category = "Drone Station|Info" )
	FOnDroneTripStatisticsChanged DroneTripStatisticsChangedDelegate;

	/** Server-only access to the actual station */
	class AFGBuildableDroneStation* GetStation() const { return mStation; }

	void SetDroneStatus( EDroneStatus droneStatus );

	float CalculateStationTripPowerCost( AFGDroneStationInfo* ToStation ) const;

	void RegisterDroneTripInformation( const FDroneTripInformation& TripInfo );

	/** STATISTICS GETTERS */
	// TODO Tobias: All of these statistics are starting to get kind of messy, refactor them later once design is settled
	
	/** @returns the number of stacks this station receives per minute, including connected stations, using the most recent trip for each station if available, otherwise uses estimate. */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info|Statistics" )
    float GetLatestEstimatedTotalIncomingItemStackRate() const;

	/** @returns the average number of items this station receives per minute, including connected stations. */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info|Statistics" )
    float GetAverageTotalIncomingItemRate() const;

	/** @returns the average number of item stacks this station receives per minute, including connected stations. */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info|Statistics" )
    float GetAverageTotalIncomingItemStackRate() const;

	/** @returns the number of stacks this station sends away per minute, including connected stations, using the most recent trip for each station if available, otherwise uses estimate. */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info|Statistics" )
    float GetLatestEstimatedTotalOutgoingItemStackRate() const;

	/** @returns the average number of items this station sends away per minute, including connected stations. */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info|Statistics" )
    float GetAverageTotalOutgoingItemRate() const;

	/** @returns the average number of item stacks this station sends away per minute, including connected stations. */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info|Statistics" )
    float GetAverageTotalOutgoingItemStackRate() const;

	/** @returns the estimated number of stacks this station can send away / receive per minute, including drones from connected stations. */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info|Statistics" )
    float GetEstimatedTotalTransportRate() const;
	
	/** @returns the estimated number of stacks the drone attached to this station can carry per minute */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info|Statistics" )
	FORCEINLINE float GetEstimatedTransportRate() const { return mEstimatedTransportRate; }
	
	/** @returns the estimated round-trip time of the drone attached to this station */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info|Statistics" )
	FORCEINLINE float GetEstimatedRoundTripTime() const { return mEstimatedRoundTripTime; }

	/** @returns the latest round-trip time of the drone attached to this station */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info|Statistics" )
    FORCEINLINE float GetLatestRoundTripTime() const { return mDroneTripStatistics.LatestRoundTripTime; }

	/** @returns the latest trip incoming item amount of the drone attached to this station */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info|Statistics" )
    FORCEINLINE int32 GetLatestTripIncomingItemAmount() const { return mDroneTripStatistics.LatestIncomingItemAmount; }

	/** @returns the latest trip outgoing item amount of the drone attached to this station */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info|Statistics" )
    FORCEINLINE int32 GetLatestTripOutgoingItemAmount() const { return mDroneTripStatistics.LatestOutgoingItemAmount; }

	/** @returns the latest trip's amount of incoming item stacks transferred per minute. */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info|Statistics" )
    FORCEINLINE float GetLatestIncomingItemStackRate() const { return mDroneTripStatistics.LatestIncomingItemStackRate; }

	/** @returns the latest trip's amount of outgoing item stacks transferred per minute. */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info|Statistics" )
    FORCEINLINE float GetLatestOutgoingItemStackRate() const { return mDroneTripStatistics.LatestOutgoingItemStackRate; }

	/** @returns the average round-trip time of the drone attached to this station based on the last few trips. */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info|Statistics" )
    FORCEINLINE float GetAverageRoundTripTime() const { return mDroneTripStatistics.AverageRoundTripTime; }

	/** @returns the average trip incoming item amount of the drone attached to this station */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info|Statistics" )
    FORCEINLINE float GetAverageTripIncomingItemAmount() const { return mDroneTripStatistics.AverageIncomingItemAmount; }

	/** @returns the average trip outgoing item amount of the drone attached to this station */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info|Statistics" )
    FORCEINLINE float GetAverageTripOutgoingItemAmount() const { return mDroneTripStatistics.AverageOutgoingItemAmount; }

	/** @returns the average amount of incoming items transferred per minute based on previous trips. */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info|Statistics" )
    FORCEINLINE float GetAverageIncomingItemRate() const { return mDroneTripStatistics.AverageIncomingItemRate; }

	/** @returns the average amount of outgoing items transferred per minute based on previous trips. */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info|Statistics" )
    FORCEINLINE float GetAverageOutgoingItemRate() const { return mDroneTripStatistics.AverageOutgoingItemRate; }

	/** @returns the average amount of incoming item stacks transferred per minute based on previous trips. */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info|Statistics" )
    FORCEINLINE float GetAverageIncomingItemStackRate() const { return mDroneTripStatistics.AverageIncomingItemStackRate; }

	/** @returns the average amount of outgoing item stacks transferred per minute based on previous trips. */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info|Statistics" )
    FORCEINLINE float GetAverageOutgoingItemStackRate() const { return mDroneTripStatistics.AverageOutgoingItemStackRate; }
	
	/** @returns the median round-trip time of the drone attached to this station based on the last few trips. */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info|Statistics" )
    FORCEINLINE float GetMedianRoundTripTime() const { return mDroneTripStatistics.MedianRoundTripTime; }

	/** @returns the median trip incoming item amount of the drone attached to this station */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info|Statistics" )
    FORCEINLINE float GetMedianTripIncomingItemAmount() const { return mDroneTripStatistics.MedianIncomingItemAmount; }

	/** @returns the median trip outgoing item amount of the drone attached to this station */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info|Statistics" )
    FORCEINLINE float GetMedianTripOutgoingItemAmount() const { return mDroneTripStatistics.MedianOutgoingItemAmount; }

	/** END STATISTICS GETTERS */

protected:
	/** Called when paired station changes. newStation can be nullptr. */
	UFUNCTION( BlueprintNativeEvent, Category = "Drone Station|Info" )
    void OnPairedStationUpdate();

	UFUNCTION()
	void OnPairedStationDestroyed( AActor* destroyedActor );

private:
	UFUNCTION()
	void OnRep_DroneStatus();

	UFUNCTION()
	void OnRep_EstimatedRoundTripTime();

	UFUNCTION()
	void OnRep_EstimatedTransportRate();

	UFUNCTION()
    void OnRep_DroneTripStatistics();

	void CalculateEstimatedRoundTripTime();
	void CalculateEstimatedTransportRate();
	
	void UpdateDroneTripStatistics();

	/** Called when a station pairs up with this one. */
	void AddConnectedStation( AFGDroneStationInfo* otherStation );
	void RemoveConnectedStation( AFGDroneStationInfo* otherStation );

private:
	friend class AFGBuildableDroneStation;
	friend class AFGDroneSubsystem;

	/** The station this info represents. */
	UPROPERTY( SaveGame )
	class AFGBuildableDroneStation* mStation;

	/** Info objects cannot have a location, so in order to keep track of the station location on both client and server we'll just cache it and replicate it. */
	UPROPERTY( Replicated )
	FVector mStationLocation;

	UPROPERTY( Replicated )
	TSubclassOf< AFGBuildableDroneStation > mStationClass;

	UPROPERTY( SaveGame, Replicated )
	AFGDroneStationInfo* mPairedStation;

	/** Stations which are connected to this one */
	UPROPERTY( Replicated )
	TArray<AFGDroneStationInfo*> mConnectedStations;

	UPROPERTY( SaveGame, Replicated )
	FString mBuildingTag;

	UPROPERTY( ReplicatedUsing = OnRep_DroneStatus )
	EDroneStatus mDroneStatus;

	UPROPERTY( ReplicatedUsing = OnRep_EstimatedRoundTripTime )
	float mEstimatedRoundTripTime;

	UPROPERTY( ReplicatedUsing = OnRep_EstimatedTransportRate )
	float mEstimatedTransportRate;

	UPROPERTY( SaveGame )
	TArray<FDroneTripInformation> mLatestDroneTrips;

	// This is a big struct to replicate, but the alternative is to just replicate the Trip array, which is potentially even more data depending on how many trips we store.
	UPROPERTY( ReplicatedUsing = OnRep_DroneTripStatistics )
	FFGDroneTripStatistics mDroneTripStatistics;
};
