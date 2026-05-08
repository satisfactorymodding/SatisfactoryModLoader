// Copyright Yamahasxviper. All Rights Reserved.

#include "SMLWebSocketRunnable.h"
#include "SMLWebSocketClient.h"
#include "SMLWebSocket.h"

#include "Async/Async.h"
#include "HAL/PlatformProcess.h"
#include "HAL/PlatformTime.h"
#include "Misc/Base64.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "IPAddress.h"

// OpenSSL headers — only available on the two Satisfactory dedicated-server platforms.
// UE's Slate/InputCore declares `namespace UI {}` at global scope.  OpenSSL's
// ossl_typ.h (line 144) also declares `typedef struct ui_st UI` at global scope.
// On MSVC this produces error C2365 ("redefinition; previous definition was
// 'namespace'") because a C++ namespace and a typedef cannot share the same
// name in the same scope.  `#undef UI` only removes a preprocessor macro and
// has no effect on a C++ namespace declaration, so the conflict remains.
//
// The correct fix is to redirect the OpenSSL typedef to a different name while
// ossl_typ.h is being processed.  By defining UI as a macro that expands to
// UI_OSSLRenamed, the typedef becomes `typedef struct ui_st UI_OSSLRenamed`
// which does not conflict with `namespace UI {}`.  push/pop_macro ensures the
// macro state is properly saved and restored around the OpenSSL includes so
// that post-include code that refers to `namespace UI` continues to work.
//
// THIRD_PARTY_INCLUDES_START/END suppress MSVC warnings (e.g. C4191, C4996)
// that are emitted by OpenSSL's own headers and would otherwise be treated as
// errors under UBT's /WX flag.
#if PLATFORM_WINDOWS || PLATFORM_LINUX
THIRD_PARTY_INCLUDES_START
#pragma push_macro("UI")
#define UI UI_OSSLRenamed
#include "openssl/ssl.h"
#include "openssl/err.h"
#include "openssl/sha.h"
#include "openssl/rand.h"
#include "openssl/bio.h"
#pragma pop_macro("UI")
THIRD_PARTY_INCLUDES_END
#endif

// ─────────────────────────────────────────────────────────────────────────────
// WebSocket opcodes (RFC 6455 §5.2)
// ─────────────────────────────────────────────────────────────────────────────
namespace WsOpcode
{
	static constexpr uint8 Continuation = 0x00;
	static constexpr uint8 Text         = 0x01;
	static constexpr uint8 Binary       = 0x02;
	static constexpr uint8 Close        = 0x08;
	static constexpr uint8 Ping         = 0x09;
	static constexpr uint8 Pong         = 0x0A;
}

// Receive timeout used during connection/handshake phases (milliseconds)
static constexpr int32 RecvTimeoutMs = 5000;
// Short poll interval used in the connected main loop (milliseconds)
static constexpr int32 PollIntervalMs = 100;

// ─────────────────────────────────────────────────────────────────────────────
// Construction / destruction
// ─────────────────────────────────────────────────────────────────────────────

FSMLWebSocketRunnable::FSMLWebSocketRunnable(USMLWebSocketClient* InOwner,
                                             const FString& InUrl,
                                             const TArray<FString>& InProtocols,
                                             const TMap<FString, FString>& InExtraHeaders,
                                             const FSMLWebSocketReconnectConfig& InReconnectCfg,
                                             uint32 InConnectionGeneration)
	: Owner(InOwner)
	, Protocols(InProtocols)
	, ExtraHeaders(InExtraHeaders)
	, ReconnectCfg(InReconnectCfg)
	, ConnectionGeneration(InConnectionGeneration)
{
	// Parse the URL into components.
	// Expected forms:  ws://host[:port]/path   or   wss://host[:port]/path
	FString Rest = InUrl;

	if (Rest.StartsWith(TEXT("wss://"), ESearchCase::IgnoreCase))
	{
		bUseSsl = true;
		ParsedPort = 443;
		Rest = Rest.RightChop(6);
	}
	else if (Rest.StartsWith(TEXT("ws://"), ESearchCase::IgnoreCase))
	{
		bUseSsl = false;
		ParsedPort = 80;
		Rest = Rest.RightChop(5);
	}
	else
	{
		// Treat an unknown scheme as plain ws://
		bUseSsl = false;
		ParsedPort = 80;
		UE_LOG(LogSMLWebSocket, Warning, TEXT("SMLWebSocket: Unrecognized scheme in URL '%s', treating as ws://"), *InUrl);
	}

	// Split host[:port] from path
	int32 SlashIdx;
	if (Rest.FindChar(TEXT('/'), SlashIdx))
	{
		ParsedHost = Rest.Left(SlashIdx);
		ParsedPath = Rest.RightChop(SlashIdx);
	}
	else
	{
		ParsedHost = Rest;
		ParsedPath = TEXT("/");
	}

	// Extract optional port from host.
	// IPv6 literals are wrapped in brackets: "[::1]:port" — find the closing
	// bracket first, then look for the port colon after it to avoid treating
	// the internal colons of the IPv6 address as the port separator.
	if (ParsedHost.StartsWith(TEXT("[")))
	{
		int32 BracketEnd;
		if (ParsedHost.FindChar(TEXT(']'), BracketEnd))
		{
			// Check for ":port" immediately after the closing bracket.
			const FString AfterBracket = ParsedHost.RightChop(BracketEnd + 1);
			if (AfterBracket.StartsWith(TEXT(":")))
			{
				const FString PortStr = AfterBracket.RightChop(1);
				if (PortStr.IsNumeric() && PortStr.Len() <= 5)
				{
					const int32 RawPort = FCString::Atoi(*PortStr);
					if (RawPort >= 1 && RawPort <= 65535)
					{
						ParsedPort = RawPort;
					}
					else
					{
						UE_LOG(LogSMLWebSocket, Warning,
						       TEXT("SMLWebSocket: Invalid port number in URL '%s' — using default port %d"),
						       *InUrl, ParsedPort);
					}
				}
				else
				{
					UE_LOG(LogSMLWebSocket, Warning,
					       TEXT("SMLWebSocket: Invalid port number in URL '%s' — using default port %d"),
					       *InUrl, ParsedPort);
				}
			}
			// Strip brackets from the stored host: "[::1]" → "::1"
			ParsedHost = ParsedHost.Mid(1, BracketEnd - 1);
		}
	}
	else
	{
		// Plain host or IPv4 address — find the single colon that separates host:port.
		int32 ColonIdx;
		if (ParsedHost.FindChar(TEXT(':'), ColonIdx))
		{
			const FString PortStr = ParsedHost.RightChop(ColonIdx + 1);
			if (PortStr.IsNumeric() && PortStr.Len() <= 5)
			{
				const int32 RawPort = FCString::Atoi(*PortStr);
				if (RawPort >= 1 && RawPort <= 65535)
				{
					ParsedPort = RawPort;
				}
				else
				{
					UE_LOG(LogSMLWebSocket, Warning,
					       TEXT("SMLWebSocket: Invalid port number in URL '%s' — using default port %d"),
					       *InUrl, ParsedPort);
				}
			}
			else
			{
				UE_LOG(LogSMLWebSocket, Warning,
				       TEXT("SMLWebSocket: Invalid port number in URL '%s' — using default port %d"),
				       *InUrl, ParsedPort);
			}
			ParsedHost = ParsedHost.Left(ColonIdx);
		}
	}
}

FSMLWebSocketRunnable::~FSMLWebSocketRunnable()
{
#if PLATFORM_WINDOWS || PLATFORM_LINUX
	DestroySsl();
#endif

	if (Socket)
	{
		ISocketSubsystem* SocketSS = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
		if (SocketSS)
		{
			SocketSS->DestroySocket(Socket);
		}
		else
		{
			UE_LOG(LogSMLWebSocket, Warning,
			       TEXT("SMLWebSocket: ISocketSubsystem unavailable in destructor — deleting socket directly"));
			delete Socket;
		}
		Socket = nullptr;
	}
}

// ─────────────────────────────────────────────────────────────────────────────
// FRunnable
// ─────────────────────────────────────────────────────────────────────────────

bool FSMLWebSocketRunnable::Init()
{
	State.store(ESMLWebSocketRunnableState::ResolvingHost);
	return true;
}

uint32 FSMLWebSocketRunnable::Run()
{
	int32 AttemptNumber   = 0;         // counts failed / reconnect attempts
	float CurrentDelay    = ReconnectCfg.ReconnectInitialDelay;

	// ── Outer reconnect loop ──────────────────────────────────────────────────
	while (!bStopRequested && !bUserInitiatedClose)
	{
		// ── Back-off sleep between reconnect attempts ─────────────────────────
		if (AttemptNumber > 0)
		{
			// Cap the attempt count against MaxReconnectAttempts before sleeping.
			if (ReconnectCfg.MaxReconnectAttempts > 0 &&
			    AttemptNumber >= ReconnectCfg.MaxReconnectAttempts)
			{
				NotifyError(FString::Printf(
					TEXT("SMLWebSocket: Gave up reconnecting after %d attempts"), ReconnectCfg.MaxReconnectAttempts));
				break;
			}

			// Notify the game thread that a reconnect is about to begin.
			NotifyReconnecting(AttemptNumber, CurrentDelay);

			// Sleep in 100 ms slices so bStopRequested / bUserInitiatedClose can
			// interrupt the wait immediately.
			const double SleepEnd = FPlatformTime::Seconds() + static_cast<double>(CurrentDelay);
			while (!bStopRequested && !bUserInitiatedClose &&
			       FPlatformTime::Seconds() < SleepEnd)
			{
				FPlatformProcess::Sleep(0.1f);
			}
			if (bStopRequested || bUserInitiatedClose) break;

			// Exponential back-off, capped at MaxReconnectDelay.
			// Apply ±20 % random jitter to spread reconnects from multiple clients
			// and avoid thundering-herd pile-up after a server restart.
			const float BackOff   = FMath::Min(CurrentDelay * 2.0f, ReconnectCfg.MaxReconnectDelay);
			const float JitterFrac = 0.2f; // ±20 %
			const float Jitter    = BackOff * JitterFrac * (FMath::FRand() * 2.0f - 1.0f);
			CurrentDelay = FMath::Max(0.1f, BackOff + Jitter);

			// Clean up any socket/SSL state left over from the previous attempt.
			CleanupConnection();
		}

		// Reset per-attempt flags.
		bReceivedServerClose = false;
		FragmentBuffer.Empty();
		bFragmentIsBinary = false;
		bInFragment = false;

		// ── 1. Resolve host and connect TCP socket ────────────────────────────
		State.store(ESMLWebSocketRunnableState::Connecting);
		if (!ResolveAndConnect(ParsedHost, ParsedPort))
		{
			NotifyError(FString::Printf(TEXT("SMLWebSocket: Failed to connect to %s:%d"), *ParsedHost, ParsedPort));
			if (!ReconnectCfg.bAutoReconnect) break;
			++AttemptNumber;
			continue;
		}
		if (bStopRequested || bUserInitiatedClose) break;

		// ── 2. Optional TLS handshake ─────────────────────────────────────────
		if (bUseSsl)
		{
			State.store(ESMLWebSocketRunnableState::SslHandshake);
			bool bSslOk = false;
#if PLATFORM_WINDOWS || PLATFORM_LINUX
			bSslOk = PerformSslHandshake(ParsedHost);
#else
			// SSL is not available on this platform; wss:// connections are unsupported.
			// Satisfactory dedicated servers only run on Win64 and Linux where OpenSSL is present.
			UE_LOG(LogSMLWebSocket, Error, TEXT("SMLWebSocket: wss:// is not supported on this platform. "
			                           "Satisfactory dedicated servers require Win64 or Linux."));
#endif
			if (!bSslOk)
			{
				NotifyError(TEXT("SMLWebSocket: SSL handshake failed"));
				if (!ReconnectCfg.bAutoReconnect) break;
				++AttemptNumber;
				continue;
			}
			if (bStopRequested || bUserInitiatedClose) break;
		}

		// ── 3. Send HTTP upgrade request ──────────────────────────────────────
		State.store(ESMLWebSocketRunnableState::SendingHttpUpgrade);
		const FString ClientKey = GenerateWebSocketKey();
		const FString AcceptKey = ComputeAcceptKey(ClientKey);

		if (!SendHttpUpgradeRequest(ParsedHost, ParsedPort, ParsedPath, ClientKey))
		{
			NotifyError(TEXT("SMLWebSocket: Failed to send HTTP upgrade request"));
			if (!ReconnectCfg.bAutoReconnect) break;
			++AttemptNumber;
			continue;
		}
		if (bStopRequested || bUserInitiatedClose) break;

		// ── 4. Read and validate HTTP 101 response ────────────────────────────
		State.store(ESMLWebSocketRunnableState::ReadingHttpUpgradeResponse);
		if (!ReadHttpUpgradeResponse(AcceptKey))
		{
			NotifyError(TEXT("SMLWebSocket: WebSocket upgrade handshake rejected by server"));
			if (!ReconnectCfg.bAutoReconnect) break;
			++AttemptNumber;
			continue;
		}
		if (bStopRequested || bUserInitiatedClose) break;

		// ── 5. Connected – main read/write loop ───────────────────────────────
		// Reset back-off: a successful connection means the server is up.
		AttemptNumber = 0;
		CurrentDelay  = ReconnectCfg.ReconnectInitialDelay;

		State.store(ESMLWebSocketRunnableState::Connected);
		bConnected = true;
		LastReceivedFrameTime = FPlatformTime::Seconds();
		PingSentTime = 0.0;
		bWaitingForPong = false;
		NotifyConnected();

		// The inner loop uses an unconditional for(;;) so that a pending close
		// request (queued via EnqueueClose) is always processed and its WebSocket
		// Close frame is always sent, even when bUserInitiatedClose was already
		// set by EnqueueClose before the loop had a chance to dequeue the request.
		while (!bStopRequested)
		{
			// Flush pending outbound messages FIRST so that any messages queued
			// just before Close() is called (e.g. presence update) are transmitted
			// before the Close frame goes out.
			FlushOutboundQueue();

			// Check for a user-requested close from the game thread.
			FSMLWebSocketCloseRequest CloseReq;
			if (CloseRequests.Dequeue(CloseReq))
			{
				State.store(ESMLWebSocketRunnableState::Closing);
				bConnected = false;

				// Build and send close frame payload (2-byte code + UTF-8 reason).
				// RFC 6455 §5.5: control frames MUST NOT carry payload > 125 bytes.
				// Close payload = 2-byte status code + reason, so reason is capped at 123 bytes.
				const FTCHARToUTF8 Utf8Reason(*CloseReq.Reason);
				const int32 ReasonLen = FMath::Min(Utf8Reason.Length(), 123);
				TArray<uint8> ClosePayload;
				ClosePayload.SetNum(2 + ReasonLen);
				ClosePayload[0] = static_cast<uint8>((CloseReq.Code >> 8) & 0xFF);
				ClosePayload[1] = static_cast<uint8>(CloseReq.Code & 0xFF);
				FMemory::Memcpy(ClosePayload.GetData() + 2, Utf8Reason.Get(), ReasonLen);

				SendWsFrame(WsOpcode::Close, ClosePayload.GetData(), ClosePayload.Num());
				NotifyClosed(CloseReq.Code, CloseReq.Reason);
				bUserInitiatedClose = true;
				break;
			}

			// EnqueueClose sets bUserInitiatedClose before queuing the request.
			// If the connection was lost before we dequeued it, honour the flag here.
			if (bUserInitiatedClose) break;

			// ── Ping/Pong keep-alive ──────────────────────────────────────────
			if (ReconnectCfg.PingInterval > 0.0f)
			{
				const double Now = FPlatformTime::Seconds();

				if (bWaitingForPong)
				{
					// Check if the pong timeout has elapsed.
					if (Now - PingSentTime >= static_cast<double>(ReconnectCfg.PingTimeout))
					{
						NotifyError(TEXT("SMLWebSocket: Ping timeout — no Pong received; closing connection"));
						bConnected = false;
						break;
					}
				}
				else
				{
					// Send a Ping if the idle threshold has been reached.
					if (Now - LastReceivedFrameTime >= static_cast<double>(ReconnectCfg.PingInterval))
					{
						SendPing();
					}
				}
			}

			// Poll for incoming data (short timeout keeps the loop responsive).
			bool bDataAvailable = false;
#if PLATFORM_WINDOWS || PLATFORM_LINUX
			if (bUseSsl && SslInstance && SSL_pending(SslInstance) > 0)
			{
				bDataAvailable = true;
			}
			else
#endif
			if (Socket)
			{
				bDataAvailable = Socket->Wait(ESocketWaitConditions::WaitForRead,
				                              FTimespan::FromMilliseconds(PollIntervalMs));
			}

			if (bDataAvailable)
			{
				if (!ProcessIncomingFrame())
				{
					// Connection lost (server Close frame or TCP/SSL error).
					bConnected = false;
					break;
				}
			}
		}

		bConnected = false;

		// ── Decide whether to reconnect ───────────────────────────────────────
		if (bStopRequested || bUserInitiatedClose)
		{
			// Deliberate stop – do not reconnect.
			break;
		}

		if (!ReconnectCfg.bAutoReconnect)
		{
			// Auto-reconnect disabled.
			if (!bReceivedServerClose)
			{
				// TCP drop without a server Close frame: notify the game thread.
				NotifyError(TEXT("SMLWebSocket: Connection lost"));
			}
			break;
		}

		// Fire NotifyError for unexpected TCP drops so the game thread is aware.
		if (!bReceivedServerClose)
		{
			NotifyError(TEXT("SMLWebSocket: Connection lost – reconnecting"));
		}

		// Schedule the next reconnect attempt.
		++AttemptNumber;
	}

	State.store(ESMLWebSocketRunnableState::Closed);
	bConnected = false;
	return 0;
}

void FSMLWebSocketRunnable::Stop()
{
	bStopRequested = true;
}

void FSMLWebSocketRunnable::Exit()
{
#if PLATFORM_WINDOWS || PLATFORM_LINUX
	DestroySsl();
#endif
}

void FSMLWebSocketRunnable::CleanupConnection()
{
	// Destroy SSL objects before the socket so any pending records are dropped cleanly.
#if PLATFORM_WINDOWS || PLATFORM_LINUX
	DestroySsl();
#endif

	if (Socket)
	{
		ISocketSubsystem* SocketSS = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
		if (SocketSS)
		{
			SocketSS->DestroySocket(Socket);
		}
		else
		{
			UE_LOG(LogSMLWebSocket, Warning,
			       TEXT("SMLWebSocket: ISocketSubsystem unavailable in CleanupConnection — deleting socket directly"));
			delete Socket;
		}
		Socket = nullptr;
	}
}

// ─────────────────────────────────────────────────────────────────────────────
// Thread-safe API
// ─────────────────────────────────────────────────────────────────────────────

bool FSMLWebSocketRunnable::EnqueueText(const FString& Text)
{
	// Accept enqueue while temporarily disconnected so reconnect can flush it.
	// Only reject when the runnable is stopping/closed and cannot send again.
	if (bStopRequested || State.load() == ESMLWebSocketRunnableState::Closed) return false;
	FSMLWebSocketOutboundMessage Msg;
	Msg.bIsBinary = false;
	const FTCHARToUTF8 Utf8(*Text);
	Msg.Payload = TArray<uint8>(reinterpret_cast<const uint8*>(Utf8.Get()), Utf8.Length());
	OutboundMessages.Enqueue(MoveTemp(Msg));
	return true;
}

bool FSMLWebSocketRunnable::EnqueueBinary(const TArray<uint8>& Data)
{
	if (bStopRequested || State.load() == ESMLWebSocketRunnableState::Closed) return false;
	FSMLWebSocketOutboundMessage Msg;
	Msg.bIsBinary = true;
	Msg.Payload   = Data;
	OutboundMessages.Enqueue(MoveTemp(Msg));
	return true;
}

bool FSMLWebSocketRunnable::EnqueueBinary(TArray<uint8>&& Data)
{
	if (bStopRequested || State.load() == ESMLWebSocketRunnableState::Closed) return false;
	FSMLWebSocketOutboundMessage Msg;
	Msg.bIsBinary = true;
	Msg.Payload   = MoveTemp(Data);
	OutboundMessages.Enqueue(MoveTemp(Msg));
	return true;
}

void FSMLWebSocketRunnable::EnqueueClose(int32 Code, const FString& Reason)
{
	// Mark as user-initiated so the reconnect loop does not restart after the close.
	bUserInitiatedClose = true;
	FSMLWebSocketCloseRequest Req;
	Req.Code   = Code;
	Req.Reason = Reason;
	CloseRequests.Enqueue(MoveTemp(Req));
}

bool FSMLWebSocketRunnable::IsConnected() const
{
	return bConnected;
}

// ─────────────────────────────────────────────────────────────────────────────
// Connection setup
// ─────────────────────────────────────────────────────────────────────────────

bool FSMLWebSocketRunnable::ResolveAndConnect(const FString& Host, int32 Port)
{
	// If a proxy is configured, connect to the proxy first and tunnel through it.
	const FString& ActualHost = ReconnectCfg.ProxyHost.IsEmpty() ? Host : ReconnectCfg.ProxyHost;
	const int32    ActualPort = ReconnectCfg.ProxyHost.IsEmpty() ? Port : ReconnectCfg.ProxyPort;

	ISocketSubsystem* SocketSS = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
	if (!SocketSS)
	{
		UE_LOG(LogSMLWebSocket, Error, TEXT("SMLWebSocket: No socket subsystem"));
		return false;
	}

	// Resolve hostname (no service name, accept any address type)
	FAddressInfoResult Result = SocketSS->GetAddressInfo(*ActualHost, nullptr,
	                                                       EAddressInfoFlags::Default,
	                                                       NAME_None);
	if (Result.ReturnCode != SE_NO_ERROR || Result.Results.IsEmpty())
	{
		UE_LOG(LogSMLWebSocket, Error, TEXT("SMLWebSocket: Failed to resolve '%s'"), *ActualHost);
		return false;
	}

	TSharedRef<FInternetAddr> Addr = Result.Results[0].Address;
	Addr->SetPort(ActualPort);

	// Create blocking TCP socket using the same protocol as the resolved address (IPv4 or IPv6)
	Socket = SocketSS->CreateSocket(NAME_Stream, TEXT("SMLWebSocket"), Addr->GetProtocolType());
	if (!Socket)
	{
		UE_LOG(LogSMLWebSocket, Error, TEXT("SMLWebSocket: Failed to create socket"));
		return false;
	}

	// Set a generous receive buffer size
	int32 NewBufferSize = 0;
	Socket->SetReceiveBufferSize(65536, NewBufferSize);
	Socket->SetNonBlocking(false);

	if (!Socket->Connect(*Addr))
	{
		UE_LOG(LogSMLWebSocket, Error, TEXT("SMLWebSocket: Connect() failed to %s:%d"), *ActualHost, ActualPort);
		CleanupConnection();
		return false;
	}

	// If a proxy was used, send the HTTP CONNECT tunnel request now.
	if (!ReconnectCfg.ProxyHost.IsEmpty())
	{
		if (!ConnectThroughProxy())
		{
			CleanupConnection();
			return false;
		}
	}

	return true;
}

bool FSMLWebSocketRunnable::ConnectThroughProxy()
{
	// Send HTTP CONNECT to the proxy to tunnel to the real destination.
	// https://developer.mozilla.org/en-US/docs/Web/HTTP/Methods/CONNECT
	FString Request = FString::Printf(TEXT("CONNECT %s:%d HTTP/1.1\r\n"), *ParsedHost, ParsedPort);
	Request += FString::Printf(TEXT("Host: %s:%d\r\n"), *ParsedHost, ParsedPort);

	if (!ReconnectCfg.ProxyUser.IsEmpty())
	{
		// Basic proxy authentication
		const FString Credentials = ReconnectCfg.ProxyUser + TEXT(":") + ReconnectCfg.ProxyPassword;
		const FTCHARToUTF8 Utf8Creds(*Credentials);
		const FString Encoded = FBase64::Encode(
			reinterpret_cast<const uint8*>(Utf8Creds.Get()),
			static_cast<uint32>(Utf8Creds.Length()));
		Request += FString::Printf(TEXT("Proxy-Authorization: Basic %s\r\n"), *Encoded);
	}

	Request += TEXT("Proxy-Connection: keep-alive\r\n\r\n");

	const FTCHARToUTF8 Utf8Req(*Request);
	if (!RawSend(reinterpret_cast<const uint8*>(Utf8Req.Get()), Utf8Req.Length()))
	{
		UE_LOG(LogSMLWebSocket, Error, TEXT("SMLWebSocket: Failed to send HTTP CONNECT to proxy"));
		return false;
	}

	// Read the proxy response — accumulate until the header block ends (\r\n\r\n).
	// Enforce a 30-second wall-clock deadline to prevent a slow/malicious proxy
	// from stalling the worker thread indefinitely (RawRecvExact can block up to
	// RecvTimeoutMs per byte without the deadline).
	FString ResponseLine;
	uint8 Buf[1];
	static constexpr int32 MaxLineBytes = 4096;
	const double ConnectDeadline = FPlatformTime::Seconds() + 30.0;
	while (!bStopRequested && ResponseLine.Len() < MaxLineBytes)
	{
		if (FPlatformTime::Seconds() > ConnectDeadline)
		{
			UE_LOG(LogSMLWebSocket, Error,
			       TEXT("SMLWebSocket: Proxy CONNECT response timed out after 30 s"));
			return false;
		}
		if (!RawRecvExact(Buf, 1)) return false;
		ResponseLine.AppendChar(static_cast<TCHAR>(Buf[0]));
		if (ResponseLine.EndsWith(TEXT("\r\n\r\n"))) break;
	}

	// Validate only the HTTP status line (first line) to avoid false-positive
	// matches when header values happen to contain "200" (e.g. Content-Length: 2000).
	// The status line is "HTTP/x.y 200 <reason>"; split off at the first \r\n.
	int32 FirstLineEnd = INDEX_NONE;
	ResponseLine.FindChar(TEXT('\r'), FirstLineEnd);
	const FString StatusLine = (FirstLineEnd != INDEX_NONE)
		? ResponseLine.Left(FirstLineEnd)
		: ResponseLine;

	if (!StatusLine.Contains(TEXT(" 200 ")) && !StatusLine.EndsWith(TEXT(" 200")))
	{
		UE_LOG(LogSMLWebSocket, Error,
		       TEXT("SMLWebSocket: Proxy CONNECT failed: %s"), *ResponseLine.Left(200));
		return false;
	}

	UE_LOG(LogSMLWebSocket, Log,
	       TEXT("SMLWebSocket: Proxy tunnel established to %s:%d"), *ParsedHost, ParsedPort);
	return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// OpenSSL helpers — only compiled on the two Satisfactory server platforms
// ─────────────────────────────────────────────────────────────────────────────
#if PLATFORM_WINDOWS || PLATFORM_LINUX

bool FSMLWebSocketRunnable::InitSslContext()
{
	SslCtx = SSL_CTX_new(TLS_client_method());
	if (!SslCtx)
	{
		char ErrBuf[256];
		ERR_error_string_n(ERR_get_error(), ErrBuf, sizeof(ErrBuf));
		UE_LOG(LogSMLWebSocket, Error, TEXT("SMLWebSocket: SSL_CTX_new failed: %s"), UTF8_TO_TCHAR(ErrBuf));
		return false;
	}

	// Certificate verification is controlled by FSMLWebSocketReconnectConfig::bVerifySSLCertificate.
	// The default is SSL_VERIFY_NONE because the Satisfactory dedicated-server environment
	// does not ship a standard OS CA bundle, so SSL_VERIFY_PEER rejects every certificate.
	// When bVerifySSLCertificate is true the system CA bundle is loaded and peer verification
	// is enabled — only set this if you have a CA bundle available on the server.
	if (ReconnectCfg.bVerifySSLCertificate)
	{
		SSL_CTX_set_default_verify_paths(SslCtx);
		SSL_CTX_set_verify(SslCtx, SSL_VERIFY_PEER, nullptr);
		UE_LOG(LogSMLWebSocket, Log, TEXT("SMLWebSocket: SSL certificate verification enabled."));
	}
	else
	{
		SSL_CTX_set_verify(SslCtx, SSL_VERIFY_NONE, nullptr);
		UE_LOG(LogSMLWebSocket, Warning,
		       TEXT("SMLWebSocket: SSL certificate verification is DISABLED. "
		            "TLS connections will accept any server certificate (including self-signed or invalid). "
		            "Set bVerifySSLCertificate=true if a CA bundle is available on this server."));
	}

	// Require at least TLS 1.2
	SSL_CTX_set_min_proto_version(SslCtx, TLS1_2_VERSION);

	SslInstance = SSL_new(SslCtx);
	if (!SslInstance)
	{
		char ErrBuf[256];
		ERR_error_string_n(ERR_get_error(), ErrBuf, sizeof(ErrBuf));
		UE_LOG(LogSMLWebSocket, Error, TEXT("SMLWebSocket: SSL_new failed: %s"), UTF8_TO_TCHAR(ErrBuf));
		// Free the context we just created — it is not freed by DestroySsl() because
		// SslInstance is null and SSL_free (which would normally release SslCtx) was
		// never called.
		SSL_CTX_free(SslCtx);
		SslCtx = nullptr;
		return false;
	}

	// Memory BIOs: network data flows in through ReadBio, encrypted output
	// is collected from WriteBio and sent over the TCP socket.
	ReadBio  = BIO_new(BIO_s_mem());
	WriteBio = BIO_new(BIO_s_mem());

	if (!ReadBio || !WriteBio)
	{
		// Free any BIO that was successfully allocated before the check to
		// avoid a leak: SSL_set_bio has not been called yet so SSL_free will
		// not release them automatically.
		if (ReadBio) { BIO_free(ReadBio); ReadBio = nullptr; }
		if (WriteBio) { BIO_free(WriteBio); WriteBio = nullptr; }
		UE_LOG(LogSMLWebSocket, Error, TEXT("SMLWebSocket: Failed to create memory BIOs"));
		return false;
	}

	// Ownership of both BIOs is transferred to the SSL object.
	SSL_set_bio(SslInstance, ReadBio, WriteBio);
	SSL_set_connect_state(SslInstance);

	return true;
}

void FSMLWebSocketRunnable::DestroySsl()
{
	if (SslInstance)
	{
		SSL_free(SslInstance); // also frees ReadBio and WriteBio
		SslInstance = nullptr;
		ReadBio     = nullptr;
		WriteBio    = nullptr;
	}
	if (SslCtx)
	{
		SSL_CTX_free(SslCtx);
		SslCtx = nullptr;
	}
}

bool FSMLWebSocketRunnable::PerformSslHandshake(const FString& Host)
{
	if (!InitSslContext())
	{
		return false;
	}

	// Set the SNI hostname so the server can choose the right certificate.
	// SSL_set_tlsext_host_name is a macro that calls SSL_ctrl(); it returns 1 on
	// success and 0 on failure.  A failure here is non-fatal for the connection
	// itself (the TLS handshake can still succeed without SNI) but we log it so
	// that certificate-selection problems are easier to diagnose.
	if (SSL_set_tlsext_host_name(SslInstance, TCHAR_TO_UTF8(*Host)) != 1)
	{
		UE_LOG(LogSMLWebSocket, Warning,
		       TEXT("SMLWebSocket: SSL_set_tlsext_host_name failed for host '%s'. "
		            "TLS handshake will proceed without SNI."), *Host);
	}

	// Run the TLS handshake. Because we use memory BIOs we must manually
	// pump data between OpenSSL and the TCP socket.
	// Guard against a slow/malicious server that never completes the handshake.
	static constexpr double HandshakeTimeoutSecs = 30.0;
	const double HandshakeStart = FPlatformTime::Seconds();
	for (;;)
	{
		if (bStopRequested) return false;
		if (FPlatformTime::Seconds() - HandshakeStart > HandshakeTimeoutSecs)
		{
			UE_LOG(LogSMLWebSocket, Error,
			       TEXT("SMLWebSocket: TLS handshake timed out after %.0f seconds"), HandshakeTimeoutSecs);
			return false;
		}

		const int32 Ret = SSL_do_handshake(SslInstance);
		if (Ret == 1)
		{
			// Handshake complete – flush any final records the library wrote.
			if (!FlushSslWriteBio())
			{
				UE_LOG(LogSMLWebSocket, Error,
				       TEXT("SMLWebSocket: Failed to flush TLS write BIO after handshake"));
				return false;
			}
			break;
		}

		const int32 Err = SSL_get_error(SslInstance, Ret);
		if (Err == SSL_ERROR_WANT_READ)
		{
			// Flush any data OpenSSL wants to send first.
			if (!FlushSslWriteBio()) return false;

			// Then read more data from the network into the read BIO.
			if (!FeedSslReadBio()) return false;
		}
		else if (Err == SSL_ERROR_WANT_WRITE)
		{
			if (!FlushSslWriteBio()) return false;
		}
		else
		{
			char ErrBuf[256];
			ERR_error_string_n(ERR_get_error(), ErrBuf, sizeof(ErrBuf));
			UE_LOG(LogSMLWebSocket, Error, TEXT("SMLWebSocket: SSL handshake error %d: %s"),
			       Err, UTF8_TO_TCHAR(ErrBuf));
			return false;
		}
	}

	return true;
}

// Drain the SSL write-BIO into the TCP socket.
bool FSMLWebSocketRunnable::FlushSslWriteBio()
{
	if (!WriteBio || !Socket) return false;

	uint8 Tmp[4096];
	int32 n;
	while ((n = static_cast<int32>(BIO_read(WriteBio, Tmp, static_cast<int>(sizeof(Tmp))))) > 0)
	{
		if (!RawSend(Tmp, n))
		{
			return false;
		}
	}
	return true;
}

// Read available TCP bytes into the SSL read-BIO (blocking, used during the TLS handshake).
bool FSMLWebSocketRunnable::FeedSslReadBio()
{
	if (!ReadBio || !Socket) return false;

	// Wait up to RecvTimeoutMs for data to arrive (the handshake must complete promptly).
	if (!Socket->Wait(ESocketWaitConditions::WaitForRead, FTimespan::FromMilliseconds(RecvTimeoutMs)))
	{
		UE_LOG(LogSMLWebSocket, Warning, TEXT("SMLWebSocket: Timed out waiting for TLS handshake data"));
		return false;
	}

	uint8 Tmp[16384];
	int32 BytesRead = 0;
	if (!Socket->Recv(Tmp, static_cast<int32>(sizeof(Tmp)), BytesRead) || BytesRead <= 0)
	{
		return false;
	}
	const int32 Written = static_cast<int32>(BIO_write(ReadBio, Tmp, BytesRead));
	if (Written < 0 || Written != BytesRead)
	{
		UE_LOG(LogSMLWebSocket, Error,
		       TEXT("SMLWebSocket: BIO_write underflow in FeedSslReadBio (%d of %d bytes written)"),
		       Written, BytesRead);
		return false;
	}
	return true;
}

int32 FSMLWebSocketRunnable::SslRead(uint8* Buffer, int32 BufferSize)
{
	for (;;)
	{
		if (bStopRequested) return -1;

		const int32 Ret = SSL_read(SslInstance, Buffer, BufferSize);
		if (Ret > 0)
		{
			// Send any TLS renegotiation records that SSL_read may have generated.
			if (!FlushSslWriteBio())
			{
				return -1; // socket broken during renegotiation flush
			}
			return Ret;
		}

		const int32 Err = SSL_get_error(SslInstance, Ret);
		if (Err == SSL_ERROR_WANT_READ)
		{
			// Flush any outgoing SSL data (e.g. renegotiation records) first.
			if (!FlushSslWriteBio()) return -1; // socket broken during flush

			// Wait briefly for incoming TCP data. Return 0 (not -1) on timeout
			// so that callers can retry and check bStopRequested / send queues.
			if (!Socket->Wait(ESocketWaitConditions::WaitForRead, FTimespan::FromMilliseconds(PollIntervalMs)))
			{
				return 0; // timeout – not an error; caller should retry
			}

			// Feed the available TCP data into the SSL read BIO.
			uint8 Tmp[16384];
			int32 BytesRead = 0;
			if (!Socket->Recv(Tmp, static_cast<int32>(sizeof(Tmp)), BytesRead) || BytesRead <= 0)
			{
				return -1; // hard TCP error
			}
			const int32 BioWritten = static_cast<int32>(BIO_write(ReadBio, Tmp, BytesRead));
			if (BioWritten < 0 || BioWritten != BytesRead)
			{
				UE_LOG(LogSMLWebSocket, Error,
				       TEXT("SMLWebSocket: BIO_write underflow in SslRead (%d of %d bytes written)"),
				       BioWritten, BytesRead);
				return -1;
			}
		}
		else if (Err == SSL_ERROR_WANT_WRITE)
		{
			if (!FlushSslWriteBio())
			{
				return -1; // socket broken during SSL_ERROR_WANT_WRITE flush
			}
		}
		else if (Err == SSL_ERROR_ZERO_RETURN)
		{
			// Peer cleanly closed the TLS session — treat as EOF, not a timeout.
			// Returning 0 here would cause NetRecvExact to retry forever since it
			// cannot distinguish timeout (retry) from clean close (stop).
			return -1;
		}
		else
		{
			return -1; // fatal SSL error
		}
	}
}

bool FSMLWebSocketRunnable::SslWrite(const uint8* Data, int32 DataSize)
{
	int32 Written = 0;
	while (Written < DataSize)
	{
		if (bStopRequested) return false;

		const int32 Ret = SSL_write(SslInstance, Data + Written, DataSize - Written);
		if (Ret > 0)
		{
			Written += Ret;
			if (!FlushSslWriteBio())
			{
				return false; // socket broken; data flushed to BIO but not sent
			}
		}
		else
		{
			const int32 Err = SSL_get_error(SslInstance, Ret);
			if (Err == SSL_ERROR_WANT_WRITE)
			{
				if (!FlushSslWriteBio())
				{
					return false; // socket broken; bail to avoid infinite loop
				}
			}
			else
			{
				char ErrBuf[256];
				ERR_error_string_n(ERR_get_error(), ErrBuf, sizeof(ErrBuf));
				UE_LOG(LogSMLWebSocket, Error, TEXT("SMLWebSocket: SSL_write error %d: %s"),
				       Err, UTF8_TO_TCHAR(ErrBuf));
				return false;
			}
		}
	}
	return true;
}

#endif // PLATFORM_WINDOWS || PLATFORM_LINUX

// ─────────────────────────────────────────────────────────────────────────────
// Raw socket helpers
// ─────────────────────────────────────────────────────────────────────────────

bool FSMLWebSocketRunnable::RawSend(const uint8* Data, int32 DataSize)
{
	int32 TotalSent = 0;
	while (TotalSent < DataSize)
	{
		if (bStopRequested) return false;

		int32 Sent = 0;
		if (!Socket->Send(Data + TotalSent, DataSize - TotalSent, Sent) || Sent <= 0)
		{
			return false;
		}
		TotalSent += Sent;
	}
	return true;
}

int32 FSMLWebSocketRunnable::RawRecvAvailable(uint8* Buffer, int32 BufferSize)
{
	if (!Socket) return -1;

	// Wait up to RecvTimeoutMs for data to arrive before returning.
	if (!Socket->Wait(ESocketWaitConditions::WaitForRead, FTimespan::FromMilliseconds(RecvTimeoutMs)))
	{
		return 0; // timeout – caller should retry
	}

	int32 BytesRead = 0;
	if (!Socket->Recv(Buffer, BufferSize, BytesRead))
	{
		return -1;
	}
	return BytesRead;
}

bool FSMLWebSocketRunnable::RawRecvExact(uint8* Buffer, int32 BytesRequired)
{
	int32 Total = 0;
	while (Total < BytesRequired)
	{
		if (bStopRequested) return false;

		// Wait for data
		if (!Socket->Wait(ESocketWaitConditions::WaitForRead, FTimespan::FromMilliseconds(RecvTimeoutMs)))
		{
			continue; // timeout – retry
		}

		int32 Received = 0;
		if (!Socket->Recv(Buffer + Total, BytesRequired - Total, Received) || Received <= 0)
		{
			return false;
		}
		Total += Received;
	}
	return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// High-level network send/recv (routes through SSL when active)
// ─────────────────────────────────────────────────────────────────────────────

bool FSMLWebSocketRunnable::NetSend(const uint8* Data, int32 DataSize)
{
#if PLATFORM_WINDOWS || PLATFORM_LINUX
	if (bUseSsl)
	{
		return SslWrite(Data, DataSize);
	}
#endif
	return RawSend(Data, DataSize);
}

int32 FSMLWebSocketRunnable::NetRecv(uint8* Buffer, int32 BufferSize)
{
#if PLATFORM_WINDOWS || PLATFORM_LINUX
	if (bUseSsl)
	{
		return SslRead(Buffer, BufferSize);
	}
#endif
	return RawRecvAvailable(Buffer, BufferSize);
}

bool FSMLWebSocketRunnable::NetRecvExact(uint8* Buffer, int32 BytesRequired)
{
#if PLATFORM_WINDOWS || PLATFORM_LINUX
	if (bUseSsl)
	{
		int32 Total = 0;
		while (Total < BytesRequired)
		{
			if (bStopRequested) return false;
			const int32 n = SslRead(Buffer + Total, BytesRequired - Total);
			if (n < 0) return false; // fatal SSL/TCP error
			Total += n;              // when n == 0 (timeout), Total stays the same and we retry
		}
		return true;
	}
#endif
	return RawRecvExact(Buffer, BytesRequired);
}

// ─────────────────────────────────────────────────────────────────────────────
// HTTP upgrade handshake
// ─────────────────────────────────────────────────────────────────────────────

bool FSMLWebSocketRunnable::SendHttpUpgradeRequest(const FString& Host, int32 Port,
                                                    const FString& Path, const FString& Key)
{
	FString Request;
	Request += FString::Printf(TEXT("GET %s HTTP/1.1\r\n"), *Path);

	// Include port in Host header only when non-default.
	const bool bDefaultPort = (!bUseSsl && Port == 80) || (bUseSsl && Port == 443);
	if (bDefaultPort)
	{
		Request += FString::Printf(TEXT("Host: %s\r\n"), *Host);
	}
	else
	{
		Request += FString::Printf(TEXT("Host: %s:%d\r\n"), *Host, Port);
	}

	Request += TEXT("Upgrade: websocket\r\n");
	Request += TEXT("Connection: Upgrade\r\n");
	Request += FString::Printf(TEXT("Sec-WebSocket-Key: %s\r\n"), *Key);
	Request += TEXT("Sec-WebSocket-Version: 13\r\n");

	if (!Protocols.IsEmpty())
	{
		Request += FString::Printf(TEXT("Sec-WebSocket-Protocol: %s\r\n"), *FString::Join(Protocols, TEXT(", ")));
	}

	for (const auto& Pair : ExtraHeaders)
	{
		// Sanitize keys and values: strip CR and LF characters to prevent
		// HTTP header injection if a caller provides untrusted header content.
		const FString SafeKey   = Pair.Key.Replace(TEXT("\r"), TEXT("")).Replace(TEXT("\n"), TEXT(""));
		const FString SafeValue = Pair.Value.Replace(TEXT("\r"), TEXT("")).Replace(TEXT("\n"), TEXT(""));
		if (SafeKey.IsEmpty()) continue;
		Request += FString::Printf(TEXT("%s: %s\r\n"), *SafeKey, *SafeValue);
	}

	Request += TEXT("\r\n");

	const FTCHARToUTF8 Utf8(*Request);
	return NetSend(reinterpret_cast<const uint8*>(Utf8.Get()), Utf8.Length());
}

bool FSMLWebSocketRunnable::ReadHttpUpgradeResponse(const FString& ExpectedAcceptKey)
{
	// Read the HTTP response line-by-line until we hit the blank line.
	// We read one byte at a time to avoid over-consuming data that belongs to the WS stream.
	FString ResponseHeaders;
	uint8 Buf[1];

	// Cap the total header bytes we will accept to protect against malicious or
	// misbehaving servers that never send \r\n\r\n.
	static constexpr int32 MaxHttpHeaderBytes = 8192;

	while (!bStopRequested)
	{
		if (ResponseHeaders.Len() >= MaxHttpHeaderBytes)
		{
			UE_LOG(LogSMLWebSocket, Error,
			       TEXT("SMLWebSocket: HTTP upgrade response headers exceeded %d bytes – aborting"),
			       MaxHttpHeaderBytes);
			return false;
		}

		if (!NetRecvExact(Buf, 1))
		{
			return false;
		}

		const char Ch = static_cast<char>(Buf[0]);
		ResponseHeaders.AppendChar(static_cast<TCHAR>(Ch));

		// Detect end of HTTP headers: \r\n\r\n
		if (ResponseHeaders.EndsWith(TEXT("\r\n\r\n")))
		{
			break;
		}
	}

	if (bStopRequested) return false;

	// Validate that the first status line is "HTTP/x.y 101 <reason>".
	// We check only the first line so we don't accidentally match "101" in
	// a header value or response body.
	TArray<FString> Lines;
	ResponseHeaders.ParseIntoArrayLines(Lines);
	const bool bGot101 = Lines.Num() > 0 &&
	                     Lines[0].StartsWith(TEXT("HTTP/"), ESearchCase::IgnoreCase) &&
	                     (Lines[0].Contains(TEXT(" 101 ")) || Lines[0].EndsWith(TEXT(" 101")));
	if (!bGot101)
	{
		UE_LOG(LogSMLWebSocket, Error,
		       TEXT("SMLWebSocket: Server did not return 101 Switching Protocols.\n%s"),
		       *ResponseHeaders);
		return false;
	}
	// Validate Sec-WebSocket-Accept (case-insensitive header search)
	if (!ResponseHeaders.Contains(TEXT("sec-websocket-accept"), ESearchCase::IgnoreCase))
	{
		UE_LOG(LogSMLWebSocket, Error, TEXT("SMLWebSocket: Response missing Sec-WebSocket-Accept header"));
		return false;
	}

	// Extract the accept value from the response (Lines is already populated above).
	// Use RightChop to avoid splitting on any colon in the value (e.g. future extensions),
	// and compare case-sensitively per RFC 6455 §4.1 (base64 is case-sensitive).
	static const FString AcceptPrefix = TEXT("Sec-WebSocket-Accept:");
	for (const FString& Line : Lines)
	{
		if (Line.StartsWith(AcceptPrefix, ESearchCase::IgnoreCase))
		{
			FString AcceptValue = Line.RightChop(AcceptPrefix.Len());
			AcceptValue.TrimStartAndEndInline();
			if (!AcceptValue.Equals(ExpectedAcceptKey, ESearchCase::CaseSensitive))
			{
				UE_LOG(LogSMLWebSocket, Error,
				       TEXT("SMLWebSocket: Sec-WebSocket-Accept mismatch. Expected '%s', got '%s'"),
				       *ExpectedAcceptKey, *AcceptValue);
				return false;
			}
			return true;
		}
	}

	UE_LOG(LogSMLWebSocket, Error, TEXT("SMLWebSocket: Could not parse Sec-WebSocket-Accept header"));
	return false;
}

// ─────────────────────────────────────────────────────────────────────────────
// WebSocket framing
// ─────────────────────────────────────────────────────────────────────────────

bool FSMLWebSocketRunnable::SendWsFrame(uint8 Opcode, const uint8* Data, int32 DataSize, bool bFinal)
{
	// RFC 6455 §5.2 – client frames MUST be masked.
	TArray<uint8> Frame;
	Frame.Reserve(2 + 8 + 4 + DataSize);

	// Byte 0: FIN + opcode
	Frame.Add(static_cast<uint8>((bFinal ? 0x80 : 0x00) | (Opcode & 0x0F)));

	// Generate 4-byte masking key (RFC 6455 §5.3 — client frames must be masked).
	// Use OpenSSL's CSPRNG on the two Satisfactory server platforms; fall back to
	// FMath::Rand() elsewhere.  The mask is sent alongside the frame in plaintext
	// and therefore provides no cryptographic security — any source of random bytes works.
	uint8 MaskKey[4];
#if PLATFORM_WINDOWS || PLATFORM_LINUX
	RAND_bytes(MaskKey, static_cast<int>(sizeof(MaskKey)));
#else
	for (int32 i = 0; i < 4; ++i)
	{
		MaskKey[i] = static_cast<uint8>(FMath::Rand() & 0xFF);
	}
#endif

	// Byte 1+: payload length with mask bit set
	if (DataSize <= 125)
	{
		Frame.Add(static_cast<uint8>(0x80 | DataSize));
	}
	else if (DataSize <= 65535)
	{
		Frame.Add(0x80 | 126);
		Frame.Add(static_cast<uint8>((DataSize >> 8) & 0xFF));
		Frame.Add(static_cast<uint8>(DataSize & 0xFF));
	}
	else
	{
		Frame.Add(0x80 | 127);
		const uint64 Len64 = static_cast<uint64>(DataSize);
		for (int32 i = 7; i >= 0; --i)
		{
			Frame.Add(static_cast<uint8>((Len64 >> (i * 8)) & 0xFF));
		}
	}

	// Masking key
	Frame.Add(MaskKey[0]);
	Frame.Add(MaskKey[1]);
	Frame.Add(MaskKey[2]);
	Frame.Add(MaskKey[3]);

	// Masked payload
	const int32 PayloadStart = Frame.Num();
	Frame.AddUninitialized(DataSize);
	for (int32 i = 0; i < DataSize; ++i)
	{
		Frame[PayloadStart + i] = Data[i] ^ MaskKey[i & 3];
	}

	return NetSend(Frame.GetData(), Frame.Num());
}

bool FSMLWebSocketRunnable::ProcessIncomingFrame()
{
	// Read the 2-byte frame header.
	// NetRecvExact returns false only on bStopRequested or a fatal TCP/SSL error
	// (it handles temporary timeouts internally by retrying). Either way, returning
	// false here is correct: the outer loop should stop or reconnect.
	uint8 Header[2];
	if (!NetRecvExact(Header, 2))
	{
		return false;
	}

	const bool bFin       = (Header[0] & 0x80) != 0;
	const uint8 Opcode    = Header[0] & 0x0F;
	const bool bMasked    = (Header[1] & 0x80) != 0; // server→client should NOT be masked
	uint64 PayloadLen     = Header[1] & 0x7F;

	// RFC 6455 §5.2: RSV1/RSV2/RSV3 must be zero when no extension is negotiated.
	if (Header[0] & 0x70)
	{
		UE_LOG(LogSMLWebSocket, Error,
		       TEXT("SMLWebSocket: Frame with nonzero RSV bits — closing connection"));
		const uint8 ClosePayload[2] = { 0x03, 0xEA }; // 1002
		SendWsFrame(WsOpcode::Close, ClosePayload, 2);
		return false;
	}

	// RFC 6455 §5.1: A client MUST close the connection if it detects a masked frame from the server.
	if (bMasked)
	{
		UE_LOG(LogSMLWebSocket, Error,
		       TEXT("SMLWebSocket: Server sent a masked frame — closing connection (RFC 6455 §5.1)"));
		const uint8 ClosePayload[2] = { 0x03, 0xEA }; // 1002 Protocol Error
		SendWsFrame(WsOpcode::Close, ClosePayload, 2);
		return false;
	}

	// Extended payload length
	if (PayloadLen == 126)
	{
		uint8 Ext[2];
		if (!NetRecvExact(Ext, 2)) return false;
		PayloadLen = (static_cast<uint64>(Ext[0]) << 8) | Ext[1];
	}
	else if (PayloadLen == 127)
	{
		uint8 Ext[8];
		if (!NetRecvExact(Ext, 8)) return false;
		PayloadLen = 0;
		for (int32 i = 0; i < 8; ++i)
		{
			PayloadLen = (PayloadLen << 8) | Ext[i];
		}
		// RFC 6455 §5.2: the most significant bit of the 8-byte extended length MUST be 0.
		if (PayloadLen & (static_cast<uint64>(1) << 63))
		{
			UE_LOG(LogSMLWebSocket, Error,
			       TEXT("SMLWebSocket: Frame has invalid 8-byte payload length (MSB set) — closing connection"));
			return false;
		}
	}

	// Optional masking key (should be absent for server→client)
	uint8 MaskKey[4] = {0, 0, 0, 0};
	if (bMasked)
	{
		if (!NetRecvExact(MaskKey, 4)) return false;
	}

	// Guard against absurdly large payloads that could cause OOM.
	// Discord messages are at most a few KB; 64 MB is a very generous ceiling.
	static constexpr uint64 MaxPayloadBytes = 64u * 1024u * 1024u;
	const uint64 EffectiveMax = (ReconnectCfg.MaxMessageSizeBytes > 0)
		? static_cast<uint64>(ReconnectCfg.MaxMessageSizeBytes)
		: MaxPayloadBytes;
	if (PayloadLen > EffectiveMax || PayloadLen > static_cast<uint64>(MAX_int32))
	{
		UE_LOG(LogSMLWebSocket, Error,
		       TEXT("SMLWebSocket: Incoming frame payload too large (%llu bytes) – closing connection"),
		       static_cast<unsigned long long>(PayloadLen));
		return false;
	}

	const int32 PayloadLen32 = static_cast<int32>(PayloadLen);

	// RFC 6455 §5.5: control frames must have FIN=1 and payload ≤ 125 bytes.
	const bool bIsControl = (Opcode == WsOpcode::Close || Opcode == WsOpcode::Ping || Opcode == WsOpcode::Pong);
	if (bIsControl && (!bFin || PayloadLen32 > 125))
	{
		UE_LOG(LogSMLWebSocket, Error,
		       TEXT("SMLWebSocket: Invalid control frame (FIN=%d, PayloadLen=%d) — closing connection"),
		       (int)bFin, PayloadLen32);
		const uint8 ClosePayload[2] = { 0x03, 0xEA }; // 1002
		SendWsFrame(WsOpcode::Close, ClosePayload, 2);
		return false;
	}

	// Read payload
	TArray<uint8> Payload;
	if (PayloadLen32 > 0)
	{
		Payload.SetNumUninitialized(PayloadLen32);
		if (!NetRecvExact(Payload.GetData(), PayloadLen32)) return false;

		if (bMasked)
		{
			for (int32 i = 0; i < Payload.Num(); ++i)
			{
				Payload[i] ^= MaskKey[i & 3];
			}
		}
	}

	// Dispatch by opcode.
	// Only update the idle-ping timer for known RFC 6455 opcodes; unknown/garbage
	// frames must not reset the liveness check or the server could appear healthy
	// while delivering no real data.
	switch (Opcode)
	{
	case WsOpcode::Text:
	case WsOpcode::Binary:
	case WsOpcode::Continuation:
	case WsOpcode::Ping:
	case WsOpcode::Pong:
	case WsOpcode::Close:
		LastReceivedFrameTime = FPlatformTime::Seconds();
		break;
	default:
		break;
	}

	switch (Opcode)
	{
	case WsOpcode::Text:
	case WsOpcode::Binary:
	{
		if (bFin && !bInFragment)
		{
			// Unfragmented message
			if (Opcode == WsOpcode::Text)
			{
				// Null-terminate the payload in-place to avoid an extra heap
				// allocation.  Payload is a local temporary so mutation is safe.
				Payload.Add(0);
				NotifyMessage(FString(UTF8_TO_TCHAR(reinterpret_cast<const ANSICHAR*>(Payload.GetData()))));
			}
			else
			{
				NotifyBinaryMessage(Payload, true);
			}
		}
		else if (bInFragment)
		{
			// RFC 6455 §5.4: A new data frame must not start while a fragmented
			// message is still being assembled. The server is misbehaving — send a
			// Close frame (1002 Protocol Error) as required by RFC 6455 §7.2, then
			// discard the in-progress fragment and close the connection.
			UE_LOG(LogSMLWebSocket, Warning,
			       TEXT("SMLWebSocket: Received a new Text/Binary frame while a fragmented "
			            "message was still in progress (RFC 6455 §5.4 violation). "
			            "Discarding %d buffered fragment byte(s) and closing connection."),
			       FragmentBuffer.Num());
			FragmentBuffer.Empty();
			bFragmentIsBinary = false;
			bInFragment = false;
			const uint8 ClosePayload[2] = { 0x03, 0xEA }; // status 1002
			SendWsFrame(WsOpcode::Close, ClosePayload, 2);
			return false;
		}
		else
		{
			// Start of a fragmented message (bFin == false, no fragment in progress).
			// Use bInFragment rather than FragmentBuffer.IsEmpty() as the state
			// indicator: a zero-length first fragment is valid per RFC 6455 §5.4
			// and would leave FragmentBuffer empty, causing a false protocol-error
			// on the subsequent Continuation frame if we relied on the buffer check.
			bFragmentIsBinary = (Opcode == WsOpcode::Binary);
			bInFragment = true;
			FragmentBuffer = MoveTemp(Payload);
		}
		break;
	}
	case WsOpcode::Continuation:
	{
		// RFC 6455 §5.4: a Continuation frame MUST follow a non-final Text or
		// Binary frame.  Receiving one when no fragmented message is in progress
		// is a protocol error — close the connection with status 1002.
		if (!bInFragment)
		{
			UE_LOG(LogSMLWebSocket, Warning,
			       TEXT("SMLWebSocket: Continuation frame received with no open fragmented message – closing connection (1002)"));
			const uint8 ClosePayload[2] = { 0x03, 0xEA }; // status 1002 protocol error
			SendWsFrame(WsOpcode::Close, ClosePayload, 2);
			return false;
		}

		// Guard against the accumulated fragmented message exceeding TArray's int32
		// size limit.  Each individual fragment is already bounded by EffectiveMax,
		// but nothing previously prevented many fragments from summing to 2^31 bytes
		// (e.g. 32 × 64 MB = exactly 2,147,483,648), which triggers the fatal
		// "Trying to resize TArray to an invalid size" crash.
		{
			const int64 NewTotalSize = static_cast<int64>(FragmentBuffer.Num()) + static_cast<int64>(Payload.Num());
			if (NewTotalSize > static_cast<int64>(MAX_int32) || NewTotalSize > static_cast<int64>(EffectiveMax))
			{
				UE_LOG(LogSMLWebSocket, Error,
				       TEXT("SMLWebSocket: Fragmented message accumulated size (%lld bytes) exceeds limit – closing connection"),
				       NewTotalSize);
				FragmentBuffer.Empty();
				bFragmentIsBinary = false;
				bInFragment = false;
				const uint8 ClosePayload[2] = { 0x03, 0xEA }; // status 1002
				SendWsFrame(WsOpcode::Close, ClosePayload, 2);
				return false;
			}
		}
		FragmentBuffer.Append(Payload);
		if (bFin)
		{
			if (bFragmentIsBinary)
			{
				NotifyBinaryMessage(FragmentBuffer, true);
			}
			else
			{
				// Null-terminate the assembled fragment in-place to avoid an
				// extra heap allocation; the buffer is immediately emptied below.
				FragmentBuffer.Add(0);
				const FString Msg = FString(UTF8_TO_TCHAR(reinterpret_cast<const ANSICHAR*>(FragmentBuffer.GetData())));
				NotifyMessage(Msg);
			}
			FragmentBuffer.Empty();
			bInFragment = false;
		}
		break;
	}
	case WsOpcode::Ping:
		SendPong(Payload);
		break;

	case WsOpcode::Pong:
		// Solicited or unsolicited Pong — mark our outstanding ping as answered.
		bWaitingForPong = false;
		PingSentTime    = 0.0;
		break;

	case WsOpcode::Close:
	{
		int32 Code = 1005; // no status code present
		FString Reason;

		if (Payload.Num() >= 2)
		{
			Code = (static_cast<int32>(Payload[0]) << 8) | Payload[1];
			if (Payload.Num() > 2)
			{
				TArray<uint8> ReasonBytes(Payload.GetData() + 2, Payload.Num() - 2);
				ReasonBytes.Add(0);
				Reason = FString(UTF8_TO_TCHAR(reinterpret_cast<const ANSICHAR*>(ReasonBytes.GetData())));
			}
		}

		// Echo the close frame back (RFC 6455 §5.5.1)
		SendWsFrame(WsOpcode::Close, Payload.GetData(), Payload.Num());
		bConnected = false;
		// Flag that the server initiated the close so Run() knows NotifyClosed
		// was already dispatched and does not fire NotifyError on top of it.
		bReceivedServerClose = true;
		NotifyClosed(Code, Reason);
		return false; // exit inner loop; Run() will decide whether to reconnect
	}

	default:
		// RFC 6455 §5.2: reserved opcodes must cause the endpoint to fail the
		// WebSocket connection. Send Close(1002 Protocol Error) and exit.
		UE_LOG(LogSMLWebSocket, Warning, TEXT("SMLWebSocket: Unknown/reserved opcode 0x%02X — sending Close(1002) and disconnecting"), Opcode);
		{
			const uint8 ClosePayload[2] = { 0x03, 0xEA }; // status 1002
			SendWsFrame(WsOpcode::Close, ClosePayload, 2);
		}
		return false;
	}

	return true;
}

void FSMLWebSocketRunnable::SendPong(const TArray<uint8>& Payload)
{
	SendWsFrame(WsOpcode::Pong, Payload.GetData(), Payload.Num());
}

void FSMLWebSocketRunnable::SendPing()
{
	// Payload: current timestamp as 8-byte big-endian milliseconds (for round-trip measurement).
	const uint64 NowMs = static_cast<uint64>(FPlatformTime::Seconds() * 1000.0);
	uint8 PingPayload[8];
	for (int32 i = 7; i >= 0; --i)
	{
		PingPayload[i] = static_cast<uint8>(NowMs >> ((7 - i) * 8));
	}
	if (SendWsFrame(WsOpcode::Ping, PingPayload, 8))
	{
		PingSentTime    = FPlatformTime::Seconds();
		bWaitingForPong = true;
	}
}

void FSMLWebSocketRunnable::FlushOutboundQueue()
{
	if (bHasPendingRetryMessage)
	{
		const uint8 PendingOpcode = PendingRetryMessage.bIsBinary ? WsOpcode::Binary : WsOpcode::Text;
		if (!SendWsFrame(PendingOpcode, PendingRetryMessage.Payload.GetData(), PendingRetryMessage.Payload.Num()))
		{
			UE_LOG(LogSMLWebSocket, Error,
			       TEXT("SMLWebSocket: SendWsFrame failed while retrying the head outbound message — "
			            "triggering reconnect."));
			return;
		}
		bHasPendingRetryMessage = false;
	}

	FSMLWebSocketOutboundMessage Msg;
	while (OutboundMessages.Dequeue(Msg))
	{
		const uint8 Opcode = Msg.bIsBinary ? WsOpcode::Binary : WsOpcode::Text;
		if (!SendWsFrame(Opcode, Msg.Payload.GetData(), Msg.Payload.Num()))
		{
			UE_LOG(LogSMLWebSocket, Error,
			       TEXT("SMLWebSocket: SendWsFrame failed in FlushOutboundQueue — "
			            "triggering reconnect."));
			// Stop draining and let the run-loop detect the broken connection.
			// Preserve the failed head message so reconnect flushes it before any
			// later queued messages, keeping FIFO delivery intact across reconnects.
			PendingRetryMessage = MoveTemp(Msg);
			bHasPendingRetryMessage = true;
			break;
		}
	}
}

// ─────────────────────────────────────────────────────────────────────────────
// Handshake key helpers (RFC 6455 §4.2.2)
// ─────────────────────────────────────────────────────────────────────────────

FString FSMLWebSocketRunnable::GenerateWebSocketKey()
{
	// Generate a random 16-byte nonce and Base64-encode it (Sec-WebSocket-Key).
	// RFC 6455 §4.1 requires a random value; the key is a nonce, not a secret.
	uint8 RawKey[16];
#if PLATFORM_WINDOWS || PLATFORM_LINUX
	// Use OpenSSL's CSPRNG when available (both Satisfactory server platforms).
	RAND_bytes(RawKey, static_cast<int>(sizeof(RawKey)));
#else
	// Fallback for non-SSL platforms: pseudo-random bytes via FMath.
	// The nonce is not security-critical (it just needs to be unique per connection).
	for (int32 i = 0; i < 16; ++i)
	{
		RawKey[i] = static_cast<uint8>(FMath::Rand() & 0xFF);
	}
#endif
	return FBase64::Encode(RawKey, static_cast<int32>(sizeof(RawKey)));
}

FString FSMLWebSocketRunnable::ComputeAcceptKey(const FString& ClientKey)
{
	// RFC 6455 §4.2.2: accept = Base64( SHA1( ClientKey + GUID ) )
	static const FString WsGuid = TEXT("258EAFA5-E914-47DA-95CA-C5AB0DC85B11");
	const FString Concat = ClientKey + WsGuid;

	const FTCHARToUTF8 Utf8(*Concat);
#if PLATFORM_WINDOWS || PLATFORM_LINUX
	// Use OpenSSL's SHA1 (available on both Satisfactory dedicated-server platforms).
	uint8 Hash[SHA_DIGEST_LENGTH];
	SHA1(reinterpret_cast<const uint8*>(Utf8.Get()),
	     static_cast<size_t>(Utf8.Length()),
	     Hash);
	return FBase64::Encode(Hash, SHA_DIGEST_LENGTH);
#else
	// SHA1 requires OpenSSL which is not available on this platform.
	// Satisfactory dedicated servers only run on Win64 and Linux, where OpenSSL is
	// always present, so this branch is dead code in all supported configurations.
	UE_LOG(LogSMLWebSocket, Error,
	       TEXT("SMLWebSocket: SHA1 is not available on this platform. "
	            "WebSocket handshake will fail. "
	            "Satisfactory dedicated servers require Win64 or Linux."));
	return FString();
#endif
}

// ─────────────────────────────────────────────────────────────────────────────
// Game-thread notifications
// ─────────────────────────────────────────────────────────────────────────────

void FSMLWebSocketRunnable::NotifyConnected()
{
	TWeakObjectPtr<USMLWebSocketClient> WeakOwner = Owner;
	const uint32 Gen = ConnectionGeneration;
	AsyncTask(ENamedThreads::GameThread, [WeakOwner, Gen]()
	{
		if (USMLWebSocketClient* Ptr = WeakOwner.Get())
		{
			if (Ptr->ConnectionGeneration == Gen)
			{
				Ptr->Internal_OnConnected();
			}
		}
	});
}

void FSMLWebSocketRunnable::NotifyMessage(const FString& Message)
{
	TWeakObjectPtr<USMLWebSocketClient> WeakOwner = Owner;
	const uint32 Gen = ConnectionGeneration;
	AsyncTask(ENamedThreads::GameThread, [WeakOwner, Gen, Message]()
	{
		if (USMLWebSocketClient* Ptr = WeakOwner.Get())
		{
			if (Ptr->ConnectionGeneration == Gen)
			{
				Ptr->Internal_OnMessage(Message);
			}
		}
	});
}

void FSMLWebSocketRunnable::NotifyBinaryMessage(const TArray<uint8>& Data, bool bIsFinal)
{
	TWeakObjectPtr<USMLWebSocketClient> WeakOwner = Owner;
	const uint32 Gen = ConnectionGeneration;
	AsyncTask(ENamedThreads::GameThread, [WeakOwner, Gen, Data, bIsFinal]()
	{
		if (USMLWebSocketClient* Ptr = WeakOwner.Get())
		{
			if (Ptr->ConnectionGeneration == Gen)
			{
				Ptr->Internal_OnBinaryMessage(Data, bIsFinal);
			}
		}
	});
}

void FSMLWebSocketRunnable::NotifyClosed(int32 Code, const FString& Reason)
{
	TWeakObjectPtr<USMLWebSocketClient> WeakOwner = Owner;
	const uint32 Gen = ConnectionGeneration;
	AsyncTask(ENamedThreads::GameThread, [WeakOwner, Gen, Code, Reason]()
	{
		if (USMLWebSocketClient* Ptr = WeakOwner.Get())
		{
			if (Ptr->ConnectionGeneration == Gen)
			{
				Ptr->Internal_OnClosed(Code, Reason);
			}
		}
	});
}

void FSMLWebSocketRunnable::NotifyError(const FString& Error)
{
	TWeakObjectPtr<USMLWebSocketClient> WeakOwner = Owner;
	const uint32 Gen = ConnectionGeneration;
	AsyncTask(ENamedThreads::GameThread, [WeakOwner, Gen, Error]()
	{
		if (USMLWebSocketClient* Ptr = WeakOwner.Get())
		{
			if (Ptr->ConnectionGeneration == Gen)
			{
				Ptr->Internal_OnError(Error);
			}
		}
	});
}

void FSMLWebSocketRunnable::NotifyReconnecting(int32 AttemptNumber, float DelaySeconds)
{
	TWeakObjectPtr<USMLWebSocketClient> WeakOwner = Owner;
	const uint32 Gen = ConnectionGeneration;
	AsyncTask(ENamedThreads::GameThread, [WeakOwner, Gen, AttemptNumber, DelaySeconds]()
	{
		if (USMLWebSocketClient* Ptr = WeakOwner.Get())
		{
			if (Ptr->ConnectionGeneration == Gen)
			{
				Ptr->Internal_OnReconnecting(AttemptNumber, DelaySeconds);
			}
		}
	});
}
