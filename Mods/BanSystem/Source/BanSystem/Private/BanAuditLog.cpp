// Copyright Yamahasxviper. All Rights Reserved.

#include "BanAuditLog.h"
#include "BanSystemConfig.h"
#include "ModLoading/ModLoadingLibrary.h"

#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFileManager.h"
#include "HAL/FileManager.h"

DEFINE_LOG_CATEGORY(LogBanAuditLog);

// ─────────────────────────────────────────────────────────────────────────────
//  USubsystem lifecycle
// ─────────────────────────────────────────────────────────────────────────────

void UBanAuditLog::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    FilePath = GetRegistryPath();

    const FString Dir = FPaths::GetPath(FilePath);
    IPlatformFile& PF = FPlatformFileManager::Get().GetPlatformFile();
    if (!PF.DirectoryExists(*Dir))
        PF.CreateDirectoryTree(*Dir);

    LoadFromFile();

    // Cache the BanSystem mod version once so every audit entry records
    // which build of the mod performed the action.  This is done via SML's
    // UModLoadingLibrary, which is a GameInstanceSubsystem and is always
    // available by the time our Initialize() runs.
    if (UGameInstance* GI = GetGameInstance())
    {
        if (UModLoadingLibrary* ModLib = GI->GetSubsystem<UModLoadingLibrary>())
        {
            FModInfo ModInfo;
            if (ModLib->GetLoadedModInfo(TEXT("BanSystem"), ModInfo))
                CachedModVersion = ModInfo.Version.ToString();
        }
    }

    UE_LOG(LogBanAuditLog, Log,
        TEXT("BanAuditLog: loaded %s (%d entry/entries)"),
        *FilePath, Entries.Num());
}

void UBanAuditLog::Deinitialize()
{
    Super::Deinitialize();
}

// ─────────────────────────────────────────────────────────────────────────────
//  Public API
// ─────────────────────────────────────────────────────────────────────────────

void UBanAuditLog::LogAction(const FString& Action,
                             const FString& TargetUid,  const FString& TargetName,
                             const FString& AdminUid,   const FString& AdminName,
                             const FString& Details)
{
    FScopeLock Lock(&Mutex);

    // Guard: if all 64-bit IDs have been exhausted NextId is set to 0 (the
    // exhausted sentinel) and no new entries should be allocated.
    if (NextId == 0)
    {
        UE_LOG(LogBanAuditLog, Error,
            TEXT("BanAuditLog: all 64-bit IDs have been used — cannot log action '%s'"), *Action);
        return;
    }

    FAuditEntry Entry;
    Entry.Id         = NextId;
    NextId           = (NextId < INT64_MAX) ? NextId + 1 : 0; // 0 = exhausted
    Entry.Action     = Action;
    Entry.TargetUid  = TargetUid;
    Entry.TargetName = TargetName;
    Entry.AdminUid   = AdminUid;
    Entry.AdminName  = AdminName;
    Entry.Details    = Details;
    Entry.ModVersion = CachedModVersion;
    Entry.Timestamp  = FDateTime::UtcNow();

    Entries.Add(Entry);

    // Trim oldest entries when the cap is exceeded.
    if (Entries.Num() > MaxEntries)
    {
        const int32 ToRemove = Entries.Num() - MaxEntries;
        Entries.RemoveAt(0, ToRemove);
    }

    if (!SaveToFile())
    {
        UE_LOG(LogBanAuditLog, Error,
            TEXT("BanAuditLog: failed to save after logging '%s' for '%s'"),
            *Action, *TargetUid);
    }
}

TArray<FAuditEntry> UBanAuditLog::GetRecentEntries(int32 Limit) const
{
    FScopeLock Lock(&Mutex);

    // A limit of 0 or negative is treated as "return nothing".
    if (Limit <= 0) return {};

    // Return newest-first up to Limit entries.
    TArray<FAuditEntry> Result;
    const int32 Total = Entries.Num();
    const int32 Start = FMath::Max(0, Total - Limit);
    for (int32 i = Total - 1; i >= Start; --i)
        Result.Add(Entries[i]);
    return Result;
}

TArray<FAuditEntry> UBanAuditLog::GetEntriesForTarget(const FString& TargetUid) const
{
    FScopeLock Lock(&Mutex);

    TArray<FAuditEntry> Result;
    for (int32 i = Entries.Num() - 1; i >= 0; --i)
    {
        if (Entries[i].TargetUid.Equals(TargetUid, ESearchCase::IgnoreCase))
            Result.Add(Entries[i]);
    }
    return Result;
}

TArray<FAuditEntry> UBanAuditLog::GetAllEntries() const
{
    FScopeLock Lock(&Mutex);
    return Entries;
}

// ─────────────────────────────────────────────────────────────────────────────
//  File I/O
// ─────────────────────────────────────────────────────────────────────────────

void UBanAuditLog::LoadFromFile()
{
    FScopeLock Lock(&Mutex);
    Entries.Empty();

    FString RawJson;
    if (!FFileHelper::LoadFileToString(RawJson, *FilePath))
        return; // File doesn't exist yet — first run.

    TSharedPtr<FJsonObject> Root;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(RawJson);
    if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
    {
        UE_LOG(LogBanAuditLog, Warning,
            TEXT("BanAuditLog: failed to parse %s — starting empty"), *FilePath);
        return;
    }

    const TArray<TSharedPtr<FJsonValue>>* Arr = nullptr;
    if (Root->TryGetArrayField(TEXT("entries"), Arr) && Arr)
    {
        for (const TSharedPtr<FJsonValue>& Val : *Arr)
        {
            if (!Val.IsValid()) continue;
            const TSharedPtr<FJsonObject>* ObjPtr = nullptr;
            if (!Val->TryGetObject(ObjPtr) || !ObjPtr) continue;

            FAuditEntry Entry;
            {
                FString IdStr;
                double IdDbl = 0.0;
                if ((*ObjPtr)->TryGetStringField(TEXT("id"), IdStr)
                    && IdStr.IsNumeric() && IdStr.Len() <= 19
                    && (IdStr.Len() < 19 || IdStr <= TEXT("9223372036854775807")))
                    Entry.Id = FCString::Atoi64(*IdStr);
                else if ((*ObjPtr)->TryGetNumberField(TEXT("id"), IdDbl)
                    && IdDbl >= 1.0 && IdDbl < static_cast<double>(INT64_MAX))
                    Entry.Id = static_cast<int64>(IdDbl);
            }
            (*ObjPtr)->TryGetStringField(TEXT("action"),     Entry.Action);
            (*ObjPtr)->TryGetStringField(TEXT("targetUid"),  Entry.TargetUid);
            (*ObjPtr)->TryGetStringField(TEXT("targetName"), Entry.TargetName);
            (*ObjPtr)->TryGetStringField(TEXT("adminUid"),   Entry.AdminUid);
            (*ObjPtr)->TryGetStringField(TEXT("adminName"),  Entry.AdminName);
            (*ObjPtr)->TryGetStringField(TEXT("details"),    Entry.Details);
            (*ObjPtr)->TryGetStringField(TEXT("modVersion"), Entry.ModVersion);

            FString TimestampStr;
            if ((*ObjPtr)->TryGetStringField(TEXT("timestamp"), TimestampStr))
            {
                if (!FDateTime::ParseIso8601(*TimestampStr, Entry.Timestamp))
                {
                    UE_LOG(LogBanAuditLog, Warning,
                        TEXT("BanAuditLog: entry id=%lld has malformed timestamp '%s' — skipping"),
                        Entry.Id, *TimestampStr);
                    continue;
                }
            }

            if (!Entry.Action.IsEmpty())
                Entries.Add(Entry);
        }
    }

    // Trim on load in case the file was edited externally and exceeds the cap.
    if (Entries.Num() > MaxEntries)
    {
        const int32 ToRemove = Entries.Num() - MaxEntries;
        Entries.RemoveAt(0, ToRemove);
    }

    // Restore counter: prefer the persisted nextId (avoids O(n) scan on large
    // logs and also handles the case where all entries were externally removed).
    {
        int64 ParsedNextId = 0;
        FString NextIdStr;
        double StoredNextId = 0.0;
        if (Root->TryGetStringField(TEXT("nextId"), NextIdStr) && !NextIdStr.IsEmpty()
            && NextIdStr.IsNumeric() && NextIdStr.Len() <= 19
            && (NextIdStr.Len() < 19 || NextIdStr <= TEXT("9223372036854775807")))
            ParsedNextId = FCString::Atoi64(*NextIdStr);
        else if (Root->TryGetNumberField(TEXT("nextId"), StoredNextId)
            && StoredNextId >= 1.0 && StoredNextId < static_cast<double>(INT64_MAX))
            ParsedNextId = static_cast<int64>(StoredNextId);

        if (ParsedNextId >= 1)
            NextId = ParsedNextId;
        else
        {
            // Fallback: derive from loaded entries.
            NextId = 1;
            for (const FAuditEntry& E : Entries)
                if (E.Id >= NextId) NextId = (E.Id < INT64_MAX) ? E.Id + 1 : 0; // 0 = exhausted
        }
    }
}

bool UBanAuditLog::SaveToFile() const
{
    // Caller must already hold Mutex.
    TArray<TSharedPtr<FJsonValue>> EntryArr;
    EntryArr.Reserve(Entries.Num());
    for (const FAuditEntry& E : Entries)
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("id"),         FString::Printf(TEXT("%lld"), E.Id));
        Obj->SetStringField(TEXT("action"),     E.Action);
        Obj->SetStringField(TEXT("targetUid"),  E.TargetUid);
        Obj->SetStringField(TEXT("targetName"), E.TargetName);
        Obj->SetStringField(TEXT("adminUid"),   E.AdminUid);
        Obj->SetStringField(TEXT("adminName"),  E.AdminName);
        Obj->SetStringField(TEXT("details"),    E.Details);
        if (!E.ModVersion.IsEmpty())
            Obj->SetStringField(TEXT("modVersion"), E.ModVersion);
        Obj->SetStringField(TEXT("timestamp"),  E.Timestamp.ToIso8601());
        EntryArr.Add(MakeShared<FJsonValueObject>(Obj));
    }

    TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
    Root->SetStringField(TEXT("nextId"),  FString::Printf(TEXT("%lld"), NextId));
    Root->SetArrayField(TEXT("entries"), EntryArr);

    FString JsonStr;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonStr);
    if (!FJsonSerializer::Serialize(Root.ToSharedRef(), Writer))
    {
        UE_LOG(LogBanAuditLog, Error,
            TEXT("BanAuditLog: failed to serialize entries"));
        return false;
    }

    const FString TmpPath = FilePath + TEXT(".tmp");
    if (!FFileHelper::SaveStringToFile(JsonStr, *TmpPath,
        FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
    {
        UE_LOG(LogBanAuditLog, Error,
            TEXT("BanAuditLog: failed to write temp file %s"), *TmpPath);
        return false;
    }
    if (!IFileManager::Get().Move(*FilePath, *TmpPath, /*bReplace=*/true))
    {
        UE_LOG(LogBanAuditLog, Error,
            TEXT("BanAuditLog: failed to replace %s with temp file"), *FilePath);
        IFileManager::Get().Delete(*TmpPath);
        return false;
    }
    return true;
}

FString UBanAuditLog::GetRegistryPath() const
{
    const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
    FString BaseDir;
    if (Cfg && !Cfg->DatabasePath.IsEmpty())
        BaseDir = FPaths::GetPath(Cfg->DatabasePath);
    else
        BaseDir = FPaths::ProjectSavedDir() / TEXT("BanSystem");

    return BaseDir / TEXT("audit_log.json");
}
