#include "EOSReliableDataTransferNetConnection.h"

FEOSReliableDataTransferNetConnection::~FEOSReliableDataTransferNetConnection(){ }
FEOSReliableDataTransferNetConnection::FEOSReliableDataTransferNetConnection(TSharedRef<const FInternetAddrEOS> InAddr): FReliableDataTransferProtocolReader(0), FReliableDataTransferProtocolWriter(0){ }
FEOSReliableDataTransferNetConnection::FEOSReliableDataTransferNetConnection(UNetConnection* Connection, FGuid ConnectionId): FReliableDataTransferProtocolReader(0), FReliableDataTransferProtocolWriter(0){ }
const FInternetAddrEOS& FEOSReliableDataTransferNetConnection::GetAddress() const{ return *(new FInternetAddrEOS()); }
void FEOSReliableDataTransferNetConnection::ReceiveBytes(const uint8* InData, int32 InLength){ }
void FEOSReliableDataTransferNetConnection::InitServerSide(FSocketSubsystemEOS* InSocketSubsystem, FReliableMessagingServerEOS* InServer, TSharedPtr<const FInternetAddrEOS> InAddress, TSharedPtr<FSocketEOS> InSocket){ }
FGuid FEOSReliableDataTransferNetConnection::GetConnectionId() const{ return FGuid(); }
void FEOSReliableDataTransferNetConnection::EnqueueMessage(uint8 Channel, TArray<uint8>&& Message){ }
EReliableMessagingConnectionState FEOSReliableDataTransferNetConnection::Tick(float DeltaTime){ return EReliableMessagingConnectionState::Disconnected; }
void FEOSReliableDataTransferNetConnection::DispatchMessages(TFunction<void(RDTProtocol::FMessage&&)> MessageDispatcher){ }
void FEOSReliableDataTransferNetConnection::Close(){ }
TSharedPtr<const FInternetAddr> FEOSReliableDataTransferNetConnection::GetClientAddress() const{ return TSharedPtr<const FInternetAddr>(); }
void FEOSReliableDataTransferNetConnection::HandleConnectionIdReceived(FGuid InConnectionId){ }
void FEOSReliableDataTransferNetConnection::HandleMessageReceived(RDTProtocol::FMessage&& InMessage){ }
bool FEOSReliableDataTransferNetConnection::ReadData(uint8* Buffer, const int32 InBufferLength, int32& BytesRead){ return false; }
bool FEOSReliableDataTransferNetConnection::WriteData(const uint8* Data, const int32 InBufferLength, int32& BytesWritten){ return false; }
void FEOSReliableDataTransferNetConnection::CloseConnection(){ }
EReliableMessagingConnectionState FEOSReliableDataTransferNetConnection::GetConnectionState() const{ return EReliableMessagingConnectionState::Disconnected; }
bool FEOSReliableDataTransferNetConnection::Connect(UNetConnection* NetConnection, const FGuid& InConnectionId){ return false; }
bool FEOSReliableDataTransferNetConnection::SendPacket(const uint8* Data, int32 Count){ return false; }