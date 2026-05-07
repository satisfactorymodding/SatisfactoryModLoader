// Copyright Yamahasxviper. All Rights Reserved.

#include "DiscordBridgeConfig.h"

#include "HAL/PlatformFileManager.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

// ─────────────────────────────────────────────────────────────────────────────
// Helpers
// ─────────────────────────────────────────────────────────────────────────────

namespace
{
	static const TCHAR* ConfigSection = TEXT("DiscordBridge");
	static const TCHAR* MaxInt32String = TEXT("2147483647");

	// Strip a leading UTF-8 BOM character (U+FEFF) from an FString in-place.
	// This handles the case where LoadFileToString preserves the BOM character
	// in the FString content, or where external tools have written the file
	// with a BOM that was round-tripped into the string.
	void StripBOM(FString& Str)
	{
		if (!Str.IsEmpty() && Str[0] == 0xFEFF)
		{
			Str.RemoveAt(0, 1, /*bAllowShrinking=*/false);
		}
	}

	// Check whether a file on disk starts with a UTF-8 BOM (bytes EF BB BF).
	// If so, strip the BOM and rewrite the file without it.  This is called
	// once at the start of LoadOrCreate to proactively clean up BOM corruption
	// regardless of the source (UE4 config hierarchy, text editors, etc.).
	void CleanDiscordConfigBOM(const FString& FilePath)
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
			UE_LOG(LogDiscordBridge, Log,
			       TEXT("DiscordBridge: Stripped UTF-8 BOM from '%s'."), *FilePath);
		}
	}

	// Returns the INI value when the key exists (including empty string values).
	// Use for optional settings where an empty value intentionally disables the feature.
	FString GetIniStringOrDefault(const FConfigFile& Cfg,
	                              const FString& Key,
	                              const FString& Default)
	{
		FString Value;
		return Cfg.GetString(ConfigSection, *Key, Value) ? Value : Default;
	}

	// Returns the INI value only when non-empty; falls back to Default otherwise.
	// Use for format/reason strings where leaving a setting blank means "use the default".
	FString GetIniStringOrFallback(const FConfigFile& Cfg,
	                               const FString& Key,
	                               const FString& Default)
	{
		FString Value;
		return (Cfg.GetString(ConfigSection, *Key, Value) && !Value.IsEmpty()) ? Value : Default;
	}

	bool GetIniBoolOrDefault(const FConfigFile& Cfg,
	                         const FString& Key,
	                         bool Default)
	{
		FString StrValue;
		if (!Cfg.GetString(ConfigSection, *Key, StrValue) || StrValue.IsEmpty())
			return Default;
		bool Value = Default;
		Cfg.GetBool(ConfigSection, *Key, Value);
		return Value;
	}

	float GetIniFloatOrDefault(const FConfigFile& Cfg,
	                           const FString& Key,
	                           float Default)
	{
		FString Value;
		if (Cfg.GetString(ConfigSection, *Key, Value) && !Value.IsEmpty())
		{
			const float Result = FCString::Atof(*Value);
			return FMath::IsFinite(Result) ? Result : Default;
		}
		return Default;
	}

	bool TryParseNonNegativeInt32(const FString& Value, int32& Out)
	{
		if (!Value.IsNumeric() || Value.IsEmpty() || Value.Len() > 10)
			return false;
		if (Value.Len() == 10 && Value > MaxInt32String)
			return false;
		const int64 Parsed = FCString::Atoi64(*Value);
		if (Parsed < 0 || Parsed > static_cast<int64>(INT32_MAX))
			return false;
		Out = static_cast<int32>(Parsed);
		return true;
	}

	int32 GetIniIntOrDefault(const FConfigFile& Cfg,
	                         const FString& Key,
	                         int32 Default)
	{
		FString Value;
		if (Cfg.GetString(ConfigSection, *Key, Value) && !Value.IsEmpty())
		{
			int32 Parsed = 0;
			if (!TryParseNonNegativeInt32(Value, Parsed))
			{
				UE_LOG(LogDiscordBridge, Warning,
					TEXT("DiscordBridgeConfig: '%s' = '%s' is not numeric, using default %d"),
					*Key, *Value, Default);
				return Default;
			}
			return Parsed;
		}
		return Default;
	}

	// ── Raw INI readers (used for the backup file) ────────────────────────────
	// FConfigFile::GetString can expand %property% references in values, which
	// corrupts user-defined format strings that intentionally use %placeholders%
	// (e.g. %ServerName%, %PlayerName%, %Message%).  Since ServerName IS a key
	// in [DiscordBridge], FConfigFile would silently replace %ServerName% with
	// the current server name when reading back the backup, and PatchLine would
	// then write that expanded (corrupted) value permanently into the primary
	// config.  Reading the backup with raw string operations avoids all such
	// processing and guarantees values are preserved exactly as written.

	// Parses the named section of a raw INI file content string into a key→value
	// map.  Values are stored verbatim (no escape-sequence or %property%
	// expansion).  Duplicate keys are resolved in favour of the last occurrence.
	TMap<FString, FString> ParseRawIniSection(const FString& RawContent,
	                                          const FString& Section)
	{
		TMap<FString, FString> Result;
		const FString SectionHeader = FString(TEXT("[")) + Section + TEXT("]");

		bool bInSection = false;
		int32 Pos       = 0;

		while (Pos < RawContent.Len())
		{
			int32 LineEnd = RawContent.Find(
				TEXT("\n"), ESearchCase::CaseSensitive, ESearchDir::FromStart, Pos);
			const bool bLastLine = (LineEnd == INDEX_NONE);
			if (bLastLine)
				LineEnd = RawContent.Len();

			// Strip the trailing \r for CRLF files before processing.
			FString Line = RawContent.Mid(Pos, LineEnd - Pos);
			if (!Line.IsEmpty() && Line[Line.Len() - 1] == TEXT('\r'))
				Line.RemoveAt(Line.Len() - 1, 1, /*bAllowShrinking=*/false);

			Pos = bLastLine ? RawContent.Len() : (LineEnd + 1);

			const FString Trimmed = Line.TrimStart();
			if (Trimmed.IsEmpty() || Trimmed.StartsWith(TEXT(";")) || Trimmed.StartsWith(TEXT("#")))
				continue; // skip blank lines and comments

			if (Trimmed.StartsWith(TEXT("[")))
			{
				bInSection = (Trimmed.TrimEnd() == SectionHeader);
				continue;
			}

			if (bInSection)
			{
				int32 EqPos = INDEX_NONE;
				if (Line.FindChar(TEXT('='), EqPos))
				{
					const FString Key   = Line.Left(EqPos).TrimStartAndEnd();
					const FString Value = Line.Mid(EqPos + 1); // keep verbatim
					if (!Key.IsEmpty())
						Result.Add(Key, Value);
				}
			}
		}

		return Result;
	}

	// Raw-map equivalents of the FConfigFile helpers above.

	FString GetRawStringOrDefault(const TMap<FString, FString>& Raw,
	                              const FString& Key,
	                              const FString& Default)
	{
		const FString* Found = Raw.Find(Key);
		return Found ? *Found : Default;
	}

	FString GetRawStringOrFallback(const TMap<FString, FString>& Raw,
	                               const FString& Key,
	                               const FString& Default)
	{
		const FString* Found = Raw.Find(Key);
		return (Found && !Found->IsEmpty()) ? *Found : Default;
	}

	bool GetRawBoolOrDefault(const TMap<FString, FString>& Raw,
	                         const FString& Key,
	                         bool Default)
	{
		const FString* Found = Raw.Find(Key);
		if (!Found || Found->IsEmpty())
			return Default;
		const FString Trimmed = Found->TrimStartAndEnd();
		if (Trimmed.Equals(TEXT("True"),  ESearchCase::IgnoreCase) || Trimmed == TEXT("1"))
			return true;
		if (Trimmed.Equals(TEXT("False"), ESearchCase::IgnoreCase) || Trimmed == TEXT("0"))
			return false;
		return Default;
	}

	float GetRawFloatOrDefault(const TMap<FString, FString>& Raw,
	                           const FString& Key,
	                           float Default)
	{
		const FString* Found = Raw.Find(Key);
		if (!Found || Found->IsEmpty()) return Default;
		const float Result = FCString::Atof(**Found);
		return FMath::IsFinite(Result) ? Result : Default;
	}

	int32 GetRawIntOrDefault(const TMap<FString, FString>& Raw,
	                         const FString& Key,
	                         int32 Default)
	{
		const FString* Found = Raw.Find(Key);
		if (!Found || Found->IsEmpty()) return Default;
		int32 Parsed = 0;
		if (!TryParseNonNegativeInt32(*Found, Parsed))
		{
			UE_LOG(LogDiscordBridge, Warning,
				TEXT("DiscordBridgeConfig: raw key '%s' = '%s' is not numeric, using default %d"),
				*Key, **Found, Default);
			return Default;
		}
		return Parsed;
	}

	// Parses all values for a given key from a raw INI file content string.
	// Accepts both "Key=value" (single value) and "+Key=value" (array-entry)
	// notation.  Values are returned in document order; empty values are skipped.
	// This mirrors the raw-parser style already used for scalar fields so that
	// array fields survive the same %property% expansion pitfall (see comment
	// above ParseRawIniSection).
	TArray<FString> ParseRawIniArray(const FString& RawContent,
	                                 const FString& Section,
	                                 const FString& Key)
	{
		TArray<FString> Result;
		const FString SectionHeader = FString(TEXT("[")) + Section + TEXT("]");
		const FString PlainPrefix   = Key + TEXT("=");
		const FString PlusPrefix    = TEXT("+") + Key + TEXT("=");

		bool  bInSection = false;
		int32 Pos        = 0;

		while (Pos < RawContent.Len())
		{
			int32      LineEnd  = RawContent.Find(
				TEXT("\n"), ESearchCase::CaseSensitive, ESearchDir::FromStart, Pos);
			const bool bLastLine = (LineEnd == INDEX_NONE);
			if (bLastLine)
				LineEnd = RawContent.Len();

			FString Line = RawContent.Mid(Pos, LineEnd - Pos);
			if (!Line.IsEmpty() && Line[Line.Len() - 1] == TEXT('\r'))
				Line.RemoveAt(Line.Len() - 1, 1, /*bAllowShrinking=*/false);

			Pos = bLastLine ? RawContent.Len() : (LineEnd + 1);

			const FString Trimmed = Line.TrimStart();
			if (Trimmed.IsEmpty() ||
			    Trimmed.StartsWith(TEXT(";")) ||
			    Trimmed.StartsWith(TEXT("#")))
				continue;

			if (Trimmed.StartsWith(TEXT("[")))
			{
				bInSection = (Trimmed.TrimEnd() == SectionHeader);
				continue;
			}

			if (!bInSection)
				continue;

			if (Trimmed.StartsWith(PlusPrefix))
			{
				const FString Val = Trimmed.Mid(PlusPrefix.Len());
				if (!Val.IsEmpty())
					Result.Add(Val);
			}
			else if (Trimmed.StartsWith(PlainPrefix))
			{
				const FString Val = Trimmed.Mid(PlainPrefix.Len());
				if (!Val.IsEmpty())
					Result.Add(Val);
			}
		}

		return Result;
	}
} // anonymous namespace

// ─────────────────────────────────────────────────────────────────────────────
// Config post-load helpers
// ─────────────────────────────────────────────────────────────────────────────

// Trims leading/trailing whitespace from every string field that may hold a
// Discord snowflake ID, URL, or credential, so accidental spaces in the INI
// file do not silently break feature guards or HTTP requests.
static void TrimConfigStringFields(FDiscordBridgeConfig& Config)
{
	Config.BotToken                 = Config.BotToken.TrimStartAndEnd();
	Config.ChannelId                = Config.ChannelId.TrimStartAndEnd();
	Config.StatusChannelId          = Config.StatusChannelId.TrimStartAndEnd();
	Config.PlayerEventsChannelId    = Config.PlayerEventsChannelId.TrimStartAndEnd();
	Config.PlayerJoinAdminChannelId = Config.PlayerJoinAdminChannelId.TrimStartAndEnd();
	Config.PlayersCommandChannelId  = Config.PlayersCommandChannelId.TrimStartAndEnd();
	Config.PhaseEventsChannelId     = Config.PhaseEventsChannelId.TrimStartAndEnd();
	Config.SchematicEventsChannelId = Config.SchematicEventsChannelId.TrimStartAndEnd();
	Config.BanEventsChannelId       = Config.BanEventsChannelId.TrimStartAndEnd();
	Config.AnnouncementChannelId    = Config.AnnouncementChannelId.TrimStartAndEnd();
	Config.ModeratorChannelId       = Config.ModeratorChannelId.TrimStartAndEnd();
	Config.ModerationLogChannelId   = Config.ModerationLogChannelId.TrimStartAndEnd();
	Config.BotInfoChannelId         = Config.BotInfoChannelId.TrimStartAndEnd();
	Config.FallbackWebhookUrl       = Config.FallbackWebhookUrl.TrimStartAndEnd();
	for (FScheduledAnnouncement& SA : Config.ScheduledAnnouncements)
		SA.ChannelId = SA.ChannelId.TrimStartAndEnd();
}

// Returns true when S is a plausible Discord snowflake ID:
// non-empty, all digits, 17–20 characters (covering IDs issued since 2015).
static bool IsValidDiscordSnowflake(const FString& S)
{
	return !S.IsEmpty() && S.IsNumeric() && S.Len() >= 17 && S.Len() <= 20;
}

// Logs actionable operator warnings for common configuration mistakes.
// Called once after all settings have been fully loaded / restored from backup.
static void ValidateConfigFields(const FDiscordBridgeConfig& Config)
{
	// Helper: warn when a non-empty ID field is not a valid snowflake.
	auto WarnBadSnowflake = [](const FString& Value, const TCHAR* Key)
	{
		if (!Value.IsEmpty() && !IsValidDiscordSnowflake(Value))
		{
			UE_LOG(LogDiscordBridge, Warning,
			       TEXT("DiscordBridgeConfig: '%s' = \"%s\" is not a valid Discord snowflake "
			            "(expected 17-20 digit numeric string). "
			            "Check DefaultDiscordBridge.ini."),
			       Key, *Value);
		}
	};

	// Channel IDs
	WarnBadSnowflake(Config.ChannelId,                TEXT("ChannelId"));
	WarnBadSnowflake(Config.StatusChannelId,          TEXT("StatusChannelId"));
	WarnBadSnowflake(Config.PlayerEventsChannelId,    TEXT("PlayerEventsChannelId"));
	WarnBadSnowflake(Config.PlayerJoinAdminChannelId, TEXT("PlayerJoinAdminChannelId"));
	WarnBadSnowflake(Config.PlayersCommandChannelId,  TEXT("PlayersCommandChannelId"));
	WarnBadSnowflake(Config.PhaseEventsChannelId,     TEXT("PhaseEventsChannelId"));
	WarnBadSnowflake(Config.SchematicEventsChannelId, TEXT("SchematicEventsChannelId"));
	WarnBadSnowflake(Config.BanEventsChannelId,       TEXT("BanEventsChannelId"));
	WarnBadSnowflake(Config.AnnouncementChannelId,    TEXT("AnnouncementChannelId"));
	WarnBadSnowflake(Config.ModeratorChannelId,       TEXT("ModeratorChannelId"));
	WarnBadSnowflake(Config.ModerationLogChannelId,   TEXT("ModerationLogChannelId"));
	WarnBadSnowflake(Config.BotInfoChannelId,         TEXT("BotInfoChannelId"));
	for (int32 i = 0; i < Config.ScheduledAnnouncements.Num(); ++i)
	{
		if (!Config.ScheduledAnnouncements[i].ChannelId.IsEmpty())
		{
			WarnBadSnowflake(Config.ScheduledAnnouncements[i].ChannelId,
			                 *FString::Printf(TEXT("ScheduledAnnouncements[%d].ChannelId"), i));
		}
	}

	// BotToken structure heuristic: a Discord bot token is always
	// base64_user_id.timestamp.hmac — at least 50 characters with two dots.
	if (!Config.BotToken.IsEmpty())
	{
		int32 DotCount = 0;
		for (int32 i = 0; i < Config.BotToken.Len(); ++i)
			if (Config.BotToken[i] == TEXT('.')) ++DotCount;
		if (Config.BotToken.Len() < 50 || DotCount < 2)
		{
			UE_LOG(LogDiscordBridge, Warning,
			       TEXT("DiscordBridgeConfig: BotToken does not look like a valid Discord bot token "
			            "(expected base64id.timestamp.hmac, at least 50 characters with two dots). "
			            "Verify you copied the Token (not the Client Secret) from "
			            "Bot -> Token in the Discord Developer Portal."));
		}
	}

	// Feature-disabled hints: alert when a feature appears configured but its
	// interval/threshold keeps it silently inactive.
	if (Config.bEnableJoinReactionVoting && Config.VoteWindowMinutes <= 0)
	{
		UE_LOG(LogDiscordBridge, Warning,
		       TEXT("DiscordBridgeConfig: EnableJoinReactionVoting=True but VoteWindowMinutes=%d. "
		            "Vote windows will be clamped to 1 second. "
		            "Set VoteWindowMinutes > 0 to control the voting period."),
		       Config.VoteWindowMinutes);
	}

	if (!Config.AnnouncementMessage.IsEmpty() && Config.AnnouncementIntervalMinutes <= 0)
	{
		UE_LOG(LogDiscordBridge, Warning,
		       TEXT("DiscordBridgeConfig: AnnouncementMessage is set but AnnouncementIntervalMinutes=%d. "
		            "The legacy scheduled announcement will not fire. "
		            "Set AnnouncementIntervalMinutes > 0, or use ScheduledAnnouncements array entries instead."),
		       Config.AnnouncementIntervalMinutes);
	}
}

// ─────────────────────────────────────────────────────────────────────────────
// FDiscordBridgeConfig
// ─────────────────────────────────────────────────────────────────────────────

FString FDiscordBridgeConfig::GetModConfigFilePath()
{
	// The primary config lives in the mod's own Config folder so it is the
	// first place a server operator would look.  On a deployed server:
	//   <ServerRoot>/FactoryGame/Mods/DiscordBridge/Config/DefaultDiscordBridge.ini
	// NOTE: Alpakit/SMM mod updates overwrite this file; the mod automatically
	// saves a backup to GetBackupConfigFilePath() so credentials survive upgrades.
	return FPaths::Combine(FPaths::ProjectDir(),
	                       TEXT("Mods"), TEXT("DiscordBridge"),
	                       TEXT("Config"), TEXT("DefaultDiscordBridge.ini"));
}

FString FDiscordBridgeConfig::GetBackupConfigFilePath()
{
	// Backup config in Saved/DiscordBridge/ – never touched by Alpakit mod updates.
	// Written automatically whenever the primary config has valid credentials.
	// On a deployed server:
	//   <ServerRoot>/FactoryGame/Saved/DiscordBridge/DiscordBridge.ini
	return FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("DiscordBridge"), TEXT("DiscordBridge.ini"));
}

FDiscordBridgeConfig FDiscordBridgeConfig::LoadOrCreate()
{
	FDiscordBridgeConfig Config;
	const FString ModFilePath    = GetModConfigFilePath();
	const FString BackupFilePath = GetBackupConfigFilePath();

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	// ── Step 0: proactively strip any UTF-8 BOM from the config files ───────
	// External tools (text editors, UE4 config hierarchy, etc.) may write a
	// UTF-8 BOM (EF BB BF) to the file, producing garbled characters (e.g.
	// "��[DiscordBridge]") when viewed.  Strip it before any further processing.
	if (PlatformFile.FileExists(*ModFilePath))
	{
		CleanDiscordConfigBOM(ModFilePath);
	}
	if (PlatformFile.FileExists(*BackupFilePath))
	{
		CleanDiscordConfigBOM(BackupFilePath);
	}

	// ── Step 1: load the primary config (mod folder) ─────────────────────────
	// [BACKUP-SYNC] When adding a new FDiscordBridgeConfig field, add a read
	// line here AND update Steps 2 (restore + PatchLine) and 3 (backup write).
	bool bLoadedFromMod = false;
	if (PlatformFile.FileExists(*ModFilePath))
	{
		FConfigFile ConfigFile;
		ConfigFile.Read(ModFilePath);
		FString ModFileRawContent;
		const bool bHasModFileRawContent = FFileHelper::LoadFileToString(ModFileRawContent, *ModFilePath);
		if (bHasModFileRawContent)
		{
			StripBOM(ModFileRawContent);
		}
		else
		{
			UE_LOG(LogDiscordBridge, Warning,
			       TEXT("DiscordBridge: Failed reading raw config '%s'; array-style fields may not load."),
			       *ModFilePath);
		}

		Config.BotToken             = GetIniStringOrDefault(ConfigFile, TEXT("BotToken"),             TEXT(""));
		Config.ChannelId            = GetIniStringOrDefault(ConfigFile, TEXT("ChannelId"),            TEXT(""));
		Config.ServerName           = GetIniStringOrDefault(ConfigFile, TEXT("ServerName"),           Config.ServerName);
		Config.GameToDiscordFormat  = GetIniStringOrFallback(ConfigFile, TEXT("GameToDiscordFormat"),  Config.GameToDiscordFormat);
		Config.DiscordToGameFormat  = GetIniStringOrFallback(ConfigFile, TEXT("DiscordToGameFormat"),  Config.DiscordToGameFormat);

		// Backward compatibility: if the old separate DiscordSenderFormat key is
		// present and the operator has not overridden DiscordToGameFormat to a value
		// that already mentions %Message%, synthesise a combined format so existing
		// configs continue to render as before.
		{
			FString OldSenderFmt;
			if (ConfigFile.GetString(ConfigSection, TEXT("DiscordSenderFormat"), OldSenderFmt) && !OldSenderFmt.IsEmpty())
			{
				// Only auto-combine when DiscordToGameFormat is still the default
				// (i.e. the operator has not explicitly customised it).
				if (Config.DiscordToGameFormat == TEXT("[Discord] %Username%: %Message%"))
				{
					Config.DiscordToGameFormat = OldSenderFmt + TEXT(": %Message%");
				}
				UE_LOG(LogDiscordBridge, Warning,
				       TEXT("DiscordBridge: 'DiscordSenderFormat' is deprecated. "
				            "Use 'DiscordToGameFormat' to control the full in-game line. "
				            "Effective format is now: \"%s\""), *Config.DiscordToGameFormat);
			}
		}
		Config.bIgnoreBotMessages   = GetIniBoolOrDefault  (ConfigFile, TEXT("IgnoreBotMessages"),
		                              GetIniBoolOrDefault  (ConfigFile, TEXT("bIgnoreBotMessages"),   Config.bIgnoreBotMessages));
		Config.bServerStatusMessagesEnabled = GetIniBoolOrDefault(ConfigFile, TEXT("ServerStatusMessagesEnabled"), Config.bServerStatusMessagesEnabled);
		Config.StatusChannelId      = GetIniStringOrDefault(ConfigFile, TEXT("StatusChannelId"),      Config.StatusChannelId);
		Config.ServerOnlineMessage  = GetIniStringOrDefault(ConfigFile, TEXT("ServerOnlineMessage"),  Config.ServerOnlineMessage);
		Config.ServerOfflineMessage = GetIniStringOrDefault(ConfigFile, TEXT("ServerOfflineMessage"), Config.ServerOfflineMessage);
		Config.bShowPlayerCountInPresence      = GetIniBoolOrDefault  (ConfigFile, TEXT("ShowPlayerCountInPresence"),
		                                         GetIniBoolOrDefault  (ConfigFile, TEXT("bShowPlayerCountInPresence"),      Config.bShowPlayerCountInPresence));
		Config.PlayerCountPresenceFormat       = GetIniStringOrFallback(ConfigFile, TEXT("PlayerCountPresenceFormat"),       Config.PlayerCountPresenceFormat);
		Config.PlayerCountUpdateIntervalSeconds = GetIniFloatOrDefault (ConfigFile, TEXT("PlayerCountUpdateIntervalSeconds"), Config.PlayerCountUpdateIntervalSeconds);
		Config.PlayerCountActivityType         = GetIniIntOrDefault   (ConfigFile, TEXT("PlayerCountActivityType"),         Config.PlayerCountActivityType);

		// Whitelist settings have moved to a separate config file
		// (DefaultWhitelist.ini) loaded by FWhitelistConfig::Load().

		// Player event notification settings
		Config.bPlayerEventsEnabled   = GetIniBoolOrDefault  (ConfigFile, TEXT("PlayerEventsEnabled"),   Config.bPlayerEventsEnabled);
		Config.PlayerEventsChannelId  = GetIniStringOrDefault(ConfigFile, TEXT("PlayerEventsChannelId"),  Config.PlayerEventsChannelId);
		Config.PlayerJoinMessage      = GetIniStringOrDefault(ConfigFile, TEXT("PlayerJoinMessage"),      Config.PlayerJoinMessage);
		Config.PlayerJoinAdminChannelId = GetIniStringOrDefault(ConfigFile, TEXT("PlayerJoinAdminChannelId"), Config.PlayerJoinAdminChannelId);
		Config.PlayerJoinAdminMessage   = GetIniStringOrDefault(ConfigFile, TEXT("PlayerJoinAdminMessage"),   Config.PlayerJoinAdminMessage);
		Config.PlayerLeaveMessage     = GetIniStringOrDefault(ConfigFile, TEXT("PlayerLeaveMessage"),     Config.PlayerLeaveMessage);
		Config.PlayerTimeoutMessage   = GetIniStringOrDefault(ConfigFile, TEXT("PlayerTimeoutMessage"),   Config.PlayerTimeoutMessage);
		Config.bUseEmbedsForPlayerEvents = GetIniBoolOrDefault(ConfigFile, TEXT("UseEmbedsForPlayerEvents"), Config.bUseEmbedsForPlayerEvents);

		// Chat relay filter – use raw file parsing to support +Key= array syntax.
		{
			if (bHasModFileRawContent)
			{
				Config.ChatRelayBlocklist = ParseRawIniArray(ModFileRawContent, TEXT("DiscordBridge"), TEXT("ChatRelayBlocklist"));

				// Parse ChatRelayBlocklistReplacements array entries.
				// Format per entry: Pattern="word",Replacement="***"
				TArray<FString> RawRepl = ParseRawIniArray(ModFileRawContent, TEXT("DiscordBridge"), TEXT("ChatRelayBlocklistReplacements"));
				for (const FString& Line : RawRepl)
				{
					// Strip outer parentheses if present.
					FString Cleaned = Line.TrimStartAndEnd();
					if (Cleaned.StartsWith(TEXT("("))) Cleaned = Cleaned.Mid(1);
					if (Cleaned.EndsWith(TEXT(")")))   Cleaned = Cleaned.LeftChop(1);

					FString PatStr, ReplStr;
					// Try to extract Pattern="…" and Replacement="…"
					// Escape-aware extraction: honours \" sequences written by the config writer.
					auto ExtractQuoted = [&](const FString& Key, FString& Out) -> bool
					{
						const FString Search = Key + TEXT("=\"");
						const int32   Idx    = Cleaned.Find(Search, ESearchCase::IgnoreCase);
						if (Idx == INDEX_NONE) return false;
						const int32 Start = Idx + Search.Len();
						FString Value;
						int32 i = Start;
						bool bClosed = false;
						while (i < Cleaned.Len())
						{
							const TCHAR C = Cleaned[i];
							if (C == TEXT('\\') && i + 1 < Cleaned.Len() && Cleaned[i + 1] == TEXT('"'))
							{ Value.AppendChar(TEXT('"')); i += 2; }
							else if (C == TEXT('"'))
							{ bClosed = true; break; }
							else
							{ Value.AppendChar(C); ++i; }
						}
						if (!bClosed) return false;
						Out = Value;
						return true;
					};

					if (ExtractQuoted(TEXT("Pattern"),     PatStr) &&
					    ExtractQuoted(TEXT("Replacement"), ReplStr))
					{
						FChatRelayReplacement R;
						R.Pattern     = PatStr;
						R.Replacement = ReplStr;
						Config.ChatRelayBlocklistReplacements.Add(R);
					}
				}
			}
		}

		// Bot commands
		Config.PlayersCommandChannelId = GetIniStringOrDefault (ConfigFile, TEXT("PlayersCommandChannelId"), Config.PlayersCommandChannelId);
		Config.DiscordInviteUrl        = GetIniStringOrDefault (ConfigFile, TEXT("DiscordInviteUrl"),        Config.DiscordInviteUrl);

		// New commands

		// Per-event channel routing
		Config.PhaseEventsChannelId    = GetIniStringOrDefault(ConfigFile, TEXT("PhaseEventsChannelId"),    Config.PhaseEventsChannelId);
		Config.SchematicEventsChannelId = GetIniStringOrDefault(ConfigFile, TEXT("SchematicEventsChannelId"), Config.SchematicEventsChannelId);
		Config.BanEventsChannelId       = GetIniStringOrDefault(ConfigFile, TEXT("BanEventsChannelId"),       Config.BanEventsChannelId);

		// Reaction voting
		Config.bEnableJoinReactionVoting = GetIniBoolOrDefault(ConfigFile, TEXT("EnableJoinReactionVoting"), Config.bEnableJoinReactionVoting);
		Config.VoteKickThreshold         = GetIniIntOrDefault (ConfigFile, TEXT("VoteKickThreshold"),         Config.VoteKickThreshold);
		Config.VoteWindowMinutes         = GetIniIntOrDefault (ConfigFile, TEXT("VoteWindowMinutes"),         Config.VoteWindowMinutes);

		// AFK kick
		Config.AfkKickMinutes = GetIniIntOrDefault   (ConfigFile, TEXT("AfkKickMinutes"), Config.AfkKickMinutes);
		Config.AfkKickReason  = GetIniStringOrDefault(ConfigFile, TEXT("AfkKickReason"),  Config.AfkKickReason);

		// Scheduled announcements
		Config.AnnouncementIntervalMinutes = GetIniIntOrDefault   (ConfigFile, TEXT("AnnouncementIntervalMinutes"), Config.AnnouncementIntervalMinutes);
		Config.AnnouncementMessage         = GetIniStringOrDefault(ConfigFile, TEXT("AnnouncementMessage"),         Config.AnnouncementMessage);
		Config.AnnouncementChannelId       = GetIniStringOrDefault(ConfigFile, TEXT("AnnouncementChannelId"),       Config.AnnouncementChannelId);

		// Embed mode flags
		Config.bUseEmbedsForPhaseEvents     = GetIniBoolOrDefault(ConfigFile, TEXT("UseEmbedsForPhaseEvents"),     Config.bUseEmbedsForPhaseEvents);
		Config.bUseEmbedsForSchematicEvents = GetIniBoolOrDefault(ConfigFile, TEXT("UseEmbedsForSchematicEvents"), Config.bUseEmbedsForSchematicEvents);

		// Webhook fallback
		Config.FallbackWebhookUrl = GetIniStringOrDefault(ConfigFile, TEXT("FallbackWebhookUrl"), Config.FallbackWebhookUrl);

		// Slash commands
		Config.bEnableSlashCommands = GetIniBoolOrDefault(ConfigFile, TEXT("EnableSlashCommands"), Config.bEnableSlashCommands);

		// Mute notifications
		Config.bNotifyMuteEvents  = GetIniBoolOrDefault  (ConfigFile, TEXT("NotifyMuteEvents"),  Config.bNotifyMuteEvents);
		Config.ModeratorChannelId = GetIniStringOrDefault(ConfigFile, TEXT("ModeratorChannelId"), Config.ModeratorChannelId);

		// Moderation log channel
		Config.ModerationLogChannelId = GetIniStringOrDefault(ConfigFile, TEXT("ModerationLogChannelId"), Config.ModerationLogChannelId);

		// Bot info / help channel
		Config.BotInfoChannelId = GetIniStringOrDefault(ConfigFile, TEXT("BotInfoChannelId"), Config.BotInfoChannelId);

		// On-join DM welcome message
		Config.WelcomeMessageDM = GetIniStringOrDefault(ConfigFile, TEXT("WelcomeMessageDM"), Config.WelcomeMessageDM);

		// On-join in-game hint message (sent privately to the joining player)
		Config.JoinHintMessage = GetIniStringOrDefault(ConfigFile, TEXT("JoinHintMessage"), Config.JoinHintMessage);

		// On-join broadcast message (sent to all players in game chat)
		Config.bInGameJoinBroadcastEnabled = GetIniBoolOrDefault(ConfigFile, TEXT("InGameJoinBroadcastEnabled"), Config.bInGameJoinBroadcastEnabled);
		Config.InGameJoinBroadcast = GetIniStringOrDefault(ConfigFile, TEXT("InGameJoinBroadcast"), Config.InGameJoinBroadcast);

		// DiscordRoleLabels array (used for %Role% placeholder in DiscordToGameFormat)
		{
			if (bHasModFileRawContent)
			{
				Config.DiscordRoleLabels = ParseRawIniArray(ModFileRawContent, TEXT("DiscordBridge"), TEXT("DiscordRoleLabels"));
			}
		}

		// Multi-slot scheduled announcements (array field)
		{
			const TArray<FString> SALines = bHasModFileRawContent
				? ParseRawIniArray(ModFileRawContent, TEXT("DiscordBridge"), TEXT("ScheduledAnnouncements"))
				: TArray<FString>{};
			for (const FString& Line : SALines)
			{
				FString Cleaned = Line.TrimStartAndEnd();
				if (Cleaned.StartsWith(TEXT("("))) Cleaned = Cleaned.Mid(1);
				if (Cleaned.EndsWith(TEXT(")")))   Cleaned = Cleaned.LeftChop(1);

				FScheduledAnnouncement SA;
				// Extract IntervalMinutes
				{
					const FString Search = TEXT("IntervalMinutes=");
					const int32 Idx = Cleaned.Find(Search, ESearchCase::IgnoreCase);
					if (Idx != INDEX_NONE)
					{
						const FString Rest = Cleaned.Mid(Idx + Search.Len());
						int32 Comma = INDEX_NONE;
						if (Rest.FindChar(TEXT(','), Comma))
						{
							// Value is followed by more fields — read up to the comma.
							const FString Left = Rest.Left(Comma).TrimStartAndEnd();
							int32 ParsedInterval = 0;
							if (TryParseNonNegativeInt32(Left, ParsedInterval))
								SA.IntervalMinutes = ParsedInterval;
						}
						else
						{
							// Value is the only / last field — use the whole remainder.
							const FString Trimmed = Rest.TrimStartAndEnd();
							int32 ParsedInterval = 0;
							if (TryParseNonNegativeInt32(Trimmed, ParsedInterval))
								SA.IntervalMinutes = ParsedInterval;
						}
					}
				}
				// Extract Message — honours \" escape sequences written by the backup writer.
				{
					const FString Search = TEXT("Message=\"");
					const int32 Idx = Cleaned.Find(Search, ESearchCase::IgnoreCase);
					if (Idx != INDEX_NONE)
					{
						const int32 Start = Idx + Search.Len();
						FString Value;
						int32 i = Start;
						bool bClosed = false;
						while (i < Cleaned.Len())
						{
							const TCHAR C = Cleaned[i];
							if (C == TEXT('\\') && i + 1 < Cleaned.Len() && Cleaned[i + 1] == TEXT('"'))
							{ Value.AppendChar(TEXT('"')); i += 2; }
							else if (C == TEXT('"'))
							{ bClosed = true; break; }
							else
							{ Value.AppendChar(C); ++i; }
						}
						if (bClosed)
							SA.Message = Value;
						else
							UE_LOG(LogDiscordBridge, Warning,
								TEXT("DiscordBridgeConfig: malformed ScheduledAnnouncements entry — "
								     "could not extract Message value"));
					}
				}
				// Extract ChannelId (Discord snowflake — digits only; no escaping needed).
				{
					const FString Search = TEXT("ChannelId=\"");
					const int32 Idx = Cleaned.Find(Search, ESearchCase::IgnoreCase);
					if (Idx != INDEX_NONE)
					{
						const int32 Start = Idx + Search.Len();
						const int32 End   = Cleaned.Find(TEXT("\""), ESearchCase::CaseSensitive, ESearchDir::FromStart, Start);
						if (End != INDEX_NONE && End > Start)
							SA.ChannelId = Cleaned.Mid(Start, End - Start);
						else
							UE_LOG(LogDiscordBridge, Warning,
								TEXT("DiscordBridgeConfig: malformed ScheduledAnnouncements entry — "
								     "could not extract ChannelId value"));
					}
				}
				if (SA.IntervalMinutes > 0 && !SA.Message.IsEmpty())
					Config.ScheduledAnnouncements.Add(SA);
			}
		}

		// Trim leading/trailing whitespace from all ID / URL fields to prevent
		// subtle mismatches when operators accidentally include spaces.
		TrimConfigStringFields(Config);

		bLoadedFromMod = true;
		UE_LOG(LogDiscordBridge, Log, TEXT("DiscordBridge: Loaded config from %s"), *ModFilePath);

		// When BotToken is empty the file may not have been configured yet.
		// Only rewrite with the annotated template when the file has no '#'
		// comment lines, which indicates Alpakit stripped them during packaging
		// and the operator cannot see the setting descriptions.  If the file
		// already contains '#' characters it is either a previously-written
		// annotated template or a user-configured file; in that case do NOT
		// overwrite it so the operator's other settings (server name, online/
		// offline messages, format strings, etc.) are preserved even when
		// BotToken has not been filled in yet.
		if (Config.BotToken.IsEmpty())
		{
			if (!bHasModFileRawContent)
			{
				UE_LOG(LogDiscordBridge, Warning,
				       TEXT("DiscordBridge: Could not inspect '%s' for comments because raw read failed; skipping template rewrite check."),
				       *ModFilePath);
			}
			else if (!ModFileRawContent.Contains(TEXT("#")))
			{
				UE_LOG(LogDiscordBridge, Log,
				       TEXT("DiscordBridge: Config at '%s' has no BotToken and no comment "
				            "lines (Alpakit-stripped or comment-free) – rewriting with "
				            "annotated template so operators can see setting descriptions."),
				       *ModFilePath);
				bLoadedFromMod = false; // fall through to the DefaultContent write below
			}
			else
			{
				UE_LOG(LogDiscordBridge, Log,
				       TEXT("DiscordBridge: Config at '%s' has no BotToken – "
				            "Discord bridge will not start until BotToken is configured."),
				       *ModFilePath);
				// bLoadedFromMod stays true; all other settings loaded above are used.
			}
		}
		else
		{
			// Second pass: detect individual settings that were added in later updates
			// but may be absent from older configs.
			// Only appends the specific missing keys so no existing custom values are lost.
			{
				FString TmpVal;
				FString AppendContent2;

				if (!ConfigFile.GetString(ConfigSection, TEXT("ServerStatusMessagesEnabled"), TmpVal))
				{
					AppendContent2 +=
						TEXT("\n")
						TEXT("# ServerStatusMessagesEnabled (added by mod update) -------------------\n")
						TEXT("# Master on/off switch for server status messages (online/offline).\n")
						TEXT("# Set to False to disable all online/offline notifications.\n")
						TEXT("# Default: True.\n")
						TEXT("ServerStatusMessagesEnabled=True\n");
				}

				if (!ConfigFile.GetString(ConfigSection, TEXT("StatusChannelId"), TmpVal))
				{
					AppendContent2 +=
						TEXT("\n")
						TEXT("# StatusChannelId (added by mod update) --------------------------------\n")
						TEXT("# Snowflake ID of a dedicated Discord channel for server status messages.\n")
						TEXT("# Leave empty to post status messages to the main bridged channel (ChannelId).\n")
						TEXT("StatusChannelId=\n");
				}

				if (!ConfigFile.GetString(ConfigSection, TEXT("PlayerEventsEnabled"), TmpVal))
				{
					AppendContent2 +=
						TEXT("\n")
						TEXT("# -- PLAYER NOTIFICATIONS (added by mod update) --------------------------\n")
						TEXT("# When True, posts a Discord message whenever a player joins, leaves,\n")
						TEXT("# or times out from the server.\n")
						TEXT("# Default: False (disabled).\n")
						TEXT("PlayerEventsEnabled=False\n")
						TEXT("#\n")
						TEXT("# Snowflake ID of the channel where player notifications are posted.\n")
						TEXT("# Leave empty to use the main bridged channel (ChannelId).\n")
						TEXT("PlayerEventsChannelId=\n")
						TEXT("#\n")
						TEXT("# Message posted when a player joins (public channel). Leave empty to disable.\n")
						TEXT("# Placeholder: %PlayerName%\n")
						TEXT("PlayerJoinMessage=\n")
						TEXT("#\n")
						TEXT("# Snowflake ID of a PRIVATE admin-only channel for sensitive join details.\n")
						TEXT("# Leave empty to disable admin-info notifications.\n")
						TEXT("PlayerJoinAdminChannelId=\n")
						TEXT("#\n")
						TEXT("# Message posted to the admin channel when a player joins.\n")
						TEXT("# Placeholders: %PlayerName%, %EOSProductUserId%, %IpAddress%\n")
						TEXT("PlayerJoinAdminMessage=\n")
						TEXT("#\n")
						TEXT("# Message posted when a player leaves cleanly. Leave empty to disable.\n")
						TEXT("# Also used as fallback when PlayerTimeoutMessage is empty.\n")
						TEXT("# Placeholder: %PlayerName%\n")
						TEXT("PlayerLeaveMessage=\n")
						TEXT("#\n")
						TEXT("# Message posted when a player times out. Leave empty to use PlayerLeaveMessage.\n")
						TEXT("# Placeholder: %PlayerName%\n")
						TEXT("PlayerTimeoutMessage=\n");
				}

				// New fields added in the chat-filter / bot-commands / embed update.
				if (!ConfigFile.GetString(ConfigSection, TEXT("UseEmbedsForPlayerEvents"), TmpVal))
				{
					AppendContent2 +=
						TEXT("\n")
						TEXT("# UseEmbedsForPlayerEvents (added by mod update) ----------------------\n")
						TEXT("# When True, player join/leave/timeout events are sent as rich Discord\n")
						TEXT("# embeds (colour-coded) instead of plain text. Default: False.\n")
						TEXT("UseEmbedsForPlayerEvents=False\n");
				}

				{
					// ChatRelayBlocklist is an array field (multi-line +Key=value).
					// Check for its presence in the raw file rather than via FConfigFile.
					if (bHasModFileRawContent && !ModFileRawContent.Contains(TEXT("ChatRelayBlocklist")))
					{
						AppendContent2 +=
							TEXT("\n")
							TEXT("# -- CHAT RELAY FILTER (added by mod update) --------------------------\n")
							TEXT("# Block in-game chat keywords from being relayed to Discord.\n")
							TEXT("# Add one keyword per line using: +ChatRelayBlocklist=keyword\n")
							TEXT("# Matching is case-insensitive. Leave empty to relay all messages.\n")
							TEXT("# Example:\n")
							TEXT("# +ChatRelayBlocklist=spam\n");
					}
					else if (!bHasModFileRawContent)
					{
						UE_LOG(LogDiscordBridge, Warning,
						       TEXT("DiscordBridge: Could not inspect raw config for ChatRelayBlocklist; skipping auto-append detection."));
					}
				}

				if (!ConfigFile.GetString(ConfigSection, TEXT("PlayersCommandChannelId"), TmpVal))
				{
					AppendContent2 +=
						TEXT("\n")
						TEXT("# -- BOT COMMANDS (added by mod update) --------------------------------\n")
						TEXT("# Channel for /players responses. Leave empty to use ChannelId.\n")
						TEXT("PlayersCommandChannelId=\n")
						TEXT("#\n")
						TEXT("# Discord invite link shown to players who type /discord in-game.\n")
						TEXT("# Leave empty to disable the /discord in-game command.\n")
						TEXT("DiscordInviteUrl=\n");
				}

				if (!ConfigFile.GetString(ConfigSection, TEXT("JoinHintMessage"), TmpVal))
				{
					AppendContent2 +=
						TEXT("\n")
						TEXT("# -- ON-JOIN IN-GAME HINT (added by mod update) -----------------------\n")
						TEXT("# Message sent privately in-game to each player when they join.\n")
						TEXT("# Advertise available commands such as /discord, /verify, /commands.\n")
						TEXT("# Leave empty to disable (default). Placeholder: %PlayerName%\n")
						TEXT("JoinHintMessage=\n");
				}

				if (!ConfigFile.GetString(ConfigSection, TEXT("InGameJoinBroadcast"), TmpVal))
				{
					AppendContent2 +=
						TEXT("\n")
						TEXT("# -- ON-JOIN IN-GAME BROADCAST (added by mod update) ------------------\n")
						TEXT("# Set to False to disable without clearing the message text.\n")
						TEXT("InGameJoinBroadcastEnabled=True\n")
						TEXT("# Message broadcast to ALL players in game chat when someone joins.\n")
						TEXT("# Works with or without the whitelist. Leave empty to disable (default).\n")
						TEXT("# Placeholder: %PlayerName%\n")
						TEXT("InGameJoinBroadcast=\n");
				}

				if (!AppendContent2.IsEmpty())
				{
					UE_LOG(LogDiscordBridge, Log,
					       TEXT("DiscordBridge: Config at '%s' is missing individual settings "
					            "(older version detected). Appending missing entries."),
					       *ModFilePath);

					FString ExistingContent2;
					if (!FFileHelper::LoadFileToString(ExistingContent2, *ModFilePath))
					{
						UE_LOG(LogDiscordBridge, Warning,
						       TEXT("DiscordBridge: Could not read '%s' to append missing settings — aborting to avoid overwrite."),
						       *ModFilePath);
						return Config;
					}
					StripBOM(ExistingContent2);

					if (FFileHelper::SaveStringToFile(ExistingContent2 + AppendContent2, *ModFilePath,
					    FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
					{
						UE_LOG(LogDiscordBridge, Log,
						       TEXT("DiscordBridge: Updated '%s' with missing settings. "
						            "Review and configure them, then restart the server."),
						       *ModFilePath);
					}
					else
					{
						UE_LOG(LogDiscordBridge, Warning,
						       TEXT("DiscordBridge: Could not update '%s' with missing settings."),
						       *ModFilePath);
					}
				}
			}
		}
	}

	if (!bLoadedFromMod)
	{
		if (!PlatformFile.FileExists(*ModFilePath))
		{
			// Primary config missing – create it with defaults so the operator has
			// a ready-made file to fill in.
			UE_LOG(LogDiscordBridge, Log,
			       TEXT("DiscordBridge: Config file not found at '%s'. "
			            "Creating it with defaults."), *ModFilePath);
		}

				const FString DefaultContent =
			TEXT("[DiscordBridge]\n")
			TEXT("# DiscordBridge - Primary Configuration File\n")
			TEXT("# ==========================================\n")
			TEXT("# 1. Set BotToken and ChannelId below.\n")
			TEXT("# 2. Restart the server. The bridge starts automatically.\n")
			TEXT("# Note: this file is NOT overwritten by mod updates, so your settings persist\n")
			TEXT("#   across version upgrades. A backup is still written automatically to\n")
			TEXT("#   <ServerRoot>/FactoryGame/Saved/DiscordBridge/DiscordBridge.ini on every server start.\n")
			TEXT("# Bot setup: Discord Developer Portal -> your app -> Bot\n")
			TEXT("#   - Enable Server Members and Message Content intents.\n")
			TEXT("#   - Invite the bot with Send Messages + Read Message History permissions.\n")
			TEXT("#   - Enable Developer Mode in Discord, right-click the channel, Copy Channel ID.\n")
			TEXT("\n")
			TEXT("# -- CONNECTION ---------------------------------------------------------------\n")
			TEXT("BotToken=\n")
			TEXT("# Discord bot token. Get from Developer Portal -> your app -> Bot -> Reset Token.\n")
			TEXT("# Treat like a password; never share it. Required — bridge won't start if empty.\n")
			TEXT("\n")
			TEXT("ChannelId=\n")
			TEXT("# Snowflake ID of the Discord text channel to bridge with in-game chat.\n")
			TEXT("# Developer Mode -> right-click the channel -> Copy Channel ID.\n")
			TEXT("\n")
			TEXT("ServerName=\n")
			TEXT("# Display name for this server. Used as %ServerName% placeholder.\n")
			TEXT("\n")
			TEXT("# -- CHAT CUSTOMISATION -------------------------------------------------------\n")
			TEXT("GameToDiscordFormat=\n")
			TEXT("# Format for game->Discord. Placeholders: %ServerName%, %PlayerName%, %Message%\n")
			TEXT("# Default: **%PlayerName%**: %Message%\n")
			TEXT("\n")
			TEXT("DiscordToGameFormat=\n")
			TEXT("# Format for Discord->game. Placeholders: %Username%, %PlayerName%, %Message%, %Role%\n")
			TEXT("# Default: [Discord] %Username%: %Message%\n")
			TEXT("\n")
			TEXT("# -- BEHAVIOUR ----------------------------------------------------------------\n")
			TEXT("IgnoreBotMessages=\n")
			TEXT("# When True, bot messages are ignored (prevents echo loops). Default: True.\n")
			TEXT("\n")
			TEXT("# -- SERVER STATUS MESSAGES ---------------------------------------------------\n")
			TEXT("ServerStatusMessagesEnabled=True\n")
			TEXT("# Master on/off switch for server status messages. Default: True.\n")
			TEXT("\n")
			TEXT("StatusChannelId=\n")
			TEXT("# Dedicated channel for status messages. Leave empty to use ChannelId.\n")
			TEXT("\n")
			TEXT("ServerOnlineMessage=:green_circle: Server is now **online**!\n")
			TEXT("# Message posted when the server starts. Leave empty to disable.\n")
			TEXT("\n")
			TEXT("ServerOfflineMessage=:red_circle: Server is now **offline**.\n")
			TEXT("# Message posted when the server stops. Leave empty to disable.\n")
			TEXT("\n")
			TEXT("# -- PLAYER COUNT PRESENCE ----------------------------------------------------\n")
			TEXT("ShowPlayerCountInPresence=\n")
			TEXT("# When True, the bot's Discord status shows the current player count. Default: True.\n")
			TEXT("\n")
			TEXT("PlayerCountPresenceFormat=\n")
			TEXT("# Text for the bot's presence. Placeholders: %PlayerCount%, %ServerName%\n")
			TEXT("# Default: Satisfactory with %PlayerCount% players\n")
			TEXT("\n")
			TEXT("PlayerCountUpdateIntervalSeconds=\n")
			TEXT("# How often (seconds) to refresh the player count. Minimum 15. Default: 60.\n")
			TEXT("\n")
			TEXT("PlayerCountActivityType=\n")
			TEXT("# Activity type: 0=Playing, 2=Listening to, 3=Watching, 5=Competing in. Default: 0.\n")
			TEXT("\n")
			TEXT("# -- WHITELIST ----------------------------------------------------------------\n")
			TEXT("# Whitelist settings moved to: Mods/DiscordBridge/Config/DefaultWhitelist.ini\n")
			TEXT("\n")
			TEXT("# -- PLAYER NOTIFICATIONS -----------------------------------------------------\n")
			TEXT("PlayerEventsEnabled=False\n")
			TEXT("# When True, posts Discord messages on player join/leave/timeout. Default: False.\n")
			TEXT("\n")
			TEXT("PlayerEventsChannelId=\n")
			TEXT("# Channel for player event notifications. Leave empty to use ChannelId.\n")
			TEXT("\n")
			TEXT("PlayerJoinMessage=\n")
			TEXT("# Message posted when a player joins. Placeholder: %PlayerName%.\n")
			TEXT("# Default: :green_circle: **%PlayerName%** joined the server.\n")
			TEXT("\n")
			TEXT("PlayerJoinAdminChannelId=\n")
			TEXT("# PRIVATE admin-only channel for sensitive join details (EOS PUID, IP).\n")
			TEXT("# Leave empty to disable admin-info notifications.\n")
			TEXT("\n")
			TEXT("PlayerJoinAdminMessage=\n")
			TEXT("# Message for the admin channel. Placeholders: %PlayerName%, %EOSProductUserId%, %IpAddress%\n")
			TEXT("# Default: :shield: **%PlayerName%** joined | EOS: `%EOSProductUserId%` | IP: `%IpAddress%`\n")
			TEXT("\n")
			TEXT("PlayerLeaveMessage=\n")
			TEXT("# Message posted when a player leaves. Placeholder: %PlayerName%. Leave empty to disable.\n")
			TEXT("# Default: :red_circle: **%PlayerName%** left the server.\n")
			TEXT("\n")
			TEXT("PlayerTimeoutMessage=\n")
			TEXT("# Message for timeouts. Leave empty to use PlayerLeaveMessage. Placeholder: %PlayerName%.\n")
			TEXT("# Default: :yellow_circle: **%PlayerName%** timed out.\n")
			TEXT("\n")
			TEXT("UseEmbedsForPlayerEvents=False\n")
			TEXT("# When True, join/leave/timeout events use colour-coded Discord embeds. Default: False.\n")
			TEXT("\n")
			TEXT("EnableJoinReactionVoting=False\n")
			TEXT("# When True, adds thumbs-up/down reactions to player-join messages. Default: False.\n")
			TEXT("\n")
			TEXT("VoteKickThreshold=0\n")
			TEXT("# Thumbs-down reactions needed within VoteWindowMinutes to auto-kick. 0 = disabled.\n")
			TEXT("\n")
			TEXT("VoteWindowMinutes=5\n")
			TEXT("# Minutes to watch for thumbs-down reactions before the vote expires. Default: 5.\n")
			TEXT("\n")
			TEXT("# -- GAME EVENT CHANNELS ------------------------------------------------------\n")
			TEXT("PhaseEventsChannelId=\n")
			TEXT("# Channel for game-phase change announcements. Leave empty to use ChannelId.\n")
			TEXT("\n")
			TEXT("UseEmbedsForPhaseEvents=True\n")
			TEXT("# When True, phase events use rich Discord embeds. Default: True.\n")
			TEXT("\n")
			TEXT("SchematicEventsChannelId=\n")
			TEXT("# Channel for schematic/research unlock announcements. Leave empty to use PhaseEventsChannelId.\n")
			TEXT("\n")
			TEXT("UseEmbedsForSchematicEvents=True\n")
			TEXT("# When True, schematic events use rich Discord embeds. Default: True.\n")
			TEXT("\n")
			TEXT("BanEventsChannelId=\n")
			TEXT("# Channel for ban notifications. Leave empty to use BanSystem webhook.\n")
			TEXT("\n")
			TEXT("# -- CHAT RELAY FILTER --------------------------------------------------------\n")
			TEXT("# Block in-game chat keywords from Discord relay: +ChatRelayBlocklist=keyword\n")
			TEXT("# Find-and-replace: +ChatRelayBlocklistReplacements=(Pattern=\"badword\",Replacement=\"***\")\n")
			TEXT("\n")
			TEXT("# -- BOT COMMANDS -------------------------------------------------------------\n")
			TEXT("PlayersCommandChannelId=\n")
			TEXT("# Channel for /players responses. Leave empty to use ChannelId.\n")
			TEXT("\n")
			TEXT("DiscordInviteUrl=\n")
			TEXT("# Discord invite link shown to players who type /discord in-game. Leave empty to disable.\n")
			TEXT("\n")
			TEXT("# -- BOT INFO / HELP CHANNEL --------------------------------------------------\n")
			TEXT("BotInfoChannelId=\n")
			TEXT("# Channel where the bot posts a full feature/command embed on first start. Leave empty to disable.\n")
			TEXT("\n")
			TEXT("# -- ON-JOIN DIRECT MESSAGE ---------------------------------------------------\n")
			TEXT("WelcomeMessageDM=\n")
			TEXT("# DM sent to a player on first join. Leave empty to disable. Placeholder: %PlayerName%.\n")
			TEXT("\n")
			TEXT("# -- ON-JOIN IN-GAME HINT -----------------------------------------------------\n")
			TEXT("JoinHintMessage=\n")
			TEXT("# Message sent privately in-game when a player joins. Leave empty to disable.\n")
			TEXT("# Placeholder: %PlayerName%.\n")
			TEXT("\n")
			TEXT("# -- ON-JOIN IN-GAME BROADCAST ------------------------------------------------\n")
			TEXT("InGameJoinBroadcastEnabled=True\n")
			TEXT("# Master switch for the in-game join broadcast. Default: True.\n")
			TEXT("\n")
			TEXT("InGameJoinBroadcast=\n")
			TEXT("# Message broadcast to ALL players in game chat when someone joins. Leave empty to disable.\n")
			TEXT("# Placeholder: %PlayerName%.\n")
			TEXT("\n")
			TEXT("# -- MODERATION ---------------------------------------------------------------\n")
			TEXT("ModeratorChannelId=\n")
			TEXT("# Channel for mute/unmute notifications. Falls back to BanEventsChannelId, then ChannelId.\n")
			TEXT("\n")
			TEXT("NotifyMuteEvents=True\n")
			TEXT("# When True, posts mute/unmute notifications (requires BanChatCommands). Default: True.\n")
			TEXT("\n")
			TEXT("ModerationLogChannelId=\n")
			TEXT("# Channel for unified moderation log (bans, kicks, warns, mutes). Leave empty to disable.\n")
			TEXT("\n")
			TEXT("# -- AFK KICK -----------------------------------------------------------------\n")
			TEXT("AfkKickMinutes=0\n")
			TEXT("# Minutes of inactivity before kicking an AFK player. 0 = disabled. Default: 0.\n")
			TEXT("\n")
			TEXT("AfkKickReason=Kicked for inactivity (AFK).\n")
			TEXT("# Reason shown to the kicked player. Default: Kicked for inactivity (AFK).\n")
			TEXT("\n")
			TEXT("# -- SCHEDULED ANNOUNCEMENTS --------------------------------------------------\n")
			TEXT("AnnouncementIntervalMinutes=0\n")
			TEXT("# Interval in minutes for repeating announcements. 0 = disabled. Default: 0.\n")
			TEXT("\n")
			TEXT("AnnouncementMessage=\n")
			TEXT("# Message text for periodic announcement. Only used when interval > 0.\n")
			TEXT("\n")
			TEXT("AnnouncementChannelId=\n")
			TEXT("# Channel for announcements. Falls back to ChannelId.\n")
			TEXT("# Multiple announcements: +ScheduledAnnouncements=(IntervalMinutes=60,Message=\"...\",ChannelId=\"\")\n")
			TEXT("\n")
			TEXT("# -- WEBHOOK FALLBACK ---------------------------------------------------------\n")
			TEXT("FallbackWebhookUrl=\n")
			TEXT("# Fallback webhook URL used when the primary bot send fails. Leave empty to disable.\n")
			TEXT("\n")
			TEXT("# -- SLASH COMMANDS -----------------------------------------------------------\n")
			TEXT("EnableSlashCommands=True\n")
			TEXT("# When True, registers Discord slash commands on startup. Default: True.\n")
			TEXT("\n")
			TEXT("# -- DISCORD ROLE LABELS (for %Role% placeholder) -----------------------------\n")
			TEXT("# Format: +DiscordRoleLabels=roleId=Label  (first matching entry wins)\n")
			TEXT("# Leave empty to disable role labels.\n");

		// Ensure the Config directory exists before writing.
		PlatformFile.CreateDirectoryTree(*FPaths::GetPath(ModFilePath));

		if (FFileHelper::SaveStringToFile(DefaultContent, *ModFilePath,
			FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
		{
			UE_LOG(LogDiscordBridge, Log,
			       TEXT("DiscordBridge: Wrote default config to '%s'. "
			            "Set BotToken and ChannelId in that file, then restart "
			            "the server to enable the Discord bridge."), *ModFilePath);
		}
		else
		{
			UE_LOG(LogDiscordBridge, Warning,
			       TEXT("DiscordBridge: Could not write default config to '%s'."),
			       *ModFilePath);
		}
	}

	// ── Step 2: fall back to backup when credentials are missing ──────────────
	// This happens after a mod update resets the primary config file.
	// All settings (connection, chat, presence, whitelist, ban) are read from
	// the single DiscordBridge.ini backup so they survive mod updates.
	// [BACKUP-SYNC] When adding a new FDiscordBridgeConfig field, add a restore
	// line below AND a PatchLine call further down AND update Steps 1 and 3.
	//
	// IMPORTANT: the backup is read with raw string parsing (ParseRawIniSection)
	// instead of FConfigFile::Read + GetString.  FConfigFile expands %property%
	// references in values against keys in the same section.  Because ServerName
	// IS a key in [DiscordBridge], any format string that contains %ServerName%
	// (e.g. GameToDiscordFormat=**[%ServerName%] %PlayerName%**: %Message%) would
	// have %ServerName% silently replaced with the actual server name.  PatchLine
	// would then write that expanded value permanently into the primary config,
	// destroying the dynamic placeholder.  Raw parsing avoids all such processing.
	if ((Config.BotToken.IsEmpty() || Config.ChannelId.IsEmpty()) &&
	    PlatformFile.FileExists(*BackupFilePath))
	{
		FString BackupFileContent;
		if (!FFileHelper::LoadFileToString(BackupFileContent, *BackupFilePath))
		{
			UE_LOG(LogDiscordBridge, Warning,
			       TEXT("DiscordBridge: Failed reading backup config '%s'; cannot restore missing token/channel from backup."),
			       *BackupFilePath);
		}
		else
		{
			StripBOM(BackupFileContent);
		}
		const TMap<FString, FString> BackupValues = BackupFileContent.IsEmpty()
			? TMap<FString, FString>{}
			: ParseRawIniSection(BackupFileContent, TEXT("DiscordBridge"));

		const bool bHadToken   = !Config.BotToken.IsEmpty();
		const bool bHadChannel = !Config.ChannelId.IsEmpty();

		if (Config.BotToken.IsEmpty())
		{
			Config.BotToken = GetRawStringOrDefault(BackupValues, TEXT("BotToken"), TEXT("")).TrimStartAndEnd();
		}
		if (Config.ChannelId.IsEmpty())
		{
			Config.ChannelId = GetRawStringOrDefault(BackupValues, TEXT("ChannelId"), TEXT("")).TrimStartAndEnd();
		}

		// Restore all other user-customised settings from the backup so that
		// message formats and status messages also survive a mod update that
		// resets the primary config to its shipped defaults.
		Config.ServerName           = GetRawStringOrDefault(BackupValues, TEXT("ServerName"),           Config.ServerName);
		Config.GameToDiscordFormat  = GetRawStringOrFallback(BackupValues, TEXT("GameToDiscordFormat"),  Config.GameToDiscordFormat);
		Config.DiscordToGameFormat  = GetRawStringOrFallback(BackupValues, TEXT("DiscordToGameFormat"),  Config.DiscordToGameFormat);
		Config.bIgnoreBotMessages   = GetRawBoolOrDefault  (BackupValues, TEXT("IgnoreBotMessages"),
		                              GetRawBoolOrDefault  (BackupValues, TEXT("bIgnoreBotMessages"),   Config.bIgnoreBotMessages));
		Config.bServerStatusMessagesEnabled = GetRawBoolOrDefault(BackupValues, TEXT("ServerStatusMessagesEnabled"), Config.bServerStatusMessagesEnabled);
		Config.StatusChannelId      = GetRawStringOrDefault(BackupValues, TEXT("StatusChannelId"),      Config.StatusChannelId);
		Config.ServerOnlineMessage  = GetRawStringOrDefault(BackupValues, TEXT("ServerOnlineMessage"),  Config.ServerOnlineMessage);
		Config.ServerOfflineMessage = GetRawStringOrDefault(BackupValues, TEXT("ServerOfflineMessage"), Config.ServerOfflineMessage);
		Config.bShowPlayerCountInPresence       = GetRawBoolOrDefault  (BackupValues, TEXT("ShowPlayerCountInPresence"),
		                                          GetRawBoolOrDefault  (BackupValues, TEXT("bShowPlayerCountInPresence"),       Config.bShowPlayerCountInPresence));
		Config.PlayerCountPresenceFormat        = GetRawStringOrFallback(BackupValues, TEXT("PlayerCountPresenceFormat"),        Config.PlayerCountPresenceFormat);
		Config.PlayerCountUpdateIntervalSeconds = GetRawFloatOrDefault (BackupValues, TEXT("PlayerCountUpdateIntervalSeconds"), Config.PlayerCountUpdateIntervalSeconds);
		Config.PlayerCountActivityType          = GetRawIntOrDefault   (BackupValues, TEXT("PlayerCountActivityType"),          Config.PlayerCountActivityType);

		// Whitelist settings are now in a separate config file
		// (DefaultWhitelist.ini) loaded by FWhitelistConfig::Load().

		// Player event notification settings
		Config.bPlayerEventsEnabled    = GetRawBoolOrDefault  (BackupValues, TEXT("PlayerEventsEnabled"),    Config.bPlayerEventsEnabled);
		Config.PlayerEventsChannelId   = GetRawStringOrDefault(BackupValues, TEXT("PlayerEventsChannelId"),   Config.PlayerEventsChannelId);
		Config.PlayerJoinMessage       = GetRawStringOrDefault(BackupValues, TEXT("PlayerJoinMessage"),       Config.PlayerJoinMessage);
		Config.PlayerJoinAdminChannelId  = GetRawStringOrDefault(BackupValues, TEXT("PlayerJoinAdminChannelId"),  Config.PlayerJoinAdminChannelId);
		Config.PlayerJoinAdminMessage    = GetRawStringOrDefault(BackupValues, TEXT("PlayerJoinAdminMessage"),    Config.PlayerJoinAdminMessage);
		Config.PlayerLeaveMessage      = GetRawStringOrDefault(BackupValues, TEXT("PlayerLeaveMessage"),      Config.PlayerLeaveMessage);
		Config.PlayerTimeoutMessage    = GetRawStringOrDefault(BackupValues, TEXT("PlayerTimeoutMessage"),    Config.PlayerTimeoutMessage);
		Config.bUseEmbedsForPlayerEvents = GetRawBoolOrDefault(BackupValues, TEXT("UseEmbedsForPlayerEvents"), Config.bUseEmbedsForPlayerEvents);

		// Chat relay filter (array field – parse from raw backup content)
		Config.ChatRelayBlocklist = ParseRawIniArray(BackupFileContent, TEXT("DiscordBridge"), TEXT("ChatRelayBlocklist"));

		// Chat relay replacements (array field – parse from raw backup content)
		{
			TArray<FString> RawRepl = ParseRawIniArray(BackupFileContent, TEXT("DiscordBridge"), TEXT("ChatRelayBlocklistReplacements"));
			for (const FString& Line : RawRepl)
			{
				FString Cleaned = Line.TrimStartAndEnd();
				if (Cleaned.StartsWith(TEXT("("))) Cleaned = Cleaned.Mid(1);
				if (Cleaned.EndsWith(TEXT(")")))   Cleaned = Cleaned.LeftChop(1);

				FString PatStr, ReplStr;
				// Escape-aware extraction: honours \" sequences written by the config writer.
				auto ExtractQuoted = [&](const FString& Key, FString& Out) -> bool
				{
					const FString Search = Key + TEXT("=\"");
					const int32   Idx    = Cleaned.Find(Search, ESearchCase::IgnoreCase);
					if (Idx == INDEX_NONE) return false;
					const int32 Start = Idx + Search.Len();
					FString Value;
					int32 i = Start;
					bool bClosed = false;
					while (i < Cleaned.Len())
					{
						const TCHAR C = Cleaned[i];
						if (C == TEXT('\\') && i + 1 < Cleaned.Len() && Cleaned[i + 1] == TEXT('"'))
						{ Value.AppendChar(TEXT('"')); i += 2; }
						else if (C == TEXT('"'))
						{ bClosed = true; break; }
						else
						{ Value.AppendChar(C); ++i; }
					}
					if (!bClosed) return false;
					Out = Value;
					return true;
				};

				if (ExtractQuoted(TEXT("Pattern"),     PatStr) &&
				    ExtractQuoted(TEXT("Replacement"), ReplStr))
				{
					FChatRelayReplacement R;
					R.Pattern     = PatStr;
					R.Replacement = ReplStr;
					Config.ChatRelayBlocklistReplacements.Add(R);
				}
			}
		}

		// Bot commands
		Config.PlayersCommandChannelId = GetRawStringOrDefault (BackupValues, TEXT("PlayersCommandChannelId"), Config.PlayersCommandChannelId);
		Config.DiscordInviteUrl        = GetRawStringOrDefault (BackupValues, TEXT("DiscordInviteUrl"),        Config.DiscordInviteUrl);

		// New fields
		Config.PhaseEventsChannelId     = GetRawStringOrDefault (BackupValues, TEXT("PhaseEventsChannelId"),     Config.PhaseEventsChannelId);
		Config.SchematicEventsChannelId = GetRawStringOrDefault (BackupValues, TEXT("SchematicEventsChannelId"), Config.SchematicEventsChannelId);
		Config.BanEventsChannelId       = GetRawStringOrDefault (BackupValues, TEXT("BanEventsChannelId"),       Config.BanEventsChannelId);
		Config.bEnableJoinReactionVoting = GetRawBoolOrDefault  (BackupValues, TEXT("EnableJoinReactionVoting"), Config.bEnableJoinReactionVoting);
		Config.VoteKickThreshold        = GetRawIntOrDefault    (BackupValues, TEXT("VoteKickThreshold"),        Config.VoteKickThreshold);
		Config.VoteWindowMinutes        = GetRawIntOrDefault    (BackupValues, TEXT("VoteWindowMinutes"),        Config.VoteWindowMinutes);
		Config.AfkKickMinutes           = GetRawIntOrDefault    (BackupValues, TEXT("AfkKickMinutes"),           Config.AfkKickMinutes);
		Config.AfkKickReason            = GetRawStringOrDefault (BackupValues, TEXT("AfkKickReason"),            Config.AfkKickReason);

		// Scheduled announcements
		Config.AnnouncementIntervalMinutes = GetRawIntOrDefault    (BackupValues, TEXT("AnnouncementIntervalMinutes"), Config.AnnouncementIntervalMinutes);
		Config.AnnouncementMessage         = GetRawStringOrDefault (BackupValues, TEXT("AnnouncementMessage"),         Config.AnnouncementMessage);
		Config.AnnouncementChannelId       = GetRawStringOrDefault (BackupValues, TEXT("AnnouncementChannelId"),       Config.AnnouncementChannelId);

		// Embed mode flags
		Config.bUseEmbedsForPhaseEvents     = GetRawBoolOrDefault(BackupValues, TEXT("UseEmbedsForPhaseEvents"),     Config.bUseEmbedsForPhaseEvents);
		Config.bUseEmbedsForSchematicEvents = GetRawBoolOrDefault(BackupValues, TEXT("UseEmbedsForSchematicEvents"), Config.bUseEmbedsForSchematicEvents);

		// Webhook fallback
		Config.FallbackWebhookUrl = GetRawStringOrDefault(BackupValues, TEXT("FallbackWebhookUrl"), Config.FallbackWebhookUrl);

		// Slash commands
		Config.bEnableSlashCommands = GetRawBoolOrDefault(BackupValues, TEXT("EnableSlashCommands"), Config.bEnableSlashCommands);

		// Mute notifications
		Config.bNotifyMuteEvents  = GetRawBoolOrDefault  (BackupValues, TEXT("NotifyMuteEvents"),  Config.bNotifyMuteEvents);
		Config.ModeratorChannelId = GetRawStringOrDefault(BackupValues, TEXT("ModeratorChannelId"), Config.ModeratorChannelId);

		Config.ModerationLogChannelId = GetRawStringOrDefault(BackupValues, TEXT("ModerationLogChannelId"), Config.ModerationLogChannelId);

		// Bot info / help channel
		Config.BotInfoChannelId = GetRawStringOrDefault(BackupValues, TEXT("BotInfoChannelId"), Config.BotInfoChannelId);

		// On-join DM welcome message
		Config.WelcomeMessageDM = GetRawStringOrDefault(BackupValues, TEXT("WelcomeMessageDM"), Config.WelcomeMessageDM);

		// On-join in-game hint message
		Config.JoinHintMessage = GetRawStringOrDefault(BackupValues, TEXT("JoinHintMessage"), Config.JoinHintMessage);

		// On-join broadcast message (all players)
		Config.bInGameJoinBroadcastEnabled = GetRawBoolOrDefault(BackupValues, TEXT("InGameJoinBroadcastEnabled"), Config.bInGameJoinBroadcastEnabled);
		Config.InGameJoinBroadcast = GetRawStringOrDefault(BackupValues, TEXT("InGameJoinBroadcast"), Config.InGameJoinBroadcast);

		// DiscordRoleLabels array (restore from raw backup content)
		Config.DiscordRoleLabels = ParseRawIniArray(BackupFileContent, TEXT("DiscordBridge"), TEXT("DiscordRoleLabels"));

		// ScheduledAnnouncements: NOT restored from backup — they remain in primary config only.

		// Only log the "restored from backup" message when credentials were
		// actually recovered (i.e. previously blank in primary but now non-empty
		// from the backup). Avoid a misleading message when the backup also has
		// blank credentials (e.g. first server start before credentials are set).
		const bool bRestoredToken   = !bHadToken   && !Config.BotToken.IsEmpty();
		const bool bRestoredChannel = !bHadChannel && !Config.ChannelId.IsEmpty();
		if (bRestoredToken || bRestoredChannel)
		{
			UE_LOG(LogDiscordBridge, Log,
			       TEXT("DiscordBridge: Primary config '%s' had no credentials – "
			            "restored from backup at '%s'. "
			            "Writing all settings back to the primary config so they persist there."),
			       *ModFilePath, *BackupFilePath);

			// Write every restored setting back into the primary config file so
			// operators always see their current settings there and do not have to
			// re-enter them manually after every mod update.
			// Uses a line-level replace: find "Key=<anything>\n" at the start of a
			// line and replace it with "Key=<Value>\n", preserving line endings and
			// all surrounding comment lines.  This handles both empty-value template
			// lines (e.g. "BotToken=\n") and lines with default values already set
			// (e.g. "WhitelistEnabled=False\n") so every user-customised setting
			// survives subsequent restarts after a mod update.
			// [BACKUP-SYNC] When adding a new FDiscordBridgeConfig field, add a
			// PatchLine call below so the restored value is written back here too.
			FString PrimaryContent;
			if (FFileHelper::LoadFileToString(PrimaryContent, *ModFilePath))
			{
				StripBOM(PrimaryContent);
				// Replace the line "Key=<current>\n" (at the start of a line) with
				// "Key=Value\n", preserving \r\n vs \n line endings.
				auto PatchLine = [&](const TCHAR* Key, const FString& Value)
				{
					const FString Prefix = FString(Key) + TEXT("=");
					for (int32 From = 0;;)
					{
						const int32 At = PrimaryContent.Find(
							Prefix, ESearchCase::CaseSensitive, ESearchDir::FromStart, From);
						if (At == INDEX_NONE)
							break;
						// Only replace when the key appears at the start of a line.
						if (At == 0 || PrimaryContent[At - 1] == '\n')
						{
							const int32 NL = PrimaryContent.Find(
								TEXT("\n"), ESearchCase::CaseSensitive, ESearchDir::FromStart, At);
							if (NL != INDEX_NONE)
							{
								const bool bHasCR = NL > 0 && PrimaryContent[NL - 1] == '\r';
								PrimaryContent = PrimaryContent.Left(At)
									+ Prefix + Value
									+ (bHasCR ? TEXT("\r\n") : TEXT("\n"))
									+ PrimaryContent.Mid(NL + 1);
							}
							else
							{
								// Last line in the file with no trailing newline — replace to end.
								PrimaryContent = PrimaryContent.Left(At) + Prefix + Value;
							}
							return;
						}
						From = At + 1;
					}
				};

				PatchLine(TEXT("BotToken"),                      Config.BotToken);
				PatchLine(TEXT("ChannelId"),                     Config.ChannelId);
				PatchLine(TEXT("ServerName"),                    Config.ServerName);
				PatchLine(TEXT("GameToDiscordFormat"),           Config.GameToDiscordFormat);
				PatchLine(TEXT("DiscordToGameFormat"),           Config.DiscordToGameFormat);
				PatchLine(TEXT("IgnoreBotMessages"),             Config.bIgnoreBotMessages ? TEXT("True") : TEXT("False"));
				PatchLine(TEXT("ServerStatusMessagesEnabled"),   Config.bServerStatusMessagesEnabled ? TEXT("True") : TEXT("False"));
				PatchLine(TEXT("StatusChannelId"),               Config.StatusChannelId);
				PatchLine(TEXT("ServerOnlineMessage"),           Config.ServerOnlineMessage);
				PatchLine(TEXT("ServerOfflineMessage"),          Config.ServerOfflineMessage);
				PatchLine(TEXT("ShowPlayerCountInPresence"),     Config.bShowPlayerCountInPresence ? TEXT("True") : TEXT("False"));
				PatchLine(TEXT("PlayerCountPresenceFormat"),     Config.PlayerCountPresenceFormat);
				PatchLine(TEXT("PlayerCountUpdateIntervalSeconds"), *FString::SanitizeFloat(Config.PlayerCountUpdateIntervalSeconds));
				PatchLine(TEXT("PlayerCountActivityType"),       *FString::FromInt(Config.PlayerCountActivityType));
				// Whitelist settings are now in DefaultWhitelist.ini (FWhitelistConfig).
				PatchLine(TEXT("PlayerEventsEnabled"),           Config.bPlayerEventsEnabled ? TEXT("True") : TEXT("False"));
				PatchLine(TEXT("PlayerEventsChannelId"),         Config.PlayerEventsChannelId);
				PatchLine(TEXT("PlayerJoinMessage"),             Config.PlayerJoinMessage);
				PatchLine(TEXT("PlayerJoinAdminChannelId"),      Config.PlayerJoinAdminChannelId);
				PatchLine(TEXT("PlayerJoinAdminMessage"),        Config.PlayerJoinAdminMessage);
				PatchLine(TEXT("PlayerLeaveMessage"),            Config.PlayerLeaveMessage);
				PatchLine(TEXT("PlayerTimeoutMessage"),          Config.PlayerTimeoutMessage);
				PatchLine(TEXT("UseEmbedsForPlayerEvents"),      Config.bUseEmbedsForPlayerEvents ? TEXT("True") : TEXT("False"));
				PatchLine(TEXT("PlayersCommandChannelId"),       Config.PlayersCommandChannelId);
				PatchLine(TEXT("DiscordInviteUrl"),              Config.DiscordInviteUrl);
				PatchLine(TEXT("PhaseEventsChannelId"),          Config.PhaseEventsChannelId);
				PatchLine(TEXT("SchematicEventsChannelId"),      Config.SchematicEventsChannelId);
				PatchLine(TEXT("BanEventsChannelId"),            Config.BanEventsChannelId);
				PatchLine(TEXT("EnableJoinReactionVoting"),      Config.bEnableJoinReactionVoting ? TEXT("True") : TEXT("False"));
				PatchLine(TEXT("VoteKickThreshold"),             *FString::FromInt(Config.VoteKickThreshold));
				PatchLine(TEXT("VoteWindowMinutes"),             *FString::FromInt(Config.VoteWindowMinutes));
				PatchLine(TEXT("AfkKickMinutes"),                *FString::FromInt(Config.AfkKickMinutes));
				PatchLine(TEXT("AfkKickReason"),                 Config.AfkKickReason);
				PatchLine(TEXT("AnnouncementIntervalMinutes"),   *FString::FromInt(Config.AnnouncementIntervalMinutes));
				PatchLine(TEXT("AnnouncementMessage"),           Config.AnnouncementMessage);
				PatchLine(TEXT("AnnouncementChannelId"),         Config.AnnouncementChannelId);
				PatchLine(TEXT("UseEmbedsForPhaseEvents"),       Config.bUseEmbedsForPhaseEvents     ? TEXT("True") : TEXT("False"));
				PatchLine(TEXT("UseEmbedsForSchematicEvents"),   Config.bUseEmbedsForSchematicEvents ? TEXT("True") : TEXT("False"));
				PatchLine(TEXT("FallbackWebhookUrl"),            Config.FallbackWebhookUrl);
				PatchLine(TEXT("EnableSlashCommands"),           Config.bEnableSlashCommands ? TEXT("True") : TEXT("False"));
				PatchLine(TEXT("NotifyMuteEvents"),              Config.bNotifyMuteEvents  ? TEXT("True") : TEXT("False"));
				PatchLine(TEXT("ModeratorChannelId"),            Config.ModeratorChannelId);
				PatchLine(TEXT("ModerationLogChannelId"),        Config.ModerationLogChannelId);
				PatchLine(TEXT("BotInfoChannelId"),              Config.BotInfoChannelId);
				PatchLine(TEXT("WelcomeMessageDM"),              Config.WelcomeMessageDM);
				PatchLine(TEXT("JoinHintMessage"),               Config.JoinHintMessage);
				PatchLine(TEXT("InGameJoinBroadcastEnabled"),    Config.bInGameJoinBroadcastEnabled ? TEXT("True") : TEXT("False"));
				PatchLine(TEXT("InGameJoinBroadcast"),           Config.InGameJoinBroadcast);

				// ChatRelayBlocklist is a multi-value array field.  Remove all
				// existing Key= / +Key= lines then append the restored values.
				{
					const FString PlainPfx = TEXT("ChatRelayBlocklist=");
					const FString PlusPfx  = TEXT("+ChatRelayBlocklist=");
					FString Rebuilt;
					Rebuilt.Reserve(PrimaryContent.Len());
					int32 Pos = 0;
					while (Pos <= PrimaryContent.Len())
					{
						const int32 NL = PrimaryContent.Find(
							TEXT("\n"), ESearchCase::CaseSensitive, ESearchDir::FromStart, Pos);
						const bool  bLast   = (NL == INDEX_NONE);
						const int32 LineEnd = bLast ? PrimaryContent.Len() : NL;
						const FString RawLine = PrimaryContent.Mid(Pos, LineEnd - Pos);
						Pos = bLast ? (PrimaryContent.Len() + 1) : (NL + 1);
						FString Cmp = RawLine;
						if (!Cmp.IsEmpty() && Cmp[Cmp.Len()-1] == TEXT('\r'))
							Cmp.RemoveAt(Cmp.Len()-1, 1, /*bAllowShrinking=*/false);
						if (!Cmp.StartsWith(PlainPfx) && !Cmp.StartsWith(PlusPfx))
						{
							Rebuilt += RawLine;
							if (!bLast) Rebuilt += TEXT("\n");
						}
					}
					if (!Rebuilt.IsEmpty() && Rebuilt[Rebuilt.Len()-1] != TEXT('\n'))
						Rebuilt += TEXT("\n");
					for (const FString& Item : Config.ChatRelayBlocklist)
						Rebuilt += PlusPfx + Item + TEXT("\n");
					PrimaryContent = MoveTemp(Rebuilt);
				}

				// ChatRelayBlocklistReplacements is a multi-value array field.
				{
					const FString PlainPfx = TEXT("ChatRelayBlocklistReplacements=");
					const FString PlusPfx  = TEXT("+ChatRelayBlocklistReplacements=");
					FString Rebuilt;
					Rebuilt.Reserve(PrimaryContent.Len());
					int32 Pos = 0;
					while (Pos <= PrimaryContent.Len())
					{
						const int32 NL = PrimaryContent.Find(
							TEXT("\n"), ESearchCase::CaseSensitive, ESearchDir::FromStart, Pos);
						const bool  bLast   = (NL == INDEX_NONE);
						const int32 LineEnd = bLast ? PrimaryContent.Len() : NL;
						const FString RawLine = PrimaryContent.Mid(Pos, LineEnd - Pos);
						Pos = bLast ? (PrimaryContent.Len() + 1) : (NL + 1);
						FString Cmp = RawLine;
						if (!Cmp.IsEmpty() && Cmp[Cmp.Len()-1] == TEXT('\r'))
							Cmp.RemoveAt(Cmp.Len()-1, 1, /*bAllowShrinking=*/false);
						if (!Cmp.StartsWith(PlainPfx) && !Cmp.StartsWith(PlusPfx))
						{
							Rebuilt += RawLine;
							if (!bLast) Rebuilt += TEXT("\n");
						}
					}
					if (!Rebuilt.IsEmpty() && Rebuilt[Rebuilt.Len()-1] != TEXT('\n'))
						Rebuilt += TEXT("\n");
					for (const FChatRelayReplacement& R : Config.ChatRelayBlocklistReplacements)
					{
						const FString EscPat  = R.Pattern.Replace(TEXT("\""), TEXT("\\\""));
						const FString EscRepl = R.Replacement.Replace(TEXT("\""), TEXT("\\\""));
						Rebuilt += PlusPfx + TEXT("(Pattern=\"") + EscPat + TEXT("\",Replacement=\"") + EscRepl + TEXT("\")\n");
					}
					PrimaryContent = MoveTemp(Rebuilt);
				}

				// DiscordRoleLabels is a multi-value array field.
				{
					const FString PlainPfx = TEXT("DiscordRoleLabels=");
					const FString PlusPfx  = TEXT("+DiscordRoleLabels=");
					FString Rebuilt;
					Rebuilt.Reserve(PrimaryContent.Len());
					int32 Pos = 0;
					while (Pos <= PrimaryContent.Len())
					{
						const int32 NL = PrimaryContent.Find(
							TEXT("\n"), ESearchCase::CaseSensitive, ESearchDir::FromStart, Pos);
						const bool  bLast   = (NL == INDEX_NONE);
						const int32 LineEnd = bLast ? PrimaryContent.Len() : NL;
						const FString RawLine = PrimaryContent.Mid(Pos, LineEnd - Pos);
						Pos = bLast ? (PrimaryContent.Len() + 1) : (NL + 1);
						FString Cmp = RawLine;
						if (!Cmp.IsEmpty() && Cmp[Cmp.Len()-1] == TEXT('\r'))
							Cmp.RemoveAt(Cmp.Len()-1, 1, /*bAllowShrinking=*/false);
						if (!Cmp.StartsWith(PlainPfx) && !Cmp.StartsWith(PlusPfx))
						{
							Rebuilt += RawLine;
							if (!bLast) Rebuilt += TEXT("\n");
						}
					}
					if (!Rebuilt.IsEmpty() && Rebuilt[Rebuilt.Len()-1] != TEXT('\n'))
						Rebuilt += TEXT("\n");
					for (const FString& Entry : Config.DiscordRoleLabels)
						Rebuilt += PlusPfx + Entry + TEXT("\n");
					PrimaryContent = MoveTemp(Rebuilt);
				}

				if (FFileHelper::SaveStringToFile(PrimaryContent, *ModFilePath,
				    FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
				{
					UE_LOG(LogDiscordBridge, Log,
					       TEXT("DiscordBridge: Updated primary config at '%s' with all restored settings."),
					       *ModFilePath);
				}
				else
				{
					UE_LOG(LogDiscordBridge, Warning,
					       TEXT("DiscordBridge: Could not write restored settings back to '%s'. "
					            "The bridge will still function using the backup."),
					       *ModFilePath);
				}
			}
		}
	}

	// ── Post-load: trim whitespace and validate all fields ──────────────────
	// Applies to values restored from backup as well as those from primary.
	TrimConfigStringFields(Config);
	ValidateConfigFields(Config);

	// ── Step 3: write up-to-date backup ─────────────────────────────────────────
	// Write a single backup file with all settings on every server start so they
	// survive the next mod update.  The backup is written even when BotToken/
	// ChannelId are still blank so settings like message formats are preserved
	// regardless of credential state.
	// [BACKUP-SYNC] When adding a new FDiscordBridgeConfig field, append a line
	// for it here so it is included in the backup that survives mod updates.
	{
		// NOTE: String concatenation is used intentionally instead of FString::Printf
		// to prevent user-configured values that contain '%' characters (e.g.
		// %PlayerName%, %Message%, %PlayerCount%) from being misinterpreted as
		// printf format specifiers, which would corrupt the written file.
		const FString BackupContent =
			FString(TEXT("[DiscordBridge]\n"))
			+ TEXT("# Auto-generated backup of ") + ModFilePath + TEXT("\n")
			+ TEXT("# This file is read automatically when the primary config is missing credentials.\n")
			+ TEXT("BotToken=") + Config.BotToken + TEXT("\n")
			+ TEXT("ChannelId=") + Config.ChannelId + TEXT("\n")
			+ TEXT("ServerName=") + Config.ServerName + TEXT("\n")
			+ TEXT("GameToDiscordFormat=") + Config.GameToDiscordFormat + TEXT("\n")
			+ TEXT("DiscordToGameFormat=") + Config.DiscordToGameFormat + TEXT("\n")
			+ TEXT("IgnoreBotMessages=") + (Config.bIgnoreBotMessages ? TEXT("True") : TEXT("False")) + TEXT("\n")
			+ TEXT("ServerStatusMessagesEnabled=") + (Config.bServerStatusMessagesEnabled ? TEXT("True") : TEXT("False")) + TEXT("\n")
			+ TEXT("StatusChannelId=") + Config.StatusChannelId + TEXT("\n")
			+ TEXT("ServerOnlineMessage=") + Config.ServerOnlineMessage + TEXT("\n")
			+ TEXT("ServerOfflineMessage=") + Config.ServerOfflineMessage + TEXT("\n")
			+ TEXT("ShowPlayerCountInPresence=") + (Config.bShowPlayerCountInPresence ? TEXT("True") : TEXT("False")) + TEXT("\n")
			+ TEXT("PlayerCountPresenceFormat=") + Config.PlayerCountPresenceFormat + TEXT("\n")
			+ TEXT("PlayerCountUpdateIntervalSeconds=") + FString::SanitizeFloat(Config.PlayerCountUpdateIntervalSeconds) + TEXT("\n")
			+ TEXT("PlayerCountActivityType=") + FString::FromInt(Config.PlayerCountActivityType) + TEXT("\n")
			+ TEXT("PlayerEventsEnabled=") + (Config.bPlayerEventsEnabled ? TEXT("True") : TEXT("False")) + TEXT("\n")
			+ TEXT("PlayerEventsChannelId=") + Config.PlayerEventsChannelId + TEXT("\n")
			+ TEXT("PlayerJoinMessage=") + Config.PlayerJoinMessage + TEXT("\n")
			+ TEXT("PlayerJoinAdminChannelId=") + Config.PlayerJoinAdminChannelId + TEXT("\n")
			+ TEXT("PlayerJoinAdminMessage=") + Config.PlayerJoinAdminMessage + TEXT("\n")
			+ TEXT("PlayerLeaveMessage=") + Config.PlayerLeaveMessage + TEXT("\n")
			+ TEXT("PlayerTimeoutMessage=") + Config.PlayerTimeoutMessage + TEXT("\n")
			+ TEXT("UseEmbedsForPlayerEvents=") + (Config.bUseEmbedsForPlayerEvents ? TEXT("True") : TEXT("False")) + TEXT("\n")
			+ TEXT("PlayersCommandChannelId=") + Config.PlayersCommandChannelId + TEXT("\n")
			+ TEXT("DiscordInviteUrl=") + Config.DiscordInviteUrl + TEXT("\n");

		// ChatRelayBlocklist is an array; append each item as +Key=value.
		FString BackupBlocklistLines;
		for (const FString& Item : Config.ChatRelayBlocklist)
		{
			BackupBlocklistLines += TEXT("+ChatRelayBlocklist=") + Item + TEXT("\n");
		}
		// ChatRelayBlocklistReplacements array
		FString BackupReplLines;
		for (const FChatRelayReplacement& R : Config.ChatRelayBlocklistReplacements)
		{
			const FString EscPat  = R.Pattern.Replace(TEXT("\""), TEXT("\\\""));
			const FString EscRepl = R.Replacement.Replace(TEXT("\""), TEXT("\\\""));
			BackupReplLines += TEXT("+ChatRelayBlocklistReplacements=(Pattern=\"") + EscPat
				+ TEXT("\",Replacement=\"") + EscRepl + TEXT("\")\n");
		}

		// New config fields for the backup
		const FString NewFieldLines =
			+ TEXT("PhaseEventsChannelId=") + Config.PhaseEventsChannelId + TEXT("\n")
			+ TEXT("SchematicEventsChannelId=") + Config.SchematicEventsChannelId + TEXT("\n")
			+ TEXT("BanEventsChannelId=") + Config.BanEventsChannelId + TEXT("\n")
			+ TEXT("EnableJoinReactionVoting=") + (Config.bEnableJoinReactionVoting ? TEXT("True") : TEXT("False")) + TEXT("\n")
			+ TEXT("VoteKickThreshold=") + FString::FromInt(Config.VoteKickThreshold) + TEXT("\n")
			+ TEXT("VoteWindowMinutes=") + FString::FromInt(Config.VoteWindowMinutes) + TEXT("\n")
			+ TEXT("AfkKickMinutes=") + FString::FromInt(Config.AfkKickMinutes) + TEXT("\n")
			+ TEXT("AfkKickReason=") + Config.AfkKickReason + TEXT("\n")
			+ TEXT("\n")
			+ TEXT("; -- Scheduled Announcements ------------------------------------------------\n")
			+ TEXT("AnnouncementIntervalMinutes=") + FString::FromInt(Config.AnnouncementIntervalMinutes) + TEXT("\n")
			+ TEXT("AnnouncementMessage=") + Config.AnnouncementMessage + TEXT("\n")
			+ TEXT("AnnouncementChannelId=") + Config.AnnouncementChannelId + TEXT("\n")
			+ TEXT("\n")
			+ TEXT("; -- Embed Mode Flags -------------------------------------------------------\n")
			+ TEXT("UseEmbedsForPhaseEvents=")     + (Config.bUseEmbedsForPhaseEvents     ? TEXT("True") : TEXT("False")) + TEXT("\n")
			+ TEXT("UseEmbedsForSchematicEvents=") + (Config.bUseEmbedsForSchematicEvents ? TEXT("True") : TEXT("False")) + TEXT("\n")
			+ TEXT("\n")
			+ TEXT("; -- Webhook Fallback -------------------------------------------------------\n")
			+ TEXT("FallbackWebhookUrl=") + Config.FallbackWebhookUrl + TEXT("\n")
			+ TEXT("\n")
			+ TEXT("; -- Slash Commands ---------------------------------------------------------\n")
			+ TEXT("EnableSlashCommands=") + (Config.bEnableSlashCommands ? TEXT("True") : TEXT("False")) + TEXT("\n")
			+ TEXT("\n")
			+ TEXT("; -- Mute Notifications -----------------------------------------------------\n")
			+ TEXT("NotifyMuteEvents=")  + (Config.bNotifyMuteEvents  ? TEXT("True") : TEXT("False")) + TEXT("\n")
			+ TEXT("ModeratorChannelId=") + Config.ModeratorChannelId + TEXT("\n")
			+ TEXT("ModerationLogChannelId=") + Config.ModerationLogChannelId + TEXT("\n")
			+ TEXT("\n")
			+ TEXT("; -- Bot Info / Help Channel ------------------------------------------------\n")
			+ TEXT("BotInfoChannelId=") + Config.BotInfoChannelId + TEXT("\n");

		// ScheduledAnnouncements array backup lines
		FString BackupSALines;
		for (const FScheduledAnnouncement& SA : Config.ScheduledAnnouncements)
		{
			// Escape embedded double-quotes in Message so the backup round-trips
			// correctly through the escape-aware extraction code above.
			const FString EscapedMsg = SA.Message.Replace(TEXT("\""), TEXT("\\\""));
			BackupSALines += TEXT("+ScheduledAnnouncements=(IntervalMinutes=")
				+ FString::FromInt(SA.IntervalMinutes)
				+ TEXT(",Message=\"") + EscapedMsg
				+ TEXT("\",ChannelId=\"") + SA.ChannelId
				+ TEXT("\")\n");
		}

		// DiscordRoleLabels array backup lines
		FString BackupRoleLabelLines;
		BackupRoleLabelLines += FString(TEXT("\n"))
			+ TEXT("; -- On-Join Messages ----------------------------------------------------------\n")
			+ TEXT("WelcomeMessageDM=") + Config.WelcomeMessageDM + TEXT("\n")
			+ TEXT("JoinHintMessage=") + Config.JoinHintMessage + TEXT("\n")
			+ TEXT("InGameJoinBroadcastEnabled=") + (Config.bInGameJoinBroadcastEnabled ? TEXT("True") : TEXT("False")) + TEXT("\n")
			+ TEXT("InGameJoinBroadcast=") + Config.InGameJoinBroadcast + TEXT("\n")
			+ TEXT("\n")
			+ TEXT("; -- Discord Role Labels (for %Role% placeholder) --------------------------\n");
		for (const FString& Entry : Config.DiscordRoleLabels)
		{
			BackupRoleLabelLines += TEXT("+DiscordRoleLabels=") + Entry + TEXT("\n");
		}

		const FString FullBackupContent = BackupContent + BackupBlocklistLines + BackupReplLines + NewFieldLines + BackupSALines + BackupRoleLabelLines;

		PlatformFile.CreateDirectoryTree(*FPaths::GetPath(BackupFilePath));

		if (FFileHelper::SaveStringToFile(FullBackupContent, *BackupFilePath,
			FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
		{
			if (Config.BotToken.IsEmpty())
			{
				UE_LOG(LogDiscordBridge, Log,
				       TEXT("DiscordBridge: Wrote backup config at '%s' (credentials not yet configured)."),
				       *BackupFilePath);
			}
			else
			{
				UE_LOG(LogDiscordBridge, Log,
				       TEXT("DiscordBridge: Updated backup config at '%s'."), *BackupFilePath);
			}
		}
		else
		{
			UE_LOG(LogDiscordBridge, Warning,
			       TEXT("DiscordBridge: Could not write backup config to '%s'."),
			       *BackupFilePath);
		}
	}

	return Config;
}
