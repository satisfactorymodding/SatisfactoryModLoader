#include "ReliableMessageProtocolTCPServer.h"

FReliableMessageProtocolTCPServer::~FReliableMessageProtocolTCPServer(){ }
bool FReliableMessageProtocolTCPServer::StartListening(UNetDriver* InNetDriver, const UReliableMessagingTCPFactory& Factory){ return false; }
int32 FReliableMessageProtocolTCPServer::GetListenPort() const{ return 0; }
void FReliableMessageProtocolTCPServer::Shutdown(){ }
TArray<TUniquePtr<IReliableMessageTransportConnection>> FReliableMessageProtocolTCPServer::Tick(float DeltaTime){ return TArray<TUniquePtr<IReliableMessageTransportConnection>>(); }
void FReliableMessageProtocolTCPServer::ComputeListenPort(const UReliableMessagingTCPFactory& Factory, int32 BoundPort, bool bPortFromCommandLine){ }
FReliableMessageProtocolTCPConnection::~FReliableMessageProtocolTCPConnection(){ }
FReliableMessageProtocolTCPConnection::FReliableMessageProtocolTCPConnection(UNetConnection* NetConnection, uint16 ListeningPort, FGuid InConnectionId): FReliableDataTransferProtocolWriter(0){ }
FReliableMessageProtocolTCPConnection::FReliableMessageProtocolTCPConnection(TUniquePtr<FReliableMessagingTCPAsyncConnHandler>&& InConnectionHandler): FReliableDataTransferProtocolWriter(0){ }
bool FReliableMessageProtocolTCPConnection::WriteData(const uint8* Data, const int32 BufferLength, int32& BytesWritten){ return false; }
FGuid FReliableMessageProtocolTCPConnection::GetConnectionId() const{ return FGuid(); }
void FReliableMessageProtocolTCPConnection::EnqueueMessage(uint8 Channel, TArray<uint8>&& Message){ }
EReliableMessagingConnectionState FReliableMessageProtocolTCPConnection::Tick(float DeltaTime){ return EReliableMessagingConnectionState::Disconnected; }
void FReliableMessageProtocolTCPConnection::DispatchMessages(TFunction<void(RDTProtocol::FMessage&&)> MessageDispatcher){ }
void FReliableMessageProtocolTCPConnection::Close(){ }