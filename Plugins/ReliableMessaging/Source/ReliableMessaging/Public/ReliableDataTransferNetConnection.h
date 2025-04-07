// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Object.h"
#include "ReliableMessagingProtocol.h"
#include "ReliableDataTransferNetConnection.generated.h"

class UNetConnection;
/**
 * 
 */
UCLASS()
class RELIABLEMESSAGING_API UReliableDataTransferNetConnection : public UObject
{
	GENERATED_BODY()
public:
	virtual bool Connect(UNetConnection* NetConnection, int32 InServerPort, const FGuid& InConnectionId);
	virtual void Close();
	virtual void SendMessage(uint8 ChannelId, TArray<uint8>&& Data);

	FGuid GetConnectionId() const { return ConnectionId; }
	TDelegate<void(RDTProtocol::FMessage&&)> OnDispatchMessage;

	virtual void Tick(float DeltaTime) {}
protected:
	void DispatchMessage(RDTProtocol::FMessage&& Message);

	FGuid ConnectionId;
	int64 NextMessageId = 0;
};
