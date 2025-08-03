#include "ReliableDataTransferNetConnection.h"

bool UReliableDataTransferNetConnection::Connect(UNetConnection* NetConnection, int32 InServerPort, const FGuid& InConnectionId){ return false; }
void UReliableDataTransferNetConnection::Close(){ }
void UReliableDataTransferNetConnection::SendMessage(uint8 ChannelId, TArray<uint8>&& Data){ }
void UReliableDataTransferNetConnection::DispatchMessage(RDTProtocol::FMessage&& Message){ }
