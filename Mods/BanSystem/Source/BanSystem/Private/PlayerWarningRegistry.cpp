// Copyright Yamahasxviper. All Rights Reserved.

#include "PlayerWarningRegistry.h"
#include "BanSystemConfig.h"

#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFileManager.h"
#include "HAL/FileManager.h"

DEFINE_LOG_CATEGORY(LogPlayerWarningRegistry);

// Static delegate definition.
UPlayerWarningRegistry::FOnWarningAdded UPlayerWarningRegistry::OnWarningAdded;

// ─────────────────────────────────────────────────────────────────────────────
//  USubsystem lifecycle
// ─────────────────────────────────────────────────────────────────────────────

void UPlayerWarningRegistry::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    FilePath = GetRegistryPath();

    const FString Dir = FPaths::GetPath(FilePath);
    IPlatformFile& PF = FPlatformFileManager::Get().GetPlatformFile();
    if (!PF.DirectoryExists(*Dir))
        PF.CreateDirectoryTree(*Dir);

    LoadFromFile();

    UE_LOG(LogPlayerWarningRegistry, Log,
        TEXT("PlayerWarningRegistry: loaded %s (%d warning(s))"),
        *FilePath, Warnings.Num());
}

void UPlayerWarningRegistry::Deinitialize()
{
    Super::Deinitialize();
}

// ─────────────────────────────────────────────────────────────────────────────
//  Public API
// ─────────────────────────────────────────────────────────────────────────────

void UPlayerWarningRegistry::AddWarning(const FString& Uid, const FString& PlayerName,
                                        const FString& Reason, const FString& WarnedBy)
{
    if (Uid.IsEmpty()) return;

    FWarningEntry Entry;
    {
        FScopeLock Lock(&Mutex);

        if (NextId == 0)
        {
            UE_LOG(LogPlayerWarningRegistry, Error,
                TEXT("PlayerWarningRegistry: all 64-bit IDs have been used — cannot add more warnings"));
            return;
        }
        Entry.Id         = NextId;
        NextId           = (NextId < INT64_MAX) ? NextId + 1 : 0; // 0 = exhausted
        Entry.Uid        = Uid;
        Entry.PlayerName = PlayerName;
        Entry.Reason     = Reason;
        Entry.WarnedBy   = WarnedBy;
        Entry.WarnDate   = FDateTime::UtcNow();
        Entry.Points     = 1;

        Warnings.Add(Entry);
        if (!SaveToFile())
        {
            UE_LOG(LogPlayerWarningRegistry, Error,
                TEXT("PlayerWarningRegistry: failed to save after adding warning id=%lld for uid='%s'"),
                Entry.Id, *Entry.Uid);
        }
    }

    // Broadcast outside the lock so listeners can safely call back into the registry.
    OnWarningAdded.Broadcast(Entry);
}

FWarningEntry UPlayerWarningRegistry::AddWarning(const FWarningEntry& InEntry)
{
    if (InEntry.Uid.IsEmpty()) return FWarningEntry();

    FWarningEntry Entry;
    {
        FScopeLock Lock(&Mutex);

        Entry = InEntry;
        if (NextId == 0)
        {
            UE_LOG(LogPlayerWarningRegistry, Error,
                TEXT("PlayerWarningRegistry: all 64-bit IDs have been used — cannot add more warnings"));
            return FWarningEntry();
        }
        Entry.Id       = NextId;
        NextId         = (NextId < INT64_MAX) ? NextId + 1 : 0; // 0 = exhausted
        Entry.WarnDate = FDateTime::UtcNow();

        Warnings.Add(Entry);
        if (!SaveToFile())
        {
            UE_LOG(LogPlayerWarningRegistry, Error,
                TEXT("PlayerWarningRegistry: failed to save after adding warning id=%lld for uid='%s'"),
                Entry.Id, *Entry.Uid);
        }
    }

    // Broadcast outside the lock so listeners can safely call back into the registry.
    OnWarningAdded.Broadcast(Entry);
    return Entry;
}

TArray<FWarningEntry> UPlayerWarningRegistry::GetWarningsForUid(const FString& Uid) const
{
    FScopeLock Lock(&Mutex);

    TArray<FWarningEntry> Result;
    for (const FWarningEntry& W : Warnings)
    {
        if (W.Uid.Equals(Uid, ESearchCase::IgnoreCase))
            Result.Add(W);
    }
    return Result;
}

int32 UPlayerWarningRegistry::ClearWarningsForUid(const FString& Uid)
{
    FScopeLock Lock(&Mutex);

    const int32 Before = Warnings.Num();
    Warnings.RemoveAll([&Uid](const FWarningEntry& W)
    {
        return W.Uid.Equals(Uid, ESearchCase::IgnoreCase);
    });
    const int32 Removed = Before - Warnings.Num();

    if (Removed > 0)
    {
        if (!SaveToFile())
        {
            UE_LOG(LogPlayerWarningRegistry, Error,
                TEXT("PlayerWarningRegistry: failed to save after clearing warnings for uid='%s'"),
                *Uid);
        }
    }

    return Removed;
}

TArray<FWarningEntry> UPlayerWarningRegistry::GetAllWarnings() const
{
    FScopeLock Lock(&Mutex);
    return Warnings;
}

int32 UPlayerWarningRegistry::GetWarningCount(const FString& Uid) const
{
    FScopeLock Lock(&Mutex);

    const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
    const int32 DecayDays = Cfg ? Cfg->WarnDecayDays : 0;
    const FDateTime DecayCutoff = (DecayDays > 0)
        ? FDateTime::UtcNow() - FTimespan::FromDays(static_cast<double>(DecayDays))
        : FDateTime::MinValue();

    int32 Count = 0;
    for (const FWarningEntry& W : Warnings)
    {
        if (!W.Uid.Equals(Uid, ESearchCase::IgnoreCase)) continue;
        if (W.IsExpired()) continue;
        if (DecayDays > 0 && W.WarnDate < DecayCutoff) continue;
        ++Count;
    }
    return Count;
}

void UPlayerWarningRegistry::AddWarning(const FString& Uid, const FString& PlayerName,
                                         const FString& Reason, const FString& WarnedBy,
                                         int32 ExpiryMinutes)
{
    AddWarning(Uid, PlayerName, Reason, WarnedBy, ExpiryMinutes, 1);
}

void UPlayerWarningRegistry::AddWarning(const FString& Uid, const FString& PlayerName,
                                         const FString& Reason, const FString& WarnedBy,
                                         int32 ExpiryMinutes, int32 Points)
{
    if (Uid.IsEmpty()) return;

    FWarningEntry Entry;
    {
        FScopeLock Lock(&Mutex);

        if (NextId == 0)
        {
            UE_LOG(LogPlayerWarningRegistry, Error,
                TEXT("PlayerWarningRegistry: all 64-bit IDs have been used — cannot add more warnings"));
            return;
        }
        Entry.Id         = NextId;
        NextId           = (NextId < INT64_MAX) ? NextId + 1 : 0; // 0 = exhausted
        Entry.Uid        = Uid;
        Entry.PlayerName = PlayerName;
        Entry.Reason     = Reason;
        Entry.WarnedBy   = WarnedBy;
        Entry.WarnDate   = FDateTime::UtcNow();
        const FDateTime WarnNow = Entry.WarnDate;
        Entry.Points     = FMath::Max(1, Points);
        if (ExpiryMinutes > 0)
        {
            Entry.bHasExpiry  = true;
            Entry.ExpireDate  = WarnNow + FTimespan::FromMinutes(ExpiryMinutes);
        }

        Warnings.Add(Entry);
        if (!SaveToFile())
        {
            UE_LOG(LogPlayerWarningRegistry, Error,
                TEXT("PlayerWarningRegistry: failed to save after adding warning id=%lld for uid='%s'"),
                Entry.Id, *Entry.Uid);
        }
    }

    // Broadcast outside the lock so listeners can safely call back into the registry.
    OnWarningAdded.Broadcast(Entry);
}

int32 UPlayerWarningRegistry::GetWarningPoints(const FString& Uid) const
{
    FScopeLock Lock(&Mutex);

    const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
    const int32 DecayDays = Cfg ? Cfg->WarnDecayDays : 0;
    const FDateTime DecayCutoff = (DecayDays > 0)
        ? FDateTime::UtcNow() - FTimespan::FromDays(static_cast<double>(DecayDays))
        : FDateTime::MinValue();

    int32 TotalPoints = 0;
    for (const FWarningEntry& W : Warnings)
    {
        if (!W.Uid.Equals(Uid, ESearchCase::IgnoreCase)) continue;
        if (W.IsExpired()) continue;
        if (DecayDays > 0 && W.WarnDate < DecayCutoff) continue;
        TotalPoints += FMath::Max(1, W.Points);
    }
    return TotalPoints;
}

int32 UPlayerWarningRegistry::PruneExpiredWarnings()
{
    FScopeLock Lock(&Mutex);

    const int32 Before = Warnings.Num();
    Warnings.RemoveAll([](const FWarningEntry& W) -> bool
    {
        return W.bHasExpiry && W.IsExpired();
    });
    const int32 Removed = Before - Warnings.Num();

    if (Removed > 0)
    {
        if (!SaveToFile())
        {
            UE_LOG(LogPlayerWarningRegistry, Error,
                TEXT("PlayerWarningRegistry: failed to save after pruning %d expired warning(s)"), Removed);
        }
        UE_LOG(LogPlayerWarningRegistry, Log,
            TEXT("PlayerWarningRegistry: pruned %d expired warning(s)."), Removed);
    }

    return Removed;
}

bool UPlayerWarningRegistry::DeleteWarningById(int64 Id)
{
    FScopeLock Lock(&Mutex);

    const int32 Before = Warnings.Num();
    Warnings.RemoveAll([Id](const FWarningEntry& W) { return W.Id == Id; });
    const bool bRemoved = Warnings.Num() < Before;

    if (bRemoved)
    {
        if (!SaveToFile())
        {
            UE_LOG(LogPlayerWarningRegistry, Error,
                TEXT("PlayerWarningRegistry: failed to save after deleting warning id=%lld"), Id);
        }
    }

    return bRemoved;
}

// ─────────────────────────────────────────────────────────────────────────────
//  File I/O
// ─────────────────────────────────────────────────────────────────────────────

void UPlayerWarningRegistry::LoadFromFile()
{
    FScopeLock Lock(&Mutex);
    Warnings.Empty();

    FString RawJson;
    if (!FFileHelper::LoadFileToString(RawJson, *FilePath))
        return; // File doesn't exist yet — first run.

    TSharedPtr<FJsonObject> Root;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(RawJson);
    if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
    {
        UE_LOG(LogPlayerWarningRegistry, Warning,
            TEXT("PlayerWarningRegistry: failed to parse %s — starting empty"), *FilePath);
        return;
    }

    const TArray<TSharedPtr<FJsonValue>>* Arr = nullptr;
    if (Root->TryGetArrayField(TEXT("warnings"), Arr) && Arr)
    {
        for (const TSharedPtr<FJsonValue>& Val : *Arr)
        {
            if (!Val.IsValid()) continue;
            const TSharedPtr<FJsonObject>* ObjPtr = nullptr;
            if (!Val->TryGetObject(ObjPtr) || !ObjPtr) continue;

            FWarningEntry Entry;
            {
                FString IdStr;
                double IdDbl = 0.0;
                if ((*ObjPtr)->TryGetStringField(TEXT("id"), IdStr))
                    Entry.Id = FCString::Atoi64(*IdStr);
                else if ((*ObjPtr)->TryGetNumberField(TEXT("id"), IdDbl)
                    && IdDbl >= 1.0 && IdDbl < static_cast<double>(INT64_MAX))
                    Entry.Id = static_cast<int64>(IdDbl);
            }
            (*ObjPtr)->TryGetStringField(TEXT("uid"),        Entry.Uid);
            (*ObjPtr)->TryGetStringField(TEXT("playerName"), Entry.PlayerName);
            (*ObjPtr)->TryGetStringField(TEXT("reason"),     Entry.Reason);
            (*ObjPtr)->TryGetStringField(TEXT("warnedBy"),   Entry.WarnedBy);

            FString WarnDateStr;
            if ((*ObjPtr)->TryGetStringField(TEXT("warnDate"), WarnDateStr))
            {
                if (!FDateTime::ParseIso8601(*WarnDateStr, Entry.WarnDate))
                {
                    UE_LOG(LogPlayerWarningRegistry, Warning,
                        TEXT("PlayerWarningRegistry: uid='%s' has malformed warnDate '%s' — skipping entry"),
                        *Entry.Uid, *WarnDateStr);
                    continue;
                }
            }

            (*ObjPtr)->TryGetBoolField(TEXT("hasExpiry"), Entry.bHasExpiry);
            FString ExpireDateStr;
            if ((*ObjPtr)->TryGetStringField(TEXT("expireDate"), ExpireDateStr) && !ExpireDateStr.IsEmpty())
            {
                if (!FDateTime::ParseIso8601(*ExpireDateStr, Entry.ExpireDate))
                {
                    UE_LOG(LogPlayerWarningRegistry, Warning,
                        TEXT("PlayerWarningRegistry: uid='%s' has malformed expireDate '%s' — skipping entry"),
                        *Entry.Uid, *ExpireDateStr);
                    continue;
                }
            }

            // Points (default 1 for records written before this feature).
            double PointsDbl = 1.0;
            if ((*ObjPtr)->TryGetNumberField(TEXT("points"), PointsDbl) && PointsDbl >= 1.0)
                Entry.Points = static_cast<int32>(PointsDbl);

            if (!Entry.Uid.IsEmpty())
                Warnings.Add(Entry);
        }
    }

    // Restore the NextId counter.  Prefer the persisted "nextId" field (written
    // since BUG-08 fix) over the scan-based reconstruction so that deleting the
    // entry that happened to hold the highest Id does not regress the counter and
    // cause duplicate-Id allocation.  Fall back to the scan for files written by
    // older builds that did not persist nextId.
    FString StoredNextIdStr;
    double  StoredNextIdDbl = 0.0;
    if (Root->TryGetStringField(TEXT("nextId"), StoredNextIdStr) && !StoredNextIdStr.IsEmpty())
    {
        const int64 Parsed = FCString::Atoi64(*StoredNextIdStr);
        NextId = (Parsed > 0) ? Parsed : 1;
    }
    else if (Root->TryGetNumberField(TEXT("nextId"), StoredNextIdDbl) && StoredNextIdDbl >= 1.0)
    {
        NextId = static_cast<int64>(StoredNextIdDbl);
    }
    else
    {
        // Legacy files without a nextId field: reconstruct from the max stored Id.
        NextId = 1;
        for (const FWarningEntry& W : Warnings)
            if (W.Id >= NextId) NextId = (W.Id < INT64_MAX) ? W.Id + 1 : 0;
    }
}

bool UPlayerWarningRegistry::SaveToFile() const
{
    // Caller must already hold Mutex.
    TArray<TSharedPtr<FJsonValue>> WarningArr;
    WarningArr.Reserve(Warnings.Num());
    for (const FWarningEntry& W : Warnings)
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("id"),         FString::Printf(TEXT("%lld"), W.Id));
        Obj->SetStringField(TEXT("uid"),        W.Uid);
        Obj->SetStringField(TEXT("playerName"), W.PlayerName);
        Obj->SetStringField(TEXT("reason"),     W.Reason);
        Obj->SetStringField(TEXT("warnedBy"),   W.WarnedBy);
        Obj->SetStringField(TEXT("warnDate"),   W.WarnDate.ToIso8601());
        Obj->SetBoolField  (TEXT("hasExpiry"),  W.bHasExpiry);
        Obj->SetStringField(TEXT("expireDate"), W.bHasExpiry ? W.ExpireDate.ToIso8601() : TEXT(""));
        Obj->SetNumberField(TEXT("points"),     static_cast<double>(W.Points > 0 ? W.Points : 1));
        WarningArr.Add(MakeShared<FJsonValueObject>(Obj));
    }

    TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
    Root->SetStringField(TEXT("nextId"),  FString::Printf(TEXT("%lld"), NextId));
    Root->SetArrayField(TEXT("warnings"), WarningArr);

    FString JsonStr;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonStr);
    if (!FJsonSerializer::Serialize(Root.ToSharedRef(), Writer))
    {
        UE_LOG(LogPlayerWarningRegistry, Error,
            TEXT("PlayerWarningRegistry: failed to serialize warnings"));
        return false;
    }

    const FString TmpPath = FilePath + TEXT(".tmp");
    if (!FFileHelper::SaveStringToFile(JsonStr, *TmpPath,
        FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
    {
        UE_LOG(LogPlayerWarningRegistry, Error,
            TEXT("PlayerWarningRegistry: failed to write temp file %s"), *TmpPath);
        return false;
    }
    if (!IFileManager::Get().Move(*FilePath, *TmpPath, /*bReplace=*/true))
    {
        UE_LOG(LogPlayerWarningRegistry, Error,
            TEXT("PlayerWarningRegistry: failed to replace %s with temp file"), *FilePath);
        IFileManager::Get().Delete(*TmpPath);
        return false;
    }
    return true;
}

FString UPlayerWarningRegistry::GetRegistryPath() const
{
    const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
    FString BaseDir;
    if (Cfg && !Cfg->DatabasePath.IsEmpty())
        BaseDir = FPaths::GetPath(Cfg->DatabasePath);
    else
        BaseDir = FPaths::ProjectSavedDir() / TEXT("BanSystem");

    return BaseDir / TEXT("warnings.json");
}
