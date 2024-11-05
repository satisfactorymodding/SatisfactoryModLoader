// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGWorldEventActor.h"
#include "FGSubsystem.h"
#include "HAL/IConsoleManager.h"
#include "FGWorldEventSubsystem.generated.h"

FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogWorldEvent, Log, All );

extern TAutoConsoleVariable<int32> CVarWorldEventDebug;

/**
 * Subsystem used to manage World Events in the level.
 */
UCLASS()
class FACTORYGAME_API AFGWorldEventSubsystem : public AFGSubsystem
{
	GENERATED_BODY()

public:
	/** Get the subsystem, this should always return something unless you call it really early. */
	static AFGWorldEventSubsystem* Get( UWorld* world );

	/** Get the subsystem from a world context, this should always return something unless you call it really early. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|WorldEvent", DisplayName = "GetWorldEventSubsystem", Meta = (DefaultToSelf = "worldContext") )
	static AFGWorldEventSubsystem* Get( UObject* worldContext );

	AFGWorldEventSubsystem();

	// Begin AActor interface
	virtual void Tick( float dt ) override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	// End AActor interface

	void RegisterWorldEventActor( class AFGWorldEventActor* worldEventActor );
	void UnregisterWorldEventActor( class AFGWorldEventActor* worldEventActor );

	/** Enables / Disables automatic world events. */
	UFUNCTION( BlueprintCallable, Category = "WorldEvent" )
	void SetAutomaticWorldEventsEnabled( bool enabled );

	/** Whether or not automatic world events are enabled. */
	UFUNCTION( BlueprintPure, Category = "WorldEvent" )
	FORCEINLINE bool IsAutomaticWorldEventsEnabled() const { return mAllowAutomaticWorldEvents; }

	/** Gets all registered World Event Actors. */
	UFUNCTION( BlueprintPure, Category = "WorldEvent" )
	FORCEINLINE TArray< class AFGWorldEventActor* > const& GetAllWorldEventActors() const { return mWorldEventActors; }

	/** Triggers a random World Event.
	 * @param bIncludeManual Whether or not to include World Events which are set to only trigger manually.
	 * @return The triggered World Event Actor, if successful.
	 */
	UFUNCTION( BlueprintCallable, Category = "WorldEvent" )
	AFGWorldEventActor* TriggerRandomWorldEvent( bool bIncludeManual = false );

private:
	/** Automatic World Event timer function. */
	UFUNCTION()
	void AutomaticallyTriggerWorldEvent();

	void StartAutomaticWorldEventTimer( bool bForceRestart = false );
	void StopAutomaticWorldEventTimer();
	
	void ManageWorldEventActors();
	void UpdateWorldEventActor( class AFGWorldEventActor* worldEventActor );

	/** Called when any world event gets triggered. Both server and client. */
	UFUNCTION()
	void OnAnyWorldEventTriggered( class AFGWorldEventActor* worldEventActor );

	/** Called when any world event gets reset. Both server and client. */
	UFUNCTION()
	void OnAnyWorldEventReset( class AFGWorldEventActor* worldEventActor );

	/** Called when any world event gets finished. Both server and client. */
	UFUNCTION()
    void OnAnyWorldEventFinished( class AFGWorldEventActor* worldEventActor );

public:
	/** Delegate called when any world event gets triggered. Called on both server and client. */
	UPROPERTY( BlueprintAssignable, Category = "WorldEvent" )
	FWorldEventDelegate mOnAnyWorldEventTriggered;
	
	/** Delegate called when any world event gets reset. Called on both server and client. */
	UPROPERTY( BlueprintAssignable, Category = "WorldEvent" )
	FWorldEventDelegate mOnAnyWorldEventReset;
	
	/** Delegate called when any world event gets finished. Called on both server and client. */
	UPROPERTY( BlueprintAssignable, Category = "WorldEvent" )
	FWorldEventDelegate mOnAnyWorldEventFinished;

private:
	/** How much time should pass between triggering world events. */
	UPROPERTY( EditDefaultsOnly, Category = "WorldEvent" )
	FFloatInterval mWorldEventInterval;

	/** Whether or not automatic world events are allowed. */
	UPROPERTY( EditDefaultsOnly, Category = "WorldEvent" )
	bool mAllowAutomaticWorldEvents;

	/** If the amount of active world events exceed this number, then don't allow any more automatic world events to trigger. <= 0 to disable limit. */
	UPROPERTY( EditDefaultsOnly, Category = "WorldEvent" )
	int32 mAutomaticWorldEventActiveLimit;

	/** All registered world event actors. */
	UPROPERTY( Replicated )
	TArray< class AFGWorldEventActor* > mWorldEventActors;

	/** Timer used for triggering world events automatically. */
	FTimerHandle mWorldEventTimerHandle;
};
