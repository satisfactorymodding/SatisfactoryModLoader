#include "ReliableMessagingPlayerComponent.h"
#include "ReliableMessagingTransportLayer.h"

UReliableMessagingPlayerComponent::UReliableMessagingPlayerComponent(){ }
void UReliableMessagingPlayerComponent::SendTaggedMessage(FGameplayTag Tag, TArray<uint8> InPayload){ }
const FGuid& UReliableMessagingPlayerComponent::GetConnectionId() const{ return ConnectionId; }
UReliableMessagingPlayerComponent* UReliableMessagingPlayerComponent::GetFromPlayer(const APlayerController* PlayerController){ return nullptr; }
void UReliableMessagingPlayerComponent::RegisterTaggedMessageHandler(FGameplayTag Tag, FOnBulkDataReplicationPayloadReceived Handler){ }
void UReliableMessagingPlayerComponent::SetTransportLayerConnection(TUniquePtr<IReliableMessageTransportConnection> InConnection){ }
void UReliableMessagingPlayerComponent::TickConnection(float DeltaTime){ }
void UReliableMessagingPlayerComponent::BeginPlay(){ Super::BeginPlay(); }
void UReliableMessagingPlayerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
void UReliableMessagingPlayerComponent::Server_RequestInitiateConnection_Implementation(){ }
void UReliableMessagingPlayerComponent::Client_AcknowledgeConnectionAdvertisement_Implementation(){ }
APlayerController* UReliableMessagingPlayerComponent::GetOwningPlayerController() const{ return nullptr; }
FDateTime UReliableMessagingPlayerComponent::GetHandshakeBeginTime() const{ return FDateTime(); }
void UReliableMessagingPlayerComponent::TriggerDC(){ }
void UReliableMessagingPlayerComponent::Client_InitiateConnection_Implementation(TSubclassOf<UReliableMessagingTransportLayerFactory> FactoryClass, const TArray<uint8>& InConnectionData){ }
void UReliableMessagingPlayerComponent::Server_AdvertiseNewConnection_Implementation(const FGuid& ConnectionIdentity){ }
