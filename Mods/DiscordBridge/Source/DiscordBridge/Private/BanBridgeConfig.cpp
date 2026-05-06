// Copyright Yamahasxviper. All Rights Reserved.

#include "BanBridgeConfig.h"

#include "Misc/ConfigCacheIni.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

DEFINE_LOG_CATEGORY(LogBanDiscord);

// -----------------------------------------------------------------------------
// BOM helpers
// -----------------------------------------------------------------------------

/** Strip a leading UTF-8 BOM (EF BB BF) from a file on disk. */
static void CleanBanBridgeConfigBOM(const FString& FilePath)
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
		UE_LOG(LogBanDiscord, Log,
		       TEXT("BanBridge: Stripped UTF-8 BOM from '%s'."), *FilePath);
	}
}

// -----------------------------------------------------------------------------
// Internal helpers
// -----------------------------------------------------------------------------

static FString GetIniBridgeString(const FConfigFile& Cfg, const FString& Key,
                                   const FString& Default = TEXT(""))
{
	FString Value;
	if (Cfg.GetString(TEXT("BanBridge"), *Key, Value))
	{
		Value.TrimStartAndEndInline();
		return Value;
	}
	return Default;
}

// -----------------------------------------------------------------------------
// FBanBridgeConfig
// -----------------------------------------------------------------------------

FString FBanBridgeConfig::GetConfigFilePath()
{
	// Mirror the pattern used by DiscordBridgeConfig and TicketConfig in this
	// repository: resolve relative to FPaths::ProjectDir() so the path works
	// on both the Windows editor host and Linux dedicated server.
	return FPaths::ProjectDir() /
	       TEXT("Mods/DiscordBridge/Config/DefaultBanBridge.ini");
}

FString FBanBridgeConfig::GetBackupFilePath()
{
	return FPaths::Combine(
		FPaths::ProjectSavedDir(),
		TEXT("DiscordBridge"),
		TEXT("BanBridge.ini"));
}

FBanBridgeConfig FBanBridgeConfig::Load()
{
	FBanBridgeConfig Out;

	const FString PrimaryPath = GetConfigFilePath();
	const FString BackupPath  = GetBackupFilePath();

	IPlatformFile& PF = FPlatformFileManager::Get().GetPlatformFile();

	// Proactively strip UTF-8 BOM if present.
	if (PF.FileExists(*PrimaryPath))
		CleanBanBridgeConfigBOM(PrimaryPath);
	if (PF.FileExists(*BackupPath))
		CleanBanBridgeConfigBOM(BackupPath);

	FConfigFile Cfg;
	bool bLoaded = false;

	// Try primary config file first.
	if (PF.FileExists(*PrimaryPath))
	{
		Cfg.Read(PrimaryPath);
		bLoaded = Cfg.Contains(TEXT("BanBridge"));
	}

	// Fall back to the backup copy if primary is missing or empty.
	if (!bLoaded && PF.FileExists(*BackupPath))
	{
		Cfg.Read(BackupPath);
		bLoaded = Cfg.Contains(TEXT("BanBridge"));
	}

	if (!bLoaded)
	{
		UE_LOG(LogBanDiscord, Log,
		       TEXT("BanBridge: No [BanBridge] section found at '%s'. "
		            "Discord ban commands are disabled until AdminRoleId is set."),
		       *PrimaryPath);
		return Out;
	}

	Out.AdminRoleId            = GetIniBridgeString(Cfg, TEXT("AdminRoleId"));
	Out.ModeratorRoleId        = GetIniBridgeString(Cfg, TEXT("ModeratorRoleId"));
	Out.BanCommandChannelId    = GetIniBridgeString(Cfg, TEXT("BanCommandChannelId"));
	Out.ModerationLogChannelId = GetIniBridgeString(Cfg, TEXT("ModerationLogChannelId"));
	Out.AdminPanelChannelId    = GetIniBridgeString(Cfg, TEXT("AdminPanelChannelId"));
	Out.StaffChatChannelId     = GetIniBridgeString(Cfg, TEXT("StaffChatChannelId"));

	// Validate: non-empty role/channel IDs must be 17-20 digit Discord snowflakes.
	// GetIniBridgeString already trims whitespace; this catches typos like "general".
	auto WarnBadSnowflake = [](const FString& Value, const TCHAR* Key)
	{
		if (Value.IsEmpty()) return;
		if (!Value.IsNumeric() || Value.Len() < 17 || Value.Len() > 20)
		{
			UE_LOG(LogBanDiscord, Warning,
			       TEXT("BanBridge: '%s' = \"%s\" is not a valid Discord snowflake "
			            "(expected 17-20 digit numeric string). "
			            "Check DefaultBanBridge.ini."),
			       Key, *Value);
		}
	};
	WarnBadSnowflake(Out.AdminRoleId,            TEXT("AdminRoleId"));
	WarnBadSnowflake(Out.ModeratorRoleId,        TEXT("ModeratorRoleId"));
	WarnBadSnowflake(Out.BanCommandChannelId,    TEXT("BanCommandChannelId"));
	WarnBadSnowflake(Out.ModerationLogChannelId, TEXT("ModerationLogChannelId"));
	WarnBadSnowflake(Out.AdminPanelChannelId,    TEXT("AdminPanelChannelId"));
	WarnBadSnowflake(Out.StaffChatChannelId,     TEXT("StaffChatChannelId"));

	if (Out.AdminRoleId.IsEmpty())
	{
		UE_LOG(LogBanDiscord, Log,
		       TEXT("BanBridge: AdminRoleId is not set. Discord ban commands are disabled."));
	}
	else
	{
		UE_LOG(LogBanDiscord, Log,
		       TEXT("BanBridge: AdminRoleId            = \"%s\""), *Out.AdminRoleId);
		UE_LOG(LogBanDiscord, Log,
		       TEXT("BanBridge: ModeratorRoleId        = \"%s\""),
		       Out.ModeratorRoleId.IsEmpty() ? TEXT("(not set)") : *Out.ModeratorRoleId);
		UE_LOG(LogBanDiscord, Log,
		       TEXT("BanBridge: BanCommandChannelId    = \"%s\""),
		       Out.BanCommandChannelId.IsEmpty() ? TEXT("(any channel)") : *Out.BanCommandChannelId);
		UE_LOG(LogBanDiscord, Log,
		       TEXT("BanBridge: ModerationLogChannelId = \"%s\""),
		       Out.ModerationLogChannelId.IsEmpty() ? TEXT("(disabled)") : *Out.ModerationLogChannelId);
		UE_LOG(LogBanDiscord, Log,
		       TEXT("BanBridge: AdminPanelChannelId    = \"%s\""),
		       Out.AdminPanelChannelId.IsEmpty() ? TEXT("(command channel)") : *Out.AdminPanelChannelId);
		UE_LOG(LogBanDiscord, Log,
		       TEXT("BanBridge: StaffChatChannelId     = \"%s\""),
		       Out.StaffChatChannelId.IsEmpty() ? TEXT("(disabled)") : *Out.StaffChatChannelId);
	}

	// -- Write backup ---------------------------------------------------------
	// Mirror the pattern used by DiscordBridgeConfig and TicketConfig: on every
	// server start write the current settings to Saved/DiscordBridge/BanBridge.ini
	// so they survive any future deletion or reset of the primary config file.
	{
		const FString BackupContent =
			FString(TEXT("[BanBridge]\n"))
			+ TEXT("# Auto-generated backup of DefaultBanBridge.ini.\n")
			+ TEXT("# This file is read automatically when the primary config has no [BanBridge] section.\n")
			+ TEXT("AdminRoleId=")            + Out.AdminRoleId            + TEXT("\n")
			+ TEXT("ModeratorRoleId=")        + Out.ModeratorRoleId        + TEXT("\n")
			+ TEXT("BanCommandChannelId=")    + Out.BanCommandChannelId    + TEXT("\n")
			+ TEXT("ModerationLogChannelId=") + Out.ModerationLogChannelId + TEXT("\n")
			+ TEXT("AdminPanelChannelId=")    + Out.AdminPanelChannelId    + TEXT("\n")
			+ TEXT("StaffChatChannelId=")     + Out.StaffChatChannelId     + TEXT("\n");

		PF.CreateDirectoryTree(*FPaths::GetPath(BackupPath));
		if (FFileHelper::SaveStringToFile(BackupContent, *BackupPath,
			FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
		{
			UE_LOG(LogBanDiscord, Log,
			       TEXT("BanBridge: Updated backup config at '%s'."), *BackupPath);
		}
		else
		{
			UE_LOG(LogBanDiscord, Warning,
			       TEXT("BanBridge: Could not write backup config to '%s'."), *BackupPath);
		}
	}

	return Out;
}

// -----------------------------------------------------------------------------
// Authorisation helpers
// -----------------------------------------------------------------------------

bool FBanBridgeConfig::IsAdminRole(const TArray<FString>& Roles) const
{
	return !AdminRoleId.IsEmpty() && Roles.Contains(AdminRoleId);
}

bool FBanBridgeConfig::IsModeratorRole(const TArray<FString>& Roles) const
{
	if (IsAdminRole(Roles))
		return true;
	return !ModeratorRoleId.IsEmpty() && Roles.Contains(ModeratorRoleId);
}

// -----------------------------------------------------------------------------
// Template restoration
// -----------------------------------------------------------------------------

void FBanBridgeConfig::RestoreDefaultConfigIfNeeded()
{
	const FString PrimaryPath = GetConfigFilePath();
	IPlatformFile& PF = FPlatformFileManager::Get().GetPlatformFile();

	// Declare the template here — used both in the early-return fallback write
	// (line ~215) and in the main write path below.  Declaring it after the
	// early-return block (as it was previously) causes use-before-declaration UB.
	// This content mirrors DefaultBanBridge.ini shipped in the repository.
	const FString Template =
		TEXT("# DiscordBridge - BanSystem integration settings\n")
		TEXT("# -----------------------------------------------------------------------------\n")
		TEXT("# Configure the Discord role and channel IDs for ban/moderation commands.\n")
		TEXT("#\n")
		TEXT("# NOTE: this file is NOT overwritten by mod updates. Your settings persist\n")
		TEXT("# across version upgrades. A backup is also written automatically to\n")
		TEXT("#   <ServerRoot>/FactoryGame/Saved/DiscordBridge/BanBridge.ini\n")
		TEXT("# on every server start so settings survive primary file deletion.\n")
		TEXT("#\n")
		TEXT("[BanBridge]\n")
		TEXT("\n")
		TEXT("AdminRoleId=\n")
		TEXT("# Discord role ID whose members may run ALL ban/moderation commands.\n")
		TEXT("# Leave empty to disable all Discord ban commands.\n")
		TEXT("# How to get: Discord Settings -> Advanced -> Developer Mode,\n")
		TEXT("# then right-click the role in Server Settings -> Roles -> Copy Role ID.\n")
		TEXT("\n")
		TEXT("ModeratorRoleId=\n")
		TEXT("# Optional: Discord role ID for moderators with limited command access.\n")
		TEXT("# Moderators may use: /mod kick, /mod ban, /mod mute, /mod unmute, /mod tempmute,\n")
		TEXT("# /mod mutecheck, /mod mutelist, /mod announce, /mod stafflist, /mod staffchat.\n")
		TEXT("# Leave empty to restrict those commands to admins only.\n")
		TEXT("\n")
		TEXT("BanCommandChannelId=\n")
		TEXT("# Optional: restrict ban commands to a single Discord channel.\n")
		TEXT("# Leave empty to allow ban commands from any channel the bot can see.\n")
		TEXT("\n")
		TEXT("ModerationLogChannelId=\n")
		TEXT("# Optional: Discord channel ID to post a moderation log after every\n")
		TEXT("# ban/unban/kick/mute/warn action. Leave empty to disable logging.\n")
		TEXT("\n")
		TEXT("AdminPanelChannelId=\n")
		TEXT("# Optional: Discord channel ID where /admin panel posts the interactive\n")
		TEXT("# admin panel embed. When empty the panel is sent to the channel in which\n")
		TEXT("# the /admin panel command was issued.\n")
		TEXT("\n")
		TEXT("StaffChatChannelId=\n")
		TEXT("# Optional: Discord channel ID for the bidirectional staff-chat bridge.\n")
		TEXT("# When set:\n")
		TEXT("#   - In-game /staffchat messages are mirrored to this Discord channel.\n")
		TEXT("#   - Regular messages posted to this channel by Discord staff are\n")
		TEXT("#     relayed to all online admin/moderator players in-game.\n")
		TEXT("# Leave empty to disable the staff-chat bridge (default).\n");

	// Leave the file as-is if it already contains comment lines - that means
	// it was either hand-edited or previously written by this function.
	if (PF.FileExists(*PrimaryPath))
	{
		FString Existing;
		const bool bReadOk = FFileHelper::LoadFileToString(Existing, *PrimaryPath);
		if (!bReadOk)
		{
			// File absent or unreadable — write template only if file truly doesn't exist
			if (!IFileManager::Get().FileExists(*PrimaryPath))
				FFileHelper::SaveStringToFile(Template, *PrimaryPath,
					FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM);
			return;
		}
		if (Existing.Contains(TEXT("#")))
			return;
	}

	// File is missing or was stripped of comments by Alpakit - write the
	// annotated template so operators can see setting descriptions.

	PF.CreateDirectoryTree(*FPaths::GetPath(PrimaryPath));
	if (FFileHelper::SaveStringToFile(Template, *PrimaryPath,
		FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
	{
		UE_LOG(LogBanDiscord, Log,
		       TEXT("BanBridge: Created annotated config template at '%s'. "
		            "Set AdminRoleId to enable Discord ban commands."), *PrimaryPath);
	}
	else
	{
		UE_LOG(LogBanDiscord, Warning,
		       TEXT("BanBridge: Could not write config template to '%s'."), *PrimaryPath);
	}
}
