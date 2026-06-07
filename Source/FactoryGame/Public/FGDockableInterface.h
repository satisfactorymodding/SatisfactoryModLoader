// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "UObject/Interface.h"
#include "FGDockableInterface.generated.h"

/**
 * Interface for dockable vehicles to implement
 */
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGDockableInterface : public UInterface
{
	GENERATED_BODY()
};

class FACTORYGAME_API IFGDockableInterface
{
	GENERATED_BODY()
public:
	/** Check if the vehicle can dock at the provided docking station */
	UFUNCTION( BlueprintNativeEvent, Category = "Docking" )
	bool CanDock( AActor* dockingStationActor ) const;

	/** Returns the resource type of the dock inventory. This determines whenever it is a fluid or solid inventory */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Docking" )
	EResourceForm GetDockInventoryResourceForm() const;

	/** Get the input/output inventory for this dockable thing. */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Docking" )
	class UFGInventoryComponent* GetDockInventory() const;

	/** Get the fuel inventory for this dockable thing. */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Docking" )
	class UFGInventoryComponent* GetDockFuelInventory() const;

	/** Called when it was docked to the station. */
	UFUNCTION( BlueprintNativeEvent, Category = "Docking" )
	void WasDocked( AActor* dockingStationActor );

	/** Called when it was undocked from the station. */
	UFUNCTION( BlueprintNativeEvent, Category = "Docking" )
	void WasUndocked();

	/** Called when we start loading the vehicle */
	UFUNCTION( BlueprintNativeEvent, Category = "Docking" )
	void OnBeginLoadVehicle();

	/** Called when we start unloading the vehicle */
	UFUNCTION( BlueprintNativeEvent, Category = "Docking" )
	void OnBeginUnloadVehicle();

	/** Notify for when loading/unloading are completed */
	UFUNCTION( BlueprintNativeEvent, Category = "Docking" )
	void OnTransferComplete();
};
