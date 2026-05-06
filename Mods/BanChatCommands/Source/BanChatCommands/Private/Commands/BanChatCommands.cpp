// Copyright Yamahasxviper. All Rights Reserved.

#include "Commands/BanChatCommands.h"
#include "BanChatCommandsConfig.h"
#include "BanChatCommandsModule.h"
#include "Command/CommandSender.h"
#include "BanDatabase.h"
#include "BanEnforcer.h"
#include "BanTypes.h"
#include "MuteRegistry.h"
#include "PlayerSessionRegistry.h"
#include "PlayerWarningRegistry.h"
#include "BanSystemConfig.h"
#include "BanDiscordNotifier.h"
#include "BanAuditLog.h"
#include "ScheduledBanRegistry.h"
#include "Engine/GameInstance.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/OnlineReplStructs.h"
// Full definition required for Cast<> between AFGPlayerController and APlayerController
// (UE Cast<> rejects incomplete types via static_assert in Casts.h).
#include "FGPlayerController.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "BanAppealRegistry.h"

DEFINE_LOG_CATEGORY(LogBanChatCommands);

// ─────────────────────────────────────────────────────────────────────────────
//  Internal helpers
// ─────────────────────────────────────────────────────────────────────────────
namespace BanChat
{
    // Forward declarations for functions used before their definition.
    static bool IsBanRateLimited(UCommandSender* Sender, const FString& AdminUid);

    static UBanDatabase* GetDB(UObject* Ctx)
    {
        if (!Ctx) return nullptr;
        UWorld* World = Ctx->GetWorld();
        if (!World) return nullptr;
        UGameInstance* GI = World->GetGameInstance();
        return GI ? GI->GetSubsystem<UBanDatabase>() : nullptr;
    }

    /** Join Arguments[StartIdx..] into a space-separated string. */
    static FString JoinArgs(const TArray<FString>& Arguments, int32 StartIdx)
    {
        FString Result;
        for (int32 i = StartIdx; i < Arguments.Num(); ++i)
        {
            if (i > StartIdx) Result += TEXT(" ");
            Result += Arguments[i];
        }
        return Result;
    }

    /** Format ban duration for human-readable confirmation. */
    static FString FormatDuration(int32 DurationMinutes)
    {
        if (DurationMinutes <= 0)
            return TEXT("permanently");

        const int32 Weeks   = DurationMinutes / (60 * 24 * 7);
        const int32 Days    = (DurationMinutes % (60 * 24 * 7)) / (60 * 24);
        const int32 Hours   = (DurationMinutes % (60 * 24)) / 60;
        const int32 Minutes = DurationMinutes % 60;

        FString Result = TEXT("for ");
        bool bNeedSpace = false;
        if (Weeks > 0)   { Result += FString::Printf(TEXT("%dw"), Weeks);   bNeedSpace = true; }
        if (Days > 0)    { if (bNeedSpace) Result += TEXT(" "); Result += FString::Printf(TEXT("%dd"), Days);    bNeedSpace = true; }
        if (Hours > 0)   { if (bNeedSpace) Result += TEXT(" "); Result += FString::Printf(TEXT("%dh"), Hours);   bNeedSpace = true; }
        if (Minutes > 0) { if (bNeedSpace) Result += TEXT(" "); Result += FString::Printf(TEXT("%dm"), Minutes); }
        return Result;
    }

    /** Format ban expiry date for display output. */
    static FString FormatExpiry(const FBanEntry& Entry)
    {
        if (Entry.bIsPermanent)
            return TEXT("never (permanent)");
        return Entry.ExpireDate.ToString(TEXT("%Y-%m-%d %H:%M:%S")) + TEXT(" UTC");
    }

    /** Returns true if Id is a 32-character lowercase hex EOS Product User ID. */
    static bool IsValidEOSPUID(const FString& Id)
    {
        if (Id.Len() != 32) return false;
        for (TCHAR c : Id)
            if (!FChar::IsHexDigit(c)) return false;
        return true;
    }

    /**
     * Given a lowercase EOS PUID, attempts to resolve the player's real display name.
     *
     * Resolution order:
     *   1. Currently-connected PlayerController whose EOS PUID matches.
     *   2. PlayerSessionRegistry (persisted from previous sessions).
     *   3. Falls back to the raw PUID string when neither source has a name.
     */
    static FString ResolveDisplayNameForPuid(UObject* Ctx, const FString& LowerPuid)
    {
        UWorld* World = Ctx ? Ctx->GetWorld() : nullptr;
        if (!World) return LowerPuid;

        // 1. Check currently-connected players.
        for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
        {
            APlayerController* PC = It->Get();
            if (!PC || !PC->PlayerState) continue;

            const FUniqueNetIdRepl& UniqueId = PC->PlayerState->GetUniqueId();
            FString ConnectedPuid;
            if (UniqueId.IsValid() && UniqueId.GetType() != FName(TEXT("NONE")))
                ConnectedPuid = UniqueId.ToString().ToLower();
            else
                ConnectedPuid = UBanEnforcer::ExtractEosPuidFromConnectionUrl(PC);

            if (!ConnectedPuid.IsEmpty() && ConnectedPuid == LowerPuid)
                return PC->PlayerState->GetPlayerName();
        }

        // 2. Check the session registry for a previously-seen display name.
        UGameInstance* GI = World->GetGameInstance();
        UPlayerSessionRegistry* Registry = GI ? GI->GetSubsystem<UPlayerSessionRegistry>() : nullptr;
        if (Registry)
        {
            FPlayerSessionRecord Record;
            if (Registry->FindByUid(UBanDatabase::MakeUid(TEXT("EOS"), LowerPuid), Record)
                && !Record.DisplayName.IsEmpty())
            {
                return Record.DisplayName;
            }
        }

        // 3. No name found — fall back to the raw PUID.
        return LowerPuid;
    }

    /**
     * Check whether the command sender is allowed to run admin commands.
     *
     * Console senders (non-player) are always permitted.  Player senders must
     * have their EOS PUID listed in UBanChatCommandsConfig::AdminEosPUIDs.
     * When the list is empty, player access is denied (console-only mode).
     *
     * Note: On CSS Dedicated Server all players are identified by their EOS
     * Product User ID regardless of launch platform (Steam, Epic, etc.).
     *
     * @param Sender  The command sender to check.
     * @param OutUid  Populated with the sender's compound UID when they connect via a known platform.
     * @return true when the sender is authorised to run admin commands.
     */
    static bool IsAdminSender(UCommandSender* Sender, FString& OutUid, bool bSendError = true)
    {
        if (!Sender) return false; // null sender — deny to fail safely
        if (!Sender->IsPlayerSender())
        {
            // Console / server operator — always allowed.
            OutUid.Reset();
            return true;
        }

        // Resolve the sender's platform identity directly from their PlayerState.
        APlayerController* PC = Cast<APlayerController>(Sender->GetPlayer());
        if (PC && PC->PlayerState)
        {
            const FUniqueNetIdRepl& UniqueId = PC->PlayerState->GetUniqueId();
            // Use direct FUniqueNetIdRepl member accessors — do NOT dereference
            // via operator-> (UniqueId->GetType() / UniqueId->ToString()).
            // On CSS DS with EOS V2 PUIDs the inner TSharedPtr slot holds a raw
            // EOS handle, not a valid C++ FUniqueNetId object; operator-> returns
            // a garbage pointer that crashes.  FUniqueNetIdRepl::GetType() and
            // FUniqueNetIdRepl::ToString() are safe for EOS PUID (V2) identities.
            // Guard against a NONE-type identity that IsValid() can return true for
            // before the EOS PUID provider assigns it (GetType()=="NONE", ToString()=="").
            if (UniqueId.IsValid() && UniqueId.GetType() != FName(TEXT("NONE")))
            {
                // CSS DS exclusively assigns EOS PUIDs — always build an EOS compound UID,
                // normalized to lowercase to match bans stored via /ban and /tempban.
                OutUid = UBanDatabase::MakeUid(TEXT("EOS"), UniqueId.ToString().ToLower());
            }
            else
            {
                // CSS DS 1.1.0 workaround: GetType()==NONE because EOS online
                // subsystem is offline.  Extract the EOS PUID from the connection
                // URL's ClientIdentity option instead.
                const FString EosPuid = UBanEnforcer::ExtractEosPuidFromConnectionUrl(PC);
                if (!EosPuid.IsEmpty())
                    OutUid = UBanDatabase::MakeUid(TEXT("EOS"), EosPuid);
            }
        }

        const UBanChatCommandsConfig* Cfg = UBanChatCommandsConfig::Get();
        if (!Cfg || !Cfg->IsAdminUid(OutUid))
        {
            if (bSendError)
                Sender->SendChatMessage(
                    TEXT("[BanChatCommands] You do not have permission to use this command."),
                    FLinearColor::Red);
            return false;
        }
        return true;
    }

    /**
     * Resolve a player argument to a compound ban UID.
     *
     * Resolution order:
     *   1. 32-char hex       → EOS PUID   → UID "EOS:xxx"
     *   2. Otherwise         → display-name substring lookup against connected players.
     *
     * Returns true on success and populates OutUid + OutDisplayName.
     */
    static bool ResolveTarget(UObject* Ctx, UCommandSender* Sender,
                              const FString& Arg,
                              FString& OutUid,
                              FString& OutDisplayName)
    {
        // 1. Raw EOS PUID (32-char hex)
        if (IsValidEOSPUID(Arg))
        {
            const FString Lower = Arg.ToLower();
            OutUid         = UBanDatabase::MakeUid(TEXT("EOS"), Lower);
            OutDisplayName = ResolveDisplayNameForPuid(Ctx, Lower);
            return true;
        }

        // 2. Compound UID supplied directly:
        //      "EOS:<32hex>"  → resolve without requiring player to be connected
        //      "IP:<address>" → IP ban UID (e.g. from /banname or manual entry)
        {
            FString Platform, RawId;
            UBanDatabase::ParseUid(Arg, Platform, RawId);
            if (Platform == TEXT("EOS") && IsValidEOSPUID(RawId))
            {
                const FString Lower = RawId.ToLower();
                OutUid         = UBanDatabase::MakeUid(TEXT("EOS"), Lower);
                OutDisplayName = ResolveDisplayNameForPuid(Ctx, Lower);
                return true;
            }
            if (Platform == TEXT("IP") && !RawId.IsEmpty())
            {
                OutUid         = UBanDatabase::MakeUid(TEXT("IP"), RawId);
                OutDisplayName = RawId;
                return true;
            }
        }

        // 3. Display-name lookup against connected PlayerControllers.
        UWorld* World = Ctx ? Ctx->GetWorld() : nullptr;
        if (!World)
        {
            Sender->SendChatMessage(
                FString::Printf(TEXT("[BanChatCommands] World context unavailable — "
                    "cannot look up player by name. Provide an explicit EOS PUID (e.g. EOS:%s) "
                    "or re-run the command once the world has initialised."), *Arg),
                FLinearColor::Red);
            return false;
        }

        APlayerController* FoundPC = nullptr;
        TArray<FString>    Matches;
        for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
        {
            APlayerController* PC = It->Get();
            if (!PC || !PC->PlayerState) continue;
            const FString Name = PC->PlayerState->GetPlayerName();
            if (Name.Contains(Arg, ESearchCase::IgnoreCase))
            {
                Matches.Add(Name);
                if (!FoundPC) FoundPC = PC;
            }
        }

        if (Matches.IsEmpty())
        {
            Sender->SendChatMessage(
                FString::Printf(TEXT("[BanChatCommands] No connected player found matching '%s'. "
                    "Use an EOS PUID to target offline players."), *Arg),
                FLinearColor::Red);
            return false;
        }

        if (Matches.Num() > 1)
        {
            Sender->SendChatMessage(
                FString::Printf(TEXT("[BanChatCommands] Ambiguous name '%s'. Matching players: %s"),
                    *Arg, *FString::Join(Matches, TEXT(", "))),
                FLinearColor::Yellow);
            return false;
        }

        // Unique match — resolve their platform identity.
        const FUniqueNetIdRepl& UniqueId = FoundPC->PlayerState->GetUniqueId();
        // Guard against NONE-type: IsValid() can return true before the EOS PUID
        // provider assigns the identity (GetType()=="NONE", ToString()=="").
        // Also use direct member accessors — NOT operator-> — to avoid a crash on
        // CSS DS with EOS V2 PUIDs (see IsAdminSender for the full explanation).
        if (!UniqueId.IsValid() || UniqueId.GetType() == FName(TEXT("NONE")))
        {
            // CSS DS 1.1.0 workaround: GetType()==NONE because the EOS online
            // subsystem is offline (IsOnline=false).  The EOS PUID is still
            // transmitted in the ClientIdentity URL option.  Try that before
            // giving up — this is the same fallback used by IsAdminSender,
            // OnPostLogin, ProcessPendingBanChecks, and KickConnectedPlayer.
            const FString EosPuid = UBanEnforcer::ExtractEosPuidFromConnectionUrl(FoundPC);
            if (!EosPuid.IsEmpty())
            {
                OutUid         = UBanDatabase::MakeUid(TEXT("EOS"), EosPuid);
                OutDisplayName = Matches[0];
                UE_LOG(LogBanChatCommands, Log,
                    TEXT("BanChatCommands: Resolved '%s' → EOS:%s (via connection URL) for moderator action"),
                    *Arg, *EosPuid);
                Sender->SendChatMessage(
                    FString::Printf(TEXT("[BanChatCommands] Resolved '%s' to player '%s'."),
                        *Arg, *Matches[0]),
                    FLinearColor::White);
                return true;
            }

            Sender->SendChatMessage(
                FString::Printf(TEXT("[BanChatCommands] Found player '%s' but could not resolve "
                    "their platform identity."), *Matches[0]),
                FLinearColor::Red);
            return false;
        }

        // CSS DS exclusively assigns EOS PUIDs — always build an EOS compound UID,
        // normalized to lowercase to match bans stored via /ban or /tempban.
        const FString RawId = UniqueId.ToString().ToLower();
        OutUid         = UBanDatabase::MakeUid(TEXT("EOS"), RawId);
        OutDisplayName = Matches[0];

        UE_LOG(LogBanChatCommands, Log,
            TEXT("BanChatCommands: Resolved '%s' → EOS:%s for moderator action"),
            *Arg, *RawId);
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] Resolved '%s' to player '%s'."),
                *Arg, *Matches[0]),
            FLinearColor::White);
        return true;
    }

    /**
     * After a primary ban has been committed for PrimaryUid, look up the
     * player's other identifiers in the session registry and create matching
     * ban records so that every identity is blocked together.
     *
     *  - EOS UID  → also bans the IP address recorded for that EOS UID.
     *  - IP UID   → also bans every EOS UID that has connected from that IP.
     *
     * All newly created records are cross-linked to PrimaryUid via
     * UBanDatabase::LinkBans().  Sender may be nullptr (console path).
     */
    static void AddCounterpartBans(UObject* Ctx, UCommandSender* Sender,
                                   const FString& PrimaryUid,
                                   const FString& DisplayName,
                                   int32 DurationMinutes,
                                   const FString& Reason,
                                   const FString& BannedBy)
    {
        UBanDatabase* DB = GetDB(Ctx);
        UWorld* World = Ctx ? Ctx->GetWorld() : nullptr;
        UGameInstance* GI = World ? World->GetGameInstance() : nullptr;
        UPlayerSessionRegistry* Registry = GI ? GI->GetSubsystem<UPlayerSessionRegistry>() : nullptr;
        if (!DB || !Registry) return;

        FString Platform, RawId;
        UBanDatabase::ParseUid(PrimaryUid, Platform, RawId);

        // Build a ban entry for a counterpart identifier, copying timing from the primary.
        // Capture the timestamp once so every counterpart ban shares the same BanDate.
        const FDateTime EntryNow = FDateTime::UtcNow();
        auto MakeEntry = [&](const FString& Uid, const FString& Plat,
                             const FString& RawUid, const FString& Name) -> FBanEntry
        {
            FBanEntry E;
            E.Uid        = Uid;
            E.Platform   = Plat;
            E.PlayerUID  = RawUid;
            E.PlayerName = Name;
            E.Reason     = Reason;
            E.BannedBy   = BannedBy;
            E.BanDate    = EntryNow;
            if (DurationMinutes <= 0)
            {
                E.bIsPermanent = true;
                E.ExpireDate   = FDateTime(0);
            }
            else
            {
                E.bIsPermanent = false;
                E.ExpireDate   = EntryNow + FTimespan::FromMinutes(DurationMinutes);
            }
            E.LinkedUids.Add(PrimaryUid);
            return E;
        };

        if (Platform == TEXT("EOS"))
        {
            // Also ban the IP address recorded for this EOS UID.
            FPlayerSessionRecord Rec;
            if (Registry->FindByUid(PrimaryUid, Rec) && !Rec.IpAddress.IsEmpty())
            {
                const FString IpUid = UBanDatabase::MakeUid(TEXT("IP"), Rec.IpAddress);
                FBanEntry IpEntry = MakeEntry(IpUid, TEXT("IP"), Rec.IpAddress, DisplayName);
                bool bChatIpSkipped = false;
                if (DB->AddBanSkipIfPermanentExists(IpEntry, bChatIpSkipped))
                {
                    DB->LinkBans(PrimaryUid, IpUid);
                    // Kick any currently-connected player whose IP matches the counterpart ban.
                    UBanEnforcer::KickConnectedPlayer(World, IpUid, IpEntry.GetKickMessage());
                    if (Sender)
                        Sender->SendChatMessage(
                            FString::Printf(TEXT("[BanChatCommands] Also banned IP %s — linked to EOS ban."),
                                *Rec.IpAddress),
                            FLinearColor::Green);
                }
                else if (bChatIpSkipped)
                {
                    // Existing permanent IP ban takes precedence; still ensure the cross-link.
                    DB->LinkBans(PrimaryUid, IpUid);
                }
            }
        }
        else if (Platform == TEXT("IP"))
        {
            // Also ban every EOS UID that has connected from this IP address.
            TArray<FPlayerSessionRecord> Records = Registry->FindByIp(RawId);
            for (const FPlayerSessionRecord& Rec : Records)
            {
                if (Rec.Uid.IsEmpty()) continue;
                FString RecPlat, RecRawId;
                UBanDatabase::ParseUid(Rec.Uid, RecPlat, RecRawId);
                const FString RecName = Rec.DisplayName.IsEmpty() ? DisplayName : Rec.DisplayName;
                FBanEntry EosEntry = MakeEntry(Rec.Uid, RecPlat, RecRawId, RecName);
                bool bChatEosSkipped = false;
                if (DB->AddBanSkipIfPermanentExists(EosEntry, bChatEosSkipped))
                {
                    DB->LinkBans(PrimaryUid, Rec.Uid);
                    // Kick any currently-connected player matching this counterpart EOS ban.
                    UBanEnforcer::KickConnectedPlayer(World, Rec.Uid, EosEntry.GetKickMessage());
                    if (Sender)
                        Sender->SendChatMessage(
                            FString::Printf(TEXT("[BanChatCommands] Also banned EOS %s (%s) — linked to IP ban."),
                                *RecName, *Rec.Uid),
                            FLinearColor::Green);
                }
                else if (bChatEosSkipped)
                {
                    // Existing permanent EOS ban takes precedence; still ensure the cross-link.
                    DB->LinkBans(PrimaryUid, Rec.Uid);
                }
            }
        }
    }

    /**
     * After removing the primary ban for PrimaryUid, also remove all linked
     * ban records so no counterpart bans are left behind.
     *
     * Removes records listed in LinkedUids (obtained from the ban entry before
     * deletion) and then uses the session registry to find any counterparts
     * that were not explicitly linked.
     *
     * Sender may be nullptr (console path).
     */
    static void RemoveCounterpartBans(UObject* Ctx, UCommandSender* Sender,
                                      UBanDatabase* DB,
                                      const FString& PrimaryUid,
                                      const TArray<FString>& LinkedUids)
    {
        if (!DB) return;

        // Remove all explicitly linked UIDs.
        for (const FString& LinkedUid : LinkedUids)
        {
            FBanEntry LinkedRecord;
            if (DB->RemoveBanByUid(LinkedUid, LinkedRecord))
            {
                FBanDiscordNotifier::NotifyBanRemoved(
                    LinkedUid, LinkedRecord.PlayerName,
                    Sender ? Sender->GetSenderName() : TEXT("console"));
                if (Sender)
                    Sender->SendChatMessage(
                        FString::Printf(TEXT("[BanChatCommands] Also removed linked ban %s."), *LinkedUid),
                        FLinearColor::Green);
            }
        }

        // Also check the session registry for counterparts that were never linked.
        UWorld* World = Ctx ? Ctx->GetWorld() : nullptr;
        UGameInstance* GI = World ? World->GetGameInstance() : nullptr;
        UPlayerSessionRegistry* Registry = GI ? GI->GetSubsystem<UPlayerSessionRegistry>() : nullptr;
        if (!Registry) return;

        FString Platform, RawId;
        UBanDatabase::ParseUid(PrimaryUid, Platform, RawId);

        if (Platform == TEXT("EOS"))
        {
            FPlayerSessionRecord Rec;
            if (Registry->FindByUid(PrimaryUid, Rec) && !Rec.IpAddress.IsEmpty())
            {
                const FString IpUid = UBanDatabase::MakeUid(TEXT("IP"), Rec.IpAddress);
                FBanEntry IpRecord;
                if (!LinkedUids.Contains(IpUid) && DB->RemoveBanByUid(IpUid, IpRecord))
                {
                    FBanDiscordNotifier::NotifyBanRemoved(
                        IpUid, IpRecord.PlayerName,
                        Sender ? Sender->GetSenderName() : TEXT("console"));
                    if (Sender)
                        Sender->SendChatMessage(
                            FString::Printf(TEXT("[BanChatCommands] Also removed IP ban for %s."),
                                *Rec.IpAddress),
                            FLinearColor::Green);
                }
            }
        }
        else if (Platform == TEXT("IP"))
        {
            TArray<FPlayerSessionRecord> Records = Registry->FindByIp(RawId);
            for (const FPlayerSessionRecord& Rec : Records)
            {
                if (Rec.Uid.IsEmpty()) continue;
                FBanEntry EosRecord;
                if (!LinkedUids.Contains(Rec.Uid) && DB->RemoveBanByUid(Rec.Uid, EosRecord))
                {
                    FBanDiscordNotifier::NotifyBanRemoved(
                        Rec.Uid, EosRecord.PlayerName,
                        Sender ? Sender->GetSenderName() : TEXT("console"));
                    if (Sender)
                        Sender->SendChatMessage(
                            FString::Printf(TEXT("[BanChatCommands] Also removed EOS ban for %s (%s)."),
                                *Rec.DisplayName, *Rec.Uid),
                            FLinearColor::Green);
                }
            }
        }
    }

    /**
     * Shared ban logic used by both /ban and /tempban.
     * AdminUid is the compound UID of the issuing admin (e.g. "EOS:xxx"), used for
     * rate-limiting so two admins with the same display name don't share a bucket.
     * BannedBy is the human-readable name stored in the ban record.
     */
    static EExecutionStatus DoBan(UObject* Ctx, UCommandSender* Sender,
                                  const FString& Uid, const FString& DisplayName,
                                  int32 DurationMinutes, const FString& Reason,
                                  const FString& BannedBy, const FString& AdminUid)
    {
        UBanDatabase* DB = GetDB(Ctx);
        if (!DB)
        {
            Sender->SendChatMessage(TEXT("[BanChatCommands] UBanDatabase unavailable."), FLinearColor::Red);
            return EExecutionStatus::UNCOMPLETED;
        }

        // Admin rate-limit check, keyed by UID so that display-name changes
        // and same-name admins each get their own independent bucket.
        {
            // Console senders have no UID; fall back to display name (console is
            // never blocked by IsBanRateLimited, but provide a stable key anyway).
            const FString RateLimitKey = AdminUid.IsEmpty()
                ? (BannedBy.IsEmpty() ? TEXT("console") : BannedBy)
                : AdminUid;
            if (IsBanRateLimited(Sender, RateLimitKey))
                return EExecutionStatus::UNCOMPLETED;
        }

        FString Platform, RawId;
        UBanDatabase::ParseUid(Uid, Platform, RawId);

        FBanEntry Entry;
        Entry.Uid        = Uid;
        Entry.PlayerUID  = RawId;
        Entry.Platform   = Platform;
        Entry.PlayerName = DisplayName;
        Entry.Reason     = Reason;
        Entry.BannedBy   = BannedBy;
        const FDateTime BanCmdNow = FDateTime::UtcNow();
        Entry.BanDate    = BanCmdNow;

        if (DurationMinutes <= 0)
        {
            Entry.bIsPermanent = true;
            Entry.ExpireDate   = FDateTime(0);
        }
        else
        {
            Entry.bIsPermanent = false;
            Entry.ExpireDate   = BanCmdNow + FTimespan::FromMinutes(DurationMinutes);
        }

        const FString DurStr = FormatDuration(DurationMinutes);

        // For temporary bans, use AddBanSkipIfPermanentExists to prevent a
        // /tempban from silently downgrading an existing permanent ban.
        bool bSkippedPerm = false;
        const bool bBanAdded = Entry.bIsPermanent
            ? DB->AddBan(Entry)
            : DB->AddBanSkipIfPermanentExists(Entry, bSkippedPerm);

        if (bSkippedPerm)
        {
            Sender->SendChatMessage(
                FString::Printf(TEXT("[BanChatCommands] '%s' already has a permanent ban — temp ban not applied."),
                    *DisplayName),
                FLinearColor::Yellow);
            return EExecutionStatus::UNCOMPLETED;
        }

        if (bBanAdded)
        {
            Sender->SendChatMessage(
                FString::Printf(TEXT("[BanChatCommands] Banned '%s' (%s: %s) %s — reason: %s"),
                    *DisplayName, *Platform, *RawId, *DurStr, *Reason),
                FLinearColor::Green);

            // Kick immediately if the player is currently connected.
            UWorld* World = Ctx ? Ctx->GetWorld() : nullptr;
            UBanEnforcer::KickConnectedPlayer(World, Uid, Entry.GetKickMessage());

            // Also ban the counterpart identifier (IP↔EOS) so no identity escapes.
            AddCounterpartBans(Ctx, Sender, Uid, DisplayName, DurationMinutes, Reason, BannedBy);

            // Write to the audit log so this action is visible alongside REST/Discord bans.
            if (UGameInstance* GI = World ? World->GetGameInstance() : nullptr)
                if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
                    AuditLog->LogAction(
                        DurationMinutes > 0 ? TEXT("tempban") : TEXT("ban"),
                        Uid, DisplayName, AdminUid, BannedBy, Reason);

            // Notify the webhook feed so in-game bans appear in the Discord ban log.
            FBanDiscordNotifier::NotifyBanCreated(Entry);

            return EExecutionStatus::COMPLETED;
        }

        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] Failed to ban %s '%s'."), *Platform, *RawId),
            FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    /**
     * Validates and normalises a compound UID argument entered by the user.
     *
     * Accepts:
     *   "EOS:<32-hex>"  → returned with lowercase hex part
     *   "<32-hex>"      → "EOS:" prefix added automatically
     *   "IP:<address>"  → IP ban UID (IPv4 or IPv6)
     *
     * On failure, sends an error to the sender and returns false.
     */
    static bool ParseAndNormaliseUidArg(UCommandSender* Sender,
                                        const FString& Arg,
                                        FString& OutUid)
    {
        // Try to parse an explicit compound UID supplied by the user (e.g. "EOS:xxx").
        FString Platform, RawId;
        UBanDatabase::ParseUid(Arg, Platform, RawId);

        if (Platform == TEXT("EOS") && IsValidEOSPUID(RawId))
        {
            OutUid = UBanDatabase::MakeUid(TEXT("EOS"), RawId.ToLower());
            return true;
        }

        if (Platform == TEXT("IP") && !RawId.IsEmpty())
        {
            OutUid = UBanDatabase::MakeUid(TEXT("IP"), RawId);
            return true;
        }

        // Accept raw EOS PUID without prefix.
        if (IsValidEOSPUID(Arg))
        {
            OutUid = UBanDatabase::MakeUid(TEXT("EOS"), Arg.ToLower());
            return true;
        }

        if (Sender)
        {
            Sender->SendChatMessage(
                FString::Printf(TEXT("[BanChatCommands] '%s' is not a valid compound UID "
                    "(EOS:<32hex> or IP:<address>)."), *Arg),
                FLinearColor::Red);
        }
        return false;
    }

    /**
     * Check whether the command sender is allowed to run moderator commands.
     *
     * Console senders are always permitted.  Player senders must have their EOS
     * PUID listed in either AdminEosPUIDs or ModeratorEosPUIDs.
     */
    static bool IsModeratorSender(UCommandSender* Sender, FString& OutUid)
    {
        if (!Sender) return false; // null sender — deny to fail safely
        if (!Sender->IsPlayerSender())
        {
            OutUid.Reset();
            return true;
        }

        APlayerController* PC = Cast<APlayerController>(Sender->GetPlayer());
        if (PC && PC->PlayerState)
        {
            const FUniqueNetIdRepl& UniqueId = PC->PlayerState->GetUniqueId();
            if (UniqueId.IsValid() && UniqueId.GetType() != FName(TEXT("NONE")))
            {
                OutUid = UBanDatabase::MakeUid(TEXT("EOS"), UniqueId.ToString().ToLower());
            }
            else
            {
                const FString EosPuid = UBanEnforcer::ExtractEosPuidFromConnectionUrl(PC);
                if (!EosPuid.IsEmpty())
                    OutUid = UBanDatabase::MakeUid(TEXT("EOS"), EosPuid);
            }
        }

        const UBanChatCommandsConfig* Cfg = UBanChatCommandsConfig::Get();
        if (!Cfg || !Cfg->IsModeratorUid(OutUid))
        {
            Sender->SendChatMessage(
                TEXT("[BanChatCommands] You do not have permission to use this command."),
                FLinearColor::Red);
            return false;
        }
        return true;
    }

    /**
     * Parse a duration string into a number of minutes.
     *
     * Accepts:
     *   - Bare integers       → treated as minutes (e.g. "60")
     *   - Shorthand strings   → combinations of d/h/m suffixes
     *     (e.g. "30m", "1h", "2h30m", "1d", "7d", "1d12h")
     *
     * Returns -1 if the format is invalid.
     */
    static int32 ParseDurationMinutes(const FString& DurationStr)
    {
        if (DurationStr.IsEmpty()) return -1;

        // Named constants for unit-to-minute conversions.
        static constexpr int64 MinutesPerHour = 60;
        static constexpr int64 MinutesPerDay  = 1440;  // 24 * 60
        static constexpr int64 MinutesPerWeek = 10080; // 7 * 24 * 60

        // Bare integer — legacy format, treat as minutes.
        // Use Atoi64 so values above INT32_MAX are caught rather than silently
        // wrapping; reject values outside the representable int32 range.
        if (DurationStr.IsNumeric())
        {
            const int64 Raw = FCString::Atoi64(*DurationStr);
            if (Raw <= 0 || Raw > static_cast<int64>(INT32_MAX)) return -1;
            return static_cast<int32>(Raw);
        }

        int64 Total   = 0;
        bool  bHadToken = false;
        const TCHAR* p = *DurationStr;

        while (*p)
        {
            if (!FChar::IsDigit(*p)) return -1;

            int64 Num = 0;
            while (*p && FChar::IsDigit(*p))
            {
                const int64 Digit = static_cast<int64>(*p - TEXT('0'));
                // Guard against int64 overflow for pathologically large digit strings.
                if (Num > (INT64_MAX - Digit) / 10) return -1;
                Num = Num * 10 + Digit;
                ++p;
            }

            if (!*p) return -1; // digits without a trailing unit

            const TCHAR Unit = FChar::ToLower(*p);
            ++p;

            if      (Unit == TEXT('w'))
            {
                // Guard: Num * MinutesPerWeek must not overflow int64, and adding to Total must not overflow.
                if (Num > INT64_MAX / MinutesPerWeek) return -1;
                const int64 Product = Num * MinutesPerWeek;
                if (Total > INT64_MAX - Product) return -1;
                Total += Product;
            }
            else if (Unit == TEXT('d'))
            {
                if (Num > INT64_MAX / MinutesPerDay) return -1;
                const int64 Product = Num * MinutesPerDay;
                if (Total > INT64_MAX - Product) return -1;
                Total += Product;
            }
            else if (Unit == TEXT('h'))
            {
                if (Num > INT64_MAX / MinutesPerHour) return -1;
                const int64 Product = Num * MinutesPerHour;
                if (Total > INT64_MAX - Product) return -1;
                Total += Product;
            }
            else if (Unit == TEXT('m'))
            {
                if (Total > INT64_MAX - Num) return -1;
                Total += Num;
            }
            else return -1;

            bHadToken = true;
        }

        if (!bHadToken || Total <= 0) return -1;
        // Reject durations that exceed the int32 range rather than silently truncating.
        if (Total > static_cast<int64>(INT32_MAX)) return -1;
        return static_cast<int32>(Total);
    }

    /**
     * Per-player command cooldown tracker.
     * Maps "commandName:uid" → last-used FDateTime.
     * Cleaned up lazily; not persisted across restarts (intentional).
     *
     * THREADING: Accessed exclusively from the game thread (SML dispatches
     * ExecuteCommand_Implementation on the game thread).  Do NOT touch this
     * map from any other thread.
     */
    static TMap<FString, FDateTime> CommandCooldowns;

    /**
     * Returns true if the sender is on cooldown for the given command.
     * Admin senders are never rate-limited.
     * Updates the cooldown timestamp when returning false (i.e. the command may proceed).
     * When returning true (on cooldown), sets *OutRemainingSecs to the number of whole
     * seconds the caller must still wait before the cooldown expires.
     */
    static bool IsOnCooldown(UCommandSender* Sender, const FString& CommandName,
                             int32 CooldownSeconds, const FString& SenderUid,
                             int32* OutRemainingSecs = nullptr)
    {
        // CommandCooldowns is game-thread-only; catch any future SML change early.
        check(IsInGameThread());
        if (CooldownSeconds <= 0) return false;
        if (!Sender->IsPlayerSender()) return false; // console is never throttled

        // Honour the documented contract: admin player-senders bypass this cooldown.
        const UBanChatCommandsConfig* Cfg = UBanChatCommandsConfig::Get();
        if (Cfg && Cfg->IsAdminUid(SenderUid)) return false;

        const FString Key = CommandName + TEXT(":") + SenderUid;
        const FDateTime Now = FDateTime::UtcNow();

        // Prune stale entries at most once per minute so this map-sweep doesn't
        // become O(players × commands) on every command invocation.  A 1-hour
        // cutoff is still used as the expiry threshold so that a player with a
        // long-cooldown command is never evicted before their actual window.
        static FDateTime LastPruneTime;
        if ((Now - LastPruneTime).GetTotalSeconds() >= 60.0)
        {
            static const FTimespan PruneCutOff = FTimespan::FromHours(1);
            for (auto It = CommandCooldowns.CreateIterator(); It; ++It)
            {
                if ((Now - It.Value()) > PruneCutOff)
                    It.RemoveCurrent();
            }
            LastPruneTime = Now;
        }

        if (const FDateTime* Last = CommandCooldowns.Find(Key))
        {
            const double ElapsedSecs = (Now - *Last).GetTotalSeconds();
            if (ElapsedSecs < static_cast<double>(CooldownSeconds))
            {
                if (OutRemainingSecs)
                    *OutRemainingSecs = FMath::Max(1, FMath::CeilToInt(CooldownSeconds - ElapsedSecs));
                return true;
            }
        }
        CommandCooldowns.Add(Key, Now);
        return false;
    }

    /**
     * Admin ban rate-limit tracker.
     * Maps AdminUid → array of timestamps of recent bans.
     *
     * THREADING: Accessed exclusively from the game thread.
     * Do NOT touch this map from any other thread.
     */
    static TMap<FString, TArray<FDateTime>> AdminBanTimestamps;

    /**
     * Returns true if the admin has exceeded the configured ban rate limit.
     * Sends a warning message to Sender and returns true when blocked.
     */
    static bool IsBanRateLimited(UCommandSender* Sender, const FString& AdminUid)
    {
        // AdminBanTimestamps is game-thread-only; catch any future SML change early.
        check(IsInGameThread());
        const UBanChatCommandsConfig* Cfg = UBanChatCommandsConfig::Get();
        if (!Cfg || Cfg->AdminBanRateLimitCount <= 0) return false;

        const int32 LimitCount = Cfg->AdminBanRateLimitCount;
        const int32 LimitMins  = FMath::Max(1, Cfg->AdminBanRateLimitMinutes);
        const FDateTime Now    = FDateTime::UtcNow();
        const FTimespan Window = FTimespan::FromMinutes(LimitMins);

        // Prune stale timestamps and empty entries first, before acquiring a
        // reference via FindOrAdd — iterating the map after FindOrAdd could
        // invalidate the reference if RemoveCurrent() removes that entry.
        for (auto It = AdminBanTimestamps.CreateIterator(); It; ++It)
        {
            It.Value().RemoveAll([&Now, &Window](const FDateTime& T){ return (Now - T) > Window; });
            if (It.Value().IsEmpty())
                It.RemoveCurrent();
        }

        TArray<FDateTime>& Timestamps = AdminBanTimestamps.FindOrAdd(AdminUid);

        if (Timestamps.Num() >= LimitCount)
        {
            if (Sender)
            {
                Sender->SendChatMessage(
                    FString::Printf(TEXT("[BanChatCommands] Rate limit: you have issued %d bans in the past %d minutes. Please wait before banning again."),
                        Timestamps.Num(), LimitMins),
                    FLinearColor::Yellow);
            }
            return true;
        }

        Timestamps.Add(Now);
        return false;
    }

    /**
     * Send a chat message to a specific connected player identified by compound UID.
     * No-op when no matching player is found online.
     */
    static void SendChatMessageToUid(UWorld* World, const FString& Uid, const FString& Message)
    {
        if (!World || Uid.IsEmpty() || Message.IsEmpty()) return;
        for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
        {
            APlayerController* PC = It->Get();
            if (!PC || !PC->PlayerState) continue;

            FString ConnectedUid;
            const FUniqueNetIdRepl& UniqueId = PC->PlayerState->GetUniqueId();
            if (UniqueId.IsValid() && UniqueId.GetType() != FName(TEXT("NONE")))
            {
                ConnectedUid = UBanDatabase::MakeUid(TEXT("EOS"), UniqueId.ToString().ToLower());
            }
            else
            {
                const FString Puid = UBanEnforcer::ExtractEosPuidFromConnectionUrl(PC);
                if (!Puid.IsEmpty())
                    ConnectedUid = UBanDatabase::MakeUid(TEXT("EOS"), Puid);
            }

            if (!ConnectedUid.IsEmpty() && ConnectedUid.Equals(Uid, ESearchCase::IgnoreCase))
            {
                PC->ClientMessage(Message);
                return;
            }
        }
    }

    /** Escape a string for embedding in a JSON string literal.
     *  Handles control characters and lone UTF-16 surrogates (U+D800–U+DFFF)
     *  so the output is always well-formed JSON. */
    static FString JsonEscape(const FString& S)
    {
        FString Out;
        Out.Reserve(S.Len() + 8);
        for (int32 i = 0; i < S.Len(); ++i)
        {
            const TCHAR C = S[i];
            switch (C)
            {
            case TEXT('"'):  Out += TEXT("\\\""); break;
            case TEXT('\\'): Out += TEXT("\\\\"); break;
            case TEXT('\n'): Out += TEXT("\\n");  break;
            case TEXT('\r'): Out += TEXT("\\r");  break;
            case TEXT('\t'): Out += TEXT("\\t");  break;
            default:
                // RFC 8259 §7: control characters U+0000–U+001F must be escaped.
                if (C < 0x20)
                    Out += FString::Printf(TEXT("\\u%04x"), static_cast<uint32>(C));
                // RFC 8259 §7: lone surrogate code-points U+D800–U+DFFF produce
                // invalid JSON.  Replace with U+FFFD (replacement character) so the
                // output is always valid JSON regardless of the player name content.
                else if (C >= 0xD800 && C <= 0xDFFF)
                    Out += TEXT("\uFFFD");
                else
                    Out += C;
                break;
            }
        }
        return Out;
    }

    /** Escape Discord markdown special characters so that player-supplied
     *  strings rendered in embed field values cannot inject bold, italic,
     *  code or link formatting. */
    static FString EscapeMarkdown(const FString& Text)
    {
        FString Out;
        Out.Reserve(Text.Len() + 8);
        for (TCHAR C : Text)
        {
            switch (C)
            {
            case TEXT('*'): case TEXT('_'): case TEXT('`'): case TEXT('~'):
            case TEXT('|'): case TEXT('>'): case TEXT('\\'): case TEXT('['):
            case TEXT(']'): case TEXT('#'):
                Out += TEXT('\\');
                break;
            default:
                break;
            }
            Out += C;
        }
        return Out;
    }
} // namespace BanChat

// ─────────────────────────────────────────────────────────────────────────────
//  ALinkBansChatCommand  — /linkbans
// ─────────────────────────────────────────────────────────────────────────────

ALinkBansChatCommand::ALinkBansChatCommand()
{
    CommandName          = TEXT("linkbans");
    MinNumberOfArguments = 2;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "LinkBansUsage",
        "/linkbans <UID1> <UID2>");
}

EExecutionStatus ALinkBansChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminUid;
    if (!BanChat::IsAdminSender(Sender, AdminUid))
        return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    FString UidA, UidB;
    if (!BanChat::ParseAndNormaliseUidArg(Sender, Arguments[0], UidA))
        return EExecutionStatus::BAD_ARGUMENTS;
    if (!BanChat::ParseAndNormaliseUidArg(Sender, Arguments[1], UidB))
        return EExecutionStatus::BAD_ARGUMENTS;

    if (UidA.Equals(UidB, ESearchCase::IgnoreCase))
    {
        Sender->SendChatMessage(
            TEXT("[BanChatCommands] Cannot link a UID to itself."),
            FLinearColor::Red);
        return EExecutionStatus::BAD_ARGUMENTS;
    }

    UBanDatabase* DB = BanChat::GetDB(this);
    if (!DB)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] UBanDatabase unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    bool bPartialOnly = false;
    if (DB->LinkBans(UidA, UidB, &bPartialOnly))
    {
        if (bPartialOnly)
        {
            // One UID had a ban record; the other did not — one-sided link stored.
            Sender->SendChatMessage(
                FString::Printf(TEXT("[BanChatCommands] Warning: only one of '%s' / '%s' has a ban "
                    "record; a one-sided link was saved. Create a ban for the missing UID and run "
                    "/linkbans again to complete the cross-link."), *UidA, *UidB),
                FLinearColor::Yellow);
        }
        else
        {
            Sender->SendChatMessage(
                FString::Printf(TEXT("[BanChatCommands] Linked %s ↔ %s. "
                    "A ban on either identity will now block both."), *UidA, *UidB),
                FLinearColor::Green);
        }

        UWorld* LWorld = GetWorld();
        UGameInstance* LGI = LWorld ? LWorld->GetGameInstance() : nullptr;
        if (UBanAuditLog* AuditLog = LGI ? LGI->GetSubsystem<UBanAuditLog>() : nullptr)
            AuditLog->LogAction(TEXT("linkbans"), UidA, UidA,
                                AdminUid, Sender->GetSenderName(),
                                FString::Printf(TEXT("%s <-> %s"), *UidA, *UidB));

        return EExecutionStatus::COMPLETED;
    }

    Sender->SendChatMessage(
        FString::Printf(TEXT("[BanChatCommands] Could not link — no ban record found for '%s' or '%s'. "
            "Both UIDs must have existing ban records before they can be linked."),
            *UidA, *UidB),
        FLinearColor::Red);
    return EExecutionStatus::UNCOMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  AUnlinkBansChatCommand  — /unlinkbans
// ─────────────────────────────────────────────────────────────────────────────

AUnlinkBansChatCommand::AUnlinkBansChatCommand()
{
    CommandName          = TEXT("unlinkbans");
    MinNumberOfArguments = 2;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "UnlinkBansUsage",
        "/unlinkbans <UID1> <UID2>");
}

EExecutionStatus AUnlinkBansChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminUid;
    if (!BanChat::IsAdminSender(Sender, AdminUid))
        return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    FString UidA, UidB;
    if (!BanChat::ParseAndNormaliseUidArg(Sender, Arguments[0], UidA))
        return EExecutionStatus::BAD_ARGUMENTS;
    if (!BanChat::ParseAndNormaliseUidArg(Sender, Arguments[1], UidB))
        return EExecutionStatus::BAD_ARGUMENTS;

    UBanDatabase* DB = BanChat::GetDB(this);
    if (!DB)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] UBanDatabase unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    if (DB->UnlinkBans(UidA, UidB))
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] Removed link between %s and %s."), *UidA, *UidB),
            FLinearColor::Green);

        UWorld* ULWorld = GetWorld();
        UGameInstance* ULGI = ULWorld ? ULWorld->GetGameInstance() : nullptr;
        if (UBanAuditLog* AuditLog = ULGI ? ULGI->GetSubsystem<UBanAuditLog>() : nullptr)
            AuditLog->LogAction(TEXT("unlinkbans"), UidA, UidA,
                                AdminUid, Sender->GetSenderName(),
                                FString::Printf(TEXT("%s <-> %s"), *UidA, *UidB));

        return EExecutionStatus::COMPLETED;
    }

    Sender->SendChatMessage(
        FString::Printf(TEXT("[BanChatCommands] No link found between %s and %s."), *UidA, *UidB),
        FLinearColor::Yellow);
    return EExecutionStatus::UNCOMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  ABanChatCommand  — /ban
// ─────────────────────────────────────────────────────────────────────────────

ABanChatCommand::ABanChatCommand()
{
    CommandName          = TEXT("ban");
    MinNumberOfArguments = 1;
    bOnlyUsableByPlayer  = false; // allow console too
    Usage = NSLOCTEXT("BanChatCommands", "BanUsage",
        "/ban <player|PUID|IP:address> [reason...]");
}

EExecutionStatus ABanChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminId;
    if (!BanChat::IsAdminSender(Sender, AdminId))
        return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    const FString& Arg = Arguments[0];
    FString Uid, DisplayName;
    if (!BanChat::ResolveTarget(this, Sender, Arg, Uid, DisplayName))
        return EExecutionStatus::BAD_ARGUMENTS;

    const FString Reason = Arguments.Num() > 1
        ? BanChat::JoinArgs(Arguments, 1)
        : TEXT("Banned by server administrator");

    const FString BannedBy = Sender->GetSenderName();
    return BanChat::DoBan(this, Sender, Uid, DisplayName, 0, Reason, BannedBy, AdminId);
}

// ─────────────────────────────────────────────────────────────────────────────
//  ATempBanChatCommand  — /tempban
// ─────────────────────────────────────────────────────────────────────────────

ATempBanChatCommand::ATempBanChatCommand()
{
    CommandName          = TEXT("tempban");
    MinNumberOfArguments = 2;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "TempBanUsage",
        "/tempban <player|PUID|IP:address> <duration> [reason...]\n"
        "  duration: minutes (e.g. 60) or shorthand (e.g. 30m, 1h, 2h30m, 1d, 7d, 1d12h)");
}

EExecutionStatus ATempBanChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminId;
    if (!BanChat::IsAdminSender(Sender, AdminId))
        return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    FString Uid, DisplayName;
    if (!BanChat::ResolveTarget(this, Sender, Arguments[0], Uid, DisplayName))
        return EExecutionStatus::BAD_ARGUMENTS;

    const int32 DurationMinutes = BanChat::ParseDurationMinutes(Arguments[1]);
    if (DurationMinutes <= 0)
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] Duration must be positive (e.g. 60) or shorthand (e.g. 30m, 1h, 2h30m, 1d, 7d, 1d12h). Got: '%s'."),
                *Arguments[1]),
            FLinearColor::Red);
        return EExecutionStatus::BAD_ARGUMENTS;
    }

    const FString Reason   = Arguments.Num() > 2
        ? BanChat::JoinArgs(Arguments, 2)
        : TEXT("Temporarily banned by server administrator");
    const FString BannedBy = Sender->GetSenderName();

    return BanChat::DoBan(this, Sender, Uid, DisplayName, DurationMinutes, Reason, BannedBy, AdminId);
}

// ─────────────────────────────────────────────────────────────────────────────
//  AUnbanChatCommand  — /unban
// ─────────────────────────────────────────────────────────────────────────────

AUnbanChatCommand::AUnbanChatCommand()
{
    CommandName          = TEXT("unban");
    MinNumberOfArguments = 1;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "UnbanUsage",
        "/unban <PUID|IP:address>");
}

EExecutionStatus AUnbanChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminId;
    if (!BanChat::IsAdminSender(Sender, AdminId))
        return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    const FString& Arg = Arguments[0];

    // Build the compound UID — accept EOS PUID or IP:<address> (exact ID required for unban).
    FString Uid;
    if (BanChat::IsValidEOSPUID(Arg))
    {
        Uid = UBanDatabase::MakeUid(TEXT("EOS"), Arg.ToLower());
    }
    else
    {
        FString Platform, RawId;
        UBanDatabase::ParseUid(Arg, Platform, RawId);
        if (Platform == TEXT("IP") && !RawId.IsEmpty())
        {
            Uid = UBanDatabase::MakeUid(TEXT("IP"), RawId);
        }
        else if (Platform == TEXT("EOS") && BanChat::IsValidEOSPUID(RawId))
        {
            Uid = UBanDatabase::MakeUid(TEXT("EOS"), RawId.ToLower());
        }
        else
        {
            Sender->SendChatMessage(
                FString::Printf(TEXT("[BanChatCommands] '%s' is not a valid "
                    "UID. Use an EOS PUID (32 hex chars) or IP:<address>."), *Arg),
                FLinearColor::Red);
            return EExecutionStatus::BAD_ARGUMENTS;
        }
    }

    UBanDatabase* DB = BanChat::GetDB(this);
    if (!DB)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] UBanDatabase unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    // Atomically look up and remove the ban in a single lock acquisition so
    // that the BanEnforcer expiry thread cannot delete or modify the record
    // between the lookup and the removal (TOCTOU fix).
    FBanEntry BanRecord;
    const bool bHadRecord = DB->RemoveBanByUid(Uid, BanRecord);

    if (bHadRecord)
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] Removed ban for %s."), *Uid),
            FLinearColor::Green);

        // Also remove every counterpart ban (linked UIDs + session registry lookup).
        BanChat::RemoveCounterpartBans(this, Sender, DB, Uid, BanRecord.LinkedUids);

        // Notify Discord moderation-log channel of the unban.
        FBanDiscordNotifier::NotifyBanRemoved(Uid, BanRecord.PlayerName, Sender->GetSenderName());

        // Write to the audit log.
        {
            UWorld* W = GetWorld();
            UGameInstance* GI = W ? W->GetGameInstance() : nullptr;
            if (UBanAuditLog* AuditLog = GI ? GI->GetSubsystem<UBanAuditLog>() : nullptr)
                AuditLog->LogAction(TEXT("unban"), Uid,
                    BanRecord.PlayerName,
                    AdminId, Sender->GetSenderName(), TEXT(""));
        }

        return EExecutionStatus::COMPLETED;
    }

    Sender->SendChatMessage(
        FString::Printf(TEXT("[BanChatCommands] No active ban found for %s."), *Uid),
        FLinearColor::Yellow);
    return EExecutionStatus::UNCOMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  AUnbanNameChatCommand  — /unbanname
// ─────────────────────────────────────────────────────────────────────────────

AUnbanNameChatCommand::AUnbanNameChatCommand()
{
    CommandName          = TEXT("unbanname");
    MinNumberOfArguments = 1;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "UnbanNameUsage",
        "/unbanname <name_substring>");
}

EExecutionStatus AUnbanNameChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminId;
    if (!BanChat::IsAdminSender(Sender, AdminId))
        return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    UWorld* World = GetWorld();
    if (!World) return EExecutionStatus::UNCOMPLETED;
    UGameInstance* GI = World->GetGameInstance();
    if (!GI) return EExecutionStatus::UNCOMPLETED;

    UPlayerSessionRegistry* Registry = GI->GetSubsystem<UPlayerSessionRegistry>();
    if (!Registry)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] PlayerSessionRegistry unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    UBanDatabase* DB = BanChat::GetDB(this);
    if (!DB)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] UBanDatabase unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    const FString NameArg = Arguments[0];
    TArray<FPlayerSessionRecord> Results = Registry->FindByName(NameArg);

    if (Results.IsEmpty())
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] No session history found for '%s'. "
                "The player must have connected at least once for /unbanname to work.  "
                "Use /unban <PUID> to unban a player directly."), *NameArg),
            FLinearColor::Red);
        return EExecutionStatus::BAD_ARGUMENTS;
    }

    if (Results.Num() > 1)
    {
        TArray<FString> Descriptions;
        for (const FPlayerSessionRecord& R : Results)
            Descriptions.Add(FString::Printf(TEXT("\"%s\" (%s)"), *R.DisplayName, *R.Uid));
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] Ambiguous name '%s' — %d matches: %s.  "
                "Use a more specific substring."),
                *NameArg, Results.Num(), *FString::Join(Descriptions, TEXT(", "))),
            FLinearColor::Yellow);
        return EExecutionStatus::BAD_ARGUMENTS;
    }

    const FPlayerSessionRecord& Rec = Results[0];
    bool bAnyRemoved = false;

    // Remove the EOS PUID ban, capturing the entry so LinkedUids can be
    // consulted to remove every explicitly linked counterpart ban as well.
    FBanEntry EosBanRecord;
    if (DB->RemoveBanByUid(Rec.Uid, EosBanRecord))
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] Removed EOS ban for '%s' (%s)."),
                *Rec.DisplayName, *Rec.Uid),
            FLinearColor::Green);
        bAnyRemoved = true;
        if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
            AuditLog->LogAction(TEXT("unban"), Rec.Uid, Rec.DisplayName,
                AdminId, Sender->GetSenderName(), TEXT(""));

        // Remove every counterpart ban (linked UIDs + session-registry IP
        // lookup) so that all identities for this player are unblocked in one
        // command.  This matches the behaviour of /unban, which was already
        // calling RemoveCounterpartBans but /unbanname was not.
        BanChat::RemoveCounterpartBans(this, Sender, DB, Rec.Uid, EosBanRecord.LinkedUids);

        // Notify Discord moderation-log channel of the unban.
        FBanDiscordNotifier::NotifyBanRemoved(Rec.Uid, Rec.DisplayName, Sender->GetSenderName());
    }
    else
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] No active EOS ban found for '%s' (%s)."),
                *Rec.DisplayName, *Rec.Uid),
            FLinearColor::Yellow);
    }

    return bAnyRemoved ? EExecutionStatus::COMPLETED : EExecutionStatus::UNCOMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  ABanCheckChatCommand  — /bancheck
// ─────────────────────────────────────────────────────────────────────────────

ABanCheckChatCommand::ABanCheckChatCommand()
{
    CommandName          = TEXT("bancheck");
    MinNumberOfArguments = 1;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "BanCheckUsage",
        "/bancheck <player|PUID|IP:address>");
}

EExecutionStatus ABanCheckChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminId;
    if (!BanChat::IsAdminSender(Sender, AdminId))
        return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    // Apply per-command cooldown for non-console senders.
    {
        const UBanChatCommandsConfig* CoolCfg = UBanChatCommandsConfig::Get();
        const int32 CoolSecs = CoolCfg ? CoolCfg->WarningCheckCooldownSeconds : 0;
        int32 RemainingCoolSecs = 0;
        if (BanChat::IsOnCooldown(Sender, TEXT("bancheck"), CoolSecs, AdminId, &RemainingCoolSecs))
        {
            Sender->SendChatMessage(
                FString::Printf(TEXT("[BanChatCommands] Please wait %d second(s) before using /bancheck again."), RemainingCoolSecs),
                FLinearColor::Yellow);
            return EExecutionStatus::UNCOMPLETED;
        }
    }

    FString Uid, DisplayName;
    if (!BanChat::ResolveTarget(this, Sender, Arguments[0], Uid, DisplayName))
        return EExecutionStatus::BAD_ARGUMENTS;

    UBanDatabase* DB = BanChat::GetDB(this);
    if (!DB)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] UBanDatabase unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    FBanEntry Entry;
    if (DB->IsCurrentlyBannedByAnyId(Uid, Entry))
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] BANNED — %s (%s)  "
                "Reason: %s  Expires: %s  Banned by: %s"),
                *DisplayName, *Uid,
                *Entry.Reason, *BanChat::FormatExpiry(Entry), *Entry.BannedBy),
            FLinearColor::Red);
        return EExecutionStatus::COMPLETED;
    }

    // Check whether there is an expired ban record.
    if (DB->GetBanByUid(Uid, Entry) && Entry.IsExpired())
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] Ban for %s has expired (will be pruned on next server tick)."), *Uid),
            FLinearColor::Yellow);
    }
    else
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] Not banned: %s"), *Uid),
            FLinearColor::White);
    }

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  ABanListChatCommand  — /banlist
// ─────────────────────────────────────────────────────────────────────────────

ABanListChatCommand::ABanListChatCommand()
{
    CommandName          = TEXT("banlist");
    MinNumberOfArguments = 0;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "BanListUsage", "/banlist [page]");
}

EExecutionStatus ABanListChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminId;
    if (!BanChat::IsAdminSender(Sender, AdminId))
        return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    UBanDatabase* DB = BanChat::GetDB(this);
    if (!DB)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] UBanDatabase unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    const TArray<FBanEntry> AllBans = DB->GetActiveBans();

    if (AllBans.IsEmpty())
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] No active bans."), FLinearColor::White);
        return EExecutionStatus::COMPLETED;
    }

    const int32 PageSize    = UBanChatCommandsConfig::Get()
        ? FMath::Clamp(UBanChatCommandsConfig::Get()->BanListPageSize, 1, 50)
        : 10;
    const int32 Page        = (Arguments.Num() > 0 && Arguments[0].IsNumeric()
                               && Arguments[0].Len() <= 9)
        ? FMath::Max(1, FCString::Atoi(*Arguments[0])) : 1;
    const int32 TotalPages  = FMath::DivideAndRoundUp(AllBans.Num(), PageSize);
    const int32 PageClamped = FMath::Clamp(Page, 1, TotalPages);
    const int32 Start       = (PageClamped - 1) * PageSize;
    const int32 End         = FMath::Min(Start + PageSize, AllBans.Num());

    Sender->SendChatMessage(
        FString::Printf(TEXT("[BanChatCommands] Active bans (%d total) — page %d/%d:"),
            AllBans.Num(), PageClamped, TotalPages),
        FLinearColor::White);

    for (int32 i = Start; i < End; ++i)
    {
        const FBanEntry& E = AllBans[i];
        Sender->SendChatMessage(
            FString::Printf(TEXT("  [%s] %s | %s | By: %s | Expires: %s"),
                *E.Platform, *E.PlayerUID,
                E.PlayerName.IsEmpty() ? TEXT("(unknown)") : *E.PlayerName,
                *E.BannedBy, *BanChat::FormatExpiry(E)),
            FLinearColor::White);
    }

    if (TotalPages > 1)
    {
        Sender->SendChatMessage(
            TEXT("[BanChatCommands] Use /banlist <page> to view more."),
            FLinearColor::White);
    }

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  AWhoAmIChatCommand  — /whoami
// ─────────────────────────────────────────────────────────────────────────────

AWhoAmIChatCommand::AWhoAmIChatCommand()
{
    CommandName          = TEXT("whoami");
    MinNumberOfArguments = 0;
    bOnlyUsableByPlayer  = true; // requires a player; no IDs for console
    Usage = NSLOCTEXT("BanChatCommands", "WhoAmIUsage", "/whoami");
}

EExecutionStatus AWhoAmIChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    APlayerController* PC = Cast<APlayerController>(Sender->GetPlayer());
    if (!PC || !PC->PlayerState)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] No player state available."),
            FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    const FUniqueNetIdRepl& UniqueId = PC->PlayerState->GetUniqueId();
    // Guard against NONE-type and use direct member accessors — NOT operator->
    // (see IsAdminSender for the full explanation on why operator-> crashes on
    // CSS DS with EOS V2 PUIDs).
    FString RawId;
    if (UniqueId.IsValid() && UniqueId.GetType() != FName(TEXT("NONE")))
    {
        // CSS DS exclusively assigns EOS PUIDs — always normalize to lowercase.
        RawId = UniqueId.ToString().ToLower();
    }
    else
    {
        // CSS DS 1.1.0 workaround: GetType()==NONE because EOS online subsystem
        // is offline (IsOnline=false).  The EOS PUID is still embedded in the
        // ClientIdentity URL option of the player's connection — use it.
        const FString EosPuid = UBanEnforcer::ExtractEosPuidFromConnectionUrl(PC);
        if (EosPuid.IsEmpty())
        {
            Sender->SendChatMessage(
                TEXT("[BanChatCommands] Could not resolve your platform identity. "
                     "Try again in a moment."),
                FLinearColor::Yellow);
            return EExecutionStatus::UNCOMPLETED;
        }
        RawId = EosPuid;
    }

    Sender->SendChatMessage(
        FString::Printf(TEXT("[BanChatCommands] Your EOS PUID: %s"), *RawId),
        FLinearColor::Green);

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  APlayerHistoryChatCommand  — /playerhistory
// ─────────────────────────────────────────────────────────────────────────────

APlayerHistoryChatCommand::APlayerHistoryChatCommand()
{
    CommandName          = TEXT("playerhistory");
    MinNumberOfArguments = 1;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "PlayerHistoryUsage",
        "/playerhistory <name_substring|UID|IP>");
}

EExecutionStatus APlayerHistoryChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminUid;
    if (!BanChat::IsAdminSender(Sender, AdminUid))
        return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    UWorld* World = GetWorld();
    if (!World) return EExecutionStatus::UNCOMPLETED;
    UGameInstance* GI = World->GetGameInstance();
    if (!GI) return EExecutionStatus::UNCOMPLETED;

    UPlayerSessionRegistry* Registry = GI->GetSubsystem<UPlayerSessionRegistry>();
    if (!Registry)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] PlayerSessionRegistry unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    const FString& Arg = Arguments[0];

    // Determine lookup mode: compound UID, IP address/prefix, or name substring.
    FString ParsePlatform, ParseRawId;
    UBanDatabase::ParseUid(Arg, ParsePlatform, ParseRawId);

    TArray<FPlayerSessionRecord> Results;
    if (ParsePlatform == TEXT("EOS") && BanChat::IsValidEOSPUID(ParseRawId))
    {
        // EOS:<puid>  — exact UID lookup.
        FPlayerSessionRecord Rec;
        if (Registry->FindByUid(UBanDatabase::MakeUid(TEXT("EOS"), ParseRawId.ToLower()), Rec))
            Results.Add(Rec);
        else
        {
            Sender->SendChatMessage(
                FString::Printf(TEXT("[BanChatCommands] No session history found for UID %s."),
                    *UBanDatabase::MakeUid(TEXT("EOS"), ParseRawId.ToLower())),
                FLinearColor::Yellow);
            return EExecutionStatus::COMPLETED;
        }
    }
    else if (BanChat::IsValidEOSPUID(Arg))
    {
        // Raw 32-hex PUID without prefix.
        FPlayerSessionRecord Rec;
        const FString SearchUid = UBanDatabase::MakeUid(TEXT("EOS"), Arg.ToLower());
        if (Registry->FindByUid(SearchUid, Rec))
            Results.Add(Rec);
        else
        {
            Sender->SendChatMessage(
                FString::Printf(TEXT("[BanChatCommands] No session history found for UID %s."), *SearchUid),
                FLinearColor::Yellow);
            return EExecutionStatus::COMPLETED;
        }
    }
    else if (ParsePlatform == TEXT("IP") || (ParsePlatform == TEXT("UNKNOWN") && Arg.Contains(TEXT("."))))
    {
        // IP:<addr>  or bare address substring (e.g. "192.168.1." for subnet search).
        const FString IpQuery = (ParsePlatform == TEXT("IP")) ? ParseRawId : Arg;
        Results = Registry->FindByIp(IpQuery);
        if (Results.IsEmpty())
        {
            Sender->SendChatMessage(
                FString::Printf(TEXT("[BanChatCommands] No session history found for IP '%s'."), *IpQuery),
                FLinearColor::Yellow);
            return EExecutionStatus::COMPLETED;
        }
    }
    else
    {
        // Display-name substring search.
        Results = Registry->FindByName(Arg);
        if (Results.IsEmpty())
        {
            Sender->SendChatMessage(
                FString::Printf(TEXT("[BanChatCommands] No session history found for name '%s'."), *Arg),
                FLinearColor::Yellow);
            return EExecutionStatus::COMPLETED;
        }
    }

    if (Results.Num() > MaxResults)
        Results.SetNum(MaxResults);

    Sender->SendChatMessage(
        FString::Printf(TEXT("[BanChatCommands] Session history for '%s' (%d result(s)):"), *Arg, Results.Num()),
        FLinearColor::White);

    UBanDatabase* DB = BanChat::GetDB(this);

    for (const FPlayerSessionRecord& Rec : Results)
    {
        FBanEntry BanEntry;
        const bool bBanned = DB && DB->IsCurrentlyBannedByAnyId(Rec.Uid, BanEntry);
        const FString BanStatus = bBanned
            ? FString::Printf(TEXT(" [BANNED: %s]"), *BanEntry.Reason)
            : TEXT("");

        Sender->SendChatMessage(
            FString::Printf(TEXT("  %s | \"%s\" | ip: %s | last seen: %s%s"),
                *Rec.Uid, *Rec.DisplayName,
                Rec.IpAddress.IsEmpty() ? TEXT("—") : *Rec.IpAddress,
                *Rec.LastSeen, *BanStatus),
            bBanned ? FLinearColor::Red : FLinearColor::White);
    }

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  ABanNameChatCommand  — /banname
// ─────────────────────────────────────────────────────────────────────────────

ABanNameChatCommand::ABanNameChatCommand()
{
    CommandName          = TEXT("banname");
    MinNumberOfArguments = 1;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "BanNameUsage",
        "/banname <name_substring> [reason...]");
}

EExecutionStatus ABanNameChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminId;
    if (!BanChat::IsAdminSender(Sender, AdminId))
        return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    UWorld* World = GetWorld();
    if (!World) return EExecutionStatus::UNCOMPLETED;
    UGameInstance* GI = World->GetGameInstance();
    if (!GI) return EExecutionStatus::UNCOMPLETED;

    UPlayerSessionRegistry* Registry = GI->GetSubsystem<UPlayerSessionRegistry>();
    if (!Registry)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] PlayerSessionRegistry unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    const FString NameArg  = Arguments[0];
    const FString Reason   = Arguments.Num() > 1
        ? BanChat::JoinArgs(Arguments, 1)
        : TEXT("Banned by server administrator");
    const FString BannedBy = Sender->GetSenderName();

    // Look up the player by display-name substring.  Works for offline players
    // as long as they connected at least once while the session registry was active.
    TArray<FPlayerSessionRecord> Results = Registry->FindByName(NameArg);

    if (Results.IsEmpty())
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] No session history found for '%s'. "
                "The player must have connected at least once for /banname to work.  "
                "Use /ban <PUID> to ban an unknown player directly."), *NameArg),
            FLinearColor::Red);
        return EExecutionStatus::BAD_ARGUMENTS;
    }

    if (Results.Num() > 1)
    {
        TArray<FString> Descriptions;
        for (const FPlayerSessionRecord& R : Results)
            Descriptions.Add(FString::Printf(TEXT("\"%s\" (%s)"), *R.DisplayName, *R.Uid));
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] Ambiguous name '%s' — %d matches: %s.  "
                "Use a more specific substring."),
                *NameArg, Results.Num(), *FString::Join(Descriptions, TEXT(", "))),
            FLinearColor::Yellow);
        return EExecutionStatus::BAD_ARGUMENTS;
    }

    const FPlayerSessionRecord& Rec = Results[0];

    // Ban the EOS PUID.  DoBan also kicks the player if they are currently online
    // and creates counterpart bans (IP↔EOS) via AddCounterpartBans.
    return BanChat::DoBan(this, Sender, Rec.Uid, Rec.DisplayName, 0, Reason, BannedBy, AdminId);
}

// ─────────────────────────────────────────────────────────────────────────────
//  AReloadConfigChatCommand  — /reloadconfig
// ─────────────────────────────────────────────────────────────────────────────

AReloadConfigChatCommand::AReloadConfigChatCommand()
{
    CommandName          = TEXT("reloadconfig");
    MinNumberOfArguments = 0;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "ReloadConfigUsage", "/reloadconfig");
}

EExecutionStatus AReloadConfigChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminId;
    if (!BanChat::IsAdminSender(Sender, AdminId))
        return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    // Snapshot key config values BEFORE reload for the diff embed.
    const UBanChatCommandsConfig* OldCfg = UBanChatCommandsConfig::Get();
    const int32 OldAdminCount     = OldCfg ? OldCfg->AdminEosPUIDs.Num()     : 0;
    const int32 OldModCount       = OldCfg ? OldCfg->ModeratorEosPUIDs.Num() : 0;
    const int32 OldPageSize       = OldCfg ? OldCfg->BanListPageSize          : 10;
    const bool  OldWarnOnKick     = OldCfg ? OldCfg->bCreateWarnOnKick        : false;

    // Force UE to re-read all UPROPERTY(Config) fields from the ini files.
    GetMutableDefault<UBanChatCommandsConfig>()->ReloadConfig();

    // Update the persistent backup so it reflects the freshly-loaded values.
    FBanChatCommandsModule::BackupConfigIfNeeded();

    const UBanChatCommandsConfig* Cfg = UBanChatCommandsConfig::Get();
    const int32 AdminCount = Cfg ? Cfg->AdminEosPUIDs.Num() : 0;
    UE_LOG(LogBanChatCommands, Log,
        TEXT("BanChatCommands: config reloaded by %s — %d admin(s) now active."),
        Sender->IsPlayerSender() ? *AdminId : TEXT("console"), AdminCount);

    Sender->SendChatMessage(
        FString::Printf(TEXT("[BanChatCommands] Config reloaded — %d admin(s) active."), AdminCount),
        FLinearColor::Green);

    // Post config-diff notification to Discord webhook.
    if (Cfg && !Cfg->ReloadConfigWebhookUrl.IsEmpty() &&
        FModuleManager::Get().IsModuleLoaded(TEXT("HTTP")))
    {
        // Build a list of changed fields for a human-readable diff.
        TArray<FString> Changes;
        if (OldAdminCount != AdminCount)
            Changes.Add(FString::Printf(TEXT("AdminCount: %d → %d"), OldAdminCount, AdminCount));
        if (OldModCount != (Cfg->ModeratorEosPUIDs.Num()))
            Changes.Add(FString::Printf(TEXT("ModeratorCount: %d → %d"), OldModCount, Cfg->ModeratorEosPUIDs.Num()));
        if (OldPageSize != Cfg->BanListPageSize)
            Changes.Add(FString::Printf(TEXT("BanListPageSize: %d → %d"), OldPageSize, Cfg->BanListPageSize));
        if (OldWarnOnKick != Cfg->bCreateWarnOnKick)
            Changes.Add(FString::Printf(TEXT("CreateWarnOnKick: %s → %s"),
                OldWarnOnKick ? TEXT("true") : TEXT("false"),
                Cfg->bCreateWarnOnKick ? TEXT("true") : TEXT("false")));

        const FString ChangeList = Changes.IsEmpty()
            ? TEXT("No changes detected")
            : FString::Join(Changes, TEXT("\n• "));

        // Escape for JSON (handles all control chars and surrogates) then escape
        // Discord markdown so the embed renders the admin name literally.
        const FString EscReloader = BanChat::JsonEscape(BanChat::EscapeMarkdown(Sender->GetSenderName()));
        const FString EscChanges  = BanChat::JsonEscape(ChangeList);

        const FString Payload = FString::Printf(
            TEXT("{\"embeds\":[{\"title\":\"🔄 Config Reloaded\",\"color\":3066993,\"fields\":["
                "{\"name\":\"Reloaded By\",\"value\":\"%s\",\"inline\":true},"
                "{\"name\":\"Admins\",\"value\":\"%d\",\"inline\":true},"
                "{\"name\":\"Changes\",\"value\":\"%s\",\"inline\":false}],"
                "\"timestamp\":\"%s\"}]}"),
            *EscReloader, AdminCount, *EscChanges, *FDateTime::UtcNow().ToIso8601());

        TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request =
            FHttpModule::Get().CreateRequest();
        Request->SetURL(Cfg->ReloadConfigWebhookUrl);
        Request->SetVerb(TEXT("POST"));
        Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
        Request->SetContentAsString(Payload);
        Request->ProcessRequest();

        UE_LOG(LogBanChatCommands, Log,
            TEXT("BanChatCommands: config-reload diff notification posted to webhook."));
    }

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  AKickChatCommand  — /kick
// ─────────────────────────────────────────────────────────────────────────────

AKickChatCommand::AKickChatCommand()
{
    CommandName          = TEXT("kick");
    MinNumberOfArguments = 1;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "KickUsage",
        "/kick <player|PUID> [reason...]");
}

EExecutionStatus AKickChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString ModUid;
    if (!BanChat::IsModeratorSender(Sender, ModUid))
        return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    FString Uid, DisplayName;
    if (!BanChat::ResolveTarget(this, Sender, Arguments[0], Uid, DisplayName))
        return EExecutionStatus::BAD_ARGUMENTS;

    const FString Reason   = Arguments.Num() > 1
        ? BanChat::JoinArgs(Arguments, 1)
        : TEXT("Kicked by server moderator");
    const FString KickedBy = Sender->GetSenderName();

    const bool bKicked = UBanEnforcer::KickConnectedPlayer(GetWorld(), Uid, Reason);

    if (bKicked)
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] Kicked '%s' — reason: %s"), *DisplayName, *Reason),
            FLinearColor::Green);

        FBanDiscordNotifier::NotifyPlayerKicked(DisplayName, Reason, KickedBy, Uid);

        // Write to the audit log.
        {
            UWorld* W = GetWorld();
            UGameInstance* GI = W ? W->GetGameInstance() : nullptr;
            if (UBanAuditLog* AuditLog = GI ? GI->GetSubsystem<UBanAuditLog>() : nullptr)
                AuditLog->LogAction(TEXT("kick"), Uid, DisplayName, ModUid, KickedBy, Reason);
        }

        // Optionally create a warning so kick reasons are preserved in history.
        // This block intentionally runs only when the player was actually kicked;
        // an offline player should not receive a spurious warning record.
        const UBanChatCommandsConfig* CmdCfg = UBanChatCommandsConfig::Get();
        if (CmdCfg && CmdCfg->bCreateWarnOnKick)
        {
            UWorld* W = GetWorld();
            UGameInstance* GI = W ? W->GetGameInstance() : nullptr;
            UPlayerWarningRegistry* WarnReg = GI ? GI->GetSubsystem<UPlayerWarningRegistry>() : nullptr;
            if (WarnReg)
            {
                WarnReg->AddWarning(Uid, DisplayName,
                    FString::Printf(TEXT("[Kick] %s"), *Reason), KickedBy);
                const int32 WarnCount = WarnReg->GetWarningCount(Uid);
                FBanDiscordNotifier::NotifyWarningIssued(Uid, DisplayName,
                    FString::Printf(TEXT("[Kick] %s"), *Reason), KickedBy, WarnCount);
            }
            else
            {
                UE_LOG(LogBanChatCommands, Warning,
                    TEXT("BanChatCommands: bCreateWarnOnKick is true but PlayerWarningRegistry "
                         "is unavailable — kick warning not recorded for '%s' (%s)."),
                    *DisplayName, *Uid);
            }
        }
    }
    else
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] '%s' is not currently online — not kicked."), *DisplayName),
            FLinearColor::Yellow);
    }

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  AModBanChatCommand  — /modban
// ─────────────────────────────────────────────────────────────────────────────

AModBanChatCommand::AModBanChatCommand()
{
    CommandName          = TEXT("modban");
    MinNumberOfArguments = 1;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "ModBanUsage",
        "/modban <player|PUID> [reason...]");
}

EExecutionStatus AModBanChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString ModUid;
    if (!BanChat::IsModeratorSender(Sender, ModUid))
        return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    FString Uid, DisplayName;
    if (!BanChat::ResolveTarget(this, Sender, Arguments[0], Uid, DisplayName))
        return EExecutionStatus::BAD_ARGUMENTS;

    const FString Reason   = Arguments.Num() > 1
        ? BanChat::JoinArgs(Arguments, 1)
        : TEXT("Temporarily banned by server moderator");
    const FString BannedBy = Sender->GetSenderName();

    const UBanChatCommandsConfig* ModBanCfg = UBanChatCommandsConfig::Get();
    const int32 ModBanMinutes = (ModBanCfg && ModBanCfg->ModBanDurationMinutes > 0) ? ModBanCfg->ModBanDurationMinutes : 30;
    return BanChat::DoBan(this, Sender, Uid, DisplayName, ModBanMinutes, Reason, BannedBy, ModUid);
}

// ─────────────────────────────────────────────────────────────────────────────
//  AWarnChatCommand  — /warn
// ─────────────────────────────────────────────────────────────────────────────

AWarnChatCommand::AWarnChatCommand()
{
    CommandName          = TEXT("warn");
    MinNumberOfArguments = 2;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "WarnUsage",
        "/warn <player|PUID> <reason...>");
}

EExecutionStatus AWarnChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminUid;
    if (!BanChat::IsAdminSender(Sender, AdminUid))
        return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    FString Uid, DisplayName;
    if (!BanChat::ResolveTarget(this, Sender, Arguments[0], Uid, DisplayName))
        return EExecutionStatus::BAD_ARGUMENTS;

    const FString Reason   = BanChat::JoinArgs(Arguments, 1);
    const FString WarnedBy = Sender->GetSenderName();

    UWorld* World = GetWorld();
    if (!World) return EExecutionStatus::UNCOMPLETED;
    UGameInstance* GI = World->GetGameInstance();
    if (!GI) return EExecutionStatus::UNCOMPLETED;

    UPlayerWarningRegistry* WarnReg = GI->GetSubsystem<UPlayerWarningRegistry>();
    if (!WarnReg)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] PlayerWarningRegistry unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    WarnReg->AddWarning(Uid, DisplayName, Reason, WarnedBy);
    const int32 WarnCount  = WarnReg->GetWarningCount(Uid);
    const int32 WarnPoints = WarnReg->GetWarningPoints(Uid);

    Sender->SendChatMessage(
        FString::Printf(TEXT("[BanChatCommands] Warned '%s' — reason: %s  (total warnings: %d)"),
            *DisplayName, *Reason, WarnCount),
        FLinearColor::Yellow);

    // Notify the warned player immediately so they are aware of the warning.
    BanChat::SendChatMessageToUid(World, Uid,
        FString::Printf(
            TEXT("[BanChatCommands] You have received a warning. Reason: %s  (Total warnings: %d)"),
            *Reason, WarnCount));

    FBanDiscordNotifier::NotifyWarningIssued(Uid, DisplayName, Reason, WarnedBy, WarnCount);

    if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
        AuditLog->LogAction(TEXT("warn"), Uid, DisplayName, AdminUid, WarnedBy, Reason);

    // Auto-ban the player when they reach the configured warning threshold.
    // Check escalation tiers first; fall back to AutoBanWarnCount if no tiers are configured.
    const UBanSystemConfig* SysCfg = UBanSystemConfig::Get();
    if (SysCfg)
    {
        int32 BanDurationMinutes = -1;
        bool  bTriggeredByPoints = false;

        if (SysCfg->WarnEscalationTiers.Num() > 0)
        {
            // Apply the highest threshold tier that has been reached so the most
            // severe applicable punishment is used regardless of config order.
            int32 BestThreshold = -1;
            for (const FWarnEscalationTier& Tier : SysCfg->WarnEscalationTiers)
            {
                const bool bByPoints  = (Tier.PointThreshold > 0);
                const bool bHit = bByPoints
                    ? (WarnPoints >= Tier.PointThreshold)
                    : (WarnCount  >= Tier.WarnCount);
                const int32 ThisThreshold = bByPoints
                    ? Tier.PointThreshold : Tier.WarnCount;
                if (bHit && ThisThreshold > BestThreshold)
                {
                    BestThreshold      = ThisThreshold;
                    BanDurationMinutes = Tier.DurationMinutes;
                    bTriggeredByPoints = bByPoints;
                }
            }
        }
        else if (SysCfg->AutoBanWarnCount > 0 && WarnCount >= SysCfg->AutoBanWarnCount)
        {
            BanDurationMinutes = SysCfg->AutoBanWarnMinutes;
        }

        if (BanDurationMinutes >= 0)
        {
            UBanDatabase* BanDB = GI->GetSubsystem<UBanDatabase>();
            if (BanDB)
            {
                // Build the entry first, then use AddBanSkipIfPermanentExists so
                // the check-and-add is atomic under the database lock, eliminating
                // the TOCTOU window that existed between the old
                // IsCurrentlyBannedByAnyId check and the subsequent DoBan/AddBan call.
                FBanEntry AutoBanEntry;
                AutoBanEntry.Uid        = Uid;
                UBanDatabase::ParseUid(Uid, AutoBanEntry.Platform, AutoBanEntry.PlayerUID);
                AutoBanEntry.PlayerName   = DisplayName;
                AutoBanEntry.Reason       = TEXT("Auto-banned: reached warning threshold");
                AutoBanEntry.BannedBy     = WarnedBy;
                const FDateTime AutoNow = FDateTime::UtcNow();
                AutoBanEntry.BanDate      = AutoNow;
                AutoBanEntry.bIsPermanent = (BanDurationMinutes <= 0);
                AutoBanEntry.ExpireDate   = AutoBanEntry.bIsPermanent
                    ? FDateTime(0)
                    : AutoNow + FTimespan::FromMinutes(BanDurationMinutes);
                bool bSkipped = false;
                if (BanDB->AddBanSkipIfPermanentExists(AutoBanEntry, bSkipped))
                {
                    const FString ThresholdDesc = bTriggeredByPoints
                        ? FString::Printf(TEXT("%d points"), WarnPoints)
                        : FString::Printf(TEXT("%d warnings"), WarnCount);
                    Sender->SendChatMessage(
                        FString::Printf(TEXT("[BanChatCommands] â%sâ reached the auto-ban threshold (%s) â banning."),
                            *DisplayName, *ThresholdDesc),
                        FLinearColor::Red);
                    // Kick immediately if the player is currently connected.
                    UBanEnforcer::KickConnectedPlayer(World, Uid, AutoBanEntry.GetKickMessage());
                    // Also ban the counterpart identifier (IPâEOS).
                    BanChat::AddCounterpartBans(this, Sender, Uid, DisplayName,
                        BanDurationMinutes, AutoBanEntry.Reason, WarnedBy);
                    // Write to the audit log.
                    if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
                        AuditLog->LogAction(TEXT("ban"), Uid, DisplayName, AdminUid, WarnedBy, AutoBanEntry.Reason);
                    // Notify Discord ban log and auto-escalation review channel.
                    FBanDiscordNotifier::NotifyBanCreated(AutoBanEntry);
                    FBanDiscordNotifier::NotifyAutoEscalationBan(AutoBanEntry, WarnCount);
                }
                else if (bSkipped)
                {
                    UE_LOG(LogBanChatCommands, Log,
                        TEXT("BanChatCommands: auto-ban skipped for â%sâ (%s) â player is already permanently banned."),
                        *DisplayName, *Uid);
                }
            }
        }
    }

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  AWarningsChatCommand  — /warnings
// ─────────────────────────────────────────────────────────────────────────────

AWarningsChatCommand::AWarningsChatCommand()
{
    CommandName          = TEXT("warnings");
    MinNumberOfArguments = 1;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "WarningsUsage",
        "/warnings <player|PUID>");
}

EExecutionStatus AWarningsChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminUid;
    if (!BanChat::IsAdminSender(Sender, AdminUid))
        return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    // Apply per-command cooldown for non-console senders.
    {
        const UBanChatCommandsConfig* CoolCfg = UBanChatCommandsConfig::Get();
        const int32 CoolSecs = CoolCfg ? CoolCfg->WarningCheckCooldownSeconds : 0;
        int32 RemainingCoolSecs = 0;
        if (BanChat::IsOnCooldown(Sender, TEXT("warnings"), CoolSecs, AdminUid, &RemainingCoolSecs))
        {
            Sender->SendChatMessage(
                FString::Printf(TEXT("[BanChatCommands] Please wait %d second(s) before using /warnings again."), RemainingCoolSecs),
                FLinearColor::Yellow);
            return EExecutionStatus::UNCOMPLETED;
        }
    }

    FString Uid, DisplayName;
    if (!BanChat::ResolveTarget(this, Sender, Arguments[0], Uid, DisplayName))
        return EExecutionStatus::BAD_ARGUMENTS;

    // Optional page argument: /warnings <target> [page]
    int32 Page = 1;
    if (Arguments.Num() >= 2 && Arguments[1].IsNumeric() && Arguments[1].Len() <= 9)
    {
        Page = FMath::Max(1, FCString::Atoi(*Arguments[1]));
    }

    UWorld* World = GetWorld();
    if (!World) return EExecutionStatus::UNCOMPLETED;
    UGameInstance* GI = World->GetGameInstance();
    if (!GI) return EExecutionStatus::UNCOMPLETED;

    UPlayerWarningRegistry* WarnReg = GI->GetSubsystem<UPlayerWarningRegistry>();
    if (!WarnReg)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] PlayerWarningRegistry unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    const TArray<FWarningEntry> Warnings = WarnReg->GetWarningsForUid(Uid);
    if (Warnings.IsEmpty())
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] No warnings on record for '%s'."), *DisplayName),
            FLinearColor::White);
        return EExecutionStatus::COMPLETED;
    }

    const UBanChatCommandsConfig* Cfg = UBanChatCommandsConfig::Get();
    const int32 PageSize   = Cfg ? Cfg->BanListPageSize : 10;
    const int32 TotalPages = (Warnings.Num() + PageSize - 1) / FMath::Max(PageSize, 1);
    Page = FMath::Clamp(Page, 1, TotalPages);
    const int32 StartIdx   = (Page - 1) * PageSize;
    const int32 EndIdx     = FMath::Min(StartIdx + PageSize, Warnings.Num());

    Sender->SendChatMessage(
        FString::Printf(TEXT("[BanChatCommands] Warnings for '%s' (page %d of %d, total %d):"),
            *DisplayName, Page, TotalPages, Warnings.Num()),
        FLinearColor::Yellow);

    for (int32 i = StartIdx; i < EndIdx; ++i)
    {
        const FWarningEntry& W = Warnings[i];
        Sender->SendChatMessage(
            FString::Printf(TEXT("  #%lld | %s | By: %s | %s"),
                W.Id, *W.Reason, *W.WarnedBy,
                *W.WarnDate.ToString(TEXT("%Y-%m-%d %H:%M:%S"))),
            FLinearColor::White);
    }

    if (TotalPages > 1 && Page < TotalPages)
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("  Use /warnings %s %d to see more."), *Arguments[0], Page + 1),
            FLinearColor::White);
    }

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  AClearWarnsChatCommand  — /clearwarns
// ─────────────────────────────────────────────────────────────────────────────

AClearWarnsChatCommand::AClearWarnsChatCommand()
{
    CommandName          = TEXT("clearwarns");
    MinNumberOfArguments = 1;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "ClearWarnsUsage",
        "/clearwarns <player|PUID>");
}

EExecutionStatus AClearWarnsChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminUid;
    if (!BanChat::IsAdminSender(Sender, AdminUid))
        return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    FString Uid, DisplayName;
    if (!BanChat::ResolveTarget(this, Sender, Arguments[0], Uid, DisplayName))
        return EExecutionStatus::BAD_ARGUMENTS;

    UWorld* World = GetWorld();
    if (!World) return EExecutionStatus::UNCOMPLETED;
    UGameInstance* GI = World->GetGameInstance();
    if (!GI) return EExecutionStatus::UNCOMPLETED;

    UPlayerWarningRegistry* WarnReg = GI->GetSubsystem<UPlayerWarningRegistry>();
    if (!WarnReg)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] PlayerWarningRegistry unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    const int32 Cleared = WarnReg->ClearWarningsForUid(Uid);

    if (Cleared > 0)
    {
        if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
            AuditLog->LogAction(TEXT("clearwarns"), Uid, DisplayName, AdminUid, Sender->GetSenderName(),
                FString::Printf(TEXT("cleared=%d"), Cleared));

        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] Cleared %d warning(s) for '%s'."),
                Cleared, *DisplayName),
            FLinearColor::Green);
    }
    else
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] No warnings on record for '%s'."), *DisplayName),
            FLinearColor::Yellow);
    }

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  AAnnounceChatCommand  — /announce
// ─────────────────────────────────────────────────────────────────────────────

AAnnounceChatCommand::AAnnounceChatCommand()
{
    CommandName          = TEXT("announce");
    MinNumberOfArguments = 1;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "AnnounceUsage",
        "/announce <message...>");
}

EExecutionStatus AAnnounceChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminUid;
    if (!BanChat::IsAdminSender(Sender, AdminUid))
        return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    const FString Message    = BanChat::JoinArgs(Arguments, 0);
    const FString SenderName = Sender->GetSenderName();

    UWorld* World = GetWorld();
    if (!World) return EExecutionStatus::UNCOMPLETED;

    // Broadcast to all connected players.
    const FString Announcement = FString::Printf(TEXT("[Server Announcement] %s"), *Message);
    for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PC = It->Get();
        if (!PC) continue;
        PC->ClientMessage(Announcement);
    }

    Sender->SendChatMessage(
        FString::Printf(TEXT("[BanChatCommands] Announcement sent: %s"), *Message),
        FLinearColor::Green);

    UE_LOG(LogBanChatCommands, Log, TEXT("Announce [%s]: %s"), *SenderName, *Message);
    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  AStaffListChatCommand  — /stafflist
// ─────────────────────────────────────────────────────────────────────────────

AStaffListChatCommand::AStaffListChatCommand()
{
    CommandName          = TEXT("stafflist");
    MinNumberOfArguments = 0;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "StaffListUsage",
        "/stafflist");
}

EExecutionStatus AStaffListChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    const UBanChatCommandsConfig* Cfg = UBanChatCommandsConfig::Get();
    if (!Cfg)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] Config unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    UWorld* World = GetWorld();
    if (!World) return EExecutionStatus::UNCOMPLETED;

    TArray<FString> OnlineAdmins;
    TArray<FString> OnlineModerators;

    for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PC = It->Get();
        if (!PC || !PC->PlayerState) continue;

        FString PlayerUid;
        const FUniqueNetIdRepl& NetId = PC->PlayerState->GetUniqueId();
        if (NetId.IsValid() && NetId.GetType() != FName(TEXT("NONE")))
            PlayerUid = UBanDatabase::MakeUid(TEXT("EOS"), NetId.ToString().ToLower());
        else
        {
            const FString EosPuid = UBanEnforcer::ExtractEosPuidFromConnectionUrl(PC);
            if (!EosPuid.IsEmpty())
                PlayerUid = UBanDatabase::MakeUid(TEXT("EOS"), EosPuid);
        }
        if (PlayerUid.IsEmpty()) continue;

        const FString Name = PC->PlayerState->GetPlayerName();
        if (Cfg->IsAdminUid(PlayerUid))
            OnlineAdmins.Add(Name);
        else if (Cfg->IsModeratorUid(PlayerUid))
            OnlineModerators.Add(Name);
    }

    if (OnlineAdmins.IsEmpty() && OnlineModerators.IsEmpty())
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] No staff online at this time."), FLinearColor::White);
    }
    else
    {
        if (!OnlineAdmins.IsEmpty())
        {
            Sender->SendChatMessage(
                FString::Printf(TEXT("[BanChatCommands] Admins online: %s"),
                    *FString::Join(OnlineAdmins, TEXT(", "))),
                FLinearColor(0.0f, 1.0f, 1.0f));
        }
        if (!OnlineModerators.IsEmpty())
        {
            Sender->SendChatMessage(
                FString::Printf(TEXT("[BanChatCommands] Moderators online: %s"),
                    *FString::Join(OnlineModerators, TEXT(", "))),
                FLinearColor(0.0f, 0.8f, 1.0f));
        }
    }

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  AReasonChatCommand  — /reason
// ─────────────────────────────────────────────────────────────────────────────

AReasonChatCommand::AReasonChatCommand()
{
    CommandName          = TEXT("reason");
    MinNumberOfArguments = 1;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "ReasonUsage",
        "/reason <UID>");
}

EExecutionStatus AReasonChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    // Restrict to admins/moderators — ban details (reason, banner, date) must not
    // be visible to regular players.
    FString CallerId;
    const UBanChatCommandsConfig* ReasonCfg = UBanChatCommandsConfig::Get();
    if (!BanChat::IsAdminSender(Sender, CallerId, false))
    {
        if (!ReasonCfg || !ReasonCfg->IsModeratorUid(CallerId))
        {
            if (Sender) Sender->SendChatMessage(
                TEXT("[BanChatCommands] You do not have permission to use this command."),
                FLinearColor::Red);
            return EExecutionStatus::INSUFFICIENT_PERMISSIONS;
        }
    }

    FString Uid;
    if (!BanChat::ParseAndNormaliseUidArg(Sender, Arguments[0], Uid))
        return EExecutionStatus::BAD_ARGUMENTS;

    UBanDatabase* DB = BanChat::GetDB(this);
    if (!DB)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] UBanDatabase unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    FBanEntry Entry;
    if (!DB->GetBanByUid(Uid, Entry))
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] No ban record found for '%s'."), *Uid),
            FLinearColor::Yellow);
        return EExecutionStatus::COMPLETED;
    }

    if (Entry.bIsPermanent)
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] Ban reason for %s: %s (permanent, by %s, %s)"),
                *Uid, *Entry.Reason, *Entry.BannedBy,
                *Entry.BanDate.ToString(TEXT("%Y-%m-%d"))),
            FLinearColor::White);
    }
    else
    {
        const FTimespan Remaining = Entry.ExpireDate - FDateTime::UtcNow();
        const FString RemainingStr = Remaining.GetTicks() > 0
            ? FString::Printf(TEXT("%.0f min remaining"), Remaining.GetTotalMinutes())
            : TEXT("expired");
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] Ban reason for %s: %s (temp — %s, by %s)"),
                *Uid, *Entry.Reason, *RemainingStr, *Entry.BannedBy),
            FLinearColor::White);
    }

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  AHistoryChatCommand  — /history (self)
// ─────────────────────────────────────────────────────────────────────────────

AHistoryChatCommand::AHistoryChatCommand()
{
    CommandName          = TEXT("history");
    MinNumberOfArguments = 0;
    bOnlyUsableByPlayer  = true;
    Usage = NSLOCTEXT("BanChatCommands", "HistoryUsage",
        "/history");
}

EExecutionStatus AHistoryChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    APlayerController* PC = Cast<APlayerController>(Sender->GetPlayer());
    if (!PC || !PC->PlayerState)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] Could not resolve your identity."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    FString Uid;
    const FUniqueNetIdRepl& NetId = PC->PlayerState->GetUniqueId();
    if (NetId.IsValid() && NetId.GetType() != FName(TEXT("NONE")))
        Uid = UBanDatabase::MakeUid(TEXT("EOS"), NetId.ToString().ToLower());
    else
    {
        const FString EosPuid = UBanEnforcer::ExtractEosPuidFromConnectionUrl(PC);
        if (!EosPuid.IsEmpty())
            Uid = UBanDatabase::MakeUid(TEXT("EOS"), EosPuid);
    }

    if (Uid.IsEmpty())
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] Could not resolve your platform identity."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    UWorld* World = GetWorld();
    if (!World) return EExecutionStatus::UNCOMPLETED;
    UGameInstance* GI = World->GetGameInstance();
    if (!GI) return EExecutionStatus::UNCOMPLETED;

    // Session info.
    UPlayerSessionRegistry* SessionReg = GI->GetSubsystem<UPlayerSessionRegistry>();
    if (SessionReg)
    {
        for (const FPlayerSessionRecord& R : SessionReg->GetAllRecords())
        {
            if (R.Uid.Equals(Uid, ESearchCase::IgnoreCase))
            {
                Sender->SendChatMessage(
                    FString::Printf(TEXT("[BanChatCommands] Your last session: %s"), *R.LastSeen),
                    FLinearColor::White);
                break;
            }
        }
    }

    // Warning history.
    UPlayerWarningRegistry* WarnReg = GI->GetSubsystem<UPlayerWarningRegistry>();
    if (WarnReg)
    {
        const TArray<FWarningEntry> Warnings = WarnReg->GetWarningsForUid(Uid);
        if (Warnings.IsEmpty())
        {
            Sender->SendChatMessage(TEXT("[BanChatCommands] You have no warnings on record."), FLinearColor::Green);
        }
        else
        {
            Sender->SendChatMessage(
                FString::Printf(TEXT("[BanChatCommands] You have %d warning(s) on record."), Warnings.Num()),
                FLinearColor::Yellow);
            const int32 MaxShow = FMath::Min(Warnings.Num(), 5);
            for (int32 i = 0; i < MaxShow; ++i)
            {
                const FWarningEntry& W = Warnings[i];
                Sender->SendChatMessage(
                    FString::Printf(TEXT("  #%d %s — %s"),
                        i + 1, *W.WarnDate.ToString(TEXT("%Y-%m-%d")), *W.Reason),
                    FLinearColor::White);
            }
            if (Warnings.Num() > MaxShow)
            {
                Sender->SendChatMessage(
                    FString::Printf(TEXT("  … and %d more."), Warnings.Num() - MaxShow),
                    FLinearColor::White);
            }
        }
    }

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  AMuteChatCommand  — /mute
// ─────────────────────────────────────────────────────────────────────────────

AMuteChatCommand::AMuteChatCommand()
{
    CommandName          = TEXT("mute");
    MinNumberOfArguments = 1;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "MuteUsage",
        "/mute <player|PUID> [duration] [reason...]\n"
        "  duration: minutes (e.g. 30) or shorthand (e.g. 30m, 1h, 2h30m, 1d, 7d, 1d12h)\n"
        "  omit duration for indefinite mute");
}

EExecutionStatus AMuteChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminUid;
    if (!BanChat::IsAdminSender(Sender, AdminUid))
        return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    FString Uid, DisplayName;
    if (!BanChat::ResolveTarget(this, Sender, Arguments[0], Uid, DisplayName))
        return EExecutionStatus::BAD_ARGUMENTS;

    int32 Minutes     = 0;
    int32 ReasonStart = 1;
    if (Arguments.Num() >= 2)
    {
        const int32 Parsed = BanChat::ParseDurationMinutes(Arguments[1]);
        if (Parsed > 0)
        {
            Minutes     = Parsed;
            ReasonStart = 2;
        }
        else if (Arguments[1].IsNumeric())
        {
            // A bare integer that is <= 0 (e.g. "0") — reject explicitly.
            Sender->SendChatMessage(
                TEXT("[BanChatCommands] Duration must be positive (e.g. 30, 30m, 1h, 1d)."),
                FLinearColor::Red);
            return EExecutionStatus::BAD_ARGUMENTS;
        }
        // else: arg2 is not a duration string — treat as start of reason
    }

    const FString Reason   = Arguments.Num() > ReasonStart
        ? BanChat::JoinArgs(Arguments, ReasonStart)
        : TEXT("Muted by admin");
    const FString MutedBy = Sender->GetSenderName();

    UWorld* World = GetWorld();
    if (!World) return EExecutionStatus::UNCOMPLETED;
    UGameInstance* GI = World->GetGameInstance();
    if (!GI) return EExecutionStatus::UNCOMPLETED;

    UMuteRegistry* MuteReg = GI->GetSubsystem<UMuteRegistry>();
    if (!MuteReg)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] MuteRegistry unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    MuteReg->MutePlayer(Uid, DisplayName, Reason, MutedBy, Minutes);

    // Notify via webhook so the action is visible even without the Discord bot.
    {
        const bool bIsTimed = Minutes > 0;
        const FDateTime MuteNow = FDateTime::UtcNow();
        const FDateTime Expiry = bIsTimed
            ? MuteNow + FTimespan::FromMinutes(static_cast<double>(Minutes))
            : FDateTime(0);
        FBanDiscordNotifier::NotifyPlayerMuted(Uid, DisplayName, MutedBy, Reason, bIsTimed, Expiry, MuteNow);
    }

    if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
        AuditLog->LogAction(TEXT("mute"), Uid, DisplayName, AdminUid, MutedBy, Reason);

    const FString DurStr = Minutes > 0
        ? FString::Printf(TEXT(" %s"), *BanChat::FormatDuration(Minutes))
        : TEXT(" indefinitely");
    Sender->SendChatMessage(
        FString::Printf(TEXT("[BanChatCommands] Muted '%s'%s — %s"), *DisplayName, *DurStr, *Reason),
        FLinearColor::Green);

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  AUnmuteChatCommand  — /unmute
// ─────────────────────────────────────────────────────────────────────────────

AUnmuteChatCommand::AUnmuteChatCommand()
{
    CommandName          = TEXT("unmute");
    MinNumberOfArguments = 1;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "UnmuteUsage",
        "/unmute <player|PUID>");
}

EExecutionStatus AUnmuteChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminUid;
    if (!BanChat::IsAdminSender(Sender, AdminUid))
        return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    FString Uid, DisplayName;
    if (!BanChat::ResolveTarget(this, Sender, Arguments[0], Uid, DisplayName))
        return EExecutionStatus::BAD_ARGUMENTS;

    UWorld* World = GetWorld();
    if (!World) return EExecutionStatus::UNCOMPLETED;
    UGameInstance* GI = World->GetGameInstance();
    if (!GI) return EExecutionStatus::UNCOMPLETED;

    UMuteRegistry* MuteReg = GI->GetSubsystem<UMuteRegistry>();
    if (!MuteReg)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] MuteRegistry unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    if (MuteReg->UnmutePlayer(Uid))
    {
        FBanDiscordNotifier::NotifyPlayerUnmuted(Uid, DisplayName, Sender->GetSenderName());
        if (UBanAuditLog* AuditLog = GI ? GI->GetSubsystem<UBanAuditLog>() : nullptr)
            AuditLog->LogAction(TEXT("unmute"), Uid, DisplayName, AdminUid, Sender->GetSenderName(), TEXT(""));
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] Unmuted '%s'."), *DisplayName),
            FLinearColor::Green);
    }
    else
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] '%s' is not currently muted."), *DisplayName),
            FLinearColor::Yellow);
    }

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  ANoteChatCommand  — /note
// ─────────────────────────────────────────────────────────────────────────────

ANoteChatCommand::ANoteChatCommand()
{
    CommandName          = TEXT("note");
    MinNumberOfArguments = 2;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "NoteUsage",
        "/note <player|PUID> <text...>");
}

EExecutionStatus ANoteChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminId;
    const UBanChatCommandsConfig* Cfg = UBanChatCommandsConfig::Get();
    if (!BanChat::IsAdminSender(Sender, AdminId, false))
    {
        if (!Cfg || !Cfg->bAllowModNotes || !Cfg->IsModeratorUid(AdminId))
        {
            if (Sender) Sender->SendChatMessage(
                TEXT("[BanChatCommands] You do not have permission to use this command."),
                FLinearColor::Red);
            return EExecutionStatus::INSUFFICIENT_PERMISSIONS;
        }
    }

    FString Uid, DisplayName;
    if (!BanChat::ResolveTarget(this, Sender, Arguments[0], Uid, DisplayName))
        return EExecutionStatus::BAD_ARGUMENTS;

    UWorld* World = GetWorld();
    if (!World) return EExecutionStatus::UNCOMPLETED;
    UGameInstance* GI = World->GetGameInstance();
    if (!GI) return EExecutionStatus::UNCOMPLETED;

    UPlayerNoteRegistry* NoteReg = GI->GetSubsystem<UPlayerNoteRegistry>();
    if (!NoteReg)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] PlayerNoteRegistry unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    const FString NoteText = BanChat::JoinArgs(Arguments, 1);
    NoteReg->AddNote(Uid, DisplayName, NoteText, Sender->GetSenderName());

    if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
        AuditLog->LogAction(TEXT("note"), Uid, DisplayName, AdminId, Sender->GetSenderName(), NoteText);

    Sender->SendChatMessage(
        FString::Printf(TEXT("[BanChatCommands] Note added for '%s'."), *DisplayName),
        FLinearColor::Green);

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  ANotesChatCommand  — /notes
// ─────────────────────────────────────────────────────────────────────────────

ANotesChatCommand::ANotesChatCommand()
{
    CommandName          = TEXT("notes");
    MinNumberOfArguments = 1;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "NotesUsage",
        "/notes <player|PUID>");
}

EExecutionStatus ANotesChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminId;
    const UBanChatCommandsConfig* Cfg = UBanChatCommandsConfig::Get();
    if (!BanChat::IsAdminSender(Sender, AdminId, false))
    {
        if (!Cfg || !Cfg->bAllowModNotes || !Cfg->IsModeratorUid(AdminId))
        {
            if (Sender) Sender->SendChatMessage(
                TEXT("[BanChatCommands] You do not have permission to use this command."),
                FLinearColor::Red);
            return EExecutionStatus::INSUFFICIENT_PERMISSIONS;
        }
    }

    FString Uid, DisplayName;
    if (!BanChat::ResolveTarget(this, Sender, Arguments[0], Uid, DisplayName))
        return EExecutionStatus::BAD_ARGUMENTS;

    UWorld* World = GetWorld();
    if (!World) return EExecutionStatus::UNCOMPLETED;
    UGameInstance* GI = World->GetGameInstance();
    if (!GI) return EExecutionStatus::UNCOMPLETED;

    UPlayerNoteRegistry* NoteReg = GI->GetSubsystem<UPlayerNoteRegistry>();
    if (!NoteReg)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] PlayerNoteRegistry unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    TArray<FPlayerNoteEntry> Notes = NoteReg->GetNotesForUid(Uid);
    if (Notes.IsEmpty())
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] No notes on record for '%s'."), *DisplayName),
            FLinearColor::Yellow);
        return EExecutionStatus::COMPLETED;
    }

    Sender->SendChatMessage(
        FString::Printf(TEXT("[BanChatCommands] Notes for '%s' (%d):"), *DisplayName, Notes.Num()),
        FLinearColor::White);

    for (const FPlayerNoteEntry& N : Notes)
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("  #%lld [%s] (%s): %s"),
                N.Id,
                *N.NoteDate.ToString(TEXT("%Y-%m-%d %H:%M")),
                *N.AddedBy,
                *N.Note),
            FLinearColor::White);
    }

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  ADurationChatCommand  — /duration
// ─────────────────────────────────────────────────────────────────────────────

ADurationChatCommand::ADurationChatCommand()
{
    CommandName          = TEXT("duration");
    MinNumberOfArguments = 1;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "DurationUsage",
        "/duration <player|PUID>");
}

EExecutionStatus ADurationChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminId;
    if (!BanChat::IsAdminSender(Sender, AdminId))
        return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    FString Uid, DisplayName;
    if (!BanChat::ResolveTarget(this, Sender, Arguments[0], Uid, DisplayName))
        return EExecutionStatus::BAD_ARGUMENTS;

    UBanDatabase* DB = BanChat::GetDB(this);
    if (!DB)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] UBanDatabase unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    FBanEntry Entry;
    if (!DB->IsCurrentlyBannedByAnyId(Uid, Entry))
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] No active ban found for '%s'."), *DisplayName),
            FLinearColor::Yellow);
        return EExecutionStatus::COMPLETED;
    }

    if (Entry.bIsPermanent)
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] Ban for '%s' is PERMANENT."), *DisplayName),
            FLinearColor::Red);
        return EExecutionStatus::COMPLETED;
    }

    const FTimespan Remaining = Entry.ExpireDate - FDateTime::UtcNow();
    if (Remaining.GetTotalSeconds() <= 0.0)
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] Tempban for '%s' has expired."), *DisplayName),
            FLinearColor::Yellow);
        return EExecutionStatus::COMPLETED;
    }

    const int32 Days    = static_cast<int32>(Remaining.GetDays());
    const int32 Hours   = Remaining.GetHours();
    const int32 Minutes = Remaining.GetMinutes();

    FString DurStr;
    if (Days > 0)   DurStr += FString::Printf(TEXT("%dd "), Days);
    if (Hours > 0)  DurStr += FString::Printf(TEXT("%dh "), Hours);
    DurStr += FString::Printf(TEXT("%dm"), Minutes);

    Sender->SendChatMessage(
        FString::Printf(TEXT("[BanChatCommands] Ban for '%s': %s remaining (expires %s UTC)."),
            *DisplayName, *DurStr.TrimEnd(),
            *Entry.ExpireDate.ToString(TEXT("%Y-%m-%d %H:%M:%S"))),
        FLinearColor::Yellow);

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  ATempUnmuteChatCommand  — /tempunmute  (lift a timed mute early)
// ─────────────────────────────────────────────────────────────────────────────

ATempUnmuteChatCommand::ATempUnmuteChatCommand()
{
    CommandName          = TEXT("tempunmute");
    MinNumberOfArguments = 1;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "TempUnmuteUsage",
        "/tempunmute <player|PUID>  — lift a timed mute before its scheduled expiry");
}

EExecutionStatus ATempUnmuteChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminId;
    if (!BanChat::IsAdminSender(Sender, AdminId, /*bSendError=*/false))
    {
        // Also allow moderators to lift timed mutes (same policy as /mutecheck).
        const UBanChatCommandsConfig* Cfg = UBanChatCommandsConfig::Get();
        if (!Cfg || !Cfg->IsModeratorUid(AdminId))
        {
            Sender->SendChatMessage(
                TEXT("[BanChatCommands] You do not have permission to use this command."),
                FLinearColor::Red);
            return EExecutionStatus::INSUFFICIENT_PERMISSIONS;
        }
    }

    FString Uid, DisplayName;
    if (!BanChat::ResolveTarget(this, Sender, Arguments[0], Uid, DisplayName))
        return EExecutionStatus::BAD_ARGUMENTS;

    UWorld* World = GetWorld();
    if (!World) return EExecutionStatus::UNCOMPLETED;
    UGameInstance* GI = World->GetGameInstance();
    if (!GI) return EExecutionStatus::UNCOMPLETED;

    UMuteRegistry* MuteReg = GI->GetSubsystem<UMuteRegistry>();
    if (!MuteReg)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] MuteRegistry unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    FMuteEntry Entry;
    if (!MuteReg->GetMuteEntry(Uid, Entry))
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] '%s' is not currently muted."), *DisplayName),
            FLinearColor::Yellow);
        return EExecutionStatus::COMPLETED;
    }

    if (Entry.bIsIndefinite)
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] '%s' has an indefinite mute. Use /unmute instead."), *DisplayName),
            FLinearColor::Yellow);
        return EExecutionStatus::COMPLETED;
    }

    if (MuteReg->UnmutePlayer(Uid))
    {
        FBanDiscordNotifier::NotifyPlayerUnmuted(Uid, DisplayName, Sender->GetSenderName());

        if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
            AuditLog->LogAction(TEXT("unmute"), Uid, DisplayName, AdminId, Sender->GetSenderName(), TEXT("Timed mute lifted early"));

        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] Timed mute lifted early for '%s'."), *DisplayName),
            FLinearColor::Green);
    }
    else
    {
        // Mute was already removed concurrently (TickExpiry or another admin's /unmute).
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] '%s' is no longer muted."), *DisplayName),
            FLinearColor::Yellow);
    }

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  AMuteCheckChatCommand  — /mutecheck
// ─────────────────────────────────────────────────────────────────────────────

AMuteCheckChatCommand::AMuteCheckChatCommand()
{
    CommandName          = TEXT("mutecheck");
    MinNumberOfArguments = 1;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "MuteCheckUsage",
        "/mutecheck <player|PUID>");
}

EExecutionStatus AMuteCheckChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString CallerId;
    const UBanChatCommandsConfig* Cfg = UBanChatCommandsConfig::Get();
    if (!BanChat::IsAdminSender(Sender, CallerId, false))
    {
        if (!Cfg || !Cfg->IsModeratorUid(CallerId))
        {
            if (Sender) Sender->SendChatMessage(
                TEXT("[BanChatCommands] You do not have permission to use this command."),
                FLinearColor::Red);
            return EExecutionStatus::INSUFFICIENT_PERMISSIONS;
        }
    }

    FString Uid, DisplayName;
    if (!BanChat::ResolveTarget(this, Sender, Arguments[0], Uid, DisplayName))
        return EExecutionStatus::BAD_ARGUMENTS;

    UWorld* World = GetWorld();
    if (!World) return EExecutionStatus::UNCOMPLETED;
    UGameInstance* GI = World->GetGameInstance();
    if (!GI) return EExecutionStatus::UNCOMPLETED;

    UMuteRegistry* MuteReg = GI->GetSubsystem<UMuteRegistry>();
    if (!MuteReg)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] MuteRegistry unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    FMuteEntry Entry;
    if (!MuteReg->GetMuteEntry(Uid, Entry))
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] '%s' is not currently muted."), *DisplayName),
            FLinearColor::Green);
        return EExecutionStatus::COMPLETED;
    }

    if (Entry.bIsIndefinite)
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] '%s' is muted indefinitely. Reason: %s. Muted by: %s."),
                *DisplayName, *Entry.Reason, *Entry.MutedBy),
            FLinearColor::Yellow);
    }
    else
    {
        const FTimespan Remaining = Entry.ExpireDate - FDateTime::UtcNow();
        const int64 RemainingMin64 = static_cast<int64>(Remaining.GetTotalMinutes());
        // If the mute has already expired (remaining ≤ 0) the MuteRegistry
        // enforcement sweep hasn't run yet.  Report expiry and clean up the
        // stale entry rather than clamping to 1 and showing false "1m remaining".
        if (RemainingMin64 <= 0)
        {
            MuteReg->UnmutePlayer(Uid);
            Sender->SendChatMessage(
                FString::Printf(TEXT("[BanChatCommands] '%s' is no longer muted (mute has expired)."), *DisplayName),
                FLinearColor::Green);
            return EExecutionStatus::COMPLETED;
        }
        const int32 RemainingMin = static_cast<int32>(FMath::Min(RemainingMin64, static_cast<int64>(INT32_MAX)));
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] '%s' is muted until %s UTC (%s remaining). Reason: %s."),
                *DisplayName,
                *Entry.ExpireDate.ToString(TEXT("%Y-%m-%d %H:%M:%S")),
                *BanChat::FormatDuration(RemainingMin),
                *Entry.Reason),
            FLinearColor::Yellow);
    }

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  ABanReasonChatCommand  — /banreason
// ─────────────────────────────────────────────────────────────────────────────

ABanReasonChatCommand::ABanReasonChatCommand()
{
    CommandName          = TEXT("banreason");
    MinNumberOfArguments = 2;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "BanReasonUsage",
        "/banreason <player|PUID> <new reason...>");
}

EExecutionStatus ABanReasonChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminId;
    if (!BanChat::IsAdminSender(Sender, AdminId))
        return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    FString Uid, DisplayName;
    if (!BanChat::ResolveTarget(this, Sender, Arguments[0], Uid, DisplayName))
        return EExecutionStatus::BAD_ARGUMENTS;

    UBanDatabase* DB = BanChat::GetDB(this);
    if (!DB)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] UBanDatabase unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    // Initial "is banned?" check — used only to obtain the primary UID and to
    // produce a friendly "not banned" message.  The actual mutation is performed
    // inside UpdateBan() which holds the database lock for the full read-modify-
    // write cycle, closing the TOCTOU window that existed with AddBan().
    FBanEntry Entry;
    if (!DB->IsCurrentlyBannedByAnyId(Uid, Entry))
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] No active ban found for '%s'."), *DisplayName),
            FLinearColor::Yellow);
        return EExecutionStatus::COMPLETED;
    }

    const FString NewReason   = BanChat::JoinArgs(Arguments, 1);
    const FString PrimaryUid  = Entry.Uid; // UpdateBan looks up by primary UID

    FBanEntry Updated;
    if (!DB->UpdateBan(PrimaryUid, [&NewReason](FBanEntry& E) { E.Reason = NewReason; }, Updated))
    {
        // The ban was removed between the check above and the atomic update
        // (concurrent unban or expiry).  Treat as "not found".
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] Ban for '%s' was removed concurrently — reason not updated."), *DisplayName),
            FLinearColor::Yellow);
        return EExecutionStatus::COMPLETED;
    }
    // UpdateBan fires OnBanUpdated, which BanDiscordSubsystem's BanUpdatedHandle
    // picks up and posts to the moderation log automatically.

    // Write audit log.
    UWorld* World = GetWorld();
    if (World)
    {
        UGameInstance* GI = World->GetGameInstance();
        if (GI)
        {
            UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>();
            if (AuditLog)
            {
                AuditLog->LogAction(TEXT("banreason"), Updated.Uid, DisplayName,
                    AdminId, Sender->GetSenderName(), NewReason);
            }
        }
    }

    Sender->SendChatMessage(
        FString::Printf(TEXT("[BanChatCommands] Updated ban reason for '%s': %s"), *DisplayName, *NewReason),
        FLinearColor::Green);

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  AStaffChatCommand  — /staffchat
// ─────────────────────────────────────────────────────────────────────────────

FOnInGameStaffChat AStaffChatCommand::OnInGameStaffChat;

AStaffChatCommand::AStaffChatCommand()
{
    CommandName          = TEXT("staffchat");
    MinNumberOfArguments = 1;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "StaffChatUsage",
        "/staffchat <message...>");
}

EExecutionStatus AStaffChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString CallerId;
    const UBanChatCommandsConfig* Cfg = UBanChatCommandsConfig::Get();
    if (!BanChat::IsAdminSender(Sender, CallerId, false))
    {
        if (!Cfg || !Cfg->IsModeratorUid(CallerId))
        {
            if (Sender) Sender->SendChatMessage(
                TEXT("[BanChatCommands] You do not have permission to use this command."),
                FLinearColor::Red);
            return EExecutionStatus::INSUFFICIENT_PERMISSIONS;
        }
    }

    const FString Message = BanChat::JoinArgs(Arguments, 0);
    const FString Formatted = FString::Printf(TEXT("[Staff] %s: %s"), *Sender->GetSenderName(), *Message);
    const FLinearColor StaffColor(0.0f, 0.8f, 1.0f, 1.0f);

    // Send only to online admins and moderators.
    UWorld* World = GetWorld();
    if (!World) return EExecutionStatus::UNCOMPLETED;

    bool bSentToAnyone = false;

    for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PC = It->Get();
        if (!PC) continue;

        APlayerState* PS = PC->PlayerState;
        if (!PS) continue;

        const FUniqueNetIdRepl& PsUniqueId = PS->GetUniqueId();
        FString PSUid;
        if (PsUniqueId.IsValid() && PsUniqueId.GetType() != FName(TEXT("NONE")))
        {
            PSUid = UBanDatabase::MakeUid(TEXT("EOS"), PsUniqueId.ToString().ToLower());
        }
        else
        {
            const FString EosPuid = UBanEnforcer::ExtractEosPuidFromConnectionUrl(PC);
            if (!EosPuid.IsEmpty())
                PSUid = UBanDatabase::MakeUid(TEXT("EOS"), EosPuid);
        }
        if (PSUid.IsEmpty()) continue;

        if (!Cfg) continue;

        if (Cfg->IsAdminUid(PSUid) || Cfg->IsModeratorUid(PSUid))
        {
            // Use SendChatMessage to the specific CommandSender is unavailable here;
            // fall back to broadcasting via ClientMessage on the PC.
            PC->ClientMessage(Formatted);
            bSentToAnyone = true;
        }
    }

    // Echo back to the sender only when they are a console/non-player sender.
    // Player senders already received the message via PC->ClientMessage() above,
    // so echoing again would produce a duplicate entry in their chat window.
    if (!Sender->IsPlayerSender())
        Sender->SendChatMessage(Formatted, StaffColor);

    // Notify the sender when no staff saw the message.  For a console sender
    // the echo above already delivered the text, so the warning is only useful
    // to player senders who would otherwise receive no feedback at all.
    if (!bSentToAnyone && Sender->IsPlayerSender())
    {
        Sender->SendChatMessage(
            TEXT("[BanChatCommands] No staff members are currently online."),
            FLinearColor::Yellow);
    }

    // Notify external systems (e.g. DiscordBridge) so the message can be
    // mirrored to a Discord staff-chat channel.
    AStaffChatCommand::OnInGameStaffChat.Broadcast(Sender->GetSenderName(), Message);

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  AMuteListChatCommand  — /mutelist
// ─────────────────────────────────────────────────────────────────────────────

AMuteListChatCommand::AMuteListChatCommand()
{
    CommandName          = TEXT("mutelist");
    MinNumberOfArguments = 0;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "MuteListUsage", "/mutelist [page]");
}

EExecutionStatus AMuteListChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString CallerId;
    const UBanChatCommandsConfig* Cfg = UBanChatCommandsConfig::Get();
    if (!BanChat::IsAdminSender(Sender, CallerId, false))
    {
        if (!Cfg || !Cfg->IsModeratorUid(CallerId))
        {
            if (Sender) Sender->SendChatMessage(
                TEXT("[BanChatCommands] You do not have permission to use this command."),
                FLinearColor::Red);
            return EExecutionStatus::INSUFFICIENT_PERMISSIONS;
        }
    }

    UWorld* World = GetWorld();
    if (!World) return EExecutionStatus::UNCOMPLETED;
    UGameInstance* GI = World->GetGameInstance();
    if (!GI) return EExecutionStatus::UNCOMPLETED;

    UMuteRegistry* MuteReg = GI->GetSubsystem<UMuteRegistry>();
    if (!MuteReg)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] MuteRegistry unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    TArray<FMuteEntry> Mutes = MuteReg->GetAllMutes();
    if (Mutes.IsEmpty())
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] No players are currently muted."), FLinearColor::Green);
        return EExecutionStatus::COMPLETED;
    }

    const int32 PageSize    = Cfg ? FMath::Clamp(Cfg->BanListPageSize, 1, 50) : 10;
    const int32 Page        = (Arguments.Num() > 0 && Arguments[0].IsNumeric()
                               && Arguments[0].Len() <= 9)
        ? FMath::Max(1, FCString::Atoi(*Arguments[0])) : 1;
    const int32 TotalPages  = FMath::DivideAndRoundUp(Mutes.Num(), PageSize);
    const int32 PageClamped = FMath::Clamp(Page, 1, TotalPages);
    const int32 Start       = (PageClamped - 1) * PageSize;
    const int32 End         = FMath::Min(Start + PageSize, Mutes.Num());

    Sender->SendChatMessage(
        FString::Printf(TEXT("[BanChatCommands] Muted players (page %d of %d, total %d):"),
            PageClamped, TotalPages, Mutes.Num()),
        FLinearColor::Yellow);

    for (int32 i = Start; i < End; ++i)
    {
        const FMuteEntry& M = Mutes[i];
        const FString ExpiryStr = M.bIsIndefinite
            ? TEXT("indefinite")
            : FString::Printf(TEXT("expires: %s UTC"), *M.ExpireDate.ToString(TEXT("%Y-%m-%d %H:%M:%S")));
        Sender->SendChatMessage(
            FString::Printf(TEXT("  %s (%s) — reason: %s [%s]"),
                *M.PlayerName, *M.Uid, *M.Reason, *ExpiryStr),
            FLinearColor::White);
    }

    if (TotalPages > 1)
    {
        Sender->SendChatMessage(
            TEXT("[BanChatCommands] Use /mutelist <page> to view more."),
            FLinearColor::White);
    }

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  AClearWarnByIdChatCommand  — /clearwarn <id>
// ─────────────────────────────────────────────────────────────────────────────

AClearWarnByIdChatCommand::AClearWarnByIdChatCommand()
{
    CommandName          = TEXT("clearwarn");
    MinNumberOfArguments = 1;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "ClearWarnByIdUsage", "/clearwarn <id>");
}

EExecutionStatus AClearWarnByIdChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminUid;
    if (!BanChat::IsAdminSender(Sender, AdminUid))
        return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    if (!Arguments[0].IsNumeric())
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] Usage: /clearwarn <numeric warning ID>"), FLinearColor::Red);
        return EExecutionStatus::BAD_ARGUMENTS;
    }

    // Guard against int64 overflow: Atoi64 is undefined for strings longer than
    // 19 digits, and a 19-digit string can still exceed INT64_MAX.  Same check
    // used by BanRestApi's ParseInt64Param helper.
    {
        const int32 IdLen = Arguments[0].Len();
        if (IdLen > 19 || (IdLen == 19 && Arguments[0] > TEXT("9223372036854775807")))
        {
            Sender->SendChatMessage(TEXT("[BanChatCommands] Warning ID is out of range."), FLinearColor::Red);
            return EExecutionStatus::BAD_ARGUMENTS;
        }
    }

    const int64 WarnId = FCString::Atoi64(*Arguments[0]);
    if (WarnId <= 0)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] Warning ID must be a positive integer."), FLinearColor::Red);
        return EExecutionStatus::BAD_ARGUMENTS;
    }

    UWorld* World = GetWorld();
    if (!World) return EExecutionStatus::UNCOMPLETED;
    UGameInstance* GI = World->GetGameInstance();
    if (!GI) return EExecutionStatus::UNCOMPLETED;

    UPlayerWarningRegistry* WarnReg = GI->GetSubsystem<UPlayerWarningRegistry>();
    if (!WarnReg)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] PlayerWarningRegistry unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    if (!WarnReg->DeleteWarningById(WarnId))
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] No warning found with ID %lld."), WarnId),
            FLinearColor::Yellow);
        return EExecutionStatus::COMPLETED;
    }

    if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
        AuditLog->LogAction(TEXT("deletewarn_id"),
            FString::Printf(TEXT("warning#%lld"), WarnId), TEXT(""),
            AdminUid, Sender->GetSenderName(),
            FString::Printf(TEXT("Deleted warning id %lld"), WarnId));

    Sender->SendChatMessage(
        FString::Printf(TEXT("[BanChatCommands] Deleted warning #%lld."), WarnId),
        FLinearColor::Green);
    return EExecutionStatus::COMPLETED;
}
// ─────────────────────────────────────────────────────────────────────────────

AExtendBanChatCommand::AExtendBanChatCommand()
{
    CommandName          = TEXT("extend");
    MinNumberOfArguments = 2;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "ExtendBanUsage",
        "/extend <player|PUID> <duration>  — duration: 30m, 1h, 1d, 1w, 2h30m, or plain minutes");
}

EExecutionStatus AExtendBanChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminUid;
    if (!BanChat::IsAdminSender(Sender, AdminUid))
        return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    FString Uid, DisplayName;
    if (!BanChat::ResolveTarget(this, Sender, Arguments[0], Uid, DisplayName))
        return EExecutionStatus::BAD_ARGUMENTS;

    const int32 ExtraMinutes = BanChat::ParseDurationMinutes(Arguments[1]);
    if (ExtraMinutes <= 0)
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] Invalid duration '%s'."), *Arguments[1]),
            FLinearColor::Red);
        return EExecutionStatus::BAD_ARGUMENTS;
    }

    UBanDatabase* DB = BanChat::GetDB(this);
    if (!DB)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] UBanDatabase unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    // Initial check — get primary UID and verify the ban exists and is not permanent.
    // The actual mutation is done inside UpdateBan() which holds the database lock
    // for the full read-modify-write, eliminating the TOCTOU window of AddBan().
    FBanEntry Entry;
    if (!DB->IsCurrentlyBannedByAnyId(Uid, Entry))
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] No active ban found for '%s'."), *DisplayName),
            FLinearColor::Yellow);
        return EExecutionStatus::COMPLETED;
    }

    if (Entry.bIsPermanent)
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] '%s' has a permanent ban; /extend only applies to temporary bans."), *DisplayName),
            FLinearColor::Yellow);
        return EExecutionStatus::COMPLETED;
    }

    const FString PrimaryUid   = Entry.Uid;
    const int32   MinutesToAdd = ExtraMinutes;

    bool bRaceWasPermanent = false;
    FBanEntry Updated;
    if (!DB->UpdateBan(PrimaryUid,
        [MinutesToAdd, &bRaceWasPermanent](FBanEntry& E)
        {
            // Re-check inside the lock: a concurrent /ban permanent could have
            // upgraded this entry between our initial check and the UpdateBan call.
            if (E.bIsPermanent)
            {
                bRaceWasPermanent = true;
                return;
            }
            // Re-read ExpireDate inside the lock so the extension is always
            // relative to the freshest known expiry, not a stale snapshot.
            const FDateTime BaseTime = FMath::Max(E.ExpireDate, FDateTime::UtcNow());
            E.ExpireDate  = BaseTime + FTimespan::FromMinutes(MinutesToAdd);
            E.bIsPermanent = false;
        },
        Updated))
    {
        // Concurrent unban raced the update.
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] Ban for '%s' was removed concurrently — not extended."), *DisplayName),
            FLinearColor::Yellow);
        return EExecutionStatus::COMPLETED;
    }

    // Abort if the ban was upgraded to permanent inside the lock.
    if (bRaceWasPermanent)
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] '%s' now has a permanent ban — /extend only applies to temporary bans."), *DisplayName),
            FLinearColor::Yellow);
        return EExecutionStatus::COMPLETED;
    }
    // UpdateBan fires OnBanUpdated, which BanDiscordSubsystem's BanUpdatedHandle
    // picks up and posts the updated ban to the moderation log automatically.

    UWorld* World = GetWorld();
    if (World)
    {
        UGameInstance* GI = World->GetGameInstance();
        UBanAuditLog* AuditLog = GI ? GI->GetSubsystem<UBanAuditLog>() : nullptr;
        if (AuditLog)
            AuditLog->LogAction(TEXT("extend"), Updated.Uid, DisplayName, AdminUid, Sender->GetSenderName(),
                FString::Printf(TEXT("Extended by %d min -> new expiry %s UTC"),
                    ExtraMinutes, *Updated.ExpireDate.ToString(TEXT("%Y-%m-%d %H:%M:%S"))));
    }

    Sender->SendChatMessage(
        FString::Printf(TEXT("[BanChatCommands] Ban for '%s' extended by %s. New expiry: %s UTC."),
            *DisplayName, *BanChat::FormatDuration(ExtraMinutes),
            *Updated.ExpireDate.ToString(TEXT("%Y-%m-%d %H:%M:%S"))),
        FLinearColor::Green);
    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  AAppealChatCommand  — /appeal
// ─────────────────────────────────────────────────────────────────────────────

AAppealChatCommand::AAppealChatCommand()
{
    CommandName          = TEXT("appeal");
    MinNumberOfArguments = 1;
    bOnlyUsableByPlayer  = true;
    Usage = NSLOCTEXT("BanChatCommands", "AppealUsage", "/appeal <reason...>");
}

EExecutionStatus AAppealChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    // Resolve caller UID.
    FString CallerUid;
    APlayerController* PC = Cast<APlayerController>(Sender->GetPlayer());
    if (PC && PC->PlayerState)
    {
        const FUniqueNetIdRepl& UniqueId = PC->PlayerState->GetUniqueId();
        if (UniqueId.IsValid() && UniqueId.GetType() != FName(TEXT("NONE")))
            CallerUid = UBanDatabase::MakeUid(TEXT("EOS"), UniqueId.ToString().ToLower());
        else
        {
            const FString EosPuid = UBanEnforcer::ExtractEosPuidFromConnectionUrl(PC);
            if (!EosPuid.IsEmpty())
                CallerUid = UBanDatabase::MakeUid(TEXT("EOS"), EosPuid);
        }
    }

    if (CallerUid.IsEmpty())
    {
        Sender->SendChatMessage(
            TEXT("[BanChatCommands] Could not determine your player identity for the appeal."),
            FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    const FString Reason = BanChat::JoinArgs(Arguments, 0);

    UWorld* World = GetWorld();
    if (!World) return EExecutionStatus::UNCOMPLETED;
    UGameInstance* GI = World->GetGameInstance();
    if (!GI) return EExecutionStatus::UNCOMPLETED;

    UBanAppealRegistry* AppealReg = GI->GetSubsystem<UBanAppealRegistry>();
    if (!AppealReg)
    {
        Sender->SendChatMessage(
            TEXT("[BanChatCommands] Appeal system unavailable. Contact server staff directly."),
            FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    AppealReg->AddAppeal(CallerUid, Reason, TEXT("in-game"));

    UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>();
    if (AuditLog)
    {
        const FString PlayerName = (PC && PC->PlayerState) ? PC->PlayerState->GetPlayerName() : TEXT("");
        AuditLog->LogAction(TEXT("appeal"), CallerUid, PlayerName, CallerUid, Sender->GetSenderName(), Reason);
    }

    Sender->SendChatMessage(
        TEXT("[BanChatCommands] Your appeal has been submitted. Server staff will review it."),
        FLinearColor::Green);
    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  AMuteReasonChatCommand  — /mutereason
// ─────────────────────────────────────────────────────────────────────────────

AMuteReasonChatCommand::AMuteReasonChatCommand()
{
    CommandName          = TEXT("mutereason");
    MinNumberOfArguments = 2;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "MuteReasonUsage",
        "/mutereason <player|PUID> <new reason...>");
}

EExecutionStatus AMuteReasonChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminId;
    if (!BanChat::IsAdminSender(Sender, AdminId))
        return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    FString Uid, DisplayName;
    if (!BanChat::ResolveTarget(this, Sender, Arguments[0], Uid, DisplayName))
        return EExecutionStatus::BAD_ARGUMENTS;

    UWorld* World = GetWorld();
    if (!World) return EExecutionStatus::UNCOMPLETED;
    UGameInstance* GI = World->GetGameInstance();
    if (!GI) return EExecutionStatus::UNCOMPLETED;

    UMuteRegistry* MuteReg = GI->GetSubsystem<UMuteRegistry>();
    if (!MuteReg)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] MuteRegistry unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    FMuteEntry Entry;
    if (!MuteReg->GetMuteEntry(Uid, Entry))
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] No active mute found for '%s'."), *DisplayName),
            FLinearColor::Yellow);
        return EExecutionStatus::COMPLETED;
    }

    const FString NewReason = BanChat::JoinArgs(Arguments, 1);
    if (!MuteReg->UpdateMuteReason(Uid, NewReason))
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] Could not update mute reason for '%s' — mute may have just expired."), *DisplayName),
            FLinearColor::Yellow);
        return EExecutionStatus::COMPLETED;
    }

    if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
        AuditLog->LogAction(TEXT("mutereason"), Uid, DisplayName, AdminId, Sender->GetSenderName(), NewReason);

    Sender->SendChatMessage(
        FString::Printf(TEXT("[BanChatCommands] Updated mute reason for '%s'."), *DisplayName),
        FLinearColor::Green);

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  AFreezeChatCommand  — /freeze / /spectator
// ─────────────────────────────────────────────────────────────────────────────

// THREADING: FrozenPlayerUids is accessed exclusively from the game thread
// (ExecuteCommand_Implementation, PostLoginHandle, and LogoutHookHandle all run
// on the game thread).  Do NOT read or write this set from any other thread.
TSet<FString> AFreezeChatCommand::FrozenPlayerUids;

AFreezeChatCommand::AFreezeChatCommand()
{
    CommandName          = TEXT("freeze");
    MinNumberOfArguments = 1;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "FreezeUsage",
        "/freeze <player|PUID>  — toggle player freeze (repeat to unfreeze)");
}

EExecutionStatus AFreezeChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    // FrozenPlayerUids is game-thread-only; catch any future SML change early.
    check(IsInGameThread());

    FString AdminId;
    if (!BanChat::IsAdminSender(Sender, AdminId))
        return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    FString Uid, DisplayName;
    if (!BanChat::ResolveTarget(this, Sender, Arguments[0], Uid, DisplayName))
        return EExecutionStatus::BAD_ARGUMENTS;

    UWorld* World = GetWorld();
    if (!World) return EExecutionStatus::UNCOMPLETED;

    // Determine the intended action based on whether the UID is currently
    // frozen.  We check whether the player is online so that admins can
    // issue /freeze against an offline player without the toggle appearing
    // to do the wrong thing: if the player is offline AND already in the
    // frozen set, pressing /freeze again still toggles them to unfrozen
    // (their freeze will not be re-applied when they reconnect), which is
    // the most intuitive behaviour.
    const bool bWasFrozen = FrozenPlayerUids.Contains(Uid);

    // Check whether the target player is currently online.
    bool bFoundOnline = false;
    APlayerController* TargetPC = nullptr;
    for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PC = It->Get();
        if (!PC || !PC->PlayerState) continue;
        const FUniqueNetIdRepl& PcId = PC->PlayerState->GetUniqueId();
        FString PcUid;
        if (PcId.IsValid() && PcId.GetType() != FName(TEXT("NONE")))
        {
            PcUid = UBanDatabase::MakeUid(TEXT("EOS"), PcId.ToString().ToLower());
        }
        else
        {
            const FString EosPuid = UBanEnforcer::ExtractEosPuidFromConnectionUrl(PC);
            if (!EosPuid.IsEmpty())
                PcUid = UBanDatabase::MakeUid(TEXT("EOS"), EosPuid);
        }
        if (PcUid == Uid)
        {
            bFoundOnline = true;
            TargetPC = PC;
            break;
        }
    }

    if (bWasFrozen)
    {
        FrozenPlayerUids.Remove(Uid);

        if (bFoundOnline && TargetPC)
            TargetPC->SetIgnoreMoveInput(false);

        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] %s has been unfrozen."), *DisplayName),
            FLinearColor::Green);
    }
    else
    {
        FrozenPlayerUids.Add(Uid);

        if (bFoundOnline && TargetPC)
        {
            TargetPC->SetIgnoreMoveInput(true);
            Sender->SendChatMessage(
                FString::Printf(TEXT("[BanChatCommands] %s has been frozen. Run /freeze again to unfreeze."), *DisplayName),
                FLinearColor::Yellow);
        }
        else
        {
            // Player is offline — the freeze will be applied automatically when
            // they reconnect via the PostLogin hook in BanChatCommandsModule.
            Sender->SendChatMessage(
                FString::Printf(TEXT("[BanChatCommands] %s is not online — they will be frozen automatically when they reconnect."), *DisplayName),
                FLinearColor::Yellow);
        }
    }

    // Write to the audit log so freeze/unfreeze actions appear in the trail.
    {
        UGameInstance* GI = World->GetGameInstance();
        if (UBanAuditLog* AuditLog = GI ? GI->GetSubsystem<UBanAuditLog>() : nullptr)
            AuditLog->LogAction(bWasFrozen ? TEXT("unfreeze") : TEXT("freeze"),
                Uid, DisplayName, AdminId, Sender->GetSenderName(), TEXT(""));
    }

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  AClearChatChatCommand  — /clearchat
// ─────────────────────────────────────────────────────────────────────────────

AClearChatChatCommand::AClearChatChatCommand()
{
    CommandName          = TEXT("clearchat");
    MinNumberOfArguments = 0;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "ClearChatUsage",
        "/clearchat [reason...]  — flush chat and notify Discord");
}

EExecutionStatus AClearChatChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminId;
    if (!BanChat::IsAdminSender(Sender, AdminId))
        return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    const FString Reason = Arguments.Num() > 0
        ? BanChat::JoinArgs(Arguments, 0)
        : TEXT("Chat cleared by administrator");
    const FString AdminName = Sender->GetSenderName();

    UWorld* World = GetWorld();
    if (!World) return EExecutionStatus::UNCOMPLETED;

    // Broadcast blank lines to visually scroll chat off screen.
    for (int32 i = 0; i < 30; ++i)
        for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
            if (APlayerController* PC = It->Get())
                PC->ClientMessage(TEXT(" "));

    // Notify all players.
    const FString Notice = FString::Printf(
        TEXT("Chat has been cleared by %s. Reason: %s"), *AdminName, *Reason);
    for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
        if (APlayerController* PC = It->Get())
            PC->ClientMessage(Notice);

    // Post to BanSystem Discord webhook.
    {
        const UBanSystemConfig* SysCfg = UBanSystemConfig::Get();
        if (SysCfg && !SysCfg->DiscordWebhookUrl.IsEmpty()
            && FModuleManager::Get().IsModuleLoaded(TEXT("HTTP")))
        {
            const FString JsonPayload = FString::Printf(
                TEXT("{\"embeds\":[{\"title\":\"Chat Cleared\",\"color\":3447003,\"fields\":["
                    "{\"name\":\"Admin\",\"value\":\"%s\",\"inline\":true},"
                    "{\"name\":\"Reason\",\"value\":\"%s\",\"inline\":false}],"
                    "\"timestamp\":\"%s\"}]}"),
                *BanChat::JsonEscape(BanChat::EscapeMarkdown(AdminName)),
            *BanChat::JsonEscape(BanChat::EscapeMarkdown(Reason)), *FDateTime::UtcNow().ToIso8601());

            TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Req =
                FHttpModule::Get().CreateRequest();
            Req->SetURL(SysCfg->DiscordWebhookUrl);
            Req->SetVerb(TEXT("POST"));
            Req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
            Req->SetContentAsString(JsonPayload);
            Req->ProcessRequest();
        }
    }

    Sender->SendChatMessage(
        FString::Printf(TEXT("[BanChatCommands] Chat cleared. Reason: %s"), *Reason),
        FLinearColor::Green);

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  AReportChatCommand  — /report
// ─────────────────────────────────────────────────────────────────────────────

AReportChatCommand::AReportChatCommand()
{
    CommandName          = TEXT("report");
    MinNumberOfArguments = 1;
    bOnlyUsableByPlayer  = true;
    Usage = NSLOCTEXT("BanChatCommands", "ReportUsage",
        "/report <player> [reason...]  — flag a player for staff review");
}

EExecutionStatus AReportChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    // Available to all players — no admin check required.
    // Derive the sender's UID for cooldown keying.
    FString SenderUid;
    {
        APlayerController* PC = Cast<APlayerController>(Sender->GetPlayer());
        if (PC && PC->PlayerState)
        {
            const FUniqueNetIdRepl& Id = PC->PlayerState->GetUniqueId();
            if (Id.IsValid() && Id.GetType() != FName(TEXT("NONE")))
                SenderUid = UBanDatabase::MakeUid(TEXT("EOS"), Id.ToString().ToLower());
            else
            {
                const FString EosPuid = UBanEnforcer::ExtractEosPuidFromConnectionUrl(PC);
                if (!EosPuid.IsEmpty())
                    SenderUid = UBanDatabase::MakeUid(TEXT("EOS"), EosPuid);
            }
        }
    }

    // 30-second per-sender cooldown to prevent spam.
    const FString CooldownKey = SenderUid.IsEmpty() ? Sender->GetSenderName() : SenderUid;
    {
        int32 RemainingCoolSecs = 0;
        if (BanChat::IsOnCooldown(Sender, TEXT("report"), 30, CooldownKey, &RemainingCoolSecs))
        {
            Sender->SendChatMessage(
                FString::Printf(TEXT("[BanChatCommands] Please wait %d second(s) before submitting another report."),
                    RemainingCoolSecs),
                FLinearColor::Yellow);
            return EExecutionStatus::UNCOMPLETED;
        }
    }

    const FString TargetName = Arguments[0];
    const FString Reason = Arguments.Num() > 1
        ? BanChat::JoinArgs(Arguments, 1)
        : TEXT("No reason given");
    const FString ReporterName = Sender->GetSenderName();

    Sender->SendChatMessage(
        FString::Printf(TEXT("[BanChatCommands] Report submitted against '%s'. Staff have been notified."), *TargetName),
        FLinearColor::Green);

    // Post to Discord via ReportWebhookUrl.
    const UBanChatCommandsConfig* Cfg = UBanChatCommandsConfig::Get();
    const FString WebhookUrl = Cfg ? Cfg->ReportWebhookUrl : TEXT("");
    if (!WebhookUrl.IsEmpty() && FModuleManager::Get().IsModuleLoaded(TEXT("HTTP")))
    {
        const FString JsonPayload = FString::Printf(
            TEXT("{\"embeds\":[{\"title\":\"Player Report\",\"color\":16744272,\"fields\":["
                "{\"name\":\"Reported Player\",\"value\":\"%s\",\"inline\":true},"
                "{\"name\":\"Reported By\",\"value\":\"%s\",\"inline\":true},"
                "{\"name\":\"Reason\",\"value\":\"%s\",\"inline\":false}],"
                "\"timestamp\":\"%s\"}]}"),
            *BanChat::JsonEscape(BanChat::EscapeMarkdown(TargetName)),
            *BanChat::JsonEscape(BanChat::EscapeMarkdown(ReporterName)),
            *BanChat::JsonEscape(BanChat::EscapeMarkdown(Reason)), *FDateTime::UtcNow().ToIso8601());

        TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Req =
            FHttpModule::Get().CreateRequest();
        Req->SetURL(WebhookUrl);
        Req->SetVerb(TEXT("POST"));
        Req->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
        Req->SetContentAsString(JsonPayload);
        Req->ProcessRequest();
    }

    // Log the report so staff can review it from the audit log.
    UWorld* World = GetWorld();
    UGameInstance* GI = World ? World->GetGameInstance() : nullptr;
    if (GI)
    {
        if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
        {
            const FString CallerId = SenderUid.IsEmpty() ? ReporterName : SenderUid;
            AuditLog->LogAction(TEXT("report"), TEXT(""), TargetName, CallerId, ReporterName, Reason);
        }
    }

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  AScheduleBanChatCommand  — /scheduleban
// ─────────────────────────────────────────────────────────────────────────────

AScheduleBanChatCommand::AScheduleBanChatCommand()
{
    CommandName          = TEXT("scheduleban");
    MinNumberOfArguments = 0;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "ScheduleBanUsage",
        "/scheduleban <player|PUID> <delay> [banDuration] [reason...]  — ban a player at a future time");
}

EExecutionStatus AScheduleBanChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminUid;
    if (!BanChat::IsAdminSender(Sender, AdminUid)) return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    // List pending scheduled bans when no arguments.
    if (Arguments.IsEmpty())
    {
        UWorld* W = GetWorld();
        UGameInstance* GI = W ? W->GetGameInstance() : nullptr;
        UScheduledBanRegistry* SchReg = GI ? GI->GetSubsystem<UScheduledBanRegistry>() : nullptr;
        if (!SchReg)
        {
            Sender->SendChatMessage(TEXT("[BanChatCommands] ScheduledBanRegistry unavailable."), FLinearColor::Red);
            return EExecutionStatus::UNCOMPLETED;
        }
        TArray<FScheduledBanEntry> Pending = SchReg->GetAllPending();
        if (Pending.IsEmpty())
        {
            Sender->SendChatMessage(TEXT("[BanChatCommands] No pending scheduled bans."), FLinearColor::White);
        }
        else
        {
            Sender->SendChatMessage(
                FString::Printf(TEXT("[BanChatCommands] %d scheduled ban(s):"), Pending.Num()),
                FLinearColor::White);
            for (const FScheduledBanEntry& S : Pending)
            {
                Sender->SendChatMessage(
                    FString::Printf(TEXT("  #%lld  %s  at %s  [%s]"),
                        S.Id, *S.Uid, *S.EffectiveAt.ToString(TEXT("%Y-%m-%d %H:%M:%S")), *S.Reason),
                    FLinearColor::White);
            }
        }
        return EExecutionStatus::COMPLETED;
    }

    if (Arguments.Num() < 2)
    {
        Sender->SendChatMessage(
            TEXT("[BanChatCommands] Usage: /scheduleban <player|PUID> <delay> [banDuration] [reason...]"),
            FLinearColor::Yellow);
        return EExecutionStatus::BAD_ARGUMENTS;
    }

    const FString TargetArg = Arguments[0];
    const FString DelayStr  = Arguments[1];

    int32 DelayMinutes = BanChat::ParseDurationMinutes(DelayStr);
    if (DelayMinutes <= 0)
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] Invalid delay '%s'. Use format like 30m, 2h, 1d."), *DelayStr),
            FLinearColor::Yellow);
        return EExecutionStatus::BAD_ARGUMENTS;
    }

    // Optional ban duration (3rd argument).
    int32 BanDurationMinutes = 0; // 0 = permanent
    int32 ReasonStartIdx = 2;
    if (Arguments.Num() > 2)
    {
        // Explicit "permanent" markers — check before ParseDurationMinutes so that
        // "0" is not silently clamped to 1 minute by FMath::Max(1, Atoi("0")).
        if (Arguments[2].Equals(TEXT("perm"), ESearchCase::IgnoreCase)
            || Arguments[2].Equals(TEXT("permanent"), ESearchCase::IgnoreCase)
            || Arguments[2] == TEXT("0"))
        {
            BanDurationMinutes = 0;
            ReasonStartIdx = 3;
        }
        else
        {
            const int32 Parsed = BanChat::ParseDurationMinutes(Arguments[2]);
            if (Parsed > 0)
            {
                BanDurationMinutes = Parsed;
                ReasonStartIdx = 3;
            }
        }
    }

    const FString Reason = Arguments.Num() > ReasonStartIdx
        ? BanChat::JoinArgs(Arguments, ReasonStartIdx)
        : TEXT("Scheduled ban");

    // Resolve target UID.
    FString Uid, PlayerName;
    if (!BanChat::ResolveTarget(this, Sender, TargetArg, Uid, PlayerName))
        return EExecutionStatus::BAD_ARGUMENTS;

    const FString AdminName = Sender->GetSenderName();
    const FDateTime EffectiveAt = FDateTime::UtcNow() + FTimespan::FromMinutes(DelayMinutes);

    UWorld* W = GetWorld();
    UGameInstance* GI = W ? W->GetGameInstance() : nullptr;
    UScheduledBanRegistry* SchReg = GI ? GI->GetSubsystem<UScheduledBanRegistry>() : nullptr;
    if (!SchReg)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] ScheduledBanRegistry unavailable."), FLinearColor::Red);
        return EExecutionStatus::UNCOMPLETED;
    }

    FScheduledBanEntry Entry = SchReg->AddScheduled(
        Uid, PlayerName, Reason, AdminName, EffectiveAt, BanDurationMinutes);

    const FString DurationStr = (BanDurationMinutes == 0)
        ? TEXT("permanent")
        : BanChat::FormatDuration(BanDurationMinutes).Mid(4);

    Sender->SendChatMessage(
        FString::Printf(TEXT("[BanChatCommands] Scheduled ban #%lld for %s in %d minutes (%s). Duration: %s. Reason: %s"),
            Entry.Id, *PlayerName, DelayMinutes, *EffectiveAt.ToString(TEXT("%Y-%m-%d %H:%M:%S")),
            *DurationStr, *Reason),
        FLinearColor::Green);

    if (UBanAuditLog* AuditLog = GI ? GI->GetSubsystem<UBanAuditLog>() : nullptr)
        AuditLog->LogAction(TEXT("schedule_ban"), Uid, PlayerName, AdminUid, AdminName, Reason);

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  AQBanChatCommand  — /qban (quick-ban from template)
// ─────────────────────────────────────────────────────────────────────────────

AQBanChatCommand::AQBanChatCommand()
{
    CommandName          = TEXT("qban");
    MinNumberOfArguments = 0;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "QBanUsage",
        "/qban <templateSlug> <player|PUID>  — quick-ban using a preset template");
}

EExecutionStatus AQBanChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminUid;
    if (!BanChat::IsAdminSender(Sender, AdminUid)) return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    const UBanSystemConfig* SysCfg = UBanSystemConfig::Get();
    if (!SysCfg || SysCfg->BanTemplates.IsEmpty())
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] No ban templates configured (BanTemplates= in DefaultBanSystem.ini)."), FLinearColor::Yellow);
        return EExecutionStatus::COMPLETED;
    }

    // Parse pipe-delimited template strings into FBanTemplate structs.
    const TArray<FBanTemplate> Templates = FBanTemplate::ParseTemplates(SysCfg->BanTemplates);

    // List templates when no arguments or only template name given.
    if (Arguments.IsEmpty())
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] Available ban templates:"), FLinearColor::White);
        for (const FBanTemplate& T : Templates)
        {
            Sender->SendChatMessage(
                FString::Printf(TEXT("  %s  |  %s  |  %s"),
                    *T.Slug,
                    T.DurationMinutes == 0 ? TEXT("permanent") : *BanChat::FormatDuration(T.DurationMinutes).Mid(4),
                    *T.Reason),
                FLinearColor::White);
        }
        return EExecutionStatus::COMPLETED;
    }

    if (Arguments.Num() < 2)
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] Usage: /qban <templateSlug> <player|PUID>"), FLinearColor::Yellow);
        return EExecutionStatus::COMPLETED;
    }

    const FString Slug      = Arguments[0].ToLower();
    const FString TargetArg = Arguments[1];

    // Find the template.
    const FBanTemplate* Template = nullptr;
    for (const FBanTemplate& T : Templates)
    {
        if (T.Slug.ToLower() == Slug) { Template = &T; break; }
    }
    if (!Template)
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] Unknown template '%s'. Use /qban to list templates."), *Slug),
            FLinearColor::Yellow);
        return EExecutionStatus::COMPLETED;
    }

    // Resolve target.
    FString Uid, PlayerName;
    if (!BanChat::ResolveTarget(this, Sender, TargetArg, Uid, PlayerName))
        return EExecutionStatus::BAD_ARGUMENTS;

    UBanDatabase* DB = BanChat::GetDB(this);
    if (!DB) { Sender->SendChatMessage(TEXT("[BanChatCommands] Database unavailable."), FLinearColor::Red); return EExecutionStatus::UNCOMPLETED; }

    const FString AdminName = Sender->GetSenderName();

    FBanEntry Ban;
    Ban.Uid        = Uid;
    UBanDatabase::ParseUid(Uid, Ban.Platform, Ban.PlayerUID);
    Ban.PlayerName      = PlayerName;
    Ban.Reason          = Template->Reason;
    Ban.BannedBy        = AdminName;
    const FDateTime TemplateChatBanNow = FDateTime::UtcNow();
    Ban.BanDate         = TemplateChatBanNow;
    Ban.Category        = Template->Category;
    Ban.bIsPermanent    = (Template->DurationMinutes <= 0);
    Ban.ExpireDate      = Ban.bIsPermanent
        ? FDateTime(0)
        : TemplateChatBanNow + FTimespan::FromMinutes(Template->DurationMinutes);

    // For temporary templates, use AddBanSkipIfPermanentExists to prevent
    // silently downgrading an existing permanent ban.
    bool bQBanChatSkipped = false;
    const bool bQBanChatAdded = Ban.bIsPermanent
        ? DB->AddBan(Ban)
        : DB->AddBanSkipIfPermanentExists(Ban, bQBanChatSkipped);
    if (!bQBanChatAdded)
    {
        if (bQBanChatSkipped)
            Sender->SendChatMessage(
                FString::Printf(TEXT("[BanChatCommands] %s already has a permanent ban — template ban not applied."), *PlayerName),
                FLinearColor::Yellow);
        else
            Sender->SendChatMessage(TEXT("[BanChatCommands] Failed to apply ban."), FLinearColor::Red);
        return EExecutionStatus::COMPLETED;
    }

    // Kick if online.
    if (UWorld* W = GetWorld())
        UBanEnforcer::KickConnectedPlayer(W, Uid, Ban.GetKickMessage());

    // Also ban counterpart identifiers (IP↔EOS).
    BanChat::AddCounterpartBans(this, Sender, Uid, PlayerName,
        Template->DurationMinutes, Template->Reason, AdminName);

    FBanDiscordNotifier::NotifyBanCreated(Ban);

    UWorld* W = GetWorld();
    UGameInstance* GI = W ? W->GetGameInstance() : nullptr;
    if (UBanAuditLog* AuditLog = GI ? GI->GetSubsystem<UBanAuditLog>() : nullptr)
        AuditLog->LogAction(TEXT("ban"), Uid, PlayerName, AdminUid, AdminName,
            FString::Printf(TEXT("[qban:%s] %s"), *Slug, *Template->Reason));

    Sender->SendChatMessage(
        FString::Printf(TEXT("[BanChatCommands] [%s] Banned %s. Reason: %s"),
            *Slug, *PlayerName, *Template->Reason),
        FLinearColor::Green);

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  AReputationChatCommand  — /reputation
// ─────────────────────────────────────────────────────────────────────────────

AReputationChatCommand::AReputationChatCommand()
{
    CommandName          = TEXT("reputation");
    MinNumberOfArguments = 1;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "ReputationUsage",
        "/reputation <player|PUID>  — show a player's reputation score");
}

EExecutionStatus AReputationChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminUid;
    if (!BanChat::IsAdminSender(Sender, AdminUid)) return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    const FString TargetArg = Arguments[0];
    FString Uid, PlayerName;
    if (!BanChat::ResolveTarget(this, Sender, TargetArg, Uid, PlayerName))
        return EExecutionStatus::BAD_ARGUMENTS;

    UWorld* W = GetWorld();
    UGameInstance* GI = W ? W->GetGameInstance() : nullptr;
    if (!GI) { Sender->SendChatMessage(TEXT("[BanChatCommands] GameInstance unavailable."), FLinearColor::Red); return EExecutionStatus::UNCOMPLETED; }

    UBanDatabase*           DB        = GI->GetSubsystem<UBanDatabase>();
    UPlayerWarningRegistry* WarnReg   = GI->GetSubsystem<UPlayerWarningRegistry>();
    UPlayerSessionRegistry* PlayerReg = GI->GetSubsystem<UPlayerSessionRegistry>();
    UBanAuditLog*           AuditLog  = GI->GetSubsystem<UBanAuditLog>();

    const int32 WarnCount  = WarnReg  ? WarnReg->GetWarningCount(Uid)  : 0;
    const int32 WarnPoints = WarnReg  ? WarnReg->GetWarningPoints(Uid) : 0;

    // Count all historical bans.
    int32 TotalBans = 0;
    bool  bCurrentlyBanned = false;
    if (DB)
    {
        for (const FBanEntry& B : DB->GetAllBans())
        {
            if (B.Uid.Equals(Uid, ESearchCase::IgnoreCase))
            {
                ++TotalBans;
                if (!B.IsExpired()) bCurrentlyBanned = true;
            }
        }
    }

    // Count kicks in audit log.
    int32 KickCount = 0;
    if (AuditLog)
    {
        for (const FAuditEntry& E : AuditLog->GetEntriesForTarget(Uid))
        {
            if (E.Action == TEXT("kick")) ++KickCount;
        }
    }

    // Last seen.
    FString LastSeen = TEXT("unknown");
    if (PlayerReg)
    {
        FPlayerSessionRecord Rec;
        if (PlayerReg->FindByUid(Uid, Rec))
        {
            LastSeen    = Rec.LastSeen;
            PlayerName  = Rec.DisplayName;
        }
    }

    // Reputation score.
    const int64 ScoreRaw = static_cast<int64>(100)
        - (static_cast<int64>(WarnPoints) * 5)
        - (static_cast<int64>(TotalBans)  * 15)
        - (static_cast<int64>(KickCount)  * 3);
    const int32 Score = static_cast<int32>(FMath::Max((int64)0, ScoreRaw));

    FString ScoreLabel;
    FLinearColor Color;
    if (Score >= 70)       { ScoreLabel = TEXT("Good");      Color = FLinearColor::Green; }
    else if (Score >= 40)  { ScoreLabel = TEXT("Moderate");  Color = FLinearColor::Yellow; }
    else                   { ScoreLabel = TEXT("High Risk");  Color = FLinearColor::Red; }

    Sender->SendChatMessage(
        FString::Printf(TEXT("[Reputation] %s (%s)"), *PlayerName, *Uid), Color);
    Sender->SendChatMessage(
        FString::Printf(TEXT("  Score: %d/100 [%s]  Banned: %s"),
            Score, *ScoreLabel, bCurrentlyBanned ? TEXT("YES") : TEXT("no")),
        Color);
    Sender->SendChatMessage(
        FString::Printf(TEXT("  Warnings: %d (pts: %d)  Bans: %d  Kicks: %d  Last seen: %s"),
            WarnCount, WarnPoints, TotalBans, KickCount, *LastSeen),
        FLinearColor::White);

    return EExecutionStatus::COMPLETED;
}

// ─────────────────────────────────────────────────────────────────────────────
//  ABulkBanChatCommand  — /bulkban
// ─────────────────────────────────────────────────────────────────────────────

ABulkBanChatCommand::ABulkBanChatCommand()
{
    CommandName          = TEXT("bulkban");
    MinNumberOfArguments = 2;
    bOnlyUsableByPlayer  = false;
    Usage = NSLOCTEXT("BanChatCommands", "BulkBanUsage",
        "/bulkban <PUID1> <PUID2> ... -- <reason>  — ban multiple players at once");
}

EExecutionStatus ABulkBanChatCommand::ExecuteCommand_Implementation(
    UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label)
{
    FString AdminUid;
    if (!BanChat::IsAdminSender(Sender, AdminUid)) return EExecutionStatus::INSUFFICIENT_PERMISSIONS;

    UBanDatabase* DB = BanChat::GetDB(this);
    if (!DB) { Sender->SendChatMessage(TEXT("[BanChatCommands] Database unavailable."), FLinearColor::Red); return EExecutionStatus::UNCOMPLETED; }

    // Split on " -- " to separate UIDs from reason.
    TArray<FString> Uids;
    FString Reason = TEXT("Bulk ban");

    // Find " -- " separator in arguments.
    int32 SepIdx = -1;
    for (int32 i = 0; i < Arguments.Num(); ++i)
    {
        if (Arguments[i] == TEXT("--")) { SepIdx = i; break; }
    }

    if (SepIdx > 0 && SepIdx < Arguments.Num() - 1)
    {
        for (int32 i = 0; i < SepIdx; ++i)
            Uids.Add(Arguments[i]);
        Reason = BanChat::JoinArgs(Arguments, SepIdx + 1);
    }
    else
    {
        // No separator — all args are UIDs, no reason.
        Uids = Arguments;
    }

    if (Uids.IsEmpty())
    {
        Sender->SendChatMessage(TEXT("[BanChatCommands] Usage: /bulkban <PUID1> ... -- <reason>"), FLinearColor::Yellow);
        return EExecutionStatus::COMPLETED;
    }

    const FString AdminName = Sender->GetSenderName();
    UWorld* W = GetWorld();
    UGameInstance* GI = W ? W->GetGameInstance() : nullptr;
    int32 BannedCount = 0;

    for (const FString& RawUid : Uids)
    {
        // Validate: only accept 32-char hex EOS PUIDs in /bulkban to prevent
        // garbage entries from typos or malformed input.
        if (!BanChat::IsValidEOSPUID(RawUid))
        {
            Sender->SendChatMessage(
                FString::Printf(TEXT("[BanChatCommands] Skipping '%s' — not a valid 32-char hex EOS PUID."), *RawUid),
                FLinearColor::Yellow);
            continue;
        }

        const FString Uid = UBanDatabase::MakeUid(TEXT("EOS"), RawUid.ToLower());

        FBanEntry Ban;
        Ban.Uid        = Uid;
        UBanDatabase::ParseUid(Uid, Ban.Platform, Ban.PlayerUID);
        Ban.PlayerName      = RawUid;
        Ban.Reason          = Reason;
        Ban.BannedBy        = AdminName;
        Ban.BanDate         = FDateTime::UtcNow();
        Ban.bIsPermanent    = true;
        Ban.ExpireDate      = FDateTime(0);

        if (DB->AddBan(Ban))
        {
            if (W)
                UBanEnforcer::KickConnectedPlayer(W, Uid, Ban.GetKickMessage());

            FBanDiscordNotifier::NotifyBanCreated(Ban);

            // Ban counterpart identifiers (IP↔EOS) matching the Discord bulk-ban path.
            BanChat::AddCounterpartBans(this, Sender, Uid, RawUid, 0 /* permanent */, Reason, AdminName);

            if (UBanAuditLog* AuditLog = GI ? GI->GetSubsystem<UBanAuditLog>() : nullptr)
                AuditLog->LogAction(TEXT("ban"), Uid, RawUid, AdminUid, AdminName, Reason);

            ++BannedCount;
        }
    }

    if (BannedCount == 0)
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] Bulk ban failed — no valid UIDs were banned (0/%d). Reason: %s"),
                Uids.Num(), *Reason),
            FLinearColor::Red);
    }
    else
    {
        Sender->SendChatMessage(
            FString::Printf(TEXT("[BanChatCommands] Bulk ban complete: %d/%d players banned. Reason: %s"),
                BannedCount, Uids.Num(), *Reason),
            BannedCount == Uids.Num() ? FLinearColor::Green : FLinearColor::Yellow);
    }

    return EExecutionStatus::COMPLETED;
}
