// Copyright Yamahasxviper. All Rights Reserved.

#include "PlayerNoteRegistry.h"

#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "HAL/PlatformFileManager.h"
#include "HAL/FileManager.h"

DEFINE_LOG_CATEGORY(LogPlayerNoteRegistry);

// ─────────────────────────────────────────────────────────────────────────────
//  USubsystem lifecycle
// ─────────────────────────────────────────────────────────────────────────────

void UPlayerNoteRegistry::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    FilePath = GetRegistryPath();

    const FString Dir = FPaths::GetPath(FilePath);
    IPlatformFile& PF = FPlatformFileManager::Get().GetPlatformFile();
    if (!PF.DirectoryExists(*Dir))
        PF.CreateDirectoryTree(*Dir);

    LoadFromFile();

    UE_LOG(LogPlayerNoteRegistry, Log,
        TEXT("PlayerNoteRegistry: loaded %s (%d note(s))"),
        *FilePath, Notes.Num());
}

void UPlayerNoteRegistry::Deinitialize()
{
    Super::Deinitialize();
}

// ─────────────────────────────────────────────────────────────────────────────
//  Public API
// ─────────────────────────────────────────────────────────────────────────────

void UPlayerNoteRegistry::AddNote(const FString& Uid, const FString& PlayerName,
                                  const FString& Note, const FString& AddedBy)
{
    if (Uid.IsEmpty()) return;

    FScopeLock Lock(&Mutex);

    FPlayerNoteEntry Entry;
    // NextId == 0 is the exhausted sentinel: it is set in LoadFromFile when the
    // highest stored Id is INT64_MAX, meaning there is no valid next Id.  Using 0
    // instead of INT64_MAX as the sentinel allows INT64_MAX itself to be legally
    // allocated as the last ever Id before the counter is exhausted.
    if (NextId == 0)
    {
        UE_LOG(LogPlayerNoteRegistry, Error,
            TEXT("PlayerNoteRegistry: all 64-bit IDs have been used — cannot add more notes"));
        return;
    }
    Entry.Id = NextId;
    NextId   = (NextId < INT64_MAX) ? NextId + 1 : 0; // 0 = exhausted
    Entry.Uid        = Uid;
    Entry.PlayerName = PlayerName;
    Entry.Note       = Note;
    Entry.AddedBy    = AddedBy;
    Entry.NoteDate   = FDateTime::UtcNow();

    Notes.Add(Entry);
    if (!SaveToFile())
        UE_LOG(LogPlayerNoteRegistry, Error,
            TEXT("PlayerNoteRegistry: failed to save notes.json after adding note for %s"), *Uid);
}

TArray<FPlayerNoteEntry> UPlayerNoteRegistry::GetNotesForUid(const FString& Uid) const
{
    FScopeLock Lock(&Mutex);
    TArray<FPlayerNoteEntry> Result;
    for (const FPlayerNoteEntry& N : Notes)
    {
        if (N.Uid.Equals(Uid, ESearchCase::IgnoreCase))
            Result.Add(N);
    }
    return Result;
}

TArray<FPlayerNoteEntry> UPlayerNoteRegistry::GetAllNotes() const
{
    FScopeLock Lock(&Mutex);
    return Notes;
}

bool UPlayerNoteRegistry::DeleteNote(int64 Id)
{
    FScopeLock Lock(&Mutex);
    const int32 Before = Notes.Num();
    Notes.RemoveAll([Id](const FPlayerNoteEntry& N)
    {
        return N.Id == Id;
    });
    const bool bRemoved = Notes.Num() < Before;
    if (bRemoved && !SaveToFile())
        UE_LOG(LogPlayerNoteRegistry, Error,
            TEXT("PlayerNoteRegistry: failed to save notes.json after deleting note id=%lld"), Id);
    return bRemoved;
}

// ─────────────────────────────────────────────────────────────────────────────
//  File I/O
// ─────────────────────────────────────────────────────────────────────────────

FString UPlayerNoteRegistry::GetRegistryPath() const
{
    return FPaths::ProjectSavedDir() / TEXT("BanChatCommands") / TEXT("notes.json");
}

void UPlayerNoteRegistry::LoadFromFile()
{
    FScopeLock Lock(&Mutex);
    Notes.Empty();

    FString RawJson;
    if (!FFileHelper::LoadFileToString(RawJson, *FilePath))
        return;

    TSharedPtr<FJsonObject> Root;
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(RawJson);
    if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid())
    {
        UE_LOG(LogPlayerNoteRegistry, Warning,
            TEXT("PlayerNoteRegistry: failed to parse %s — starting empty"), *FilePath);
        return;
    }

    const TArray<TSharedPtr<FJsonValue>>* Arr = nullptr;
    if (Root->TryGetArrayField(TEXT("notes"), Arr) && Arr)
    {
        for (const TSharedPtr<FJsonValue>& Val : *Arr)
        {
            if (!Val.IsValid()) continue;
            const TSharedPtr<FJsonObject>* ObjPtr = nullptr;
            if (!Val->TryGetObject(ObjPtr) || !ObjPtr) continue;

            FPlayerNoteEntry Entry;
            // Prefer string format (written since precision-loss fix); fall back
            // to legacy double for files written by older builds.
            FString IdStr;
            {
                double  IdDbl = 0.0;
                if ((*ObjPtr)->TryGetStringField(TEXT("id"), IdStr))
                    Entry.Id = FCString::Atoi64(*IdStr);
                else if ((*ObjPtr)->TryGetNumberField(TEXT("id"), IdDbl) && IdDbl >= 1.0
                    && IdDbl < static_cast<double>(INT64_MAX))
                    Entry.Id = static_cast<int64>(IdDbl);
            }
            if (Entry.Id <= 0)
            {
                UE_LOG(LogPlayerNoteRegistry, Warning,
                    TEXT("PlayerNoteRegistry: skipping note with invalid id='%s'"), *IdStr);
                continue;
            }
            (*ObjPtr)->TryGetStringField(TEXT("uid"),        Entry.Uid);
            (*ObjPtr)->TryGetStringField(TEXT("playerName"), Entry.PlayerName);
            (*ObjPtr)->TryGetStringField(TEXT("note"),       Entry.Note);
            (*ObjPtr)->TryGetStringField(TEXT("addedBy"),    Entry.AddedBy);

            FString DateStr;
            if ((*ObjPtr)->TryGetStringField(TEXT("noteDate"), DateStr))
            {
                if (!FDateTime::ParseIso8601(*DateStr, Entry.NoteDate))
                {
                    UE_LOG(LogPlayerNoteRegistry, Warning,
                        TEXT("PlayerNoteRegistry: uid='%s' has malformed noteDate '%s' — skipping entry"),
                        *Entry.Uid, *DateStr);
                    continue;
                }
            }

            if (!Entry.Uid.IsEmpty())
                Notes.Add(Entry);
        }
    }

    // Restore the NextId counter.  Prefer the persisted "nextId" field (written
    // since BUG-09 fix) over the scan-based reconstruction so that deleting the
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
        for (const FPlayerNoteEntry& N : Notes)
            if (N.Id >= NextId) NextId = (N.Id < INT64_MAX) ? N.Id + 1 : 0;
    }
}

bool UPlayerNoteRegistry::SaveToFile() const
{
    // Caller must already hold Mutex.
    TArray<TSharedPtr<FJsonValue>> NoteArr;
    NoteArr.Reserve(Notes.Num());
    for (const FPlayerNoteEntry& N : Notes)
    {
        TSharedPtr<FJsonObject> Obj = MakeShared<FJsonObject>();
        Obj->SetStringField(TEXT("id"),         FString::Printf(TEXT("%lld"), N.Id));
        Obj->SetStringField(TEXT("uid"),        N.Uid);
        Obj->SetStringField(TEXT("playerName"), N.PlayerName);
        Obj->SetStringField(TEXT("note"),       N.Note);
        Obj->SetStringField(TEXT("addedBy"),    N.AddedBy);
        Obj->SetStringField(TEXT("noteDate"),   N.NoteDate.ToIso8601());
        NoteArr.Add(MakeShared<FJsonValueObject>(Obj));
    }

    TSharedPtr<FJsonObject> Root = MakeShared<FJsonObject>();
    Root->SetStringField(TEXT("nextId"), FString::Printf(TEXT("%lld"), NextId));
    Root->SetArrayField(TEXT("notes"), NoteArr);

    FString JsonStr;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonStr);
    if (!FJsonSerializer::Serialize(Root.ToSharedRef(), Writer))
    {
        UE_LOG(LogPlayerNoteRegistry, Error,
            TEXT("PlayerNoteRegistry: failed to serialize notes"));
        return false;
    }

    const FString TmpPath = FilePath + TEXT(".tmp");
    if (!FFileHelper::SaveStringToFile(JsonStr, *TmpPath,
        FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM))
    {
        UE_LOG(LogPlayerNoteRegistry, Error,
            TEXT("PlayerNoteRegistry: failed to write temp file %s"), *TmpPath);
        return false;
    }
    if (!IFileManager::Get().Move(*FilePath, *TmpPath, /*bReplace=*/true))
    {
        UE_LOG(LogPlayerNoteRegistry, Error,
            TEXT("PlayerNoteRegistry: failed to replace %s with temp file"), *FilePath);
        IFileManager::Get().Delete(*TmpPath);
        return false;
    }

    return true;
}
