// Copyright Yamahasxviper. All Rights Reserved.

#include "BanSystemModule.h"
#include "BanDatabase.h"
#include "BanSystemConfig.h"
#include "PlayerWarningRegistry.h"
#include "PlayerSessionRegistry.h"
#include "ScheduledBanRegistry.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Engine/World.h"
#include "Engine/GameInstance.h"

DEFINE_LOG_CATEGORY_STATIC(LogBanSystem, Log, All);

#define LOCTEXT_NAMESPACE "FBanSystemModule"

void FBanSystemModule::StartupModule()
{
    UE_LOG(LogBanSystem, Log, TEXT("BanSystem module starting."));
    // UBanDatabase, UBanRestApi, and UBanEnforcer are UGameInstanceSubsystem
    // subclasses and initialise automatically when the game instance starts.
    // No manual setup is required here.

    // Restore the annotated Default*.ini so operators can always read the
    // setting descriptions even after a mod update or fresh install.
    RestoreDefaultConfigIfNeeded();

    // On every server start, write a backup to Saved/BanSystem/BanSystem.ini.
    // That folder is never touched by mod updates so settings survive any wipe
    // of the mod directory.
    BackupConfigIfNeeded();

    // Start the scheduled backup ticker if BackupIntervalHours > 0.
    const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
    if (Cfg && Cfg->BackupIntervalHours > 0.0f)
    {
        BackupAccumulatedSeconds = 0.0f;
        BackupTickHandle = FTSTicker::GetCoreTicker().AddTicker(
            FTickerDelegate::CreateRaw(this, &FBanSystemModule::OnBackupTick),
            1.0f);
        UE_LOG(LogBanSystem, Log,
            TEXT("BanSystem: scheduled backup enabled — every %.1f hour(s)."),
            Cfg->BackupIntervalHours);
    }

    // Start the scheduled prune ticker if PruneIntervalHours > 0.
    if (Cfg && Cfg->PruneIntervalHours > 0.0f)
    {
        PruneAccumulatedSeconds = 0.0f;
        PruneTickHandle = FTSTicker::GetCoreTicker().AddTicker(
            FTickerDelegate::CreateRaw(this, &FBanSystemModule::OnPruneTick),
            1.0f);
        UE_LOG(LogBanSystem, Log,
            TEXT("BanSystem: scheduled prune enabled — every %.1f hour(s)."),
            Cfg->PruneIntervalHours);
    }

    // Start the session retention ticker if SessionRetentionDays > 0.
    // Runs independently from the ban-prune ticker: once every 24 hours.
    if (Cfg && Cfg->SessionRetentionDays > 0)
    {
        SessionPruneAccumulatedSeconds = 0.0f;
        SessionPruneTickHandle = FTSTicker::GetCoreTicker().AddTicker(
            FTickerDelegate::CreateRaw(this, &FBanSystemModule::OnSessionPruneTick),
            1.0f);
        UE_LOG(LogBanSystem, Log,
            TEXT("BanSystem: session retention enabled — keeping records for %d day(s)."),
            Cfg->SessionRetentionDays);
    }

    // Always start the scheduled-ban ticker (every 30 s).
    // UScheduledBanRegistry is a GameInstanceSubsystem and initialises automatically,
    // but we route the tick through the module ticker so the registry stays active
    // even when no game-instance tick is running at module startup.
    ScheduledBanTickHandle = FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateRaw(this, &FBanSystemModule::OnScheduledBanTick),
        1.0f);
    UE_LOG(LogBanSystem, Log, TEXT("BanSystem: scheduled-ban ticker started."));

    // Start the config-file hot-reload watcher.
    // Capture baseline mod-times for both monitored INI files so the first
    // poll can detect changes made between server start and the first tick.
    {
        const FString SavedIni = FPaths::Combine(
            FPaths::ProjectSavedDir(), TEXT("BanSystem"), TEXT("BanSystem.ini"));
        const FString DefaultIni = FPaths::Combine(
            FPaths::ProjectDir(), TEXT("Mods"), TEXT("BanSystem"),
            TEXT("Config"), TEXT("DefaultBanSystem.ini"));
        ConfigFileModTimes[0] = IFileManager::Get().GetTimeStamp(*SavedIni);
        ConfigFileModTimes[1] = IFileManager::Get().GetTimeStamp(*DefaultIni);
    }
    ConfigPollTickHandle = FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateRaw(this, &FBanSystemModule::OnConfigPollTick),
        ConfigPollIntervalSeconds);
    UE_LOG(LogBanSystem, Log,
        TEXT("BanSystem: config auto-reload enabled — polling every %.0f seconds."),
        ConfigPollIntervalSeconds);

    UE_LOG(LogBanSystem, Log, TEXT("BanSystem module started."));
}

void FBanSystemModule::BackupConfigIfNeeded()
{
    const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
    if (!Cfg) return;

    // Strip any newline characters from a config value before writing it into
    // the INI file — a value containing '\n' would inject extra lines and could
    // create malformed or injected keys when the file is parsed on reload.
    auto SanitizeIni = [](const FString& S) -> FString
    {
        return S.Replace(TEXT("\r\n"), TEXT(" "))
                .Replace(TEXT("\n"),   TEXT(" "))
                .Replace(TEXT("\r"),   TEXT(" "));
    };

    // Saved/BanSystem/BanSystem.ini — dedicated per-mod folder so it's easy to
    // find, and never touched by mod updates or Alpakit dev deploys.
    const FString BackupPath = FPaths::Combine(
        FPaths::ProjectSavedDir(),
        TEXT("BanSystem"),
        TEXT("BanSystem.ini"));

    // Write on every server start so the backup always reflects the current
    // settings.  Saved/BanSystem/ is never touched by mod updates or Alpakit
    // dev deploys, so the settings survive any wipe of the mod directory.
    // NOTE: String concatenation (not Printf) to avoid misinterpreting any
    // '%' character that might appear in a custom DatabasePath.
    const FString Content =
        FString(TEXT("; BanSystem configuration.\n"))
        + TEXT(";\n")
        + TEXT("; Edit this file to configure BanSystem persistently.\n")
        + TEXT("; It is never overwritten by mod updates.\n")
        + TEXT(";\n")
        + TEXT("; Settings are also read from the mod's own Config/DefaultBanSystem.ini,\n")
        + TEXT("; but that file may be overwritten when the mod is updated.\n")
        + TEXT("\n")
        + TEXT("[/Script/BanSystem.BanSystemConfig]\n")
        + TEXT("\n")
        + TEXT("; -- Database ------------------------------------------------------------------\n")
        + TEXT(";\n")
        + TEXT("; Absolute path to the JSON ban file.\n")
        + TEXT("; Leave empty to use the default: <ProjectSaved>/BanSystem/bans.json\n")
        + TEXT("; On Linux this is typically: /home/<user>/.config/Epic/FactoryGame/Saved/BanSystem/bans.json\n")
        + TEXT("DatabasePath=") + SanitizeIni(Cfg->DatabasePath) + TEXT("\n")
        + TEXT("\n")
        + TEXT("; -- REST Management API -------------------------------------------------------\n")
        + TEXT(";\n")
        + TEXT("; Port for the local HTTP management API (default: 3000).\n")
        + TEXT("; Mirrors the Tools/BanSystem API_PORT setting.\n")
        + TEXT(";\n")
        + TEXT("; The API binds to all interfaces (0.0.0.0).\n")
        + TEXT("; Restrict external access with your server firewall if needed.\n")
        + TEXT(";\n")
        + TEXT("; Set to 0 to disable the REST API entirely.\n")
        + TEXT("RestApiPort=")  + FString::FromInt(Cfg->RestApiPort) + TEXT("\n")
        + TEXT("\n")
        + TEXT("; -- Backup --------------------------------------------------------------------\n")
        + TEXT(";\n")
        + TEXT("; Number of automatic database backups to keep (default: 5).\n")
        + TEXT("; A backup is created on demand via POST /bans/backup.\n")
        + TEXT("; Older backups beyond this limit are deleted automatically.\n")
        + TEXT("MaxBackups=")   + FString::FromInt(Cfg->MaxBackups)  + TEXT("\n")
        + TEXT("\n")
        + TEXT("; -- REST API Authentication ---------------------------------------------------\n")
        + TEXT(";\n")
        + TEXT("; Optional API key for authenticating REST API requests.\n")
        + TEXT("; When non-empty, all endpoints except GET /health require the header: X-Api-Key: <value>\n")
        + TEXT("; Leave empty to disable API key authentication (default; only safe on a firewalled server).\n")
        + TEXT("RestApiKey=")   + SanitizeIni(Cfg->RestApiKey) + TEXT("\n")
        + TEXT("\n")
        + TEXT("; -- Discord Notifications -----------------------------------------------------\n")
        + TEXT(";\n")
        + TEXT("; Optional Discord webhook URL for ban/unban/warn/kick notifications.\n")
        + TEXT("; When set, BanDiscordNotifier posts an embed to this URL whenever a ban is\n")
        + TEXT("; created or removed, a warning is issued, or a player is kicked.\n")
        + TEXT("; Leave empty to disable Discord notifications (default).\n")
        + TEXT("DiscordWebhookUrl=") + SanitizeIni(Cfg->DiscordWebhookUrl) + TEXT("\n")
        + TEXT("\n")
        + TEXT("; -- Auto-ban on Warnings ------------------------------------------------------\n")
        + TEXT(";\n")
        + TEXT("; Number of warnings before an automatic permanent ban is issued (default: 0 = disabled).\n")
        + TEXT("; When a player reaches this many warnings via /warn, they are automatically\n")
        + TEXT("; permanently banned with reason \"Auto-banned: reached warning threshold\".\n")
        + TEXT("; Set to 0 to disable auto-banning on warnings.\n")
        + TEXT("AutoBanWarnCount=")   + FString::FromInt(Cfg->AutoBanWarnCount)   + TEXT("\n")
        + TEXT(";\n")
        + TEXT("; Duration in minutes for the auto-ban issued when AutoBanWarnCount is reached (default: 0 = permanent).\n")
        + TEXT("; Set to 0 for a permanent auto-ban.\n")
        + TEXT("AutoBanWarnMinutes=") + FString::FromInt(Cfg->AutoBanWarnMinutes) + TEXT("\n")
        + TEXT("\n")
        + TEXT("; -- Warning Escalation Tiers -------------------------------------------------\n")
        + TEXT(";\n")
        + TEXT("; Multi-tier automatic bans based on warning count.\n")
        + TEXT("; Each tier: WarnCount=<N>,PointThreshold=<P>,DurationMinutes=<M>  (0 = permanent ban)\n")
        + TEXT("; PointThreshold=0 uses plain warn count instead of accumulated points.\n")
        + TEXT("; Example:\n")
        + TEXT(";   +WarnEscalationTiers=(WarnCount=2,PointThreshold=0,DurationMinutes=30)\n")
        + TEXT(";   +WarnEscalationTiers=(WarnCount=3,PointThreshold=0,DurationMinutes=1440)\n")
        + TEXT(";   +WarnEscalationTiers=(WarnCount=5,PointThreshold=0,DurationMinutes=0)\n")
        + TEXT("\n")
        + TEXT("; -- Session Retention -------------------------------------------------------\n")
        + TEXT(";\n")
        + TEXT("; Number of days to retain player session records (default: 0 = keep forever).\n")
        + TEXT("SessionRetentionDays=") + FString::FromInt(Cfg->SessionRetentionDays) + TEXT("\n")
        + TEXT("\n")
        + TEXT("; -- Warning Decay -----------------------------------------------------------\n")
        + TEXT(";\n")
        + TEXT("; Number of days after which warnings are excluded from escalation (0 = never decay).\n")
        + TEXT("WarnDecayDays=") + FString::FromInt(Cfg->WarnDecayDays) + TEXT("\n")
        + TEXT("\n")
        + TEXT("; -- Scheduled Backup --------------------------------------------------------\n")
        + TEXT(";\n")
        + TEXT("; Interval in hours between automatic database backups (default: 0 = disabled).\n")
        + TEXT("BackupIntervalHours=") + FString::SanitizeFloat(Cfg->BackupIntervalHours) + TEXT("\n")
        + TEXT("\n")
        + TEXT("; -- Ban Expiry Notifications ------------------------------------------------\n")
        + TEXT(";\n")
        + TEXT("; When true, post a Discord notification when a temporary ban expires (default: false).\n")
        + TEXT("bNotifyBanExpired=") + (Cfg->bNotifyBanExpired ? TEXT("True") : TEXT("False")) + TEXT("\n")
        + TEXT("\n")
        + TEXT("; -- Auto-Prune --------------------------------------------------------------\n")
        + TEXT(";\n")
        + TEXT("; Interval in hours between automatic expired-ban prune runs (0 = disabled).\n")
        + TEXT("PruneIntervalHours=") + FString::SanitizeFloat(Cfg->PruneIntervalHours) + TEXT("\n")
        + TEXT("\n")
        + TEXT("; -- WebSocket Push Events ---------------------------------------------------\n")
        + TEXT(";\n")
        + TEXT("; When true, BanSystem pushes live JSON events to WebSocketPushUrl via SMLWebSocket.\n")
        + TEXT("bPushEventsToWebSocket=") + (Cfg->bPushEventsToWebSocket ? TEXT("True") : TEXT("False")) + TEXT("\n")
        + TEXT("WebSocketPushUrl=") + SanitizeIni(Cfg->WebSocketPushUrl) + TEXT("\n")
        + TEXT("\n")
        + TEXT("; -- Kick Message Templates --------------------------------------------------\n")
        + TEXT(";\n")
        + TEXT("; Custom message for permanently banned players. Supports {reason}, {appeal_url}.\n")
        + TEXT("BanKickMessageTemplate=") + SanitizeIni(Cfg->BanKickMessageTemplate) + TEXT("\n")
        + TEXT("; Custom message for temporarily banned players. Supports {reason}, {expiry}, {appeal_url}.\n")
        + TEXT("TempBanKickMessageTemplate=") + SanitizeIni(Cfg->TempBanKickMessageTemplate) + TEXT("\n")
        + TEXT("; URL included as {appeal_url} in ban kick messages.\n")
        + TEXT("AppealUrl=") + SanitizeIni(Cfg->AppealUrl) + TEXT("\n")
        + TEXT("\n")
        + TEXT("; -- Admin Action Rate Limiting ----------------------------------------------\n")
        + TEXT(";\n")
        + TEXT("; Maximum ban actions an admin may issue within AdminBanRateLimitMinutes (0 = disabled).\n")
        + TEXT("AdminBanRateLimitCount=") + FString::FromInt(Cfg->AdminBanRateLimitCount) + TEXT("\n")
        + TEXT("; Rolling window in minutes for the ban rate limiter (default: 5).\n")
        + TEXT("AdminBanRateLimitMinutes=") + FString::FromInt(Cfg->AdminBanRateLimitMinutes) + TEXT("\n")
        + TEXT("\n")
        + TEXT("; -- Chat-Pattern Auto-Warn / Auto-Mute -------------------------------------\n")
        + TEXT(";\n")
        + TEXT("; Chat-filter hits within ChatFilterAutoWarnWindowMinutes that auto-warn a player (0 = disabled).\n")
        + TEXT("ChatFilterAutoWarnThreshold=") + FString::FromInt(Cfg->ChatFilterAutoWarnThreshold) + TEXT("\n")
        + TEXT("; Rolling window in minutes for the chat-filter auto-warn counter (default: 10).\n")
        + TEXT("ChatFilterAutoWarnWindowMinutes=") + FString::FromInt(Cfg->ChatFilterAutoWarnWindowMinutes) + TEXT("\n")
        + TEXT("\n")
        + TEXT("; -- Geo-IP Region Blocking --------------------------------------------------\n")
        + TEXT(";\n")
        + TEXT("; When true, GeoIP lookups are performed at player login.\n")
        + TEXT("bGeoIpEnabled=") + (Cfg->bGeoIpEnabled ? TEXT("True") : TEXT("False")) + TEXT("\n")
        + TEXT("; GeoIP API URL. {ip} is replaced with the connecting player's IP address.\n")
        + TEXT("GeoIpApiUrl=") + SanitizeIni(Cfg->GeoIpApiUrl) + TEXT("\n")
        + TEXT("; Message shown to players kicked by the Geo-IP filter. Supports {country}.\n")
        + TEXT("GeoIpKickMessage=") + SanitizeIni(Cfg->GeoIpKickMessage) + TEXT("\n");

    // WarnEscalationTiers array — one entry per line
    FString TiersContent;
    for (const FWarnEscalationTier& Tier : Cfg->WarnEscalationTiers)
    {
        TiersContent += FString::Printf(
            TEXT("+WarnEscalationTiers=(WarnCount=%d,PointThreshold=%d,DurationMinutes=%d)\n"),
            Tier.WarnCount, Tier.PointThreshold, Tier.DurationMinutes);
    }

    // BanTemplates array — one entry per line
    FString BanTemplatesContent;
    for (const FString& BanTemplate : Cfg->BanTemplates)
    {
        BanTemplatesContent += TEXT("+BanTemplates=") + SanitizeIni(BanTemplate) + TEXT("\n");
    }

    // PeerWebSocketUrls array — one entry per line
    FString PeerUrlsContent;
    for (const FString& PeerUrl : Cfg->PeerWebSocketUrls)
    {
        PeerUrlsContent += TEXT("+PeerWebSocketUrls=") + SanitizeIni(PeerUrl) + TEXT("\n");
    }

    // AllowedCountryCodes array — one entry per line
    FString AllowedCountriesContent;
    for (const FString& Code : Cfg->AllowedCountryCodes)
    {
        AllowedCountriesContent += TEXT("+AllowedCountryCodes=") + SanitizeIni(Code) + TEXT("\n");
    }

    // BlockedCountryCodes array — one entry per line
    FString BlockedCountriesContent;
    for (const FString& Code : Cfg->BlockedCountryCodes)
    {
        BlockedCountriesContent += TEXT("+BlockedCountryCodes=") + SanitizeIni(Code) + TEXT("\n");
    }

    const FString FullContent = Content + TiersContent + BanTemplatesContent
        + PeerUrlsContent + AllowedCountriesContent + BlockedCountriesContent;

    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    PlatformFile.CreateDirectoryTree(*FPaths::GetPath(BackupPath));

    if (FFileHelper::SaveStringToFile(FullContent, *BackupPath,
        FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
    {
        UE_LOG(LogBanSystem, Log,
            TEXT("BanSystem: Updated backup config at '%s'."), *BackupPath);
    }
    else
    {
        UE_LOG(LogBanSystem, Warning,
            TEXT("BanSystem: Could not write backup config to '%s'."), *BackupPath);
    }
}

void FBanSystemModule::RestoreDefaultConfigIfNeeded()
{
    const FString DefaultIniPath = FPaths::Combine(
        FPaths::ProjectDir(),
        TEXT("Mods"), TEXT("BanSystem"),
        TEXT("Config"), TEXT("DefaultBanSystem.ini"));

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
        if (Existing.Contains(TEXT("#")))
            return; // comment lines present — leave as-is
    }

    const FString Content =
        FString(TEXT("# BanSystem configuration.\n"))
        + TEXT("#\n")
        + TEXT("# Settings in this file are read automatically by UBanSystemConfig\n")
        + TEXT("# (UCLASS Config=BanSystem).\n")
        + TEXT("#\n")
        + TEXT("# ── How to persist settings across mod updates ───────────────────────────────\n")
        + TEXT("#\n")
        + TEXT("# This file ships with the mod and may be replaced when you update BanSystem.\n")
        + TEXT("# To keep your settings permanently, place your overrides in ONE of:\n")
        + TEXT("#\n")
        + TEXT("#   1. Saved/BanSystem/BanSystem.ini          <- written by BanSystem on every\n")
        + TEXT("#                                                start; survives mod directory wipes\n")
        + TEXT("#   2. Saved/Config/<Platform>/BanSystem.ini  <- standard UE config override path\n")
        + TEXT("#\n")
        + TEXT("# Both use the same [/Script/BanSystem.BanSystemConfig] section header.\n")
        + TEXT("# Restart the server after editing any config file.\n")
        + TEXT("#\n")
        + TEXT("# Example override file contents:\n")
        + TEXT("#\n")
        + TEXT("#   [/Script/BanSystem.BanSystemConfig]\n")
        + TEXT("#   DatabasePath=/data/satisfactory/bans.json\n")
        + TEXT("#   RestApiPort=3001\n")
        + TEXT("#   MaxBackups=10\n")
        + TEXT("\n")
        + TEXT("[/Script/BanSystem.BanSystemConfig]\n")
        + TEXT("\n")
        + TEXT("# ── Database ──────────────────────────────────────────────────────────────────\n")
        + TEXT("#\n")
        + TEXT("# Absolute path to the JSON ban database file.\n")
        + TEXT("# Leave empty to use the default location: <ProjectSaved>/BanSystem/bans.json\n")
        + TEXT("#\n")
        + TEXT("# Default resolved paths by OS:\n")
        + TEXT("#   Windows: C:\\SatisfactoryServer\\FactoryGame\\Saved\\BanSystem\\bans.json\n")
        + TEXT("#   Linux:   /home/<user>/.config/Epic/FactoryGame/Saved/BanSystem/bans.json\n")
        + TEXT("#\n")
        + TEXT("# The parent directory is created automatically if it does not exist.\n")
        + TEXT("# A second file (player_sessions.json) is stored in the same directory as an\n")
        + TEXT("# audit log of all player UIDs and display names seen at join time.\n")
        + TEXT("DatabasePath=\n")
        + TEXT("\n")
        + TEXT("# ── REST Management API ───────────────────────────────────────────────────────\n")
        + TEXT("#\n")
        + TEXT("# Port for the local HTTP management API (default: 3000).\n")
        + TEXT("# The API binds to all interfaces (0.0.0.0) -- restrict external access with\n")
        + TEXT("# your server firewall.  The API has no authentication.\n")
        + TEXT("#\n")
        + TEXT("# Endpoints: GET /health, GET /bans, GET /bans/all, GET /bans/check/:uid,\n")
        + TEXT("#            POST /bans, DELETE /bans/:uid, DELETE /bans/id/:id,\n")
        + TEXT("#            POST /bans/prune, POST /bans/backup\n")
        + TEXT("#\n")
        + TEXT("# Set to 0 to disable the REST API entirely.\n")
        + TEXT("RestApiPort=3000\n")
        + TEXT("\n")
        + TEXT("# ── Backup ────────────────────────────────────────────────────────────────────\n")
        + TEXT("#\n")
        + TEXT("# Maximum number of timestamped backup files to keep (default: 5).\n")
        + TEXT("# Backups are created on demand via POST /bans/backup on the REST API.\n")
        + TEXT("# When this limit is reached the oldest backup is deleted automatically.\n")
        + TEXT("# Backups are stored alongside bans.json as bans_YYYY-MM-DD_HH-MM-SS.json.\n")
        + TEXT("MaxBackups=5\n")
        + TEXT("\n")
        + TEXT("# ── Warning Decay ─────────────────────────────────────────────────────────────\n")
        + TEXT("#\n")
        + TEXT("# Number of days after which warnings are considered \"decayed\" and excluded from\n")
        + TEXT("# automatic escalation checks (default: 0 = warnings never decay).\n")
        + TEXT("# When non-zero, GetWarningCount() ignores warnings older than WarnDecayDays days.\n")
        + TEXT("# Old warnings are NOT deleted — they remain in the history for audit purposes.\n")
        + TEXT("# Set to 0 to count all warnings regardless of age (original behaviour).\n")
        + TEXT("WarnDecayDays=0\n")
        + TEXT("\n")
        + TEXT("# ── REST API Authentication ───────────────────────────────────────────────────\n")
        + TEXT("#\n")
        + TEXT("# Optional API key for authenticating REST API requests.\n")
        + TEXT("# When non-empty, all endpoints except GET /health require the header: X-Api-Key: <value>\n")
        + TEXT("# Leave empty to disable API key authentication (default; only safe on a firewalled server).\n")
        + TEXT("RestApiKey=\n")
        + TEXT("\n")
        + TEXT("# ── Scheduled Backup ─────────────────────────────────────────────────────────\n")
        + TEXT("#\n")
        + TEXT("# Interval in hours between automatic database backups (default: 0 = disabled).\n")
        + TEXT("# Set to 0 to rely solely on the manual POST /bans/backup endpoint.\n")
        + TEXT("BackupIntervalHours=0\n")
        + TEXT("\n")
        + TEXT("# ── Discord Notifications ─────────────────────────────────────────────────────\n")
        + TEXT("#\n")
        + TEXT("# Optional Discord webhook URL for ban/unban/warn/kick notifications.\n")
        + TEXT("# When set, BanDiscordNotifier posts an embed to this URL whenever a ban is\n")
        + TEXT("# created or removed, a warning is issued, or a player is kicked.\n")
        + TEXT("# Leave empty to disable Discord notifications (default).\n")
        + TEXT("DiscordWebhookUrl=\n")
        + TEXT("\n")
        + TEXT("# When true, post a Discord notification when a temporary ban expires (default: false).\n")
        + TEXT("# Only has an effect when DiscordWebhookUrl is set.\n")
        + TEXT("bNotifyBanExpired=False\n")
        + TEXT("\n")
        + TEXT("# ── Auto-ban on Warnings ──────────────────────────────────────────────────────\n")
        + TEXT("#\n")
        + TEXT("# Number of warnings before an automatic permanent ban is issued (default: 0 = disabled).\n")
        + TEXT("# When a player reaches this many warnings via /warn, they are automatically\n")
        + TEXT("# permanently banned with reason \"Auto-banned: reached warning threshold\".\n")
        + TEXT("# Set to 0 to disable. Use WarnEscalationTiers below for multi-tier escalation.\n")
        + TEXT("AutoBanWarnCount=0\n")
        + TEXT("#\n")
        + TEXT("# Duration in minutes for the auto-ban issued when AutoBanWarnCount is reached (default: 0 = permanent).\n")
        + TEXT("# Set to 0 for a permanent auto-ban.\n")
        + TEXT("AutoBanWarnMinutes=0\n")
        + TEXT("\n")
        + TEXT("# ── Warning Escalation Tiers ─────────────────────────────────────────────────\n")
        + TEXT("#\n")
        + TEXT("# Multi-tier automatic bans based on warning count or accumulated warning points.\n")
        + TEXT("# Each tier: +WarnEscalationTiers=(WarnCount=<N>,PointThreshold=<P>,DurationMinutes=<M>)\n")
        + TEXT("# DurationMinutes=0 means permanent ban. PointThreshold=0 uses plain warn count.\n")
        + TEXT("# Example:\n")
        + TEXT("#   +WarnEscalationTiers=(WarnCount=2,PointThreshold=0,DurationMinutes=30)\n")
        + TEXT("#   +WarnEscalationTiers=(WarnCount=3,PointThreshold=0,DurationMinutes=1440)\n")
        + TEXT("#   +WarnEscalationTiers=(WarnCount=5,PointThreshold=0,DurationMinutes=0)\n")
        + TEXT("\n")
        + TEXT("# ── Session Retention ────────────────────────────────────────────────────────\n")
        + TEXT("#\n")
        + TEXT("# Number of days to retain player session records (default: 0 = keep forever).\n")
        + TEXT("# Records older than this value are pruned by POST /players/prune.\n")
        + TEXT("# Set to 0 to keep all records.\n")
        + TEXT("SessionRetentionDays=0\n")
        + TEXT("\n")
        + TEXT("# ── Auto-Prune ───────────────────────────────────────────────────────────────\n")
        + TEXT("#\n")
        + TEXT("# Interval in hours between automatic expired-ban prune runs (0 = disabled).\n")
        + TEXT("# Set to 0 to rely solely on the manual POST /bans/prune endpoint.\n")
        + TEXT("PruneIntervalHours=0\n")
        + TEXT("\n")
        + TEXT("# ── WebSocket Push Events ────────────────────────────────────────────────────\n")
        + TEXT("#\n")
        + TEXT("# When true, BanSystem pushes live JSON events to WebSocketPushUrl via SMLWebSocket.\n")
        + TEXT("bPushEventsToWebSocket=False\n")
        + TEXT("# WebSocket endpoint URL to push events to (requires SMLWebSocket mod).\n")
        + TEXT("WebSocketPushUrl=\n")
        + TEXT("\n")
        + TEXT("# ── Ban Templates (quick-ban presets) ────────────────────────────────────────\n")
        + TEXT("#\n")
        + TEXT("# Presets for /qban <slug> [reason]. Format: +BanTemplates=slug|DurationMinutes|Reason[|Category]\n")
        + TEXT("# DurationMinutes=0 means permanent.\n")
        + TEXT("# Example:\n")
        + TEXT("#   +BanTemplates=griefing|10080|Griefing — destroying other players' builds|griefing\n")
        + TEXT("#   +BanTemplates=cheating|0|Cheating — use of third-party tools|cheating\n")
        + TEXT("\n")
        + TEXT("# ── Kick Message Templates ────────────────────────────────────────────────────\n")
        + TEXT("#\n")
        + TEXT("# Custom message shown to permanently banned players. Supports {reason}, {appeal_url}.\n")
        + TEXT("# Leave empty to use the built-in default message.\n")
        + TEXT("BanKickMessageTemplate=\n")
        + TEXT("#\n")
        + TEXT("# Custom message shown to temporarily banned players. Supports {reason}, {expiry}, {appeal_url}.\n")
        + TEXT("# Leave empty to use the built-in default message.\n")
        + TEXT("TempBanKickMessageTemplate=\n")
        + TEXT("#\n")
        + TEXT("# URL included as {appeal_url} in ban kick messages.\n")
        + TEXT("# Example: AppealUrl=http://myserver.com:3000/appeals/portal\n")
        + TEXT("AppealUrl=\n")
        + TEXT("\n")
        + TEXT("# ── Multi-Server Ban Sync ─────────────────────────────────────────────────────\n")
        + TEXT("#\n")
        + TEXT("# WebSocket endpoint URLs of peer servers to synchronise bans with.\n")
        + TEXT("# Example: +PeerWebSocketUrls=ws://server2.example.com:9000/events\n")
        + TEXT("\n")
        + TEXT("# ── Admin Action Rate Limiting ────────────────────────────────────────────────\n")
        + TEXT("#\n")
        + TEXT("# Maximum ban actions an admin may issue within AdminBanRateLimitMinutes (0 = disabled).\n")
        + TEXT("AdminBanRateLimitCount=0\n")
        + TEXT("# Rolling window in minutes for the admin ban rate limiter (default: 5).\n")
        + TEXT("AdminBanRateLimitMinutes=5\n")
        + TEXT("\n")
        + TEXT("# ── Chat-Pattern Auto-Warn ────────────────────────────────────────────────────\n")
        + TEXT("#\n")
        + TEXT("# Chat-filter hits within ChatFilterAutoWarnWindowMinutes that auto-warn a player (0 = disabled).\n")
        + TEXT("ChatFilterAutoWarnThreshold=0\n")
        + TEXT("# Rolling window in minutes for the chat-filter auto-warn counter (default: 10).\n")
        + TEXT("ChatFilterAutoWarnWindowMinutes=10\n")
        + TEXT("\n")
        + TEXT("# ── Geo-IP Region Blocking ────────────────────────────────────────────────────\n")
        + TEXT("#\n")
        + TEXT("# When true, GeoIP lookups are performed at player login. Default: false.\n")
        + TEXT("bGeoIpEnabled=False\n")
        + TEXT("# GeoIP API URL. {ip} is replaced with the connecting player's IP address.\n")
        + TEXT("# Example: GeoIpApiUrl=http://ip-api.com/json/{ip}?fields=countryCode\n")
        + TEXT("GeoIpApiUrl=\n")
        + TEXT("# ISO 3166-1 alpha-2 allowlist. Takes priority over BlockedCountryCodes when non-empty.\n")
        + TEXT("# Example: +AllowedCountryCodes=US\n")
        + TEXT("# ISO 3166-1 alpha-2 blocklist (used when AllowedCountryCodes is empty).\n")
        + TEXT("# Example: +BlockedCountryCodes=XX\n")
        + TEXT("# Message shown to Geo-IP-kicked players. Supports {country}.\n")
        + TEXT("GeoIpKickMessage=\n");

    PlatformFile.CreateDirectoryTree(*FPaths::GetPath(DefaultIniPath));

    if (FFileHelper::SaveStringToFile(Content, *DefaultIniPath,
        FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
    {
        UE_LOG(LogBanSystem, Log,
            TEXT("BanSystem: Restored annotated default config at '%s'."), *DefaultIniPath);
    }
    else
    {
        UE_LOG(LogBanSystem, Warning,
            TEXT("BanSystem: Could not write default config to '%s'."), *DefaultIniPath);
    }
}

void FBanSystemModule::ShutdownModule()
{
    if (BackupTickHandle.IsValid())
    {
        FTSTicker::GetCoreTicker().RemoveTicker(BackupTickHandle);
        BackupTickHandle.Reset();
    }
    if (PruneTickHandle.IsValid())
    {
        FTSTicker::GetCoreTicker().RemoveTicker(PruneTickHandle);
        PruneTickHandle.Reset();
    }
    if (SessionPruneTickHandle.IsValid())
    {
        FTSTicker::GetCoreTicker().RemoveTicker(SessionPruneTickHandle);
        SessionPruneTickHandle.Reset();
    }
    if (ScheduledBanTickHandle.IsValid())
    {
        FTSTicker::GetCoreTicker().RemoveTicker(ScheduledBanTickHandle);
        ScheduledBanTickHandle.Reset();
    }
    if (ConfigPollTickHandle.IsValid())
    {
        FTSTicker::GetCoreTicker().RemoveTicker(ConfigPollTickHandle);
        ConfigPollTickHandle.Reset();
    }
    UE_LOG(LogBanSystem, Log, TEXT("BanSystem module shut down."));
}

bool FBanSystemModule::OnBackupTick(float DeltaTime)
{
    const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
    if (!Cfg || Cfg->BackupIntervalHours <= 0.0f) return true;

    // Find the game instance to get the UBanDatabase subsystem.
    // We walk the GEngine world list to find the first server world.
    if (GEngine)
    {
        for (const FWorldContext& Ctx : GEngine->GetWorldContexts())
        {
            UWorld* World = Ctx.World();
            if (!World) continue;
            if (World->GetNetMode() != NM_DedicatedServer && World->GetNetMode() != NM_ListenServer) continue;

            // Auto-pause-aware: don't accumulate interval time while the server
            // is paused (no players connected).  Bans/backups are deferred until
            // activity resumes, keeping the timer semantically meaningful.
            if (World->IsPaused()) return true;

            BackupAccumulatedSeconds += DeltaTime;
            const float IntervalSeconds = Cfg->BackupIntervalHours * 3600.0f;
            if (BackupAccumulatedSeconds < IntervalSeconds) return true;

            BackupAccumulatedSeconds -= IntervalSeconds;

            UGameInstance* GI = World->GetGameInstance();
            if (!GI) continue;
            UBanDatabase* DB = GI->GetSubsystem<UBanDatabase>();
            if (!DB) break;

            const FString BackupDir = FPaths::GetPath(DB->GetDatabasePath()) / TEXT("backups");
            const FString Dest = DB->Backup(BackupDir, Cfg ? Cfg->MaxBackups : 5);
            if (!Dest.IsEmpty())
            {
                UE_LOG(LogBanSystem, Log, TEXT("BanSystem: scheduled backup written to '%s'"), *Dest);
            }
            else
            {
                UE_LOG(LogBanSystem, Warning, TEXT("BanSystem: scheduled backup failed"));
            }
            break;
        }
    }

    return true; // keep ticking
}

bool FBanSystemModule::OnPruneTick(float DeltaTime)
{
    const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
    if (!Cfg || Cfg->PruneIntervalHours <= 0.0f) return true;

    if (GEngine)
    {
        for (const FWorldContext& Ctx : GEngine->GetWorldContexts())
        {
            UWorld* World = Ctx.World();
            if (!World) continue;
            if (World->GetNetMode() != NM_DedicatedServer && World->GetNetMode() != NM_ListenServer) continue;

            // Auto-pause-aware: freeze the prune interval while the server is idle.
            if (World->IsPaused()) return true;

            PruneAccumulatedSeconds += DeltaTime;
            const float IntervalSeconds = Cfg->PruneIntervalHours * 3600.0f;
            if (PruneAccumulatedSeconds < IntervalSeconds) return true;

            PruneAccumulatedSeconds -= IntervalSeconds;

            UGameInstance* GI = World->GetGameInstance();
            if (!GI) continue;
            UBanDatabase* DB = GI->GetSubsystem<UBanDatabase>();
            if (!DB) break;

            const int32 Pruned = DB->PruneExpiredBans();
            if (Pruned > 0)
            {
                UE_LOG(LogBanSystem, Log,
                    TEXT("BanSystem: auto-prune removed %d expired ban(s)."), Pruned);
            }

            // Also prune expired timed warnings.
            if (UPlayerWarningRegistry* WarnReg = GI->GetSubsystem<UPlayerWarningRegistry>())
                WarnReg->PruneExpiredWarnings();

            break;
        }
    }

    return true; // keep ticking
}

bool FBanSystemModule::OnSessionPruneTick(float DeltaTime)
{
    const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
    if (!Cfg || Cfg->SessionRetentionDays <= 0) return true;

    // Run once per 24 hours.
    static constexpr float SessionPruneIntervalSeconds = 24.0f * 3600.0f;

    if (GEngine)
    {
        for (const FWorldContext& Ctx : GEngine->GetWorldContexts())
        {
            UWorld* World = Ctx.World();
            if (!World) continue;
            if (World->GetNetMode() != NM_DedicatedServer && World->GetNetMode() != NM_ListenServer) continue;

            // Auto-pause-aware: hold the session-prune clock while idle.
            if (World->IsPaused()) return true;

            SessionPruneAccumulatedSeconds += DeltaTime;
            if (SessionPruneAccumulatedSeconds < SessionPruneIntervalSeconds) return true;

            SessionPruneAccumulatedSeconds -= SessionPruneIntervalSeconds;

            UGameInstance* GI = World->GetGameInstance();
            if (!GI) continue;
            UPlayerSessionRegistry* Reg = GI->GetSubsystem<UPlayerSessionRegistry>();
            if (!Reg) break;

            const int32 Pruned = Reg->PruneOldRecords(Cfg->SessionRetentionDays);
            if (Pruned > 0)
            {
                UE_LOG(LogBanSystem, Log,
                    TEXT("BanSystem: session-retention pruned %d record(s) older than %d day(s)."),
                    Pruned, Cfg->SessionRetentionDays);
            }
            break;
        }
    }

    return true; // keep ticking
}

bool FBanSystemModule::OnScheduledBanTick(float DeltaTime)
{
    if (GEngine)
    {
        for (const FWorldContext& Ctx : GEngine->GetWorldContexts())
        {
            UWorld* World = Ctx.World();
            if (!World) continue;
            if (World->GetNetMode() != NM_DedicatedServer && World->GetNetMode() != NM_ListenServer) continue;

            // Auto-pause-aware: when the server is auto-paused (no players) we
            // freeze the 30-second interval accumulator so scheduled bans do not
            // fire during idle time.  When the server unpauses, any ban whose
            // EffectiveAt has passed will be applied on the very next tick because
            // UScheduledBanRegistry::Tick() compares against FDateTime::UtcNow().
            if (World->IsPaused()) return true;

            UGameInstance* GI = World->GetGameInstance();
            if (!GI) continue;
            UScheduledBanRegistry* Reg = GI->GetSubsystem<UScheduledBanRegistry>();
            if (Reg)
                Reg->Tick(DeltaTime);
            break;
        }
    }
    return true; // keep ticking
}

bool FBanSystemModule::OnConfigPollTick(float /*DeltaTime*/)
{
    // Paths to both monitored INI files.
    const FString SavedIni = FPaths::Combine(
        FPaths::ProjectSavedDir(), TEXT("BanSystem"), TEXT("BanSystem.ini"));
    const FString DefaultIni = FPaths::Combine(
        FPaths::ProjectDir(), TEXT("Mods"), TEXT("BanSystem"),
        TEXT("Config"), TEXT("DefaultBanSystem.ini"));

    const FDateTime NewTimes[2] = {
        IFileManager::Get().GetTimeStamp(*SavedIni),
        IFileManager::Get().GetTimeStamp(*DefaultIni)
    };

    const bool bChanged = (NewTimes[0] != ConfigFileModTimes[0])
                       || (NewTimes[1] != ConfigFileModTimes[1]);

    if (bChanged)
    {
        ConfigFileModTimes[0] = NewTimes[0];
        ConfigFileModTimes[1] = NewTimes[1];

        // Force UE to re-read all UPROPERTY(Config) fields from the ini files.
        GetMutableDefault<UBanSystemConfig>()->ReloadConfig();

        // Update the persistent backup so any changes are mirrored to
        // Saved/BanSystem/BanSystem.ini even if the operator edited DefaultBanSystem.ini.
        BackupConfigIfNeeded();

        UE_LOG(LogBanSystem, Log,
            TEXT("BanSystem: config auto-reloaded (INI file changed on disk)."));
    }

    return true; // keep ticking
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBanSystemModule, BanSystem)
