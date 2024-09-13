// Copyright Coffee Stain Studios. All Rights Reserved.

#include "GameplayEventsSubsystem.h"

#include "GameFramework/PlayerController.h"
#include "GameplayEvent.h"
#include "GameplayEventsControllerComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameplayEvents, Log, Verbose);

void UGameplayEventsSubsystem::DispatchGameplayEvent(const FGameplayEvent& GameplayEvent)
{
	// These ensures should probably be removed later. They are very useful for Satisfactory but might not be correct in future projects.
	for (const auto instigator : GameplayEvent.Instigators)
	{
		if (!IsValid(instigator))
		{
			ensureMsgf(instigator, TEXT("Nullptr instigator sent to UGameplayEventsSubsystem::DispatchGameplayEvent()."));
			UE_LOG(LogGameplayEvents, Error, TEXT("Nullptr instigator sent to UGameplayEventsSubsystem::DispatchGameplayEvent()."));
			FDebug::DumpStackTraceToLog(ELogVerbosity::Error);
			return;
		}
	}
	EventQueue.Add(GameplayEvent);
}

FDelegateHandle UGameplayEventsSubsystem::AddOnGameplayEventDelegate(FOnGameplayEventTriggered::FDelegate&& Delegate)
{
	return OnGameplayEventTriggeredNative.Add(Delegate);
}

void UGameplayEventsSubsystem::RemoveOnGameplayEventDelegate(FDelegateHandle DelegateHandle)
{
	OnGameplayEventTriggeredNative.Remove(DelegateHandle);
}

void UGameplayEventsSubsystem::RegisterControllerComponent(UGameplayEventsControllerComponent* ControllerComponent)
{
	ControllerComponents.Add(ControllerComponent);
}

void UGameplayEventsSubsystem::DeregisterControllerComponent(UGameplayEventsControllerComponent* ControllerComponent)
{
	ControllerComponents.Remove(ControllerComponent);
}

void UGameplayEventsSubsystem::Tick(float DeltaTime)
{
	for (const auto& GameplayEvent : EventQueue)
	{
		UE_LOG(LogGameplayEvents, Verbose, TEXT("Dispatchintg gameplay event %s. Instigators: %d"), *GameplayEvent.EventTag.ToString(), GameplayEvent.Instigators.Num());

		// Log a few more likely types of payload
		if (GameplayEvent.Payload.GetType() == EVariantTypes::Int32)
		{
			UE_LOG(LogGameplayEvents, Verbose, TEXT("Int payload: %d"), GameplayEvent.Payload.GetValue<int32>());
		}
		else if (GameplayEvent.Payload.GetType() == EVariantTypes::String)
		{
			UE_LOG(LogGameplayEvents, Verbose, TEXT("String payload: '%s'"), *GameplayEvent.Payload.GetValue<FString>());
		}

		OnGameplayEventTriggeredNative.Broadcast(GameplayEvent);
		OnGameplayEventTriggered.Broadcast(GameplayEvent);

		for (const APlayerController* Instigator : GameplayEvent.Instigators)
		{
			if (!Instigator->IsLocalController())
			{
				if (UGameplayEventsControllerComponent* Component = Instigator->GetComponentByClass<UGameplayEventsControllerComponent>(); IsValid(Component))
				{
					Component->ReplicateGameplayEvent(GameplayEvent);
				}
			}
		}
	}

	EventQueue.Reset();

	for (UGameplayEventsControllerComponent* Component: ControllerComponents)
	{
		Component->ReplicationTick();
	}
}

TStatId UGameplayEventsSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UGameplayEventsSubsystem, STATGROUP_Tickables);
}
