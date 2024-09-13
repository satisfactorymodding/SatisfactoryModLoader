// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEvent.h"
#include "Tickable.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "GameplayEventsSubsystem.generated.h"

class UGameplayEventsControllerComponent;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameplayEventTriggeredK2, const FGameplayEvent&, GameplayEvent);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameplayEventTriggered, const FGameplayEvent& GameplayEvent);

/**
 * A subsystem that can be used as a generic event dispatcher. Promotes loose coupling between components.  
 */
UCLASS()
class GAMEPLAYEVENTS_API UGameplayEventsSubsystem: public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()
	friend class UGameplayEventsControllerComponent;
public:
	/**
	 * Dispatches a gameplay event. The event is dispatched to subscribers immediately
	 * @param GameplayEvent The gameplay event to be dispatched
	 */
	UFUNCTION(BlueprintCallable, Category=GameplayEvents)
	void DispatchGameplayEvent(const FGameplayEvent& GameplayEvent);

	FDelegateHandle AddOnGameplayEventDelegate(FOnGameplayEventTriggered::FDelegate&& Delegate);
	void RemoveOnGameplayEventDelegate(FDelegateHandle DelegateHandle);

	/**
	 * Registers the @ControllerComponent with the subsystem, in effect enabling gameplay event replication for the owning player
	 */
	void RegisterControllerComponent(UGameplayEventsControllerComponent* ControllerComponent);

	/**
	 * De-registers the @ControllerComponent with the subsystem, thus disabling gameplay event replication for the owning player
	 */
	void DeregisterControllerComponent(UGameplayEventsControllerComponent* ControllerComponent);
	
protected:
	// Begin FTickableGameObject
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	// End FTickableGameObject
	
	UPROPERTY(BlueprintAssignable, Category=GameplayEvents)
	FOnGameplayEventTriggeredK2 OnGameplayEventTriggered;
	FOnGameplayEventTriggered OnGameplayEventTriggeredNative;

	UPROPERTY()
	TSet<TObjectPtr<UGameplayEventsControllerComponent>> ControllerComponents;

	/**
	 * Events are placed in this array before being dispatched asynchronously on tick.
	 */
	UPROPERTY()
	TArray<FGameplayEvent> EventQueue;
};
