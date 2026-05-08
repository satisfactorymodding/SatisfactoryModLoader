// Copyright Yamahasxviper. All Rights Reserved.

#include "MuteRegistry.h"
#include "BanSystemConfig.h"

#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFileManager.h"
#include "HAL/FileManager.h"

DEFINE_LOG_CATEGORY(LogMuteRegistry);

// ─────────────────────────────────────────────────────────────────────────────
//  USubsystem lifecycle
// ─────────────────────────────────────────────────────────────────────────────

void UMuteRegistry::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    FilePath = GetRegistryPath();

    const FString Dir = FPaths::GetPath(FilePath);
    IPlatformFile& PF = FPlatformFileManager::Get().GetPlatformFile();
    if (!PF.DirectoryExists(*Dir))
        PF.CreateDirectoryTree(*Dir);

    LoadFromFile();

    UE_LOG(LogMuteRegistry, Log,
        TEXT("MuteRegistry: loaded %s (%d mute(s))"),
        *FilePath, Mutes.Num());
}

void UMuteRegistry::Deinitialize()
{
    Super::Deinitialize();
}

// ─────────────────────────────────────────────────────────────────────────────
//  Public API
// ─────────────────────────────────────────────────────────────────────────────

void UMuteRegistry::MutePlayer(const FString& Uid, const FString& PlayerName,
                                const FString& Reason, const FString& MutedBy,
                                int32 ExpiryMinutes)
{
    if (Uid.IsEmpty()) return;

    FMuteEntry Entry;
    Entry.Uid         = Uid;
    Entry.PlayerName  = PlayerName;
    Entry.Reason      = Reason;
    Entry.MutedBy     = MutedBy;
    const FDateTime Now = FDateTime::UtcNow();
    Entry.MuteDate    = Now;

    if (ExpiryMinutes > 0)
    {
        Entry.bIsIndefinite = false;
        Entry.ExpireDate    = Now + FTimespan::FromMinutes(ExpiryMinutes);
    }
    else
    {
        Entry.bIsIndefinite = true;
        Entry.ExpireDate    = FDateTime(0);
    }

    bool bPersisted = false;
    {
        FScopeLock Lock(&Mutex);
        // Find and save the existing entry for this UID so it can be restored
        // if SaveToFile fails.  At most one entry exists per UID (MutePlayer
        // enforces uniqueness via RemoveAll below), so this is O(1) storage
        // rather than an O(n) full-array copy.
        FMuteEntry PrevEntry;
        bool bHadPrevEntry = false;
        for (const FMuteEntry& M : Mutes)
        {
            if (M.Uid.Equals(Uid, ESearchCase::IgnoreCase))
            {
                PrevEntry = M;
                bHadPrevEntry = true;
                break;
            }
        }
        // Replace any existing mute for this UID.
        Mutes.RemoveAll([&Uid](const FMuteEntry& M)
        {
            return M.Uid.Equals(Uid, ESearchCase::IgnoreCase);
        });
        Mutes.Add(Entry);
        if (!SaveToFile())
        {
            // Rollback: remove the newly added entry and restore the old one.
            Mutes.RemoveAt(Mutes.Num() - 1);
            if (bHadPrevEntry) Mutes.Add(PrevEntry);
            UE_LOG(LogMuteRegistry, Error,
                TEXT("MuteRegistry: failed to save mutes.json after muting %s"), *Uid);
        }
        else
        {
            bPersisted = true;
        }
    }

    // Broadcast outside the lock only after successful persistence.
    if (bPersisted)
        OnPlayerMuted.Broadcast(Entry, ExpiryMinutes > 0);
}

bool UMuteRegistry::UnmutePlayer(const FString& Uid)
{
    bool bRemoved = false;
    bool bWasActive = false;

    {
        FScopeLock Lock(&Mutex);
        // Capture the entry we are about to remove so it can be restored if
        // SaveToFile fails.  At most one entry exists per UID, so this is
        // O(1) storage rather than an O(n) full-array copy.
        FMuteEntry RemovedEntry;
        for (const FMuteEntry& M : Mutes)
        {
            if (M.Uid.Equals(Uid, ESearchCase::IgnoreCase))
            {
                bWasActive = !M.IsExpired();
                RemovedEntry = M;
                break;
            }
        }
        const int32 Before = Mutes.Num();
        Mutes.RemoveAll([&Uid](const FMuteEntry& M)
        {
            return M.Uid.Equals(Uid, ESearchCase::IgnoreCase);
        });
        bRemoved = Mutes.Num() < Before;
        if (bRemoved && !SaveToFile())
        {
            Mutes.Add(RemovedEntry);
            bRemoved = false;
            bWasActive = false;
            UE_LOG(LogMuteRegistry, Error,
                TEXT("MuteRegistry: failed to save mutes.json after unmuting %s"), *Uid);
        }
    }

    if (bRemoved && bWasActive)
        OnPlayerUnmuted.Broadcast(Uid);

    return bRemoved;
}

bool UMuteRegistry::IsMuted(const FString& Uid) const
{
    FScopeLock Lock(&Mutex);
    for (const FMuteEntry& M : Mutes)
    {
        if (M.Uid.Equals(Uid, ESearchCase::IgnoreCase))
            return !M.IsExpired();
    }
    return false;
}

bool UMuteRegistry::GetMuteEntry(const FString& Uid, FMuteEntry& OutEntry) const
{
    FScopeLock Lock(&Mutex);
    for (const FMuteEntry& M : Mutes)
    {
        if (M.Uid.Equals(Uid, ESearchCase::IgnoreCase))
        {
            if (M.IsExpired()) return false;
            OutEntry = M;
            return true;
        }
    }
    return false;
}

TArray<FMuteEntry> UMuteRegistry::GetAllMutes() const
{
    FScopeLock Lock(&Mutex);
    TArray<FMuteEntry> Result;
    for (const FMuteEntry& M : Mutes)
    {
        if (!M.IsExpired()) Result.Add(M);
    }
    return Result;
}

bool UMuteRegistry::UpdateMuteReason(const FString& Uid, const FString& NewReason)
{
    FScopeLock Lock(&Mutex);
    for (FMuteEntry& M : Mutes)
    {
        if (M.Uid.Equals(Uid, ESearchCase::IgnoreCase) && !M.IsExpired())
        {
            const FString PrevReason = M.Reason;
            M.Reason = NewReason;
            if (!SaveToFile())
            {
                M.Reason = PrevReason;
                UE_LOG(LogMuteRegistry, Error,
                    TEXT("MuteRegistry: failed to save mutes.json after updating reason for %s"), *Uid);
                return false;
            }
            return true;
        }
    }
    return false;
}

TArray<FString> UMuteRegistry::TickExpiry()
{
    TArray<FString> Expired;

    {
        FScopeLock Lock(&Mutex);
        // Collect only the entries being expired so that, if SaveToFile fails,
        // we can restore exactly those entries rather than copying the full Mutes
        // array.  This is O(expired_count) storage, typically 0 in steady state.
        TArray<FMuteEntry> ExpiredEntries;
        const int32 Before = Mutes.Num();
        Mutes.RemoveAll([&ExpiredEntries, &Expired](const FMuteEntry& M) -> bool
        {
            if (!M.bIsIndefinite && M.IsExpired())
            {
                ExpiredEntries.Add(M);
                Expired.Add(M.Uid);
                return true;
            }
            return false;
        });

        if (Mutes.Num() < Before)
        {
            if (!SaveToFile())
            {
                for (const FMuteEntry& E : ExpiredEntries)
                    Mutes.Add(E);
                Expired.Reset();
                UE_LOG(LogMuteRegistry, Error,
                    TEXT("MuteRegistry: failed to save mutes.json after expiry — "
                         "rolling back in-memory expiry removals."));
            }
            else
            {
                UE_LOG(LogMuteRegistry, Log,
                    TEXT("MuteRegistry: expired %d timed mute(s)."), Expired.Num());
            }
        }
    }

    for (const FString& Uid : Expired)
        OnPlayerUnmuted.Broadcast(Uid);

    return Expired;
}

// ─────────────────────────────────────────────────────────────────────────────
//  File I/O
// ─────────────────────────────────────────────────────────────────────────────

FString UMuteRegistry::GetRegistryPath() const
{
    const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
    FString BaseDir;
    if (Cfg && !Cfg->DatabasePath.IsEmpty())
        BaseDir = FPaths::GetPath(Cfg->DatabasePath) / TEXT("BanChatCommands");
    else
        BaseDir = FPaths::ProjectSavedDir() / TEXT("BanChatCommands");
    return BaseDir / TEXT("mutes.json");
}

void UMuteRegistry::LoadFromFile()
{
    FScopeLock Lock(&Mutex);
    Mutes.Empty();

    FString RawJson;
    if (!FFileHelper::LoadFileToString(RawJson, *FilePath))
        return;

    TSharedPtr<FJsonObject> Root;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(RawJson);
    if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
    {
        UE_LOG(LogMuteRegistry, Warning,
            TEXT("MuteRegistry: failed to parse %s — starting empty"), *FilePath);
        return;
    }

    const TArray<TSharedPtr<FJsonValue>>* Arr = nullptr;
    int32 LoadedCount = 0;
    int32 ExpiredSkipped = 0;
    if (Root->TryGetArrayField(TEXT("mutes"), Arr) && Arr)
    {
        for (const TSharedPtr<FJsonValue>& Val : *Arr)
        {
            if (!Val.IsValid()) continue;
            const TSharedPtr<FJsonObject>* ObjPtr = nullptr;
            if (!Val->TryGetObject(ObjPtr) || !ObjPtr) continue;

            FMuteEntry Entry;
            (*ObjPtr)->TryGetStringField(TEXT("uid"),        Entry.Uid);
            (*ObjPtr)->TryGetStringField(TEXT("playerName"), Entry.PlayerName);
            (*ObjPtr)->TryGetStringField(TEXT("reason"),     Entry.Reason);
            (*ObjPtr)->TryGetStringField(TEXT("mutedBy"),    Entry.MutedBy);
            (*ObjPtr)->TryGetBoolField  (TEXT("isIndefinite"), Entry.bIsIndefinite);

            FString DateStr;
            if ((*ObjPtr)->TryGetStringField(TEXT("muteDate"), DateStr))
            {
                if (!FDateTime::ParseIso8601(*DateStr, Entry.MuteDate))
                {
                    UE_LOG(LogMuteRegistry, Warning,
                        TEXT("MuteRegistry: uid='%s' has malformed muteDate '%s' — skipping entry"),
                        *Entry.Uid, *DateStr);
                    continue;
                }
            }
            if ((*ObjPtr)->TryGetStringField(TEXT("expireDate"), DateStr))
            {
                if (!Entry.bIsIndefinite && !FDateTime::ParseIso8601(*DateStr, Entry.ExpireDate))
                {
                    UE_LOG(LogMuteRegistry, Warning,
                        TEXT("MuteRegistry: uid='%s' has malformed expireDate '%s' — skipping entry"),
                        *Entry.Uid, *DateStr);
                    continue;
                }
            }

            if (Entry.Uid.IsEmpty()) continue;

            if (Entry.IsExpired())
            {
                ++ExpiredSkipped;
            }
            else
            {
                Mutes.Add(Entry);
                ++LoadedCount;
            }
        }
    }

    // Compact the file when expired entries were skipped so they do not
    // accumulate on disk indefinitely across server restarts.
    if (ExpiredSkipped > 0)
    {
        UE_LOG(LogMuteRegistry, Log,
            TEXT("MuteRegistry: discarding %d expired mute(s) from disk during load."),
            ExpiredSkipped);
        if (!SaveToFile())
            UE_LOG(LogMuteRegistry, Error,
                TEXT("MuteRegistry: failed to compact mutes.json after skipping %d expired entry(s)"),
                ExpiredSkipped);
    }
}

bool UMuteRegistry::SaveToFile() const
{
    // Caller must already hold Mutex.
    TArray<TSharedPtr<FJsonValue>> MuteArr;
    MuteArr.Reserve(Mutes.Num());
    for (const FMuteEntry& M : Mutes)
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("uid"),         M.Uid);
        Obj->SetStringField(TEXT("playerName"),  M.PlayerName);
        Obj->SetStringField(TEXT("reason"),      M.Reason);
        Obj->SetStringField(TEXT("mutedBy"),     M.MutedBy);
        Obj->SetStringField(TEXT("muteDate"),    M.MuteDate.ToIso8601());
        if (M.bIsIndefinite)
            Obj->SetField(TEXT("expireDate"), MakeShared<FJsonValueNull>());
        else
            Obj->SetStringField(TEXT("expireDate"), M.ExpireDate.ToIso8601());
        Obj->SetBoolField  (TEXT("isIndefinite"), M.bIsIndefinite);
        MuteArr.Add(MakeShared<FJsonValueObject>(Obj));
    }

    TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
    Root->SetArrayField(TEXT("mutes"), MuteArr);

    FString JsonStr;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonStr);
    if (!FJsonSerializer::Serialize(Root.ToSharedRef(), Writer))
    {
        UE_LOG(LogMuteRegistry, Error,
            TEXT("MuteRegistry: failed to serialize mutes"));
        return false;
    }

    const FString TmpPath = FilePath + TEXT(".tmp");
    if (!FFileHelper::SaveStringToFile(JsonStr, *TmpPath,
        FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
    {
        UE_LOG(LogMuteRegistry, Error,
            TEXT("MuteRegistry: failed to write temp file %s"), *TmpPath);
        return false;
    }
    if (!IFileManager::Get().Move(*FilePath, *TmpPath, /*bReplace=*/true))
    {
        UE_LOG(LogMuteRegistry, Error,
            TEXT("MuteRegistry: failed to replace %s with temp file"), *FilePath);
        IFileManager::Get().Delete(*TmpPath);
        return false;
    }

    return true;
}
