// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ReliableMessagingSteamConnection.h"
#include "ReliableMessagingTransportLayer.h"
#include "SteamSocketsSubsystem.h"
#include "steam/isteamnetworkingutils.h"

class FReliableMessagingSteamServer : public IReliableMessageTransportServer
{
public:
	virtual ~FReliableMessagingSteamServer() override;
	
	bool StartListening(UNetDriver* InNetDriver);
	virtual TArray<TUniquePtr<IReliableMessageTransportConnection>> Tick(float DeltaTime) override;
	virtual void Shutdown() override;

private:
	void OnSteamConnectionStatusChanged(SteamNetConnectionStatusChangedCallback_t* Callback);
	FSteamSocketsSubsystem* SocketSubsystem = nullptr;
	TArray<TUniquePtr<FReliableMessagingSteamConnection>> PendingConnections;
	FDelegateHandle SteamConnectionStatusChangedHandle;
	HSteamListenSocket ListenSocketHandle = k_HSteamNetConnection_Invalid;
	HSteamNetPollGroup PollGroup = k_HSteamNetPollGroup_Invalid;
};
