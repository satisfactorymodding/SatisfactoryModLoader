#include "ReliableMessagingSubsystem.h"

float UReliableMessagingSubsystem::GetDefaultConnectionTimeoutSeconds(){ return float(); }
void UReliableMessagingSubsystem::InitializeServer(){ }
TSubclassOf<UReliableMessagingTransportLayerFactory> UReliableMessagingSubsystem::GetProtocolFactoryClass() const{ return nullptr; }
void UReliableMessagingSubsystem::SendTaggedMessage(const APlayerController* Player, FGameplayTag Tag, TArray<uint8> InPayload){ }
IReliableMessageTransportServer* UReliableMessagingSubsystem::GetServer() const{ return nullptr; }
bool UReliableMessagingSubsystem::RegisterControllerComponentPendingConnection(UReliableMessagingPlayerComponent* UnmappedComponent){ return false; }
void UReliableMessagingSubsystem::RegisterControllerComponentClientSide(UReliableMessagingPlayerComponent* ClientComponent){ }
void UReliableMessagingSubsystem::UnregisterControllerComponent(UReliableMessagingPlayerComponent* Component){ }
void UReliableMessagingSubsystem::Initialize(FSubsystemCollectionBase& Collection){ Super::Initialize(Collection); }
void UReliableMessagingSubsystem::Deinitialize(){ Super::Deinitialize(); }
bool UReliableMessagingSubsystem::DoesSupportWorldType(const EWorldType::Type WorldType) const{ return Super::DoesSupportWorldType(WorldType); }
void UReliableMessagingSubsystem::OnWorldBeginPlay(UWorld& InWorld){ Super::OnWorldBeginPlay(InWorld); }
void UReliableMessagingSubsystem::Tick(float DeltaTime){ }
bool UReliableMessagingSubsystem::IsTickable() const{ return FTickableGameObject::IsTickable(); }
bool UReliableMessagingSubsystem::IsTickableWhenPaused() const{ return FTickableGameObject::IsTickableWhenPaused(); }
TStatId UReliableMessagingSubsystem::GetStatId() const{ return TStatId(); }
void UReliableMessagingSubsystem::OnNewIncomingConnection(TUniquePtr<IReliableMessageTransportConnection> Connection){ }
