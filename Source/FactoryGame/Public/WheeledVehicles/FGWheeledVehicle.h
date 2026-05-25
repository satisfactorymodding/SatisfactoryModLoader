// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGVehicle.h"
#include "FGVehiclePathValidation.h"
#include "FGWheeledVehicleMovementComponent.h"
#include "FGWheeledVehicle.generated.h"

class AFGWheeledVehicleProxyActor;
struct FVehiclePathVisualizationHandle;
class UFGVehicleAutopilotComponent;
class UFGVehiclePathPreset;
class AFGVehiclePathSegment;
class AFGWheeledVehicleIdentifier;
struct FInputActionValue;
class AFGBuildableDockingStation;
class UFGHologramBuildModeDescriptor;
class UFGBuildGunModeDescriptor;

UCLASS( BlueprintType, Abstract, Config = Game )
class FACTORYGAME_API AFGWheeledVehicle : public AFGVehicle, public IFGDockableInterface
{
	GENERATED_BODY()
public:
	AFGWheeledVehicle();

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	virtual void Tick( float dt ) override;
	virtual void Destroyed() override;
	virtual void NotifyControllerChanged() override;
	// End AActor interface

	// Begin ADriveablePawn interface
	virtual bool DriverEnter( AFGCharacterPlayer* driver ) override;
	virtual void LeavesVehicle() override;
	virtual void SubmergedInWaterUpdated(bool newIsSubmerged) override;
	virtual void AddInputBindings( UInputComponent* enhancedInput ) override;
	virtual void OnIsSimulatedChanged() override;
	virtual void UpdatePlayerStatus() override;
	virtual void OnDrivingStatusChanged() override;
	virtual void UpdateVehicleSimulationState() override;
	virtual void OnRelevantToNearbyPlayersChanged() override;
	virtual void SetCustomizationData_Native(const FFactoryCustomizationData& customizationData, bool skipCombine = false) override;
	virtual void GetVehicleLocationAndRotation(FVector& OutVehicleLocation, FRotator& OutVehicleRotation) const override;
	virtual FBox GetVehicleBoundingBox() const override;
	virtual bool ShouldDestroyVehicleOnContact(const TSubclassOf<UFGDamageType>& gameDamageTypeClass) const override;
	// End ADriveablePawn interface

	// Begin IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	//End IFGSignificanceInterface

	// Begin IFGDockableInterface
	virtual bool CanDock_Implementation( AActor* dockingStationActor ) const override;
	virtual EResourceForm GetDockInventoryResourceForm_Implementation() const override;
	virtual UFGInventoryComponent* GetDockInventory_Implementation() const override;
	virtual UFGInventoryComponent* GetDockFuelInventory_Implementation() const override;
	virtual void WasDocked_Implementation( AActor* dockingStationActor ) override;
	virtual void WasUndocked_Implementation() override;
	// End IFGDockableInterface

	// Begin IFGUseableInterface
	virtual void UpdateUseState_Implementation( AFGCharacterPlayer* byCharacter, const FVector& atLocation, UPrimitiveComponent* componentHit, FUseState& out_useState ) override;
	// End IFGUseableInterface

	// Begin IFGSaveInterface
	virtual void PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion) override;
	// End IFGSaveInterface

	/** Returns the vehicle identifier for this wheeled vehicle */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	AFGWheeledVehicleIdentifier* GetVehicleIdentifier() const { return mVehicleIdentifier; }

	/** Returns chaos movement component for the vehicle */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	FORCEINLINE UFGWheeledVehicleMovementComponent* GetVehicleMovementComponent() const { return mVehicleMovement; }

	/** Returns the vehicle fuel inventory */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	FORCEINLINE UFGInventoryComponent* GetFuelInventory() const { return mFuelInventory; }

	/** Returns the vehicle storage inventory */
	UFUNCTION( BlueprintPure, Category = "Inventory" )
	FORCEINLINE UFGInventoryComponent* GetStorageInventory() const { return mStorageInventory; }

	/** Returns the forward speed of a vehicle. This holds the correct value both in simulated and real mode */
	UFUNCTION( BlueprintPure, Category = "Velocity" )
	float GetForwardSpeed() const { return mVehicleForwardSpeed; }

	/** Returns the estimated speed of the vehicle in kilometers per hour. This holds the correct value both in simulated and real mode */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	int32 GetSpeedInKMH() const;

	/** Returns true if vehicle currently has enough fuel buffered to drive */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	FORCEINLINE bool HasFuel() const { return mVehicleHasFuel; }

	/** Returns the station the vehicle is currently docked at */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	FORCEINLINE AActor* GetCurrentlyDockingStationActor() const { return mCurrentlyDockingStation; }

	/** Returns the proposed station for manual docking */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	FORCEINLINE AActor* GetManualDockingTargetStation() const { return mManualDockingTargetStation; }

	/** Can be called on the server to flip the vehicle */
	UFUNCTION( BlueprintCallable, Category = "Vehicle" )
	void TurnOverVehicle();

	/** Blueprint client accessor for when foliage was destroyed */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic, Category = "Character" )
	void Client_PlayFoliageDestroyedEffect( UStaticMesh* HitMesh, FTransform HitTransform, AActor* HitActor = nullptr );
	
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "Vehicle" )
	void CloseVehicleTrunk();

	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "Vehicle" )
	void OpenVehicleTrunk( AFGCharacterPlayer* player );

	/** Updates the combined light status of the vehicle */
	void RecalculateVehicleLightStatus();

	/** Returns the path build mode for the vehicle */
	UFUNCTION( BlueprintPure, Category = "Wheeled Vehicle" )
	FORCEINLINE UFGVehiclePathPreset* GetVehiclePathPreset() const { return mVehiclePathPreset; }

	/** Returns the path build mode for the vehicle class */
	UFUNCTION( BlueprintPure, Category = "Wheeled Vehicle" )
	static UFGVehiclePathPreset* GetPathPathPresetForVehicleType( TSubclassOf<AFGWheeledVehicle> vehicleClass );

	/** Returns true if autopilot is available for the vehicle of this type overall, false if the vehicle has no valid path preset */
	UFUNCTION( BlueprintPure, Category = "Wheeled Vehicle" )
	static bool IsAutopilotAvailableForVehicleType( TSubclassOf<AFGWheeledVehicle> vehicleClass );

	/** Calculates the maximum speed of the autopilot movement for the given vehicle type */
	UFUNCTION( BlueprintPure, Category = "Wheeled Vehicle" )
	static float GetMaxAutopilotSpeedForVehicleType( TSubclassOf<AFGWheeledVehicle> vehicleClass );

	/** Returns the vehicle path segment the vehicle is currently on, if any */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	FORCEINLINE AFGVehiclePathSegment* GetCurrentVehiclePathSegment() const { return mCurrentVehiclePathSegment; }

	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	FORCEINLINE UBoxComponent* GetFoliageCollideBox() const { return mFoliageCollideBox; }

#if WITH_EDITOR
	FORCEINLINE bool ShouldVisualizePathValidationConfig() const { return mVisualizePathValidationConfig; }
#endif

	/**
	 * Updates the vehicle path segment this vehicle is currently on.
	 * Will automatically update the vehicle identifier cached information and register on the new segment
	 * This is internal function that should not be used by code other than the autopilot and the vehicle itself.
	 */
	void SetCurrentVehiclePathSegment( AFGVehiclePathSegment* newVehiclePathSegment, bool bIsFromBeginPlay = false );

	/** Returns the autopilot component for the vehicle. This should not be used directly */
	UFGVehicleAutopilotComponent* GetVehicleAutopilotComponent() const { return mAutopilotComponent; }
	UFGWheeledVehicleVFXHandler* GetVehicleVFXHandler() const { return mVehicleVFXHandler; }

	/** Returns the fuel consumption per unit of time when manually driving the vehicle, in MW */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	FORCEINLINE float GetManualFuelConsumption() const { return mManualFuelConsumption; }

	/** Returns the fuel consumption of the vehicle per centimeter of distance travelled with autopilot enabled, in MW */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	FORCEINLINE float GetAutopilotFuelConsumption() const { return mAutopilotFuelConsumption; }

	/** Returns true if the vehicle is in a "proxy" mode. Proxy mode is used to represent low LOD vehicles in the distance when idle or self-driving */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	FORCEINLINE bool IsVehicleInProxyMode() const { return mIsVehicleInProxyMode; }

	/** Calculates the current vehicle path segment from the current vehicle location */
	AFGVehiclePathSegment* CalculateCurrentVehiclePathSegmentFromVehicleLocation() const;

	/** Updates the path segment on which the vehicle is currently located when the vehicle is manually driven */
	void UpdateCurrentVehiclePathSegmentFromVehicleLocation();

	/** Teleports the vehicle (or vehicle proxy, depending on the vehicle proxy mode) to the current autopilot location and rotation. Full sync will also teleport the physical vehicle and not just the proxy */
	void SyncVehicleLocationAndRotation( bool bFullSync );

	/** Utility function to tick vehicle movement smoothing on the client. Used by vehicle and vehicle proxy actors */
	static void TickVehicleClientMovementSmoothing( AActor* actor, const FVector& authoritativeLocation, const FQuat& authoritativeRotation, const FVector& authoritativeLinearVelocity, float& timeSinceAccurateVehicleLocation, float deltaTime );
protected:
	/** Updates physics state of the vehicle depending on the relevance to the players */
	void UpdateVehicleProxyState( bool bFromBeginPlay = false );

	/** Called when the lights status is changed */
	UFUNCTION( BlueprintNativeEvent, Category = "Vehicle" )
	void UpdateVehicleLightStatus( bool newVehicleLightStatus );

	/** Called when the honk status is changed */
	UFUNCTION( BlueprintImplementableEvent, Category = "Vehicle" )
	void OnHonkStatusChanged();

	/** Called on the server when the vehicle is docked */
	UFUNCTION( BlueprintImplementableEvent, Category = "Vehicle" )
	void ServerNotifyVehicleDocked();

	/** Called on the server when the vehicle stops being docked */
	UFUNCTION( BlueprintImplementableEvent, Category = "Vehicle" )
	void ServerNotifyVehicleUndocked();

	/** Input Actions */
	UFUNCTION()
	void Input_ThrottleSteer( const FInputActionValue& actionValue );
	UFUNCTION()
	void Input_GamepadThrottle( const FInputActionValue& actionValue );
	UFUNCTION()
	void Input_GamepadBrake( const FInputActionValue& actionValue );
	UFUNCTION()
	void Input_GamepadSteer( const FInputActionValue& actionValue );
	UFUNCTION()
	void Input_LookAxis( const FInputActionValue& actionValue );
	UFUNCTION()
	void Input_Handbrake( const FInputActionValue& actionValue );
	UFUNCTION()
	void Input_Honk( const FInputActionValue& actionValue );
	UFUNCTION()
	void Input_ToggleCamera( const FInputActionValue& actionValue );
	UFUNCTION()
	void Input_ToggleLights( const FInputActionValue& actionValue );
	UFUNCTION()
	void Input_Dock( const FInputActionValue& actionValue );
	UFUNCTION()
	void Input_TogglePathVisualization( const FInputActionValue& actionValue );

	void MoveForward( float throttle, float brake );
	void MoveRight( float axisValue );

	/** Ticks foliage removal and character ragdoll */
	void TickPendingVehicleCollisions( float dt );

	/** Updates the station that can be manually docked at by this vehicle */
	void UpdateManualDockingTargetStation();

	/** Updates vehicle position on the client when driven by the server or another player, or on the server when driven by a remote player */
	void TickClientMovementReplication( float deltaTime );

	UFUNCTION()
	bool FilterFuelClasses( TSubclassOf< UObject > object, int32 idx ) const;
	void BurnFuel( float dt );

	/** Returns true if the player can apply input to the vehicle movement component at this point */
	bool CanApplyVehicleInput() const;
	bool ShouldApplyHandbrake() const;
	void ResetLocalVehicleBrakeInput();

	void CreateLocalPathVisualizationHandle();
	void DestroyLocalPathVisualizationHandle();
	void UpdateSpringArmComponentTickEnabled();
	
	void CreateWheeledVehicleIdentifier();
	void CreateVehicleProxyActor();

	UFUNCTION( Server, Reliable )
	void Server_ManuallyDockAtStation( AActor* dockingStationActor );
	UFUNCTION( Server, Reliable )
	void Server_SetVehicleLightsOn( bool active );
	UFUNCTION( Server, Reliable )
	void Server_SetHonkStatus( bool active );
	UFUNCTION( Server, Reliable )
	void Server_ReplicateClientMovement( FVector authoritativeLocation, FQuat authoritativeRotation, FVector authoritativeLinearVelocity );
	UFUNCTION( Server, Reliable )
	void Server_SetPathVisualizationEnabled( bool newPathVisualizationEnabled );

	UFUNCTION()
	void OnRepTrunkUser();
	UFUNCTION()
	void OnRep_VehicleCombinedLightsState();
protected:
	/** Angular damping strength (multiplier?) that is applied to the vehicle when in the air. Used to stabilize vehicles in the air and prever over-rotation */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category= "Vehicle" )
	float mAirDampingStrength{2.5f};

	/** Damage class applied to characters being ran over by this vehicle */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category= "Damage" )
	TSubclassOf<UFGDamageType> mRunOverDamageTypeClass;

	/** Base Damage applied to characters that get run over this vehicle at its current speed. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category= "Damage" )
	FRuntimeFloatCurve mDamageAtSpeed;
	
	/** Min speed required to ragdoll a character that's being ran over. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category= "Vehicle" )
	float mRagdollRunOverMinSpeed{10.0f};
	
	/** Fuel consumption of the vehicle when manually driving it at full throttle, in MW/s */
	UPROPERTY( EditDefaultsOnly, Category = "Fuel", meta = ( AddAutoJSON = true ) )
	float mManualFuelConsumption{1.0f};

	/** Fuel consumption of the vehicle per unit of distance travelled in self-driving mode, in MW */
	UPROPERTY( EditDefaultsOnly, Category = "Fuel", meta = ( AddAutoJSON = true ) )
	float mAutopilotFuelConsumption{0.05f};

	/** Maximum distance from the vehicle location to the point on path for the vehicle to be considered "on path" */
	UPROPERTY( EditDefaultsOnly, Category= "Vehicle|Path" )
	float mMaxDistanceFromPathToConsiderVehicleOnPath{200.0f};

	/** Maximum angle between the vehicle and the vehicle path for the vehicle to be considered "on path" */
	UPROPERTY( EditDefaultsOnly, Category= "Vehicle|Path" )
	float mMaxAngleBetweenVehicleAndPathToConsiderVehicleOnPath{10.0f};

	/** vehicle simulation component */
    UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
    TObjectPtr<UFGWheeledVehicleMovementComponent> mVehicleMovement;

	/** The autopilot vehicle movement component */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	TObjectPtr<UFGVehicleAutopilotComponent> mAutopilotComponent;

	/** VFX handler for the vehicle */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	TObjectPtr<UFGWheeledVehicleVFXHandler> mVehicleVFXHandler;
	
	/** Collision box for detecting overlaps with foliage only. Shape modified in BP */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	TObjectPtr<UBoxComponent> mFoliageCollideBox;

	/** List of head lights this vehicle has */
	UPROPERTY( BlueprintReadOnly, Category = "Vehicle")
	TArray<TObjectPtr<ULightComponent> > mVehicleHeadlights;

	/** List of tail lights this vehicle has */
	UPROPERTY( BlueprintReadOnly, Category = "Vehicle")
	TArray<TObjectPtr<ULightComponent> > mVehicleTailLights;

	/** Are lights on? */
	UPROPERTY( SaveGame, Replicated, BlueprintReadOnly, Category = "Vehicle" )
	bool mVehicleLightsOn{true};

	/** Combined state of the vehicle lights, updated on the server, depends on autopilot, presence of driver, and a bunch of other factors */
	UPROPERTY( ReplicatedUsing = OnRep_VehicleCombinedLightsState )
	bool mVehicleCombinedLightsState{false};

	/** Is Vehicle honking? */
	UPROPERTY( BlueprintReadOnly, ReplicatedUsing=OnHonkStatusChanged )
	bool mVehicleHonkOn{false};

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Input")
	FRotator mDefaultLockedSprintArmRotation;

	UPROPERTY( BlueprintReadOnly, Category = "Vehicle")
	bool mCameraLocked{false};

	UPROPERTY( BlueprintReadWrite, ReplicatedUsing=OnRepTrunkUser )
	TObjectPtr<AFGCharacterPlayer> mTrunkUser;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Vehicle" )
	FGameplayTag mEnteredVehicleTag;

	/** Path validation template for this vehicle type. Determines which paths can be traversed by the vehicle when self-driving */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle|Path" )
	TObjectPtr<UFGVehiclePathPreset> mVehiclePathPreset;
	
	/** Whether to visualize the path validation setup for this vehicle */
#if WITH_EDITORONLY_DATA
	UPROPERTY( EditDefaultsOnly, Transient, NonTransactional, SkipSerialization, Category = "Vehicle" )
	bool mVisualizePathValidationConfig{false};
#endif

	UPROPERTY( Replicated, BlueprintReadWrite, Category = "Vehicle" )
	bool mIsTrunkOpen{false};

	/** Inventory for fuel */
	UPROPERTY( VisibleDefaultsOnly )
	TObjectPtr<UFGInventoryComponent> mFuelInventory;

	/** Inventory for storage */
	UPROPERTY( VisibleDefaultsOnly )
	TObjectPtr<UFGInventoryComponent> mStorageInventory;

	/** Number of storage inventory slots that this vehicle has */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle|Inventory", meta = ( AddAutoJSON = true ) )
	int32 mInventorySize{0};

	/** True if the storage inventory of this truck is for fluids, and as such only fluids can be added to it */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle|Inventory", meta = ( AddAutoJSON = true ) )
	bool mIsFluidStorageInventory{false};

	/** Scalar for multiplying the default Stack Size for Fluid Inventory Slots ( 1 is default. 2 == 2 * FluidStackSize )*/
	UPROPERTY( EditDefaultsOnly, Category = "Inventory|Inventory" )
	int32 mFluidStackSizeMultiplier{64};

	/** Class of the proxy actor used to represent a LOD version of the vehicle */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	TSubclassOf<AFGWheeledVehicleProxyActor> mProxyActorClass;
public:
	/** Deprecated. Kept for compatibility with legacy saves */
	UPROPERTY( SaveGame )
	TObjectPtr<class UFGTargetPointLinkedList> mTargetNodeLinkedList;

	/** Deprecated. Kept for compatibility with legacy saves */
	UPROPERTY( SaveGame )
	TObjectPtr<class AFGDrivingTargetList> mTargetList;

	/** Deprecated. Kept for compatibility with legacy saves */
	UPROPERTY( SaveGame )
	bool mIsLegacyAutopilotEnabled{false};

protected:
	/** Do we need fuel to drive */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	bool mNeedsFuelToDrive{true};

	/** Always relevant actor holding common information about the vehicle */
	UPROPERTY( Replicated, SaveGame )
	TObjectPtr<AFGWheeledVehicleIdentifier> mVehicleIdentifier;

	/** Docking station that we are currently docking */
	UPROPERTY( Replicated, SaveGame )
	TObjectPtr<AActor> mCurrentlyDockingStation;

	/** Vehicle path segment that the vehicle is currently traversing */
	UPROPERTY( Replicated, SaveGame )
	TObjectPtr<AFGVehiclePathSegment> mCurrentVehiclePathSegment;

	/** Station that can be manually docked at by the player */
	UPROPERTY()
	TObjectPtr<AActor> mManualDockingTargetStation;

	/** Vehicle proxy actor is used to represent the vehicle LOD mesh over the distance */
	UPROPERTY( Replicated )
	TObjectPtr<AFGWheeledVehicleProxyActor> mVehicleProxyActor;

	/** Current vehicle speed. This holds correct value both for autopilot and manual driving */
	UPROPERTY( Replicated )
	float mVehicleForwardSpeed{0};

	/** Current linear velocity of the vehicle from the perspective of the server */
	FVector mVehicleLinearVelocity{ForceInit};

	/** True if vehicle currently has fuel to drive, false if we ran out of fuel */
	UPROPERTY( Replicated )
	bool mVehicleHasFuel{true};

	/** Amount left of the currently burned piece of fuel. In megawatt seconds (MWs). */
	UPROPERTY( SaveGame, Replicated )
	float mCurrentFuelAmount{0.0f};

	/** True if path visualization was enabled last time the vehicle was driven */
	UPROPERTY( SaveGame, Replicated )
	bool mPathVisualizationEnabled{true};

	/** True if we are currently holding brakes */
	bool mCurrentHandbrakeStatus{false};
	/** Current steering input by the player. If steering input is not held and we are on the path, we will automatically follow the path */
	float mCurrentSteeringInput{0.0f};

	/** Active handle to the path visualization, valid only for locally controlled vehicles */
	TSharedPtr<FVehiclePathVisualizationHandle> mActivePathVisualizationHandle;

	// Replicated state of the vehicle from the client. Used to ensure that the position of the vehicle matches between the server and the clients
	UPROPERTY( Replicated )
	FVector mAuthoritativeLocation{ForceInit};
	UPROPERTY( Replicated )
	FQuat mAuthoritativeRotation{ForceInit};
	UPROPERTY( Replicated )
	FVector mAuthoritativeLinearVelocity{ForceInit};
	UPROPERTY( Replicated )
	bool mHasAuthoritativeMovementData{false};

	float mTimeSinceAccurateVehicleLocation{0.0f};

	/** True if we are currently in proxy mode (e.g. vehicle is hidden, and only proxy mesh is visible) */
	UPROPERTY( Replicated )
	bool mIsVehicleInProxyMode{false};
};
