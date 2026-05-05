// Copyright Yamahasxviper. All Rights Reserved.

#pragma once

#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include "HAL/CriticalSection.h"
#include "Containers/Queue.h"
#include "Templates/SharedPointer.h"
#include <atomic>

class FSocket;
class USMLWebSocketServer;

/**
 * FSMLWebSocketServerRunnable
 *
 * Background thread that drives a TCP listener accepting WebSocket connections.
 * Uses FSocket (Unreal's portable socket layer) for the TCP accept loop, then
 * performs a minimal RFC 6455 HTTP upgrade handshake per connection.
 *
 * Each accepted connection is tracked by a unique string ClientId (generated
 * as a simple incrementing counter).  Frame demultiplexing is handled here;
 * text frames are forwarded to the game thread via AsyncTask.
 *
 * Only text frames are supported (binary frames are acknowledged but not forwarded).
 * ws:// only — TLS server mode is not implemented in this version.
 */
class FSMLWebSocketServerRunnable : public FRunnable,
                                     public TSharedFromThis<FSMLWebSocketServerRunnable>
{
public:
    explicit FSMLWebSocketServerRunnable(USMLWebSocketServer* InOwner, int32 InPort,
                                         const FString& InApiToken = FString());
    virtual ~FSMLWebSocketServerRunnable() override;

    // ── FRunnable ─────────────────────────────────────────────────────────────
    virtual bool Init() override;
    virtual uint32 Run() override;
    virtual void Stop() override;
    virtual void Exit() override;

    /** Send a text message to all connected clients. Thread-safe. */
    void BroadcastText(const FString& Message);

    /** Send a text message to one specific client. Thread-safe. */
    void SendTextToClient(const FString& ClientId, const FString& Message);

    /** Disconnect a specific client. Thread-safe. */
    void DisconnectClient(const FString& ClientId);

    /** Returns the number of currently-tracked client connections. */
    int32 GetClientCount() const;

    /** Returns all currently-tracked client IDs. */
    TArray<FString> GetClientIds() const;

private:
    struct FClientState
    {
        FSocket* Socket{nullptr};
        FString  RemoteAddress;
        TArray<uint8> RecvBuffer;
        bool bHandshakeDone{false};

        // RFC 6455 fragmented-message reassembly state.
        // When FIN=0 is received the payload is accumulated here until
        // a continuation frame with FIN=1 completes the message.
        TArray<uint8> FragmentBuffer;
        uint8 FragmentOpcode{0}; // 0x1 = text, 0x2 = binary
        bool  bInFragment{false};

        // Close frame to send before destroying the socket when ProcessFrames
        // returns false due to a received Close frame or a protocol violation.
        // Set inside ProcessFrames (under ClientMutex); consumed and cleared by
        // the ToRemove loop in Run() after the mutex is released.
        TArray<uint8> PendingCloseFrame;
    };

    /** Perform the RFC 6455 HTTP Upgrade handshake for a new connection.
     *  Returns true on success, false on failure (socket should be closed). */
    bool PerformHandshake(FClientState& Client);

    /** Process available data in Client.RecvBuffer; dispatch any complete frames.
     *  Returns false when the client sends a Close frame or a read error occurs. */
    bool ProcessFrames(const FString& ClientId, FClientState& Client);

    /** Build a masked/unmasked WebSocket text frame. */
    static TArray<uint8> BuildTextFrame(const FString& Text);

    /** Send all bytes of a frame to the given socket. */
    static bool SendFrame(FSocket* Socket, const TArray<uint8>& Frame);

    TWeakObjectPtr<USMLWebSocketServer> Owner;
    int32 ListenPort{0};
    FString ApiToken;
    std::atomic<bool> bStopping{false};

    FSocket* ListenSocket{nullptr};

    mutable FCriticalSection ClientMutex;
    TMap<FString, FClientState> Clients;

    /** Outbound messages queued for specific clients: (ClientId, Frame). */
    struct FOutboundMsg
    {
        FString ClientId; // empty = broadcast
        TArray<uint8> Frame;
    };
    TQueue<FOutboundMsg, EQueueMode::Mpsc> OutboundQueue;

    /**
     * Sockets that have been removed from Clients by DisconnectClient() and are
     * waiting to have a Close frame sent and then be destroyed by the I/O thread.
     * DisconnectClient() must NOT destroy the socket directly because the I/O
     * thread may already hold a raw FSocket* snapshot taken from Clients during
     * the broadcast-drain loop.  Destroying the socket on the game thread while
     * the I/O thread is mid-SendFrame() on that same pointer is a use-after-free.
     *
     * Each entry carries a pre-built Close frame so the I/O thread can fulfil the
     * RFC 6455 §7.1.1 closing handshake (send Close frame) before tearing down the
     * TCP connection.
     *
     * Ownership: game thread enqueues; I/O thread (Run) dequeues and processes at
     * the start of each loop iteration and once more after shutdown cleanup,
     * ensuring all in-flight sends have completed first.
     */
    struct FPendingCloseSocket
    {
        FSocket*      Socket{nullptr};
        TArray<uint8> CloseFrame;
    };
    TQueue<FPendingCloseSocket, EQueueMode::Mpsc> SocketsToDestroy;

    static std::atomic<uint64> NextClientId;
};
