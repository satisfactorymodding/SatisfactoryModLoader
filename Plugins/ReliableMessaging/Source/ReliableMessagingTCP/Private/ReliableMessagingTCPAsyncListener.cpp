#include "ReliableMessagingTCPAsyncListener.h"

#include "ReliableMessagingTCPAsyncConnHandler.h"

FReliableMessagingTCPAsyncListener::FReliableMessagingTCPAsyncListener(FUniqueSocket&& InSocket, ISocketSubsystem* InSocketSubsystem, FTimespan InExpectedConnectionLifetime){ }
void FReliableMessagingTCPAsyncListener::StartThread(){ }
void FReliableMessagingTCPAsyncListener::Terminate(){ }
void FReliableMessagingTCPAsyncListener::GetListenAddress(FInternetAddr& OutAddr) const{ }
bool FReliableMessagingTCPAsyncListener::DequeueIncomingConnectionHandler(TUniquePtr<FReliableMessagingTCPAsyncConnHandler>& OutHandler){ return false; }
void FReliableMessagingTCPAsyncListener::EnqueueExpectedConnectionPeer(TSharedPtr<FInternetAddr> PeerAddr, FGuid ConnectionId){ }
bool FReliableMessagingTCPAsyncListener::Init(){ return FRunnable::Init(); }
uint32 FReliableMessagingTCPAsyncListener::Run(){ return 0; }
void FReliableMessagingTCPAsyncListener::Stop(){ FRunnable::Stop(); }
