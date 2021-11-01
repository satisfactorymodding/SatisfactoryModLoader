// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGDockableInterface.generated.h"


/**
 * @todo: Change this in favour for more flexible docking stations (for instance, boats) that can be done in mods
 * Different type of docks.
 */
UENUM( BlueprintType )
enum class EDockStationType : uint8
{
	DST_NONE			UMETA( DisplayName = "None" ),
	DST_TRUCK			UMETA( DisplayName = "Truck" ),
	DST_TRAIN			UMETA( DisplayName = "Train" ),
	DST_DRONE			UMETA( DisplayName = "Drone" ),
	DST_LAST_ENUM		UMETA( Hidden )
};

/**
 * Interface for all dockable actors out there, i.e. trucks and trains.
 */
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGDockableInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class FACTORYGAME_API IFGDockableInterface
{
	GENERATED_IINTERFACE_BODY()

	/** Check if this thing can dock at the given type of docking station. */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Docking" )
	bool CanDock( EDockStationType atStation ) const;

	/** Get the input/output inventory for this dockable thing. */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Docking" )
	class UFGInventoryComponent* GetDockInventory() const;

	/** Get the fuel inventory for this dockable thing. */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Docking" )
	class UFGInventoryComponent* GetDockFuelInventory() const;

	/** Called when it was docked to the station. */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Docking" )
	void WasDocked( class AFGBuildableDockingStation* atStation );

	/** Called when it was undocked from the station. */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Docking" )
	void WasUndocked();

	/** Called when we start loading the vehicle */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Docking" )
	void OnBeginLoadVehicle();

	/** Called when we start unloading the vehicle */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Docking" )
	void OnBeginUnloadVehicle();

	/** Notify for when loading/unloading are completed */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Docking" )
	void OnTransferComplete();
};
