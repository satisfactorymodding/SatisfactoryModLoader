// Copyright Yamahasxviper. All Rights Reserved.

#include "TicketConfig.h"

#include "Misc/ConfigCacheIni.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

// ─────────────────────────────────────────────────────────────────────────────
// Helpers
// ─────────────────────────────────────────────────────────────────────────────

static FString GetIniString(const FConfigFile& Cfg, const FString& Key,
                            const FString& Default = TEXT(""))
{
	FString Value;
	if (Cfg.GetString(TEXT("TicketSystem"), *Key, Value))
	{
		Value.TrimStartAndEndInline();
		return Value;
	}
	return Default;
}

static bool GetIniBool(const FConfigFile& Cfg, const FString& Key, bool Default)
{
	bool Value;
	if (Cfg.GetBool(TEXT("TicketSystem"), *Key, Value))
	{
		return Value;
	}
	return Default;
}

static float GetIniFloat(const FConfigFile& Cfg, const FString& Key, float Default)
{
	FString StrVal;
	if (Cfg.GetString(TEXT("TicketSystem"), *Key, StrVal))
	{
		StrVal.TrimStartAndEndInline();
		if (!StrVal.IsEmpty())
		{
			const float Result = FCString::Atof(*StrVal);
			return FMath::IsFinite(Result) ? Result : Default;
		}
	}
	return Default;
}

/** Read a config key as int32, clamping to [0, INT32_MAX] so callers never
 *  receive a negative value from a mis-typed or pathologically large entry. */
static int32 GetIniInt(const FConfigFile& Cfg, const FString& Key, int32 Default)
{
	const float Raw = GetIniFloat(Cfg, Key, static_cast<float>(Default));
	if (!FMath::IsFinite(Raw)) return Default;
	if (Raw < 0.0f) return 0;
	if (Raw > static_cast<float>(INT32_MAX)) return INT32_MAX;
	return static_cast<int32>(Raw);
}

/** Strip a leading UTF-8 BOM (EF BB BF) from a file on disk. */
static void CleanTicketConfigBOM(const FString& FilePath)
{
	TArray<uint8> RawBytes;
	if (!FFileHelper::LoadFileToArray(RawBytes, *FilePath))
		return;
	if (RawBytes.Num() >= 3 &&
	    RawBytes[0] == 0xEF &&
	    RawBytes[1] == 0xBB &&
	    RawBytes[2] == 0xBF)
	{
		RawBytes.RemoveAt(0, 3, /*bAllowShrinking=*/false);
		FFileHelper::SaveArrayToFile(RawBytes, *FilePath);
		UE_LOG(LogTicketSystem, Log,
		       TEXT("TicketSystem: Stripped UTF-8 BOM from '%s'."), *FilePath);
	}
}

/** Parse every occurrence of "Key=Value" in a raw INI file string. */
static TArray<FString> ParseRawIniArray(const FString& RawContent, const FString& Key)
{
	TArray<FString> Result;
	TArray<FString> Lines;
	RawContent.ParseIntoArrayLines(Lines);

	const FString Prefix = Key + TEXT("=");
	for (const FString& Line : Lines)
	{
		const FString Trimmed = Line.TrimStartAndEnd();
		if (Trimmed.StartsWith(Prefix))
		{
			Result.Add(Trimmed.Mid(Prefix.Len()).TrimStartAndEnd());
		}
	}
	return Result;
}

// ─────────────────────────────────────────────────────────────────────────────
// FTicketConfig
// ─────────────────────────────────────────────────────────────────────────────

FString FTicketConfig::GetConfigFilePath()
{
	// Use FPaths::ProjectDir() + "Mods/..." — the same pattern used by
	// BanSystem and DiscordBridge throughout this repo.
	// FPaths::ProjectModsDir() is not part of Satisfactory's CSS custom
	// Unreal Engine build and would cause a compile/link failure.
	return FPaths::ProjectDir() /
	       TEXT("Mods/DiscordBridge/Config/DefaultTickets.ini");
}

FString FTicketConfig::GetBackupFilePath()
{
	return FPaths::Combine(
		FPaths::ProjectSavedDir(),
		TEXT("DiscordBridge"),
		TEXT("TicketSystem.ini"));
}

TArray<FString> FTicketConfig::ParseChannelIds(const FString& CommaList)
{
	TArray<FString> Parts;
	CommaList.ParseIntoArray(Parts, TEXT(","), /*bCullEmpty=*/true);
	for (FString& Part : Parts)
	{
		Part.TrimStartAndEndInline();
	}
	return Parts;
}

FTicketConfig FTicketConfig::Load()
{
	FTicketConfig Config;

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	const FString PrimaryPath = GetConfigFilePath();
	const FString BackupPath  = GetBackupFilePath();

	// Proactively strip UTF-8 BOM if present.
	if (PlatformFile.FileExists(*PrimaryPath))
		CleanTicketConfigBOM(PrimaryPath);
	if (PlatformFile.FileExists(*BackupPath))
		CleanTicketConfigBOM(BackupPath);

	// ── Try to load the primary config file ───────────────────────────────────
	const bool bPrimaryExists = PlatformFile.FileExists(*PrimaryPath);

	if (bPrimaryExists)
	{
		FString RawContent;
		bool bRawContentLoaded = FFileHelper::LoadFileToString(RawContent, *PrimaryPath);
		if (!bRawContentLoaded)
		{
			UE_LOG(LogTicketSystem, Warning,
			       TEXT("TicketSystem: Failed reading raw config '%s'; array fields may use backup."),
			       *PrimaryPath);
			if (PlatformFile.FileExists(*BackupPath) &&
			    FFileHelper::LoadFileToString(RawContent, *BackupPath))
			{
				bRawContentLoaded = true;
				UE_LOG(LogTicketSystem, Warning,
				       TEXT("TicketSystem: Using backup raw config '%s' for array fields."),
				       *BackupPath);
			}
		}

		FConfigFile Cfg;
		Cfg.Read(PrimaryPath);

		Config.BotToken                 = GetIniString(Cfg, TEXT("BotToken"));
		Config.GuildId                  = GetIniString(Cfg, TEXT("GuildId"));
		Config.TicketChannelId          = GetIniString(Cfg, TEXT("TicketChannelId"));
		Config.TicketLogChannelId       = GetIniString(Cfg, TEXT("TicketLogChannelId"));
		Config.bTicketWhitelistEnabled  = GetIniBool  (Cfg, TEXT("TicketWhitelistEnabled"),  true);
		Config.bTicketHelpEnabled       = GetIniBool  (Cfg, TEXT("TicketHelpEnabled"),       true);
		Config.bTicketReportEnabled     = GetIniBool  (Cfg, TEXT("TicketReportEnabled"),     true);
		Config.bTicketBanAppealEnabled  = GetIniBool  (Cfg, TEXT("BanAppealEnabled"),        true);
		Config.bTicketMuteAppealEnabled = GetIniBool  (Cfg, TEXT("MuteAppealEnabled"),       true);
		Config.TicketNotifyRoleId       = GetIniString(Cfg, TEXT("TicketNotifyRoleId"));
		Config.TicketPanelChannelId     = GetIniString(Cfg, TEXT("TicketPanelChannelId"));
		Config.TicketCategoryId         = GetIniString(Cfg, TEXT("TicketCategoryId"));
		Config.CustomTicketReasons      = bRawContentLoaded ? ParseRawIniArray(RawContent, TEXT("TicketReason")) : TArray<FString>{};
		Config.InactiveTicketTimeoutHours = GetIniFloat(Cfg, TEXT("InactiveTicketTimeoutHours"), 0.0f);
		Config.WhitelistCategoryId         = GetIniString(Cfg, TEXT("WhitelistCategoryId"));
		Config.HelpCategoryId              = GetIniString(Cfg, TEXT("HelpCategoryId"));
		Config.ReportCategoryId            = GetIniString(Cfg, TEXT("ReportCategoryId"));
		Config.AppealCategoryId            = GetIniString(Cfg, TEXT("AppealCategoryId"));
		Config.MuteAppealCategoryId        = GetIniString(Cfg, TEXT("MuteAppealCategoryId"));
		Config.bTicketFeedbackEnabled      = GetIniBool  (Cfg, TEXT("TicketFeedbackEnabled"),      false);
		Config.TicketMacros                = bRawContentLoaded ? ParseRawIniArray(RawContent, TEXT("TicketMacro")) : TArray<FString>{};
		Config.TicketCooldownMinutes       = GetIniInt(Cfg, TEXT("TicketCooldownMinutes"), 0);
		Config.TicketReopenGracePeriodMinutes = GetIniInt(Cfg, TEXT("TicketReopenGracePeriodMinutes"), 0);
		Config.bAllowMultipleTicketTypes   = GetIniBool  (Cfg, TEXT("AllowMultipleTicketTypes"),   false);
		Config.bAutoRefreshPanel           = GetIniBool  (Cfg, TEXT("AutoRefreshPanel"),           false);
		Config.bDmOpenerOnStaffReply       = GetIniBool  (Cfg, TEXT("DmOpenerOnStaffReply"),       false);
		Config.TicketSlaWarningMinutes     = GetIniInt(Cfg, TEXT("TicketSlaWarningMinutes"), 0);
		Config.TicketEscalationRoleId      = GetIniString(Cfg, TEXT("TicketEscalationRoleId"));
		Config.TicketEscalationCategoryId  = GetIniString(Cfg, TEXT("TicketEscalationCategoryId"));
		Config.TicketTemplates             = bRawContentLoaded ? ParseRawIniArray(RawContent, TEXT("TicketTemplate")) : TArray<FString>{};
		Config.TicketAutoResponses         = bRawContentLoaded ? ParseRawIniArray(RawContent, TEXT("TicketAutoResponse")) : TArray<FString>{};
		Config.BanAppealCooldownDays       = GetIniInt(Cfg, TEXT("BanAppealCooldownDays"), 0);
		Config.MaxLifetimeAppeals          = GetIniInt(Cfg, TEXT("MaxLifetimeAppeals"), 0);

		UE_LOG(LogTicketSystem, Log,
		       TEXT("TicketSystem: Loaded config from %s"), *PrimaryPath);
	}
	else
	{
		// ── Fall back to backup ────────────────────────────────────────────────
		if (PlatformFile.FileExists(*BackupPath))
		{
			FString BackupRaw;
			const bool bBackupRawLoaded = FFileHelper::LoadFileToString(BackupRaw, *BackupPath);
			if (!bBackupRawLoaded)
			{
				UE_LOG(LogTicketSystem, Warning,
				       TEXT("TicketSystem: Failed reading backup raw config '%s'; array fields will stay empty."),
				       *BackupPath);
			}

			FConfigFile BackupCfg;
			BackupCfg.Read(BackupPath);

			Config.BotToken                = GetIniString(BackupCfg, TEXT("BotToken"));
			Config.GuildId                 = GetIniString(BackupCfg, TEXT("GuildId"));
			Config.TicketChannelId         = GetIniString(BackupCfg, TEXT("TicketChannelId"));
			Config.TicketLogChannelId      = GetIniString(BackupCfg, TEXT("TicketLogChannelId"));
			Config.bTicketWhitelistEnabled = GetIniBool  (BackupCfg, TEXT("TicketWhitelistEnabled"), true);
			Config.bTicketHelpEnabled      = GetIniBool  (BackupCfg, TEXT("TicketHelpEnabled"),      true);
			Config.bTicketReportEnabled    = GetIniBool  (BackupCfg, TEXT("TicketReportEnabled"),    true);
			Config.bTicketBanAppealEnabled = GetIniBool  (BackupCfg, TEXT("BanAppealEnabled"),       true);
			Config.bTicketMuteAppealEnabled = GetIniBool (BackupCfg, TEXT("MuteAppealEnabled"),      true);
			Config.TicketNotifyRoleId      = GetIniString(BackupCfg, TEXT("TicketNotifyRoleId"));
			Config.TicketPanelChannelId    = GetIniString(BackupCfg, TEXT("TicketPanelChannelId"));
			Config.TicketCategoryId        = GetIniString(BackupCfg, TEXT("TicketCategoryId"));
			Config.CustomTicketReasons     = bBackupRawLoaded ? ParseRawIniArray(BackupRaw, TEXT("TicketReason")) : TArray<FString>{};
			Config.InactiveTicketTimeoutHours = GetIniFloat(BackupCfg, TEXT("InactiveTicketTimeoutHours"), 0.0f);
			Config.WhitelistCategoryId         = GetIniString(BackupCfg, TEXT("WhitelistCategoryId"));
			Config.HelpCategoryId              = GetIniString(BackupCfg, TEXT("HelpCategoryId"));
			Config.ReportCategoryId            = GetIniString(BackupCfg, TEXT("ReportCategoryId"));
			Config.AppealCategoryId            = GetIniString(BackupCfg, TEXT("AppealCategoryId"));
			Config.MuteAppealCategoryId        = GetIniString(BackupCfg, TEXT("MuteAppealCategoryId"));
			Config.bTicketFeedbackEnabled      = GetIniBool  (BackupCfg, TEXT("TicketFeedbackEnabled"),      false);
			Config.TicketMacros                = bBackupRawLoaded ? ParseRawIniArray(BackupRaw, TEXT("TicketMacro")) : TArray<FString>{};
			Config.TicketCooldownMinutes       = GetIniInt(BackupCfg, TEXT("TicketCooldownMinutes"), 0);
			Config.TicketReopenGracePeriodMinutes = GetIniInt(BackupCfg, TEXT("TicketReopenGracePeriodMinutes"), 0);
			Config.bAllowMultipleTicketTypes   = GetIniBool  (BackupCfg, TEXT("AllowMultipleTicketTypes"),   false);
			Config.bAutoRefreshPanel           = GetIniBool  (BackupCfg, TEXT("AutoRefreshPanel"),           false);
			Config.bDmOpenerOnStaffReply       = GetIniBool  (BackupCfg, TEXT("DmOpenerOnStaffReply"),       false);
			Config.TicketSlaWarningMinutes     = GetIniInt(BackupCfg, TEXT("TicketSlaWarningMinutes"), 0);
			Config.TicketEscalationRoleId      = GetIniString(BackupCfg, TEXT("TicketEscalationRoleId"));
			Config.TicketEscalationCategoryId  = GetIniString(BackupCfg, TEXT("TicketEscalationCategoryId"));
			Config.TicketTemplates             = bBackupRawLoaded ? ParseRawIniArray(BackupRaw, TEXT("TicketTemplate")) : TArray<FString>{};
			Config.TicketAutoResponses         = bBackupRawLoaded ? ParseRawIniArray(BackupRaw, TEXT("TicketAutoResponse")) : TArray<FString>{};
			Config.BanAppealCooldownDays       = GetIniInt(BackupCfg, TEXT("BanAppealCooldownDays"), 0);
			Config.MaxLifetimeAppeals          = GetIniInt(BackupCfg, TEXT("MaxLifetimeAppeals"), 0);

			UE_LOG(LogTicketSystem, Log,
			       TEXT("TicketSystem: Primary config not found at '%s' – restored from backup."),
			       *PrimaryPath);
		}
		else
		{
			UE_LOG(LogTicketSystem, Warning,
			       TEXT("TicketSystem: No config found at '%s' or '%s'. Using defaults."),
			       *PrimaryPath, *BackupPath);
		}
	}

	// ── Write the backup ───────────────────────────────────────────────────────
	// Build a raw key=value map to write to the backup file so settings survive
	// a mod update that resets DefaultTickets.ini.
	if (bPrimaryExists || PlatformFile.FileExists(*BackupPath))
	{
		FString BackupContent;
		BackupContent += TEXT("[TicketSystem]\n");
		BackupContent += FString::Printf(TEXT("BotToken=%s\n"),               *Config.BotToken);
		BackupContent += FString::Printf(TEXT("GuildId=%s\n"),                *Config.GuildId);
		BackupContent += FString::Printf(TEXT("TicketChannelId=%s\n"),        *Config.TicketChannelId);
		BackupContent += FString::Printf(TEXT("TicketLogChannelId=%s\n"),     *Config.TicketLogChannelId);
		BackupContent += FString::Printf(TEXT("TicketWhitelistEnabled=%s\n"), Config.bTicketWhitelistEnabled ? TEXT("True") : TEXT("False"));
		BackupContent += FString::Printf(TEXT("TicketHelpEnabled=%s\n"),      Config.bTicketHelpEnabled      ? TEXT("True") : TEXT("False"));
		BackupContent += FString::Printf(TEXT("TicketReportEnabled=%s\n"),    Config.bTicketReportEnabled    ? TEXT("True") : TEXT("False"));
		BackupContent += FString::Printf(TEXT("BanAppealEnabled=%s\n"),       Config.bTicketBanAppealEnabled ? TEXT("True") : TEXT("False"));
		BackupContent += FString::Printf(TEXT("MuteAppealEnabled=%s\n"),      Config.bTicketMuteAppealEnabled ? TEXT("True") : TEXT("False"));
		BackupContent += FString::Printf(TEXT("TicketNotifyRoleId=%s\n"),     *Config.TicketNotifyRoleId);
		BackupContent += FString::Printf(TEXT("TicketPanelChannelId=%s\n"),   *Config.TicketPanelChannelId);
		BackupContent += FString::Printf(TEXT("TicketCategoryId=%s\n"),       *Config.TicketCategoryId);
		for (const FString& Reason : Config.CustomTicketReasons)
		{
			BackupContent += FString::Printf(TEXT("TicketReason=%s\n"), *Reason);
		}
		BackupContent += FString::Printf(TEXT("InactiveTicketTimeoutHours=%.2f\n"),
			Config.InactiveTicketTimeoutHours);
		BackupContent += FString::Printf(TEXT("WhitelistCategoryId=%s\n"),         *Config.WhitelistCategoryId);
		BackupContent += FString::Printf(TEXT("HelpCategoryId=%s\n"),              *Config.HelpCategoryId);
		BackupContent += FString::Printf(TEXT("ReportCategoryId=%s\n"),            *Config.ReportCategoryId);
		BackupContent += FString::Printf(TEXT("AppealCategoryId=%s\n"),            *Config.AppealCategoryId);
		BackupContent += FString::Printf(TEXT("MuteAppealCategoryId=%s\n"),        *Config.MuteAppealCategoryId);
		BackupContent += FString::Printf(TEXT("TicketFeedbackEnabled=%s\n"),       Config.bTicketFeedbackEnabled      ? TEXT("True") : TEXT("False"));
		BackupContent += FString::Printf(TEXT("TicketCooldownMinutes=%d\n"),       Config.TicketCooldownMinutes);
		BackupContent += FString::Printf(TEXT("TicketReopenGracePeriodMinutes=%d\n"), Config.TicketReopenGracePeriodMinutes);
		BackupContent += FString::Printf(TEXT("AllowMultipleTicketTypes=%s\n"),    Config.bAllowMultipleTicketTypes   ? TEXT("True") : TEXT("False"));
		BackupContent += FString::Printf(TEXT("AutoRefreshPanel=%s\n"),            Config.bAutoRefreshPanel           ? TEXT("True") : TEXT("False"));
		BackupContent += FString::Printf(TEXT("DmOpenerOnStaffReply=%s\n"),        Config.bDmOpenerOnStaffReply       ? TEXT("True") : TEXT("False"));
		BackupContent += FString::Printf(TEXT("TicketSlaWarningMinutes=%d\n"),     Config.TicketSlaWarningMinutes);
		BackupContent += FString::Printf(TEXT("TicketEscalationRoleId=%s\n"),      *Config.TicketEscalationRoleId);
		BackupContent += FString::Printf(TEXT("TicketEscalationCategoryId=%s\n"),  *Config.TicketEscalationCategoryId);
		for (const FString& Tmpl : Config.TicketTemplates)
		{
			BackupContent += FString::Printf(TEXT("TicketTemplate=%s\n"), *Tmpl);
		}
		for (const FString& AR : Config.TicketAutoResponses)
		{
			BackupContent += FString::Printf(TEXT("TicketAutoResponse=%s\n"), *AR);
		}
		for (const FString& Macro : Config.TicketMacros)
		{
			BackupContent += FString::Printf(TEXT("TicketMacro=%s\n"), *Macro);
		}
		BackupContent += FString::Printf(TEXT("BanAppealCooldownDays=%d\n"),       Config.BanAppealCooldownDays);
		BackupContent += FString::Printf(TEXT("MaxLifetimeAppeals=%d\n"),           Config.MaxLifetimeAppeals);

		PlatformFile.CreateDirectoryTree(*FPaths::GetPath(BackupPath));
		if (FFileHelper::SaveStringToFile(BackupContent, *BackupPath,
			FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
		{
			UE_LOG(LogTicketSystem, Log,
			       TEXT("TicketSystem: Updated backup config at '%s'."), *BackupPath);
		}
		else
		{
			UE_LOG(LogTicketSystem, Warning,
			       TEXT("TicketSystem: Could not write backup config to '%s'."), *BackupPath);
		}
	}

	return Config;
}

// ─────────────────────────────────────────────────────────────────────────────
// Template restoration
// ─────────────────────────────────────────────────────────────────────────────

void FTicketConfig::RestoreDefaultConfigIfNeeded()
{
	const FString PrimaryPath = GetConfigFilePath();
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	// Leave the file as-is if it already contains comment lines — that means
	// it was either hand-edited or previously written by this function.
	if (PlatformFile.FileExists(*PrimaryPath))
	{
		FString Existing;
		FFileHelper::LoadFileToString(Existing, *PrimaryPath);
		if (Existing.Contains(TEXT("# ")))
			return;
	}

	// File is missing or was stripped of comments by Alpakit — write the
	// annotated template so operators can see setting descriptions.
	// This content mirrors DefaultTickets.ini shipped in the repository.
	const FString Template =
		TEXT("[TicketSystem]\n")
		TEXT("# TicketSystem - Configuration\n")
		TEXT("# ============================\n")
		TEXT("#\n")
		TEXT("# NOTE: this file is NOT overwritten by mod updates. Your settings persist\n")
		TEXT("# across version upgrades. A backup is also written automatically to\n")
		TEXT("#   <ServerRoot>/FactoryGame/Saved/DiscordBridge/TicketSystem.ini\n")
		TEXT("# on every server start so settings survive primary file deletion.\n")
		TEXT("#\n")
		TEXT("# STANDALONE MODE: set BotToken to run without DiscordBridge.\n")
		TEXT("# PAIRED MODE: leave BotToken empty — DiscordBridge will power the tickets.\n")
		TEXT("\n")
		TEXT("# -- STANDALONE DISCORD BOT (leave empty when using DiscordBridge) ------------\n")
		TEXT("BotToken=\n")
		TEXT("# Your Discord bot token. Required for standalone mode (without DiscordBridge).\n")
		TEXT("# SECURITY: Keep private. Leave empty when DiscordBridge is installed.\n")
		TEXT("\n")
		TEXT("GuildId=\n")
		TEXT("# Optional Discord guild (server) ID. Leave empty to auto-detect (recommended).\n")
		TEXT("\n")
		TEXT("# -- TICKET CHANNEL -----------------------------------------------------------\n")
		TEXT("TicketChannelId=\n")
		TEXT("# Discord channel ID(s) where ticket notifications are posted (comma-separated).\n")
		TEXT("\n")
		TEXT("TicketLogChannelId=\n")
		TEXT("# Discord channel ID for closed-ticket transcripts. Leave empty to disable.\n")
		TEXT("\n")
		TEXT("# -- TICKET TYPE TOGGLES ------------------------------------------------------\n")
		TEXT("TicketWhitelistEnabled=True\n")
		TEXT("# Whether the Whitelist Request button is shown on the ticket panel. Default: True.\n")
		TEXT("\n")
		TEXT("TicketHelpEnabled=True\n")
		TEXT("# Whether the Help / Support button is shown on the ticket panel. Default: True.\n")
		TEXT("\n")
		TEXT("TicketReportEnabled=True\n")
		TEXT("# Whether the Report a Player button is shown on the ticket panel. Default: True.\n")
		TEXT("\n")
		TEXT("BanAppealEnabled=True\n")
		TEXT("# Whether the Ban Appeal button is shown on the ticket panel. Default: True.\n")
		TEXT("\n")
		TEXT("MuteAppealEnabled=True\n")
		TEXT("# Whether the Mute Appeal button is shown on the ticket panel. Default: True.\n")
		TEXT("\n")
		TEXT("# -- ADMIN NOTIFICATIONS ------------------------------------------------------\n")
		TEXT("TicketNotifyRoleId=\n")
		TEXT("# Discord role ID to @mention when a new ticket is created.\n")
		TEXT("# Members of this role also get access to every ticket channel.\n")
		TEXT("# Members holding this role can run /ticket panel to post the panel.\n")
		TEXT("\n")
		TEXT("# -- BUTTON-BASED TICKET PANEL ------------------------------------------------\n")
		TEXT("TicketPanelChannelId=\n")
		TEXT("# Discord channel ID where the bot posts the ticket selection panel.\n")
		TEXT("# Required bot permissions: Manage Channels, View Channel, Send Messages.\n")
		TEXT("\n")
		TEXT("TicketCategoryId=\n")
		TEXT("# Optional Discord category ID to place created ticket channels under.\n")
		TEXT("\n")
		TEXT("# -- PER-TYPE CATEGORY IDS (optional overrides) -------------------------------\n")
		TEXT("# Override the category for specific ticket types. Leave empty to use TicketCategoryId.\n")
		TEXT("WhitelistCategoryId=\n")
		TEXT("HelpCategoryId=\n")
		TEXT("ReportCategoryId=\n")
		TEXT("AppealCategoryId=\n")
		TEXT("\n")
		TEXT("MuteAppealCategoryId=\n")
		TEXT("# Optional category ID for mute appeal ticket channels. Falls back to TicketCategoryId.\n")
		TEXT("\n")
		TEXT("# -- CUSTOM TICKET REASONS ----------------------------------------------------\n")
		TEXT("# Add one line per custom button: TicketReason=Label|Description\n")
		TEXT("# Example:\n")
		TEXT("#   TicketReason=Bug Report|Report a bug or technical issue\n")
		TEXT("\n")
		TEXT("# -- INACTIVE TICKET AUTO-CLOSE -----------------------------------------------\n")
		TEXT("InactiveTicketTimeoutHours=0\n")
		TEXT("# Hours of inactivity before an open ticket is automatically closed. 0 = disabled.\n")
		TEXT("\n")
		TEXT("# -- ADVANCED OPTIONS ---------------------------------------------------------\n")
		TEXT("TicketFeedbackEnabled=False\n")
		TEXT("# When True, a DM with a star-rating request is sent to the opener on close. Default: False.\n")
		TEXT("\n")
		TEXT("TicketCooldownMinutes=0\n")
		TEXT("# Cooldown in minutes between ticket opens per user. 0 = disabled.\n")
		TEXT("\n")
		TEXT("TicketReopenGracePeriodMinutes=0\n")
		TEXT("# Grace period in minutes for re-opening a recently closed ticket. 0 = disabled.\n")
		TEXT("\n")
		TEXT("AllowMultipleTicketTypes=False\n")
		TEXT("# Allow a user to have multiple open tickets of different types. Default: False.\n")
		TEXT("\n")
		TEXT("AutoRefreshPanel=False\n")
		TEXT("# Auto-refresh the panel embed on each server start. Default: False.\n")
		TEXT("\n")
		TEXT("DmOpenerOnStaffReply=False\n")
		TEXT("# DM the ticket opener when a staff member replies. Default: False.\n")
		TEXT("\n")
		TEXT("TicketSlaWarningMinutes=0\n")
		TEXT("# Minutes before SLA warning is posted (0 = disabled).\n")
		TEXT("\n")
		TEXT("TicketEscalationRoleId=\n")
		TEXT("# Role to @mention on /ticket escalate. Leave empty to disable.\n")
		TEXT("\n")
		TEXT("TicketEscalationCategoryId=\n")
		TEXT("# Category to move escalated tickets to. Leave empty to keep in place.\n")
		TEXT("\n")
		TEXT("# -- TICKET MACROS ------------------------------------------------------------\n")
		TEXT("# Canned responses staff can insert with /ticket macro <name>.\n")
		TEXT("# Format: TicketMacro=name|response text\n")
		TEXT("# Example:\n")
		TEXT("#   TicketMacro=greeting|Hello! Thanks for opening a ticket. How can we help?\n")
		TEXT("#   TicketMacro=closing|This ticket will be closed. Please re-open if you need more help.\n")
		TEXT("\n")
		TEXT("# Ban appeal macros\n")
		TEXT("TicketMacro=appeal_pending|:hourglass: Your appeal has been received and is under review. We will respond as soon as possible. Please be patient.\n")
		TEXT("TicketMacro=appeal_more_info|:information_source: We need more information to process your appeal. Please provide your in-game name, your EOS Player UID, and a detailed explanation of why the ban should be lifted.\n")
		TEXT("TicketMacro=appeal_cheating|:no_entry: After reviewing the evidence, your ban for cheating / exploiting has been upheld. This decision is final.\n")
		TEXT("TicketMacro=appeal_griefing|:no_entry: After reviewing the evidence, your ban for griefing has been upheld. Our server has a zero-tolerance policy for intentional destruction of other players' work.\n")
		TEXT("TicketMacro=appeal_harassment|:no_entry: After reviewing the evidence, your ban for harassment / toxic behaviour has been upheld. All players are expected to treat each other with respect.\n")
		TEXT("TicketMacro=appeal_approved|:white_check_mark: Your ban appeal has been approved. You are now free to rejoin the server. Please review our server rules before doing so.\n")
		TEXT("# General macros\n")
		TEXT("TicketMacro=greeting|:wave: Hello! Thanks for opening a ticket. How can we help you today?\n")
		TEXT("TicketMacro=closing|:envelope: This ticket will now be closed. If you need further assistance, please open a new ticket.\n")
		TEXT("\n")
		TEXT("# -- TICKET TEMPLATES ---------------------------------------------------------\n")
		TEXT("# Structured intake forms shown when a ticket type is opened.\n")
		TEXT("# Format: TicketTemplate=TypeSlug|Field1Label|Field2Label|...\n")
		TEXT("# Example:\n")
		TEXT("#   TicketTemplate=report|Player Name|What happened|Evidence link\n")
		TEXT("#   TicketTemplate=whitelist|In-Game Name|How did you find us\n")
		TEXT("\n")
		TEXT("# -- TICKET AUTO-RESPONSES ----------------------------------------------------\n")
		TEXT("# Automatic message sent to the ticket channel when a ticket of a given type is opened.\n")
		TEXT("# Format: TicketAutoResponse=TypeSlug|Auto-response message text\n")
		TEXT("# Example:\n")
		TEXT("#   TicketAutoResponse=whitelist|Please provide your in-game name and how you found the server.\n")
		TEXT("#   TicketAutoResponse=report|Please include the player name, what happened, and any evidence.\n")
		TEXT("\n")
		TEXT("# -- BAN APPEAL RATE-LIMITING -------------------------------------------------\n")
		TEXT("BanAppealCooldownDays=0\n")
		TEXT("# Days a player must wait after a denied appeal before submitting another.\n")
		TEXT("# Set to 0 (default) to disable the cooldown.\n")
		TEXT("\n")
		TEXT("MaxLifetimeAppeals=0\n")
		TEXT("# Maximum number of lifetime denied ban appeals a player may submit.\n")
		TEXT("# Once reached, further appeal tickets are blocked. 0 = disabled.\n");

	PlatformFile.CreateDirectoryTree(*FPaths::GetPath(PrimaryPath));
	if (FFileHelper::SaveStringToFile(Template, *PrimaryPath,
		FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
	{
		UE_LOG(LogTicketSystem, Log,
		       TEXT("TicketSystem: Created annotated config template at '%s'. "
		            "Set TicketPanelChannelId and TicketNotifyRoleId to enable the ticket panel."),
		       *PrimaryPath);
	}
	else
	{
		UE_LOG(LogTicketSystem, Warning,
		       TEXT("TicketSystem: Could not write config template to '%s'."), *PrimaryPath);
	}
}
