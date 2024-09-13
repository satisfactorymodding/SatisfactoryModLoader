// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PacketHandler.h"

enum class EServerSubStateId : uint8;
enum class EServerFlags : uint64;
enum class EServerState : uint8;
class UNetDriver;

struct FFGProcessServerQueryData
{
	int32 MagicHeaderNumBits{};
	uint32 MagicHeaderUint{};
	EServerState ServerState{};
	EServerFlags ServerFlags{};
	FString ServerName;
	TMap<EServerSubStateId, uint16> ServerSubStateVersions;
};

class FACTORYDEDICATEDSERVER_API FDSQueryHandlerComponent : public HandlerComponent
{
public:
	FDSQueryHandlerComponent();

	// Begin HandlerComponent interface
	virtual void Initialize() override;
	virtual bool IsValid() const override;
	virtual int32 GetReservedPacketBits() const override;
	virtual void IncomingConnectionless(FIncomingPacketRef PacketRef) override;
	// End HandlerComponent interface

	void ProcessQueryPacket( FBitReader& Packet, const TSharedPtr<const FInternetAddr>& RemoteAddress ) const;

	/** Note: This function does not read MagicHeader from the packet buffer, and does not write terminator bit to the response packet. */
	static bool StaticProcessQueryPacket( FFGProcessServerQueryData& QueryData, FBitReader& Packet, FBitWriter& ResponsePacket );
public:
	static const FName HandlerName;
	
	// The net driver that owns this handler component. Component will not be activated without a valid net driver.
	UNetDriver* OwnerNetDriver{nullptr};
protected:
	int32 MagicHeaderNumBits{};
	uint32 MagicHeaderUint{};
};
