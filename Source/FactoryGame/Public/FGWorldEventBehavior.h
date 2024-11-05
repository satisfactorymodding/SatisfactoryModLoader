// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGWorldEventBehavior.generated.h"

/**
 * A World Event Behavior is an instanced object on a World Event Actor which can be used to add extra functionality.
 */
UCLASS( Abstract, BlueprintType, Blueprintable, EditInlineNew )
class FACTORYGAME_API UFGWorldEventBehavior : public UObject
{
	GENERATED_BODY()

	friend class AFGWorldEventActor;
public:	
	/** Returns the World Event Actor this behavior belongs to. */
	UFUNCTION( BlueprintPure, Category = "WorldEvent|Behavior" )
	FORCEINLINE class AFGWorldEventActor* GetWorldEventActor() const { return mWorldEventActor; }

protected:
	/** Runs when the world event activates. Called on both Server and Client. */
    UFUNCTION( BlueprintNativeEvent, Category = "WorldEvent|Behavior" )
    void OnWorldEventTriggered();

	/** Runs when the world event resets. Called on both Server and Client. */
	UFUNCTION( BlueprintNativeEvent, Category = "WorldEvent|Behavior" )
	void OnWorldEventReset();

	/** Runs when the world event finishes. Called on both Server and Client. */
	UFUNCTION( BlueprintNativeEvent, Category = "WorldEvent|Behavior" )
	void OnWorldEventFinished();

	/** Used to initialize the world event behavior. Runs from BeginPlay of the World Event Actor. */
	UFUNCTION( BlueprintNativeEvent, Category = "WorldEvent|Behavior" )
	void Initialize();

protected:
	bool HasAuthority() const;

private:
	UPROPERTY()
	class AFGWorldEventActor* mWorldEventActor;
};

/**
 * A World Event Behavior which uses a timer.
 * TODO: Elapsed time state, we don't always wanna start the timer from the beginning.
 */
UCLASS( Abstract )
class FACTORYGAME_API UFGWorldEventBehavior_Timer : public UFGWorldEventBehavior
{
	GENERATED_BODY()
public:
	UFGWorldEventBehavior_Timer();
	
	virtual void Initialize_Implementation() override;
	virtual void OnWorldEventTriggered_Implementation() override;
	virtual void OnWorldEventReset_Implementation() override;
	virtual void OnWorldEventFinished_Implementation() override;

	/** Starts / Restarts the behavior timer. */
	UFUNCTION( BlueprintCallable, Category = "WorldEvent|Behavior" )
	void StartTimer();
	
	/** Called when the world event behavior timer finishes. */
	UFUNCTION( BlueprintCallable, Category = "WorldEvent|Behavior" )
	void StopTimer();

protected:
	/** Called when the world event behavior timer triggers. Runs on server only. */
	UFUNCTION( BlueprintNativeEvent, Category = "WorldEvent|Behavior" )
	void OnTimerTriggered();

private:
	/** How long until the behavior timer finishes. */
	UPROPERTY( EditAnywhere, Category = "Timer" )
	float mDuration;

private:
	FTimerHandle mTimerHandle;
};

/**
 * World Event Behavior used to automatically finish a World Event after a specified duration.
 */
UCLASS()
class FACTORYGAME_API UFGWorldEventBehavior_FinishAfterDuration : public UFGWorldEventBehavior_Timer
{
	GENERATED_BODY()
public:
	UFGWorldEventBehavior_FinishAfterDuration();
	
protected:
	virtual void OnTimerTriggered_Implementation() override;
};