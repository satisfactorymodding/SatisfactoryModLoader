// Copyright Yamahasxviper. All Rights Reserved.

#include "BanSyncClient.h"
#include "BanDatabase.h"
#include "BanEnforcer.h"
#include "BanSystemConfig.h"
#include "BanAuditLog.h"
#include "SMLWebSocketClient.h"

#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

#include "Engine/GameInstance.h"

DEFINE_LOG_CATEGORY(LogBanSyncClient);

// ─────────────────────────────────────────────────────────────────────────────
//  USubsystem lifecycle
// ─────────────────────────────────────────────────────────────────────────────

void UBanSyncClient::Initialize(FSubsystemCollectionBase& Collection)
{
    Collection.InitializeDependency<UBanDatabase>();
    Super::Initialize(Collection);

    const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
    if (!Cfg || Cfg->PeerWebSocketUrls.IsEmpty())
        return;

    for (const FString& Url : Cfg->PeerWebSocketUrls)
    {
        if (Url.IsEmpty()) continue;

        USMLWebSocketClient* Client = NewObject<USMLWebSocketClient>(this);
        if (!Client) continue;

        // Subscribe to incoming messages.
        Client->OnMessage.AddDynamic(this, &UBanSyncClient::OnPeerMessage);

        // Auto-reconnect with default parameters.
        Client->bAutoReconnect = true;
        Client->ReconnectInitialDelaySeconds = 5.0f;
        Client->MaxReconnectDelaySeconds     = 60.0f;
        Client->bVerifySSLCertificate        = Cfg->bVerifyWSCertificate;
        Client->Connect(Url, TArray<FString>(), TMap<FString, FString>());

        PeerClients.Add(Client);

        UE_LOG(LogBanSyncClient, Log,
            TEXT("BanSyncClient: connecting to peer %s"), *Url);
    }

    // Subscribe to local ban/unban events so we can forward them to peers.
    UBanDatabase::OnBanAdded.AddUObject(this, &UBanSyncClient::OnLocalBanAdded);
    UBanDatabase::OnBanUpdated.AddUObject(this, &UBanSyncClient::OnLocalBanAdded);
    UBanDatabase::OnBanRemoved.AddUObject(this, &UBanSyncClient::OnLocalBanRemoved);
}

void UBanSyncClient::Deinitialize()
{
    UBanDatabase::OnBanAdded.RemoveAll(this);
    UBanDatabase::OnBanUpdated.RemoveAll(this);
    UBanDatabase::OnBanRemoved.RemoveAll(this);

    for (USMLWebSocketClient* Client : PeerClients)
    {
        if (Client)
            Client->Close();
    }
    PeerClients.Empty();
    Super::Deinitialize();
}

// ─────────────────────────────────────────────────────────────────────────────
//  Outbound broadcast
// ─────────────────────────────────────────────────────────────────────────────

void UBanSyncClient::BroadcastBan(const FString& Uid, const FString& PlayerName,
                                   const FString& Reason, const FString& BannedBy,
                                   int32 DurationMinutes, const FString& Category,
                                   const TArray<FString>& Evidence, FDateTime BanDate)
{
    TSharedPtr<FJsonObject> Msg = MakeShared<FJsonObject>();
    Msg->SetStringField(TEXT("type"),            TEXT("ban"));
    Msg->SetStringField(TEXT("uid"),             Uid);
    Msg->SetStringField(TEXT("playerName"),      PlayerName);
    Msg->SetStringField(TEXT("reason"),          Reason);
    Msg->SetStringField(TEXT("bannedBy"),        BannedBy);
    // int32 value — exactly representable in double; string encoding not needed
    // (the int64-string convention applies only to IDs that exceed 2^53).
    Msg->SetNumberField(TEXT("durationMinutes"), static_cast<double>(DurationMinutes));
    Msg->SetStringField(TEXT("category"),        Category);
    // Transmit the original ban-creation timestamp so peers preserve when the ban
    // was first placed rather than resetting BanDate to the sync timestamp.
    if (BanDate.GetTicks() > 0)
        Msg->SetStringField(TEXT("banDate"), BanDate.ToIso8601());
    // Transmit evidence links so peers store the same proof as the origin server.
    // Without this, any sync (including an update sync fired by OnBanUpdated) would
    // silently overwrite the peer's evidence array with an empty one.
    if (Evidence.Num() > 0)
    {
        TArray<TSharedPtr<FJsonValue>> EvidArr;
        for (const FString& Ev : Evidence)
            EvidArr.Add(MakeShared<FJsonValueString>(Ev));
        Msg->SetArrayField(TEXT("evidence"), EvidArr);
    }

    FString JsonStr;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonStr);
    if (!FJsonSerializer::Serialize(Msg.ToSharedRef(), Writer))
    {
        UE_LOG(LogBanSyncClient, Warning,
            TEXT("BanSyncClient: failed to serialize ban broadcast for %s"), *Uid);
        return;
    }

    for (USMLWebSocketClient* Client : PeerClients)
    {
        if (Client && Client->IsConnected())
            Client->SendText(JsonStr);
    }
}

void UBanSyncClient::BroadcastUnban(const FString& Uid, const FString& PlayerName)
{
    TSharedPtr<FJsonObject> Msg = MakeShared<FJsonObject>();
    Msg->SetStringField(TEXT("type"),       TEXT("unban"));
    Msg->SetStringField(TEXT("uid"),        Uid);
    Msg->SetStringField(TEXT("playerName"), PlayerName);

    FString JsonStr;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonStr);
    if (!FJsonSerializer::Serialize(Msg.ToSharedRef(), Writer))
    {
        UE_LOG(LogBanSyncClient, Warning,
            TEXT("BanSyncClient: failed to serialize unban broadcast for %s"), *Uid);
        return;
    }

    for (USMLWebSocketClient* Client : PeerClients)
    {
        if (Client && Client->IsConnected())
            Client->SendText(JsonStr);
    }
}

void UBanSyncClient::OnLocalBanAdded(const FBanEntry& Entry)
{
    // Consume-once: if OnPeerMessage registered this UID before calling AddBan(),
    // suppress re-broadcasting and remove the guard entry.  Using a UID set means
    // the guard survives even when OnBanAdded fires asynchronously after AddBan()
    // returns — a plain bool would have been cleared too early in that case.
    if (PeerAppliedBanUids.Remove(Entry.Uid) > 0) return;

    // Skip IP bans (Platform=="IP") from sync by default to avoid interfering
    // with peer-specific CIDR bans.
    if (Entry.Platform == TEXT("IP")) return;

    // Compute remaining lifetime in minutes as a floating-point value so we
    // can distinguish "truly expired" (≤ 0.0) from "< 1 minute remaining".
    const double RemainingMinutesDbl = Entry.bIsPermanent
        ? 0.0
        : (Entry.ExpireDate - FDateTime::UtcNow()).GetTotalMinutes();

    // Do not sync a temporary ban that has already expired — the peer would
    // have no meaningful duration to enforce.
    if (!Entry.bIsPermanent && (!FMath::IsFinite(RemainingMinutesDbl) || RemainingMinutesDbl <= 0.0))
        return;

    // Round UP fractional minutes so a ban with < 1 minute remaining maps to
    // 1 min rather than 0.  The previous static_cast<int32> (floor) caused
    // 1-minute bans to truncate to 0, which both triggered the early-return
    // guard above (ban silently never synced) and would have been read by the
    // receiver as a permanent ban had the guard not existed.  Ceiling also
    // prevents any ban from losing up to 59 seconds of enforced duration on
    // the receiving peer.
    // Guard against NaN/Inf before CeilToInt (UB on non-finite doubles).
    const int32 DurationMinutes = Entry.bIsPermanent
        ? 0
        : FMath::Max(1, FMath::CeilToInt(FMath::Min(RemainingMinutesDbl, static_cast<double>(INT32_MAX))));

    BroadcastBan(Entry.Uid, Entry.PlayerName, Entry.Reason, Entry.BannedBy,
                 DurationMinutes, Entry.Category, Entry.Evidence, Entry.BanDate);
}

void UBanSyncClient::OnLocalBanRemoved(const FString& Uid, const FString& PlayerName)
{
    // Consume-once: suppress re-broadcast for peer-sourced removals (both the
    // unban path and the stale-record removal that precedes a peer-sourced update).
    if (PeerAppliedUnbanUids.Remove(Uid) > 0) return;

    BroadcastUnban(Uid, PlayerName);
}

// ─────────────────────────────────────────────────────────────────────────────
//  Inbound message handler
// ─────────────────────────────────────────────────────────────────────────────

void UBanSyncClient::OnPeerMessage(const FString& Message)
{
    TSharedPtr<FJsonObject> Root;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Message);
    if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid()) return;

    FString Type;
    if (!Root->TryGetStringField(TEXT("type"), Type)) return;

    UGameInstance* GI = GetGameInstance();
    if (!GI) return;

    UBanDatabase* DB = GI->GetSubsystem<UBanDatabase>();
    if (!DB) return;

    if (Type == TEXT("ban"))
    {
        FString Uid, PlayerName, Reason, BannedBy, Category;
        Root->TryGetStringField(TEXT("uid"),        Uid);
        Root->TryGetStringField(TEXT("playerName"), PlayerName);
        Root->TryGetStringField(TEXT("reason"),     Reason);
        Root->TryGetStringField(TEXT("bannedBy"),   BannedBy);
        Root->TryGetStringField(TEXT("category"),   Category);

        double DurDbl = 0.0;
        const bool bHasDurationMinutes = Root->TryGetNumberField(TEXT("durationMinutes"), DurDbl);
        if (bHasDurationMinutes && (!FMath::IsFinite(DurDbl) || DurDbl < 0.0))
        {
            UE_LOG(LogBanSyncClient, Warning,
                TEXT("BanSyncClient: dropping peer ban for uid '%s' due to invalid durationMinutes=%f"),
                *Uid, DurDbl);
            return;
        }
        if (bHasDurationMinutes && DurDbl > 0.0 && FMath::Fmod(DurDbl, 1.0) != 0.0)
        {
            UE_LOG(LogBanSyncClient, Warning,
                TEXT("BanSyncClient: dropping peer ban for uid '%s' due to non-integer durationMinutes=%f"),
                *Uid, DurDbl);
            return;
        }
        const int32 DurationMinutes = (FMath::IsFinite(DurDbl) && DurDbl > 0.0 && DurDbl <= static_cast<double>(INT32_MAX))
            ? FMath::Max(1, static_cast<int32>(DurDbl))
            : 0;

        // Parse the original ban-creation timestamp.  Fall back to UtcNow() so
        // that messages from older peers (without the banDate field) still work.
        FDateTime OriginalBanDate;
        {
            FString BanDateStr;
            if (!Root->TryGetStringField(TEXT("banDate"), BanDateStr) ||
                !FDateTime::ParseIso8601(*BanDateStr, OriginalBanDate) ||
                OriginalBanDate.GetTicks() <= 0)
            {
                OriginalBanDate = FDateTime(0); // sentinel: will be set to Now below
            }
        }

        // Parse the evidence array.  Empty arrays are silently accepted (no evidence
        // was attached to this ban).
        TArray<FString> IncomingEvidence;
        {
            const TArray<TSharedPtr<FJsonValue>>* EvidArr = nullptr;
            if (Root->TryGetArrayField(TEXT("evidence"), EvidArr) && EvidArr)
            {
                for (const TSharedPtr<FJsonValue>& EvidVal : *EvidArr)
                {
                    if (!EvidVal.IsValid()) continue;
                    FString Ev;
                    if (EvidVal->TryGetString(Ev) && !Ev.IsEmpty())
                        IncomingEvidence.Add(Ev);
                }
            }
        }

        if (Uid.IsEmpty()) return;

        // If the player is already banned, check whether key fields differ.
        // If they match exactly, skip (no change). If they differ (reason, duration,
        // category updated on the origin server), update the existing record in
        // place so a SaveToFile failure cannot silently unban the player.
        bool bWasUpdate = false; // true when we're replacing an existing ban record
        FBanEntry Existing;
        if (DB->IsCurrentlyBanned(Uid, Existing))
        {
            // Never downgrade a permanent ban to a temporary ban via peer sync.
            // The origin server may have since extended the ban or it may have
            // been placed manually; in either case the permanent record wins.
            if (Existing.bIsPermanent && DurationMinutes > 0)
                return;

            const FString IncomingReason   = Reason.IsEmpty() ? TEXT("Synced ban from peer server") : Reason;
            const FString IncomingBannedBy = BannedBy.IsEmpty() ? TEXT("peer") : BannedBy;
            const bool bPermanentMatch     = (Existing.bIsPermanent == (DurationMinutes <= 0));
            const bool bReasonMatch        = (Existing.Reason == IncomingReason);
            const bool bCategoryMatch      = (Existing.Category == Category);
            // Compare remaining lifetime of the existing ban against the incoming
            // duration to detect duration-only updates.  Using remaining seconds
            // avoids the systematic positive offset that occurred when IncomingExpiry
            // was projected as UtcNow()+DurationMinutes after ceiling-rounding had
            // already added up to 59 extra seconds.  Allow a 60-second tolerance to
            // absorb transmission latency and sub-minute timing drift.
            const bool bExpiryMatch = Existing.bIsPermanent
                ? true
                : FMath::Abs((Existing.ExpireDate - FDateTime::UtcNow()).GetTotalSeconds() -
                              DurationMinutes * 60.0) < 60.0;
            // Compare evidence arrays so that an update which only adds/removes evidence
            // is not silently dropped (both arrays must have the same ordered elements).
            const bool bEvidenceMatch = (Existing.Evidence == IncomingEvidence);
            if (bPermanentMatch && bReasonMatch && bCategoryMatch && bExpiryMatch && bEvidenceMatch)
                return; // Identical — nothing to update.

            FBanEntry UpdatedBan;
            UpdatedBan.Uid        = Existing.Uid;
            UpdatedBan.Platform   = Existing.Platform;
            UpdatedBan.PlayerUID  = Existing.PlayerUID;
            UpdatedBan.PlayerName = PlayerName;
            UpdatedBan.Reason     = IncomingReason;
            UpdatedBan.BannedBy   = IncomingBannedBy;
            UpdatedBan.BanDate    = (OriginalBanDate.GetTicks() > 0) ? OriginalBanDate : Existing.BanDate;
            UpdatedBan.Category   = Category;
            UpdatedBan.bIsPermanent = (DurationMinutes <= 0);
            UpdatedBan.ExpireDate   = UpdatedBan.bIsPermanent
                ? FDateTime(0)
                : FDateTime::UtcNow() + FTimespan::FromMinutes(DurationMinutes);
            UpdatedBan.Evidence     = IncomingEvidence;
            UpdatedBan.LinkedUids   = Existing.LinkedUids;

            FBanEntry PersistedUpdate;
            bWasUpdate = DB->UpdateBan(Uid,
                [UpdatedBan](FBanEntry& BanToMutate)
                {
                    BanToMutate.PlayerName   = UpdatedBan.PlayerName;
                    BanToMutate.Reason       = UpdatedBan.Reason;
                    BanToMutate.BannedBy     = UpdatedBan.BannedBy;
                    BanToMutate.BanDate      = UpdatedBan.BanDate;
                    BanToMutate.Category     = UpdatedBan.Category;
                    BanToMutate.bIsPermanent = UpdatedBan.bIsPermanent;
                    BanToMutate.ExpireDate   = UpdatedBan.ExpireDate;
                    BanToMutate.Evidence     = UpdatedBan.Evidence;
                },
                PersistedUpdate);

            if (bWasUpdate)
            {
                if (UWorld* World = GI->GetWorld())
                    UBanEnforcer::KickConnectedPlayer(World, Uid, PersistedUpdate.GetKickMessage());

                if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
                    AuditLog->LogAction(TEXT("ban"), Uid, PlayerName,
                        TEXT("peer"), TEXT("peer"),
                        FString::Printf(TEXT("Synced from peer. Reason: %s"), *PersistedUpdate.Reason));

                UE_LOG(LogBanSyncClient, Log,
                    TEXT("BanSyncClient: updated synced ban for %s"), *Uid);
                return;
            }

            // UpdateBan() returns false both when the row disappeared concurrently
            // and when persistence failed. If the old ban is still present, abort
            // here so a follow-up AddBan attempt cannot overwrite it or emit a
            // misleading OnBanAdded event.
            FBanEntry StillExisting;
            if (DB->IsCurrentlyBanned(Uid, StillExisting))
                return;
        }

        FBanEntry Ban;
        Ban.Uid        = Uid;
        UBanDatabase::ParseUid(Uid, Ban.Platform, Ban.PlayerUID);
        Ban.PlayerName      = PlayerName;
        Ban.Reason          = Reason.IsEmpty() ? TEXT("Synced ban from peer server") : Reason;
        Ban.BannedBy        = BannedBy.IsEmpty() ? TEXT("peer") : BannedBy;
        const FDateTime Now = FDateTime::UtcNow();
        // Preserve the original ban-creation timestamp when the peer sent one;
        // fall back to Now for messages from older peers that omit the field.
        Ban.BanDate         = (OriginalBanDate.GetTicks() > 0) ? OriginalBanDate : Now;
        Ban.Category        = Category;
        Ban.bIsPermanent    = (DurationMinutes <= 0);
        Ban.ExpireDate      = Ban.bIsPermanent
            ? FDateTime(0)
            : Now + FTimespan::FromMinutes(DurationMinutes);
        // Preserve evidence so peers store the same proof as the origin server.
        Ban.Evidence        = IncomingEvidence;

        // Register the UID in PeerAppliedBanUids before calling AddBan() so that
        // OnLocalBanAdded suppresses re-broadcasting this peer-sourced ban.
        // Consume-once semantics: OnLocalBanAdded removes the entry when it fires,
        // so the guard holds whether OnBanAdded fires synchronously or asynchronously.
        PeerAppliedBanUids.Add(Uid);

        // Use AddBanSkipIfPermanentExists for temporary bans so that a permanent
        // ban that was added between the IsCurrentlyBanned() check above and this
        // AddBan call is never silently downgraded to a shorter temp ban (TOCTOU).
        // Permanent bans are safe to use AddBan directly — an intentional overwrite
        // is acceptable when the origin server explicitly escalated to permanent.
        bool bPeerSyncSkipped = false;
        const bool bAdded = Ban.bIsPermanent
            ? DB->AddBan(Ban)
            : DB->AddBanSkipIfPermanentExists(Ban, bPeerSyncSkipped);

        if (!bAdded)
        {
            // AddBan / AddBanSkipIfPermanentExists failed or skipped — clean up the
            // pre-added guard entry so it does not silently suppress a future
            // legitimate local ban for this UID.
            PeerAppliedBanUids.Remove(Uid);

            if (bPeerSyncSkipped)
            {
                UE_LOG(LogBanSyncClient, Log,
                    TEXT("BanSyncClient: skipped temp sync ban for %s — a permanent ban already exists."),
                    *Uid);
            }
        }

        if (bAdded)
        {
            if (UWorld* World = GI->GetWorld())
                UBanEnforcer::KickConnectedPlayer(World, Uid, Ban.GetKickMessage());

            // Only fire the "🔨 Player Banned" webhook embed for genuinely new bans.
            // When bWasUpdate is true the ban already existed on this peer; posting
            // NotifyBanCreated would produce a spurious "Player Banned" Discord embed
            // for what was merely a reason/duration/evidence edit on the origin server.
            if (!bWasUpdate)
                FBanDiscordNotifier::NotifyBanCreated(Ban);

            if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
                AuditLog->LogAction(TEXT("ban"), Uid, PlayerName,
                    TEXT("peer"), TEXT("peer"),
                    FString::Printf(TEXT("Synced from peer. Reason: %s"), *Ban.Reason));

            UE_LOG(LogBanSyncClient, Log,
                TEXT("BanSyncClient: applied synced ban for %s"), *Uid);
        }
    }
    else if (Type == TEXT("unban"))
    {
        FString Uid, PlayerName;
        Root->TryGetStringField(TEXT("uid"),        Uid);
        Root->TryGetStringField(TEXT("playerName"), PlayerName);

        if (Uid.IsEmpty()) return;

        // Register the UID in PeerAppliedUnbanUids before calling RemoveBanByUid()
        // so OnLocalBanRemoved suppresses re-broadcasting this peer-sourced unban.
        PeerAppliedUnbanUids.Add(Uid);
        FBanEntry RemovedEntry;
        const bool bRemoved = DB->RemoveBanByUid(Uid, RemovedEntry);
        if (!bRemoved)
        {
            // Ban was not found — RemoveBanByUid will not fire OnBanRemoved,
            // so clean up the pre-added entry to avoid a spurious future suppression.
            PeerAppliedUnbanUids.Remove(Uid);
        }

        if (bRemoved)
        {
            // Also remove any counterpart bans (IP↔EOS links) so no linked
            // ban is left behind after the peer-sourced unban is applied.
            for (const FString& LinkedUid : RemovedEntry.LinkedUids)
            {
                PeerAppliedUnbanUids.Add(LinkedUid);
                if (!DB->RemoveBanByUid(LinkedUid))
                    PeerAppliedUnbanUids.Remove(LinkedUid);
            }

            // Notify Discord so the unban appears in the audit log channel —
            // mirrors NotifyBanCreated fired on peer ban at line 358.
            FBanDiscordNotifier::NotifyBanRemoved(Uid, PlayerName, TEXT("peer"));

            if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
                AuditLog->LogAction(TEXT("unban"), Uid, PlayerName,
                    TEXT("peer"), TEXT("peer"),
                    TEXT("Synced unban from peer server"));

            UE_LOG(LogBanSyncClient, Log,
                TEXT("BanSyncClient: applied synced unban for %s"), *Uid);
        }
    }
}
