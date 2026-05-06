// Copyright Yamahasxviper. All Rights Reserved.

#include "WhitelistConfig.h"

#include "Misc/ConfigCacheIni.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

DEFINE_LOG_CATEGORY(LogWhitelistConfig);

// -----------------------------------------------------------------------------
// BOM helpers
// -----------------------------------------------------------------------------

/** Strip a leading UTF-8 BOM (EF BB BF) from a file on disk. */
static void CleanWhitelistConfigBOM(const FString& FilePath)
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
		UE_LOG(LogWhitelistConfig, Log,
		       TEXT("Whitelist: Stripped UTF-8 BOM from '%s'."), *FilePath);
	}
}

// -----------------------------------------------------------------------------
// Internal helpers
// -----------------------------------------------------------------------------

static const TCHAR* WLSection = TEXT("Whitelist");

static FString GetWLString(const FConfigFile& Cfg, const FString& Key,
                           const FString& Default = TEXT(""))
{
	FString Value;
	if (Cfg.GetString(WLSection, *Key, Value))
	{
		Value.TrimStartAndEndInline();
		return Value;
	}
	return Default;
}

static FString GetWLStringOrFallback(const FConfigFile& Cfg, const FString& Key,
                                     const FString& Default)
{
	FString Value;
	return (Cfg.GetString(WLSection, *Key, Value) && !Value.IsEmpty()) ? Value : Default;
}

static bool GetWLBool(const FConfigFile& Cfg, const FString& Key, bool Default)
{
	FString StrValue;
	if (!Cfg.GetString(WLSection, *Key, StrValue) || StrValue.IsEmpty())
		return Default;
	bool Value = Default;
	Cfg.GetBool(WLSection, *Key, Value);
	return Value;
}

static int32 GetWLInt(const FConfigFile& Cfg, const FString& Key, int32 Default)
{
	FString Value;
	if (Cfg.GetString(WLSection, *Key, Value) && !Value.IsEmpty())
	{
		if (!Value.IsNumeric() || Value.Len() > 10)
			return Default;
		return FCString::Atoi(*Value);
	}
	return Default;
}

static float GetWLFloat(const FConfigFile& Cfg, const FString& Key, float Default)
{
	FString Value;
	if (Cfg.GetString(WLSection, *Key, Value) && !Value.IsEmpty())
	{
		const float Result = FCString::Atof(*Value);
		return FMath::IsFinite(Result) ? Result : Default;
	}
	return Default;
}

// -----------------------------------------------------------------------------
// FWhitelistConfig
// -----------------------------------------------------------------------------

FString FWhitelistConfig::GetConfigFilePath()
{
	return FPaths::ProjectDir() /
	       TEXT("Mods/DiscordBridge/Config/DefaultWhitelist.ini");
}

FString FWhitelistConfig::GetBackupFilePath()
{
	return FPaths::Combine(
		FPaths::ProjectSavedDir(),
		TEXT("DiscordBridge"),
		TEXT("Whitelist.ini"));
}

FWhitelistConfig FWhitelistConfig::Load()
{
	FWhitelistConfig Out;

	const FString PrimaryPath = GetConfigFilePath();
	const FString BackupPath  = GetBackupFilePath();

	IPlatformFile& PF = FPlatformFileManager::Get().GetPlatformFile();

	// Proactively strip UTF-8 BOM if present.
	if (PF.FileExists(*PrimaryPath))
		CleanWhitelistConfigBOM(PrimaryPath);
	if (PF.FileExists(*BackupPath))
		CleanWhitelistConfigBOM(BackupPath);

	FConfigFile Cfg;
	bool bLoaded = false;

	// Try primary config file first.
	if (PF.FileExists(*PrimaryPath))
	{
		Cfg.Read(PrimaryPath);
		bLoaded = Cfg.Contains(WLSection);
	}

	// Fall back to the backup copy if primary is missing or empty.
	if (!bLoaded && PF.FileExists(*BackupPath))
	{
		Cfg.Read(BackupPath);
		bLoaded = Cfg.Contains(WLSection);
	}

	if (!bLoaded)
	{
		UE_LOG(LogWhitelistConfig, Log,
		       TEXT("Whitelist: No [Whitelist] section found at '%s'. "
		            "Whitelist is disabled until configured."),
		       *PrimaryPath);
		return Out;
	}

	Out.bWhitelistEnabled                = GetWLBool  (Cfg, TEXT("WhitelistEnabled"),                Out.bWhitelistEnabled);
	Out.WhitelistCommandRoleId           = GetWLString(Cfg, TEXT("WhitelistCommandRoleId"));
	Out.WhitelistRoleId                  = GetWLString(Cfg, TEXT("WhitelistRoleId"));
	Out.WhitelistChannelId               = GetWLString(Cfg, TEXT("WhitelistChannelId"));
	Out.WhitelistKickDiscordMessage      = GetWLString(Cfg, TEXT("WhitelistKickDiscordMessage"),     Out.WhitelistKickDiscordMessage);
	Out.WhitelistKickReason              = GetWLStringOrFallback(Cfg, TEXT("WhitelistKickReason"),   Out.WhitelistKickReason);
	Out.WhitelistEventsChannelId         = GetWLString(Cfg, TEXT("WhitelistEventsChannelId"));
	Out.MaxWhitelistSlots                = GetWLInt   (Cfg, TEXT("MaxWhitelistSlots"),               Out.MaxWhitelistSlots);
	Out.bSyncWhitelistWithRole           = GetWLBool  (Cfg, TEXT("SyncWhitelistWithRole"),           Out.bSyncWhitelistWithRole);
	Out.WhitelistApplicationChannelId    = GetWLString(Cfg, TEXT("WhitelistApplicationChannelId"));
	Out.bWhitelistApplyEnabled           = GetWLBool  (Cfg, TEXT("WhitelistApplyEnabled"),           Out.bWhitelistApplyEnabled);
	Out.WhitelistApprovedDmMessage       = GetWLString(Cfg, TEXT("WhitelistApprovedDmMessage"));
	Out.WhitelistExpiryWarningHours      = GetWLFloat (Cfg, TEXT("WhitelistExpiryWarningHours"),     Out.WhitelistExpiryWarningHours);
	Out.bWhitelistVerificationEnabled    = GetWLBool  (Cfg, TEXT("WhitelistVerificationEnabled"),    Out.bWhitelistVerificationEnabled);
	Out.WhitelistVerificationChannelId   = GetWLString(Cfg, TEXT("WhitelistVerificationChannelId"));

	UE_LOG(LogWhitelistConfig, Log,
	       TEXT("Whitelist: WhitelistEnabled           = %s"), Out.bWhitelistEnabled ? TEXT("True") : TEXT("False"));
	UE_LOG(LogWhitelistConfig, Log,
	       TEXT("Whitelist: WhitelistCommandRoleId     = \"%s\""),
	       Out.WhitelistCommandRoleId.IsEmpty() ? TEXT("(not set)") : *Out.WhitelistCommandRoleId);
	UE_LOG(LogWhitelistConfig, Log,
	       TEXT("Whitelist: WhitelistRoleId            = \"%s\""),
	       Out.WhitelistRoleId.IsEmpty() ? TEXT("(not set)") : *Out.WhitelistRoleId);
	UE_LOG(LogWhitelistConfig, Log,
	       TEXT("Whitelist: WhitelistChannelId         = \"%s\""),
	       Out.WhitelistChannelId.IsEmpty() ? TEXT("(disabled)") : *Out.WhitelistChannelId);
	UE_LOG(LogWhitelistConfig, Log,
	       TEXT("Whitelist: MaxWhitelistSlots          = %d"), Out.MaxWhitelistSlots);
	UE_LOG(LogWhitelistConfig, Log,
	       TEXT("Whitelist: SyncWhitelistWithRole      = %s"), Out.bSyncWhitelistWithRole ? TEXT("True") : TEXT("False"));
	UE_LOG(LogWhitelistConfig, Log,
	       TEXT("Whitelist: WhitelistApplyEnabled      = %s"), Out.bWhitelistApplyEnabled ? TEXT("True") : TEXT("False"));
	UE_LOG(LogWhitelistConfig, Log,
	       TEXT("Whitelist: WhitelistExpiryWarningHours= %.1f"), Out.WhitelistExpiryWarningHours);
	UE_LOG(LogWhitelistConfig, Log,
	       TEXT("Whitelist: WhitelistVerification      = %s"), Out.bWhitelistVerificationEnabled ? TEXT("True") : TEXT("False"));

	// -- Write backup ---------------------------------------------------------
	{
		const FString BackupContent =
			FString(TEXT("[Whitelist]\n"))
			+ TEXT("# Auto-generated backup of DefaultWhitelist.ini.\n")
			+ TEXT("# This file is read automatically when the primary config has no [Whitelist] section.\n")
			+ TEXT("WhitelistEnabled=") + (Out.bWhitelistEnabled ? TEXT("True") : TEXT("False")) + TEXT("\n")
			+ TEXT("WhitelistCommandRoleId=") + Out.WhitelistCommandRoleId + TEXT("\n")
			+ TEXT("WhitelistRoleId=") + Out.WhitelistRoleId + TEXT("\n")
			+ TEXT("WhitelistChannelId=") + Out.WhitelistChannelId + TEXT("\n")
			+ TEXT("WhitelistKickDiscordMessage=") + Out.WhitelistKickDiscordMessage + TEXT("\n")
			+ TEXT("WhitelistKickReason=") + Out.WhitelistKickReason + TEXT("\n")
			+ TEXT("WhitelistEventsChannelId=") + Out.WhitelistEventsChannelId + TEXT("\n")
			+ TEXT("MaxWhitelistSlots=") + FString::FromInt(Out.MaxWhitelistSlots) + TEXT("\n")
			+ TEXT("SyncWhitelistWithRole=") + (Out.bSyncWhitelistWithRole ? TEXT("True") : TEXT("False")) + TEXT("\n")
			+ TEXT("WhitelistApplicationChannelId=") + Out.WhitelistApplicationChannelId + TEXT("\n")
			+ TEXT("WhitelistApplyEnabled=") + (Out.bWhitelistApplyEnabled ? TEXT("True") : TEXT("False")) + TEXT("\n")
			+ TEXT("WhitelistApprovedDmMessage=") + Out.WhitelistApprovedDmMessage + TEXT("\n")
			+ TEXT("WhitelistExpiryWarningHours=") + FString::SanitizeFloat(Out.WhitelistExpiryWarningHours) + TEXT("\n")
			+ TEXT("WhitelistVerificationEnabled=") + (Out.bWhitelistVerificationEnabled ? TEXT("True") : TEXT("False")) + TEXT("\n")
			+ TEXT("WhitelistVerificationChannelId=") + Out.WhitelistVerificationChannelId + TEXT("\n");

		PF.CreateDirectoryTree(*FPaths::GetPath(BackupPath));
		if (FFileHelper::SaveStringToFile(BackupContent, *BackupPath,
			FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
		{
			UE_LOG(LogWhitelistConfig, Log,
			       TEXT("Whitelist: Updated backup config at '%s'."), *BackupPath);
		}
		else
		{
			UE_LOG(LogWhitelistConfig, Warning,
			       TEXT("Whitelist: Could not write backup config to '%s'."), *BackupPath);
		}
	}

	return Out;
}

// -----------------------------------------------------------------------------
// Template restoration
// -----------------------------------------------------------------------------

void FWhitelistConfig::RestoreDefaultConfigIfNeeded()
{
	const FString PrimaryPath = GetConfigFilePath();
	IPlatformFile& PF = FPlatformFileManager::Get().GetPlatformFile();

	// Leave the file as-is if it already contains comment lines - that means
	// it was either hand-edited or previously written by this function.
	// Check for both '# ' (current) and '; ' (legacy) comment markers so
	// that configs from any version are recognised and preserved.
	if (PF.FileExists(*PrimaryPath))
	{
		FString Existing;
		FFileHelper::LoadFileToString(Existing, *PrimaryPath);
		if (Existing.Contains(TEXT("# ")) || Existing.Contains(TEXT("; ")))
			return;
	}

	// File is missing or was stripped of comments by Alpakit - write the
	// annotated template so operators can see setting descriptions.
	const FString Template =
		TEXT("# DiscordBridge - Whitelist Settings\n")
		TEXT("# -----------------------------------------------------------------------------\n")
		TEXT("# All whitelist settings are configured here.  Edit this file, then restart\n")
		TEXT("# the server for changes to take effect.\n")
		TEXT("# Note: this file is NOT overwritten by mod updates, so your settings persist\n")
		TEXT("#   across version upgrades. A backup is still written automatically to\n")
		TEXT("#   <ServerRoot>/FactoryGame/Saved/DiscordBridge/Whitelist.ini\n")
		TEXT("#   on every server start so settings survive primary file deletion.\n")
		TEXT("# To apply changes: restart the server (or delete this file to regenerate it).\n")
		TEXT("\n")
		TEXT("[Whitelist]\n")
		TEXT("\n")
		TEXT("WhitelistEnabled=False\n")
		TEXT("# Whether the whitelist is active on every server start.\n")
		TEXT("# Default: False (all players can join).\n")
		TEXT("\n")
		TEXT("WhitelistCommandRoleId=\n")
		TEXT("# Snowflake ID of the Discord role whose members may run /whitelist commands.\n")
		TEXT("# Leave empty to disable /whitelist commands for all Discord users.\n")
		TEXT("# How to get: Discord Settings > Advanced > Developer Mode,\n")
		TEXT("# then right-click the role in Server Settings > Roles > Copy Role ID.\n")
		TEXT("\n")
		TEXT("WhitelistRoleId=\n")
		TEXT("# Snowflake ID of the Discord role assigned to whitelisted members.\n")
		TEXT("# Leave empty to disable Discord role integration.\n")
		TEXT("\n")
		TEXT("WhitelistChannelId=\n")
		TEXT("# Snowflake ID of a dedicated Discord channel for whitelisted members.\n")
		TEXT("# Leave empty to disable the whitelist-only channel.\n")
		TEXT("\n")
		TEXT("WhitelistKickDiscordMessage=:boot: **%PlayerName%** tried to join but is not on the whitelist and was kicked.\n")
		TEXT("# Message posted to Discord when a non-whitelisted player is kicked.\n")
		TEXT("# Leave empty to disable. Placeholder: %PlayerName%.\n")
		TEXT("\n")
		TEXT("WhitelistKickReason=You are not on the server whitelist. Contact the server admin to be added.\n")
		TEXT("# Reason shown in-game to the player when kicked for not being whitelisted.\n")
		TEXT("\n")
		TEXT("WhitelistEventsChannelId=\n")
		TEXT("# Snowflake ID of a Discord channel for whitelist event notifications.\n")
		TEXT("# Leave empty to disable whitelist event notifications.\n")
		TEXT("\n")
		TEXT("MaxWhitelistSlots=0\n")
		TEXT("# Maximum number of whitelist slots. 0 = unlimited.\n")
		TEXT("\n")
		TEXT("SyncWhitelistWithRole=False\n")
		TEXT("# When True, auto-add/remove players based on Discord WhitelistRoleId membership.\n")
		TEXT("\n")
		TEXT("WhitelistApplicationChannelId=\n")
		TEXT("# Channel where whitelist application embeds (Approve/Deny) are posted.\n")
		TEXT("# Leave empty to disable the application flow.\n")
		TEXT("\n")
		TEXT("WhitelistApplyEnabled=False\n")
		TEXT("# When True, any Discord user can run /whitelist apply <InGameName>. Default: False.\n")
		TEXT("\n")
		TEXT("WhitelistApprovedDmMessage=\n")
		TEXT("# DM sent to user when approved. %PlayerName% placeholder. Leave empty to disable.\n")
		TEXT("\n")
		TEXT("WhitelistExpiryWarningHours=24\n")
		TEXT("# Hours before expiry to post a warning embed. 0 = disabled. Default: 24.\n")
		TEXT("\n")
		TEXT("WhitelistVerificationEnabled=False\n")
		TEXT("# When True, enables /whitelist link / in-game /verify account linking. Default: False.\n")
		TEXT("\n")
		TEXT("WhitelistVerificationChannelId=\n")
		TEXT("# Channel where /whitelist link commands are accepted. Empty = any channel.\n");

	PF.CreateDirectoryTree(*FPaths::GetPath(PrimaryPath));
	if (FFileHelper::SaveStringToFile(Template, *PrimaryPath,
		FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
	{
		UE_LOG(LogWhitelistConfig, Log,
		       TEXT("Whitelist: Created annotated config template at '%s'. "
		            "Set WhitelistEnabled=True and WhitelistCommandRoleId to enable the whitelist."),
		       *PrimaryPath);
	}
	else
	{
		UE_LOG(LogWhitelistConfig, Warning,
		       TEXT("Whitelist: Could not write config template to '%s'."), *PrimaryPath);
	}
}
