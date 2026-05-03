// Copyright Yamahasxviper. All Rights Reserved.

#include "BanAppealRegistry.h"
#include "BanSystemConfig.h"

#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFileManager.h"
#include "HAL/FileManager.h"

DEFINE_LOG_CATEGORY(LogBanAppealRegistry);

// Static delegate definition.
UBanAppealRegistry::FOnBanAppealSubmitted UBanAppealRegistry::OnBanAppealSubmitted;
UBanAppealRegistry::FOnBanAppealReviewed  UBanAppealRegistry::OnBanAppealReviewed;

// ─────────────────────────────────────────────────────────────────────────────
//  USubsystem lifecycle
// ─────────────────────────────────────────────────────────────────────────────

void UBanAppealRegistry::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    FilePath = GetRegistryPath();

    const FString Dir = FPaths::GetPath(FilePath);
    IPlatformFile& PF = FPlatformFileManager::Get().GetPlatformFile();
    if (!PF.DirectoryExists(*Dir))
        PF.CreateDirectoryTree(*Dir);

    LoadFromFile();

    UE_LOG(LogBanAppealRegistry, Log,
        TEXT("BanAppealRegistry: loaded %s (%d appeal(s))"),
        *FilePath, Appeals.Num());
}

void UBanAppealRegistry::Deinitialize()
{
    Super::Deinitialize();
}

// ─────────────────────────────────────────────────────────────────────────────
//  Public API
// ─────────────────────────────────────────────────────────────────────────────

FBanAppealEntry UBanAppealRegistry::AddAppealIfNoDuplicate(const FString& Uid,
                                                            const FString& Reason,
                                                            const FString& ContactInfo)
{
    FBanAppealEntry Entry;
    bool bBroadcast = false;

    {
        FScopeLock Lock(&Mutex);

        // Check for an existing Pending appeal inside the same lock that adds the new
        // one — eliminates the check-then-act TOCTOU present in GetAllAppeals()+AddAppeal().
        for (const FBanAppealEntry& A : Appeals)
        {
            if (A.Uid.Equals(Uid, ESearchCase::IgnoreCase) && A.Status == EAppealStatus::Pending)
                return FBanAppealEntry{}; // duplicate — return empty entry (Id == 0)
        }

        if (NextId == 0)
        {
            UE_LOG(LogBanAppealRegistry, Error,
                TEXT("BanAppealRegistry: all 64-bit IDs have been used — cannot add more appeals"));
            return FBanAppealEntry{};
        }
        Entry.Id          = NextId;
        NextId            = (NextId < INT64_MAX) ? NextId + 1 : 0;
        Entry.Uid         = Uid;
        Entry.Reason      = Reason;
        Entry.ContactInfo = ContactInfo;
        Entry.SubmittedAt = FDateTime::UtcNow();

        Appeals.Add(Entry);
        if (!SaveToFile())
        {
            UE_LOG(LogBanAppealRegistry, Error,
                TEXT("BanAppealRegistry: failed to save after adding appeal id=%lld for uid='%s'"),
                Entry.Id, *Entry.Uid);
        }
        bBroadcast = true;
    }

    if (bBroadcast)
        OnBanAppealSubmitted.Broadcast(Entry);

    return Entry;
}

FBanAppealEntry UBanAppealRegistry::AddAppeal(const FString& Uid,
                                               const FString& Reason,
                                               const FString& ContactInfo)
{
    FBanAppealEntry Entry;

    {
        FScopeLock Lock(&Mutex);

        // NextId == 0 is the exhausted sentinel (set when INT64_MAX has already
        // been allocated).  Using 0 allows INT64_MAX to be the last valid Id.
        if (NextId == 0)
        {
            UE_LOG(LogBanAppealRegistry, Error,
                TEXT("BanAppealRegistry: all 64-bit IDs have been used — cannot add more appeals"));
            return FBanAppealEntry{};
        }
        Entry.Id = NextId;
        NextId   = (NextId < INT64_MAX) ? NextId + 1 : 0; // 0 = exhausted
        Entry.Uid         = Uid;
        Entry.Reason      = Reason;
        Entry.ContactInfo = ContactInfo;
        Entry.SubmittedAt = FDateTime::UtcNow();

        Appeals.Add(Entry);
        if (!SaveToFile())
        {
            UE_LOG(LogBanAppealRegistry, Error,
                TEXT("BanAppealRegistry: failed to save after adding appeal id=%lld for uid='%s'"),
                Entry.Id, *Entry.Uid);
        }
    }

    // Broadcast outside the lock so listeners can safely call back into the registry.
    OnBanAppealSubmitted.Broadcast(Entry);

    return Entry;
}

TArray<FBanAppealEntry> UBanAppealRegistry::GetAllAppeals() const
{
    FScopeLock Lock(&Mutex);
    return Appeals;
}

FBanAppealEntry UBanAppealRegistry::GetAppealById(int64 Id) const
{
    FScopeLock Lock(&Mutex);
    for (const FBanAppealEntry& A : Appeals)
    {
        if (A.Id == Id)
            return A;
    }
    return FBanAppealEntry(); // Id == 0 signals "not found"
}

bool UBanAppealRegistry::DeleteAppeal(int64 Id)
{
    FScopeLock Lock(&Mutex);

    const int32 Before = Appeals.Num();
    Appeals.RemoveAll([Id](const FBanAppealEntry& A)
    {
        return A.Id == Id;
    });
    const bool bRemoved = Appeals.Num() < Before;
    if (bRemoved)
    {
        if (!SaveToFile())
        {
            UE_LOG(LogBanAppealRegistry, Error,
                TEXT("BanAppealRegistry: failed to save after deleting appeal id=%lld"), Id);
        }
    }
    return bRemoved;
}

bool UBanAppealRegistry::ReviewAppeal(int64 Id, EAppealStatus NewStatus,
                                       const FString& ReviewedByName,
                                       const FString& ReviewNote)
{
    FBanAppealEntry ReviewedEntry;
    bool bFound = false;

    {
        FScopeLock Lock(&Mutex);
        for (FBanAppealEntry& A : Appeals)
        {
            if (A.Id != Id) continue;
            A.Status     = NewStatus;
            A.ReviewedBy = ReviewedByName;
            A.ReviewNote = ReviewNote;
            A.ReviewedAt = FDateTime::UtcNow();
            ReviewedEntry = A;
            bFound = true;
            break;
        }
        if (bFound)
        {
            if (!SaveToFile())
            {
                UE_LOG(LogBanAppealRegistry, Error,
                    TEXT("BanAppealRegistry: failed to save after reviewing appeal id=%lld"), Id);
            }
        }
    }

    if (bFound)
        OnBanAppealReviewed.Broadcast(ReviewedEntry);

    return bFound;
}

// ─────────────────────────────────────────────────────────────────────────────
//  File I/O
// ─────────────────────────────────────────────────────────────────────────────

FString UBanAppealRegistry::GetRegistryPath() const
{
    const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
    FString BaseDir;
    if (Cfg && !Cfg->DatabasePath.IsEmpty())
        BaseDir = FPaths::GetPath(Cfg->DatabasePath);
    else
        BaseDir = FPaths::ProjectSavedDir() / TEXT("BanSystem");

    return BaseDir / TEXT("appeals.json");
}

void UBanAppealRegistry::LoadFromFile()
{
    FScopeLock Lock(&Mutex);
    Appeals.Empty();

    FString RawJson;
    if (!FFileHelper::LoadFileToString(RawJson, *FilePath))
        return;

    TSharedPtr<FJsonObject> Root;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(RawJson);
    if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
    {
        UE_LOG(LogBanAppealRegistry, Warning,
            TEXT("BanAppealRegistry: failed to parse %s — starting empty"), *FilePath);
        return;
    }

    const TArray<TSharedPtr<FJsonValue>>* Arr = nullptr;
    if (Root->TryGetArrayField(TEXT("appeals"), Arr) && Arr)
    {
        for (const TSharedPtr<FJsonValue>& Val : *Arr)
        {
            if (!Val.IsValid()) continue;
            const TSharedPtr<FJsonObject>* ObjPtr = nullptr;
            if (!Val->TryGetObject(ObjPtr) || !ObjPtr) continue;

            FBanAppealEntry Entry;
            {
                FString IdStr;
                double IdDbl = 0.0;
                if ((*ObjPtr)->TryGetStringField(TEXT("id"), IdStr))
                    Entry.Id = FCString::Atoi64(*IdStr);
                else if ((*ObjPtr)->TryGetNumberField(TEXT("id"), IdDbl)
                    && IdDbl >= 1.0 && IdDbl < static_cast<double>(INT64_MAX))
                    Entry.Id = static_cast<int64>(IdDbl);
            }
            if (Entry.Id <= 0)
            {
                UE_LOG(LogBanAppealRegistry, Warning,
                    TEXT("BanAppealRegistry: skipping appeal with invalid id (uid=%s)"), *Entry.Uid);
                continue;
            }
            (*ObjPtr)->TryGetStringField(TEXT("uid"),         Entry.Uid);
            (*ObjPtr)->TryGetStringField(TEXT("reason"),      Entry.Reason);
            (*ObjPtr)->TryGetStringField(TEXT("contactInfo"), Entry.ContactInfo);

            FString DateStr;
            if ((*ObjPtr)->TryGetStringField(TEXT("submittedAt"), DateStr))
            {
                if (!FDateTime::ParseIso8601(*DateStr, Entry.SubmittedAt))
                {
                    UE_LOG(LogBanAppealRegistry, Warning,
                        TEXT("BanAppealRegistry: uid='%s' has malformed submittedAt '%s' — skipping"),
                        *Entry.Uid, *DateStr);
                    continue;
                }
            }

            // Status (default Pending for records written before this feature).
            FString StatusStr;
            if ((*ObjPtr)->TryGetStringField(TEXT("status"), StatusStr))
            {
                if (StatusStr == TEXT("approved"))      Entry.Status = EAppealStatus::Approved;
                else if (StatusStr == TEXT("denied"))   Entry.Status = EAppealStatus::Denied;
                else                                    Entry.Status = EAppealStatus::Pending;
            }

            (*ObjPtr)->TryGetStringField(TEXT("reviewedBy"),  Entry.ReviewedBy);
            (*ObjPtr)->TryGetStringField(TEXT("reviewNote"),  Entry.ReviewNote);
            FString ReviewedAtStr;
            if ((*ObjPtr)->TryGetStringField(TEXT("reviewedAt"), ReviewedAtStr) && !ReviewedAtStr.IsEmpty())
            {
                if (!FDateTime::ParseIso8601(*ReviewedAtStr, Entry.ReviewedAt))
                    UE_LOG(LogBanAppealRegistry, Warning,
                        TEXT("BanAppealRegistry: uid='%s' has malformed reviewedAt '%s' — using default"),
                        *Entry.Uid, *ReviewedAtStr);
            }

            if (!Entry.Uid.IsEmpty())
                Appeals.Add(Entry);
        }
    }

    // Restore the NextId counter.  Prefer the persisted "nextId" field (written
    // since BUG-02 fix) over the scan-based reconstruction so that deleting the
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
        for (const FBanAppealEntry& A : Appeals)
            if (A.Id >= NextId) NextId = (A.Id < INT64_MAX) ? A.Id + 1 : 0;
    }
}

bool UBanAppealRegistry::SaveToFile() const
{
    // Caller must already hold Mutex.
    TArray<TSharedPtr<FJsonValue>> AppealArr;
    AppealArr.Reserve(Appeals.Num());
    for (const FBanAppealEntry& A : Appeals)
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("id"),          FString::Printf(TEXT("%lld"), A.Id));
        Obj->SetStringField(TEXT("uid"),         A.Uid);
        Obj->SetStringField(TEXT("reason"),      A.Reason);
        Obj->SetStringField(TEXT("contactInfo"), A.ContactInfo);
        Obj->SetStringField(TEXT("submittedAt"), A.SubmittedAt.ToIso8601());

        // Status
        FString StatusStr;
        switch (A.Status)
        {
        case EAppealStatus::Approved: StatusStr = TEXT("approved"); break;
        case EAppealStatus::Denied:   StatusStr = TEXT("denied");   break;
        default:                      StatusStr = TEXT("pending");  break;
        }
        Obj->SetStringField(TEXT("status"), StatusStr);

        if (!A.ReviewedBy.IsEmpty())
            Obj->SetStringField(TEXT("reviewedBy"), A.ReviewedBy);
        if (!A.ReviewNote.IsEmpty())
            Obj->SetStringField(TEXT("reviewNote"), A.ReviewNote);
        if (A.ReviewedAt != FDateTime(0))
            Obj->SetStringField(TEXT("reviewedAt"), A.ReviewedAt.ToIso8601());

        AppealArr.Add(MakeShared<FJsonValueObject>(Obj));
    }

    TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
    Root->SetStringField(TEXT("nextId"),  FString::Printf(TEXT("%lld"), NextId));
    Root->SetArrayField(TEXT("appeals"), AppealArr);

    FString JsonStr;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonStr);
    if (!FJsonSerializer::Serialize(Root.ToSharedRef(), Writer))
    {
        UE_LOG(LogBanAppealRegistry, Error,
            TEXT("BanAppealRegistry: failed to serialize appeals"));
        return false;
    }

    const FString TmpPath = FilePath + TEXT(".tmp");
    if (!FFileHelper::SaveStringToFile(JsonStr, *TmpPath,
        FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
    {
        UE_LOG(LogBanAppealRegistry, Error,
            TEXT("BanAppealRegistry: failed to write temp file %s"), *TmpPath);
        return false;
    }
    if (!IFileManager::Get().Move(*FilePath, *TmpPath, /*bReplace=*/true))
    {
        UE_LOG(LogBanAppealRegistry, Error,
            TEXT("BanAppealRegistry: failed to replace %s with temp file"), *FilePath);
        IFileManager::Get().Delete(*TmpPath);
        return false;
    }

    return true;
}
