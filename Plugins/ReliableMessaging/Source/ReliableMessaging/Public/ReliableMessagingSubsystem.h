// Copyright Coffee Stain Studios. All Rights Reserved.
 
#pragma once

#include "Subsystems/WorldSubsystem.h"
#include "ReliableMessagingTransportLayer.h"

#include "ReliableMessagingSubsystem.generated.h"


class UReliableMessagingTransportLayerFactory;
class IReliableMessageTransportServer;
class UReliableMessagingPlayerComponent;
class APlayerController;

UCLASS()
class RELIABLEMESSAGING_API UReliableMessagingSubsystem : public UWorldSubsystem, public FTickableGameObject
{
	GENERATED_BODY()
	friend class UReliableMessagingPlayerComponent;
public:
	/**
	 * Will initialize the server side of the reliable message protocol. This should only be called on the server. Will be called by the world subsystem
	 * on BeginPlay but if the game code needs to initialize the server before that, this function can be called basically at any time after net driver is initialized.
	 */
	virtual void InitializeServer();

	struct FReliableMessagingFactoryRegistration
	{
		TSubclassOf<UReliableMessagingTransportLayerFactory> FactoryClass;
		int32 Priority = 0;
	};
	
	using FProvideTransportLayerFactoryDelegate = TMulticastDelegate<void(UNetDriver*, TArray<FReliableMessagingFactoryRegistration>&)>;
	static FProvideTransportLayerFactoryDelegate OnProvideTransportLayerFactoryClass;

	TSubclassOf<UReliableMessagingTransportLayerFactory> GetProtocolFactoryClass() const;
	
	/**
	 * Sends a single message. If called on the client, the payload is sent to the server. If called on the server, the payload is sent to the client.
	 */
	static void SendMessage(const APlayerController* Player, int32 Channel, TArray<uint8> InPayload);

	/**
	 * Returns the server instance. This is only valid on the server and only as long as the server is correctly initialized.
	 */
	IReliableMessageTransportServer* GetServer() const;

protected:
	void RegisterControllerComponentPendingConnection(UReliableMessagingPlayerComponent* UnmappedComponent);
	void RegisterControllerComponentClientSide(UReliableMessagingPlayerComponent* ClientComponent);
	void UnregisterControllerComponent(UReliableMessagingPlayerComponent* Component);
	
	// Begin UWorldSubsystem interface
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	// End UWorldSubsystem interface

	// Begin FTickableGameObject interface
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual bool IsTickableWhenPaused() const override;
	virtual TStatId GetStatId() const override;
	// End FTickableGameObject interface

	void OnNewIncomingConnection(TUniquePtr<IReliableMessageTransportConnection> Connection);
private:
	UPROPERTY()
	TMap<FGuid, TObjectPtr<UReliableMessagingPlayerComponent>> ControllerComponentsPendingConnection;

	UPROPERTY()
	TArray<TObjectPtr<UReliableMessagingPlayerComponent>> EstablishedConnections;

	TUniquePtr<IReliableMessageTransportServer> Server;
	
	UPROPERTY()
	TObjectPtr<UReliableMessagingTransportLayerFactory> ProtocolFactory;
};