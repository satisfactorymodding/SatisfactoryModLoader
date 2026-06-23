// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGActorRepresentationInterface.h"
#include "FGSaveInterface.h"
#include "LocalUserInfo.h"
#include "GameFramework/Info.h"
#include "FGWheeledVehicleIdentifier.generated.h"

class UFGItemDescriptor;
class AFGWheeledVehicle;
class AFGDockingStationIdentifier;

UENUM(BlueprintType)
enum class EVehicleAutopilotErrorStatus : uint8
{
	None,
	StationUnreachable,
	NotOnPath,
	TooFewStations,
	NoFuel,
	Deadlocked,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnVehicleAutopilotStatusChangedDelegate );

/** Describes an information about a wheeled vehicle that must always be replicated to the clients */
UCLASS()
class FACTORYGAME_API AFGWheeledVehicleIdentifier : public AInfo, public IFGSaveInterface, public IFGActorRepresentationInterface
{
	GENERATED_BODY()
public:
	AFGWheeledVehicleIdentifier();

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End AActor interface

	// Begin IFGSaveInterface
	virtual bool ShouldSave_Implementation() const override;
	virtual void PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion) override;
	// End IFGSaveInterface

	// Begin IFGActorRepresentationInterface
	virtual bool AddAsRepresentation() override;
	virtual bool UpdateRepresentation() override;
	virtual bool RemoveAsRepresentation() override;
	virtual bool IsActorStatic() override;
	virtual FVector GetRealActorLocation() override;
	virtual FRotator GetRealActorRotation() override;
	virtual ERepresentationType GetActorRepresentationType() override;
	virtual bool GetActorShouldShowOnMap() override;
	virtual bool GetActorShouldShowInCompass() override;
	virtual FText GetActorRepresentationText() override;
	virtual FPlayerInfoHandle GetLastEditedBy() const override;
	virtual UTexture2D* GetActorRepresentationTexture() override;
	virtual FLinearColor GetActorRepresentationColor() override;
	virtual UMaterialInterface* GetActorRepresentationCompassMaterial() override;
	virtual void SetActorRepresentationText(const FText& newText) override;
	virtual void SetActorLastEditedByHandle(const FPlayerInfoHandle& playerInfoHandle) override;
	// End IFGActorRepresentationInterface

	/** Updates a representation owned by this vehicle identifier, even if we are a client */
	void UpdateRepresentation_Local();

	/** Returns the class of the owner vehicle. This will always be available on the client even if the vehicle itself has not been replicated yet */
	UFUNCTION( BlueprintPure, Category = "Vehicle Identifier" )
	FORCEINLINE TSubclassOf<AFGWheeledVehicle> GetVehicleClass() const { return mOwnerVehicleClass; }

	/** Returns the name of the vehicle */
	UFUNCTION( BlueprintPure, Category = "Vehicle Identifier" )
	FORCEINLINE FText GetVehicleName() const { return mVehicleName; }

	/** Returns the current route of the vehicle */
	UFUNCTION( BlueprintPure, Category = "Vehicle Identifier" )
	const TArray<FGuid>& GetVehicleRoute() const { return ObjectPtrDecay( mVehicleRoute ); }

	/** Returns true whenever the autopilot is enabled */
	UFUNCTION( BlueprintPure, Category = "Vehicle Identifier" )
	FORCEINLINE bool IsAutopilotEnabled() const { return mIsAutopilotEnabled; }

	UFUNCTION( BlueprintPure, Category = "Vehicle Identifier" )
	FORCEINLINE EVehicleAutopilotErrorStatus GetAutopilotErrorStatus() const { return mCurrentAutopilotErrorStatus; }

	/** Returns true if the vehicle is currently docking to a docking station */
	UFUNCTION( BlueprintPure, Category = "Vehicle Identifier" )
	FORCEINLINE bool IsCurrentlyDocking() const { return mIsCurrentlyDocking; }

	/** Returns the Guid of the path node at the start of the segment the vehicle is currently on. Will return invalid Guid if vehicle is currently not on the path */
	UFUNCTION( BlueprintPure, Category = "Vehicle Identifier" )
	FORCEINLINE FGuid GetCurrentFromPathNodeGUID() const { return mCurrentFromPathNodeGuid; }

	/** Returns the Guid of the path node at the end of the segment the vehicle is currently on. Will return invalid Guid if vehicle is currently not on the path */
	UFUNCTION( BlueprintPure, Category = "Vehicle Identifier" )
	FORCEINLINE FGuid GetCurrentToPathNodeGUID() const { return mCurrentToPathNodeGuid; }

	/** Returns the docking station the vehicle is currently heading towards */
	UFUNCTION( BlueprintPure, Category = "Vehicle Identifier" )
	FORCEINLINE int32 GetCurrentTargetWaypointIndex() const { return mCurrentTargetWaypointIndex; }

	/** Returns the vehicle actor if it has been replicated to the client */
	UFUNCTION( BlueprintPure, Category = "Vehicle Identifier" )
	FORCEINLINE AFGWheeledVehicle* GetOwnerVehicle() const { return mOwnerVehicle; }

	/** Item descriptor for the last fuel type the vehicle has been running on. This will return a valid descriptor even if the vehicle presently has no fuel */
	UFUNCTION( BlueprintPure, Category = "Vehicle Identifier" )
	FORCEINLINE TSubclassOf<UFGItemDescriptor> GetFuelTypeDescriptor() const { return mFuelTypeDescriptor; }

	/** Updates the vehicle name to the provided one */
	UFUNCTION( BlueprintCallable, Category = "Vehicle Identifier" )
	void SetVehicleName( const FText& newVehicleName );

	/** Returns true if the autopilot can currently be enabled for this vehicle */
	UFUNCTION( BlueprintPure, Category = "Vehicle Identifier" )
	bool CanEnableAutopilot() const;

	/** Updates whenever the autopilot is enabled on the vehicle */
	UFUNCTION( BlueprintCallable, Category = "Vehicle Identifier" )
	void SetAutopilotEnabled( bool newAutopilotEnabled );

	void Internal_SetVehicleName( const FText& newVehicleName );

	/** Removes waypoint from the vehicle route */
	UFUNCTION( BlueprintCallable, Category = "Vehicle Identifier" )
	void RemoveWaypointAtIndex( int32 waypointIndex );

	/** Adds waypoint to the last position in the vehicle route */
	UFUNCTION( BlueprintCallable, Category = "Vehicle Identifier" )
	void AddWaypoint( const FGuid& waypointGuid );

	/** Inserts waypoint to the vehicle route at the given index */
	UFUNCTION( BlueprintCallable, Category = "Vehicle Identifier" )
	void InsertWaypoint( int32 waypointIndex, const FGuid& waypointGuid );

	/** Completely overwrites the current vehicle route */
	UFUNCTION( BlueprintCallable, Category = "Vehicle Identifier" )
	void SetVehicleRoute( const TArray<FGuid>& newVehicleRoute );

	/** Removes waypoints that no longer exist from the vehicle route */
	void SanitizeVehicleRoute();

	void SetOwnerVehicle( AFGWheeledVehicle* ownerVehicle );

	FORCEINLINE int32 GetVehicleRouteChangelist() const { return mVehicleRouteChangelist; }

	void SetCurrentVehicleSegment( const FGuid& fromPathNodeGuid, const FGuid& toPathNodeGuid );
	void SetCurrentTargetWaypoint( int32 newTargetWaypointIndex );
	void SetCurrentAutopilotErrorStatus( EVehicleAutopilotErrorStatus newAutopilotErrorStatus );
	void SetIsCurrentlyDocking( bool newIsCurrentlyDocking );
	void SetFuelTypeDescriptor( const TSubclassOf<UFGItemDescriptor>& newFuelDescriptor );

	/** Broadcast both on the server and the client when vehicle autopilot status changes */
	UPROPERTY( BlueprintAssignable, Category = "Vehicle Identifier" )
	FOnVehicleAutopilotStatusChangedDelegate OnVehicleAutopilotStatusChanged;
protected:
	void OnVehicleSubsystemValid();
	UFUNCTION()
	void OnRep_CurrentAutopilotErrorStatus();
	UFUNCTION()
	void OnRep_IsAutopilotEnabled();

	UPROPERTY( SaveGame, Replicated )
	TSubclassOf<AFGWheeledVehicle> mOwnerVehicleClass;
	
	UPROPERTY( SaveGame, Replicated )
	TObjectPtr<AFGWheeledVehicle> mOwnerVehicle;
	
	UPROPERTY( SaveGame, Replicated )
	FText mVehicleName;

	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_IsAutopilotEnabled )
	bool mIsAutopilotEnabled{false};

	/** Vehicle route that the vehicle will follow */
	UPROPERTY( SaveGame, Replicated )
	TArray<FGuid> mVehicleRoute;

	/** Guid of the path node at the start of the path segment the vehicle is currently on (valid both autopilot on and off) */
	UPROPERTY( Replicated )
	FGuid mCurrentFromPathNodeGuid;
	/** Guid of the path node at the end of the path segment the vehicle is currently on (valid both autopilot on and off) */
	UPROPERTY( Replicated )
	FGuid mCurrentToPathNodeGuid;

	int32 mVehicleRouteChangelist{0};
	
	UPROPERTY( SaveGame, Replicated )
	FPlayerInfoHandle mLastEditedBy;

	/** if the autopilot is enabled, this is the current status of the autopilot navigation */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_CurrentAutopilotErrorStatus )
	EVehicleAutopilotErrorStatus mCurrentAutopilotErrorStatus{EVehicleAutopilotErrorStatus::None};

	/** Index of the path node that the vehicle is currently moving towards. Only set with autopilot enabled */
	UPROPERTY( SaveGame, Replicated )
	int32 mCurrentTargetWaypointIndex{INDEX_NONE};

	/** True if the vehicle is currently docking */
	UPROPERTY( SaveGame, Replicated )
	bool mIsCurrentlyDocking{false};

	/** Item descriptor for the last fuel type the vehicle has been running on. This will return a valid descriptor even if the vehicle presently has no fuel */
	UPROPERTY( SaveGame, Replicated )
	TSubclassOf<UFGItemDescriptor> mFuelTypeDescriptor;
};