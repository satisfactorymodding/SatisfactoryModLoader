// Copyright Coffee Stain Studios. All Rights Reserved.

#include "GameplayEventsControllerComponent.h"

#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameplayEvent.h"
#include "GameplayEventsSubsystem.h"
#include "UnrealNetwork.h"

FReplicatedGameplayEvent::FReplicatedGameplayEvent(const FGameplayEvent& GameplayEvent) : EventTag(GameplayEvent.EventTag), Payload(GameplayEvent.Payload)
{
}

FArchive& operator<<(FArchive& Archive, FReplicatedGameplayEvent &Event)
{
	Archive << Event.EventTag;
	Archive << Event.Payload;
	return Archive;
}

bool FReplicatedGameplayEventStream::NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaSerializeInfo)
{
	if (DeltaSerializeInfo.bUpdateUnmappedObjects)
	{
		return true;
	}
	if (DeltaSerializeInfo.Writer)
	{
		FBitWriter& Writer = *DeltaSerializeInfo.Writer; 
		
		// Look for any events that haven't been flushed yet
		if (!EventQueue.IsEmpty())
		{
 			Writer << EventQueue;
			EventQueue.Reset();
			return true;
		}
	}
	else if (DeltaSerializeInfo.Reader)
	{
		FBitReader& Reader = *DeltaSerializeInfo.Reader;
		TArray<FReplicatedGameplayEvent> IncomingEvents;
		
		Reader << IncomingEvents;
		EventQueue.Append(MoveTemp(IncomingEvents));
		
		return true;
	}
	return false;
}

UGameplayEventsControllerComponent::UGameplayEventsControllerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UGameplayEventsControllerComponent::ReplicateGameplayEvent(const FGameplayEvent& GameplayEvent)
{
	if (ensure(GetOwner()->HasAuthority()))
	{
		ReplicatedEventStream.EventQueue.Emplace(GameplayEvent);
	}
}

void UGameplayEventsControllerComponent::ReplicationTick()
{
	if (!GetOwner()->HasAuthority())
	{
		for (const FReplicatedGameplayEvent& ReplicatedEvent: ReplicatedEventStream.EventQueue)
		{
			UGameplayEventsSubsystem* GameplayEventsSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameplayEventsSubsystem>();
			check(GameplayEventsSubsystem);

			FGameplayEvent Event;
			Event.Instigators = {Cast<APlayerController>(GetOwner())};
			Event.Payload = ReplicatedEvent.Payload;
			Event.EventTag = ReplicatedEvent.EventTag;
			
			GameplayEventsSubsystem->DispatchGameplayEvent(Event);
		}

		ReplicatedEventStream.EventQueue.Reset();
	}
}

void UGameplayEventsControllerComponent::BeginPlay()
{
	Super::BeginPlay();
	UGameplayEventsSubsystem* GameplayEventsSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameplayEventsSubsystem>();
	check(GameplayEventsSubsystem);

	GameplayEventsSubsystem->RegisterControllerComponent(this);
}

void UGameplayEventsControllerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UGameplayEventsSubsystem* GameplayEventsSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGameplayEventsSubsystem>();
	check(GameplayEventsSubsystem);

	GameplayEventsSubsystem->DeregisterControllerComponent(this);
}

void UGameplayEventsControllerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(UGameplayEventsControllerComponent, ReplicatedEventStream);

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
