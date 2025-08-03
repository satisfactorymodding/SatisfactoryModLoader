// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FGLightweightBuildableReplicationComponent.generated.h"

struct FLightweightBuildableReplicationSendState;
struct FLightweightBuildableRemovalData;
class AFGBuildable;
class AFGLightweightBuildableSubsystem;
class AFGBuildableSubsystem;
enum class ELightweightBuildableMessageId : uint32;
struct FLightweightBuildableConstructionData;
struct FLightweightBuildableInitialReplicationMessage;
struct FLightweightBuildableUpdateMessage;
struct FLightweightBuildableRemovalMessage;
struct FLightweightBuildableConstructionMessage;
struct FFactoryCustomizationData;
struct FRuntimeBuildableInstanceData;
struct FLightweightBuildableUpdateData;

UCLASS(NotBlueprintable, Within = FGPlayerController)
class FACTORYGAME_API UFGLightweightBuildableReplicationComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UFGLightweightBuildableReplicationComponent();
	
	// Begin UActorComponent interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// End UActorComponent interface

	FORCEINLINE bool HasReceivedInitialReplicationData() const { return bReceivedInitialReplicationMessage; }

	/** Functions called from the lightweight buildable subsystem to notify the component of the events within the subsystem */
	void HandleBuildableInstanceConstructed(const TSubclassOf<AFGBuildable>& BuildableClass, const FRuntimeBuildableInstanceData& RuntimeData, int32 InstanceID, uint16 ConstructionID, AActor* ConstructionInstigator, int32 BlueprintBuildEffectIndex) const;
	void HandleBuildableInstanceRemoved(const TSubclassOf<AFGBuildable>& BuildableClass, int32 InstanceID) const;
	void HandleBuildableInstanceUpdated(const TSubclassOf<AFGBuildable>& BuildableClass, const FRuntimeBuildableInstanceData& RuntimeData, int32 InstanceID) const;
protected:
	
	/** Handles lightweight buildable reliable message */
	void HandleRawLightweightBuildableMessage(TArray<uint8>&& InMessageData);
	/** Sends a lightweight buildable reliable message */
	void SendRawLightweightBuildableMessage(ELightweightBuildableMessageId MessageId, const TFunctionRef<void(FArchive&)>& MessageSerializer) const;
	
	/** Sends a lightweight buildable message to the player */
    template<typename T>
    void SendLightweightBuildableMessage(T& Message)
    {
    	SendRawLightweightBuildableMessage(T::MessageId, [&](FArchive& Ar) { Ar << Message; });
    }

	/** Message handlers for various message types */
	void ReceivedInitialReplicationMessage(const FLightweightBuildableInitialReplicationMessage& InitialReplicationMessage);
	void ReceivedConstructionMessage(const FLightweightBuildableConstructionMessage& ConstructionMessage) const;
	void ReceivedRemovalMessage(const FLightweightBuildableRemovalMessage& RemovalMessage) const;
	void ReceivedUpdateMessage(const FLightweightBuildableUpdateMessage& UpdateMessage) const;

	/** Sends the initial replication message to the player */
	void SendInitialReplicationMessage();
	void SendIncrementalUpdateReplicationMessage();
	
	/** Handles construction message for a bunch of lightweight buildables */
	void HandleLightweightBuildableConstructionData(const FLightweightBuildableConstructionData& ConstructionData) const;
private:
	/** True if we have received initial replication data */
	bool bReceivedInitialReplicationMessage{false};
	/** True if the message containing the initial replication data has been sent */
	bool bSentInitialReplicationMessage{false};
	/** Send state used to squash and send the lightweight buildable replication events */
	TSharedPtr<FLightweightBuildableReplicationSendState> CurrentSendState;

	/** Cached lightweight buildable subsystem this component is mapped to */
	UPROPERTY()
	AFGLightweightBuildableSubsystem* LightweightBuildableSubsystem{};
	
	/** Cached buildable subsystem */
	UPROPERTY()
	AFGBuildableSubsystem* BuildableSubsystem{};
};