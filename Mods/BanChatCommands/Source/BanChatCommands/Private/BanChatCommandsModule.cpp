// Copyright Yamahasxviper. All Rights Reserved.

#include "BanChatCommandsModule.h"
#include "BanChatCommandsConfig.h"
#include "Command/ChatCommandLibrary.h"
#include "Commands/BanChatCommands.h"
#include "MuteRegistry.h"
#include "BanWebSocketPusher.h"
#include "BanAuditLog.h"
#include "BanDatabase.h"
#include "BanEnforcer.h"
#include "Engine/World.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/Crc.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/OnlineReplStructs.h"
#include "Patching/NativeHookManager.h"

#define LOCTEXT_NAMESPACE "FBanChatCommandsModule"

void FBanChatCommandsModule::StartupModule()
{
    UE_LOG(LogBanChatCommands, Log, TEXT("BanChatCommands module starting up."));

    // Restore the annotated Default*.ini so operators can always read the
    // setting descriptions even after a mod update or fresh install.
    RestoreDefaultConfigIfNeeded();

    // On every server start, write a backup to Saved/BanChatCommands/BanChatCommands.ini.
    // That folder is never touched by mod updates so the admin list survives
    // any wipe of the mod directory.
    BackupConfigIfNeeded();

    // Record the initial admin-list hash so the first poll can detect changes.
    LastConfigHash = ComputeAdminHash();

    // Start the periodic config-reload ticker.  It fires every
    // ConfigPollIntervalSeconds seconds for the lifetime of the module,
    // reloading BanChatCommands.ini from disk and logging when the admin list
    // changes.  No server restart or manual /reloadconfig needed.
    ConfigPollHandle = FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateRaw(this, &FBanChatCommandsModule::OnConfigPollTick),
        ConfigPollIntervalSeconds);

    UE_LOG(LogBanChatCommands, Log,
        TEXT("BanChatCommands: config auto-reload enabled — polling every %.0f seconds."),
        ConfigPollIntervalSeconds);

    // Start the mute expiry ticker — checks timed mutes every 30 s.
    MuteExpiryHandle = FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateRaw(this, &FBanChatCommandsModule::OnMuteExpiryTick),
        30.0f);

    // Bind game-mode post-login event to re-apply any active freeze when a
    // frozen player reconnects.  This means a freeze persists across disconnects
    // until an admin explicitly runs /freeze again (the toggle then unfreezes).
    PostLoginHandle = FGameModeEvents::GameModePostLoginEvent.AddLambda(
        [](AGameModeBase* /*GameMode*/, APlayerController* NewPlayer)
        {
            if (!NewPlayer || !NewPlayer->PlayerState) return;
            const FUniqueNetIdRepl& UniqueId = NewPlayer->PlayerState->GetUniqueId();
            FString Uid;
            if (UniqueId.IsValid() && UniqueId.GetType() != FName(TEXT("NONE")))
            {
                Uid = UBanDatabase::MakeUid(TEXT("EOS"), UniqueId.ToString().ToLower());
            }
            else
            {
                const FString EosPuid = UBanEnforcer::ExtractEosPuidFromConnectionUrl(NewPlayer);
                if (!EosPuid.IsEmpty())
                    Uid = UBanDatabase::MakeUid(TEXT("EOS"), EosPuid);
            }
            if (Uid.IsEmpty()) return;
            if (AFreezeChatCommand::FrozenPlayerUids.Contains(Uid))
                NewPlayer->SetIgnoreMoveInput(true);
        });

    // Hook AGameModeBase::Logout so that a frozen player who reconnects is
    // automatically re-frozen by the PostLogin hook above.  We intentionally
    // do NOT remove the UID from FrozenPlayerUids on disconnect so the
    // PostLogin hook can find it.  The /freeze command itself handles the
    // "toggle while offline" case by checking whether the player is currently
    // online before deciding which branch (freeze vs. unfreeze) to enter.
    LogoutHookHandle = SUBSCRIBE_METHOD_VIRTUAL_AFTER(
        AGameModeBase::Logout,
        GetMutableDefault<AGameModeBase>(),
        [](AGameModeBase* /*GameMode*/, AController* Exiting)
        {
            APlayerController* PC = Cast<APlayerController>(Exiting);
            if (!PC) return;

            // Re-apply frozen movement state immediately on reconnect by keeping
            // the UID in FrozenPlayerUids across the disconnect.  The PostLogin
            // hook will call SetIgnoreMoveInput(true) when the player comes back.
            // Nothing to do here — the entry is intentionally left in the set.
            (void)PC;
        });

    WorldInitHandle = FWorldDelegates::OnWorldInitializedActors.AddLambda(
        [this](const UWorld::FActorsInitializedParams& Params)
        {
            UWorld* World = Params.World;
            if (!World) return;

            const ENetMode NetMode = World->GetNetMode();
            if (NetMode != NM_DedicatedServer && NetMode != NM_ListenServer)
                return;

            AChatCommandSubsystem* CmdSys = AChatCommandSubsystem::Get(World);
            if (!CmdSys)
            {
                UE_LOG(LogBanChatCommands, Warning,
                    TEXT("BanChatCommands: AChatCommandSubsystem not available — commands not registered."));
                return;
            }

            int32 RegisteredCommandCount = 0;
            auto Reg = [&](UClass* Cls) { CmdSys->RegisterCommand(TEXT("BanChatCommands"), Cls); ++RegisteredCommandCount; };

            Reg(ABanChatCommand::StaticClass());
            Reg(ATempBanChatCommand::StaticClass());
            Reg(AUnbanChatCommand::StaticClass());
            Reg(AUnbanNameChatCommand::StaticClass());
            Reg(ABanCheckChatCommand::StaticClass());
            Reg(ABanListChatCommand::StaticClass());
            Reg(ALinkBansChatCommand::StaticClass());
            Reg(AUnlinkBansChatCommand::StaticClass());
            Reg(APlayerHistoryChatCommand::StaticClass());
            Reg(AWhoAmIChatCommand::StaticClass());
            Reg(ABanNameChatCommand::StaticClass());
            Reg(AReloadConfigChatCommand::StaticClass());
            Reg(AKickChatCommand::StaticClass());
            Reg(AModBanChatCommand::StaticClass());
            Reg(AWarnChatCommand::StaticClass());
            Reg(AWarningsChatCommand::StaticClass());
            Reg(AClearWarnsChatCommand::StaticClass());
            Reg(AAnnounceChatCommand::StaticClass());
            Reg(AStaffListChatCommand::StaticClass());
            Reg(AReasonChatCommand::StaticClass());
            Reg(AHistoryChatCommand::StaticClass());
            Reg(AMuteChatCommand::StaticClass());
            Reg(AUnmuteChatCommand::StaticClass());
            Reg(ANoteChatCommand::StaticClass());
            Reg(ANotesChatCommand::StaticClass());
            Reg(ADurationChatCommand::StaticClass());
            Reg(ATempUnmuteChatCommand::StaticClass());
            Reg(AMuteCheckChatCommand::StaticClass());
            Reg(ABanReasonChatCommand::StaticClass());
            Reg(AStaffChatCommand::StaticClass());
            Reg(AMuteListChatCommand::StaticClass());
            Reg(AClearWarnByIdChatCommand::StaticClass());
            Reg(AExtendBanChatCommand::StaticClass());
            Reg(AAppealChatCommand::StaticClass());
            Reg(AMuteReasonChatCommand::StaticClass());
            Reg(AFreezeChatCommand::StaticClass());
            Reg(AClearChatChatCommand::StaticClass());
            Reg(AReportChatCommand::StaticClass());
            Reg(AScheduleBanChatCommand::StaticClass());
            Reg(AQBanChatCommand::StaticClass());
            Reg(AReputationChatCommand::StaticClass());
            Reg(ABulkBanChatCommand::StaticClass());

            UE_LOG(LogBanChatCommands, Log,
                TEXT("BanChatCommands: Registered %d commands (ban, tempban, unban, unbanname, bancheck, banlist, linkbans, unlinkbans, playerhistory, whoami, banname, reloadconfig, kick, modban, warn, warnings, clearwarns, announce, stafflist, reason, history, mute, unmute, note, notes, duration, tempunmute, mutecheck, banreason, staffchat, mutelist, clearwarn, extend, appeal, mutereason, freeze, clearchat, report, scheduleban, qban, reputation, bulkban)."),
                RegisteredCommandCount);

            // Bind MuteRegistry delegates to push WebSocket events and write audit log.
            // Remove any previous binding first: on servers that reload a world while the
            // GameInstance persists the same UMuteRegistry survives, so AddLambda would
            // otherwise stack a new binding on every world load.
            UGameInstance* GI = World->GetGameInstance();
            if (GI)
            {
                TWeakObjectPtr<UGameInstance> WeakGI(GI);
                UMuteRegistry* MuteReg = GI->GetSubsystem<UMuteRegistry>();
                if (MuteReg)
                {
                    // Remove any previous binding unconditionally: Remove() with an
                    // invalid handle is a documented no-op, and always calling it
                    // guarantees cleanup even in the edge case where a prior
                    // UMuteRegistry instance was replaced between world loads.
                    MuteReg->OnPlayerMuted.Remove(MutedDelegateHandle);
                    MuteReg->OnPlayerUnmuted.Remove(UnmutedDelegateHandle);

                    MutedDelegateHandle = MuteReg->OnPlayerMuted.AddLambda(
                        [](const FMuteEntry& Entry, bool bIsTimed)
                        {
                            // Push the WebSocket event only.  Audit logging is handled by
                            // every caller of MutePlayer() (AMuteChatCommand, BanDiscordSubsystem,
                            // etc.) to avoid double-entries with the correct adminUid.
                            UBanWebSocketPusher::PushMuteEvent(
                                TEXT("mute"), Entry.Uid, Entry.PlayerName,
                                Entry.MutedBy, Entry.Reason,
                                bIsTimed,
                                bIsTimed ? Entry.ExpireDate.ToIso8601() : FString());
                        });

                    UnmutedDelegateHandle = MuteReg->OnPlayerUnmuted.AddLambda(
                        [](const FString& Uid)
                        {
                            // Push the WebSocket event only.  Audit logging is handled by
                            // every caller of UnmutePlayer() (AUnmuteChatCommand, BanDiscordSubsystem,
                            // etc.) to avoid double-entries with the correct adminUid.
                            UBanWebSocketPusher::PushMuteEvent(
                                TEXT("unmute"), Uid, TEXT(""), TEXT(""), TEXT(""), false, FString());
                        });
                }
            }
        }
    );

    UE_LOG(LogBanChatCommands, Log, TEXT("BanChatCommands module started."));
}

// ─────────────────────────────────────────────────────────────────────────────
//  Automatic config-reload ticker
// ─────────────────────────────────────────────────────────────────────────────

uint32 FBanChatCommandsModule::ComputeAdminHash()
{
    const UBanChatCommandsConfig* Cfg = UBanChatCommandsConfig::Get();
    if (!Cfg) return 0;

    // Sort so that order-only changes don't trigger a false positive.
    TArray<FString> Sorted = Cfg->AdminEosPUIDs;
    Sorted.Sort();
    const FString Joined = FString::Join(Sorted, TEXT(","));
    return FCrc::StrCrc32(*Joined);
}

bool FBanChatCommandsModule::OnConfigPollTick(float /*DeltaTime*/)
{
    // Force UE to re-read all UPROPERTY(Config) fields from the ini files on disk.
    UBanChatCommandsConfig* MutableCfg = GetMutableDefault<UBanChatCommandsConfig>();
    if (!MutableCfg)
        return true; // Safety: CDO unavailable (should never happen, but guard anyway).
    MutableCfg->ReloadConfig();

    const uint32 NewHash = ComputeAdminHash();
    if (NewHash != LastConfigHash)
    {
        LastConfigHash = NewHash;
        BackupConfigIfNeeded();

        const UBanChatCommandsConfig* Cfg = UBanChatCommandsConfig::Get();
        const int32 AdminCount = Cfg ? Cfg->AdminEosPUIDs.Num() : 0;
        UE_LOG(LogBanChatCommands, Log,
            TEXT("BanChatCommands: config auto-reloaded — %d admin(s) now active."),
            AdminCount);
    }

    return true; // keep ticking
}

// ─────────────────────────────────────────────────────────────────────────────
//  Persistent config backup
// ─────────────────────────────────────────────────────────────────────────────

void FBanChatCommandsModule::BackupConfigIfNeeded()
{
    const UBanChatCommandsConfig* Cfg = UBanChatCommandsConfig::Get();
    if (!Cfg) return;

    // Saved/BanChatCommands/BanChatCommands.ini — dedicated per-mod folder so it's
    // easy to find, and never touched by mod updates or Alpakit dev deploys.
    const FString BackupPath = FPaths::Combine(
        FPaths::ProjectSavedDir(),
        TEXT("BanChatCommands"),
        TEXT("BanChatCommands.ini"));

    // Write on every server start so the backup always reflects the current
    // admin list.  Saved/BanChatCommands/ is never touched by mod updates or
    // Alpakit dev deploys, so the list survives any wipe of the mod directory.
    FString Content =
        FString(TEXT("; BanChatCommands admin configuration.\n"))
        + TEXT(";\n")
        + TEXT("; Edit this file to configure the admin and moderator lists persistently.\n")
        + TEXT("; It is never overwritten by mod updates.\n")
        + TEXT(";\n")
        + TEXT("; EOS Product User IDs -- Each +AdminEosPUIDs= entry grants that player\n")
        + TEXT("; permission to run /ban, /tempban, /unban, /bancheck, /banlist,\n")
        + TEXT("; /linkbans, /unlinkbans, /playerhistory, /warn, /warnings, and /clearwarns\n")
        + TEXT("; from in-game chat.\n")
        + TEXT(";\n")
        + TEXT("; Each +ModeratorEosPUIDs= entry grants permission to run /kick and /modban only.\n")
        + TEXT("; Admins automatically have moderator permissions too.\n")
        + TEXT(";\n")
        + TEXT("; EOS PUIDs are 32-character hex strings.  Players can find their own\n")
        + TEXT("; PUID by running /whoami in-game.\n")
        + TEXT(";\n")
        + TEXT("; Note: On CSS Dedicated Server, all players are identified by their EOS\n")
        + TEXT("; Product User ID regardless of their launch platform (Steam, Epic, etc.).\n")
        + TEXT(";\n")
        + TEXT("; If the admin list is empty, those commands are only usable from the server\n")
        + TEXT("; console.  /whoami is always available to all players.\n")
        + TEXT("\n")
        + TEXT("[/Script/BanChatCommands.BanChatCommandsConfig]\n");

    // Sanitize values to prevent newline injection into the INI file.
    auto SanitizeIni = [](const FString& S) -> FString
    {
        FString Out; Out.Reserve(S.Len());
        for (TCHAR C : S) if (C != TEXT('\r') && C != TEXT('\n')) Out += C;
        return Out;
    };

    for (const FString& Puid : Cfg->AdminEosPUIDs)
    {
        Content += TEXT("+AdminEosPUIDs=") + SanitizeIni(Puid) + TEXT("\n");
    }

    if (Cfg->AdminEosPUIDs.IsEmpty())
    {
        Content += TEXT("; +AdminEosPUIDs=YOUR_EOS_PUID_HERE\n");
    }

    Content += TEXT("\n");

    for (const FString& Puid : Cfg->ModeratorEosPUIDs)
    {
        Content += TEXT("+ModeratorEosPUIDs=") + SanitizeIni(Puid) + TEXT("\n");
    }

    if (Cfg->ModeratorEosPUIDs.IsEmpty())
    {
        Content += TEXT("; +ModeratorEosPUIDs=MODERATOR_EOS_PUID_HERE\n");
    }

    Content += FString::Printf(TEXT("BanListPageSize=%d\n"), Cfg->BanListPageSize);
    Content += FString::Printf(TEXT("ModBanDurationMinutes=%d\n"), Cfg->ModBanDurationMinutes);
    Content += FString::Printf(TEXT("MaxModMuteDurationMinutes=%d\n"), Cfg->MaxModMuteDurationMinutes);
    Content += FString::Printf(TEXT("bAllowModNotes=%s\n"), Cfg->bAllowModNotes ? TEXT("True") : TEXT("False"));
    Content += FString::Printf(TEXT("bCreateWarnOnKick=%s\n"), Cfg->bCreateWarnOnKick ? TEXT("True") : TEXT("False"));
    Content += FString::Printf(TEXT("WarningCheckCooldownSeconds=%d\n"), Cfg->WarningCheckCooldownSeconds);
    Content += FString::Printf(TEXT("AdminBanRateLimitCount=%d\n"), Cfg->AdminBanRateLimitCount);
    Content += FString::Printf(TEXT("AdminBanRateLimitMinutes=%d\n"), Cfg->AdminBanRateLimitMinutes);
    Content += TEXT("ReloadConfigWebhookUrl=") + SanitizeIni(Cfg->ReloadConfigWebhookUrl) + TEXT("\n");
    Content += TEXT("ReportWebhookUrl=") + SanitizeIni(Cfg->ReportWebhookUrl) + TEXT("\n");

    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    PlatformFile.CreateDirectoryTree(*FPaths::GetPath(BackupPath));

    // Write atomically: write to .tmp then rename, so a crash mid-write never
    // leaves a partial/corrupt admin config file.
    const FString TmpPath = BackupPath + TEXT(".tmp");
    if (FFileHelper::SaveStringToFile(Content, *TmpPath,
        FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
    {
        if (IFileManager::Get().Move(*BackupPath, *TmpPath, /*bReplace=*/true))
        {
            UE_LOG(LogBanChatCommands, Log,
                TEXT("BanChatCommands: Updated backup config at '%s'."), *BackupPath);
        }
        else
        {
            IFileManager::Get().Delete(*TmpPath);
            UE_LOG(LogBanChatCommands, Warning,
                TEXT("BanChatCommands: Could not rename backup config to '%s'."), *BackupPath);
        }
    }
    else
    {
        UE_LOG(LogBanChatCommands, Warning,
            TEXT("BanChatCommands: Could not write backup config to '%s'."), *TmpPath);
    }
}

void FBanChatCommandsModule::RestoreDefaultConfigIfNeeded()
{
    const FString DefaultIniPath = FPaths::Combine(
        FPaths::ProjectDir(),
        TEXT("Mods"), TEXT("BanChatCommands"),
        TEXT("Config"), TEXT("DefaultBanChatCommands.ini"));

    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

    // Only rewrite when the file is missing or has been stripped of comment
    // lines.  Alpakit's staging step runs Default*.ini through UE's config
    // cache, which drops all semicolon comment lines.  Excluding the file via
    // PluginSettings.ini prevents that, but a fresh install may still land
    // without the file.  This keeps comments visible after every update.
    if (PlatformFile.FileExists(*DefaultIniPath))
    {
        FString Existing;
        FFileHelper::LoadFileToString(Existing, *DefaultIniPath);
        // Check whether any line starts with a comment character.  Using
        // Contains() on the whole string would incorrectly match '#' or ';'
        // appearing inside a value (e.g. in a URL or player message).
        TArray<FString> Lines;
        Existing.ParseIntoArrayLines(Lines);
        for (const FString& Line : Lines)
        {
            const FString Trimmed = Line.TrimStart();
            if (Trimmed.StartsWith(TEXT("#")) || Trimmed.StartsWith(TEXT(";")))
                return; // comment lines present — leave as-is
        }
    }

    const FString Content =
        FString(TEXT("# BanChatCommands admin configuration.\n"))
        + TEXT("#\n")
        + TEXT("# ── How to persist settings across mod updates ───────────────────────────────\n")
        + TEXT("#\n")
        + TEXT("# This file ships with the mod and may be replaced when you update BanChatCommands.\n")
        + TEXT("# To keep your admin list permanently, place your overrides in ONE of:\n")
        + TEXT("#\n")
        + TEXT("#   1. Saved/BanChatCommands/BanChatCommands.ini  <- written by BanChatCommands on\n")
        + TEXT("#                                                    every start; survives mod wipes\n")
        + TEXT("#   2. Saved/Config/<Platform>/BanChatCommands.ini <- standard UE config override\n")
        + TEXT("#\n")
        + TEXT("# Both use the same [/Script/BanChatCommands.BanChatCommandsConfig] section header.\n")
        + TEXT("# Restart the server after editing any config file.\n")
        + TEXT("#\n")
        + TEXT("# ── Admin list ───────────────────────────────────────────────────────────────\n")
        + TEXT("#\n")
        + TEXT("# EOS Product User IDs — each +AdminEosPUIDs= entry grants that player permission\n")
        + TEXT("# to run the following commands from in-game chat:\n")
        + TEXT("#\n")
        + TEXT("#   /ban, /tempban, /unban, /unbanname, /banname, /bancheck, /banlist,\n")
        + TEXT("#   /banreason, /extend, /scheduleban, /qban, /bulkban,\n")
        + TEXT("#   /linkbans, /unlinkbans, /warn, /warnings, /clearwarns, /clearwarn,\n")
        + TEXT("#   /mute, /unmute, /mutecheck, /mutelist, /mutereason,\n")
        + TEXT("#   /announce, /stafflist, /staffchat, /note, /notes, /reason, /history,\n")
        + TEXT("#   /playerhistory, /reputation, /freeze, /clearchat, /reloadconfig\n")
        + TEXT("#\n")
        + TEXT("#   Moderator-only commands (/kick, /modban, /tempunmute, /mutecheck):\n")
        + TEXT("#   controlled separately via +ModeratorEosPUIDs= below.\n")
        + TEXT("#\n")
        + TEXT("# EOS PUIDs are 32-character hex strings (case-insensitive).\n")
        + TEXT("# Players can find their own PUID by running /whoami in-game.\n")
        + TEXT("#\n")
        + TEXT("# Note: On CSS Dedicated Server all players are identified by their EOS Product\n")
        + TEXT("# User ID regardless of their launch platform (Steam, Epic Games Store, etc.).\n")
        + TEXT("#\n")
        + TEXT("# If the list is empty, those commands are only usable from the server console.\n")
        + TEXT("# /whoami is always available to all connected players regardless of this setting.\n")
        + TEXT("# The server console always bypasses the admin list.\n")
        + TEXT("#\n")
        + TEXT("# Example:\n")
        + TEXT("#   [/Script/BanChatCommands.BanChatCommandsConfig]\n")
        + TEXT("#   +AdminEosPUIDs=00020aed06f0a6958c3c067fb4b73d51\n")
        + TEXT("#   +AdminEosPUIDs=aabbccdd11223344aabbccdd11223344\n")
        + TEXT("\n")
        + TEXT("[/Script/BanChatCommands.BanChatCommandsConfig]\n")
        + TEXT("# +AdminEosPUIDs=YOUR_EOS_PUID_HERE\n")
        + TEXT("# +ModeratorEosPUIDs=MODERATOR_EOS_PUID_HERE\n")
        + TEXT("BanListPageSize=10\n")
        + TEXT("ModBanDurationMinutes=30\n")
        + TEXT("# Maximum mute duration (minutes) a moderator may pass to /tempmute.\n")
        + TEXT("# 0 = no ceiling (same as admins).\n")
        + TEXT("MaxModMuteDurationMinutes=0\n")
        + TEXT("# Set to True to allow moderators to use /note and /notes (default: only admins).\n")
        + TEXT("bAllowModNotes=False\n")
        + TEXT("# Cooldown in seconds between /warnings / /bancheck uses for non-admin senders.\n")
        + TEXT("# Set to 0 to disable (default).\n")
        + TEXT("WarningCheckCooldownSeconds=0\n")
        + TEXT("# Discord webhook URL for /report command notifications.\n")
        + TEXT("# Leave empty to disable Discord delivery.\n")
        + TEXT("# ReportWebhookUrl=https://discord.com/api/webhooks/YOUR_ID/YOUR_TOKEN\n")
        + TEXT("# When True, issuing /kick also records a warning to the player's history (default: False).\n")
        + TEXT("bCreateWarnOnKick=False\n")
        + TEXT("# Discord webhook URL called when /reloadconfig is used. Leave empty to disable.\n")
        + TEXT("# ReloadConfigWebhookUrl=\n")
        + TEXT("# Maximum ban actions an admin may issue within AdminBanRateLimitMinutes (0 = disabled).\n")
        + TEXT("AdminBanRateLimitCount=0\n")
        + TEXT("# Time window in minutes for the admin ban rate limit (default: 5).\n")
        + TEXT("AdminBanRateLimitMinutes=5\n");

    PlatformFile.CreateDirectoryTree(*FPaths::GetPath(DefaultIniPath));

    if (FFileHelper::SaveStringToFile(Content, *DefaultIniPath,
        FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
    {
        UE_LOG(LogBanChatCommands, Log,
            TEXT("BanChatCommands: Restored annotated default config at '%s'."), *DefaultIniPath);
    }
    else
    {
        UE_LOG(LogBanChatCommands, Warning,
            TEXT("BanChatCommands: Could not write default config to '%s'."), *DefaultIniPath);
    }
}

void FBanChatCommandsModule::ShutdownModule()
{
    FTSTicker::GetCoreTicker().RemoveTicker(ConfigPollHandle);
    ConfigPollHandle.Reset();
    FTSTicker::GetCoreTicker().RemoveTicker(MuteExpiryHandle);
    MuteExpiryHandle.Reset();

    FGameModeEvents::GameModePostLoginEvent.Remove(PostLoginHandle);
    PostLoginHandle.Reset();

    UNSUBSCRIBE_METHOD(AGameModeBase::Logout, LogoutHookHandle);
    LogoutHookHandle.Reset();

    FWorldDelegates::OnWorldInitializedActors.Remove(WorldInitHandle);
    WorldInitHandle.Reset();

    // Remove the MuteRegistry delegate bindings that were set up inside the
    // OnWorldInitializedActors lambda.  Without this, the stale closures will
    // remain in UMuteRegistry and fire after the module has been unloaded,
    // potentially accessing freed memory (UBanWebSocketPusher is guarded by
    // a weak pointer but the closure itself still executes until removed).
    if (GEngine)
    {
        for (const FWorldContext& WCtx : GEngine->GetWorldContexts())
        {
            UGameInstance* GI = WCtx.OwningGameInstance;
            if (!GI) continue;
            if (UMuteRegistry* MuteReg = GI->GetSubsystem<UMuteRegistry>())
            {
                MuteReg->OnPlayerMuted.Remove(MutedDelegateHandle);
                MuteReg->OnPlayerUnmuted.Remove(UnmutedDelegateHandle);
            }
        }
    }
    MutedDelegateHandle.Reset();
    UnmutedDelegateHandle.Reset();

    UE_LOG(LogBanChatCommands, Log, TEXT("BanChatCommands module shut down."));
}

#undef LOCTEXT_NAMESPACE

// ─────────────────────────────────────────────────────────────────────────────
//  Mute expiry ticker
// ─────────────────────────────────────────────────────────────────────────────

bool FBanChatCommandsModule::OnMuteExpiryTick(float /*DeltaTime*/)
{
    // Walk all game instances and tick UMuteRegistry on each.
    // In practice there is one game instance on a dedicated server, but this
    // approach is future-proof if multiple worlds/instances ever run.
    if (!GEngine) return true;
    for (const FWorldContext& WCtx : GEngine->GetWorldContexts())
    {
        UGameInstance* GI = WCtx.OwningGameInstance;
        if (!GI) continue;
        UMuteRegistry* MuteReg = GI->GetSubsystem<UMuteRegistry>();
        if (!MuteReg) continue;
        TArray<FString> Expired = MuteReg->TickExpiry();
        if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
        {
            for (const FString& ExpiredUid : Expired)
                AuditLog->LogAction(TEXT("unmute"), ExpiredUid, TEXT(""), TEXT("system"), TEXT("system"), TEXT("Timed mute expired"));
        }
    }
    return true; // keep ticking
}

IMPLEMENT_MODULE(FBanChatCommandsModule, BanChatCommands)
