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
	EDS_NOT_ENOUGH_FUEL			UMETA( displayName = "Not Enough Fuel" ),
	EDS_CANNOT_UNLOAD			UMETA( displayName = "Cannot Unload" )
};

/** Struct containing information about a fuel type, such as estimated roundtrip time. */
USTRUCT( BlueprintType )
struct FFGDroneFuelInformation
{
	GENERATED_BODY()

	FFGDroneFuelInformation()
		: FuelItemDescriptor( nullptr )
		, SingleTripFuelCost( 0.0f )
		, EstimatedFuelCostRate( 0.0f )
		, EstimatedRoundTripTime( 0.0f )
		, EstimatedTransportRate( 0.0f )
	{}

	/** The type of fuel. */
	UPROPERTY( BlueprintReadOnly )
	TSubclassOf< class UFGItemDescriptor > FuelItemDescriptor;

	/** How many items a single trip is gonna cost. */
	UPROPERTY( BlueprintReadOnly )
	float SingleTripFuelCost;

	/** Roughly how many items need to be supplied per minute in order for the drone to not have to ever wait for fuel. The actual cost will be lower than this. */
	UPROPERTY( BlueprintReadOnly )
	float EstimatedFuelCostRate;

	/** Roughly how long time a single trip will take in seconds. */
	UPROPERTY( BlueprintReadOnly )
	float EstimatedRoundTripTime;

	/** Roughly how many items per minute can be delivered with this fuel type. */
	UPROPERTY( BlueprintReadOnly )
	float EstimatedTransportRate;
};

USTRUCT( BlueprintType )
struct FFGDroneTripStatistics
{
	GENERATED_BODY()

public:
	void Clear();

	// Latest RTT
	UPROPERTY( BlueprintReadOnly )
	float LatestRoundTripTime = 0.f;

	// Latest incoming item amount
	UPROPERTY( BlueprintReadOnly )
	int32 LatestIncomingItemAmount = 0;

	// Latest outgoing item amount
	UPROPERTY( BlueprintReadOnly )
	int32 LatestOutgoingItemAmount = 0;

	// Latest incoming item stacks
	UPROPERTY( BlueprintReadOnly )
	float LatestIncomingItemStacks = 0.f;

	// Latest outgoing item stacks
	UPROPERTY( BlueprintReadOnly )
	float LatestOutgoingItemStacks = 0.f;

	// Latest incoming item stack rate
	UPROPERTY( BlueprintReadOnly )
	float LatestIncomingItemStackRate = 0.f;

	// Latest outgoing item stack rate
	UPROPERTY( BlueprintReadOnly )
	float LatestOutgoingItemStackRate = 0.f;

	// Average RTT
	UPROPERTY( BlueprintReadOnly )
	float AverageRoundTripTime = 0.f;

	// Average incoming item amount
	UPROPERTY( BlueprintReadOnly )
	float AverageIncomingItemAmount = 0.f;

	// Average outgoing item amount
	UPROPERTY( BlueprintReadOnly )
	float AverageOutgoingItemAmount = 0.f;

	// Average incoming item stacks
	UPROPERTY( BlueprintReadOnly )
	float AverageIncomingItemStacks = 0.f;

	// Average outgoing item stacks
	UPROPERTY( BlueprintReadOnly )
	float AverageOutgoingItemStacks = 0.f;

	// Average incoming item rate
	UPROPERTY( BlueprintReadOnly )
	float AverageIncomingItemRate = 0.f;

	// Average outgoing item rate
	UPROPERTY( BlueprintReadOnly )
	float AverageOutgoingItemRate = 0.f;

	// Average incoming item stack rate
	UPROPERTY( BlueprintReadOnly )
	float AverageIncomingItemStackRate = 0.f;

	// Average outgoing item stack rate
	UPROPERTY( BlueprintReadOnly )
	float AverageOutgoingItemStackRate = 0.f;

	// Median RTT
	UPROPERTY( BlueprintReadOnly )
	float MedianRoundTripTime = 0.f;

	// Median incoming item amount
	UPROPERTY( BlueprintReadOnly )
	float MedianIncomingItemAmount = 0.f;

	// Median outgoing item amount
	UPROPERTY( BlueprintReadOnly )
	float MedianOutgoingItemAmount = 0.f;

	// Median incoming item stacks
	UPROPERTY( BlueprintReadOnly )
	float MedianIncomingItemStacks = 0.f;

	// Median outgoing item stacks
	UPROPERTY( BlueprintReadOnly )
	float MedianOutgoingItemStacks = 0.f;
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
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FDroneFuelInformationChanged, const TArray< FFGDroneFuelInformation >&, fuelInformation );
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FDroneActiveFuelChanged, TSubclassOf< class UFGItemDescriptor>, newFuelType );
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

	UFUNCTION( BlueprintPure, Category = "Drone Station|Info" )
	const FVector& GetStationLocation() const { return mStationLocation; }

	UFUNCTION( BlueprintCallable, Category = "Drone Station|Info" )
    void PairStation( AFGDroneStationInfo* otherStation );

	UFUNCTION( BlueprintCallable, Category = "Drone Station|Info" )
	void ClearLatestDroneTrips();

	/** Gets the fuel types the drone belonging to the station can use. */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info" )
	TArray< FFGDroneFuelType > GetDroneFuelTypes() const;

	/** Gets the fuel type currently in use by the drone. */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info" )
	FORCEINLINE TSubclassOf< class UFGItemDescriptor > GetDroneActiveFuelType() const { return mActiveDroneFuelType; }
	
	/** Gets the fuel type that was last inserted into the station. */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info" )
	FORCEINLINE TSubclassOf< class UFGItemDescriptor > GetLastInsertedFuelType() const { return mLastInsertedFuelType; }

	/** Gets the fuel information of the currently active fuel of the drone. */
	const FFGDroneFuelInformation* Native_GetActiveFuelInfo() const;

	/** Gets the fuel information of the currently active fuel of the drone. Can contain invalid information if there's no active fuel. */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info" )
	FFGDroneFuelInformation GetActiveFuelInfo() const;

	/** Invoked when the status of the drone attached to this station has changed */
	UPROPERTY( BlueprintAssignable, Category = "Drone Station|Info" )
	FOnDroneStatusChanged DroneStatusChangedDelegate;

	/** Invoked when the information about drone fuel has changed. */
	UPROPERTY( BlueprintAssignable, Category = "Drone Station|Info" )
	FDroneFuelInformationChanged DroneFuelInformationChangedDelegate;

	/** Invoked when the drone of this station has changed its active fuel type. */
	UPROPERTY( BlueprintAssignable, Category = "Drone Station|Info" )
	FDroneActiveFuelChanged DroneActiveFuelChangedDelegate;

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
	
	/** @returns information related to each fuel type of the drone, such as estimated roundtrip time for that fuel type. */
	UFUNCTION( BlueprintPure, Category = "Drone Station|Info|Statistics" )
	FORCEINLINE TArray< FFGDroneFuelInformation > const& GetDroneFuelInformation() const { return mDroneFuelInformation; }

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
	void OnRep_DroneFuelInformation();
	
	UFUNCTION()
    void OnRep_DroneTripStatistics();

	UFUNCTION()
	void OnRep_ActiveDroneFuelType();

	void UpdateDroneFuelInformation();
	
	void UpdateDroneTripStatistics();

	void UpdateActiveDroneFuelType( TSubclassOf< UFGItemDescriptor > fuelItem );

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

	/** Information related to each fuel type of the drone. */
	UPROPERTY( ReplicatedUsing = OnRep_DroneFuelInformation )
	TArray< FFGDroneFuelInformation > mDroneFuelInformation;

	/** The current fuel type used by the drone of this station. */
	UPROPERTY( ReplicatedUsing = OnRep_ActiveDroneFuelType )
	TSubclassOf< class UFGItemDescriptor > mActiveDroneFuelType;

	/** The last fuel type inserted into the station. */
	UPROPERTY( Replicated, SaveGame )
	TSubclassOf< class UFGItemDescriptor > mLastInsertedFuelType;

	UPROPERTY( SaveGame )
	TArray<FDroneTripInformation> mLatestDroneTrips;

	// This is a big struct to replicate, but the alternative is to just replicate the Trip array, which is potentially even more data depending on how many trips we store.
	UPROPERTY( ReplicatedUsing = OnRep_DroneTripStatistics )
	FFGDroneTripStatistics mDroneTripStatistics;
};
