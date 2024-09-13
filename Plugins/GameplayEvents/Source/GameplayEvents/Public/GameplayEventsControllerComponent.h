// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Misc/Variant.h"
#include "Net/Serialization/FastArraySerializer.h"

#include "GameplayEventsControllerComponent.generated.h"

struct FGameplayEvent;

USTRUCT()
struct FReplicatedGameplayEvent
{
	GENERATED_BODY()

	FReplicatedGameplayEvent() = default;
	FReplicatedGameplayEvent(const FReplicatedGameplayEvent&) = default;
	FReplicatedGameplayEvent(FReplicatedGameplayEvent&&) = default;

	FReplicatedGameplayEvent& operator=(const FReplicatedGameplayEvent&) = default;
	FReplicatedGameplayEvent& operator=(FReplicatedGameplayEvent&&) = default;

	explicit FReplicatedGameplayEvent(const FGameplayEvent& GameplayEvent);
	
	/**
	 * A tag that uniquely identifies an event
	 */
	UPROPERTY(VisibleAnywhere)
	FGameplayTag EventTag;

	FVariant Payload;

	friend FArchive& operator<<(FArchive& Archive, FReplicatedGameplayEvent &Event);
};

/**
 * An event queue where the server pushes events and the client pulls them. 
 */ 
USTRUCT()
struct FReplicatedGameplayEventStream
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FReplicatedGameplayEvent> EventQueue;

	bool NetDeltaSerialize(FNetDeltaSerializeInfo &DeltaSerializeInfo);
};

template<>
struct TStructOpsTypeTraits<FReplicatedGameplayEventStream>: public TStructOpsTypeTraitsBase2<FReplicatedGameplayEventStream>
{
	enum { WithNetDeltaSerializer = true };
};

/**
 *	Player controller component that enables replication of gameplay events for the owning player.
 */
UCLASS(ClassGroup = (GameplayEvents), Within = PlayerController)
class GAMEPLAYEVENTS_API UGameplayEventsControllerComponent : public UActorComponent
{
	GENERATED_BODY()
	friend class UGameplayEventsSubsystem;
public:
	// Sets default values for this component's properties
	UGameplayEventsControllerComponent();
	
protected:
	void ReplicateGameplayEvent(const FGameplayEvent& GameplayEvent);
	void ReplicationTick();

	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated)
	FReplicatedGameplayEventStream ReplicatedEventStream;
};
