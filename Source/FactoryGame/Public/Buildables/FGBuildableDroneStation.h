// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildableFactory.h"
#include "FGDroneVehicle.h"
#include "FGDroneStationInfo.h"
#include "FGActorRepresentationInterface.h"
#include "FGBuildableDroneStation.generated.h"

FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogDroneStation, Log, All );

UENUM( BlueprintType )
enum class EItemTransferringStage : uint8
{
	ITS_NONE		UMETA(displayName = "None"),
	
	ITS_UNLOAD		UMETA(displayName = "Unload"),
	ITS_LOAD		UMETA(displayName = "Load")
};

UENUM( BlueprintType )
enum class EItemTransferTickResult : uint8
{
	ITTR_DONE		UMETA(displayName = "Done"),
	
    ITTR_PARTIAL	UMETA(displayName = "Partial"),
    ITTR_FAILED		UMETA(displayName = "Failed")
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildableDroneStation : public AFGBuildableFactory, public IFGActorRepresentationInterface
{
	GENERATED_BODY()

public:
	AFGBuildableDroneStation();

	// Begin IFGActorRepresentationInterface
	UFUNCTION() virtual bool AddAsRepresentation() override;
	UFUNCTION() virtual bool UpdateRepresentation() override;
	UFUNCTION() virtual bool RemoveAsRepresentation() override;
	UFUNCTION() virtual bool IsActorStatic() override;
	UFUNCTION() virtual FVector GetRealActorLocation() override;
	UFUNCTION() virtual FRotator GetRealActorRotation() override;
	UFUNCTION() virtual class UTexture2D* GetActorRepresentationTexture() override;
	UFUNCTION() virtual FText GetActorRepresentationText() override;
	UFUNCTION() virtual void SetActorRepresentationText( const FText& newText ) override;
	UFUNCTION() virtual FLinearColor GetActorRepresentationColor() override;
	UFUNCTION() virtual void SetActorRepresentationColor( FLinearColor newColor ) override;
	UFUNCTION() virtual ERepresentationType GetActorRepresentationType() override;
	UFUNCTION() virtual bool GetActorShouldShowInCompass() override;
	UFUNCTION() virtual bool GetActorShouldShowOnMap() override;
	UFUNCTION() virtual EFogOfWarRevealType GetActorFogOfWarRevealType() override;
	UFUNCTION() virtual float GetActorFogOfWarRevealRadius() override;
	UFUNCTION() virtual ECompassViewDistance GetActorCompassViewDistance() override;
	UFUNCTION() virtual void SetActorCompassViewDistance( ECompassViewDistance compassViewDistance ) override;
	UFUNCTION() virtual UMaterialInterface* GetActorRepresentationCompassMaterial() override;
	// End IFGActorRepresentationInterface

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	// End AActor interface

	// Begin Factory_ interface
	virtual void Factory_Tick( float dt ) override;
	virtual void Factory_TickProducing( float dt ) override;
	virtual void Factory_CollectInput_Implementation() override;
	// End Factory_ interface

	//~ Begin IFGDismantleInterface
	virtual void Dismantle_Implementation() override;
	virtual void GetChildDismantleActors_Implementation( TArray< AActor* >& out_ChildDismantleActors ) const override;
	//~ End IFGDismantleInferface

	// Begin IFGSaveInterface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End IFGSaveInterface

	virtual void StartIsLookedAtForSnapping( class AFGCharacterPlayer* byCharacter, bool IsValidSnap );
	virtual void StopIsLookedAtForSnapping( class AFGCharacterPlayer* byCharacter );

	void Undock( bool Immediate = false );

	/** If successful, returns 0 if docking is approved right away, otherwise returns position in queue. */
	UFUNCTION( BlueprintCallable, Category = "Drone Station" )
	int32 RequestDocking( class AFGDroneVehicle* DroneToDock );

	UFUNCTION( BlueprintCallable, Category = "Drone Station" )
	bool IsDroneInQueue( class AFGDroneVehicle* Drone ) const;

	UFUNCTION( BlueprintPure, Category = "Drone Station" )
    EItemTransferringStage GetItemTransferringStage() const { return mItemTransferringStage; }

	UFUNCTION( BlueprintPure, Category = "Drone Station" )
    bool IsTransferringItems() const { return mItemTransferringStage != EItemTransferringStage::ITS_NONE; }

	void SetStationDrone( class AFGDroneVehicle* Drone );

	UFUNCTION( BlueprintPure, Category = "Drone Station" )
	bool HasDronesInQueue() const { return mStationHasDronesInQueue; }
	
	UFUNCTION( BlueprintPure, Category = "Drone Station" )
    class AFGDroneVehicle* GetStationDrone() const { return mStationDrone; }

	UFUNCTION( BlueprintPure, Category = "Drone Station" )
    class AFGDroneVehicle* GetDockedDrone() const { return mDockedDrone; }

	UFUNCTION( BlueprintPure, Category = "Drone Station" )
	FVector GetDroneDockingStartLocation() const;

	UFUNCTION( BlueprintPure, Category = "Drone Station" )
    FVector GetDroneDockingLocation() const;

	UFUNCTION( BlueprintPure, Category = "Drone Station" )
	float GetDroneQueueRadius() const { return mDroneQueueRadius; }

	UFUNCTION( BlueprintPure, Category = "Drone Station" )
    float GetDroneQueueVerticalSeparation() const { return mDroneQueueVerticalSeparation; }

	UFUNCTION( BlueprintPure, Category = "Drone Station" )
    float GetDroneQueueSeparationRadius() const { return mDroneQueueSeparationRadius; }

	UFUNCTION( BlueprintPure, Category = "Drone Station" )
    int32 GetTripInformationSampleCount() const { return mTripInformationSampleCount; }
	
	/** Get the inventory that the docked drone unloads into */
	UFUNCTION( BlueprintPure, Category = "Drone Station" )
	class UFGInventoryComponent* GetInputInventory() const { return mInputInventory; }

	/** Get the inventory that the docked drone loads from */
	UFUNCTION( BlueprintPure, Category = "Drone Station" )
	class UFGInventoryComponent* GetOutputInventory() const { return mOutputInventory; }

	/** Get the inventory that the docked drone grabs fuel from. */
	UFUNCTION( BlueprintPure, Category = "Drone Station" )
	class UFGInventoryComponent* GetFuelInventory() const { return mFuelInventory; }

	/** @returns the info that is always present on both client and server */
	UFUNCTION( BlueprintPure, Category = "Drone Station" )
    AFGDroneStationInfo* GetInfo() const { return mInfo; }

	void EnsureInfoCreated();

public:
	/** Called when the drone changes docking state. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Drone" )
    void OnDockingStateChanged( EDroneDockingState NewState, float TimeSinceChanged );

	/** Called when the drone changes from having no drone in the queue to having at least one, or vice versa. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Drone" )
    void OnStationHasDroneQueueUpdated( bool StationHasDroneQueue );
	
	/** Called when a drone starts its docking sequence. */
	UFUNCTION( BlueprintNativeEvent, Category = "Drone Station" )
    void StartDockingSequence( class AFGDroneVehicle* Drone );

	/** Called when a drone ends its docking sequence. */
	UFUNCTION( BlueprintNativeEvent, Category = "Drone Station" )
	void EndDockingSequence( class AFGDroneVehicle* Drone, bool ShouldTransferItems );
	
	/** Called when a drone starts its takeoff sequence. */
	UFUNCTION( BlueprintNativeEvent, Category = "Drone Station" )
    void StartTakeoffSequence( class AFGDroneVehicle* Drone );

	/** Called when a drone ends its takeoff sequence. */
	UFUNCTION( BlueprintNativeEvent, Category = "Drone Station" )
	void EndTakeoffSequence( class AFGDroneVehicle* Drone );

	/** Fetches the color to use for this actors representation */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	FLinearColor GetDefaultRepresentationColor();

	virtual void PreSerializedToBlueprint() override;
	virtual void PostSerializedToBlueprint() override;
	virtual void PostSerializedFromBlueprint( bool isBlueprintWorld ) override;

protected:
	/** Get the text that should be shown in the map and compass. */
	UFUNCTION( BlueprintImplementableEvent, Category = "Representation" )
	FText GetRepresentationText();
	
	UFUNCTION()
    bool FilterFuelClasses( TSubclassOf< UObject > object, int32 idx ) const;

	UFUNCTION()
	void OnFuelItemAdded( TSubclassOf< UFGItemDescriptor > item, const int32 amount, UFGInventoryComponent* sourceInventory = nullptr );
	
private:
	UFUNCTION()
	void OnRep_ItemTransferringStage();

	UFUNCTION()
    void OnRep_StationHasDronesInQueue();

	UFUNCTION()
	void OnRep_DroneStationInfo();

	void SetItemTransferringStage( EItemTransferringStage NewStage );
	
    void BeginItemTransfer();
	void EndItemTransfer();

	/** One tick of item transferring. Returns true when done transferring. */
	EItemTransferTickResult ItemTransferTick( class UFGInventoryComponent* FromInventory, class UFGInventoryComponent* ToInventory, bool MustTransferEverything );

	UFUNCTION()
	void OnDroneFuelTypeChanged( const FFGDroneFuelType& newFuelType );
	
private:
	friend class AFGDroneStationInfo;
	friend class AFGDroneSubsystem;

	/** All connection components tagged with this is considered fuel components */
	static FName sFuelTag;
	
	/** Where the drones should fly to before starting docking procedure. Local Space. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	FVector mDroneDockingStartLocationLocal;

	/** Where the drone is positioned when docked to the station. Local Space. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	FVector mDroneDockingLocationLocal;
	
	/** Class of the drone actor to spawn. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	TSubclassOf<class AFGDroneVehicle> mDroneClass;
	
	/** Drones waiting to dock. */
	UPROPERTY( SaveGame )
	TArray<class AFGDroneVehicle*> mDroneDockingQueue;

	/** Whether or not the station has drones in queue. */
	UPROPERTY( ReplicatedUsing=OnRep_StationHasDronesInQueue )
	bool mStationHasDronesInQueue;

	UPROPERTY( SaveGame )
	/** The most recent drone to dock. Gets cleared after traveling a certain distance away. */
	class AFGDroneVehicle* mRecentlyDockedDrone;

	/** Whether we are in the process of transferring items, and what stage. */
	UPROPERTY( SaveGame, ReplicatedUsing=OnRep_ItemTransferringStage )
	EItemTransferringStage mItemTransferringStage;

	/** Current progress on transfer from/to docking station ( in seconds ) */
	UPROPERTY()
	float mTransferProgress;

	/** How long time it takes to transfer one stack of item from/to docking station ( in seconds ) */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	float mTransferSpeed;

	/** How much of a stack to transfer in each separate transfer moment */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	float mStackTransferSize;

	/** How far away drones circle the station when in queue. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	float mDroneQueueRadius;

	/** How far away drones seperate outward when in queue. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	float mDroneQueueSeparationRadius;
	
	/** How far away drones seperate vertically when in queue. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	float mDroneQueueVerticalSeparation;

	/** Base cost of a launching a drone on a trip. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	float mTripPowerCost;
	
	/** How much power every meter of travel costs between this station and another. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	float mTripPowerPerMeterCost;

	/** We store this many of the station drone's latest trip for statistics. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	int32 mTripInformationSampleCount;
	
	/** The drone belonging to this station. */
	UPROPERTY( Replicated, SaveGame )
	class AFGDroneVehicle* mStationDrone;

	/** The currently docked drone. */
	UPROPERTY( Replicated, SaveGame )
	class AFGDroneVehicle* mDockedDrone;

	/** SizeX of input and output inventories */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	int8 mStorageSizeX;

	/** SizeY of input and output inventories */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	int8 mStorageSizeY;

	/** SizeX of fuel inventory. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	int8 mFuelStorageSizeX;

	/** SizeY of fuel inventory. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	int8 mFuelStorageSizeY;
	
	/** Inventory where we transfer items from when loading a drone.  */
	UPROPERTY( SaveGame )
	class UFGInventoryComponent* mInputInventory;

	/** Inventory where we transfer items to when unloading from a drone.  */
	UPROPERTY( SaveGame )
	class UFGInventoryComponent* mOutputInventory;
	
	/** Inventory where fuel is stored. */
	UPROPERTY( SaveGame )
	class UFGInventoryComponent* mFuelInventory;

	/** All connections that can pull to data to our storage, (References hold by Components array, no need for UPROPERTY) */
	TArray<class UFGFactoryConnectionComponent*> mStorageInputConnections;
	
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_DroneStationInfo )
	AFGDroneStationInfo* mInfo;

	/** Used to hold a reference to the mInfo during blueprint serialization. Holds a reference to mInfo which is nulled during blueprint serialization */
	UPROPERTY()
	AFGDroneStationInfo* mTempInfo;

	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	class UTexture2D* mActorRepresentationTexture;

	UPROPERTY( EditDefaultsOnly, Category = "Representation" )
	UMaterialInterface* mActorRepresentationCompassMaterial;
	
	UPROPERTY( Replicated )
	FText mMapText;
};
