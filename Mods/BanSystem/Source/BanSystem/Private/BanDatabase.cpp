// Copyright Yamahasxviper. All Rights Reserved.
// Direct port of Tools/BanSystem/src/database.ts

#include "BanDatabase.h"
#include "BanSystemConfig.h"

#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/FileManager.h"
#include "HAL/PlatformFileManager.h"

DEFINE_LOG_CATEGORY(LogBanDatabase);

// ─────────────────────────────────────────────────────────────────────────────
//  Internal JSON helpers
// ─────────────────────────────────────────────────────────────────────────────
namespace BanDbJson
{
    static TSharedPtr<FJsonObject> EntryToJson(const FBanEntry& E)
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("id"),          FString::Printf(TEXT("%lld"), E.Id));
        Obj->SetStringField(TEXT("uid"),         E.Uid);
        Obj->SetStringField(TEXT("playerUID"),   E.PlayerUID);
        Obj->SetStringField(TEXT("platform"),    E.Platform);
        Obj->SetStringField(TEXT("playerName"),  E.PlayerName);
        Obj->SetStringField(TEXT("reason"),      E.Reason);
        Obj->SetStringField(TEXT("bannedBy"),    E.BannedBy);
        Obj->SetStringField(TEXT("banDate"),     E.BanDate.ToIso8601());
        if (E.bIsPermanent)
            Obj->SetField(TEXT("expireDate"), MakeShared<FJsonValueNull>());
        else
            Obj->SetStringField(TEXT("expireDate"), E.ExpireDate.ToIso8601());
        Obj->SetBoolField(TEXT("isPermanent"), E.bIsPermanent);

        // Persist linked UIDs (cross-platform identity).
        if (E.LinkedUids.Num() > 0)
        {
            TArray<TSharedPtr<FJsonValue>> LinkedArr;
            for (const FString& L : E.LinkedUids)
                LinkedArr.Add(MakeShared<FJsonValueString>(L));
            Obj->SetArrayField(TEXT("linkedUids"), LinkedArr);
        }

        // Category and evidence (may be empty — omit for cleaner JSON).
        if (!E.Category.IsEmpty())
            Obj->SetStringField(TEXT("category"), E.Category);

        if (E.Evidence.Num() > 0)
        {
            TArray<TSharedPtr<FJsonValue>> EvidArr;
            for (const FString& Ev : E.Evidence)
                EvidArr.Add(MakeShared<FJsonValueString>(Ev));
            Obj->SetArrayField(TEXT("evidence"), EvidArr);
        }

        return Obj;
    }

    static bool JsonToEntry(const TSharedPtr<FJsonObject>& Obj, FBanEntry& OutEntry)
    {
        if (!Obj.IsValid()) return false;

        FString IdStr;
        double IdDbl = 0.0;
        if (Obj->TryGetStringField(TEXT("id"), IdStr))
            OutEntry.Id = FCString::Atoi64(*IdStr);
        else if (Obj->TryGetNumberField(TEXT("id"), IdDbl)
            && IdDbl >= 1.0 && IdDbl < static_cast<double>(INT64_MAX))
            OutEntry.Id = static_cast<int64>(IdDbl);

        Obj->TryGetStringField(TEXT("uid"),        OutEntry.Uid);
        Obj->TryGetStringField(TEXT("playerUID"),  OutEntry.PlayerUID);
        Obj->TryGetStringField(TEXT("platform"),   OutEntry.Platform);
        Obj->TryGetStringField(TEXT("playerName"), OutEntry.PlayerName);
        Obj->TryGetStringField(TEXT("reason"),     OutEntry.Reason);
        Obj->TryGetStringField(TEXT("bannedBy"),   OutEntry.BannedBy);

        FString BanDateStr;
        if (Obj->TryGetStringField(TEXT("banDate"), BanDateStr))
        {
            if (!FDateTime::ParseIso8601(*BanDateStr, OutEntry.BanDate))
            {
                // Malformed banDate — fall back to UtcNow() so duration displays and
                // point-in-time audit queries do not produce wildly incorrect values.
                UE_LOG(LogBanDatabase, Warning,
                    TEXT("BanDatabase: record uid='%s' has malformed banDate '%s' — using UtcNow() as fallback"),
                    *OutEntry.Uid, *BanDateStr);
                OutEntry.BanDate = FDateTime::UtcNow();
            }
        }
        else
        {
            // banDate field is absent — this should not happen for well-formed records.
            // Use UtcNow() as a safe fallback so duration calculations don't produce
            // absurdly large values from the epoch (FDateTime(0)).
            UE_LOG(LogBanDatabase, Warning,
                TEXT("BanDatabase: record uid='%s' is missing banDate field — using UtcNow() as fallback"),
                *OutEntry.Uid);
            OutEntry.BanDate = FDateTime::UtcNow();
        }

        bool bPerm = false;
        Obj->TryGetBoolField(TEXT("isPermanent"), bPerm);
        OutEntry.bIsPermanent = bPerm;

        if (!bPerm)
        {
            FString ExpireDateStr;
            if (Obj->TryGetStringField(TEXT("expireDate"), ExpireDateStr) && !ExpireDateStr.IsEmpty())
            {
                if (!FDateTime::ParseIso8601(*ExpireDateStr, OutEntry.ExpireDate))
                {
                    // Malformed expireDate — treat as permanent so the ban is not
                    // silently discarded by PruneExpiredBans (ExpireDate epoch < UtcNow()
                    // would make IsExpired() return true, allowing the player to join).
                    UE_LOG(LogBanDatabase, Warning,
                        TEXT("BanDatabase: record uid='%s' has malformed expireDate '%s' — treating as permanent"),
                        *OutEntry.Uid, *ExpireDateStr);
                    OutEntry.bIsPermanent = true;
                    OutEntry.ExpireDate   = FDateTime(0);
                }
            }
            else
            {
                // Malformed record — isPermanent=false but expireDate is missing or empty.
                // Treat as permanent to avoid an unbounded active-ban window.
                UE_LOG(LogBanDatabase, Warning,
                    TEXT("BanDatabase: record uid='%s' has isPermanent=false but "
                         "expireDate is missing or empty — treating as permanent"),
                    *OutEntry.Uid);
                OutEntry.bIsPermanent = true;
                OutEntry.ExpireDate   = FDateTime(0);
            }
        }
        else
        {
            OutEntry.ExpireDate = FDateTime(0);
        }

        // Restore linked UIDs (may be absent in older records).
        const TArray<TSharedPtr<FJsonValue>>* LinkedArr = nullptr;
        if (Obj->TryGetArrayField(TEXT("linkedUids"), LinkedArr) && LinkedArr)
        {
            for (const TSharedPtr<FJsonValue>& Val : *LinkedArr)
            {
                FString L;
                if (Val.IsValid() && Val->TryGetString(L) && !L.IsEmpty())
                    OutEntry.LinkedUids.Add(L);
            }
        }

        // Category (optional, absent in records written before this feature).
        Obj->TryGetStringField(TEXT("category"), OutEntry.Category);

        // Evidence (optional array).
        const TArray<TSharedPtr<FJsonValue>>* EvidArr = nullptr;
        if (Obj->TryGetArrayField(TEXT("evidence"), EvidArr) && EvidArr)
        {
            for (const TSharedPtr<FJsonValue>& Val : *EvidArr)
            {
                FString Ev;
                if (Val.IsValid() && Val->TryGetString(Ev) && !Ev.IsEmpty())
                    OutEntry.Evidence.Add(Ev);
            }
        }

        // A-1: also require Platform and PlayerUID so malformed records are rejected
        return !OutEntry.Uid.IsEmpty() && !OutEntry.BannedBy.IsEmpty()
            && !OutEntry.Platform.IsEmpty() && !OutEntry.PlayerUID.IsEmpty();
    }
} // namespace BanDbJson

// Static delegate definitions.
UBanDatabase::FOnBanAdded   UBanDatabase::OnBanAdded;
UBanDatabase::FOnBanRemoved UBanDatabase::OnBanRemoved;
UBanDatabase::FOnBanUpdated UBanDatabase::OnBanUpdated;

// ─────────────────────────────────────────────────────────────────────────────
//  USubsystem lifecycle
// ─────────────────────────────────────────────────────────────────────────────

void UBanDatabase::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    DbPath = GetDatabasePath();

    // Ensure the directory exists.
    const FString Dir = FPaths::GetPath(DbPath);
    IPlatformFile& PF = FPlatformFileManager::Get().GetPlatformFile();
    if (!PF.DirectoryExists(*Dir))
        PF.CreateDirectoryTree(*Dir);

    LoadFromFile();

    // Bootstrap the file the very first time (or if it was deleted).
    // Calling SaveToFile() here ensures bans.json always exists after
    // initialization so that a subsequent /ban + server-restart cycle can
    // never leave the file absent.
    if (!PF.FileExists(*DbPath))
    {
        if (SaveToFile())
        {
            UE_LOG(LogBanDatabase, Log,
                TEXT("BanDatabase: created empty ban database at %s"), *DbPath);
        }
        else
        {
            UE_LOG(LogBanDatabase, Error,
                TEXT("BanDatabase: failed to create initial ban database at %s"), *DbPath);
        }
    }

    // Capture the mtime so we can detect external edits in ReloadIfChanged().
    LastKnownFileModTime = IFileManager::Get().GetTimeStamp(*DbPath);

    const int32 Pruned = PruneExpiredBans(/*bSilent=*/true);
    UE_LOG(LogBanDatabase, Log,
        TEXT("BanDatabase: loaded %s (%d ban(s), pruned %d expired)"),
        *DbPath, Bans.Num(), Pruned);
}

void UBanDatabase::Deinitialize()
{
    Super::Deinitialize();
}

// ─────────────────────────────────────────────────────────────────────────────
//  Hot-reload on external file change
// ─────────────────────────────────────────────────────────────────────────────

void UBanDatabase::ReloadIfChanged()
{
    // Read the file mtime and compare it against the cached value inside a
    // single lock scope.  Reading outside the lock and then acquiring it would
    // create a TOCTOU window: a concurrent SaveToFile() could update
    // LastKnownFileModTime to T2 between our GetTimeStamp() call (which saw T1)
    // and our lock acquisition, causing us to store the stale T1 and then loop
    // on every subsequent call (T2 != T1 forever).
    FDateTime NewModTime;
    bool bForcedThisTick = false;
    {
        FScopeLock Lock(&DbMutex);
        bForcedThisTick = bPendingForcedReload;
        bPendingForcedReload = false;

        NewModTime = IFileManager::Get().GetTimeStamp(*DbPath);

        // GetTimeStamp returns FDateTime(0) when the file does not exist.
        if (NewModTime == FDateTime(0))
            return;

        // If neither a forced reload was requested nor the mtime changed, skip.
        if (!bForcedThisTick && NewModTime == LastKnownFileModTime)
            return;

        // Record the new mtime BEFORE releasing the lock and calling LoadFromFile().
        // If another external edit arrives concurrently during the load it will
        // produce a timestamp strictly greater than NewModTime, so the next
        // ReloadIfChanged() call will detect and load it.  Storing the mtime
        // after loading would create a window where that concurrent edit is
        // permanently missed.
        LastKnownFileModTime = NewModTime;
    }

    UE_LOG(LogBanDatabase, Log,
        TEXT("BanDatabase: bans.json changed on disk, reloading (%s)"), *DbPath);

    LoadFromFile();

    // Guard: if another external edit (T2) arrived while LoadFromFile was running,
    // the file mtime will have advanced past NewModTime (T1).  Without this check,
    // PruneExpiredBans's SaveToFile (T3 > T2) would overwrite the T2 content and
    // update LastKnownFileModTime to T3, making the T2 edit permanently invisible
    // to every subsequent ReloadIfChanged call (T3 == T3 → early-return forever).
    bool bConcurrentEditDuringLoad = false;
    {
        FScopeLock Lock(&DbMutex);
        const FDateTime PostLoadMtime = IFileManager::Get().GetTimeStamp(*DbPath);
        bConcurrentEditDuringLoad = (PostLoadMtime != NewModTime && PostLoadMtime != FDateTime(0));
    }

    // Prune any bans that expired while the file was externally edited and
    // immediately write the cleaned list back so the file stays consistent.
    // PruneExpiredBans() calls SaveToFile() when bans are removed, which in
    // turn updates LastKnownFileModTime to the post-prune file mtime.
    const int32 Pruned = PruneExpiredBans();

    if (bConcurrentEditDuringLoad)
    {
        // SaveToFile (called by PruneExpiredBans) may have set LastKnownFileModTime
        // to T3 > T2, permanently hiding the T2 edit.  Set bPendingForcedReload so
        // the next tick unconditionally re-reads the file — this avoids using
        // FDateTime(0) as a sentinel (which collides with "file not found").
        FScopeLock Lock(&DbMutex);
        bPendingForcedReload = true;
    }

    UE_LOG(LogBanDatabase, Log,
        TEXT("BanDatabase: reload complete (pruned %d expired)"), Pruned);
}

// ─────────────────────────────────────────────────────────────────────────────
//  File I/O
// ─────────────────────────────────────────────────────────────────────────────

void UBanDatabase::LoadFromFile()
{
    // This function acquires DbMutex internally. Call without holding the lock.
    FScopeLock Lock(&DbMutex);

    FString RawJson;
    if (!FFileHelper::LoadFileToString(RawJson, *DbPath))
    {
        // File doesn't exist yet — clear atomically so callers never see a
        // partial list.  This is fine on first run.
        Bans.Empty();
        NextId = 1;
        return;
    }

    TSharedPtr<FJsonObject> Root;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(RawJson);
    if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
    {
        UE_LOG(LogBanDatabase, Warning,
            TEXT("BanDatabase: failed to parse %s — keeping existing in-memory list"), *DbPath);
        // Rename the corrupt file so it is not silently re-discarded on every
        // server restart.  A fresh empty database will be written on the next
        // SaveToFile() call (e.g. when the first ban is added or at Initialize).
        const FString CorruptPath = DbPath + TEXT(".corrupt.bak");
        if (IFileManager::Get().Move(*CorruptPath, *DbPath))
        {
            UE_LOG(LogBanDatabase, Warning,
                TEXT("BanDatabase: corrupt file moved to %s — a fresh database will be created on next write."),
                *CorruptPath);
        }
        // Do NOT clear Bans here: on hot-reload a parse failure must not wipe
        // the live in-memory ban list that is currently protecting the server.
        return;
    }

    // Prefer string format (written since this fix); fall back to legacy double
    // format for databases written by older builds.  int64 values above 2^53
    // lose precision when stored as double, so the canonical format is now a
    // decimal string ("nextId": "12345").
    int64 NewNextId = 1;
    FString NextIdStr;
    double  NextIdDbl = 1.0;
    if (Root->TryGetStringField(TEXT("nextId"), NextIdStr))
        NewNextId = FMath::Max((int64)1, FCString::Atoi64(*NextIdStr));
    else if (Root->TryGetNumberField(TEXT("nextId"), NextIdDbl))
        NewNextId = FMath::Max((int64)1, static_cast<int64>(NextIdDbl));

    // Build the new ban list into a local array first so that concurrent readers
    // never observe an empty list during the parse phase.  The live Bans field is
    // only updated once the new list is fully constructed (atomic swap).
    TArray<FBanEntry> NewBans;
    const TArray<TSharedPtr<FJsonValue>>* BanArray = nullptr;
    if (Root->TryGetArrayField(TEXT("bans"), BanArray) && BanArray)
    {
        NewBans.Reserve(BanArray->Num());
        for (const TSharedPtr<FJsonValue>& Val : *BanArray)
        {
            if (!Val.IsValid()) continue;
            const TSharedPtr<FJsonObject>* ObjPtr = nullptr;
            if (!Val->TryGetObject(ObjPtr) || !ObjPtr) continue;

            FBanEntry E;
            if (BanDbJson::JsonToEntry(*ObjPtr, E))
                NewBans.Add(E);
        }
    }

    // Atomic swap: readers either see the old complete list or the new complete
    // list — never an empty intermediate state.
    Bans    = MoveTemp(NewBans);
    NextId  = NewNextId;
}

bool UBanDatabase::SaveToFile() const
{
    // Caller must hold DbMutex.

    // Defensively recreate the directory — it may have been absent on first
    // run or removed externally between Initialize() and the first write.
    const FString Dir = FPaths::GetPath(DbPath);
    IPlatformFile& PF = FPlatformFileManager::Get().GetPlatformFile();
    if (!PF.DirectoryExists(*Dir))
        PF.CreateDirectoryTree(*Dir);

    TArray<TSharedPtr<FJsonValue>> BanArray;
    BanArray.Reserve(Bans.Num());
    for (const FBanEntry& E : Bans)
        BanArray.Add(MakeShared<FJsonValueObject>(BanDbJson::EntryToJson(E)));

    TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
    // Store nextId as a decimal string so int64 values above 2^53 round-trip
    // without precision loss.  Old builds that wrote a double are handled in
    // LoadFromFile() by the string-first / number-fallback pattern.
    Root->SetStringField(TEXT("nextId"), FString::Printf(TEXT("%lld"), NextId));
    Root->SetArrayField(TEXT("bans"), BanArray);

    FString JsonStr;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonStr);
    if (!FJsonSerializer::Serialize(Root.ToSharedRef(), Writer))
    {
        UE_LOG(LogBanDatabase, Error, TEXT("BanDatabase: failed to serialize ban list"));
        return false;
    }

    if (!FFileHelper::SaveStringToFile(JsonStr, *(DbPath + TEXT(".tmp")),
        FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
    {
        UE_LOG(LogBanDatabase, Error,
            TEXT("BanDatabase: failed to write temp file %s.tmp"), *DbPath);
        return false;
    }

    if (!IFileManager::Get().Move(*DbPath, *(DbPath + TEXT(".tmp")), /*bReplace=*/true))
    {
        UE_LOG(LogBanDatabase, Error,
            TEXT("BanDatabase: failed to rename temp file to %s"), *DbPath);
        IFileManager::Get().Delete(*(DbPath + TEXT(".tmp")));
        return false;
    }

    // Update the cached mtime so ReloadIfChanged() does not treat our own
    // writes as external edits and reload the file unnecessarily.
    LastKnownFileModTime = IFileManager::Get().GetTimeStamp(*DbPath);

    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Write
// ─────────────────────────────────────────────────────────────────────────────

bool UBanDatabase::UpdateBan(const FString& Uid, TFunction<void(FBanEntry&)> Mutator,
                              FBanEntry& OutUpdated)
{
    bool bSaved = false;

    {
        FScopeLock Lock(&DbMutex);

        FBanEntry* Found = nullptr;
        for (FBanEntry& E : Bans)
        {
            if (E.Uid.Equals(Uid, ESearchCase::IgnoreCase))
            {
                Found = &E;
                break;
            }
        }

        if (!Found) return false;

        Mutator(*Found);
        OutUpdated = *Found;
        bSaved = SaveToFile();
    }

    if (bSaved)
        OnBanUpdated.Broadcast(OutUpdated);

    return bSaved;
}

bool UBanDatabase::AddBan(const FBanEntry& Entry)
{
    FBanEntry NewEntry;
    bool bSaved;

    {
        FScopeLock Lock(&DbMutex);

        // Upsert: remove any existing record with the same UID first (case-insensitive).
        Bans.RemoveAll([&Entry](const FBanEntry& E){ return E.Uid.Equals(Entry.Uid, ESearchCase::IgnoreCase); });

        NewEntry = Entry;
        if (NewEntry.Id <= 0)
        {
            // Guard against ID exhaustion — 0 is the "exhausted" sentinel.
            if (NextId == 0)
            {
                UE_LOG(LogBanDatabase, Error,
                    TEXT("BanDatabase: all 64-bit IDs have been used — cannot add more bans"));
                return false;
            }
            NewEntry.Id = NextId;
            NextId = (NextId < INT64_MAX) ? NextId + 1 : 0; // 0 = exhausted
        }
        else
        {
            // External ID supplied (e.g. from peer sync or file reload).
            // Advance NextId past it only when it would collide with or fall
            // behind the external ID.  If the external ID is below NextId, the
            // counter is already safe and must not be disturbed.
            // Guard: if the supplied ID is INT64_MAX there is no higher valid Id,
            // so mark the counter exhausted rather than letting it overflow.
            if (NextId != 0 && NewEntry.Id >= NextId)
            {
                NextId = (NewEntry.Id < INT64_MAX) ? NewEntry.Id + 1 : 0;
            }
        }

        Bans.Add(NewEntry);
        bSaved = SaveToFile();
    }

    if (bSaved)
        OnBanAdded.Broadcast(NewEntry);

    return bSaved;
}

bool UBanDatabase::AddBanSkipIfPermanentExists(const FBanEntry& Entry, bool& bOutSkippedPermanent)
{
    FBanEntry NewEntry;
    bool bSaved = false;
    bOutSkippedPermanent = false;

    {
        FScopeLock Lock(&DbMutex);

        // Atomically check for an existing permanent ban.  If one is found,
        // abort without touching the database so the permanent ban is never
        // silently downgraded to a temporary one by a scheduled or sync operation.
        for (const FBanEntry& E : Bans)
        {
            if (E.Uid.Equals(Entry.Uid, ESearchCase::IgnoreCase) && E.bIsPermanent)
            {
                bOutSkippedPermanent = true;
                return false;
            }
        }

        // No permanent ban found — perform the standard upsert (identical to AddBan).
        Bans.RemoveAll([&Entry](const FBanEntry& E){ return E.Uid.Equals(Entry.Uid, ESearchCase::IgnoreCase); });

        NewEntry = Entry;
        if (NewEntry.Id <= 0)
        {
            if (NextId == 0)
            {
                UE_LOG(LogBanDatabase, Error,
                    TEXT("BanDatabase: all 64-bit IDs have been used — cannot add more bans"));
                return false;
            }
            NewEntry.Id = NextId;
            NextId = (NextId < INT64_MAX) ? NextId + 1 : 0;
        }
        else
        {
            if (NextId != 0 && NewEntry.Id >= NextId)
                NextId = (NewEntry.Id < INT64_MAX) ? NewEntry.Id + 1 : 0;
        }

        Bans.Add(NewEntry);
        bSaved = SaveToFile();
    }

    if (bSaved)
        OnBanAdded.Broadcast(NewEntry);

    return bSaved;
}

bool UBanDatabase::RemoveBanByUid(const FString& Uid, bool bSilent)
{
    FBanEntry Ignored;
    return RemoveBanByUid(Uid, Ignored, bSilent);
}

bool UBanDatabase::RemoveBanByUid(const FString& Uid, FBanEntry& OutEntry, bool bSilent)
{
    bool bRemoved = false;
    bool bSaveOk  = true;

    {
        FScopeLock Lock(&DbMutex);

        // Capture the full entry before removal so callers have the data they
        // need for notifications without a separate GetBanByUid() round-trip,
        // eliminating the TOCTOU window.
        for (const FBanEntry& E : Bans)
        {
            if (E.Uid.Equals(Uid, ESearchCase::IgnoreCase)) { OutEntry = E; break; }
        }

        const int32 Removed = Bans.RemoveAll([&Uid](const FBanEntry& E){ return E.Uid.Equals(Uid, ESearchCase::IgnoreCase); });
        bRemoved = (Removed > 0);
        if (bRemoved)
        {
            if (!SaveToFile())
            {
                UE_LOG(LogBanDatabase, Warning,
                    TEXT("RemoveBanByUid: SaveToFile failed for Uid=%s"), *Uid);
                bSaveOk = false;
            }
        }
    }

    if (!bSaveOk) return false;

    if (bRemoved && !bSilent)
        OnBanRemoved.Broadcast(OutEntry.Uid, OutEntry.PlayerName);

    return bRemoved;
}

bool UBanDatabase::RemoveBanById(int64 Id, bool bSilent)
{
    FBanEntry Ignored;
    return RemoveBanById(Id, Ignored, bSilent);
}

bool UBanDatabase::RemoveBanById(int64 Id, FBanEntry& OutEntry, bool bSilent)
{
    bool bRemoved = false;
    bool bSaveOk  = true;

    {
        FScopeLock Lock(&DbMutex);

        // Capture the full entry before removal so callers have the data they
        // need for notifications without a separate GetAllBans() round-trip.
        for (const FBanEntry& E : Bans)
        {
            if (E.Id == Id) { OutEntry = E; break; }
        }

        const int32 Removed = Bans.RemoveAll([Id](const FBanEntry& E){ return E.Id == Id; });
        bRemoved = (Removed > 0);
        if (bRemoved)
        {
            if (!SaveToFile())
            {
                UE_LOG(LogBanDatabase, Warning,
                    TEXT("RemoveBanById: SaveToFile failed for Id=%lld"), Id);
                bSaveOk = false;
            }
        }
    }

    if (!bSaveOk) return false;

    if (bRemoved && !bSilent)
        OnBanRemoved.Broadcast(OutEntry.Uid, OutEntry.PlayerName);

    return bRemoved;
}

int32 UBanDatabase::PruneExpiredBans(bool bSilent)
{
    TArray<FBanEntry> Expired;

    {
        FScopeLock Lock(&DbMutex);

        const FDateTime Now = FDateTime::UtcNow();

        // Collect expired entries before removal so we can broadcast OnBanRemoved
        // outside the lock, matching the behaviour of RemoveBanByUid/RemoveBanById.
        for (const FBanEntry& E : Bans)
        {
            if (!E.bIsPermanent && E.ExpireDate < Now)
                Expired.Add(E);
        }

        if (!Expired.IsEmpty())
        {
            Bans.RemoveAll([&Now](const FBanEntry& E)
            {
                return !E.bIsPermanent && E.ExpireDate < Now;
            });
            if (!SaveToFile())
            {
                UE_LOG(LogBanDatabase, Error,
                    TEXT("BanDatabase: failed to persist pruning of %d expired ban(s) — "
                         "they will reappear after a server restart if the disk issue persists"),
                    Expired.Num());
            }
        }
    }

    // Broadcast outside the lock to avoid re-entrancy with OnBanRemoved subscribers.
    // Skipped in silent mode (e.g. startup pruning) to avoid notification floods.
    if (!bSilent)
    {
        for (const FBanEntry& E : Expired)
            OnBanRemoved.Broadcast(E.Uid, E.PlayerName);
    }

    return Expired.Num();
}

// ─────────────────────────────────────────────────────────────────────────────
//  Read
// ─────────────────────────────────────────────────────────────────────────────

bool UBanDatabase::IsCurrentlyBanned(const FString& Uid, FBanEntry& OutEntry) const
{
    FScopeLock Lock(&DbMutex);

    for (const FBanEntry& E : Bans)
    {
        if (!E.Uid.Equals(Uid, ESearchCase::IgnoreCase)) continue;

        // Permanent bans are always active.
        if (E.bIsPermanent)
        {
            OutEntry = E;
            return true;
        }
        // Temporary bans are active until expiry.
        if (FDateTime::UtcNow() < E.ExpireDate)
        {
            OutEntry = E;
            return true;
        }
        // Expired — keep scanning in case a different record for this UID is still active
        // (e.g. if bans.json was externally edited to contain two entries for the same UID).
        continue;
    }
    return false;
}

bool UBanDatabase::IsCurrentlyBannedByAnyId(const FString& Uid, FBanEntry& OutEntry) const
{
    FScopeLock Lock(&DbMutex);

    const FDateTime Now = FDateTime::UtcNow();
    for (const FBanEntry& E : Bans)
    {
        if (!E.MatchesUid(Uid)) continue;

        if (E.bIsPermanent || Now < E.ExpireDate)
        {
            OutEntry = E;
            return true;
        }
        // Expired — keep scanning in case a different linked record is still active.
    }
    return false;
}

bool UBanDatabase::GetBanByUid(const FString& Uid, FBanEntry& OutEntry) const
{
    FScopeLock Lock(&DbMutex);
    return GetBanByUid_Locked(Uid, OutEntry);
}

bool UBanDatabase::GetBanByUid_Locked(const FString& Uid, FBanEntry& OutEntry) const
{
    for (const FBanEntry& E : Bans)
    {
        if (E.Uid.Equals(Uid, ESearchCase::IgnoreCase))
        {
            OutEntry = E;
            return true;
        }
    }
    return false;
}

TArray<FBanEntry> UBanDatabase::GetActiveBans() const
{
    FScopeLock Lock(&DbMutex);

    const FDateTime Now = FDateTime::UtcNow();
    TArray<FBanEntry> Active;
    for (const FBanEntry& E : Bans)
    {
        if (E.bIsPermanent || Now < E.ExpireDate)
            Active.Add(E);
    }
    return Active;
}

TArray<FBanEntry> UBanDatabase::GetAllBans() const
{
    FScopeLock Lock(&DbMutex);
    return Bans;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Cross-platform linking
// ─────────────────────────────────────────────────────────────────────────────

bool UBanDatabase::LinkBans(const FString& UidA, const FString& UidB)
{
    if (UidA.IsEmpty() || UidB.IsEmpty() || UidA.Equals(UidB, ESearchCase::IgnoreCase))
        return false;

    bool bSaved = false;
    TArray<FBanEntry> Modified;

    {
        FScopeLock Lock(&DbMutex);

        bool bDirty = false;
        bool bFoundA = false;
        bool bFoundB = false;

        auto AddLinkIfMissing = [&](FBanEntry& Entry, const FString& LinkUid) -> bool
        {
            for (const FString& L : Entry.LinkedUids)
                if (L.Equals(LinkUid, ESearchCase::IgnoreCase)) return false;
            Entry.LinkedUids.Add(LinkUid);
            return true;
        };

        for (FBanEntry& E : Bans)
        {
            if (E.Uid.Equals(UidA, ESearchCase::IgnoreCase))
            {
                bFoundA = true;
                if (AddLinkIfMissing(E, UidB)) { bDirty = true; Modified.Add(E); }
            }
            if (E.Uid.Equals(UidB, ESearchCase::IgnoreCase))
            {
                bFoundB = true;
                if (AddLinkIfMissing(E, UidA)) { bDirty = true; Modified.Add(E); }
            }
        }

        if (bDirty)
        {
            if (!bFoundA)
                UE_LOG(LogBanDatabase, Warning,
                    TEXT("BanDatabase: LinkBans — no ban found for '%s'; link added to '%s' only"),
                    *UidA, *UidB);
            else if (!bFoundB)
                UE_LOG(LogBanDatabase, Warning,
                    TEXT("BanDatabase: LinkBans — no ban found for '%s'; link added to '%s' only"),
                    *UidB, *UidA);
            bSaved = SaveToFile();
        }
        else if (bFoundA && bFoundB)
        {
            // Both ban records exist but were already cross-linked — no-op, not an error.
            UE_LOG(LogBanDatabase, Verbose,
                TEXT("BanDatabase: LinkBans — '%s' and '%s' are already linked; no change"),
                *UidA, *UidB);
        }
        else
        {
            UE_LOG(LogBanDatabase, Warning,
                TEXT("BanDatabase: LinkBans — no ban found for '%s' or '%s'"), *UidA, *UidB);
        }
    }

    if (bSaved)
        for (const FBanEntry& E : Modified)
            OnBanUpdated.Broadcast(E);

    return bSaved;
}

bool UBanDatabase::UnlinkBans(const FString& UidA, const FString& UidB)
{
    if (UidA.IsEmpty() || UidB.IsEmpty()) return false;

    bool bSaved = false;
    TArray<FBanEntry> Modified;

    {
        FScopeLock Lock(&DbMutex);

        bool bDirty = false;

        for (FBanEntry& E : Bans)
        {
            if (E.Uid.Equals(UidA, ESearchCase::IgnoreCase) || E.Uid.Equals(UidB, ESearchCase::IgnoreCase))
            {
                const FString& ToRemove = E.Uid.Equals(UidA, ESearchCase::IgnoreCase) ? UidB : UidA;
                const int32 Removed = E.LinkedUids.RemoveAll([&ToRemove](const FString& L)
                {
                    return L.Equals(ToRemove, ESearchCase::IgnoreCase);
                });
                if (Removed > 0) { bDirty = true; Modified.Add(E); }
            }
        }

        if (bDirty) bSaved = SaveToFile();
    }

    if (bSaved)
        for (const FBanEntry& E : Modified)
            OnBanUpdated.Broadcast(E);

    return bSaved;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Backup  (mirrors BanDatabase.backup() in database.ts)
// ─────────────────────────────────────────────────────────────────────────────

FString UBanDatabase::Backup(const FString& BackupDir, int32 MaxKeep) const
{
    FScopeLock Lock(&DbMutex);

    IPlatformFile& PF = FPlatformFileManager::Get().GetPlatformFile();

    if (!PF.FileExists(*DbPath))
        return FString();

    if (!PF.DirectoryExists(*BackupDir))
        PF.CreateDirectoryTree(*BackupDir);

    const FDateTime Now   = FDateTime::UtcNow();
    const FString   Stamp = FString::Printf(
        TEXT("%04d-%02d-%02d_%02d-%02d-%02d"),
        Now.GetYear(), Now.GetMonth(),  Now.GetDay(),
        Now.GetHour(), Now.GetMinute(), Now.GetSecond());
    const FString Dest = BackupDir / FString::Printf(TEXT("bans_%s.json"), *Stamp);

    if (!PF.CopyFile(*Dest, *DbPath))
    {
        UE_LOG(LogBanDatabase, Warning,
            TEXT("Backup: failed to copy %s → %s"), *DbPath, *Dest);
        return FString();
    }

    UE_LOG(LogBanDatabase, Log, TEXT("Backup: %s"), *Dest);

    // Prune old backups beyond MaxKeep.
    TArray<FString> Files;
    IFileManager::Get().FindFiles(Files, *(BackupDir / TEXT("bans_*.json")), true, false);
    Files.Sort();
    // Files is sorted oldest-first by timestamp-stamped filename.
    // Delete the surplus oldest entries in a single forward pass (O(n)).
    const int32 ToDelete = FMath::Max(0, Files.Num() - MaxKeep);
    for (int32 i = 0; i < ToDelete; ++i)
    {
        PF.DeleteFile(*(BackupDir / Files[i]));
    }

    return Dest;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Helpers
// ─────────────────────────────────────────────────────────────────────────────

FString UBanDatabase::MakeUid(const FString& Platform, const FString& PlayerUID)
{
    return Platform.ToUpper() + TEXT(":") + PlayerUID;
}

void UBanDatabase::ParseUid(const FString& Uid, FString& OutPlatform, FString& OutPlayerUID)
{
    int32 ColonIdx = INDEX_NONE;
    if (Uid.FindChar(TEXT(':'), ColonIdx) && ColonIdx > 0)
    {
        OutPlatform  = Uid.Left(ColonIdx).ToUpper();
        OutPlayerUID = Uid.Mid(ColonIdx + 1);
    }
    else
    {
        OutPlatform  = TEXT("UNKNOWN");
        OutPlayerUID = Uid;
    }
}

FString UBanDatabase::GetDatabasePath() const
{
    const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
    if (Cfg && !Cfg->DatabasePath.IsEmpty())
        return Cfg->DatabasePath;

    return FPaths::ProjectSavedDir() / TEXT("BanSystem") / TEXT("bans.json");
}
