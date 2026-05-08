// Copyright Yamahasxviper. All Rights Reserved.
// Direct port of Tools/BanSystem/src/enforcer.ts

#include "BanEnforcer.h"
#include "BanDatabase.h"
#include "BanDiscordNotifier.h"
#include "BanSystemConfig.h"
#include "PlayerSessionRegistry.h"
#include "ModLoading/ModLoadingLibrary.h"
#include "FGServerSubsystem.h"

#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

// Pull in the full FUniqueNetIdRepl definition that was forward-declared in the header.
#include "GameFramework/OnlineReplStructs.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Engine/NetConnection.h"
#include "TimerManager.h"
// CSS dedicated-server component hooked to capture client login Options before
// UNetConnection::URL is overwritten with the server bind address.
#include "FGGameModeDSComponent.h"
// SML native hook macros used for the PreLogin / NotifyPlayerLogout hooks.
#include "Patching/NativeHookManager.h"

DEFINE_LOG_CATEGORY(LogBanEnforcer);

// ─────────────────────────────────────────────────────────────────────────────
//  USubsystem lifecycle
// ─────────────────────────────────────────────────────────────────────────────

void UBanEnforcer::Initialize(FSubsystemCollectionBase& Collection)
{
    Collection.InitializeDependency<UBanDatabase>();
    Collection.InitializeDependency<UPlayerSessionRegistry>();
    Super::Initialize(Collection);

    // Primary enforcement hook — AGameModeBase::PostLogin broadcasts this event
    // and CSS (confirmed by SML) calls it on every player join.
    // Note: CSS routes PreLogin through UFGDedicatedServerGameModeComponentInterface
    // rather than AGameModeBase::PreLogin, so FGameModeEvents::GameModePreLoginEvent
    // does not fire on CSS dedicated servers and is not hooked here.
    // Use AddLambda + TWeakObjectPtr instead of AddUObject to avoid C2665 in
    // CSS 5.3's strict template matching while still handling object lifetime safely.
    TWeakObjectPtr<UBanEnforcer> WeakThis(this);
    PostLoginHandle = FGameModeEvents::GameModePostLoginEvent.AddLambda(
        [WeakThis](AGameModeBase* GameMode, APlayerController* NewPlayer)
        {
            if (UBanEnforcer* Enforcer = WeakThis.Get())
                Enforcer->OnPostLogin(GameMode, NewPlayer);
        });

    // ─────────────────────────────────────────────────────────────────────────
    // PreLogin hook — capture the EOS PUID from the client Options string.
    //
    // Root cause of the "gave up waiting for EOS PUID" / "/whoami UNCOMPLETED"
    // bug:  On CSS DS 1.1.0, UNetConnection::URL is initialised from the
    // server's bind address, NOT from the client's join URL.  So
    // Conn->URL.GetOption("ClientIdentity=") always returns null, and
    // ExtractEosPuidFromConnectionUrl silently returns empty every time.
    //
    // UFGGameModeDSComponent::PreLogin IS called with the full Options string
    // (same string logged as "Login request: ?ClientIdentity=...").  We hook it
    // here with SUBSCRIBE_UOBJECT_METHOD_AFTER to extract and cache the decoded
    // EOS PUID, keyed by UNetConnection, before PostLogin fires.
    // ─────────────────────────────────────────────────────────────────────────
    PreLoginHookHandle = SUBSCRIBE_UOBJECT_METHOD_AFTER(UFGGameModeDSComponent, PreLogin,
        ([WeakThis](const bool& bLoginAllowed,
                    UFGGameModeDSComponent* /*Self*/,
                    UPlayer* NewPlayer,
                    const FString& Options,
                    const FUniqueNetIdRepl& /*UniqueId*/,
                    FString& /*ErrorMessage*/,
                    TSharedPtr<FDedicatedServerGameModeComponentPreLoginDataInterface>& /*OutPreLoginData*/)
        {
            // Only cache for accepted logins.
            if (!bLoginAllowed) return;

            UBanEnforcer* Enforcer = WeakThis.Get();
            if (!Enforcer) return;

            UNetConnection* Conn = Cast<UNetConnection>(NewPlayer);
            if (!Conn) return;

            // Options format: "?ClientIdentity=<hex>?EntryTicket=...?Name=..."
            // Extract the hex blob from between "ClientIdentity=" and the next "?".
            const FString ClientIdentityKey = TEXT("ClientIdentity=");
            int32 KeyIdx = Options.Find(ClientIdentityKey, ESearchCase::IgnoreCase);
            if (KeyIdx == INDEX_NONE) return;

            FString HexStr = Options.Mid(KeyIdx + ClientIdentityKey.Len());
            int32 EndIdx;
            if (HexStr.FindChar(TEXT('?'), EndIdx))
                HexStr = HexStr.Left(EndIdx);
            HexStr.TrimStartAndEndInline();

            // Decode EOS PUID from the binary blob encoded as a lowercase hex string.
            // Layout: offsets 0-7 = 4-byte LE header; offsets 8-71 = 32 ASCII PUID bytes.
            if (HexStr.Len() < 72) return;

            FString Puid;
            Puid.Reserve(32);
            for (int32 i = 8; i < 72; i += 2)
            {
                const TCHAR Hi = FChar::ToLower(HexStr[i]);
                const TCHAR Lo = FChar::ToLower(HexStr[i + 1]);
                if (!FChar::IsHexDigit(Hi) || !FChar::IsHexDigit(Lo)) return;

                const uint8 HiN = (Hi >= TEXT('a')) ? (uint8)(Hi - TEXT('a') + 10) : (uint8)(Hi - TEXT('0'));
                const uint8 LoN = (Lo >= TEXT('a')) ? (uint8)(Lo - TEXT('a') + 10) : (uint8)(Lo - TEXT('0'));
                const TCHAR Ch = static_cast<TCHAR>((HiN << 4) | LoN);
                // Each decoded byte must itself be a hex-digit ASCII character
                // (0x30–0x39 or 0x61–0x66 after ToLower).  If it is not, the
                // blob is malformed — discard it rather than caching a garbage
                // PUID that would silently fail every ban lookup.
                if (!FChar::IsHexDigit(Ch)) return;
                Puid.AppendChar(Ch);
            }
            if (Puid.Len() != 32) return;
            Puid = Puid.ToLower();

            Enforcer->CachedConnectionPuids.Add(TWeakObjectPtr<UNetConnection>(Conn), Puid);
            UE_LOG(LogBanEnforcer, Log,
                TEXT("BanEnforcer: cached EOS PUID %s for incoming connection (via PreLogin Options)"),
                *Puid);

            // Also cache the remote IP address while the connection object is
            // available in the PreLogin callback.
            const FString RemoteIp = Conn->LowLevelGetRemoteAddress(/*bAppendPort=*/false);
            if (!RemoteIp.IsEmpty())
            {
                Enforcer->CachedConnectionIPs.Add(TWeakObjectPtr<UNetConnection>(Conn), RemoteIp);
                UE_LOG(LogBanEnforcer, Log,
                    TEXT("BanEnforcer: cached remote IP %s for incoming connection"),
                    *RemoteIp);
            }

            // Capture the client version string from the Options URL if present.
            // Standard UE clients include ?version=<buildid>; CSS/SML may add
            // ?SMLVersion=.  If absent the field stays empty (backward compat).
            auto ExtractOption = [&Options](const FString& Key) -> FString
            {
                int32 OptIdx = Options.Find(Key, ESearchCase::IgnoreCase);
                if (OptIdx == INDEX_NONE) return FString();
                FString Val = Options.Mid(OptIdx + Key.Len());
                int32 Sep;
                if (Val.FindChar(TEXT('?'), Sep))
                    Val = Val.Left(Sep);
                Val.TrimStartAndEndInline();
                return Val;
            };

            FString ClientVersion = ExtractOption(TEXT("SMLVersion="));
            if (ClientVersion.IsEmpty())
                ClientVersion = ExtractOption(TEXT("version="));
            if (!ClientVersion.IsEmpty())
            {
                Enforcer->CachedConnectionVersions.Add(
                    TWeakObjectPtr<UNetConnection>(Conn), ClientVersion);
                UE_LOG(LogBanEnforcer, Log,
                    TEXT("BanEnforcer: cached client version '%s' for incoming connection"),
                    *ClientVersion);
            }
        }));

    // Evict cache entries when the player's connection is torn down.
    PlayerLogoutHookHandle = SUBSCRIBE_UOBJECT_METHOD_AFTER(UFGGameModeDSComponent, NotifyPlayerLogout,
        ([WeakThis](UFGGameModeDSComponent* /*Self*/, AController* ExitingController)
        {
            UBanEnforcer* Enforcer = WeakThis.Get();
            if (!Enforcer) return;

            if (UNetConnection* Conn = Cast<UNetConnection>(
                    ExitingController ? ExitingController->GetNetConnection() : nullptr))
            {
                const int32 Removed = Enforcer->CachedConnectionPuids.Remove(TWeakObjectPtr<UNetConnection>(Conn));
                if (Removed > 0)
                    UE_LOG(LogBanEnforcer, Log,
                        TEXT("BanEnforcer: evicted cached EOS PUID on player logout"));
                Enforcer->CachedConnectionIPs.Remove(TWeakObjectPtr<UNetConnection>(Conn));
                Enforcer->CachedConnectionVersions.Remove(TWeakObjectPtr<UNetConnection>(Conn));
            }

            // Also prune any fully garbage-collected (stale) entries.
            for (auto It = Enforcer->CachedConnectionPuids.CreateIterator(); It; ++It)
            {
                if (!It.Key().IsValid())
                    It.RemoveCurrent();
            }
            for (auto It = Enforcer->CachedConnectionIPs.CreateIterator(); It; ++It)
            {
                if (!It.Key().IsValid())
                    It.RemoveCurrent();
            }
            for (auto It = Enforcer->CachedConnectionVersions.CreateIterator(); It; ++It)
            {
                if (!It.Key().IsValid())
                    It.RemoveCurrent();
            }
        }));

    UE_LOG(LogBanEnforcer, Log, TEXT("BanEnforcer: login enforcement active (PostLogin)"));

    // Cache the BanSystem mod version string before binding the health-check
    // lambda so that the version is available immediately when the delegate
    // fires (avoids an empty version string if the health check fires before
    // the code below can run in the same tick).
    if (UGameInstance* GI2 = GetGameInstance())
    {
        if (UModLoadingLibrary* ModLib = GI2->GetSubsystem<UModLoadingLibrary>())
        {
            FModInfo ModInfo;
            if (ModLib->GetLoadedModInfo(TEXT("BanSystem"), ModInfo))
                CachedBanSystemModVersion = ModInfo.Version.ToString();
        }
    }

    // The server health-check response includes BanSystem status information.
    // This lets the CSS server browser / health-check clients surface ban-system
    // health alongside standard game metrics (completely additive, zero risk).
    //
    // We only bind when the delegate is currently unbound to avoid overwriting a
    // handler registered by another mod.  Single-bind delegates support at most
    // one handler; prefer binding early at subsystem init time.
    if (UGameInstance* GI = GetGameInstance())
    {
        if (UFGServerSubsystem* FGSub = GI->GetSubsystem<UFGServerSubsystem>())
        {
            if (!FGSub->CheckHealthCheckCompatibility.IsBound())
            {
                bBoundHealthCheck = true;
                TWeakObjectPtr<UBanEnforcer> WeakThisHealth(this);
                FGSub->CheckHealthCheckCompatibility.BindLambda(
                    [WeakThisHealth](const FString& /*ClientCustomData*/, FString& OutServerCustomData)
                        -> FFGServerErrorResponse
                    {
                        UBanEnforcer* Enforcer = WeakThisHealth.Get();
                        if (Enforcer)
                        {
                            // Append BanSystem status fields to OutServerCustomData.
                            // Use a simple key=value format so other fields already
                            // written by CSS are not disturbed.
                            UGameInstance* GI2 = Enforcer->GetGameInstance();
                            int32 ActiveBanCount = 0;
                            if (GI2)
                            {
                                if (UBanDatabase* DB = GI2->GetSubsystem<UBanDatabase>())
                                    ActiveBanCount = DB->GetActiveBans().Num();
                            }
                            if (!OutServerCustomData.IsEmpty())
                                OutServerCustomData += TEXT(",");
                            OutServerCustomData += FString::Printf(
                                TEXT("banSystemActiveBans=%d,banSystemModVersion=%s"),
                                ActiveBanCount, *Enforcer->CachedBanSystemModVersion);
                        }
                        return FFGServerErrorResponse::Ok();
                    });
                UE_LOG(LogBanEnforcer, Log,
                    TEXT("BanEnforcer: bound to UFGServerSubsystem::CheckHealthCheckCompatibility"));
            }
            else
            {
                UE_LOG(LogBanEnforcer, Log,
                    TEXT("BanEnforcer: CheckHealthCheckCompatibility already bound — health-check integration skipped to avoid conflict"));
            }
        }
    }

    // Subscribe to ban-removal events so AlreadyNotifiedExpiredBanUids does not
    // grow unboundedly.  When a ban record is deleted (manually, via REST API, or
    // by expiry pruning) the corresponding UID is evicted from the dedup set so
    // that a future re-ban + expiry cycle will still trigger a notification.
    // Also cancel any pending 20-second kick timer for the removed UID so that
    // a player who was just unbanned is not disconnected anyway.
    TWeakObjectPtr<UBanEnforcer> WeakThisBR(this);
    BanRemovedHandle = UBanDatabase::OnBanRemoved.AddLambda(
        [WeakThisBR](const FString& Uid, const FString& /*PlayerName*/)
        {
            UBanEnforcer* Enforcer = WeakThisBR.Get();
            if (!Enforcer) return;

            Enforcer->AlreadyNotifiedExpiredBanUids.Remove(Uid);

            // Cancel the pending disconnect timer (if any) for this UID so a
            // player unbanned within the 20-second kick-message window is not
            // disconnected after the ban is lifted.
            if (FTimerHandle* Handle = Enforcer->PendingKickTimersByUid.Find(Uid))
            {
                if (UGameInstance* GI = Enforcer->GetGameInstance())
                {
                    if (UWorld* World = GI->GetWorld())
                        World->GetTimerManager().ClearTimer(*Handle);
                }
                Enforcer->PendingKickTimersByUid.Remove(Uid);
                UE_LOG(LogBanEnforcer, Log,
                    TEXT("BanEnforcer: cancelled pending kick timer for unbanned UID %s"), *Uid);
            }
        });
}

void UBanEnforcer::Deinitialize()
{
    FGameModeEvents::GameModePostLoginEvent.Remove(PostLoginHandle);
    PostLoginHandle.Reset();

    // Unsubscribe from ban-removal notifications.
    if (BanRemovedHandle.IsValid())
    {
        UBanDatabase::OnBanRemoved.Remove(BanRemovedHandle);
        BanRemovedHandle.Reset();
    }

    // Remove the PreLogin / NotifyPlayerLogout SML hooks.
    UNSUBSCRIBE_UOBJECT_METHOD(UFGGameModeDSComponent, PreLogin, PreLoginHookHandle);
    PreLoginHookHandle.Reset();
    UNSUBSCRIBE_UOBJECT_METHOD(UFGGameModeDSComponent, NotifyPlayerLogout, PlayerLogoutHookHandle);
    PlayerLogoutHookHandle.Reset();

    // Unbind the health-check delegate if we were the ones who bound it.
    if (bBoundHealthCheck)
    {
        if (UGameInstance* GI = GetGameInstance())
        {
            if (UFGServerSubsystem* FGSub = GI->GetSubsystem<UFGServerSubsystem>())
                FGSub->CheckHealthCheckCompatibility.Unbind();
        }
        bBoundHealthCheck = false;
    }

    // Clear the EOS PUID cache.
    CachedConnectionPuids.Empty();
    CachedConnectionIPs.Empty();
    CachedConnectionVersions.Empty();

    // Cancel and clear all pending kick timers.
    // Use the stored world reference (GetGameInstance()->GetWorld() may already
    // be null at this point) to reach the timer manager and invalidate each
    // handle before emptying the map.  Without the ClearTimer calls the
    // underlying FTimerManager callbacks remain registered and will fire after
    // Deinitialize returns, closing connections that should stay open.
    if (UWorld* World = PollTimerWorld.Get())
    {
        for (auto& KickPair : PendingKickTimersByUid)
            World->GetTimerManager().ClearTimer(KickPair.Value);
    }
    PendingKickTimersByUid.Empty();

    // Cancel any in-flight identity poll and clear the queue.
    PendingBanChecks.Empty();

    // Use the stored world reference because GetGameInstance()->GetWorld() may
    // already return null by the time Deinitialize() is called on shutdown.
    if (UWorld* World = PollTimerWorld.Get())
        World->GetTimerManager().ClearTimer(PollTimerHandle);
    PollTimerWorld.Reset();

    Super::Deinitialize();
}

// ─────────────────────────────────────────────────────────────────────────────
//  PostLogin enforcement (primary path on CSS dedicated servers)
// ─────────────────────────────────────────────────────────────────────────────

void UBanEnforcer::OnPostLogin(AGameModeBase* GameMode, APlayerController* NewPlayer)
{
    if (!GameMode || !NewPlayer) return;

    UGameInstance* GI = GetGameInstance();
    if (!GI) return;

    UBanDatabase* DB = GI->GetSubsystem<UBanDatabase>();
    if (!DB)
    {
        UE_LOG(LogBanEnforcer, Error,
            TEXT("BanEnforcer: OnPostLogin — UBanDatabase subsystem unavailable, skipping ban check"));
        return;
    }

    UWorld* World = GI->GetWorld();
    if (!World) return;

    // Attempt an immediate ban check when PlayerState and identity are ready.
    // On CSS dedicated servers APlayerState::UniqueId is typically set during
    // AGameModeBase::Login() so this fast path fires for most EOS players.
    if (NewPlayer->PlayerState)
    {
        const FUniqueNetIdRepl& NetIdAtLogin = NewPlayer->PlayerState->GetUniqueId();
        if (NetIdAtLogin.IsValid() && NetIdAtLogin.GetType() != FName(TEXT("NONE")))
        {
            // Defer the kick one tick so CSS's own PostLogin code can finish
            // before the connection is closed.  Closing synchronously inside the
            // PostLogin event can crash if AFGGameMode::PostLogin() runs more
            // setup code after Super::PostLogin() returns.
            TWeakObjectPtr<UBanEnforcer> WeakThis(this);
            TWeakObjectPtr<APlayerController> WeakPC(NewPlayer);
            World->GetTimerManager().SetTimerForNextTick(
                FTimerDelegate::CreateLambda([WeakThis, WeakPC]()
                {
                    UBanEnforcer* Enforcer = WeakThis.Get();
                    APlayerController* PC  = WeakPC.Get();
                    if (!Enforcer || !IsValid(PC)) return;

                    UGameInstance* GI2 = Enforcer->GetGameInstance();
                    if (!GI2) return;
                    UWorld* W2 = GI2->GetWorld();
                    UBanDatabase* DB2 = GI2->GetSubsystem<UBanDatabase>();
                    if (W2 && DB2)
                        Enforcer->PerformBanCheckForPlayer(W2, PC, DB2);
                }));
            return;
        }
    }

    // CSS DS 1.1.0 workaround: GetType()==NONE because EOS online subsystem is
    // offline (IsOnline=false).  The EOS PUID is still transmitted in the
    // ClientIdentity URL option — try to extract it directly from the connection.
    {
        const FString EosPuid = ExtractEosPuidFromConnectionUrl(NewPlayer);
        if (!EosPuid.IsEmpty())
        {
            const FString Uid = UBanDatabase::MakeUid(TEXT("EOS"), EosPuid);
            const FString PlayerName = (NewPlayer->PlayerState)
                ? NewPlayer->PlayerState->GetPlayerName()
                : TEXT("(unknown)");

            UE_LOG(LogBanEnforcer, Log,
                TEXT("BanEnforcer: extracted EOS PUID from connection URL for '%s' (%s) — deferred ban check"),
                *PlayerName, *Uid);

            TWeakObjectPtr<UBanEnforcer> WeakThis(this);
            TWeakObjectPtr<APlayerController> WeakPC(NewPlayer);
            World->GetTimerManager().SetTimerForNextTick(
                FTimerDelegate::CreateLambda([WeakThis, WeakPC, Uid]()
                {
                    UBanEnforcer* Enforcer = WeakThis.Get();
                    APlayerController* PC  = WeakPC.Get();
                    if (!Enforcer || !IsValid(PC)) return;

                    UGameInstance* GI2 = Enforcer->GetGameInstance();
                    if (!GI2) return;
                    UWorld* W2 = GI2->GetWorld();
                    UBanDatabase* DB2 = GI2->GetSubsystem<UBanDatabase>();
                    if (W2 && DB2)
                        Enforcer->PerformBanCheckForUid(W2, PC, DB2, Uid);
                }));
            return;
        }
    }

    // PlayerState is null OR identity not yet available AND no URL PUID found.
    // CSS may initialise PlayerState asynchronously after PostLogin fires.
    // Queue the player and poll every 0.5 s until both PlayerState and identity
    // are available.
    PendingBanChecks.Add({NewPlayer, 0});

    if (!World->GetTimerManager().IsTimerActive(PollTimerHandle))
    {
        PollTimerWorld = World;
        World->GetTimerManager().SetTimer(
            PollTimerHandle,
            FTimerDelegate::CreateUObject(this, &UBanEnforcer::ProcessPendingBanChecks),
            0.5f,
            /*bLoop=*/true);

        UE_LOG(LogBanEnforcer, Log,
            TEXT("BanEnforcer: started identity-poll timer for pending ban checks"));
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  Identity poll timer  (fires every 0.5 s while there are pending checks)
// ─────────────────────────────────────────────────────────────────────────────

void UBanEnforcer::ProcessPendingBanChecks()
{
    UGameInstance* GI = GetGameInstance();
    if (!GI) return;

    UWorld* World = GI->GetWorld();
    if (!World) return;

    UBanDatabase* DB = GI->GetSubsystem<UBanDatabase>();
    if (!DB) return;

    // Iterate backwards so we can safely RemoveAt while iterating.
    for (int32 i = PendingBanChecks.Num() - 1; i >= 0; --i)
    {
        FPendingBanCheck& Check = PendingBanChecks[i];
        APlayerController* PC = Check.Player.Get();

        // Player already disconnected.
        if (!IsValid(PC))
        {
            PendingBanChecks.RemoveAt(i);
            continue;
        }

        // PlayerState not yet available — CSS may initialise it asynchronously
        // after PostLogin.  Treat this the same as an unresolved identity: burn
        // one attempt and keep the player in the queue.
        if (!PC->PlayerState)
        {
            if (++Check.Attempts >= FPendingBanCheck::MaxAttempts)
            {
                UE_LOG(LogBanEnforcer, Warning,
                    TEXT("BanEnforcer: gave up waiting for PlayerState for player after %d attempts (~%.0f s)"),
                    FPendingBanCheck::MaxAttempts,
                    FPendingBanCheck::MaxAttempts * 0.5f);
                PendingBanChecks.RemoveAt(i);
            }
            // else: PlayerState not ready yet — keep queued, retry next tick.
            continue;
        }

        const FUniqueNetIdRepl& NetId = PC->PlayerState->GetUniqueId();
        if (!NetId.IsValid() || NetId.GetType() == FName(TEXT("NONE")))
        {
            // CSS DS 1.1.0 workaround: identity stays NONE when EOS subsystem is
            // offline.  Try extracting the EOS PUID from the connection URL before
            // burning another attempt (the PUID is baked into ClientIdentity and
            // doesn't change, so a single successful decode is enough).
            const FString EosPuid = ExtractEosPuidFromConnectionUrl(PC);
            if (!EosPuid.IsEmpty())
            {
                const FString Uid = UBanDatabase::MakeUid(TEXT("EOS"), EosPuid);
                PendingBanChecks.RemoveAt(i);
                PerformBanCheckForUid(World, PC, DB, Uid);
                continue;
            }

            if (++Check.Attempts >= FPendingBanCheck::MaxAttempts)
            {
                UE_LOG(LogBanEnforcer, Warning,
                    TEXT("BanEnforcer: gave up waiting for UniqueId (or NONE-type EOS PUID) for player '%s' after %d attempts (~%.0f s)"),
                    *PC->PlayerState->GetPlayerName(),
                    FPendingBanCheck::MaxAttempts,
                    FPendingBanCheck::MaxAttempts * 0.5f);
                PendingBanChecks.RemoveAt(i);
            }
            // else: identity not ready yet or still NONE type — keep queued, retry next tick.
            continue;
        }

        // Identity is now valid — run the ban check and remove from queue.
        PendingBanChecks.RemoveAt(i);
        PerformBanCheckForPlayer(World, PC, DB);
    }

    // Stop the poll timer when the queue is drained to avoid unnecessary work.
    if (PendingBanChecks.IsEmpty())
    {
        World->GetTimerManager().ClearTimer(PollTimerHandle);
        PollTimerWorld.Reset();
        UE_LOG(LogBanEnforcer, Log,
            TEXT("BanEnforcer: identity-poll timer stopped (queue empty)"));
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  Ban lookup + kick for a player whose identity has been confirmed valid
// ─────────────────────────────────────────────────────────────────────────────

void UBanEnforcer::PerformBanCheckForPlayer(UWorld* World, APlayerController* PC, UBanDatabase* DB)
{
    if (!World || !IsValid(PC) || !DB || !PC->PlayerState) return;

    // Refresh the in-memory ban list from disk in case an admin manually edited
    // bans.json (e.g. to remove a ban) without going through the REST API or
    // chat commands.  This is a no-op when the file has not changed.
    DB->ReloadIfChanged();

    const FUniqueNetIdRepl& NetId = PC->PlayerState->GetUniqueId();
    if (!NetId.IsValid()) return;

    // Use the direct FUniqueNetIdRepl accessors (GetType/ToString on the repl
    // struct itself) instead of dereferencing through operator->. On CSS dedicated
    // servers, EOS V2 (PUID) identities do not use the TSharedPtr<FUniqueNetId>
    // storage path — the inner pointer slot holds a raw EOS handle value, not a
    // valid C++ object, so calling NetId->GetType() causes a SIGSEGV.
    // FUniqueNetIdRepl::GetType() and FUniqueNetIdRepl::ToString() are safe for
    // EOS PUID (V2) identities.
    const FString Platform = NetId.GetType().ToString().ToUpper();
    // Guard against an unresolved EOS identity: on CSS DS, FUniqueNetIdRepl::IsValid()
    // can return true before the EOS PUID provider has been assigned, leaving GetType()
    // as "NONE" and ToString() as "".  Recording or enforcing a "NONE:" UID is wrong.
    if (Platform == TEXT("NONE"))
    {
        UE_LOG(LogBanEnforcer, Warning,
            TEXT("BanEnforcer: PerformBanCheckForPlayer — identity type is NONE for player '%s', skipping (EOS PUID not yet resolved)"),
            *PC->PlayerState->GetPlayerName());
        return;
    }
    // Normalize to lowercase so UIDs match bans stored by chat commands
    // (which also lowercase EOS PUIDs via the /ban and /tempban resolution paths).
    const FString RawId    = NetId.ToString().ToLower();
    const FString Uid      = UBanDatabase::MakeUid(Platform, RawId);

    UE_LOG(LogBanEnforcer, Log,
        TEXT("BanEnforcer: checking ban status for player '%s' (%s: %s)"),
        *PC->PlayerState->GetPlayerName(), *Platform, *RawId);

    FBanEntry Entry;
    if (!DB->IsCurrentlyBannedByAnyId(Uid, Entry))
    {
        // Check whether the player had a temporary ban that just expired and,
        // if configured, post a Discord notification so admins are aware.
        // AlreadyNotifiedExpiredBanUids deduplicates notifications when both
        // PerformBanCheckForPlayer and PerformBanCheckForUid run for the same login.
        {
            FBanEntry ExpiredEntry;
            if (DB->GetBanByUid(Uid, ExpiredEntry) && !ExpiredEntry.bIsPermanent && ExpiredEntry.IsExpired())
            {
                if (!AlreadyNotifiedExpiredBanUids.Contains(Uid))
                {
                    AlreadyNotifiedExpiredBanUids.Add(Uid);
                    FBanDiscordNotifier::NotifyBanExpired(ExpiredEntry);
                }
            }
        }
        const FString CachedIp = GetCachedIpForPlayer(PC);
        if (!CachedIp.IsEmpty())
        {
            const FString IpUid = UBanDatabase::MakeUid(TEXT("IP"), CachedIp);
            FBanEntry IpEntry;
            if (DB->IsCurrentlyBannedByAnyId(IpUid, IpEntry))
            {
                const FString KickMsg = IpEntry.GetKickMessage();
                UE_LOG(LogBanEnforcer, Log,
                    TEXT("BanEnforcer: kicking IP-banned player '%s' (IP: %s) — %s"),
                    *PC->PlayerState->GetPlayerName(), *CachedIp, *KickMsg);

                if (IsValid(PC))
                {
                    PC->ClientWasKicked(FText::FromString(KickMsg));
                    TWeakObjectPtr<APlayerController> WeakPC(PC);
                    TWeakObjectPtr<UBanEnforcer> WeakEnforcer(this);
                    // Store the handle in PendingKickTimersByUid so OnBanRemoved can
                    // cancel the disconnect if the ban is lifted within 20 seconds.
                    const FString BanUid = IpEntry.Uid;
                    FTimerHandle& KickTimerHandle = PendingKickTimersByUid.FindOrAdd(BanUid);
                    World->GetTimerManager().SetTimer(KickTimerHandle,
                        FTimerDelegate::CreateLambda([WeakPC, WeakEnforcer, BanUid]()
                        {
                            if (UBanEnforcer* E = WeakEnforcer.Get())
                                E->PendingKickTimersByUid.Remove(BanUid);
                            APlayerController* PCToKick = WeakPC.Get();
                            if (!IsValid(PCToKick)) return;
                            if (UNetConnection* Conn = Cast<UNetConnection>(PCToKick->Player))
                                Conn->Close();
                        }), 20.0f, false);
                }
                return;
            }
        }

        UE_LOG(LogBanEnforcer, Log,
            TEXT("BanEnforcer: player '%s' (%s) is not banned — allowing join"),
            *PC->PlayerState->GetPlayerName(), *Uid);

        // Record the session for identity-persistence tracking (Gap 4).
        // This lets admins use /playerhistory to audit which UIDs a player
        // has connected with across server sessions.
        UGameInstance* GI = GetGameInstance();
        if (GI)
        {
            if (UPlayerSessionRegistry* Registry = GI->GetSubsystem<UPlayerSessionRegistry>())
                Registry->RecordSession(Uid, PC->PlayerState->GetPlayerName(),
                                        GetCachedIpForPlayer(PC),
                                        GetCachedVersionForPlayer(PC));
        }

        // Geo-IP check (async, config-gated).
        // Kick players from blocked/non-allowed regions without auto-banning.
        {
            const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
            if (Cfg && Cfg->bGeoIpEnabled && !Cfg->GeoIpApiUrl.IsEmpty())
            {
                const FString PlayerName = PC->PlayerState->GetPlayerName();
                const FString IpAddress  = GetCachedIpForPlayer(PC);
                if (!IpAddress.IsEmpty() && FModuleManager::Get().IsModuleLoaded(TEXT("HTTP")))
                {
                    FString ApiUrl = Cfg->GeoIpApiUrl;
                    ApiUrl = ApiUrl.Replace(TEXT("{ip}"), *IpAddress, ESearchCase::IgnoreCase);

                    const TArray<FString> Allowed = Cfg->AllowedCountryCodes;
                    const TArray<FString> Blocked = Cfg->BlockedCountryCodes;
                    const FString KickMsg = Cfg->GeoIpKickMessage.IsEmpty()
                        ? TEXT("You are not permitted to join this server from your region.")
                        : Cfg->GeoIpKickMessage;

                    TWeakObjectPtr<APlayerController> WeakPC(PC);
                    const FString CapturedUid = Uid;

                    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> GeoReq =
                        FHttpModule::Get().CreateRequest();
                    GeoReq->SetURL(ApiUrl);
                    GeoReq->SetVerb(TEXT("GET"));
                    GeoReq->OnProcessRequestComplete().BindLambda(
                        [WeakPC, PlayerName, IpAddress, CapturedUid,
                         Allowed, Blocked, KickMsg]
                        (FHttpRequestPtr /*Req*/, FHttpResponsePtr Resp, bool bSuccess)
                        {
                            if (!bSuccess || !Resp.IsValid()) return;
                            // Treat non-2xx responses (rate-limits, errors, etc.) as
                            // "no data" rather than silently acting on a stale/error body.
                            const int32 Code = Resp->GetResponseCode();
                            if (Code < 200 || Code >= 300) return;

                            TSharedPtr<FJsonObject> Root;
                            TSharedRef<TJsonReader<>> Reader =
                                TJsonReaderFactory<>::Create(Resp->GetContentAsString());
                            if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid()) return;

                            FString CountryCode;
                            Root->TryGetStringField(TEXT("countryCode"), CountryCode);
                            CountryCode = CountryCode.ToUpper();
                            if (CountryCode.IsEmpty()) return;

                            // Determine whether to block.
                            bool bBlock = false;
                            if (Allowed.Num() > 0)
                                bBlock = !Allowed.ContainsByPredicate([&CountryCode](const FString& C){ return C.ToUpper() == CountryCode; });
                            else if (Blocked.Num() > 0)
                                bBlock = Blocked.ContainsByPredicate([&CountryCode](const FString& C){ return C.ToUpper() == CountryCode; });

                            if (!bBlock) return;

                            const FString FinalMsg = KickMsg.Replace(TEXT("{country}"), *CountryCode);
                            UE_LOG(LogBanEnforcer, Log,
                                TEXT("BanEnforcer: GeoIP block '%s' (%s) from %s"),
                                *PlayerName, *CapturedUid, *CountryCode);

                            // HTTP response callbacks fire on the HTTP thread; ALL UObject
                            // operations — WeakPtr resolution, IsValid(), GetWorld() — must
                            // run on the game thread to avoid data races with the GC.
                            AsyncTask(ENamedThreads::GameThread,
                                [WeakPC, CapturedUid, FinalMsg, PlayerName, IpAddress, CountryCode]()
                                {
                                    APlayerController* PCKick = WeakPC.Get();
                                    if (!IsValid(PCKick)) return;
                                    if (UWorld* W2 = PCKick->GetWorld())
                                        UBanEnforcer::KickConnectedPlayer(W2, CapturedUid, FinalMsg);
                                    FBanDiscordNotifier::NotifyGeoIpBlocked(
                                        PlayerName, CapturedUid, IpAddress, CountryCode);
                                });
                        });
                    GeoReq->ProcessRequest();
                }
            }
        }

        return;
    }

    const FString KickMsg = Entry.GetKickMessage();
    UE_LOG(LogBanEnforcer, Log,
        TEXT("BanEnforcer: kicking banned player %s (%s) — %s"),
        *RawId, *Platform, *KickMsg);

    // Send the ban reason to the client, then close the connection.
    // PC->ClientWasKicked() delivers the FText message to the player before
    // they are disconnected.  We do NOT call GM->GameSession->KickPlayer()
    // because AFGGameSession::KickPlayer registers with UFGServerSubsystem and
    // blocks reconnection even after the ban is lifted.
    // A 20-second timer gives the player time to read the reason before
    // they are actually disconnected.
    if (IsValid(PC))
    {
        PC->ClientWasKicked(FText::FromString(KickMsg));
        TWeakObjectPtr<APlayerController> WeakPC(PC);
        TWeakObjectPtr<UBanEnforcer> WeakEnforcer(this);
        // Store the handle in PendingKickTimersByUid so OnBanRemoved can cancel
        // the disconnect if the ban is lifted within the 20-second window.
        const FString BanUid = Entry.Uid;
        FTimerHandle& KickTimerHandle = PendingKickTimersByUid.FindOrAdd(BanUid);
        World->GetTimerManager().SetTimer(KickTimerHandle,
            FTimerDelegate::CreateLambda([WeakPC, WeakEnforcer, BanUid]()
            {
                if (UBanEnforcer* E = WeakEnforcer.Get())
                    E->PendingKickTimersByUid.Remove(BanUid);
                APlayerController* PCToKick = WeakPC.Get();
                if (!IsValid(PCToKick)) return;
                if (UNetConnection* Conn = Cast<UNetConnection>(PCToKick->Player))
                    Conn->Close();
            }), 20.0f, false);
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  Kick helper
// ─────────────────────────────────────────────────────────────────────────────

bool UBanEnforcer::KickConnectedPlayer(UWorld* World, const FString& Uid, const FString& Reason)
{
    if (!World) return false;

    AGameModeBase* GM = World->GetAuthGameMode();
    if (!GM) return false;

    // Parse the platform and raw player ID from the compound UID so we can fall back
    // to a second matching strategy when GetUniqueId() is not yet populated.
    FString UidPlatform, UidRawId;
    UBanDatabase::ParseUid(Uid, UidPlatform, UidRawId);

    for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PC = It->Get();
        if (!PC || !PC->PlayerState) continue;

        // ── Primary match: compound UID via FUniqueNetIdRepl ─────────────────
        const FUniqueNetIdRepl& NetId = PC->PlayerState->GetUniqueId();
        bool bMatched = false;
        if (NetId.IsValid() && NetId.GetType() != FName(TEXT("NONE")))
        {
            // Use direct FUniqueNetIdRepl accessors — safe for EOS V2 PUIDs.
            // (See PerformBanCheckForPlayer for the full explanation.)
            const FString Platform   = NetId.GetType().ToString().ToUpper();
            // Normalize to lowercase to match stored ban UIDs.
            const FString RawId      = NetId.ToString().ToLower();
            const FString PlayerUid  = UBanDatabase::MakeUid(Platform, RawId);

            if (Uid.Equals(PlayerUid, ESearchCase::IgnoreCase))
                bMatched = true;
        }

        if (!bMatched)
        {
            // ── Fallback A: CSS DS 1.1.0 — GetType()==NONE but EOS PUID may be
            //    available from the connection URL's ClientIdentity option.
            const FString UrlPuid = ExtractEosPuidFromConnectionUrl(PC);
            if (!UrlPuid.IsEmpty())
            {
                const FString UrlUid = UBanDatabase::MakeUid(TEXT("EOS"), UrlPuid);
                if (UrlUid == Uid)
                    bMatched = true;
            }
        }

        if (!bMatched && UidPlatform == TEXT("IP"))
        {
            // ── Fallback C: IP ban — compare against the remote address cached
            //    during the PreLogin hook.  Required when a ban is added at runtime
            //    and the player is already connected (the EOS PUID may never match
            //    the IP UID).
            UGameInstance* GI = World->GetGameInstance();
            if (GI)
            {
                if (UBanEnforcer* Enforcer = GI->GetSubsystem<UBanEnforcer>())
                {
                    const FString PlayerIp = Enforcer->GetCachedIpForPlayer(PC);
                    if (!PlayerIp.IsEmpty() && PlayerIp.Equals(UidRawId, ESearchCase::IgnoreCase))
                        bMatched = true;
                }
            }
        }

        if (!bMatched) continue;

        // Send the ban reason to the client, then close the connection after
        // 20 seconds so the player has time to read the reason.
        if (IsValid(PC))
        {
            PC->ClientWasKicked(FText::FromString(Reason));
            TWeakObjectPtr<APlayerController> WeakPC(PC);
            // Look up the Enforcer instance so we can store the timer handle in
            // PendingKickTimersByUid, allowing the OnBanRemoved handler to cancel
            // the pending disconnect if the ban is lifted within the 20-second window.
            UGameInstance* KickGI = World->GetGameInstance();
            UBanEnforcer* Enforcer = KickGI ? KickGI->GetSubsystem<UBanEnforcer>() : nullptr;
            TWeakObjectPtr<UBanEnforcer> WeakEnforcer(Enforcer);
            const FString KickBanUid = Uid;

            FTimerHandle LocalHandle; // fallback if Enforcer is unavailable
            FTimerHandle& KickTimerHandle = Enforcer
                ? Enforcer->PendingKickTimersByUid.FindOrAdd(KickBanUid)
                : LocalHandle;

            World->GetTimerManager().SetTimer(KickTimerHandle,
                FTimerDelegate::CreateLambda([WeakPC, WeakEnforcer, KickBanUid]()
                {
                    if (UBanEnforcer* E = WeakEnforcer.Get())
                        E->PendingKickTimersByUid.Remove(KickBanUid);
                    APlayerController* PCToKick = WeakPC.Get();
                    if (!IsValid(PCToKick)) return;
                    if (UNetConnection* Conn = Cast<UNetConnection>(PCToKick->Player))
                        Conn->Close();
                }), 20.0f, false);
        }

        UE_LOG(LogBanEnforcer, Log,
            TEXT("BanEnforcer: kicked connected player %s — %s"), *Uid, *Reason);
        return true;
    }

    UE_LOG(LogBanEnforcer, Log,
        TEXT("BanEnforcer: KickConnectedPlayer — no connected player found for UID %s"), *Uid);
    return false;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Ban check using a pre-computed UID (URL-extracted identity path)
// ─────────────────────────────────────────────────────────────────────────────

void UBanEnforcer::PerformBanCheckForUid(UWorld* World, APlayerController* PC, UBanDatabase* DB, const FString& Uid)
{
    if (!World || !IsValid(PC) || !DB) return;

    // Refresh the in-memory ban list from disk in case an admin manually edited
    // bans.json (e.g. to remove a ban) without going through the REST API or
    // chat commands.  This is a no-op when the file has not changed.
    DB->ReloadIfChanged();

    FString Platform, RawId;
    UBanDatabase::ParseUid(Uid, Platform, RawId);

    const FString PlayerName = (PC->PlayerState)
        ? PC->PlayerState->GetPlayerName()
        : TEXT("(unknown)");

    UE_LOG(LogBanEnforcer, Log,
        TEXT("BanEnforcer: checking ban status for player '%s' (%s: %s) [URL-extracted identity]"),
        *PlayerName, *Platform, *RawId);

    FBanEntry Entry;
    if (!DB->IsCurrentlyBannedByAnyId(Uid, Entry))
    {
        // Notify Discord if a temporary ban just expired.
        // AlreadyNotifiedExpiredBanUids deduplicates notifications when both
        // PerformBanCheckForPlayer and PerformBanCheckForUid run for the same login.
        {
            FBanEntry ExpiredEntry;
            if (DB->GetBanByUid(Uid, ExpiredEntry) && !ExpiredEntry.bIsPermanent && ExpiredEntry.IsExpired())
            {
                if (!AlreadyNotifiedExpiredBanUids.Contains(Uid))
                {
                    AlreadyNotifiedExpiredBanUids.Add(Uid);
                    FBanDiscordNotifier::NotifyBanExpired(ExpiredEntry);
                }
            }
        }

        // Also check the player's IP address — catches evasion via new EOS PUID.
        const FString CachedIp = GetCachedIpForPlayer(PC);
        if (!CachedIp.IsEmpty())
        {
            const FString IpUid = UBanDatabase::MakeUid(TEXT("IP"), CachedIp);
            FBanEntry IpEntry;
            if (DB->IsCurrentlyBannedByAnyId(IpUid, IpEntry))
            {
                const FString KickMsg = IpEntry.GetKickMessage();
                UE_LOG(LogBanEnforcer, Log,
                    TEXT("BanEnforcer: kicking IP-banned player '%s' (IP: %s) [URL-extracted path] — %s"),
                    *PlayerName, *CachedIp, *KickMsg);

                if (IsValid(PC))
                {
                    PC->ClientWasKicked(FText::FromString(KickMsg));
                    TWeakObjectPtr<APlayerController> WeakPC(PC);
                    TWeakObjectPtr<UBanEnforcer> WeakEnforcer(this);
                    const FString BanUid = IpEntry.Uid;
                    FTimerHandle& KickTimerHandle = PendingKickTimersByUid.FindOrAdd(BanUid);
                    World->GetTimerManager().SetTimer(KickTimerHandle,
                        FTimerDelegate::CreateLambda([WeakPC, WeakEnforcer, BanUid]()
                        {
                            if (UBanEnforcer* E = WeakEnforcer.Get())
                                E->PendingKickTimersByUid.Remove(BanUid);
                            APlayerController* PCToKick = WeakPC.Get();
                            if (!IsValid(PCToKick)) return;
                            if (UNetConnection* Conn = Cast<UNetConnection>(PCToKick->Player))
                                Conn->Close();
                        }), 20.0f, false);
                }
                return;
            }
        }

        UE_LOG(LogBanEnforcer, Log,
            TEXT("BanEnforcer: player '%s' (%s) is not banned — allowing join"),
            *PlayerName, *Uid);

        // Record the session for identity-persistence tracking.
        UGameInstance* GI = GetGameInstance();
        if (GI)
        {
            if (UPlayerSessionRegistry* Registry = GI->GetSubsystem<UPlayerSessionRegistry>())
                Registry->RecordSession(Uid, PlayerName,
                                        GetCachedIpForPlayer(PC),
                                        GetCachedVersionForPlayer(PC));
        }

        // Geo-IP check (async, config-gated) — same logic as PerformBanCheckForPlayer.
        {
            const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
            if (Cfg && Cfg->bGeoIpEnabled && !Cfg->GeoIpApiUrl.IsEmpty())
            {
                const FString IpAddress  = GetCachedIpForPlayer(PC);
                if (!IpAddress.IsEmpty() && FModuleManager::Get().IsModuleLoaded(TEXT("HTTP")))
                {
                    FString ApiUrl = Cfg->GeoIpApiUrl;
                    ApiUrl = ApiUrl.Replace(TEXT("{ip}"), *IpAddress, ESearchCase::IgnoreCase);

                    const TArray<FString> Allowed = Cfg->AllowedCountryCodes;
                    const TArray<FString> Blocked = Cfg->BlockedCountryCodes;
                    const FString KickMsg = Cfg->GeoIpKickMessage.IsEmpty()
                        ? TEXT("You are not permitted to join this server from your region.")
                        : Cfg->GeoIpKickMessage;

                    TWeakObjectPtr<APlayerController> WeakPC(PC);
                    const FString CapturedUid  = Uid;
                    const FString CapturedName = PlayerName;

                    TSharedRef<IHttpRequest, ESPMode::ThreadSafe> GeoReq =
                        FHttpModule::Get().CreateRequest();
                    GeoReq->SetURL(ApiUrl);
                    GeoReq->SetVerb(TEXT("GET"));
                    GeoReq->OnProcessRequestComplete().BindLambda(
                        [WeakPC, CapturedName, IpAddress, CapturedUid,
                         Allowed, Blocked, KickMsg]
                        (FHttpRequestPtr /*Req*/, FHttpResponsePtr Resp, bool bSuccess)
                        {
                            if (!bSuccess || !Resp.IsValid()) return;
                            // Treat non-2xx responses (rate-limits, errors, etc.) as
                            // "no data" rather than silently acting on a stale/error body.
                            const int32 Code = Resp->GetResponseCode();
                            if (Code < 200 || Code >= 300) return;

                            TSharedPtr<FJsonObject> Root;
                            TSharedRef<TJsonReader<>> Reader =
                                TJsonReaderFactory<>::Create(Resp->GetContentAsString());
                            if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid()) return;

                            FString CountryCode;
                            Root->TryGetStringField(TEXT("countryCode"), CountryCode);
                            CountryCode = CountryCode.ToUpper();
                            if (CountryCode.IsEmpty()) return;

                            bool bBlock = false;
                            if (Allowed.Num() > 0)
                                bBlock = !Allowed.ContainsByPredicate([&CountryCode](const FString& C){ return C.ToUpper() == CountryCode; });
                            else if (Blocked.Num() > 0)
                                bBlock = Blocked.ContainsByPredicate([&CountryCode](const FString& C){ return C.ToUpper() == CountryCode; });

                            if (!bBlock) return;

                            const FString FinalMsg = KickMsg.Replace(TEXT("{country}"), *CountryCode);
                            // HTTP response callbacks fire on the HTTP thread; ALL UObject
                            // operations — WeakPtr resolution, IsValid(), GetWorld() — must
                            // run on the game thread to avoid data races with the GC.
                            AsyncTask(ENamedThreads::GameThread,
                                [WeakPC, CapturedUid, FinalMsg, CapturedName, IpAddress, CountryCode]()
                                {
                                    APlayerController* PCKick = WeakPC.Get();
                                    if (!IsValid(PCKick)) return;
                                    if (UWorld* W2 = PCKick->GetWorld())
                                        UBanEnforcer::KickConnectedPlayer(W2, CapturedUid, FinalMsg);
                                    FBanDiscordNotifier::NotifyGeoIpBlocked(
                                        CapturedName, CapturedUid, IpAddress, CountryCode);
                                });
                        });
                    GeoReq->ProcessRequest();
                }
            }
        }

        return;
    }

    const FString KickMsg = Entry.GetKickMessage();
    UE_LOG(LogBanEnforcer, Log,
        TEXT("BanEnforcer: kicking banned player %s (%s) — %s"),
        *RawId, *Platform, *KickMsg);

    // Send the ban reason to the client, then close the connection after
    // 20 seconds so the player has time to read the reason.
    if (IsValid(PC))
    {
        PC->ClientWasKicked(FText::FromString(KickMsg));
        TWeakObjectPtr<APlayerController> WeakPC(PC);
        TWeakObjectPtr<UBanEnforcer> WeakEnforcer(this);
        const FString BanUid = Entry.Uid;
        FTimerHandle& KickTimerHandle = PendingKickTimersByUid.FindOrAdd(BanUid);
        World->GetTimerManager().SetTimer(KickTimerHandle,
            FTimerDelegate::CreateLambda([WeakPC, WeakEnforcer, BanUid]()
            {
                if (UBanEnforcer* E = WeakEnforcer.Get())
                    E->PendingKickTimersByUid.Remove(BanUid);
                APlayerController* PCToKick = WeakPC.Get();
                if (!IsValid(PCToKick)) return;
                if (UNetConnection* Conn = Cast<UNetConnection>(PCToKick->Player))
                    Conn->Close();
            }), 20.0f, false);
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  CSS DS 1.1.0 EOS PUID extraction from connection URL
// ─────────────────────────────────────────────────────────────────────────────

FString UBanEnforcer::ExtractEosPuidFromConnectionUrl(APlayerController* PC)
{
    if (!IsValid(PC)) return FString();

    // ── Primary path: PreLogin hook cache ────────────────────────────────────
    // On CSS DS 1.1.0 the server-side UNetConnection::URL is the server's bind
    // address, so Conn->URL.GetOption("ClientIdentity=") always returns null.
    // The PreLogin hook (installed in Initialize) caches the decoded EOS PUID
    // from the client's Options string before PostLogin fires.  Check it first.
    UNetConnection* Conn = Cast<UNetConnection>(PC->Player);
    if (Conn)
    {
        if (UGameInstance* GI = PC->GetWorld() ? PC->GetWorld()->GetGameInstance() : nullptr)
        {
            if (UBanEnforcer* Enforcer = GI->GetSubsystem<UBanEnforcer>())
            {
                if (const FString* Cached = Enforcer->CachedConnectionPuids.Find(TWeakObjectPtr<UNetConnection>(Conn)))
                {
                    UE_LOG(LogBanEnforcer, Verbose,
                        TEXT("BanEnforcer: ExtractEosPuidFromConnectionUrl — resolved '%s' from PreLogin cache"),
                        **Cached);
                    return *Cached;
                }
            }
        }
    }

    // ── Fallback path: Conn->URL option (works if CSS ever sets it) ──────────
    // Kept as a belt-and-suspenders fallback; historically always returned null
    // on CSS DS 1.1.0 because Conn->URL holds the server bind address, not the
    // client join URL.  May become relevant for future CSS versions.
    if (!Conn) return FString();

    // The ClientIdentity query option contains the EOS PUID as ASCII bytes
    // embedded in a binary blob encoded as a lowercase hex string.
    //
    // Layout (hex string offsets):
    //   0 - 7  : 4-byte LE header (length or version field)
    //   8 - 71 : 32 ASCII bytes that form the 32-char EOS PUID
    //            e.g. hex pair "34" = 0x34 = 52 = '4', so "3438" → "48"
    //   72+    : additional platform data (flags, etc.)
    const TCHAR* Opt = Conn->URL.GetOption(TEXT("ClientIdentity="), nullptr);
    if (!Opt || !*Opt) return FString();

    const FString Hex(Opt);
    // Minimum: 8 header chars + 64 PUID-as-bytes chars = 72 hex chars
    if (Hex.Len() < 72) return FString();

    FString Puid;
    Puid.Reserve(32);

    for (int32 i = 8; i < 72; i += 2)
    {
        // Decode one hex byte pair into the ASCII character it represents.
        const TCHAR Hi = FChar::ToLower(Hex[i]);
        const TCHAR Lo = FChar::ToLower(Hex[i + 1]);

        if (!FChar::IsHexDigit(Hi) || !FChar::IsHexDigit(Lo)) return FString();

        const uint8 HiNibble = (Hi >= 'a') ? (uint8)(Hi - 'a' + 10) : (uint8)(Hi - '0');
        const uint8 LoNibble = (Lo >= 'a') ? (uint8)(Lo - 'a' + 10) : (uint8)(Lo - '0');
        const TCHAR Ch       = (TCHAR)((HiNibble << 4) | LoNibble);

        // Each decoded byte must itself be a hex character: EOS PUIDs are
        // 32-char lowercase hex strings.
        if (!FChar::IsHexDigit(Ch)) return FString();
        Puid.AppendChar(Ch);
    }

    if (Puid.Len() != 32) return FString();
    return Puid.ToLower();
}

// ─────────────────────────────────────────────────────────────────────────────
//  IP address lookup from the PreLogin cache
// ─────────────────────────────────────────────────────────────────────────────

FString UBanEnforcer::GetCachedIpForPlayer(APlayerController* PC) const
{
    if (!IsValid(PC)) return FString();

    UNetConnection* Conn = Cast<UNetConnection>(PC->Player);
    if (!Conn) return FString();

    if (const FString* Cached = CachedConnectionIPs.Find(TWeakObjectPtr<UNetConnection>(Conn)))
        return *Cached;

    return FString();
}

FString UBanEnforcer::GetCachedVersionForPlayer(APlayerController* PC) const
{
    if (!IsValid(PC)) return FString();

    UNetConnection* Conn = Cast<UNetConnection>(PC->Player);
    if (!Conn) return FString();

    if (const FString* Cached = CachedConnectionVersions.Find(TWeakObjectPtr<UNetConnection>(Conn)))
        return *Cached;

    return FString();
}
