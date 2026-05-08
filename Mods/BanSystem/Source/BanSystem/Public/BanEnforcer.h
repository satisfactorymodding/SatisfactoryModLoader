// Copyright Yamahasxviper. All Rights Reserved.
// Direct port of Tools/BanSystem/src/enforcer.ts
// (PreLogin/PostLogin hooks replace the external DS-API polling loop)

#pragma once

#include "CoreMinimal.h"
#include "Engine/TimerHandle.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BanEnforcer.generated.h"

// Forward declaration to avoid pulling GameFramework/OnlineReplStructs.h into every
// translation unit that includes this header.  The CSS Alpakit server distribution
// does not ship OnlineReplStructs.h through the standalone Engine dep; it is only
// reachable via FactoryGame's transitive Engine include paths.
struct FUniqueNetIdRepl;

class UBanDatabase;

DECLARE_LOG_CATEGORY_EXTERN(LogBanEnforcer, Log, All);

class AGameModeBase;
class APlayerController;
class UWorld;
class UNetConnection;

/**
 * Tracks a player whose PlayerState or platform identity was not yet available
 * at PostLogin time.  Retried every 0.5 s up to MaxAttempts times (~20 s total).
 */
struct FPendingBanCheck
{
    TWeakObjectPtr<APlayerController> Player;
    int32 Attempts = 0;
    static constexpr int32 MaxAttempts = 40; // 40 * 0.5s = 20 s
};

/**
 * UBanEnforcer
 *
 * Enforces bans at player login.  Direct port of the Enforcer class in
 * Tools/BanSystem/src/enforcer.ts, adapted for a UE server-side mod:
 *
 *   Tools/BanSystem approach: external service polls the DS HTTPS API
 *                              every N seconds and kicks banned players.
 *
 *   UE mod approach:          hook PreLogin (fires before the player
 *                              joins) to reject the connection outright
 *                              with the ban reason.  No polling needed.
 *
 * Supports EOS player IDs (the only identity CSS DS assigns).  The compound UID format
 * ("EOS:xxx") matches the database schema exactly.
 */
UCLASS()
class BANSYSTEM_API UBanEnforcer : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    /**
     * Kick any currently-connected player whose compound UID matches.
     *
     * Must be called from the game thread.  Iterates connected
     * PlayerControllers, resolves each player's platform UID (same format
     * as stored in UBanDatabase: "EOS:xxx"), and kicks the
     * first matching player.  First tries AGameSession::KickPlayer, then
     * falls back to closing the UNetConnection directly to handle CSS
     * dedicated-server configurations where the session kick does not fully
     * disconnect the client.  Does NOT call PC->Destroy() — the connection
     * close triggers the standard UE cleanup path.
     *
     * If a player's FUniqueNetIdRepl is not yet populated (CSS DS async
     * identity), the raw player ID embedded in the UID is compared against the
     * PlayerState display name as a best-effort fallback.
     */
    static bool KickConnectedPlayer(UWorld* World, const FString& Uid, const FString& Reason);

    /**
     * CSS DS 1.1.0 workaround: extract the EOS Product User ID from the
     * ClientIdentity URL option embedded in the player's UNetConnection.
     *
     * On CSS dedicated servers running Satisfactory 1.1.0+, EOS V2 PUIDs are
     * used for player authentication, but the server-side EOS online subsystem
     * is offline (IsOnline=false).  As a result FUniqueNetIdRepl::GetType()
     * returns "NONE" and ToString() returns "" for the entire session, making
     * it impossible to retrieve the player identity via PlayerState::GetUniqueId().
     *
     * The EOS PUID is, however, transmitted in the ClientIdentity query
     * parameter of the player's connection URL.  Its binary layout is:
     *   Bytes 0-3  (hex offset  0- 7): LE uint32 header / length
     *   Bytes 4-35 (hex offset  8-71): 32-byte ASCII EOS PUID
     *                                  (each byte is a printable hex char,
     *                                   e.g. '4','8','c','b',... → "48cb...")
     *   Bytes 36+  (hex offset 72+  ): additional platform data (flags, etc.)
     *
     * @param PC  The player controller whose connection URL to inspect.
     * @return    The 32-char lowercase EOS PUID string, or an empty FString if
     *            the option is absent, malformed, or the PUID cannot be decoded.
     */
    static FString ExtractEosPuidFromConnectionUrl(APlayerController* PC);

private:
    /**
     * FGameModeEvents::GameModePostLoginEvent hook — primary ban enforcement
     * path on CSS dedicated servers.
     *
     * CSS's AFGGameMode::Login() routes authentication through
     * UFGDedicatedServerGameModeComponentInterface::PreLogin rather than the
     * standard AGameModeBase::PreLogin, so GameModePreLoginEvent may never
     * fire.  GameModePostLoginEvent is broadcast by AGameModeBase::PostLogin
     * which CSS does call (SML relies on it).
     *
     * If the player's FUniqueNetIdRepl is already valid at PostLogin time
     * (the common case for EOS players on CSS DS), the ban check runs
     * immediately and synchronously.  Otherwise the player is queued for
     * identity polling every 0.5 s up to MaxAttempts ticks (~20 s) while
     * the async Server_RegisterControllerComponent RPC populates the identity.
     */
    void OnPostLogin(AGameModeBase* GameMode, APlayerController* NewPlayer);

    /**
     * Timer callback fired every 0.5 s while there are pending ban checks.
     * For each queued player it checks whether their FUniqueNetIdRepl is now
     * valid.  If so, the ban lookup is performed and the player is kicked if
     * banned.  Players whose identity does not arrive within MaxAttempts ticks
     * (~20 s) are dropped from the queue with a warning.
     */
    void ProcessPendingBanChecks();

    /**
     * Performs the actual ban database lookup and kick for a player whose
     * platform identity has been confirmed valid.  Safe to call from the game
     * thread only.
     */
    void PerformBanCheckForPlayer(UWorld* World, APlayerController* PC, UBanDatabase* DB);

    /**
     * Variant of PerformBanCheckForPlayer that takes a pre-computed compound
     * UID instead of deriving it from PlayerState::GetUniqueId().
     *
     * Used when the identity was extracted from the connection URL
     * (ExtractEosPuidFromConnectionUrl) rather than from the EOS subsystem,
     * e.g. on CSS DS 1.1.0 where GetType() stays "NONE" for the whole session.
     *
     * PC->PlayerState may still be null when this is called.
     */
    void PerformBanCheckForUid(UWorld* World, APlayerController* PC, UBanDatabase* DB, const FString& Uid);

    /**
     * Returns the cached remote IP address for the player's UNetConnection, or
     * an empty string if it was not captured (e.g. the PreLogin hook did not
     * fire for this connection, or the player has already disconnected).
     */
    FString GetCachedIpForPlayer(APlayerController* PC) const;

    /**
     * Returns the cached client version string for the player's UNetConnection,
     * or an empty string if it was not present in the PreLogin Options string or
     * the player has already disconnected.
     */
    FString GetCachedVersionForPlayer(APlayerController* PC) const;

    FDelegateHandle PostLoginHandle;

    /**
     * Subscription to UBanDatabase::OnBanRemoved so that UIDs are evicted from
     * AlreadyNotifiedExpiredBanUids when the underlying ban record is deleted.
     * Without this the set would grow for the entire server session lifetime.
     */
    FDelegateHandle BanRemovedHandle;

    /**
     * Handle for the UFGGameModeDSComponent::PreLogin after-hook installed in
     * Initialize().  Removed in Deinitialize() to prevent stale handlers if the
     * subsystem is ever torn down and re-created.
     */
    FDelegateHandle PreLoginHookHandle;

    /**
     * Handle for the UFGGameModeDSComponent::NotifyPlayerLogout after-hook used
     * to evict stale entries from CachedConnectionPuids when a player disconnects.
     */
    FDelegateHandle PlayerLogoutHookHandle;

    /**
     * EOS PUID cache populated by the PreLogin hook.
     *
     * On CSS DS 1.1.0 (IsOnline=false), UNetConnection::URL on the server side
     * holds the server's bind address, not the client's join URL.  Consequently
     * Conn->URL.GetOption("ClientIdentity=") always returns null.  The ONLY place
     * where the client's Options string (containing ClientIdentity=...) is
     * available is inside UFGGameModeDSComponent::PreLogin.  We extract and cache
     * the decoded EOS PUID here, keyed by the UNetConnection pointer.
     *
     * ExtractEosPuidFromConnectionUrl() checks this map first.
     */
    TMap<TWeakObjectPtr<UNetConnection>, FString> CachedConnectionPuids;

    /**
     * Remote IP address cache populated by the PreLogin hook alongside
     * CachedConnectionPuids.  Keyed by UNetConnection pointer; evicted on
     * player logout.  Looked up in PerformBanCheckForPlayer /
     * PerformBanCheckForUid to pass the IP to UPlayerSessionRegistry::RecordSession().
     */
    TMap<TWeakObjectPtr<UNetConnection>, FString> CachedConnectionIPs;

    /**
     * Client version string cache populated by the PreLogin hook.
     * Extracted from the join Options string (?SMLVersion= or ?version=).
     * Keyed by UNetConnection pointer; evicted on player logout.
     * Passed to UPlayerSessionRegistry::RecordSession() for audit purposes.
     * May be empty when the client does not include a version option.
     */
    TMap<TWeakObjectPtr<UNetConnection>, FString> CachedConnectionVersions;

    /** Players queued for PlayerState / identity polling (CSS async init). */
    TArray<FPendingBanCheck> PendingBanChecks;

    /** Looping 0.5 s timer that drives ProcessPendingBanChecks(). Active only
     *  while PendingBanChecks is non-empty. */
    FTimerHandle PollTimerHandle;

    /** Weak reference to the world the poll timer was registered on.
     *  Kept so Deinitialize() can clear the timer even if GetWorld() is
     *  already null at that point. */
    TWeakObjectPtr<UWorld> PollTimerWorld;

    /**
     * True when UBanEnforcer bound itself to
     * UFGServerSubsystem::CheckHealthCheckCompatibility.
     * Used in Deinitialize() to conditionally call Unbind() — we only unbind
     * if we were the ones who registered, to avoid removing another mod's handler.
     */
    bool bBoundHealthCheck = false;

    /**
     * BanSystem mod version string cached at Initialize() time for use inside
     * the CheckHealthCheckCompatibility lambda (which cannot call UModLoadingLibrary
     * itself without a game-instance reference).
     */
    FString CachedBanSystemModVersion;

    /**
     * UIDs for which NotifyBanExpired has already been fired this server session.
     * Prevents duplicate Discord notifications when both PerformBanCheckForPlayer
     * and PerformBanCheckForUid are triggered for the same player login event.
     * Reset on Deinitialize() (i.e. server shutdown).
     */
    TSet<FString> AlreadyNotifiedExpiredBanUids;

    /**
     * Pending 20-second kick timers keyed by ban UID.
     *
     * When a player is kicked for a ban, ClientWasKicked() is sent immediately
     * but the connection close is deferred by 20 seconds so the player can read
     * the ban message.  Storing the FTimerHandle here (rather than as a transient
     * local) lets the OnBanRemoved handler cancel the pending disconnect if the
     * ban is lifted within the 20-second window — preventing a just-unbanned
     * player from being disconnected anyway.
     */
    TMap<FString, FTimerHandle> PendingKickTimersByUid;
};
