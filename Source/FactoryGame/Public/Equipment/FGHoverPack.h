// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGEquipment.h"
#include "FGHoverPack.generated.h"

UENUM( BlueprintType )
enum class EHoverPackMode : uint8
{
	HPM_Inactive			UMETA( DisplayName = "Inactive" ),
    HPM_Hover				UMETA( DisplayName = "Hover" ),
    HPM_HoverSlowFall		UMETA( DisplayName = "Slow Fall" )
};

UENUM( BlueprintType )
enum class EHoverConnectionStatus : uint8
{
	HCS_NULL				UMETA( DisplayName = "Null" ),
	HCS_OK					UMETA( DisplayName = "OK" ),
    HCS_NO_POWER			UMETA( DisplayName = "No Power" ),
    HCS_OUT_OF_RANGE		UMETA( DisplayName = "Out of Range" )
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnConnectionStatusUpdated, bool, status );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnConnectionLocationUpdated, FVector, location );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnHoverModeChanged, EHoverPackMode, newMode );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnRangeWarningToggle, bool, status );

FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogHoverPack, Log, All );

DECLARE_STATS_GROUP( TEXT("HoverPack"), STATGROUP_HoverPack, STATCAT_Advanced );

UCLASS()
class FACTORYGAME_API AFGHoverPack : public AFGEquipment
{
	GENERATED_BODY()
	
public:	
	AFGHoverPack();

	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void Tick( float deltaTime ) override;
	// End AActor interface

	// Begin AFGEquipment interface
	virtual void UnEquip() override;
	virtual void OnCharacterMovementModeChanged( EMovementMode PreviousMovementMode, uint8 PreviousCustomMode, EMovementMode NewMovementMode, uint8 NewCustomMode ) override;
	virtual void AddEquipmentActionBindings() override;
	virtual float GetCharacterUseDistanceOverride() const override;
	// End AFGEquipment interface

	/** Gets the max speed for the hover pack. */
	UFUNCTION( BlueprintPure, Category = "HoverPack" )
	float GetMaxSpeed( bool IsSprinting ) const;

	/** Gets the hover speed for the hover pack. */
	UFUNCTION( BlueprintPure, Category = "HoverPack" )
	float GetHoverSpeed( bool IsSprinting ) const;

	/** Gets the hover acceleration speed in units / second. */
	UFUNCTION( BlueprintPure, Category = "HoverPack" )
	float GetHoverAccelerationSpeed( bool IsSprinting ) const;

	/** Gets the friction used when flying with the hover pack. */
	UFUNCTION( BlueprintPure, Category = "HoverPack" )
	float GetFriction() const { return mHoverFriction; }

	/** Gets the current power level of the hoverpack. */
	UFUNCTION( BlueprintPure, Category = "HoverPack" )
	float GetCurrentPowerLevel() const { return mCurrentPowerLevel; }

	/** Gets the power capacity of the hoverpack. */
	UFUNCTION( BlueprintPure, Category = "HoverPack" )
	float GetPowerCapacity() const { return mPowerCapacity; }

	/** Gets the power level of the hoverpack normalized between 0 and 1. */
	UFUNCTION( BlueprintPure, Category = "HoverPack" )
	float GetNormalizedPowerLevel() const { return mCurrentPowerLevel / mPowerCapacity; }

	/** Gets the maximum fall speed allowed if the hoverpack has power. */
	UFUNCTION( BlueprintPure, Category = "HoverPack" )
	float GetFallSpeedLimitWhenPowered() const { return mFallSpeedLimitWhenPowered; }

	/** Whether or not we have a power connection. */
	UFUNCTION( BlueprintPure, Category = "HoverPack" )
	bool HasConnection() const { return mHasConnection; }
	
	/** Gets the connection we're connected to (Server Only). */
	UFUNCTION( BlueprintPure, Category = "HoverPack" )
	FVector GetCurrentConnectionLocation() const;

	UFUNCTION( BlueprintPure, Category = "HoverPack" )
	FORCEINLINE bool ShouldDisplayRangeWarning() const { return mDisplayRangeWarning; }

	/** Gets the normalized distance (0-1) from the current connection. */
	UFUNCTION( BlueprintPure, Category = "HoverPack" )
	float GetNormalizedDistanceFromConnection() const;
	
	/** Gets the distance from the current connection. */
	UFUNCTION( BlueprintPure, Category = "HoverPack" )
	float GetDistanceFromCurrentConnection() const;
    
	/** Gets the max distance allowed away from the current connection. Changes if connected to a railroad track. */
	UFUNCTION( BlueprintPure, Category = "HoverPack" )
	float GetMaxDistanceFromCurrentConnection() const;

	/** Gets the vertical distance between us and the current connection, between 0-1 based on radius. */
	UFUNCTION( BlueprintPure, Category = "HoverPack" )
	float GetHeightAboveCurrentConnection() const;

	/** Gets the railroad track we're connected to. */
	UFUNCTION( BlueprintPure, Category = "HoverPack" )
	FORCEINLINE class AFGBuildableRailroadTrack* GetCurrentRailroadTrack() const { return mCurrentRailroadTrack; }

	/** Get the current mode of the hoverpack. */
	UFUNCTION( BlueprintPure, Category = "HoverPack" )
	FORCEINLINE EHoverPackMode GetCurrentHoverMode() const { return mCurrentHoverMode; }

	UFUNCTION( BlueprintPure, Category = "HoverPack" )
	FORCEINLINE UFGPowerConnectionComponent* GetConnectedToComponent() const { return mCurrentPowerConnection; }
	
	/** Whether or not hoverpack is active. */
	UFUNCTION( BlueprintPure, Category = "HoverPack" )
	FORCEINLINE bool IsHoverActive() const { return mCurrentHoverMode != EHoverPackMode::HPM_Inactive; }

	/** Activate / Deactivate the hover pack. */
	void SetHoverMode( EHoverPackMode HoverMode, bool UpdateMovementMode = true );

	/** Finds a nearby valid power connection. */
	void ConnectToNearestPowerConnection();

	/** Checks if a power connection is valid, and returns the reason if not. */
	EHoverConnectionStatus GetPowerConnectionStatus( class UFGPowerConnectionComponent* Connection ) const;

	/** Checks if a power connection is valid for connection. */
	bool IsPowerConnectionValid( class UFGPowerConnectionComponent* Connection, bool CheckDistance = true ) const;

	/** Checks if a railroad track is valid for connection. */
	bool IsRailroadTrackValid( class AFGBuildableRailroadTrack* RailroadTrack, bool CheckDistance = true ) const;

	/** Called when the current power connection location changes. */
	UPROPERTY( BlueprintAssignable, Category = "HoverPack", DisplayName = "On Connection Location Updated" )
	FOnConnectionLocationUpdated ConnectionLocationUpdatedDelegate;
	
	/** Called when we go from connected to disconnected or vice versa. */
	UPROPERTY( BlueprintAssignable, Category = "HoverPack", DisplayName = "On Connection Status Updated" )
	FOnConnectionStatusUpdated ConnectionStatusUpdatedDelegate;

	/** Called whenever the hoverpack changes mode. */
	UPROPERTY( BlueprintAssignable, Category = "HoverPack", DisplayName = "On Hover Mode Changed" )
	FOnHoverModeChanged HoverModeChangedDelegate;

	/** Called whenever we wanna toggle the range warning. */
	UPROPERTY( BlueprintAssignable, Category = "HoverPack", DisplayName = "On Range Warning Toggle" )
	FOnRangeWarningToggle RangeWarningToggleDelegate;

protected:
	/** Called when the HoverPack changes mode. */
	UFUNCTION( BlueprintImplementableEvent, Category = "HoverPack", DisplayName = "On Hover Mode Changed" )
	void K2_OnHoverModeChanged( EHoverPackMode newMode, EHoverPackMode previousMode );

	/** Called when the current power connection location or status changes. */
	UFUNCTION( BlueprintImplementableEvent, Category = "HoverPack", DisplayName = "On Power Connection Updated" )
	void K2_OnPowerConnectionUpdated();
	
	/** Called when range warning should be enabled or disabled. */
	UFUNCTION( BlueprintImplementableEvent, Category = "HoverPack", DisplayName = "On Range Warning Toggle" )
	void K2_OnRangeWarningToggle();
	
private:
	/** Wrapper to handle all power connection logic. */
	void HandlePowerConnection( const float DeltaTime );
	void UpdateShowRangeWarning();

	/** Used to set up a connection to a power connection. */
	void ConnectToPowerConnection( class UFGPowerConnectionComponent* Connection );

	/** Disconnects the current power connection, if one exists. */
	void DisconnectFromCurrentPowerConnection();

	/** Used to set up a connection to a rail road track. */
	void ConnectToRailroadTrack( class AFGBuildableRailroadTrack* RailroadTrack );

	void UpdateHoverNoise();

	void ApplyHoverPackMovementMode() const;
	
	/** Called when the player presses crouch, on server. */
	UFUNCTION( Server, Reliable, WithValidation )
	void PlayerStopHover_Server();
	
	/** Called when the player presses crouch. */
	void PlayerStopHover();

	/** Used to report a noise event for when the hoverpack is active. */
	UFUNCTION()
	void MakeActiveNoise();

	/** Input Actions */
	void Input_Crouch( const FInputActionValue& actionValue );

private:
	UFUNCTION()
	void OnRep_HasConnection();

	UFUNCTION()
	void OnRep_CurrentHoverMode( EHoverPackMode previousHoverMode );

	UFUNCTION()
	void OnRep_CurrentConnectionLocation();

	UFUNCTION()
	void OnRep_DisplayRangeWarning();
private:
	/** How fast the character moves with the hover pack. */
	UPROPERTY( EditDefaultsOnly, Category = "HoverPack" )
	float mHoverSpeed;

	/** How fast the hoverpack accelerates. Units / Second. Might need to be higher / lower depending on hover friction. */
	UPROPERTY( EditDefaultsOnly, Category = "HoverPack" )
	float mHoverAccelerationSpeed;

	/** How fast the character moves with the hover pack when sprinting. */
	UPROPERTY( EditDefaultsOnly, Category = "HoverPack" )
	float mHoverSprintMultiplier;

	/** Friction of the movement while airborne (0-1). */
	UPROPERTY( EditDefaultsOnly, Category = "HoverPack" )
	float mHoverFriction;

	/** How long the user needs to hold jump in order to activate the hoverpack. */
	UPROPERTY( EditDefaultsOnly, Category = "HoverPack" )
	float mJumpKeyHoldActivationTime;

	/** How fast the character is falls if hoverpack has power but is disconnected from grid. */
	UPROPERTY( EditDefaultsOnly, Category = "HoverPack" )
	float mFallSpeedLimitWhenPowered;

	/** How far away we look for power connections. */
	UPROPERTY( EditDefaultsOnly, Category = "HoverPack" )
	float mPowerConnectionSearchRadius;

	/** How often we look for new connections. */
	UPROPERTY( EditDefaultsOnly, Category = "HoverPack" )
	float mPowerConnectionSearchTickRate;

	float mPowerConnectionSearchTimer;

	/** How much time needs to pass after leaving a power connection before getting disconnected. */
	UPROPERTY( EditDefaultsOnly, Category = "HoverPack" )
	float mPowerConnectionDisconnectionTime;

	/** Timer for disconnecting from power connection if it is out of range. */
	float mPowerDisconnectionTimer;

	/** How much power the power pack battery can contain. */
	UPROPERTY( EditDefaultsOnly, Category = "HoverPack" )
	float mPowerCapacity;

	/** How much power is drained per second when using the slow fall mode. */
	UPROPERTY( EditDefaultsOnly, Category = "HoverPack" )
	float mPowerDrainRate;

	/** How much power the hoverpack drains when connected to a grid. */
	UPROPERTY( EditDefaultsOnly, Category = "HoverPack" )
	float mPowerConsumption;

	/** How much power the hoverpack currently has. */
	UPROPERTY( VisibleAnywhere, Replicated, Category = "HoverPack" )
	float mCurrentPowerLevel;

	/** 0-1 value how far away the player needs to be from the current connection when the warning indicator should start showing. */
	UPROPERTY( EditDefaultsOnly, Category = "HoverPack", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0") )
	float mRangeWarningNormalizedDistanceThreshold;
	
	/** Used to keep track of whether or not the range warning indicator is being displayed. */
	UPROPERTY( ReplicatedUsing = OnRep_DisplayRangeWarning )
	bool mDisplayRangeWarning;

	/** The current hoverpack mode. */
	UPROPERTY( ReplicatedUsing = OnRep_CurrentHoverMode )
	EHoverPackMode mCurrentHoverMode;

	/** The current power connection we are connected to. */
	UPROPERTY()
	class UFGPowerConnectionComponent* mCurrentPowerConnection;

	/** Whether or not we have an active location. */
	UPROPERTY( ReplicatedUsing = OnRep_HasConnection )
	bool mHasConnection;

	/** Whether or not we should automatically start hovering when we get a connection. */
	UPROPERTY( SaveGame )
	bool mShouldAutomaticallyHoverWhenConnected;

	/** How fast the player has to double tap crouch in order to exit hover mode. */
	UPROPERTY( EditDefaultsOnly, Category = "HoverPack" )
	float mCrouchHoverCancelTime;
	
	/** Timer used for disabling hover mode if the player double taps crouch. */
	float mPlayerCrouchHoverCancelTimer;
	
	/** How far the character using the hoverpack can reach when it's active. */
	UPROPERTY( EditDefaultsOnly, Category = "HoverPack" )
	float mCharacterUseDistanceWhenActive;

	/** The noise to make when the hoverpack is active. */
	UPROPERTY( EditDefaultsOnly, Category = "HoverPack" )
	TSubclassOf< class UFGNoise > mActiveNoise;

	/** How often to make the noise (in seconds) while the hoverpack is active. */
	UPROPERTY( EditDefaultsOnly, Category = "HoverPack" )
	float mActiveNoiseFrequency;

	FTimerHandle mActiveNoiseTimerHandle;

	/** The location of our power connection. */
	UPROPERTY( ReplicatedUsing = OnRep_CurrentConnectionLocation )
	FVector mCurrentConnectionLocation;

	/** The rail road track we are currently surfing. */
	UPROPERTY( Replicated )
	class AFGBuildableRailroadTrack* mCurrentRailroadTrack;

	/** Our own power info component. */
	UPROPERTY( VisibleAnywhere )
	class UFGPowerInfoComponent* mPowerInfo;

	/** Our own power connection component. */
	UPROPERTY( VisibleAnywhere )
	class UFGPowerConnectionComponent* mPowerConnection;
};
