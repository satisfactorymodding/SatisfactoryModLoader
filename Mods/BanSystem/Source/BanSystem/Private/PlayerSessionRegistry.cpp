// Copyright Yamahasxviper. All Rights Reserved.

#include "PlayerSessionRegistry.h"
#include "BanSystemConfig.h"
#include "BanWebSocketPusher.h"

#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFileManager.h"
#include "HAL/FileManager.h"

DEFINE_LOG_CATEGORY(LogPlayerSessionRegistry);

// ─────────────────────────────────────────────────────────────────────────────
//  USubsystem lifecycle
// ─────────────────────────────────────────────────────────────────────────────

void UPlayerSessionRegistry::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    FilePath = GetRegistryPath();

    const FString Dir = FPaths::GetPath(FilePath);
    IPlatformFile& PF = FPlatformFileManager::Get().GetPlatformFile();
    if (!PF.DirectoryExists(*Dir))
        PF.CreateDirectoryTree(*Dir);

    LoadFromFile();

    UE_LOG(LogPlayerSessionRegistry, Log,
        TEXT("PlayerSessionRegistry: loaded %s (%d record(s))"),
        *FilePath, Records.Num());
}

void UPlayerSessionRegistry::Deinitialize()
{
    Super::Deinitialize();
}

// ─────────────────────────────────────────────────────────────────────────────
//  Public API
// ─────────────────────────────────────────────────────────────────────────────

void UPlayerSessionRegistry::RecordSession(const FString& Uid, const FString& DisplayName,
                                           const FString& IpAddress, const FString& ClientVersion)
{
    if (Uid.IsEmpty()) return;

    bool bPersisted = false;
    {
        FScopeLock Lock(&Mutex);

        // Capture the current time while holding the lock so the stored
        // LastSeen value is consistent with the moment of the actual insert.
        const FString NowStr = FDateTime::UtcNow().ToIso8601();

        bool bUpdated = false;
        for (FPlayerSessionRecord& R : Records)
        {
            if (R.Uid.Equals(Uid, ESearchCase::IgnoreCase))
            {
                const FPlayerSessionRecord PrevRecord = R;
                R.DisplayName = DisplayName;
                R.LastSeen    = NowStr;
                if (!IpAddress.IsEmpty())
                    R.IpAddress = IpAddress;
                if (!ClientVersion.IsEmpty())
                    R.ClientVersion = ClientVersion;
                if (!SaveToFile())
                {
                    R = PrevRecord;
                    UE_LOG(LogPlayerSessionRegistry, Warning,
                        TEXT("PlayerSessionRegistry: failed to save updated session for uid='%s'"), *Uid);
                }
                else
                {
                    bPersisted = true;
                }
                bUpdated = true;
                break;
            }
        }

        if (!bUpdated)
        {
            FPlayerSessionRecord NewRec;
            NewRec.Uid           = Uid;
            NewRec.DisplayName   = DisplayName;
            NewRec.LastSeen      = NowStr;
            NewRec.IpAddress     = IpAddress;
            NewRec.ClientVersion = ClientVersion;
            Records.Add(NewRec);
            if (!SaveToFile())
            {
                Records.RemoveAt(Records.Num() - 1);
                UE_LOG(LogPlayerSessionRegistry, Warning,
                    TEXT("PlayerSessionRegistry: failed to save new session for uid='%s'"), *Uid);
            }
            else
            {
                bPersisted = true;
            }
        }
    }

    // Push player-join event via WebSocket (outside the lock) only after a
    // successful save so events do not announce non-persisted state.
    if (bPersisted)
    {
        TSharedPtr<FJsonObject> Fields = MakeShared<FJsonObject>();
        Fields->SetStringField(TEXT("uid"),         Uid);
        Fields->SetStringField(TEXT("displayName"), DisplayName);
        if (!IpAddress.IsEmpty())
            Fields->SetStringField(TEXT("ipAddress"), IpAddress);
        if (!ClientVersion.IsEmpty())
            Fields->SetStringField(TEXT("clientVersion"), ClientVersion);
        UBanWebSocketPusher::PushEvent(TEXT("player_join"), Fields);
    }
}

TArray<FPlayerSessionRecord> UPlayerSessionRegistry::FindByName(const FString& NameSubstring) const
{
    FScopeLock Lock(&Mutex);

    TArray<FPlayerSessionRecord> Result;
    for (const FPlayerSessionRecord& R : Records)
    {
        if (R.DisplayName.Contains(NameSubstring, ESearchCase::IgnoreCase))
            Result.Add(R);
    }
    return Result;
}

bool UPlayerSessionRegistry::FindByUid(const FString& Uid, FPlayerSessionRecord& OutRecord) const
{
    FScopeLock Lock(&Mutex);

    for (const FPlayerSessionRecord& R : Records)
    {
        if (R.Uid.Equals(Uid, ESearchCase::IgnoreCase))
        {
            OutRecord = R;
            return true;
        }
    }
    return false;
}

TArray<FPlayerSessionRecord> UPlayerSessionRegistry::FindByIp(const FString& IpSubstring) const
{
    FScopeLock Lock(&Mutex);

    TArray<FPlayerSessionRecord> Result;
    for (const FPlayerSessionRecord& R : Records)
    {
        if (!R.IpAddress.IsEmpty() && R.IpAddress.Contains(IpSubstring, ESearchCase::IgnoreCase))
            Result.Add(R);
    }
    return Result;
}

TArray<FPlayerSessionRecord> UPlayerSessionRegistry::GetAllRecords() const
{
    FScopeLock Lock(&Mutex);
    return Records;
}

int32 UPlayerSessionRegistry::GetCount() const
{
    FScopeLock Lock(&Mutex);
    return Records.Num();
}

int32 UPlayerSessionRegistry::PruneOldRecords(int32 DaysToKeep)
{
    if (DaysToKeep <= 0) return 0;

    const FDateTime Cutoff = FDateTime::UtcNow() - FTimespan::FromDays(static_cast<double>(DaysToKeep));
    FScopeLock Lock(&Mutex);
    const TArray<FPlayerSessionRecord> PrevRecords = Records;

    const int32 Before = Records.Num();
    Records.RemoveAll([&Cutoff](const FPlayerSessionRecord& R) -> bool
    {
        FDateTime LastSeenDt;
        // M13: treat a corrupted LastSeen as if the record is expired so that
        // bad data doesn't prevent the record from being pruned.
        if (!FDateTime::ParseIso8601(*R.LastSeen, LastSeenDt))
            return true;
        return LastSeenDt < Cutoff;
    });
    const int32 Pruned = Before - Records.Num();
    if (Pruned > 0)
    {
        if (!SaveToFile())
        {
            Records = PrevRecords;
            UE_LOG(LogPlayerSessionRegistry, Warning,
                TEXT("PlayerSessionRegistry: failed to save after pruning %d record(s)"), Pruned);
            return 0;
        }
        UE_LOG(LogPlayerSessionRegistry, Log,
            TEXT("PlayerSessionRegistry: pruned %d record(s) older than %d day(s)"),
            Pruned, DaysToKeep);
    }
    return Pruned;
}

// ─────────────────────────────────────────────────────────────────────────────
//  File I/O
// ─────────────────────────────────────────────────────────────────────────────

void UPlayerSessionRegistry::LoadFromFile()
{
    FScopeLock Lock(&Mutex);
    Records.Empty();

    FString RawJson;
    if (!FFileHelper::LoadFileToString(RawJson, *FilePath))
        return; // File doesn't exist yet — first run.

    TSharedPtr<FJsonObject> Root;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(RawJson);
    if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
    {
        UE_LOG(LogPlayerSessionRegistry, Warning,
            TEXT("PlayerSessionRegistry: failed to parse %s — starting empty"), *FilePath);
        return;
    }

    const TArray<TSharedPtr<FJsonValue>>* Arr = nullptr;
    if (Root->TryGetArrayField(TEXT("sessions"), Arr) && Arr)
    {
        for (const TSharedPtr<FJsonValue>& Val : *Arr)
        {
            if (!Val.IsValid()) continue;
            const TSharedPtr<FJsonObject>* ObjPtr = nullptr;
            if (!Val->TryGetObject(ObjPtr) || !ObjPtr) continue;

            FPlayerSessionRecord Rec;
            (*ObjPtr)->TryGetStringField(TEXT("uid"),           Rec.Uid);
            (*ObjPtr)->TryGetStringField(TEXT("displayName"),   Rec.DisplayName);
            (*ObjPtr)->TryGetStringField(TEXT("lastSeen"),      Rec.LastSeen);
            (*ObjPtr)->TryGetStringField(TEXT("ipAddress"),     Rec.IpAddress);
            (*ObjPtr)->TryGetStringField(TEXT("clientVersion"), Rec.ClientVersion);

            if (!Rec.Uid.IsEmpty())
                Records.Add(Rec);
        }
    }
}

bool UPlayerSessionRegistry::SaveToFile() const
{
    // Caller must already hold Mutex.
    TArray<TSharedPtr<FJsonValue>> SessionArr;
    SessionArr.Reserve(Records.Num());
    for (const FPlayerSessionRecord& R : Records)
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("uid"),         R.Uid);
        Obj->SetStringField(TEXT("displayName"), R.DisplayName);
        Obj->SetStringField(TEXT("lastSeen"),    R.LastSeen);
        if (!R.IpAddress.IsEmpty())
            Obj->SetStringField(TEXT("ipAddress"), R.IpAddress);
        if (!R.ClientVersion.IsEmpty())
            Obj->SetStringField(TEXT("clientVersion"), R.ClientVersion);
        SessionArr.Add(MakeShared<FJsonValueObject>(Obj));
    }

    TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
    Root->SetArrayField(TEXT("sessions"), SessionArr);

    FString JsonStr;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonStr);
    if (!FJsonSerializer::Serialize(Root.ToSharedRef(), Writer))
    {
        UE_LOG(LogPlayerSessionRegistry, Error,
            TEXT("PlayerSessionRegistry: failed to serialize sessions"));
        return false;
    }

    const FString TmpPath = FilePath + TEXT(".tmp");
    if (!FFileHelper::SaveStringToFile(JsonStr, *TmpPath,
        FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
    {
        UE_LOG(LogPlayerSessionRegistry, Error,
            TEXT("PlayerSessionRegistry: failed to write temp file %s"), *TmpPath);
        return false;
    }
    if (!IFileManager::Get().Move(*FilePath, *TmpPath, /*bReplace=*/true))
    {
        UE_LOG(LogPlayerSessionRegistry, Error,
            TEXT("PlayerSessionRegistry: failed to replace %s with temp file"), *FilePath);
        IFileManager::Get().Delete(*TmpPath);
        return false;
    }
    return true;
}

FString UPlayerSessionRegistry::GetRegistryPath() const
{
    const UBanSystemConfig* Cfg = UBanSystemConfig::Get();
    FString BaseDir;
    if (Cfg && !Cfg->DatabasePath.IsEmpty())
        BaseDir = FPaths::GetPath(Cfg->DatabasePath);
    else
        BaseDir = FPaths::ProjectSavedDir() / TEXT("BanSystem");

    return BaseDir / TEXT("player_sessions.json");
}
