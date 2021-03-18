// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildableCircuitBridge.h"
#include "FGBuildableCircuitSwitch.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnCircuitSwitchPropertyChanged );

/**
 * Building that connects two circuits, allowing them to act as one single circuit when the switch is turned on.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableCircuitSwitch : public AFGBuildableCircuitBridge, public IFGBuildingTagInterface
{
	GENERATED_BODY()
public:
	AFGBuildableCircuitSwitch();

	//~ Begin AActor interface
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	//~ End AActor interface
	
	//~ Begin FGBuildingTagInterface
	virtual bool HasBuildingTag_Implementation() const override { return mHasBuildingTag; }
	virtual void SetHasBuildingTag_Implementation( bool hasBuildingTag ) override;
	virtual FString GetBuildingTag_Implementation() const override { return mBuildingTag; }
	virtual void SetBuildingTag_Implementation( const FString& buildingTag ) override;
	//~ End FGBuildingTagInterface

	/**
	 * @param isSwitchOn true if this switch should be turned on, false otherwise
	 */
	UFUNCTION( BlueprintCallable, Category = "CircuitSwitch" )
	void SetSwitchOn( bool isSwitchOn );

	/**
	 * @returns true if this switch is turned on, false otherwise
	*/
	UFUNCTION( BlueprintPure, Category = "CircuitSwitch" )
	bool IsSwitchOn() const { return mIsSwitchOn; }
	
	/**
	 * @returns true if this bridge is connected to two circuits, false otherwise
	*/
	UFUNCTION( BlueprintPure, Category = "CircuitSwitch" )
	bool IsSwitchConnected() const { return Super::IsBridgeConnected(); }
	
	virtual bool IsBridgeActive() const override { return mIsSwitchOn; }

	/**
	 * Broadcast when the switch is turned on or off.
	 */
	UPROPERTY( BlueprintAssignable, Category = "CircuitSwitch" )
	FOnCircuitSwitchPropertyChanged mOnIsSwitchOnChanged;

	/**
	 * Broadcast when this building is connected or disconnected from the circuit
	 */
	UPROPERTY( BlueprintAssignable, Category = "CircuitSwitch" )
	FOnCircuitSwitchPropertyChanged mOnIsConnectedChanged;

protected:
	/**
	 * Called when the switch is turned on or off
	 */
	UFUNCTION( BlueprintImplementableEvent, Category = "CircuitSwitch" )
	void IsSwitchOnChanged();

	/**
	 * Called when this building is connected or disconnected from the circuit
	 */
	UFUNCTION( BlueprintImplementableEvent, Category = "CircuitSwitch" )
	void IsSwitchConnectedChanged();

private:
	UFUNCTION()
	void OnRep_IsSwitchOn();

	UFUNCTION()
	void OnRep_HasBuildingTag();

	UFUNCTION()
	void OnRep_BuildingTag();

	virtual void OnRep_IsBridgeConnected() override;

private:
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_IsSwitchOn )
	bool mIsSwitchOn;
	
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_HasBuildingTag )
	bool mHasBuildingTag;

	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_BuildingTag )
	FString mBuildingTag;
};
