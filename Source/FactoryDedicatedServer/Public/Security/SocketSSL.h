// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

class FFGSslContextDeleter;
using FSharedSslContext = TSharedPtr<struct ssl_ctx_st*>;

enum class ESSLConnectionState : uint8
{
	WaitingForHandshake,
	HandshakeStarted,
	HandshakeDone,
	TerminatedWithError,
	Shutdown,
	Closed
};

class FACTORYDEDICATEDSERVER_API FSocketSSL : public FSocket, public FNoncopyable
{
public:
	FSocketSSL( FUniqueSocket&& InUnderlyingSocket, struct ssl_ctx_st* InSslContext );
	virtual ~FSocketSSL() override;

	// Initializes the SSL socket in either a client or a server state. Must be called exactly once.
	bool InitializeSslState( bool bIsServerSocket );

	// Allows changing the peer verification status for this socket.
	void SetVerifyPeer( bool bVerifyPeer );
	
	// Begin FSocket interface
	virtual bool Shutdown(ESocketShutdownMode Mode) override;
	virtual bool Close() override;
	virtual bool Bind(const FInternetAddr& Addr) override;
	virtual bool Connect(const FInternetAddr& Addr) override;
	virtual bool Listen(int32 MaxBacklog) override;
	virtual bool WaitForPendingConnection(bool& bHasPendingConnection, const FTimespan& WaitTime) override;
	virtual bool HasPendingData(uint32& PendingDataSize) override;
	virtual class FSocket* Accept(const FString& SocketDescription) override;
	virtual class FSocket* Accept(FInternetAddr& OutAddr, const FString& SocketDescription) override;
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
private:
	/** Returns 1 if the handshake is finished successfully, 0 if we need more data, and -1 if there was an error */
	int32 AttemptInitiateHandshake();
	bool IsSSLOperationWaitingForData( int32 ResultCode ) const;
	void NotifySSLCallError( int32 ResultCode );
	
	void SetSSLConnectionState( ESSLConnectionState NewState );
	void ShutdownSSLConnectionAndWait( const FTimespan& MaxWaitTime );
	FSocket* AcceptInternal( FInternetAddr* OutAddr, const FString& InSocketDescription ) const;

	/** Global SSL error handler */
	static int32 StaticSslErrorHandler( const char* AnsiErrorStr, size_t StrLen, void* UserData );
	/** Socket SSL info handler */
	static void StaticSslInfoHandler( const struct ssl_st* InSslInstance, int32 InEventType, int32 InEventVal );
	
	/** The underlying socket for this SSL wrapper */
	FUniqueSocket Socket;
	/** State of the SSL connection */
	ESSLConnectionState ConnectionState{};

	FGuid SocketId{};
	bool bIsNonBlockingMode{false};
	bool bIsVerifyPeer{true};
	
	/** SSL instance associated with this socket. */
	ssl_st* SslInstance{nullptr};

	/** SSL Context associated with this socket and all the sockets it has created */
	ssl_ctx_st* SslContext{nullptr};

	// Used to make sure we are not closing a deleted socket via AsyncTask
	static TMap<FGuid, FSocketSSL*> AllocatedSocketMap;
};
