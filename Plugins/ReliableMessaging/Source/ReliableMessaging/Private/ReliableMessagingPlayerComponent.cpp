#include "ReliableMessagingPlayerComponent.h"

UReliableMessagingPlayerComponent::UReliableMessagingPlayerComponent(){ }
void UReliableMessagingPlayerComponent::SendMessage(int32 Channel, TArray<uint8> InPayload){ }
const FGuid& UReliableMessagingPlayerComponent::GetConnectionId() const{ return ConnectionId; }
UReliableMessagingPlayerComponent* UReliableMessagingPlayerComponent::GetFromPlayer(const APlayerController* PlayerController){ return nullptr; }
void UReliableMessagingPlayerComponent::RegisterMessageHandler(int32 Channel, FOnBulkDataReplicationPayloadReceived Handler){ }
void UReliableMessagingPlayerComponent::SetTransportLayerConnection(TUniquePtr<IReliableMessageTransportConnection> InConnection){ }
void UReliableMessagingPlayerComponent::TickConnection(float DeltaTime){ }
void UReliableMessagingPlayerComponent::BeginPlay(){ Super::BeginPlay(); }
void UReliableMessagingPlayerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
APlayerController* UReliableMessagingPlayerComponent::GetOwningPlayerController() const{ return nullptr; }
void UReliableMessagingPlayerComponent::TriggerDC(){ }
void UReliableMessagingPlayerComponent::Client_InitiateConnection_Implementation(TSubclassOf<UReliableMessagingTransportLayerFactory> FactoryClass, const TArray<uint8>& InConnectionData){ }
void UReliableMessagingPlayerComponent::Server_AdvertiseNewConnection_Implementation(const FGuid& ConnectionIdentity){ }
