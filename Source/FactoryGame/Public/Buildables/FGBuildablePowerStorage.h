// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Buildables/FGBuildableFactory.h"
#include "FGBuildablePowerStorage.generated.h"

UENUM( BlueprintType )
enum class EBatteryStatus : uint8
{
	BS_Idle				UMETA( DisplayName = "Idle" ),
	BS_IdleEmpty		UMETA( DisplayName = "Idle Empty" ),
	BS_IdleFull			UMETA( DisplayName = "Idle Full" ),
	BS_PowerIn			UMETA( DisplayName = "Power In" ),
	BS_PowerOut 		UMETA( DisplayName = "Power Out" )
};

/**
 * Building that stores surplus power from the power grid they are connected to,
 * power that can later be spent to compensate for power shortage.
 */
UCLASS()
class FACTORYGAME_API AFGBuildablePowerStorage : public AFGBuildableFactory
{
	GENERATED_BODY()
public:
	AFGBuildablePowerStorage();
	
	//~ Begin AActor interface
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void GetConditionalReplicatedProps(TArray<FFGCondReplicatedProperty>& outProps) const override;
	//~ End AActor interface

	//~ Begin AFGBuildableFactory interface
	virtual bool Factory_HasPower() const override;
	virtual bool CanProduce_Implementation() const override;
	virtual EProductionStatus GetProductionIndicatorStatus() const override;
	virtual void Factory_StartProducing() override;
	virtual void Factory_StopProducing() override;
	virtual void Factory_TickProducing( float deltaTime ) override;
	virtual void GainedSignificance_Implementation() override;
	//~ End AFGBuildableFactory interface

	/** @return the amount of power currently stored in this battery, in MWh. */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetPowerStore() const;

	/** @return the maximum amount of power that can be stored in this battery, in MWh. */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetPowerStoreCapacity() const { return mPowerStoreCapacity; }

	/** @return the current power store as percentage of the power-store capacity of this battery. In the range [0.0, 1.0]. */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetPowerStorePercent() const { return mPowerStore / mPowerStoreCapacity; }

	/** @return the current power input of this battery in MWh. */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetPowerInput() const { return FMath::Max( GetNetPowerInput(), 0.0f ); }

	/** @return the current power output of this battery in MWh. */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetPowerOutput() const { return FMath::Max( -GetNetPowerInput(), 0.0f ); }

	/** @return time in seconds until the battery is full with current power input. */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetTimeUntilFull() const;

	/** @return time in seconds until the battery is empty with current power output. */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetTimeUntilEmpty() const;

	/** @return the current status of this battery */
	UFUNCTION( BlueprintPure, Category = "Power" )
	EBatteryStatus GetBatteryStatus() const { return mBatteryStatus; }

	/** @return how many discrete indicator blocks (displayed on the side of the power storage building) represent a fully charged power storage */
	UFUNCTION( BlueprintPure, Category = "Power" )
	uint8 GetIndicatorLevelMax() const { return mIndicatorLevelMax; }

protected:
	/**
	 * Called when the battery status of this power storage changes
	 */
	UFUNCTION( BlueprintImplementableEvent, Category = "Power" )
	void StatusChanged( EBatteryStatus status );

	/**
	 * Called when the indicator level of this power storage changes
	 */
	UFUNCTION( BlueprintImplementableEvent, Category = "Power" )
	void IndicatorLevelChanged( uint8 indicatorLevel );

	/** Zero-based ID of the customization data that will have the current status of the power storage. Inside the material, the custom data index is 11 + StatusPrimitiveID */
	UPROPERTY(EditDefaultsOnly, Category = "Visuals")
	int32 mStatusPrimitiveID{2};
	
	/** Zero-based ID of the customization data that will have the current charge level of the power storage (0.0-1.0). Inside the material, the custom data index is 11 + mChargePrimitiveID */
	UPROPERTY(EditDefaultsOnly, Category = "Visuals")
	int32 mChargePrimitiveID{3};

	/** Number of extra customization data to maintain on the power storage. Should be bigger than Status Primitive ID and Charge Primitive ID */
	UPROPERTY(EditDefaultsOnly, Category = "Visuals")
	int32 mNumExtraCustomizationData{4};

	UPROPERTY(EditDefaultsOnly)
	UFGColoredInstanceMeshProxy* mMeshMesh;
	
private:
	float GetNetPowerInput() const;

	uint8 CalculateIndicatorLevel() const;

	void UpdatePropertiesOnGameThread( EBatteryStatus status, uint8 indicatorLevel );
	void UpdateProperties( EBatteryStatus status, uint8 indicatorLevel );
	
	UFUNCTION()
	void OnRep_Status();

	UFUNCTION()
	void OnRep_IndicatorLevel();

	void UpdateExtraCustomizationData();

private:
	/** Battery info */
	UPROPERTY()
	class UFGBatteryInfo* mBatteryInfo;

	UPROPERTY( ReplicatedUsing = OnRep_Status )
	EBatteryStatus mBatteryStatus;

	/**
	 * The current amount of power stored in this battery in MWh.
	 */
	UPROPERTY( SaveGame, meta = ( FGReplicated ) )
	float mPowerStore;

	/**
	 * The maximum power that can be stored in this battery, in MWh.
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Power" )
	float mPowerStoreCapacity;

	/**
	 * The current power input to this battery, in MW. Negative values denote power output.
	 */
	UPROPERTY( meta = ( FGReplicated ) )
	float mPowerInput = 0.0f;

	/**
	 * The maximum input power to this battery, in MW. @note there is no cap on output power.
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Power" )
	float mPowerInputCapacity;

	/**
	* How many discrete indicator blocks (displayed on the side of the power storage building) represent a fully charged power storage
	*/
	UPROPERTY( EditDefaultsOnly, Category = "Power" )
	uint8 mIndicatorLevelMax;

	/**
	* How many discrete indicator blocks are currently being displayed on the side of the power storage building
	*/
	UPROPERTY( ReplicatedUsing = OnRep_IndicatorLevel )
	uint8 mIndicatorLevel;

	/** Maximum amount of time, in seconds, by which the visual state can be out of sync with the real state of the power grid */
	UPROPERTY( EditDefaultsOnly, Category = "Visuals" )
	float mMaxRealDataDriftTime{4.0f};

	/** Amount of time the data on the factory tick has been different from the visual state observable on the game thread. Used to clamp the update frequency for power storages */
	float mRealDataDriftTime{0.0f};
	/** Offset of the drift time to start at. This is a random value from 0 to 1.0 to more evenly distribute the load from buildables across multiple frames. Value is in [0;1] range */
	float mRealDataDriftTimeOffset{0.0f};
};
