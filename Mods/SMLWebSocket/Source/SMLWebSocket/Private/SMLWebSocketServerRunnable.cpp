// Copyright Yamahasxviper. All Rights Reserved.

#include "SMLWebSocketServerRunnable.h"
#include "SMLWebSocketServer.h"

#include "Async/Async.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "IPAddress.h"
#include "Misc/Base64.h"
#include "HAL/PlatformProcess.h"
#include "Misc/SecureHash.h"

DEFINE_LOG_CATEGORY_STATIC(LogWSServer, Log, All);

std::atomic<uint64> FSMLWebSocketServerRunnable::NextClientId{1};

// ─────────────────────────────────────────────────────────────────────────────
//  Construction / destruction
// ─────────────────────────────────────────────────────────────────────────────

FSMLWebSocketServerRunnable::FSMLWebSocketServerRunnable(USMLWebSocketServer* InOwner, int32 InPort,
                                                          const FString& InApiToken)
    : Owner(InOwner)
    , ListenPort(InPort)
    , ApiToken(InApiToken)
{}

FSMLWebSocketServerRunnable::~FSMLWebSocketServerRunnable()
{
    if (ListenSocket)
    {
        ISocketSubsystem* SocketSS = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
        if (SocketSS)
            SocketSS->DestroySocket(ListenSocket);
        ListenSocket = nullptr;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  FRunnable
// ─────────────────────────────────────────────────────────────────────────────

bool FSMLWebSocketServerRunnable::Init()
{
    ISocketSubsystem* SocketSub = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
    if (!SocketSub)
    {
        UE_LOG(LogWSServer, Error, TEXT("WSServer: socket subsystem unavailable"));
        return false;
    }
    ListenSocket = SocketSub->CreateSocket(NAME_Stream, TEXT("SMLWSServer"), false);
    if (!ListenSocket)
    {
        UE_LOG(LogWSServer, Error, TEXT("WSServer: failed to create listen socket"));
        return false;
    }

    ListenSocket->SetReuseAddr(true);
    if (!ListenSocket->SetNonBlocking(false))
    {
        UE_LOG(LogWSServer, Warning,
            TEXT("WSServer: SetNonBlocking(false) failed — socket blocking mode may be undefined"));
    }

    TSharedRef<FInternetAddr> Addr = SocketSub->CreateInternetAddr();
    Addr->SetAnyAddress();
    Addr->SetPort(ListenPort);

    if (!ListenSocket->Bind(*Addr))
    {
        UE_LOG(LogWSServer, Error, TEXT("WSServer: failed to bind to port %d"), ListenPort);
        SocketSub->DestroySocket(ListenSocket);
        ListenSocket = nullptr;
        return false;
    }

    if (!ListenSocket->Listen(8))
    {
        UE_LOG(LogWSServer, Error, TEXT("WSServer: failed to listen on port %d"), ListenPort);
        SocketSub->DestroySocket(ListenSocket);
        ListenSocket = nullptr;
        return false;
    }

    UE_LOG(LogWSServer, Log, TEXT("WSServer: listening on port %d"), ListenPort);
    return true;
}

uint32 FSMLWebSocketServerRunnable::Run()
{
    while (!bStopping.load())
    {
        // Send the queued Close frames and destroy the deferred sockets.  This
        // drain must happen at the top of the loop, before the OutboundQueue drain
        // below collects new raw socket snapshots.  Any socket enqueued by
        // DisconnectClient() was already removed from Clients (under
        // ClientMutex) before being enqueued here, so no new snapshot of it
        // will be taken after this point; all outstanding snapshots were taken
        // in the *previous* iteration and their SendFrame() calls have already
        // completed, making it safe to call SendFrame and then destroy the socket now.
        {
            FPendingCloseSocket S;
            ISocketSubsystem* SocketSS = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
            while (SocketsToDestroy.Dequeue(S))
            {
                // RFC 6455 §7.1.1: send a Close frame before closing the TCP connection.
                // Ignore the return value — if the client has already closed their side
                // the send will fail, but we must still destroy the socket.
                SendFrame(S.Socket, S.CloseFrame);
                if (SocketSS)
                    SocketSS->DestroySocket(S.Socket);
                else
                    delete S.Socket;
            }
        }

        // Accept any pending connections (non-blocking poll).
        bool bHasPending = false;
        if (ListenSocket && ListenSocket->HasPendingConnection(bHasPending) && bHasPending)
        {
            ISocketSubsystem* AcceptSS = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
            if (!AcceptSS)
            {
                UE_LOG(LogWSServer, Warning, TEXT("WSServer: socket subsystem unavailable, cannot accept connection"));
            }
            else
            {
                TSharedRef<FInternetAddr> RemoteAddr = AcceptSS->CreateInternetAddr();
                FSocket* NewSocket = ListenSocket->Accept(*RemoteAddr, TEXT("SMLWSClient"));
                if (NewSocket)
                {
                    const FString ClientId = FString::Printf(TEXT("%llu"), NextClientId.fetch_add(1));
                    const FString Remote   = RemoteAddr->ToString(true);

                    FClientState State;
                    State.Socket        = NewSocket;
                    State.RemoteAddress = Remote;
                    State.bHandshakeDone = false;

                    if (PerformHandshake(State))
                    {
                        State.bHandshakeDone = true;
                        {
                            FScopeLock L(&ClientMutex);
                            Clients.Add(ClientId, MoveTemp(State));
                        }

                        TWeakObjectPtr<USMLWebSocketServer> WeakOwner = Owner;
                        AsyncTask(ENamedThreads::GameThread, [WeakOwner, ClientId, Remote]()
                        {
                            if (USMLWebSocketServer* O = WeakOwner.Get())
                                O->Internal_OnClientConnected(ClientId, Remote);
                        });
                    }
                    else
                    {
                        AcceptSS->DestroySocket(NewSocket);
                    }
                }
            }
        }

        // Drain outbound queue.
        // Collect target sockets while holding ClientMutex, then release the
        // lock before calling SendFrame().  SendFrame() performs a blocking
        // socket write; holding ClientMutex across it would stall the read
        // loop (which also locks ClientMutex) for every slow or full-buffer
        // client.
        FOutboundMsg Msg;
        while (OutboundQueue.Dequeue(Msg))
        {
            TArray<FSocket*> Targets;
            {
                FScopeLock L(&ClientMutex);
                if (Msg.ClientId.IsEmpty())
                {
                    // Broadcast: collect all connected sockets.
                    for (auto& KV : Clients)
                        Targets.Add(KV.Value.Socket);
                }
                else
                {
                    FClientState* C = Clients.Find(Msg.ClientId);
                    if (C) Targets.Add(C->Socket);
                }
            } // ClientMutex released before any blocking I/O
            for (FSocket* Sock : Targets)
                SendFrame(Sock, Msg.Frame);
        }

        // Read from connected clients.
        TArray<FString> ToRemove;
        {
            FScopeLock L(&ClientMutex);
            for (auto& KV : Clients)
            {
                FClientState& C = KV.Value;
                uint32 Pending = 0;
                if (!C.Socket->HasPendingData(Pending))
                {
                    // HasPendingData() returns false when the socket has been
                    // closed by the remote side (connection reset / EOF).
                    // We must also verify that the socket is actually in a
                    // connected state before treating this as a disconnect.
                    ESocketConnectionState State = C.Socket->GetConnectionState();
                    if (State != SCS_Connected)
                    {
                        ToRemove.Add(KV.Key);
                    }
                    continue;
                }
                if (Pending == 0) continue;

                const int32 OldLen = C.RecvBuffer.Num();
                if (Pending > static_cast<uint32>(MAX_int32))
                {
                    UE_LOG(LogWSServer, Error,
                        TEXT("WSServer: pending read too large (%u bytes) – dropping client"),
                        Pending);
                    ToRemove.Add(KV.Key);
                    continue;
                }

                const int32 Pending32 = static_cast<int32>(Pending);
                if (OldLen > (MAX_int32 - Pending32))
                {
                    UE_LOG(LogWSServer, Error,
                        TEXT("WSServer: receive buffer growth overflow (old=%d, pending=%u) – dropping client"),
                        OldLen, Pending);
                    ToRemove.Add(KV.Key);
                    continue;
                }

                C.RecvBuffer.SetNum(OldLen + Pending32);
                int32 Read = 0;
                if (!C.Socket->Recv(C.RecvBuffer.GetData() + OldLen, Pending32, Read))
                {
                    // Restore buffer to its original size so the oversized
                    // allocation is not held until the client slot is removed.
                    C.RecvBuffer.SetNum(OldLen);
                    ToRemove.Add(KV.Key);
                    continue;
                }
                if (Read < 0 || Read > Pending32)
                {
                    UE_LOG(LogWSServer, Error,
                        TEXT("WSServer: socket returned invalid read size (%d, pending=%d) – dropping client"),
                        Read, Pending32);
                    C.RecvBuffer.SetNum(OldLen);
                    ToRemove.Add(KV.Key);
                    continue;
                }
                C.RecvBuffer.SetNum(OldLen + Read);

                // Read == 0 means the remote peer closed the connection (EOF).
                // Treat it as a disconnect so the client slot is cleaned up.
                if (Read == 0)
                {
                    ToRemove.Add(KV.Key);
                    continue;
                }

                if (!ProcessFrames(KV.Key, C))
                    ToRemove.Add(KV.Key);
            }
        }

        for (const FString& Id : ToRemove)
        {
            FClientState Removed;
            bool bWasRemoved = false;
            {
                FScopeLock L(&ClientMutex);
                bWasRemoved = Clients.RemoveAndCopyValue(Id, Removed);
            }
            if (bWasRemoved)
            {
                // Send any pending RFC 6455 Close frame (set by ProcessFrames for received
                // Close frames and protocol violations) BEFORE destroying the socket.
                // The outbound queue is drained at the TOP of the iteration — before the
                // read phase — so anything enqueued in ProcessFrames would be orphaned once
                // the client is removed from Clients.  Sending inline here ensures the
                // remote peer always receives the Close frame as required by RFC 6455 §7.1.1.
                if (Removed.PendingCloseFrame.Num() > 0)
                    SendFrame(Removed.Socket, Removed.PendingCloseFrame);

                ISocketSubsystem* RemoveSS = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
                if (RemoveSS)
                    RemoveSS->DestroySocket(Removed.Socket);
                else
                    delete Removed.Socket;
            }
            TWeakObjectPtr<USMLWebSocketServer> WeakOwner = Owner;
            AsyncTask(ENamedThreads::GameThread, [WeakOwner, Id]()
            {
                if (USMLWebSocketServer* O = WeakOwner.Get())
                    O->Internal_OnClientDisconnected(Id, TEXT("connection closed"));
            });
        }

        FPlatformProcess::SleepNoStats(0.005f);
    }

    // Close all client sockets on shutdown and notify the game thread for each.
    // RFC 6455 §7.1.1 + §7.4.1: send Close(1001 Going Away) before destroying each
    // socket.  SendFrame is blocking I/O — collect sockets while holding the mutex,
    // then send Close frames and destroy outside it to avoid indefinite lock stalls.
    TArray<FString> RemainingIds;
    TArray<FSocket*> ShutdownSockets;
    {
        FScopeLock L(&ClientMutex);
        for (auto& KV : Clients)
        {
            RemainingIds.Add(KV.Key);
            ShutdownSockets.Add(KV.Value.Socket);
        }
        Clients.Empty();
    }
    {
        ISocketSubsystem* SocketSS = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
        const TArray<uint8> GoingAwayFrame = { 0x88, 0x02, 0x03, 0xE9 };
        for (FSocket* S : ShutdownSockets)
        {
            SendFrame(S, GoingAwayFrame); // ignore failure — client may already be gone
            if (SocketSS)
                SocketSS->DestroySocket(S);
            else
                delete S;
        }
    }
    TWeakObjectPtr<USMLWebSocketServer> WeakOwner = Owner;
    for (FString& ClientId : RemainingIds)
    {
        AsyncTask(ENamedThreads::GameThread, [WeakOwner, Id = MoveTemp(ClientId)]()
        {
            if (USMLWebSocketServer* O = WeakOwner.Get())
                O->Internal_OnClientDisconnected(Id, TEXT("server stopped"));
        });
    }

    // Final drain of SocketsToDestroy: a DisconnectClient() call may have
    // raced with the shutdown cleanup above, removing a client from Clients
    // (so it was not destroyed in the loop) and enqueueing its socket here.
    {
        FPendingCloseSocket S;
        ISocketSubsystem* SocketSS = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
        while (SocketsToDestroy.Dequeue(S))
        {
            SendFrame(S.Socket, S.CloseFrame);
            if (SocketSS)
                SocketSS->DestroySocket(S.Socket);
            else
                delete S.Socket;
        }
    }

    return 0;
}

void FSMLWebSocketServerRunnable::Stop()
{
    bStopping.store(true);
}

void FSMLWebSocketServerRunnable::Exit()
{
}

// ─────────────────────────────────────────────────────────────────────────────
//  Handshake
// ─────────────────────────────────────────────────────────────────────────────

bool FSMLWebSocketServerRunnable::PerformHandshake(FClientState& Client)
{
    // Read HTTP request headers.
    TArray<uint8> HeaderBuf;
    HeaderBuf.Reserve(1024);
    uint8 Ch = 0;
    int32 Recv = 0;
    bool bFoundHeaderEnd = false;

    // Prevent a slow/adversarial client from pinning this thread indefinitely
    // by reading one byte at a time with no deadline.
    Client.Socket->SetReceiveTimeout(FTimespan::FromSeconds(5));

    for (int32 i = 0; i < 8192 && !bStopping.load(); ++i)
    {
        if (!Client.Socket->Recv(&Ch, 1, Recv) || Recv == 0) return false;
        HeaderBuf.Add(Ch);
        // Look for \r\n\r\n.
        const int32 N = HeaderBuf.Num();
        if (N >= 4 &&
            HeaderBuf[N-4] == '\r' && HeaderBuf[N-3] == '\n' &&
            HeaderBuf[N-2] == '\r' && HeaderBuf[N-1] == '\n')
        {
            bFoundHeaderEnd = true;
            break;
        }
    }

    // If the loop exhausted the budget without finding the header terminator,
    // the request is incomplete or malformed — reject it.
    if (!bFoundHeaderEnd)
    {
        UE_LOG(LogWSServer, Warning,
            TEXT("WSServer: Rejected client — HTTP header terminator not found within 8192 bytes."));
        return false;
    }

    FString Headers = FUTF8ToTCHAR(reinterpret_cast<const ANSICHAR*>(HeaderBuf.GetData()), HeaderBuf.Num()).Get();

    // Extract Sec-WebSocket-Key.
    FString Key;
    const FString Marker = TEXT("Sec-WebSocket-Key: ");
    int32 KeyPos = Headers.Find(Marker, ESearchCase::IgnoreCase);
    if (KeyPos == INDEX_NONE) return false;
    int32 Start = KeyPos + Marker.Len();
    int32 End   = Headers.Find(TEXT("\r\n"), ESearchCase::CaseSensitive, ESearchDir::FromStart, Start);
    if (End == INDEX_NONE) return false;
    Key = Headers.Mid(Start, End - Start).TrimStartAndEnd();

    // Compute accept key: SHA1(Key + GUID) → Base64.
    const FString Combined = Key + TEXT("258EAFA5-E914-47DA-95CA-C5AB0DC85B11");
    const FTCHARToUTF8 CombinedUtf8(*Combined);
    FSHA1 Sha;
    Sha.Update(reinterpret_cast<const uint8*>(CombinedUtf8.Get()),
               static_cast<uint32>(CombinedUtf8.Length()));
    Sha.Final();
    uint8 Hash[20];
    Sha.GetHash(Hash);
    const FString Accept = FBase64::Encode(Hash, 20);

    // ── API token check ──────────────────────────────────────────────────────
    if (!ApiToken.IsEmpty())
    {
        FString AuthValue;
        const FString AuthPrefix = TEXT("Authorization:");
        int32 AuthIdx = Headers.Find(AuthPrefix, ESearchCase::IgnoreCase);
        if (AuthIdx != INDEX_NONE)
        {
            const int32 ValueStart = AuthIdx + AuthPrefix.Len();
            int32 LineEnd = Headers.Find(TEXT("\r\n"), ESearchCase::CaseSensitive, ESearchDir::FromStart, ValueStart);
            if (LineEnd == INDEX_NONE) LineEnd = Headers.Len();
            AuthValue = Headers.Mid(ValueStart, LineEnd - ValueStart).TrimStartAndEnd();
        }

        const FString Expected = FString(TEXT("Bearer ")) + ApiToken;

        // Use a constant-time byte comparison to avoid timing side-channel
        // attacks that could allow an attacker to brute-force the token one
        // byte at a time by measuring response latency.
        const FTCHARToUTF8 AuthUtf8(*AuthValue);
        const FTCHARToUTF8 ExpectedUtf8(*Expected);
        const int32 AuthLen     = AuthUtf8.Length();
        const int32 ExpectedLen = ExpectedUtf8.Length();

        // XOR-fold all bytes from both strings — result is 0 only when every
        // byte matches.  Running the full loop regardless of length ensures the
        // comparison takes the same time whether or not the lengths differ.
        // volatile prevents dead-store-elimination of the loop body when the
        // compiler can infer from the length XOR that Diff is already non-zero.
        volatile uint32 Diff = static_cast<uint32>(AuthLen ^ ExpectedLen);
        const int32 CmpLen = FMath::Min(AuthLen, ExpectedLen);
        for (int32 i = 0; i < CmpLen; ++i)
            Diff |= static_cast<uint32>(static_cast<uint8>(AuthUtf8.Get()[i])) ^ static_cast<uint32>(static_cast<uint8>(ExpectedUtf8.Get()[i]));

        if (Diff != 0)
        {
            const FString Response401 =
                TEXT("HTTP/1.1 401 Unauthorized\r\n")
                TEXT("Content-Length: 0\r\n")
                TEXT("Connection: close\r\n\r\n");
            FTCHARToUTF8 R401Utf8(*Response401);
            const int32 R401Len = R401Utf8.Length();
            int32 Sent401 = 0;
            while (Sent401 < R401Len)
            {
                int32 Sent = 0;
                if (!Client.Socket->Send(
                        reinterpret_cast<const uint8*>(R401Utf8.Get()) + Sent401,
                        R401Len - Sent401, Sent)
                    || Sent <= 0)
                {
                    break; // best-effort: connection is being rejected anyway
                }
                Sent401 += Sent;
            }
            UE_LOG(LogWSServer, Warning, TEXT("WSServer: Rejected client — invalid or missing API token."));
            return false;
        }
    }

    // Send HTTP 101 response.
    FString Response = FString(TEXT("HTTP/1.1 101 Switching Protocols\r\n")
                               TEXT("Upgrade: websocket\r\n")
                               TEXT("Connection: Upgrade\r\n"))
                       + TEXT("Sec-WebSocket-Accept: ") + Accept + TEXT("\r\n")
                       + TEXT("\r\n");
    FTCHARToUTF8 ResponseUtf8(*Response);
    const int32 TotalLen = ResponseUtf8.Length();
    int32 TotalSent = 0;
    while (TotalSent < TotalLen)
    {
        int32 Sent = 0;
        if (!Client.Socket->Send(
                reinterpret_cast<const uint8*>(ResponseUtf8.Get()) + TotalSent,
                TotalLen - TotalSent, Sent)
            || Sent <= 0)
        {
            return false;
        }
        TotalSent += Sent;
    }
    // Clear the 5-second handshake guard so the normal message loop is not
    // subject to a receive deadline it does not expect.
    Client.Socket->SetReceiveTimeout(FTimespan::Zero());
    return true;
}
// ─────────────────────────────────────────────────────────────────────────────

// Maximum total message size (after reassembly of all fragments), in bytes.
// Prevents a malicious client from forcing a giant allocation via fragmented frames.
static constexpr int32 MaxMessageBytes = 4 * 1024 * 1024; // 4 MB

bool FSMLWebSocketServerRunnable::ProcessFrames(const FString& ClientId, FClientState& Client)
{
    TArray<uint8>& Buf = Client.RecvBuffer;

    while (Buf.Num() >= 2)
    {
        const uint8 B0 = Buf[0];
        const uint8 B1 = Buf[1];
        const bool  bFin    = (B0 & 0x80) != 0;
        const uint8 Opcode  = B0 & 0x0F;
        const bool  bMasked = (B1 & 0x80) != 0;
        uint64 PayloadLen   = B1 & 0x7F;

        // RFC 6455 §5.2: RSV1/RSV2/RSV3 must all be zero when no extension is negotiated.
        if (B0 & 0x70)
        {
            UE_LOG(LogWSServer, Error, TEXT("WSServer: Frame with nonzero RSV bits — dropping client"));
            return false;
        }

        // RFC 6455 §5.1: A server MUST close the connection if a client sends an unmasked frame.
        if (!bMasked)
        {
            UE_LOG(LogWSServer, Error, TEXT("WSServer: Client sent an unmasked frame — dropping client (RFC 6455 §5.1)"));
            // Store the Close(1002) frame in PendingCloseFrame so the ToRemove loop
            // sends it before destroying the socket (OutboundQueue is drained at the
            // TOP of the iteration — after the client is removed — so enqueuing there
            // would result in the frame never being sent).
            Client.PendingCloseFrame = { 0x88, 0x02, 0x03, 0xEA }; // FIN=1, Close, 1002
            return false;
        }

        int32 HeaderSize = 2;
        if (PayloadLen == 126)
        {
            if (Buf.Num() < 4) break;
            PayloadLen = (static_cast<uint64>(Buf[2]) << 8) | Buf[3];
            HeaderSize = 4;
        }
        else if (PayloadLen == 127)
        {
            if (Buf.Num() < 10) break;
            PayloadLen = 0;
            for (int32 i = 0; i < 8; ++i)
                PayloadLen = (PayloadLen << 8) | Buf[2 + i];
            // RFC 6455 §5.2: the most significant bit of the 8-byte length MUST be 0.
            if (PayloadLen & (static_cast<uint64>(1) << 63))
            {
                UE_LOG(LogWSServer, Error,
                    TEXT("WSServer: Frame has invalid 8-byte payload length (MSB set) – dropping client"));
                return false;
            }
            HeaderSize = 10;
        }

        const int32 MaskSize = bMasked ? 4 : 0;

        // Guard against payloads larger than int32 max (TArray size limit).
        if (PayloadLen > static_cast<uint64>(MAX_int32 - HeaderSize - MaskSize))
        {
            UE_LOG(LogWSServer, Error,
                TEXT("WSServer: Frame payload too large (%llu bytes) – dropping client"),
                static_cast<unsigned long long>(PayloadLen));
            return false;
        }

        const int32 PayloadLen32 = static_cast<int32>(PayloadLen);
        const int32 TotalSize = HeaderSize + MaskSize + PayloadLen32;
        if (Buf.Num() < TotalSize) break;

        // RFC 6455 §5.5: control frames (opcode 0x8/0x9/0xA) must have FIN=1 and payload ≤ 125.
        const bool bIsControl = (Opcode == 0x8 || Opcode == 0x9 || Opcode == 0xA);
        if (bIsControl && (!bFin || PayloadLen32 > 125))
        {
            UE_LOG(LogWSServer, Error,
                TEXT("WSServer: Invalid control frame (FIN=%d, PayloadLen=%d) — dropping client"),
                (int)bFin, PayloadLen32);
            return false;
        }

        if (Opcode == 0x8) // Close
        {
            // RFC 6455 §5.5.1: echo a Close frame back before closing the connection.
            // The echo must include the client's status code (first 2 bytes of payload,
            // unmasked) if the client supplied one; otherwise send an empty payload.
            // Store in PendingCloseFrame rather than OutboundQueue: the outbound drain
            // runs at the TOP of the next iteration, after the socket has already been
            // removed and destroyed by the ToRemove loop, so it would never be sent.
            TArray<uint8> CloseEcho;
            CloseEcho.Add(0x88); // FIN=1, opcode=0x8
            if (PayloadLen32 >= 2)
            {
                // Unmask the 2-byte status code using the mask key at Buf[HeaderSize].
                const uint8 CloseB0 = Buf[HeaderSize + MaskSize + 0] ^ (bMasked ? Buf[HeaderSize + 0] : 0);
                const uint8 CloseB1 = Buf[HeaderSize + MaskSize + 1] ^ (bMasked ? Buf[HeaderSize + 1] : 0);
                CloseEcho.Add(0x02); // payload length = 2
                CloseEcho.Add(CloseB0);
                CloseEcho.Add(CloseB1);
            }
            else
            {
                CloseEcho.Add(0x00); // no payload
            }
            Client.PendingCloseFrame = MoveTemp(CloseEcho);
            Buf.RemoveAt(0, TotalSize);
            return false;
        }

        if (Opcode == 0x9) // Ping — respond with Pong
        {
            // Echo the payload back as a Pong (opcode 0xA, FIN=1).
            // Per RFC 6455 §5.3, client frames are masked; the mask key occupies
            // the 4 bytes at Buf[HeaderSize..HeaderSize+3] when bMasked is true.
            // We must XOR each payload byte with the mask key before echoing it —
            // sending back the raw (still-masked) bytes is a §5.3 violation.
            const int32 PongPayloadLen = FMath::Min(PayloadLen32, 125); // Pong payload ≤ 125 bytes
            TArray<uint8> PongFrame;
            PongFrame.Add(0x8A); // FIN=1, opcode=0xA
            PongFrame.Add(static_cast<uint8>(PongPayloadLen));
            for (int32 i = 0; i < PongPayloadLen; ++i)
            {
                const uint8 Raw = Buf[HeaderSize + MaskSize + i];
                const uint8 Unmasked = bMasked
                    ? (Raw ^ Buf[HeaderSize + (i & 3)])
                    : Raw;
                PongFrame.Add(Unmasked);
            }
            // Enqueue the pong for the outbound-drain phase which runs outside
            // the ClientMutex lock.  SendFrame() is a blocking socket write; calling
            // it here under ClientMutex would stall any game-thread call to
            // GetClientCount/GetClientIds/DisconnectClient that also takes the lock.
            FOutboundMsg Pong;
            Pong.ClientId = ClientId;
            Pong.Frame    = MoveTemp(PongFrame);
            OutboundQueue.Enqueue(MoveTemp(Pong));
            Buf.RemoveAt(0, TotalSize);
            continue;
        }

        if (Opcode == 0xA) // Pong — RFC 6455 §5.5.3: silently accept, no reply
        {
            Buf.RemoveAt(0, TotalSize);
            continue;
        }

        if (Opcode == 0x1 || Opcode == 0x2 || Opcode == 0x0) // Text, Binary, or Continuation
        {
            uint8 Mask[4] = {0,0,0,0};
            if (bMasked)
            {
                for (int32 i = 0; i < 4; ++i)
                    Mask[i] = Buf[HeaderSize + i];
            }

            TArray<uint8> Payload;
            Payload.SetNum(PayloadLen32);
            for (int32 i = 0; i < PayloadLen32; ++i)
                Payload[i] = Buf[HeaderSize + MaskSize + i] ^ (bMasked ? Mask[i % 4] : 0);

            if (Opcode == 0x1 || Opcode == 0x2) // Start of a new message (possibly fragmented)
            {
                if (bFin)
                {
                    // RFC 6455 §5.4: a new data frame must not arrive while a
                    // fragmented message is being assembled.
                    if (Client.bInFragment)
                    {
                        UE_LOG(LogWSServer, Warning,
                            TEXT("WSServer: New data frame received while fragment in progress — dropping client"));
                        Client.PendingCloseFrame = { 0x88, 0x02, 0x03, 0xEA }; // Close 1002
                        return false;
                    }
                    // Single unfragmented frame — deliver immediately.
                    if (Opcode == 0x2)
                    {
                        TWeakObjectPtr<USMLWebSocketServer> WeakOwner = Owner;
                        const FString CId = ClientId;
                        AsyncTask(ENamedThreads::GameThread, [WeakOwner, CId, Payload = MoveTemp(Payload)]()
                        {
                            if (USMLWebSocketServer* O = WeakOwner.Get())
                                O->Internal_OnClientBinaryMessage(CId, Payload);
                        });
                    }
                    else
                    {
                        Payload.Add(0);
                        const FString Text = FString(UTF8_TO_TCHAR(reinterpret_cast<const ANSICHAR*>(Payload.GetData())));
                        TWeakObjectPtr<USMLWebSocketServer> WeakOwner = Owner;
                        const FString CId = ClientId;
                        AsyncTask(ENamedThreads::GameThread, [WeakOwner, CId, Text]()
                        {
                            if (USMLWebSocketServer* O = WeakOwner.Get())
                                O->Internal_OnClientMessage(CId, Text);
                        });
                    }
                    // Ensure no stale fragment state remains.
                    Client.bInFragment = false;
                    Client.FragmentBuffer.Reset();
                }
                else
                {
                    // RFC 6455 §5.4: a new fragmented data frame must not arrive
                    // while another fragmented message is still being assembled.
                    if (Client.bInFragment)
                    {
                        UE_LOG(LogWSServer, Warning,
                            TEXT("WSServer: New fragmented data frame received while fragment in progress — dropping client"));
                        Client.PendingCloseFrame = { 0x88, 0x02, 0x03, 0xEA }; // Close 1002
                        return false;
                    }

                    // First fragment of a multi-frame message — begin accumulation.
                    if (Payload.Num() > MaxMessageBytes)
                    {
                        UE_LOG(LogWSServer, Error,
                            TEXT("WSServer: Fragmented message exceeds %d byte limit – dropping client"),
                            MaxMessageBytes);
                        return false;
                    }

                    Client.bInFragment    = true;
                    Client.FragmentOpcode = Opcode;
                    Client.FragmentBuffer = MoveTemp(Payload);
                }
            }
            else // Opcode == 0x0: Continuation frame
            {
                if (!Client.bInFragment)
                {
                    UE_LOG(LogWSServer, Warning,
                        TEXT("WSServer: Received continuation frame with no active fragment – dropping client"));
                    return false;
                }

                // Guard accumulated size before appending.
                // Cast to int64 to prevent int32 wrap-around when both operands
                // are near INT_MAX, which would bypass this check and cause OOM.
                if (static_cast<int64>(Client.FragmentBuffer.Num()) + static_cast<int64>(PayloadLen32) > static_cast<int64>(MaxMessageBytes))
                {
                    UE_LOG(LogWSServer, Error,
                        TEXT("WSServer: Fragmented message exceeds %d byte limit – dropping client"),
                        MaxMessageBytes);
                    return false;
                }

                Client.FragmentBuffer.Append(Payload);

                if (bFin)
                {
                    // Final continuation frame — deliver the reassembled message.
                    if (Client.FragmentOpcode == 0x2)
                    {
                        TArray<uint8> Complete = MoveTemp(Client.FragmentBuffer);
                        TWeakObjectPtr<USMLWebSocketServer> WeakOwner = Owner;
                        const FString CId = ClientId;
                        AsyncTask(ENamedThreads::GameThread, [WeakOwner, CId, Complete = MoveTemp(Complete)]()
                        {
                            if (USMLWebSocketServer* O = WeakOwner.Get())
                                O->Internal_OnClientBinaryMessage(CId, Complete);
                        });
                    }
                    else
                    {
                        TArray<uint8> Complete = MoveTemp(Client.FragmentBuffer);
                        Complete.Add(0);
                        const FString Text = FString(UTF8_TO_TCHAR(reinterpret_cast<const ANSICHAR*>(Complete.GetData())));
                        TWeakObjectPtr<USMLWebSocketServer> WeakOwner = Owner;
                        const FString CId = ClientId;
                        AsyncTask(ENamedThreads::GameThread, [WeakOwner, CId, Text]()
                        {
                            if (USMLWebSocketServer* O = WeakOwner.Get())
                                O->Internal_OnClientMessage(CId, Text);
                        });
                    }

                    Client.bInFragment = false;
                    Client.FragmentBuffer.Reset();
                }
            }
        }
        else
        {
            // Unknown / reserved opcode — RFC 6455 §5.2 requires failing the connection.
            UE_LOG(LogWSServer, Warning,
                TEXT("WSServer: Unknown opcode 0x%02X — dropping client"), Opcode);
            return false;
        }

        Buf.RemoveAt(0, TotalSize);
    }

    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Outbound helpers
// ─────────────────────────────────────────────────────────────────────────────

TArray<uint8> FSMLWebSocketServerRunnable::BuildTextFrame(const FString& Text)
{
    FTCHARToUTF8 UTF8(*Text);
    const int32 PayloadLen = UTF8.Length();

    TArray<uint8> Frame;
    Frame.Add(0x81); // FIN + text opcode

    if (PayloadLen <= 125)
    {
        Frame.Add(static_cast<uint8>(PayloadLen));
    }
    else if (PayloadLen <= 65535)
    {
        Frame.Add(126);
        Frame.Add(static_cast<uint8>(PayloadLen >> 8));
        Frame.Add(static_cast<uint8>(PayloadLen & 0xFF));
    }
    else
    {
        Frame.Add(127);
        for (int32 i = 7; i >= 0; --i)
            Frame.Add(static_cast<uint8>((static_cast<uint64>(PayloadLen) >> (i * 8)) & 0xFF));
    }

    const uint8* Data = reinterpret_cast<const uint8*>(UTF8.Get());
    Frame.Append(Data, PayloadLen);
    return Frame;
}

bool FSMLWebSocketServerRunnable::SendFrame(FSocket* Socket, const TArray<uint8>& Frame)
{
    int32 TotalSent = 0;
    const int32 TotalLen = Frame.Num();
    while (TotalSent < TotalLen)
    {
        int32 Sent = 0;
        if (!Socket->Send(Frame.GetData() + TotalSent, TotalLen - TotalSent, Sent) || Sent <= 0)
            return false;
        TotalSent += Sent;
    }
    return true;
}

void FSMLWebSocketServerRunnable::BroadcastText(const FString& Message)
{
    FOutboundMsg Msg;
    Msg.ClientId = TEXT(""); // empty = broadcast
    Msg.Frame    = BuildTextFrame(Message);
    OutboundQueue.Enqueue(MoveTemp(Msg));
}

void FSMLWebSocketServerRunnable::SendTextToClient(const FString& ClientId, const FString& Message)
{
    FOutboundMsg Msg;
    Msg.ClientId = ClientId;
    Msg.Frame    = BuildTextFrame(Message);
    OutboundQueue.Enqueue(MoveTemp(Msg));
}

void FSMLWebSocketServerRunnable::DisconnectClient(const FString& ClientId)
{
    FClientState Removed;
    {
        FScopeLock L(&ClientMutex);
        if (!Clients.RemoveAndCopyValue(ClientId, Removed))
            return;
    }
    // Do NOT destroy Removed.Socket here.  The I/O thread (Run) may already
    // hold a raw pointer snapshot of this socket taken from Clients during the
    // broadcast-drain loop.  Destroying the socket on this thread while Run()
    // is mid-SendFrame() on the same pointer is a use-after-free.  Instead,
    // hand ownership to SocketsToDestroy so that Run() sends the Close frame
    // and then destroys the socket at the start of the next iteration, by which
    // time all in-flight sends from the current iteration have completed.
    //
    // Build a Close(1000 Normal Closure) frame per RFC 6455 §7.1.1.
    // The I/O thread sends this frame before destroying the TCP socket.
    FPendingCloseSocket Pending;
    Pending.Socket = Removed.Socket;
    Pending.CloseFrame.Add(0x88); // FIN=1, opcode=0x8 (Close)
    Pending.CloseFrame.Add(0x02); // payload length = 2
    Pending.CloseFrame.Add(0x03); // status 1000 high byte
    Pending.CloseFrame.Add(0xE8); // status 1000 low byte
    SocketsToDestroy.Enqueue(MoveTemp(Pending));

    TWeakObjectPtr<USMLWebSocketServer> WeakOwner = Owner;
    AsyncTask(ENamedThreads::GameThread, [WeakOwner, ClientId]()
    {
        if (USMLWebSocketServer* O = WeakOwner.Get())
            O->Internal_OnClientDisconnected(ClientId, TEXT("server disconnected"));
    });
}

int32 FSMLWebSocketServerRunnable::GetClientCount() const
{
    FScopeLock L(const_cast<FCriticalSection*>(&ClientMutex));
    return Clients.Num();
}

TArray<FString> FSMLWebSocketServerRunnable::GetClientIds() const
{
    FScopeLock L(const_cast<FCriticalSection*>(&ClientMutex));
    TArray<FString> Ids;
    Clients.GetKeys(Ids);
    return Ids;
}
