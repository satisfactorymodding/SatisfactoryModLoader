#include "ReliableMessagingTCPAsyncConnHandler.h"

#include "ReliableMessagingTransportLayer.h"

FReliableMessagingTCPAsyncConnHandler::FReliableMessagingTCPAsyncConnHandler(ISocketSubsystem* InSocketSubsystem, FUniqueSocket&& InSocket): FReliableDataTransferProtocolReader(0), RemoteAddress(ISocketSubsystem::Get()->CreateInternetAddr()){ }
FReliableMessagingTCPAsyncConnHandler::~FReliableMessagingTCPAsyncConnHandler(){ }
void FReliableMessagingTCPAsyncConnHandler::StartThread(){ }
void FReliableMessagingTCPAsyncConnHandler::Terminate(){ }
void FReliableMessagingTCPAsyncConnHandler::GetRemoteAddress(FInternetAddr& Addr) const{ }
FGuid FReliableMessagingTCPAsyncConnHandler::GetConnectionId() const{ return FGuid(); }
bool FReliableMessagingTCPAsyncConnHandler::HasReceivedConnectionId() const{ return false; }
void FReliableMessagingTCPAsyncConnHandler::HandleConnectionIdReceived(FGuid InConnectionId){ }
void FReliableMessagingTCPAsyncConnHandler::HandleMessageReceived(RDTProtocol::FMessage&& InMessage){ }
bool FReliableMessagingTCPAsyncConnHandler::ReadData(uint8* Buffer, const int32 InBufferLength, int32& BytesRead){ return false; }
void FReliableMessagingTCPAsyncConnHandler::CloseConnection(){ }
EReliableMessagingConnectionState FReliableMessagingTCPAsyncConnHandler::GetConnectionState() const{ return EReliableMessagingConnectionState::Disconnected; }
bool FReliableMessagingTCPAsyncConnHandler::Init(){ return FRunnable::Init(); }
uint32 FReliableMessagingTCPAsyncConnHandler::Run(){ return 0; }
void FReliableMessagingTCPAsyncConnHandler::Stop(){ FRunnable::Stop(); }
