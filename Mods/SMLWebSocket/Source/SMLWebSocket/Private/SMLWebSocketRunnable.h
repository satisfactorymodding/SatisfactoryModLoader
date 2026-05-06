// Copyright Yamahasxviper. All Rights Reserved.

#pragma once

#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include "Containers/Queue.h"
#include "Templates/SharedPointer.h"
#include <atomic>

// Forward-declare OpenSSL types so consumers don't need to include openssl headers.
// Guarded because OpenSSL is only available on the two Satisfactory server platforms.
#if PLATFORM_WINDOWS || PLATFORM_LINUX
struct ssl_ctx_st;
struct ssl_st;
struct bio_st;
#endif
class FSocket;
class USMLWebSocketClient;

// ── Internal message types ────────────────────────────────────────────────────

struct FSMLWebSocketOutboundMessage
{
	bool bIsBinary{false};
	TArray<uint8> Payload; // UTF-8 bytes for text, raw bytes for binary
};

struct FSMLWebSocketCloseRequest
{
	int32 Code{1000};
	FString Reason;
};

// ── Reconnect configuration (passed from USMLWebSocketClient at Connect time) ─

struct FSMLWebSocketReconnectConfig
{
	bool  bAutoReconnect{true};
	float ReconnectInitialDelay{2.0f}; // seconds
	float MaxReconnectDelay{30.0f};    // seconds
	int32 MaxReconnectAttempts{0};     // 0 = infinite
	float PingInterval{30.0f};         // seconds; 0 = disabled
	float PingTimeout{10.0f};          // seconds
	int32 MaxMessageSizeBytes{0};      // 0 = use internal hard ceiling (64 MB)
	// Proxy settings
	FString ProxyHost;
	int32   ProxyPort{3128};
	FString ProxyUser;
	FString ProxyPassword;
	// SSL settings
	bool bVerifySSLCertificate{false};
};

// ── State machine ─────────────────────────────────────────────────────────────

enum class ESMLWebSocketRunnableState : uint8
{
	Idle,
	ResolvingHost,
	Connecting,
	SslHandshake,
	SendingHttpUpgrade,
	ReadingHttpUpgradeResponse,
	Connected,
	Closing,
	Closed
};

/**
 * Background thread that manages the raw TCP (+ optional SSL) socket and the
 * WebSocket protocol (RFC 6455) for USMLWebSocketClient.
 *
 * When bAutoReconnect is true the thread will re-attempt the full connection
 * sequence (TCP → TLS → HTTP upgrade) with exponential back-off whenever the
 * connection is lost due to a server-side or network failure. User-initiated
 * closes (EnqueueClose) always terminate the loop without reconnecting.
 *
 * All public game-thread callbacks are dispatched via AsyncTask so that
 * delegates always fire on the game thread.
 */
class FSMLWebSocketRunnable final : public FRunnable, public TSharedFromThis<FSMLWebSocketRunnable>
{
public:
	FSMLWebSocketRunnable(USMLWebSocketClient* InOwner,
	                      const FString& InUrl,
	                      const TArray<FString>& InProtocols,
	                      const TMap<FString, FString>& InExtraHeaders,
	                      const FSMLWebSocketReconnectConfig& InReconnectCfg,
	                      uint32 InConnectionGeneration);

	virtual ~FSMLWebSocketRunnable() override;

	// ── FRunnable ─────────────────────────────────────────────────────────────

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

	// ── Thread-safe API (called from the game thread) ─────────────────────────

	/** Queue a text message to be sent. Returns false when the connection is down and the message was dropped. */
	bool EnqueueText(const FString& Text);

	/** Queue a binary message to be sent (copy overload). Returns false when the connection is down and the message was dropped. */
	bool EnqueueBinary(const TArray<uint8>& Data);

	/** Queue a binary message to be sent (move overload — avoids an allocation for owned buffers). Returns false when the connection is down and the message was dropped. */
	bool EnqueueBinary(TArray<uint8>&& Data);

	/**
	 * Request a graceful WebSocket close. Suppresses auto-reconnect so the
	 * thread exits cleanly after the closing handshake completes.
	 */
	void EnqueueClose(int32 Code, const FString& Reason);

	/** True once the WebSocket handshake has been completed. */
	bool IsConnected() const;

	/** Attempt an HTTP CONNECT tunnel through the configured proxy. */
	bool ConnectThroughProxy();

private:
	// ── Connection setup ──────────────────────────────────────────────────────

	bool ResolveAndConnect(const FString& Host, int32 Port);
	bool SendHttpUpgradeRequest(const FString& Host, int32 Port, const FString& Path, const FString& Key);
	bool ReadHttpUpgradeResponse(const FString& ExpectedAcceptKey);

	/** Tear down the existing socket and SSL state so a new attempt can start. */
	void CleanupConnection();

	// ── OpenSSL helpers ───────────────────────────────────────────────────────
	// Only available on the two Satisfactory dedicated-server platforms.
#if PLATFORM_WINDOWS || PLATFORM_LINUX
	bool PerformSslHandshake(const FString& Host);
	bool InitSslContext();
	void DestroySsl();

	/** Read decrypted bytes through SSL (handles re-keying / WANT_READ internally). */
	int32 SslRead(uint8* Buffer, int32 BufferSize);

	/** Encrypt and write bytes through SSL. */
	bool SslWrite(const uint8* Data, int32 DataSize);

	/** Drain the SSL write-BIO into the TCP socket. */
	bool FlushSslWriteBio();

	/** Feed available TCP bytes into the SSL read-BIO. */
	bool FeedSslReadBio();
#endif

	// ── Raw socket helpers ────────────────────────────────────────────────────

	/** Send all bytes to the TCP socket (blocking). */
	bool RawSend(const uint8* Data, int32 DataSize);

	/** Receive exactly BytesRequired bytes from TCP (blocking, timeout aware). */
	bool RawRecvExact(uint8* Buffer, int32 BytesRequired);

	/** Receive at most BufferSize bytes; returns the number actually read (<= 0 on error). */
	int32 RawRecvAvailable(uint8* Buffer, int32 BufferSize);

	// ── High-level send/recv (routes through SSL when bUseSsl is true) ────────

	bool NetSend(const uint8* Data, int32 DataSize);
	int32 NetRecv(uint8* Buffer, int32 BufferSize);
	bool NetRecvExact(uint8* Buffer, int32 BytesRequired);

	// ── WebSocket framing (RFC 6455) ──────────────────────────────────────────

	/** Build and send a WebSocket frame (client-to-server, always masked). */
	bool SendWsFrame(uint8 Opcode, const uint8* Data, int32 DataSize, bool bFinal = true);

	/**
	 * Read and process the next incoming WebSocket frame.
	 * Returns false when the loop should exit:
	 *   • A WebSocket Close frame was received (bReceivedServerClose is set).
	 *   • A fatal TCP/SSL error was detected.
	 *   • bStopRequested is true.
	 */
	bool ProcessIncomingFrame();

	/** Send a Pong frame in response to a Ping. */
	void SendPong(const TArray<uint8>& Payload);

	/** Send an unsolicited Ping frame to measure connection liveness. */
	void SendPing();

	/** Drain the outbound message queue and send all pending frames. */
	void FlushOutboundQueue();

	// ── WebSocket handshake key helpers ───────────────────────────────────────

	/** Generate a random 16-byte key and Base64-encode it (Sec-WebSocket-Key). */
	static FString GenerateWebSocketKey();

	/** Compute the expected Sec-WebSocket-Accept value for a given key (RFC 6455 §4.2.2). */
	static FString ComputeAcceptKey(const FString& ClientKey);

	// ── Game-thread notifications ─────────────────────────────────────────────

	void NotifyConnected();
	void NotifyMessage(const FString& Message);
	void NotifyBinaryMessage(const TArray<uint8>& Data, bool bIsFinal);
	void NotifyClosed(int32 Code, const FString& Reason);
	void NotifyError(const FString& Error);
	void NotifyReconnecting(int32 AttemptNumber, float DelaySeconds);

	// ── Fields ────────────────────────────────────────────────────────────────

	TWeakObjectPtr<USMLWebSocketClient> Owner;

	// URL components parsed during construction
	FString ParsedHost;
	FString ParsedPath;
	int32   ParsedPort{80};
	bool    bUseSsl{false};

	TArray<FString>        Protocols;
	TMap<FString, FString> ExtraHeaders;

	// Reconnect configuration (immutable after construction)
	FSMLWebSocketReconnectConfig ReconnectCfg;

	// Connection-generation snapshot taken from USMLWebSocketClient at construction
	// time. Every async game-thread notification lambda captures this value and
	// discards the callback when it no longer matches the client's current
	// generation, preventing stale events from a replaced connection.
	uint32 ConnectionGeneration{0};

	// Unreal TCP socket (blocking mode)
	FSocket* Socket{nullptr};

	// OpenSSL objects (only valid when bUseSsl == true, and only on SSL-capable platforms)
#if PLATFORM_WINDOWS || PLATFORM_LINUX
	ssl_ctx_st* SslCtx{nullptr};
	ssl_st*     SslInstance{nullptr};
	bio_st*     ReadBio{nullptr};  // network → SSL
	bio_st*     WriteBio{nullptr}; // SSL → network
#endif

	// Shared state between game thread and I/O thread
	std::atomic<ESMLWebSocketRunnableState> State{ESMLWebSocketRunnableState::Idle};
	FThreadSafeBool bStopRequested{false};
	FThreadSafeBool bConnected{false};

	// Set by EnqueueClose(); prevents auto-reconnect after a user-initiated close.
	FThreadSafeBool bUserInitiatedClose{false};

	// Set by ProcessIncomingFrame() when a WS Close frame arrives from the server.
	// Used by Run() to know that NotifyClosed was already dispatched (skip NotifyError).
	bool bReceivedServerClose{false};

	// Outbound queues (game thread → I/O thread)
	TQueue<FSMLWebSocketOutboundMessage, EQueueMode::Mpsc> OutboundMessages;
	TQueue<FSMLWebSocketCloseRequest,    EQueueMode::Mpsc> CloseRequests;

	// Reassembly buffer for fragmented WebSocket messages.
	// bInFragment is a dedicated flag so that a valid zero-length first fragment
	// does not leave FragmentBuffer empty and trigger the "no fragment in progress"
	// protocol-error path in the Continuation handler (the server-side runnable
	// uses the same pattern with FClientState::bInFragment).
	TArray<uint8> FragmentBuffer;
	bool          bFragmentIsBinary{false};
	bool          bInFragment{false};

	// ── Ping / pong keep-alive ────────────────────────────────────────────────

	/** Wall-clock time (FPlatformTime::Seconds) of the last received frame from the server.
	 *  Used to detect when the idle period exceeds PingInterval. */
	double LastReceivedFrameTime{0.0};

	/** Wall-clock time when the most recent Ping was sent.
	 *  0.0 means no Ping is currently outstanding. */
	double PingSentTime{0.0};

	/** true while we are waiting for a Pong in response to our last Ping. */
	bool bWaitingForPong{false};
};
