// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGSaveInterface.h"
#include "GameFramework/Actor.h"
#include "FGWorldEventActor.generated.h"

/** Enum representing state of the world event. */
UENUM()
enum class EWorldEventState : uint8
{
	// World event is inactive, can be triggered by WorldEventSubsystem
	Inactive		UMETA( DisplayName = "Inactive" ),

	// World event is active, will not be automatically reset
	Active			UMETA( DisplayName = "Active" ),

	// World event is finished, can be automatically reset by WorldEventSubsystem
	Finished		UMETA( DisplayName = "Finished" )
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FWorldEventDelegate, class AFGWorldEventActor*, worldEventActor );

/**
 * Actor responsible for a World Event. Can be triggered by the World Event Subsystem.
 */
UCLASS()
class FACTORYGAME_API AFGWorldEventActor : public AActor, public IFGSaveInterface
{
	GENERATED_BODY()

public:
	AFGWorldEventActor();

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	// End AActor interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	/** Whether or not this world event can be triggered. */
	UFUNCTION( BlueprintNativeEvent, Category = "WorldEvent" )
	bool CanTrigger() const;

	/** Gets the current state of this world event. */
	UFUNCTION( BlueprintPure, Category = "WorldEvent" )
	FORCEINLINE EWorldEventState GetState() const { return mState; }

	/** Gets the timestamp for when the event was last finished. Will be 0 if the event hasn't finished yet. */
	UFUNCTION( BlueprintPure, Category = "WorldEvent" )
	FORCEINLINE float GetLastFinishTimestamp() const { return mLastFinishTimestamp; }

	/** Gets the radius of this World Event. Used for automatic triggering and resetting. */
	UFUNCTION( BlueprintPure, Category = "WorldEvent" )
	FORCEINLINE float GetEventRadius() const { return mEventRadius; }

	UFUNCTION( BlueprintPure, Category = "WorldEvent" )
	FORCEINLINE bool CanAutomaticallyTrigger() const { return mCanBeAutomaticallyTriggered; }

	UFUNCTION( BlueprintPure, Category = "WorldEvent" )
	FORCEINLINE bool CanAutomaticallyReset() const { return mCanBeAutomaticallyReset; }
	
	/** Used to trigger the world event. Returns true if the world event was triggered. */
	UFUNCTION( BlueprintCallable, Category = "WorldEvent" )
	bool TriggerWorldEvent();

	/** Used to reset the world event. */
    UFUNCTION( BlueprintCallable, Category = "WorldEvent" )
    void ResetWorldEvent();

	/** Finished the world event, which enables it to be automatically reset by the World Event Subsystem. */
	UFUNCTION( BlueprintCallable, Category = "WorldEvent" )
	void FinishWorldEvent();

protected:
	/** Called when the world event gets triggered. Called on both Server and Client. */
	UFUNCTION( BlueprintNativeEvent, Category = "WorldEvent" )
	void OnWorldEventTriggered();

	/** Called when the world event gets reset. Called on both Server and Client. */
    UFUNCTION( BlueprintNativeEvent, Category = "WorldEvent" )
    void OnWorldEventReset();

	/** Called when the world event finishes. Called on both Server and Client. */
	UFUNCTION( BlueprintNativeEvent, Category = "WorldEvent" )
	void OnWorldEventFinished();

private:
	void SetDataLayerActive( bool Active );

	bool SetWorldEventState( EWorldEventState newState );

	UFUNCTION()
	void OnRep_WorldEventState();

public:
	/** Delegate called when this world event gets triggered. Called on both server and client. */
	UPROPERTY( BlueprintAssignable, Category = "WorldEvent" )
	FWorldEventDelegate mOnWorldEventTriggered;
	
	/** Delegate called when this world event gets reset. Called on both server and client. */
	UPROPERTY( BlueprintAssignable, Category = "WorldEvent" )
	FWorldEventDelegate mOnWorldEventReset;
	
	/** Delegate called when this world event gets finished. Called on both server and client. */
	UPROPERTY( BlueprintAssignable, Category = "WorldEvent" )
	FWorldEventDelegate mOnWorldEventFinished;

protected:
	/** Radius of the event. Can't be automatically triggered if a player is within this radius. Can be automatically reset if a player is outside of this radius. */
	UPROPERTY( EditAnywhere, Category = "WorldEvent" )
	float mEventRadius;
	
	/** Whether or not the World Event can be automatically triggered by the World Event Subsystem. */
	UPROPERTY( EditAnywhere, Category = "WorldEvent" )
	bool mCanBeAutomaticallyTriggered;
	
	/** Whether or not the World Event can be automatically reset by the World Event Subsystem. */
    UPROPERTY( EditAnywhere, Category = "WorldEvent" )
    bool mCanBeAutomaticallyReset;

private:
	/** The data layer this world event actor will interact with. */
	UPROPERTY( EditDefaultsOnly, Category = "WorldEvent" )
	TObjectPtr< UDataLayerAsset > mDataLayer;

	/** List of World Event Behaviors which will influence the world event. */
	UPROPERTY( EditAnywhere, Instanced, Category = "WorldEvent" )
	TArray< class UFGWorldEventBehavior* > mWorldEventBehaviors;

	/** Current state of this world event. */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_WorldEventState )
	EWorldEventState mState;
	
	/** Whether or not the world event actor is currently changing state. Used to make sure we don't try to do a state change in the middle of another one. */
	bool mIsChangingState;

	/** Timestamp of when the event was last finished. */
    float mLastFinishTimestamp;
};
