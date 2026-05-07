// Copyright Yamahasxviper. All Rights Reserved.

#include "SMLWebSocketClient.h"
#include "SMLWebSocket.h"
#include "SMLWebSocketRunnable.h"
#include "HAL/RunnableThread.h"
#include "Async/Async.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

// ─────────────────────────────────────────────────────────────────────────────
// USMLWebSocketClient
// ─────────────────────────────────────────────────────────────────────────────

USMLWebSocketClient::USMLWebSocketClient()
	: bIsConnected(false)
{
}

USMLWebSocketClient::~USMLWebSocketClient()
{
	StopRunnable();
}

void USMLWebSocketClient::BeginDestroy()
{
	StopRunnable();
	Super::BeginDestroy();
}

// ── Factory ───────────────────────────────────────────────────────────────────

USMLWebSocketClient* USMLWebSocketClient::CreateWebSocketClient(UObject* WorldContextObject)
{
	return NewObject<USMLWebSocketClient>(WorldContextObject ? WorldContextObject : GetTransientPackage());
}

// ── Connection ────────────────────────────────────────────────────────────────

void USMLWebSocketClient::Connect(const FString& Url,
                                  const TArray<FString>& Protocols,
                                  const TMap<FString, FString>& ExtraHeaders)
{
	// Stop any existing connection first.
	StopRunnable();

	bIsConnected = false;
	bHasConnectedOnce = false;
	SetConnectionState(EWebSocketState::Connecting);

	// Build the reconnect configuration from our current property values.
	FSMLWebSocketReconnectConfig ReconnectCfg;
	ReconnectCfg.bAutoReconnect            = bAutoReconnect;
	ReconnectCfg.ReconnectInitialDelay     = ReconnectInitialDelaySeconds;
	ReconnectCfg.MaxReconnectDelay         = MaxReconnectDelaySeconds;
	ReconnectCfg.MaxReconnectAttempts      = MaxReconnectAttempts;
	ReconnectCfg.PingInterval              = PingIntervalSeconds;
	ReconnectCfg.PingTimeout               = PingTimeoutSeconds;
	ReconnectCfg.MaxMessageSizeBytes       = MaxMessageSizeBytes;
	ReconnectCfg.ProxyHost                 = ProxyHost;
	ReconnectCfg.ProxyPort                 = ProxyPort;
	ReconnectCfg.ProxyUser                 = ProxyUser;
	ReconnectCfg.ProxyPassword             = ProxyPassword;
	ReconnectCfg.bVerifySSLCertificate     = bVerifySSLCertificate;

	Runnable = MakeShared<FSMLWebSocketRunnable>(this, Url, Protocols, ExtraHeaders, ReconnectCfg,
	                                             ConnectionGeneration);
	RunnableThread = FRunnableThread::Create(Runnable.Get(),
	                                         TEXT("SMLWebSocketThread"),
	                                         0,
	                                         TPri_Normal);
}

// ── Sending ───────────────────────────────────────────────────────────────────

void USMLWebSocketClient::SendText(const FString& Message)
{
	if (bIsConnected && Runnable.IsValid())
	{
		if (Runnable->EnqueueText(Message))
		{
			StatBytesSent.fetch_add(FTCHARToUTF8(Message.GetCharArray().GetData()).Length());
			StatMessagesSent.fetch_add(1);
		}
		return;
	}
	if (bQueueMessagesWhileDisconnected)
	{
		FScopeLock Lock(&QueueMutex);
		PendingSendQueue.Add(Message);
		if (MaxQueuedMessages > 0 && PendingSendQueue.Num() > MaxQueuedMessages)
		{
			UE_LOG(LogSMLWebSocket, VeryVerbose,
				TEXT("SMLWebSocketClient: outbound text queue full (%d) — oldest message dropped"),
				MaxQueuedMessages);
			PendingSendQueue.RemoveAt(0);
		}
	}
}

void USMLWebSocketClient::SendBinary(const TArray<uint8>& Data)
{
	if (bIsConnected && Runnable.IsValid())
	{
		if (Runnable->EnqueueBinary(Data))
		{
			StatBytesSent.fetch_add(Data.Num());
			StatMessagesSent.fetch_add(1);
		}
		return;
	}
	if (bQueueMessagesWhileDisconnected)
	{
		FScopeLock Lock(&QueueMutex);
		PendingSendBinaryQueue.Add(Data);
		if (MaxQueuedMessages > 0 && PendingSendBinaryQueue.Num() > MaxQueuedMessages)
		{
			UE_LOG(LogSMLWebSocket, VeryVerbose,
				TEXT("SMLWebSocketClient: outbound binary queue full (%d) — oldest message dropped"),
				MaxQueuedMessages);
			PendingSendBinaryQueue.RemoveAt(0);
		}
	}
}

void USMLWebSocketClient::SendBinary(TArray<uint8>&& Data)
{
	const int32 NumBytes = Data.Num();
	if (bIsConnected && Runnable.IsValid())
	{
		if (Runnable->EnqueueBinary(MoveTemp(Data)))
		{
			StatBytesSent.fetch_add(NumBytes);
			StatMessagesSent.fetch_add(1);
		}
		return;
	}
	if (bQueueMessagesWhileDisconnected)
	{
		FScopeLock Lock(&QueueMutex);
		PendingSendBinaryQueue.Add(MoveTemp(Data));
		if (MaxQueuedMessages > 0 && PendingSendBinaryQueue.Num() > MaxQueuedMessages)
		{
			UE_LOG(LogSMLWebSocket, VeryVerbose,
				TEXT("SMLWebSocketClient: outbound binary queue full (%d) — oldest message dropped"),
				MaxQueuedMessages);
			PendingSendBinaryQueue.RemoveAt(0);
		}
	}
}

// ── Lifecycle ─────────────────────────────────────────────────────────────────

void USMLWebSocketClient::Close(int32 Code, const FString& Reason)
{
	if (Runnable.IsValid())
	{
		bIsConnected = false;
		SetConnectionState(EWebSocketState::Closing);
		Runnable->EnqueueClose(Code, Reason);
	}
}

bool USMLWebSocketClient::IsConnected() const
{
	return bIsConnected;
}

EWebSocketState USMLWebSocketClient::GetConnectionState() const
{
	return static_cast<EWebSocketState>(ConnectionState.load());
}

// ── Private helpers ───────────────────────────────────────────────────────────

void USMLWebSocketClient::StopRunnable()
{
	// Invalidate any game-thread callbacks that were queued by the old
	// connection before we tear it down.  The Notify* lambdas inside
	// FSMLWebSocketRunnable capture this generation value and silently
	// discard their work when it no longer matches.
	++ConnectionGeneration;

	if (Runnable.IsValid())
	{
		Runnable->Stop();
	}
	if (RunnableThread)
	{
		RunnableThread->Kill(true /*bShouldWait*/);
		delete RunnableThread;
		RunnableThread = nullptr;
	}
	Runnable.Reset();
	bIsConnected = false;
	SetConnectionState(EWebSocketState::Disconnected);
}

void USMLWebSocketClient::SetConnectionState(EWebSocketState NewState)
{
	const EWebSocketState OldState = static_cast<EWebSocketState>(ConnectionState.load());
	if (OldState == NewState) return;
	ConnectionState.store(static_cast<uint8>(NewState));
	if (OnStateChanged.IsBound())
	{
		OnStateChanged.Broadcast(OldState, NewState);
	}
}

// ── Internal callbacks (called on the game thread) ────────────────────────────

void USMLWebSocketClient::Internal_OnConnected()
{
	bIsConnected = true;
	SetConnectionState(EWebSocketState::Connected);

	// Reset connection stats for the new session.
	StatBytesSent.store(0);
	StatBytesReceived.store(0);
	StatMessagesSent.store(0);
	StatMessagesReceived.store(0);
	StatConnectTime = FPlatformTime::Seconds();

	// Flush messages that were queued while the connection was down.
	{
		FScopeLock Lock(&QueueMutex);
		for (const FString& Msg : PendingSendQueue)
		{
			if (Runnable.IsValid())
			{
				Runnable->EnqueueText(Msg);
			}
		}
		PendingSendQueue.Empty();

		for (const TArray<uint8>& Payload : PendingSendBinaryQueue)
		{
			if (Runnable.IsValid())
			{
				Runnable->EnqueueBinary(Payload);
			}
		}
		PendingSendBinaryQueue.Empty();
	}

	if (bHasConnectedOnce)
	{
		OnReconnected.Broadcast();
	}
	else
	{
		bHasConnectedOnce = true;
		OnConnected.Broadcast();
	}
}

void USMLWebSocketClient::Internal_OnMessage(const FString& Message)
{
	StatBytesReceived.fetch_add(FTCHARToUTF8(Message.GetCharArray().GetData()).Length());
	StatMessagesReceived.fetch_add(1);

	OnMessage.Broadcast(Message);

	// Fire OnJsonMessage when the text parses as JSON.
	TSharedPtr<FJsonObject> Obj;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Message);
	if (FJsonSerializer::Deserialize(Reader, Obj) && Obj.IsValid())
	{
		OnJsonMessage.Broadcast(Message);
	}
}

void USMLWebSocketClient::Internal_OnBinaryMessage(const TArray<uint8>& Data, bool bIsFinal)
{
	OnBinaryMessage.Broadcast(Data, bIsFinal);
}

void USMLWebSocketClient::Internal_OnClosed(int32 StatusCode, const FString& Reason)
{
	bIsConnected = false;
	SetConnectionState(bAutoReconnect ? EWebSocketState::Connecting : EWebSocketState::Disconnected);
	OnClosed.Broadcast(StatusCode, Reason);
}

void USMLWebSocketClient::Internal_OnError(const FString& ErrorMessage)
{
	bIsConnected = false;
	SetConnectionState(bAutoReconnect ? EWebSocketState::Connecting : EWebSocketState::Disconnected);
	OnError.Broadcast(ErrorMessage);
}

void USMLWebSocketClient::Internal_OnReconnecting(int32 AttemptNumber, float DelaySeconds)
{
	bIsConnected = false;
	OnReconnecting.Broadcast(AttemptNumber, DelaySeconds);
}

// ── Queued message helpers ────────────────────────────────────────────────────

int32 USMLWebSocketClient::GetQueuedMessageCount() const
{
	FScopeLock Lock(&QueueMutex);
	return PendingSendQueue.Num() + PendingSendBinaryQueue.Num();
}

void USMLWebSocketClient::ClearQueue()
{
	FScopeLock Lock(&QueueMutex);
	PendingSendQueue.Empty();
	PendingSendBinaryQueue.Empty();
}

void USMLWebSocketClient::FlushQueue()
{
	if (!bIsConnected || !Runnable.IsValid()) return;

	FScopeLock Lock(&QueueMutex);
	for (const FString& Msg : PendingSendQueue)
	{
		if (Runnable->EnqueueText(Msg))
		{
			StatBytesSent.fetch_add(FTCHARToUTF8(Msg.GetCharArray().GetData()).Length());
			StatMessagesSent.fetch_add(1);
		}
	}
	PendingSendQueue.Empty();

	for (const TArray<uint8>& Payload : PendingSendBinaryQueue)
	{
		if (Runnable->EnqueueBinary(Payload))
		{
			StatBytesSent.fetch_add(Payload.Num());
			StatMessagesSent.fetch_add(1);
		}
	}
	PendingSendBinaryQueue.Empty();
}

void USMLWebSocketClient::SendJson(const FString& JsonString)
{
	SendText(JsonString);
}

FSMLWebSocketStats USMLWebSocketClient::GetConnectionStats() const
{
	FSMLWebSocketStats Stats;
	Stats.BytesSent        = StatBytesSent.load();
	Stats.BytesReceived    = StatBytesReceived.load();
	Stats.MessagesSent     = StatMessagesSent.load();
	Stats.MessagesReceived = StatMessagesReceived.load();

	if (bIsConnected && StatConnectTime > 0.0)
		Stats.ConnectedForSeconds = static_cast<float>(FPlatformTime::Seconds() - StatConnectTime);
	else
		Stats.ConnectedForSeconds = 0.0f;

	return Stats;
}
