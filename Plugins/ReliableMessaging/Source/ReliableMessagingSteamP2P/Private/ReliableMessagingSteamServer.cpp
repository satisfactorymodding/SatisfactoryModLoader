#include "ReliableMessagingSteamServer.h"

FReliableMessagingSteamServer::~FReliableMessagingSteamServer(){ }
bool FReliableMessagingSteamServer::StartListening(UNetDriver* InNetDriver){ return false; }
TArray<TUniquePtr<IReliableMessageTransportConnection>> FReliableMessagingSteamServer::Tick(float DeltaTime){ return TArray<TUniquePtr<IReliableMessageTransportConnection>>(); }
void FReliableMessagingSteamServer::Shutdown(){ }
void FReliableMessagingSteamServer::RegisterIncomingConnection(TSharedRef<FInternetAddr> Address, FGuid ConnectionId){ }
void FReliableMessagingSteamServer::OnSteamConnectionStatusChanged(SteamNetConnectionStatusChangedCallback_t* Callback){ }
