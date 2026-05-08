// Copyright Yamahasxviper. All Rights Reserved.

#include "ScheduledBanRegistry.h"
#include "BanDatabase.h"
#include "BanEnforcer.h"
#include "BanSystemConfig.h"
#include "BanAuditLog.h"
#include "BanDiscordNotifier.h"
#include "PlayerSessionRegistry.h"

#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFileManager.h"
#include "HAL/FileManager.h"
#include "Engine/GameInstance.h"

DEFINE_LOG_CATEGORY(LogScheduledBanRegistry);

namespace
{
    bool MatchesScheduledBan(const FBanEntry& Existing, const FScheduledBanEntry& Entry)
    {
        if (!Existing.Uid.Equals(Entry.Uid, ESearchCase::IgnoreCase)) return false;
        if (Existing.Reason != Entry.Reason) return false;
        if (Existing.BannedBy != Entry.ScheduledBy) return false;
        if (Existing.Category != Entry.Category) return false;

        const bool bShouldBePermanent = (Entry.DurationMinutes <= 0);
        if (Existing.bIsPermanent != bShouldBePermanent) return false;
        if (bShouldBePermanent) return true;

        const double RemainingSeconds = (Existing.ExpireDate - FDateTime::UtcNow()).GetTotalSeconds();
        return RemainingSeconds > 0.0
            && FMath::Abs(RemainingSeconds - Entry.DurationMinutes * 60.0) < 60.0
            && Existing.BanDate >= Entry.EffectiveAt;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
//  USubsystem lifecycle
// ─────────────────────────────────────────────────────────────────────────────

void UScheduledBanRegistry::Initialize(FSubsystemCollectionBase& Collection)
{
    Collection.InitializeDependency<UBanDatabase>();
    Super::Initialize(Collection);

    FilePath = GetRegistryPath();

    const FString Dir = FPaths::GetPath(FilePath);
    IPlatformFile& PF = FPlatformFileManager::Get().GetPlatformFile();
    if (!PF.DirectoryExists(*Dir))
        PF.CreateDirectoryTree(*Dir);

    LoadFromFile();

    UE_LOG(LogScheduledBanRegistry, Log,
        TEXT("ScheduledBanRegistry: loaded %s (%d pending scheduled ban(s))"),
        *FilePath, Pending.Num());
}

void UScheduledBanRegistry::Deinitialize()
{
    Super::Deinitialize();
}

// ─────────────────────────────────────────────────────────────────────────────
//  Public API
// ─────────────────────────────────────────────────────────────────────────────

FScheduledBanEntry UScheduledBanRegistry::AddScheduled(
    const FString& Uid, const FString& PlayerName, const FString& Reason,
    const FString& ScheduledBy, FDateTime EffectiveAt, int32 DurationMinutes,
    const FString& Category)
{
    FScopeLock Lock(&Mutex);
    const int64 OriginalNextId = NextId;

    // NextId == 0 is the exhausted sentinel (set when INT64_MAX has already
    // been allocated).  Using 0 allows INT64_MAX to be the last valid Id.
    if (NextId == 0)
    {
        UE_LOG(LogScheduledBanRegistry, Error,
            TEXT("ScheduledBanRegistry: all 64-bit IDs have been used — cannot schedule more bans"));
        return FScheduledBanEntry{};
    }

    FScheduledBanEntry Entry;
    Entry.Id              = NextId;
    NextId                = (NextId < INT64_MAX) ? NextId + 1 : 0; // 0 = exhausted
    Entry.Uid             = Uid;
    Entry.PlayerName      = PlayerName;
    Entry.Reason          = Reason;
    Entry.ScheduledBy     = ScheduledBy;
    Entry.EffectiveAt     = EffectiveAt;
    Entry.CreatedAt       = FDateTime::UtcNow();
    Entry.DurationMinutes = DurationMinutes;
    Entry.Category        = Category;

    Pending.Add(Entry);
    if (!SaveToFile())
    {
        Pending.RemoveAt(Pending.Num() - 1);
        NextId = OriginalNextId;
        UE_LOG(LogScheduledBanRegistry, Error,
            TEXT("ScheduledBanRegistry: failed to save after adding scheduled ban #%lld for %s"),
            Entry.Id, *Uid);
        return FScheduledBanEntry{};
    }

    UE_LOG(LogScheduledBanRegistry, Log,
        TEXT("ScheduledBanRegistry: scheduled ban #%lld for %s at %s"),
        Entry.Id, *Uid, *EffectiveAt.ToIso8601());

    return Entry;
}

TArray<FScheduledBanEntry> UScheduledBanRegistry::GetAllPending() const
{
    FScopeLock Lock(&Mutex);
    return Pending;
}

bool UScheduledBanRegistry::DeleteScheduled(int64 Id)
{
    FScheduledBanEntry Unused;
    return DeleteScheduled(Id, Unused);
}

bool UScheduledBanRegistry::DeleteScheduled(int64 Id, FScheduledBanEntry& OutEntry)
{
    FScopeLock Lock(&Mutex);

    int32 RemoveIdx = INDEX_NONE;
    for (int32 i = 0; i < Pending.Num(); ++i)
    {
        if (Pending[i].Id == Id)
        {
            RemoveIdx = i;
            break;
        }
    }
    if (RemoveIdx == INDEX_NONE)
        return false;

    const FScheduledBanEntry RemovedEntry = Pending[RemoveIdx];
    Pending.RemoveAt(RemoveIdx);
    if (!SaveToFile())
    {
        Pending.Insert(RemovedEntry, RemoveIdx);
        UE_LOG(LogScheduledBanRegistry, Error,
            TEXT("ScheduledBanRegistry: failed to save after deleting scheduled ban #%lld"), Id);
        return false;
    }
    OutEntry = RemovedEntry;
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
//  Tick
// ─────────────────────────────────────────────────────────────────────────────

void UScheduledBanRegistry::Tick(float DeltaTime)
{
    AccumulatedSeconds += DeltaTime;
    if (AccumulatedSeconds < TickIntervalSeconds) return;
    AccumulatedSeconds -= TickIntervalSeconds;

    const FDateTime Now = FDateTime::UtcNow();

    // Collect due entries without removing them from Pending yet.
    // We apply first and only commit the Pending changes after we know the
    // outcome of each apply — this eliminates the durability window that existed
    // when entries were removed from the on-disk file before apply was attempted:
    // if the server crashed between the two saves, failed entries were permanently
    // lost from the file even though they had never been applied.
    TArray<FScheduledBanEntry> Due;
    {
        FScopeLock Lock(&Mutex);
        for (const FScheduledBanEntry& E : Pending)
        {
            if (E.EffectiveAt <= Now)
                Due.Add(E);
        }
    }

    if (Due.IsEmpty()) return;

    // Apply each due entry outside the lock (AddBan may do disk I/O).
    // Track which entries were applied and which failed (with updated RetryCount).
    TArray<int64>              AppliedIds;
    TArray<FScheduledBanEntry> FailedEntries; // copies with incremented RetryCount

    for (FScheduledBanEntry S : Due) // value copy so we can increment RetryCount
    {
        if (ApplyScheduledBan(S))
        {
            AppliedIds.Add(S.Id);
        }
        else
        {
            // Guard against signed overflow: S.RetryCount + 1 is UB when
            // RetryCount == INT32_MAX. Use a pre-check instead of FMath::Min
            // which evaluates the addition unconditionally.
            S.RetryCount = (S.RetryCount < INT32_MAX) ? S.RetryCount + 1 : INT32_MAX;
            FailedEntries.Add(S);
        }
    }

    // Under the lock: remove applied entries and entries that have exceeded the
    // retry cap; update RetryCount in Pending for surviving failures; then save
    // once so the persisted RetryCount survives the next restart.
    {
        FScopeLock Lock(&Mutex);
        // Remove `const` so that the retry-count updates applied to PrevPending
        // elements inside the rollback loop below are preserved when
        // `Pending = PrevPending` restores the snapshot.  With `const` the
        // range-for variable binds as a copy and mutations are silently lost,
        // causing the 5-attempt retry cap to never advance past its pre-save value.
        TArray<FScheduledBanEntry> PrevPending = Pending;

        // Build the set of IDs to remove entirely.
        TSet<int64> IdsToRemove(AppliedIds);
        for (const FScheduledBanEntry& FE : FailedEntries)
        {
            if (FE.RetryCount >= 5) // 5-attempt cap: drop after 5 failed retries
            {
                UE_LOG(LogScheduledBanRegistry, Error,
                    TEXT("ScheduledBanRegistry: dropping entry id=%lld after %d failed attempts"),
                    FE.Id, FE.RetryCount);
                IdsToRemove.Add(FE.Id);

                // Write an audit log entry so admins can see that the ban was not enforced.
                if (UBanAuditLog* AuditLog = GetGameInstance() ? GetGameInstance()->GetSubsystem<UBanAuditLog>() : nullptr)
                {
                    AuditLog->LogAction(
                        TEXT("scheduled_ban_dropped"), FE.Uid, FE.PlayerName,
                        TEXT("system"), FE.ScheduledBy,
                        FString::Printf(TEXT("Scheduled ban id=%lld dropped after %d failed apply attempts"),
                            FE.Id, FE.RetryCount));
                }
            }
        }

        // Walk Pending in reverse so RemoveAt indices stay valid.
        for (int32 i = Pending.Num() - 1; i >= 0; --i)
        {
            const int64 Id = Pending[i].Id;

            if (IdsToRemove.Contains(Id))
            {
                Pending.RemoveAt(i);
            }
            else
            {
                // If this entry failed, update its persisted RetryCount so the
                // cap is honoured correctly after a server restart.
                for (const FScheduledBanEntry& FE : FailedEntries)
                {
                    if (FE.Id == Id)
                    {
                        Pending[i].RetryCount = FE.RetryCount;
                        break;
                    }
                }
            }
        }

        if (!SaveToFile())
        {
            // Restore the structural state (re-add entries that were removed),
            // but carry over the updated RetryCount values so the 5-attempt cap
            // is honoured correctly even if the save keeps failing.
            for (FScheduledBanEntry& Prev : PrevPending)
            {
                for (const FScheduledBanEntry& FE : FailedEntries)
                {
                    if (FE.Id == Prev.Id && FE.RetryCount > Prev.RetryCount)
                    {
                        Prev.RetryCount = FE.RetryCount;
                        break;
                    }
                }
            }
            Pending = PrevPending;
            UE_LOG(LogScheduledBanRegistry, Error,
                TEXT("ScheduledBanRegistry: failed to save after processing %d due entry(ies)"),
                Due.Num());
        }
    }
}

bool UScheduledBanRegistry::ApplyScheduledBan(const FScheduledBanEntry& Entry)
{
    UGameInstance* GI = GetGameInstance();
    if (!GI) return false;

    UBanDatabase* DB = GI->GetSubsystem<UBanDatabase>();
    if (!DB) return false;

    FBanEntry Existing;
    if (DB->IsCurrentlyBanned(Entry.Uid, Existing) && MatchesScheduledBan(Existing, Entry))
    {
        UE_LOG(LogScheduledBanRegistry, Log,
            TEXT("ScheduledBanRegistry: scheduled ban #%lld for %s was already applied earlier; removing stale pending entry"),
            Entry.Id, *Entry.Uid);
        return true;
    }

    FBanEntry Ban;
    Ban.Uid        = Entry.Uid;
    UBanDatabase::ParseUid(Entry.Uid, Ban.Platform, Ban.PlayerUID);
    Ban.PlayerName      = Entry.PlayerName;
    Ban.Reason          = Entry.Reason;
    Ban.BannedBy        = Entry.ScheduledBy;
    const FDateTime Now = FDateTime::UtcNow();
    Ban.BanDate         = Now;
    Ban.Category        = Entry.Category;
    Ban.bIsPermanent    = (Entry.DurationMinutes <= 0);
    Ban.ExpireDate      = Ban.bIsPermanent
        ? FDateTime(0)
        : Now + FTimespan::FromMinutes(Entry.DurationMinutes);

    // Use AddBanSkipIfPermanentExists so the "permanent ban → skip" guard and
    // the actual insert happen under a single DB lock.  The previous two-step
    // pattern (IsCurrentlyBanned + AddBan as separate calls) had a TOCTOU window
    // where a concurrent operation (e.g. an incoming REST API ban) could insert a
    // permanent ban between the check and the upsert, silently overwriting it.
    bool bSkippedPermanent = false;
    if (!DB->AddBanSkipIfPermanentExists(Ban, bSkippedPermanent))
    {
        if (bSkippedPermanent)
        {
            UE_LOG(LogScheduledBanRegistry, Log,
                TEXT("ScheduledBanRegistry: skipping scheduled ban #%lld for %s — permanent ban already active"),
                Entry.Id, *Entry.Uid);
            return true; // intentional skip — do not re-queue
        }
        UE_LOG(LogScheduledBanRegistry, Warning,
            TEXT("ScheduledBanRegistry: failed to apply scheduled ban #%lld for %s"),
            Entry.Id, *Entry.Uid);
        return false; // transient failure — re-queue for retry
    }
    if (UWorld* World = GI->GetWorld())
        UBanEnforcer::KickConnectedPlayer(World, Entry.Uid, Ban.GetKickMessage());

    // Add counterpart bans (IP↔EOS) so the scheduled ban blocks all identities.
    if (UPlayerSessionRegistry* SR = GI->GetSubsystem<UPlayerSessionRegistry>())
    {
        FString Plat, RawId;
        UBanDatabase::ParseUid(Entry.Uid, Plat, RawId);
        if (Plat == TEXT("EOS"))
        {
            FPlayerSessionRecord SR_Rec;
            if (SR->FindByUid(Entry.Uid, SR_Rec) && !SR_Rec.IpAddress.IsEmpty())
            {
                const FString IpUid = UBanDatabase::MakeUid(TEXT("IP"), SR_Rec.IpAddress);
                FBanEntry IpBan;
                IpBan.Uid = IpUid;
                IpBan.Platform = TEXT("IP");
                IpBan.PlayerUID = SR_Rec.IpAddress;
                IpBan.PlayerName = Entry.PlayerName;
                IpBan.Reason = Ban.Reason;
                IpBan.BannedBy = Ban.BannedBy;
                IpBan.BanDate = Ban.BanDate;
                IpBan.bIsPermanent = Ban.bIsPermanent;
                IpBan.ExpireDate = Ban.ExpireDate;
                IpBan.LinkedUids.Add(Entry.Uid);
                bool bIpSkipped = false;
                if (DB->AddBanSkipIfPermanentExists(IpBan, bIpSkipped) || bIpSkipped)
                    DB->LinkBans(Entry.Uid, IpUid);
            }
        }
    }

    FBanDiscordNotifier::NotifyBanCreated(Ban);
    if (UBanAuditLog* AuditLog = GI->GetSubsystem<UBanAuditLog>())
        AuditLog->LogAction(TEXT("ban"), Entry.Uid, Entry.PlayerName,
            TEXT("scheduled"), Entry.ScheduledBy,
            FString::Printf(TEXT("Scheduled ban applied. Reason: %s"), *Entry.Reason));

    UE_LOG(LogScheduledBanRegistry, Log,
        TEXT("ScheduledBanRegistry: applied scheduled ban #%lld for %s"),
        Entry.Id, *Entry.Uid);
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
//  File I/O
// ─────────────────────────────────────────────────────────────────────────────

void UScheduledBanRegistry::LoadFromFile()
{
    // Always hold the mutex regardless of calling context (Initialize or reload).
    FScopeLock Lock(&Mutex);
    Pending.Empty();

    FString RawJson;
    if (!FFileHelper::LoadFileToString(RawJson, *FilePath))
        return;

    TSharedPtr<FJsonObject> Root;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(RawJson);
    if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
    {
        UE_LOG(LogScheduledBanRegistry, Warning,
            TEXT("ScheduledBanRegistry: failed to parse %s — starting empty"), *FilePath);
        return;
    }

    const TArray<TSharedPtr<FJsonValue>>* Arr = nullptr;
    if (Root->TryGetArrayField(TEXT("scheduled"), Arr) && Arr)
    {
        for (const TSharedPtr<FJsonValue>& Val : *Arr)
        {
            if (!Val.IsValid()) continue;
            const TSharedPtr<FJsonObject>* ObjPtr = nullptr;
            if (!Val->TryGetObject(ObjPtr) || !ObjPtr) continue;

            FScheduledBanEntry Entry;
            {
                FString IdStr;
                double IdDbl = 0.0;
                if ((*ObjPtr)->TryGetStringField(TEXT("id"), IdStr)
                    && IdStr.IsNumeric() && IdStr.Len() <= 19
                    && (IdStr.Len() < 19 || IdStr <= TEXT("9223372036854775807")))
                    Entry.Id = FCString::Atoi64(*IdStr);
                else if ((*ObjPtr)->TryGetNumberField(TEXT("id"), IdDbl)
                    && IdDbl >= 1.0 && IdDbl < static_cast<double>(INT64_MAX)
                    && FMath::Fmod(IdDbl, 1.0) == 0.0)
                    Entry.Id = static_cast<int64>(IdDbl);
            }
            if (Entry.Id <= 0)
            {
                UE_LOG(LogScheduledBanRegistry, Warning,
                    TEXT("ScheduledBanRegistry: skipping entry with invalid id"));
                continue;
            }

            (*ObjPtr)->TryGetStringField(TEXT("uid"),          Entry.Uid);
            (*ObjPtr)->TryGetStringField(TEXT("playerName"),   Entry.PlayerName);
            (*ObjPtr)->TryGetStringField(TEXT("reason"),       Entry.Reason);
            (*ObjPtr)->TryGetStringField(TEXT("scheduledBy"),  Entry.ScheduledBy);
            (*ObjPtr)->TryGetStringField(TEXT("category"),     Entry.Category);

            double DurDbl = 0.0;
            if ((*ObjPtr)->TryGetNumberField(TEXT("durationMinutes"), DurDbl)
                && FMath::IsFinite(DurDbl) && DurDbl >= 0.0
                && DurDbl <= static_cast<double>(MAX_int32)
                && FMath::Fmod(DurDbl, 1.0) == 0.0)
                Entry.DurationMinutes = static_cast<int32>(DurDbl);

            double RetryDbl = 0.0;
            if ((*ObjPtr)->TryGetNumberField(TEXT("retryCount"), RetryDbl)
                && RetryDbl > 0.0 && RetryDbl <= static_cast<double>(MAX_int32)
                && FMath::Fmod(RetryDbl, 1.0) == 0.0)
                Entry.RetryCount = static_cast<int32>(RetryDbl);

            FString EffStr, CreatedStr;
            bool bEffectiveAtValid = false;
            if ((*ObjPtr)->TryGetStringField(TEXT("effectiveAt"), EffStr))
            {
                if (FDateTime::ParseIso8601(*EffStr, Entry.EffectiveAt))
                    bEffectiveAtValid = true;
                else
                    UE_LOG(LogScheduledBanRegistry, Warning,
                        TEXT("ScheduledBanRegistry: skipping entry for uid '%s' — malformed effectiveAt '%s'"),
                        *Entry.Uid, *EffStr);
            }
            if ((*ObjPtr)->TryGetStringField(TEXT("createdAt"), CreatedStr))
            {
                if (!FDateTime::ParseIso8601(*CreatedStr, Entry.CreatedAt))
                    UE_LOG(LogScheduledBanRegistry, Warning,
                        TEXT("ScheduledBanRegistry: uid='%s' has malformed createdAt '%s' — using default"),
                        *Entry.Uid, *CreatedStr);
            }

            if (!Entry.Uid.IsEmpty() && bEffectiveAtValid)
                Pending.Add(Entry);
        }
    }

    // Restore the NextId counter.  Prefer the persisted "nextId" field (written
    // since BUG-03 fix) over the scan-based reconstruction so that once all
    // pending entries fire (and are removed from the list) the counter does not
    // regress to 1 and cause duplicate-Id allocation.  Fall back to the scan for
    // files written by older builds that did not persist nextId.
    FString StoredNextIdStr;
    double  StoredNextIdDbl = 0.0;
    if (Root->TryGetStringField(TEXT("nextId"), StoredNextIdStr) && !StoredNextIdStr.IsEmpty()
        && StoredNextIdStr.IsNumeric() && StoredNextIdStr.Len() <= 19
        && (StoredNextIdStr.Len() < 19 || StoredNextIdStr <= TEXT("9223372036854775807")))
    {
        const int64 Parsed = FCString::Atoi64(*StoredNextIdStr);
        NextId = (Parsed >= 0) ? Parsed : 1;
    }
    else if (Root->TryGetNumberField(TEXT("nextId"), StoredNextIdDbl)
             && StoredNextIdDbl >= 0.0
             && StoredNextIdDbl < static_cast<double>(INT64_MAX)
             && FMath::Fmod(StoredNextIdDbl, 1.0) == 0.0) // guard against Inf/NaN before cast
    {
        NextId = static_cast<int64>(StoredNextIdDbl);
    }
    else
    {
        // Legacy files without a nextId field: reconstruct from the max stored Id.
        NextId = 1;
        for (const FScheduledBanEntry& E : Pending)
            if (E.Id >= NextId) NextId = (E.Id < INT64_MAX) ? E.Id + 1 : 0;
    }
}

bool UScheduledBanRegistry::SaveToFile() const
{
    // Caller must hold Mutex.
    TArray<TSharedPtr<FJsonValue>> Arr;
    Arr.Reserve(Pending.Num());
    for (const FScheduledBanEntry& E : Pending)
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("id"),              FString::Printf(TEXT("%lld"), E.Id));
        Obj->SetStringField(TEXT("uid"),             E.Uid);
        Obj->SetStringField(TEXT("playerName"),      E.PlayerName);
        Obj->SetStringField(TEXT("reason"),          E.Reason);
        Obj->SetStringField(TEXT("scheduledBy"),     E.ScheduledBy);
        Obj->SetStringField(TEXT("category"),        E.Category);
        // int32 values — exactly representable in double; the int64-string
        // convention only applies to IDs that could exceed 2^53.
        Obj->SetNumberField(TEXT("durationMinutes"), static_cast<double>(E.DurationMinutes));
        Obj->SetStringField(TEXT("effectiveAt"),     E.EffectiveAt.ToIso8601());
        Obj->SetStringField(TEXT("createdAt"),       E.CreatedAt.ToIso8601());
        // Persist retryCount so that the 5-attempt cap survives server restarts.
        // Without this field the count resets to 0 on every restart, letting
        // permanently-failing entries loop indefinitely across reboots.
        if (E.RetryCount > 0)
            Obj->SetNumberField(TEXT("retryCount"), static_cast<double>(E.RetryCount));
        Arr.Add(MakeShared<FJsonValueObject>(Obj));
    }

    TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
    Root->SetStringField(TEXT("nextId"),   FString::Printf(TEXT("%lld"), NextId));
    Root->SetArrayField(TEXT("scheduled"), Arr);

    FString JsonStr;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonStr);
    if (!FJsonSerializer::Serialize(Root.ToSharedRef(), Writer))
    {
        UE_LOG(LogScheduledBanRegistry, Error,
            TEXT("ScheduledBanRegistry: failed to serialize"));
        return false;
    }

    const FString TmpPath = FilePath + TEXT(".tmp");
    if (!FFileHelper::SaveStringToFile(JsonStr, *TmpPath,
        FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
    {
        UE_LOG(LogScheduledBanRegistry, Error,
            TEXT("ScheduledBanRegistry: failed to write temp file %s"), *TmpPath);
        return false;
    }
    if (!IFileManager::Get().Move(*FilePath, *TmpPath, /*bReplace=*/true))
    {
        UE_LOG(LogScheduledBanRegistry, Error,
            TEXT("ScheduledBanRegistry: failed to replace %s with temp file"), *FilePath);
        IFileManager::Get().Delete(*TmpPath);
        return false;
    }
    return true;
}

FString UScheduledBanRegistry::GetRegistryPath() const
{
    const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
    FString BaseDir;
    if (Cfg && !Cfg->DatabasePath.IsEmpty())
        BaseDir = FPaths::GetPath(Cfg->DatabasePath);
    else
        BaseDir = FPaths::ProjectSavedDir() / TEXT("BanSystem");

    return BaseDir / TEXT("scheduled_bans.json");
}
