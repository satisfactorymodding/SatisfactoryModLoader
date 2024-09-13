// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

/**
 * Multi-dispatch socket implementation for DataGram (UDP) connections
 * These sockets only support a plentiful of UDP interfaces and do not allow any advanced functionality like multicast groups,
 * broadcasts or receive with paket info, or multi-receive.
 * The intended use case is multi-binding to multiple interfaced on the same machine for UDP IpNetDriver to allow listening
 * on multiple interfaces without having to resort to multi-home options.
 *
 * Keep in mind that this classes uses unused bytes in the socketaddr_storage to mark which socket the packet belongs to,
 * and for IPv6 there is no space in the struct to store that information!
 * So in that case it will instead attempt to store it in the most significant bits of the IPv6 flow, potentially nulling them out.
 * This can cause problems with packets not being treated as a part of the same flow, but it's better than not having them handled at all.
 * Another thing to keep in mind that this flow is only relevant in case of multiple adapters being present in the system .
 * If there is only one adapter, this socket will correctly distinguish between IPv4 and IPv6 without needing to colour the IP information.
 */
class FACTORYDEDICATEDSERVER_API FMultiBindDatagramSocket : public FSocket, public FNoncopyable
{
public:
	FMultiBindDatagramSocket(const FString& InSocketDescription);
	~FMultiBindDatagramSocket();
	
	void AddUnderlyingSocket( FUniqueSocket&& NewSocket );
	void SetSocketToTransferDataToOnClose( FMultiBindDatagramSocket* NewSocket );
	void TransferDataToSocket( FMultiBindDatagramSocket* SocketToTransferTo );

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
	int32 WaitForBSDSocketStateMulti( bool bWaitForRead, FTimespan WaitTime);
	void MoveSocketsToNewInstance( FMultiBindDatagramSocket* NewSocketInstance );

	TArray<FUniqueSocket> Sockets;
	TSharedPtr<FInternetAddr> LocalBindAddress;
	FMultiBindDatagramSocket* SocketToTransferDataToOnClose{nullptr};
	bool bSocketReadErrorOccurred{false};
};