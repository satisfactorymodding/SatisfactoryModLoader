// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

/**
 * Multi-dispatch socket is a socket that can bind multiple socket simultaneously and listen for their connections
 * This socket does not support anything other than binding, setting options and accepting pending connections.
 * The underlying sockets can be of different protocols and server subsystems.
 * Keep in mind that the bind address passed to the Bind of this socket will not be actually used.
 */
class FACTORYDEDICATEDSERVER_API FMultiDispatchSocket : public FSocket, public FNoncopyable
{
public:
	FMultiDispatchSocket(const FString& InSocketDescription);
	~FMultiDispatchSocket();
	void AddUnderlyingSocket( FUniqueSocket&& NewSocket, const TSharedRef<FInternetAddr>& BindAddress );
	
	// Begin FSocket interface
	virtual bool Shutdown(ESocketShutdownMode Mode) override;
	virtual bool Close() override;
	virtual bool Bind(const FInternetAddr& Addr) override;
	virtual bool Connect(const FInternetAddr& Addr) override;
	virtual bool Listen(int32 MaxBacklog) override;
	virtual bool WaitForPendingConnection(bool& bHasPendingConnection, const FTimespan& WaitTime) override;
	virtual bool HasPendingData(uint32& PendingDataSize) override;
	virtual class FSocket* Accept(const FString& InSocketDescription) override;
	virtual class FSocket* Accept(FInternetAddr& OutAddr, const FString& InSocketDescription) override;
	virtual bool SendTo(const uint8* Data, int32 Count, int32& BytesSent, const FInternetAddr& Destination) override;
	virtual bool Send(const uint8* Data, int32 Count, int32& BytesSent) override;
	virtual bool RecvFrom(uint8* Data, int32 BufferSize, int32& BytesRead, FInternetAddr& Source, ESocketReceiveFlags::Type Flags = ESocketReceiveFlags::None) override;
	virtual bool Recv(uint8* Data,int32 BufferSize,int32& BytesRead, ESocketReceiveFlags::Type Flags = ESocketReceiveFlags::None) override;
	virtual bool Wait(ESocketWaitConditions::Type Condition, FTimespan WaitTime) override;
	virtual ESocketConnectionState GetConnectionState() override;
	virtual void GetAddress(FInternetAddr& OutAddr) override;
	virtual bool GetPeerAddress(FInternetAddr& OutAddr) override;
	virtual bool SetNonBlocking(bool bIsNonBlocking = true) override;
	virtual bool SetNoDelay(bool bIsNoDelay = true) override;
	virtual bool SetBroadcast(bool bAllowBroadcast = true) override;
	virtual bool JoinMulticastGroup(const FInternetAddr& GroupAddress) override;
	virtual bool JoinMulticastGroup(const FInternetAddr& GroupAddress, const FInternetAddr& InterfaceAddress) override;
	virtual bool LeaveMulticastGroup(const FInternetAddr& GroupAddress) override;
	virtual bool LeaveMulticastGroup(const FInternetAddr& GroupAddress, const FInternetAddr& InterfaceAddress) override;
	virtual bool SetMulticastLoopback(bool bLoopback) override;
	virtual bool SetMulticastTtl(uint8 TimeToLive) override;
	virtual bool SetMulticastInterface(const FInternetAddr& InterfaceAddress) override;
	virtual bool SetReuseAddr(bool bAllowReuse = true) override;
	virtual bool SetLinger(bool bShouldLinger = true, int32 Timeout = 0) override;
	virtual bool SetRecvErr(bool bUseErrorQueue = true) override;
	virtual bool SetSendBufferSize(int32 Size,int32& NewSize) override;
	virtual bool SetReceiveBufferSize(int32 Size,int32& NewSize) override;
	virtual int32 GetPortNo() override;
	virtual bool SetIpPktInfo(bool bEnable) override;
	virtual bool RecvFromWithPktInfo(uint8* Data, int32 BufferSize, int32& BytesRead, FInternetAddr& Source, FInternetAddr& Destination, ESocketReceiveFlags::Type Flags = ESocketReceiveFlags::None) override;
	// End FSocket interface
protected:
	TArray<FUniqueSocket> Sockets;
	TMap<FSocket*, const TSharedRef<FInternetAddr>> SocketBindAddresses;
	TSharedPtr<FInternetAddr> LocalBindAddress;
};