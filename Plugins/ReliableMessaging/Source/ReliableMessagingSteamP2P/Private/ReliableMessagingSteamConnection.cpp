#include "ReliableMessagingSteamConnection.h"

FReliableMessagingSteamConnection::FReliableMessagingSteamConnection(UNetConnection* Connection, FGuid ConnectionId): FReliableDataTransferProtocolReader(0), FReliableDataTransferProtocolWriter(0){ }
FReliableMessagingSteamConnection::FReliableMessagingSteamConnection(HSteamNetConnection InConnectionHandle, FSteamSocketsSubsystem* InSocketSubsystem): FReliableDataTransferProtocolReader(0), FReliableDataTransferProtocolWriter(0){ }
FReliableMessagingSteamConnection::~FReliableMessagingSteamConnection(){ }
void FReliableMessagingSteamConnection::EnqueueMessage(uint8 Channel, TArray<uint8>&& Message){ }
FGuid FReliableMessagingSteamConnection::GetConnectionId() const { return FGuid(); }
EReliableMessagingConnectionState FReliableMessagingSteamConnection::Tick(float DeltaTime){ return EReliableMessagingConnectionState::Disconnected; }
void FReliableMessagingSteamConnection::DispatchMessages(TFunction<void(RDTProtocol::FMessage&&)> MessageDispatcher){ }
void FReliableMessagingSteamConnection::Close(){ }
bool FReliableMessagingSteamConnection::HasReceivedConnectionId() const{ return false; }
void FReliableMessagingSteamConnection::HandleConnectionIdReceived(FGuid InConnectionId){ }
void FReliableMessagingSteamConnection::HandleMessageReceived(RDTProtocol::FMessage&& InMessage){ }
bool FReliableMessagingSteamConnection::ReadData(uint8* Buffer, const int32 BufferLength, int32& BytesRead){ return false; }
bool FReliableMessagingSteamConnection::WriteData(const uint8* Data, const int32 BufferLength, int32& BytesWritten){ return false; }
void FReliableMessagingSteamConnection::CloseConnection(){ }
void FReliableMessagingSteamConnection::OnSteamConnectionStatusChanged(
	SteamNetConnectionStatusChangedCallback_t* Callback){ }