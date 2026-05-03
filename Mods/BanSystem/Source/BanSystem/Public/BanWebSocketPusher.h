// Copyright Yamahasxviper. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Dom/JsonObject.h"
#include "BanWebSocketPusher.generated.h"

class USMLWebSocketClient;

DECLARE_LOG_CATEGORY_EXTERN(LogBanWebSocketPusher, Log, All);

/**
 * UBanWebSocketPusher
 *
 * GameInstance subsystem that maintains a persistent WebSocket connection to
 * WebSocketPushUrl and pushes structured JSON events whenever a ban, unban,
 * warning, or kick occurs.
 *
 * Activated only when bPushEventsToWebSocket=true AND WebSocketPushUrl is
 * non-empty in DefaultBanSystem.ini.
 *
 * Event format:
 *   { "event": "<type>", "timestamp": "<ISO-8601>", ... extra fields ... }
 *
 * Use the static PushEvent() method from anywhere (e.g. FBanDiscordNotifier)
 * to send an event.  The method is a no-op when the subsystem is not active.
 */
UCLASS()
class BANSYSTEM_API UBanWebSocketPusher : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // ── USubsystem lifecycle ─────────────────────────────────────────────────
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    /**
     * Push a JSON event to the configured WebSocket endpoint.
     * Wraps the provided Fields object with a standard envelope
     * ({ "event", "timestamp" }) and calls SendJson on the client.
     *
     * Thread-safe: always dispatches on the game thread.
     * No-op when the subsystem is not active or the client is not connected.
     *
     * @param EventType   Short string identifier, e.g. "ban", "unban", "warn", "kick".
     * @param Fields      Additional JSON fields to merge into the event payload.
     */
    static void PushEvent(const FString& EventType,
                          const TSharedPtr<FJsonObject>& Fields);

    /**
     * Convenience helper called by BanChatCommands to push mute/unmute events.
     * Builds the appropriate Fields object and forwards to PushEvent().
     * No-op when the subsystem is not active.
     *
     * @param EventType   "mute" or "unmute".
     * @param Uid         Compound UID of the affected player.
     * @param PlayerName  Display name (may be empty for unmute events).
     * @param MutedBy     Admin who issued the mute (may be empty for unmute).
     * @param Reason      Reason for the mute (may be empty for unmute).
     * @param bIsTimed    True when the mute has a finite duration.
     * @param ExpiresAt   ISO-8601 expiry timestamp, or empty string if indefinite.
     */
    static void PushMuteEvent(const FString& EventType,
                               const FString& Uid,
                               const FString& PlayerName,
                               const FString& MutedBy,
                               const FString& Reason,
                               bool           bIsTimed,
                               const FString& ExpiresAt);

private:
    /** The WebSocket client connected to WebSocketPushUrl. */
    UPROPERTY()
    TObjectPtr<USMLWebSocketClient> Client = nullptr;

    /** Weak self-reference used by the static PushEvent helper to locate the
     *  subsystem without requiring a UWorld* at the call site. */
    static TWeakObjectPtr<UBanWebSocketPusher> ActiveInstance;
};
