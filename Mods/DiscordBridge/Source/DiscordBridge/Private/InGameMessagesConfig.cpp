// Copyright Yamahasxviper. All Rights Reserved.

#include "InGameMessagesConfig.h"

#include "Misc/ConfigCacheIni.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

DEFINE_LOG_CATEGORY(LogInGameMessagesConfig);

// -----------------------------------------------------------------------------
// BOM helpers
// -----------------------------------------------------------------------------

/** Strip a leading UTF-8 BOM (EF BB BF) from a file on disk. */
static void CleanInGameMessagesConfigBOM(const FString& FilePath)
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
		UE_LOG(LogInGameMessagesConfig, Log,
		       TEXT("InGameMessages: Stripped UTF-8 BOM from '%s'."), *FilePath);
	}
}

// -----------------------------------------------------------------------------
// Internal helpers
// -----------------------------------------------------------------------------

static const TCHAR* IGMSection = TEXT("InGameMessages");

static FString GetIGMString(const FConfigFile& Cfg, const FString& Key,
                            const FString& Default = TEXT(""))
{
	FString Value;
	if (Cfg.GetString(IGMSection, *Key, Value))
	{
		Value.TrimStartAndEndInline();
		return Value;
	}
	return Default;
}

static bool GetIGMBool(const FConfigFile& Cfg, const FString& Key, bool Default)
{
	FString StrValue;
	if (!Cfg.GetString(IGMSection, *Key, StrValue) || StrValue.IsEmpty())
		return Default;
	bool Value = Default;
	Cfg.GetBool(IGMSection, *Key, Value);
	return Value;
}

// -----------------------------------------------------------------------------
// Raw INI array parser (same approach as DiscordBridgeConfig ParseRawIniArray)
// -----------------------------------------------------------------------------

static TArray<FString> ParseRawIniArrayIGM(const FString& RawContent,
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

		FString Value;
		if (Trimmed.StartsWith(PlusPrefix))
			Value = Trimmed.Mid(PlusPrefix.Len());
		else if (Trimmed.StartsWith(PlainPrefix))
			Value = Trimmed.Mid(PlainPrefix.Len());
		else
			continue;

		Value.TrimStartAndEndInline();
		if (!Value.IsEmpty())
			Result.Add(Value);
	}

	return Result;
}

// -----------------------------------------------------------------------------
// Struct field extraction from parenthesised tuple
// -----------------------------------------------------------------------------

/**
 * Extract a quoted string field from a cleaned INI tuple line.
 * e.g. for FieldName="Hello world" returns "Hello world".
 */
static FString ExtractQuotedField(const FString& Cleaned, const FString& FieldName)
{
	const FString Search = FieldName + TEXT("=\"");
	const int32 Idx = Cleaned.Find(Search, ESearchCase::IgnoreCase);
	if (Idx == INDEX_NONE)
		return FString();

	const int32 Start = Idx + Search.Len();
	const int32 End   = Cleaned.Find(TEXT("\""), ESearchCase::CaseSensitive,
	                                  ESearchDir::FromStart, Start);
	if (End == INDEX_NONE)
		return FString();

	return Cleaned.Mid(Start, End - Start);
}

/** Extract an integer field from a cleaned INI tuple line. */
static int32 ExtractIntField(const FString& Cleaned, const FString& FieldName, int32 Default)
{
	const FString Search = FieldName + TEXT("=");
	const int32 Idx = Cleaned.Find(Search, ESearchCase::IgnoreCase);
	if (Idx == INDEX_NONE)
		return Default;

	const FString Rest = Cleaned.Mid(Idx + Search.Len());
	int32 Comma = INDEX_NONE;
	if (Rest.FindChar(TEXT(','), Comma))
	{
		const FString Val = Rest.Left(Comma).TrimStartAndEnd();
		return Val.IsNumeric() ? FCString::Atoi(*Val) : Default;
	}
	const FString Val = Rest.TrimStartAndEnd();
	return Val.IsNumeric() ? FCString::Atoi(*Val) : Default;
}

// -----------------------------------------------------------------------------
// FInGameMessagesConfig
// -----------------------------------------------------------------------------

FString FInGameMessagesConfig::GetConfigFilePath()
{
	return FPaths::ProjectDir() /
	       TEXT("Mods/DiscordBridge/Config/DefaultInGameMessages.ini");
}

FString FInGameMessagesConfig::GetBackupFilePath()
{
	return FPaths::Combine(
		FPaths::ProjectSavedDir(),
		TEXT("DiscordBridge"),
		TEXT("InGameMessages.ini"));
}

FInGameMessagesConfig FInGameMessagesConfig::Load()
{
	FInGameMessagesConfig Out;

	const FString PrimaryPath = GetConfigFilePath();
	const FString BackupPath  = GetBackupFilePath();

	IPlatformFile& PF = FPlatformFileManager::Get().GetPlatformFile();

	// Proactively strip UTF-8 BOM if present.
	if (PF.FileExists(*PrimaryPath))
		CleanInGameMessagesConfigBOM(PrimaryPath);
	if (PF.FileExists(*BackupPath))
		CleanInGameMessagesConfigBOM(BackupPath);

	// -- Load scalar fields via FConfigFile -----------------------------------
	FConfigFile Cfg;
	bool bLoaded = false;
	FString RawFileContent;

	// Try primary config file first.
	if (PF.FileExists(*PrimaryPath))
	{
		Cfg.Read(PrimaryPath);
		bLoaded = Cfg.Contains(IGMSection);
		if (bLoaded)
			FFileHelper::LoadFileToString(RawFileContent, *PrimaryPath);
	}

	// Fall back to the backup copy if primary is missing or empty.
	if (!bLoaded && PF.FileExists(*BackupPath))
	{
		Cfg.Read(BackupPath);
		bLoaded = Cfg.Contains(IGMSection);
		if (bLoaded)
			FFileHelper::LoadFileToString(RawFileContent, *BackupPath);
	}

	if (!bLoaded)
	{
		UE_LOG(LogInGameMessagesConfig, Log,
		       TEXT("InGameMessages: No [InGameMessages] section found at '%s'. "
		            "In-game broadcast messages are disabled until configured."),
		       *PrimaryPath);
		return Out;
	}

	Out.bEnabled          = GetIGMBool  (Cfg, TEXT("Enabled"),          Out.bEnabled);
	Out.DefaultSenderName = GetIGMString(Cfg, TEXT("DefaultSenderName"), Out.DefaultSenderName);

	// -- Parse +Messages=(...) array ------------------------------------------
	{
		const TArray<FString> MsgLines = ParseRawIniArrayIGM(
			RawFileContent, TEXT("InGameMessages"), TEXT("Messages"));

		for (const FString& Line : MsgLines)
		{
			FString Cleaned = Line.TrimStartAndEnd();
			if (Cleaned.StartsWith(TEXT("("))) Cleaned = Cleaned.Mid(1);
			if (Cleaned.EndsWith(TEXT(")")))   Cleaned = Cleaned.LeftChop(1);

			FInGameBroadcastMessage Entry;
			Entry.IntervalMinutes = ExtractIntField(Cleaned, TEXT("IntervalMinutes"), 0);
			Entry.Message         = ExtractQuotedField(Cleaned, TEXT("Message"));
			Entry.SenderName      = ExtractQuotedField(Cleaned, TEXT("SenderName"));

			// Fall back to the global default sender name if omitted.
			if (Entry.SenderName.IsEmpty())
				Entry.SenderName = Out.DefaultSenderName;

			if (Entry.IntervalMinutes > 0 && !Entry.Message.IsEmpty())
			{
				Out.Messages.Add(Entry);
				UE_LOG(LogInGameMessagesConfig, Log,
				       TEXT("InGameMessages: Loaded message [%d min] sender=\"%s\" text=\"%s\""),
				       Entry.IntervalMinutes, *Entry.SenderName, *Entry.Message);
			}
		}
	}

	UE_LOG(LogInGameMessagesConfig, Log,
	       TEXT("InGameMessages: Enabled=%s  DefaultSenderName=\"%s\"  Messages=%d"),
	       Out.bEnabled ? TEXT("True") : TEXT("False"),
	       *Out.DefaultSenderName,
	       Out.Messages.Num());

	// -- Write backup ---------------------------------------------------------
	{
		FString BackupContent =
			FString(TEXT("[InGameMessages]\n"))
			+ TEXT("# Auto-generated backup of DefaultInGameMessages.ini.\n")
			+ TEXT("# This file is read automatically when the primary config has no [InGameMessages] section.\n")
			+ TEXT("Enabled=") + (Out.bEnabled ? TEXT("True") : TEXT("False")) + TEXT("\n")
			+ TEXT("DefaultSenderName=") + Out.DefaultSenderName + TEXT("\n");

		// Escape embedded double-quotes in string fields to prevent INI parse
		// corruption: ExtractQuotedField() searches for the closing " and would
		// stop prematurely on an unescaped " inside the value.
		auto EscapeIniStr = [](const FString& S) -> FString
		{
			return S.Replace(TEXT("\""), TEXT("\\\""));
		};
		for (const FInGameBroadcastMessage& M : Out.Messages)
		{
			BackupContent += FString::Printf(
				TEXT("+Messages=(IntervalMinutes=%d,SenderName=\"%s\",Message=\"%s\")\n"),
				M.IntervalMinutes, *EscapeIniStr(M.SenderName), *EscapeIniStr(M.Message));
		}

		PF.CreateDirectoryTree(*FPaths::GetPath(BackupPath));
		if (FFileHelper::SaveStringToFile(BackupContent, *BackupPath,
			FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
		{
			UE_LOG(LogInGameMessagesConfig, Log,
			       TEXT("InGameMessages: Updated backup config at '%s'."), *BackupPath);
		}
		else
		{
			UE_LOG(LogInGameMessagesConfig, Warning,
			       TEXT("InGameMessages: Could not write backup config to '%s'."), *BackupPath);
		}
	}

	return Out;
}

// -----------------------------------------------------------------------------
// Template restoration
// -----------------------------------------------------------------------------

void FInGameMessagesConfig::RestoreDefaultConfigIfNeeded()
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
		TEXT("# DiscordBridge - In-Game Broadcast Messages\n")
		TEXT("# -----------------------------------------------------------------------------\n")
		TEXT("# Scheduled messages that the bot broadcasts to in-game chat on a timer.\n")
		TEXT("# Add as many +Messages entries as you like - each one runs on its own\n")
		TEXT("# independent timer.  Messages can contain web links, server invite links,\n")
		TEXT("# and emoji characters (Unicode or copy-paste from Discord).\n")
		TEXT("#\n")
		TEXT("# This file is NOT overwritten by mod updates, so your messages persist\n")
		TEXT("#   across version upgrades. A backup is written automatically to\n")
		TEXT("#   <ServerRoot>/FactoryGame/Saved/DiscordBridge/InGameMessages.ini\n")
		TEXT("#   on every server start so messages survive primary file deletion.\n")
		TEXT("# To apply changes: restart the server (or delete this file to regenerate it).\n")
		TEXT("\n")
		TEXT("[InGameMessages]\n")
		TEXT("\n")
		TEXT("Enabled=True\n")
		TEXT("# Master switch — set to False to disable all scheduled in-game messages.\n")
		TEXT("\n")
		TEXT("DefaultSenderName=[Server]\n")
		TEXT("# Default sender name shown in chat when a message entry omits SenderName.\n")
		TEXT("\n")
		TEXT("# -- MESSAGE FORMAT -------------------------------------------------------------\n")
		TEXT("#\n")
		TEXT("# Each +Messages entry has three fields:\n")
		TEXT("#   IntervalMinutes  - How often (in minutes) this message is sent. Required.\n")
		TEXT("#   SenderName       - Name shown in chat (e.g. \"[Server]\"). Optional, uses DefaultSenderName.\n")
		TEXT("#   Message          - The text to broadcast. Required. Supports:\n")
		TEXT("#                      - Web links:    https://example.com\n")
		TEXT("#                      - Discord links: https://discord.gg/yourserver\n")
		TEXT("#                      - Emoji:        Copy-paste Unicode emoji directly\n")
		TEXT("#\n")
		TEXT("# -- EXAMPLES -------------------------------------------------------------------\n")
		TEXT("#\n")
		TEXT("#   +Messages=(IntervalMinutes=15,SenderName=\"[Server]\",Message=\"Welcome! Check the rules at https://example.com/rules\")\n")
		TEXT("#   +Messages=(IntervalMinutes=30,SenderName=\"[Admin]\",Message=\"Join our Discord: https://discord.gg/yourserver\")\n")
		TEXT("#   +Messages=(IntervalMinutes=60,Message=\"Remember to save your game!\")\n");

	PF.CreateDirectoryTree(*FPaths::GetPath(PrimaryPath));
	if (FFileHelper::SaveStringToFile(Template, *PrimaryPath,
		FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
	{
		UE_LOG(LogInGameMessagesConfig, Log,
		       TEXT("InGameMessages: Created annotated config template at '%s'. "
		            "Uncomment +Messages lines and restart to enable broadcast messages."),
		       *PrimaryPath);
	}
	else
	{
		UE_LOG(LogInGameMessagesConfig, Warning,
		       TEXT("InGameMessages: Could not write config template to '%s'."), *PrimaryPath);
	}
}
