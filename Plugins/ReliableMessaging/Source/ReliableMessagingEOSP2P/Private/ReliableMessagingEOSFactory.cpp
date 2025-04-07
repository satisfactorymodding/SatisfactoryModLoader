#include "ReliableMessagingEOSFactory.h"

bool FReliableMessagingServerEOS::StartListening(UNetDriver* InNetDriver){ return false;}
TArray<TUniquePtr<IReliableMessageTransportConnection>> FReliableMessagingServerEOS::Tick(float DeltaTime){ return TArray<TUniquePtr<IReliableMessageTransportConnection>>(); }
void FReliableMessagingServerEOS::Shutdown(){ }
void FReliableMessagingServerEOS::DispatchPacket(const TArray<uint8>& Data, TSharedRef<const FInternetAddrEOS> SenderAddress){ }
void FReliableMessagingServerEOS::ForgetAboutConnection(FEOSReliableDataTransferNetConnection* Connection){ }
TUniquePtr<IReliableMessageTransportServer> UReliableMessagingEOSFactory::CreateListeningServer(UNetDriver* NetDriver) const{ return Super::CreateListeningServer(NetDriver); }
TUniquePtr<IReliableMessageTransportConnection> UReliableMessagingEOSFactory::Connect(UNetConnection* Connection, const TArray<uint8>& CustomClientConnectionData, FGuid ConnectionId) const{ return Super::Connect(Connection, CustomClientConnectionData, ConnectionId); }
