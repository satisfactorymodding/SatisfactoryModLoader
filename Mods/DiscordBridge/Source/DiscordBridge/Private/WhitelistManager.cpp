// Copyright Yamahasxviper. All Rights Reserved.

#include "WhitelistManager.h"
#include "Logging/LogMacros.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

DEFINE_LOG_CATEGORY_STATIC(LogWhitelistManager, Log, All);

// ---------------------------------------------------------------------------
// Static member definitions
// ---------------------------------------------------------------------------
bool                           FWhitelistManager::bEnabled  = false;
TArray<FWhitelistEntry>        FWhitelistManager::Entries;
TArray<FWhitelistAuditEntry>   FWhitelistManager::AuditLog;
int32                          FWhitelistManager::MaxSlots  = 0;
FCriticalSection               FWhitelistManager::Mutex;

// ---------------------------------------------------------------------------
// Internal helpers
// ---------------------------------------------------------------------------

FString FWhitelistManager::GetFilePath()
{
	return FPaths::ProjectSavedDir() / TEXT("DiscordBridge") / TEXT("ServerWhitelist.json");
}

// ---------------------------------------------------------------------------
// Public API
// ---------------------------------------------------------------------------

void FWhitelistManager::Load(bool bDefaultEnabled)
{
	FScopeLock Lock(&Mutex);
	const FString FilePath = GetFilePath();

	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
	{
		bEnabled = bDefaultEnabled;
		UE_LOG(LogWhitelistManager, Display,
			TEXT("Whitelist file not found — creating default at %s (enabled=%s)"),
			*FilePath, bEnabled ? TEXT("true") : TEXT("false"));
		Save_Locked();
		return;
	}

	FString RawJson;
	if (!FFileHelper::LoadFileToString(RawJson, *FilePath))
	{
		UE_LOG(LogWhitelistManager, Error,
			TEXT("Failed to read whitelist from %s"), *FilePath);
		return;
	}

	TSharedPtr<FJsonObject> Root;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(RawJson);
	if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
	{
		UE_LOG(LogWhitelistManager, Warning,
			TEXT("Whitelist JSON is malformed — resetting to defaults"));
		bEnabled = bDefaultEnabled;
		Entries.Empty();
		Save_Locked();
		return;
	}

	// Restore the runtime-toggled enabled state from JSON (overrides the ini default).
	Root->TryGetBoolField(TEXT("enabled"), bEnabled);

	// Load max_slots
	double MaxSlotsD = 0.0;
	if (Root->TryGetNumberField(TEXT("max_slots"), MaxSlotsD))
		MaxSlots = (MaxSlotsD >= 0.0 && MaxSlotsD <= static_cast<double>(INT_MAX))
		           ? static_cast<int32>(MaxSlotsD) : 0;

	// Load players array (backward compat: string or object)
	Entries.Empty();
	if (Root->HasTypedField<EJson::Array>(TEXT("players")))
	{
		for (const TSharedPtr<FJsonValue>& Val : Root->GetArrayField(TEXT("players")))
		{
			if (Val->Type == EJson::String)
			{
				// Legacy: plain string — store as-is; comparisons are case-insensitive.
				FWhitelistEntry E;
				E.Name      = Val->AsString();
				E.EosPUID   = TEXT("");
				E.ExpiresAt = FDateTime(0);
				Entries.Add(E);
			}
			else if (Val->Type == EJson::Object)
			{
				const TSharedPtr<FJsonObject>* ObjPtr = nullptr;
				if (Val->TryGetObject(ObjPtr) && ObjPtr)
				{
					FWhitelistEntry E;
					// Store the original display name as loaded; all comparisons use ToLower().
					(*ObjPtr)->TryGetStringField(TEXT("name"), E.Name);
					(*ObjPtr)->TryGetStringField(TEXT("eos_puid"), E.EosPUID);
					(*ObjPtr)->TryGetStringField(TEXT("group"), E.Group);
					FString ExpiresStr;
					(*ObjPtr)->TryGetStringField(TEXT("expires_at"), ExpiresStr);
					if (ExpiresStr.IsEmpty() || !FDateTime::ParseIso8601(*ExpiresStr, E.ExpiresAt))
						E.ExpiresAt = FDateTime(0);
					Entries.Add(E);
				}
			}
		}
	}

	// Load audit log
	AuditLog.Empty();
	if (Root->HasTypedField<EJson::Array>(TEXT("audit_log")))
	{
		for (const TSharedPtr<FJsonValue>& Val : Root->GetArrayField(TEXT("audit_log")))
		{
			const TSharedPtr<FJsonObject>* ObjPtr = nullptr;
			if (!Val->TryGetObject(ObjPtr) || !ObjPtr) continue;

			FWhitelistAuditEntry A;
			FString TsStr;
			(*ObjPtr)->TryGetStringField(TEXT("timestamp"), TsStr);
			if (!TsStr.IsEmpty() && !FDateTime::ParseIso8601(*TsStr, A.Timestamp))
				A.Timestamp = FDateTime(0);
			(*ObjPtr)->TryGetStringField(TEXT("admin"),  A.AdminName);
			(*ObjPtr)->TryGetStringField(TEXT("action"), A.Action);
			(*ObjPtr)->TryGetStringField(TEXT("target"), A.Target);
			AuditLog.Add(A);
		}
	}

	UE_LOG(LogWhitelistManager, Display,
		TEXT("Whitelist loaded: %s, %d player(s)"),
		bEnabled ? TEXT("ENABLED") : TEXT("disabled"),
		Entries.Num());
}

// Internal: caller must already hold Mutex.
static bool WhitelistAtomicSave(const FString& JsonStr, const FString& FilePath)
{
	const FString TmpPath = FilePath + TEXT(".tmp");
	if (!FFileHelper::SaveStringToFile(JsonStr, *TmpPath,
		FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
		return false;
	if (!IFileManager::Get().Move(*FilePath, *TmpPath, /*bReplace=*/true))
	{
		IFileManager::Get().Delete(*TmpPath);
		return false;
	}
	return true;
}

void FWhitelistManager::Save_Locked()
{
	// Caller must already hold Mutex.
	const FString FilePath = GetFilePath();
	FPlatformFileManager::Get().GetPlatformFile().CreateDirectoryTree(*FPaths::GetPath(FilePath));

	const TSharedRef<FJsonObject> Root = MakeShareable(new FJsonObject());
	Root->SetBoolField(TEXT("enabled"), bEnabled);
	Root->SetNumberField(TEXT("max_slots"), MaxSlots);

	TArray<TSharedPtr<FJsonValue>> PlayerArray;
	for (const FWhitelistEntry& E : Entries)
	{
		TSharedPtr<FJsonObject> EntryObj = MakeShared<FJsonObject>();
		EntryObj->SetStringField(TEXT("name"),      E.Name);
		EntryObj->SetStringField(TEXT("eos_puid"),  E.EosPUID);
		EntryObj->SetStringField(TEXT("group"),     E.Group);
		EntryObj->SetStringField(TEXT("expires_at"),
			E.ExpiresAt.GetTicks() > 0 ? E.ExpiresAt.ToIso8601() : FString());
		PlayerArray.Add(MakeShared<FJsonValueObject>(EntryObj));
	}
	Root->SetArrayField(TEXT("players"), PlayerArray);

	// Save audit log
	TArray<TSharedPtr<FJsonValue>> AuditArray;
	for (const FWhitelistAuditEntry& A : AuditLog)
	{
		TSharedPtr<FJsonObject> AObj = MakeShared<FJsonObject>();
		AObj->SetStringField(TEXT("timestamp"), A.Timestamp.ToIso8601());
		AObj->SetStringField(TEXT("admin"),     A.AdminName);
		AObj->SetStringField(TEXT("action"),    A.Action);
		AObj->SetStringField(TEXT("target"),    A.Target);
		AuditArray.Add(MakeShared<FJsonValueObject>(AObj));
	}
	Root->SetArrayField(TEXT("audit_log"), AuditArray);

	FString OutJson;
	const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutJson);
	if (!FJsonSerializer::Serialize(Root, Writer))
	{
		UE_LOG(LogWhitelistManager, Error,
			TEXT("Failed to serialize whitelist JSON — aborting save to avoid data loss"));
		return;
	}

	if (!WhitelistAtomicSave(OutJson, FilePath))
	{
		UE_LOG(LogWhitelistManager, Error,
			TEXT("Failed to save whitelist to %s"), *FilePath);
		return;
	}
	UE_LOG(LogWhitelistManager, Verbose,
		TEXT("Whitelist saved to %s"), *FilePath);
}

void FWhitelistManager::Save()
{
	FScopeLock Lock(&Mutex);
	Save_Locked();
}

bool FWhitelistManager::IsEnabled()
{
	FScopeLock Lock(&Mutex);
	return bEnabled;
}

void FWhitelistManager::SetEnabled(bool bNewEnabled, const FString& AdminName)
{
	FScopeLock Lock(&Mutex);
	bEnabled = bNewEnabled;
	LogAudit(AdminName, bNewEnabled ? TEXT("enable") : TEXT("disable"), TEXT("whitelist"));
	Save_Locked();
}

bool FWhitelistManager::IsWhitelisted(const FString& PlayerName, const FString& EosPUID)
{
	FScopeLock Lock(&Mutex);
	const FDateTime Now = FDateTime::UtcNow();
	for (const FWhitelistEntry& E : Entries)
	{
		// Skip expired entries
		if (E.ExpiresAt.GetTicks() > 0 && E.ExpiresAt <= Now) continue;

		if (E.Name.Equals(PlayerName, ESearchCase::IgnoreCase)) return true;
		if (!EosPUID.IsEmpty() && !E.EosPUID.IsEmpty() && E.EosPUID.Equals(EosPUID, ESearchCase::IgnoreCase)) return true;
	}
	return false;
}

bool FWhitelistManager::IsWhitelistedByPUID(const FString& EosPUID)
{
	FScopeLock Lock(&Mutex);
	if (EosPUID.IsEmpty()) return false;
	const FDateTime Now = FDateTime::UtcNow();
	for (const FWhitelistEntry& E : Entries)
	{
		if (E.ExpiresAt.GetTicks() > 0 && E.ExpiresAt <= Now) continue;
		if (!E.EosPUID.IsEmpty() && E.EosPUID.Equals(EosPUID, ESearchCase::IgnoreCase)) return true;
	}
	return false;
}

bool FWhitelistManager::AddPlayer(const FString& PlayerName,
                                   const FString& EosPUID,
                                   const FString& AdminName,
                                   FDateTime      ExpiresAt,
                                   const FString& Group)
{
	FScopeLock Lock(&Mutex);

	// Capture a single timestamp used for both the capacity check and the
	// duplicate check so both operate against the same instant.
	const FDateTime Now = FDateTime::UtcNow();

	// Capacity check — only count active (non-expired) entries so that
	// expired slots do not permanently consume whitelist capacity.
	if (MaxSlots > 0)
	{
		int32 ActiveCount = 0;
		for (const FWhitelistEntry& E : Entries)
		{
			if (E.ExpiresAt.GetTicks() <= 0 || E.ExpiresAt > Now)
				++ActiveCount;
		}
		if (ActiveCount >= MaxSlots)
			return false;
	}

	// Duplicate check (by name or PUID) — skip expired entries so they can be re-added.
	for (const FWhitelistEntry& E : Entries)
	{
		if (E.ExpiresAt.GetTicks() > 0 && E.ExpiresAt <= Now) continue;
		if (E.Name.Equals(PlayerName, ESearchCase::IgnoreCase)) return false;
		if (!EosPUID.IsEmpty() && !E.EosPUID.IsEmpty() &&
		    E.EosPUID.Equals(EosPUID, ESearchCase::IgnoreCase)) return false;
	}

	FWhitelistEntry NewEntry;
	NewEntry.Name      = PlayerName; // store original casing; comparisons are case-insensitive
	NewEntry.EosPUID   = EosPUID;
	NewEntry.ExpiresAt = ExpiresAt;
	NewEntry.Group     = Group;
	Entries.Add(NewEntry);

	LogAudit(AdminName, TEXT("add"), PlayerName);
	Save_Locked();
	return true;
}

bool FWhitelistManager::RemovePlayer(const FString& PlayerName, const FString& EosPUID, const FString& AdminName)
{
	FScopeLock Lock(&Mutex);

	int32 RemovedIdx = INDEX_NONE;

	if (!EosPUID.IsEmpty())
		RemovedIdx = Entries.IndexOfByPredicate([&EosPUID](const FWhitelistEntry& E)
		{
			return E.EosPUID.Equals(EosPUID, ESearchCase::IgnoreCase);
		});
	else
		RemovedIdx = Entries.IndexOfByPredicate([&PlayerName](const FWhitelistEntry& E)
		{
			return E.Name.Equals(PlayerName, ESearchCase::IgnoreCase);
		});

	if (RemovedIdx == INDEX_NONE) return false;

	const FString RemovedName = Entries[RemovedIdx].Name;
	Entries.RemoveAt(RemovedIdx);
	LogAudit(AdminName, TEXT("remove"), RemovedName);
	Save_Locked();
	return true;
}

TArray<FString> FWhitelistManager::GetAll()
{
	FScopeLock Lock(&Mutex);
	const FDateTime Now = FDateTime::UtcNow();
	TArray<FString> Names;
	for (const FWhitelistEntry& E : Entries)
	{
		// Skip expired entries so callers see only currently active whitelist players.
		if (E.ExpiresAt.GetTicks() > 0 && E.ExpiresAt <= Now) continue;
		Names.Add(E.Name);
	}
	return Names;
}

TArray<FWhitelistEntry> FWhitelistManager::GetAllEntries()
{
	FScopeLock Lock(&Mutex);
	return Entries;
}

void FWhitelistManager::LogAudit(const FString& Admin, const FString& Action, const FString& Target)
{
	// Caller must already hold Mutex.
	FWhitelistAuditEntry Entry;
	Entry.Timestamp = FDateTime::UtcNow();
	Entry.AdminName = Admin;
	Entry.Action    = Action;
	Entry.Target    = Target;
	AuditLog.Add(Entry);

	// Keep max 100 entries — use a single RemoveAt call to avoid O(n²) shifting.
	if (AuditLog.Num() > 100)
		AuditLog.RemoveAt(0, AuditLog.Num() - 100);
}

TArray<FWhitelistAuditEntry> FWhitelistManager::GetAuditLog(int32 MaxEntries)
{
	FScopeLock Lock(&Mutex);
	if (MaxEntries <= 0)  MaxEntries = 20;
	if (MaxEntries > 100) MaxEntries = 100;

	const int32 Total = AuditLog.Num();
	if (Total <= MaxEntries)
		return AuditLog;

	TArray<FWhitelistAuditEntry> Result;
	Result.Reserve(MaxEntries);
	for (int32 i = Total - MaxEntries; i < Total; ++i)
		Result.Add(AuditLog[i]);
	return Result;
}

int32 FWhitelistManager::GetActiveEntryCount()
{
	FScopeLock Lock(&Mutex);
	const FDateTime Now = FDateTime::UtcNow();
	int32 ActiveCount = 0;
	for (const FWhitelistEntry& E : Entries)
	{
		if (E.ExpiresAt.GetTicks() <= 0 || E.ExpiresAt > Now)
			++ActiveCount;
	}
	return ActiveCount;
}

int32 FWhitelistManager::GetMaxSlots()
{
	FScopeLock Lock(&Mutex);
	return MaxSlots;
}

void FWhitelistManager::SetMaxSlots(int32 InMaxSlots)
{
	FScopeLock Lock(&Mutex);
	MaxSlots = InMaxSlots;
}

FTimespan FWhitelistManager::ParseDuration(const FString& DurStr)
{
	if (DurStr.IsEmpty()) return FTimespan::Zero();
	FString Lower = DurStr.ToLower().TrimStartAndEnd();
	if (Lower.EndsWith(TEXT("w")))
	{
		const double Val = FCString::Atod(*Lower.LeftChop(1));
		// FTimespan::FromDays internally casts to int64 — IsFinite guards against Infinity/NaN UB.
		// Cap at 36500 days (~100 years) to prevent absurdly large timespan values.
		return (FMath::IsFinite(Val) && Val > 0.0 && Val <= 36500.0) ? FTimespan::FromDays(Val * 7.0) : FTimespan::Zero();
	}
	if (Lower.EndsWith(TEXT("d")))
	{
		const double Val = FCString::Atod(*Lower.LeftChop(1));
		return (FMath::IsFinite(Val) && Val > 0.0 && Val <= 36500.0) ? FTimespan::FromDays(Val) : FTimespan::Zero();
	}
	if (Lower.EndsWith(TEXT("h")))
	{
		const double Val = FCString::Atod(*Lower.LeftChop(1));
		return (FMath::IsFinite(Val) && Val > 0.0 && Val <= 876000.0) ? FTimespan::FromHours(Val) : FTimespan::Zero();
	}
	if (Lower.EndsWith(TEXT("m")))
	{
		const double Val = FCString::Atod(*Lower.LeftChop(1));
		return (FMath::IsFinite(Val) && Val > 0.0 && Val <= 52560000.0) ? FTimespan::FromMinutes(Val) : FTimespan::Zero();
	}
	return FTimespan::Zero();
}

void FWhitelistManager::RemoveExpiredEntries(TArray<FString>& OutExpiredNames)
{
	FScopeLock Lock(&Mutex);
	OutExpiredNames.Reset(); // ensure callers always get exactly the expired set, not an accumulation
	const FDateTime Now = FDateTime::UtcNow();
	for (const FWhitelistEntry& E : Entries)
		if (E.ExpiresAt.GetTicks() > 0 && E.ExpiresAt <= Now)
			OutExpiredNames.Add(E.Name);

	const int32 Removed = Entries.RemoveAll([&Now](const FWhitelistEntry& E)
	{
		return E.ExpiresAt.GetTicks() > 0 && E.ExpiresAt <= Now;
	});
	if (Removed > 0)
		Save_Locked();
}

TArray<FWhitelistEntry> FWhitelistManager::Search(const FString& PartialName)
{
	FScopeLock Lock(&Mutex);
	TArray<FWhitelistEntry> Result;
	if (PartialName.IsEmpty()) return Result;
	for (const FWhitelistEntry& E : Entries)
	{
		if (E.Name.Contains(PartialName, ESearchCase::IgnoreCase))
			Result.Add(E);
	}
	return Result;
}
