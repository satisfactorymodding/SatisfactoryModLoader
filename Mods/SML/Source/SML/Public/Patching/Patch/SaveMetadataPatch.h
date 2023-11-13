#pragma once
#include "CoreMinimal.h"
#include "FGSaveSystem.h"
#include "ModLoading/ModLoadingLibrary.h"

struct FSavedModInfo
{
    FSavedModInfo() {}
    FSavedModInfo(const FString& Reference, const FString& Name, const FVersion& Version);
    
    FString Reference;
    FString Name;
    FVersion Version;

    bool Read(const TSharedRef<FJsonObject>& Object, FString& OutError);
    void Write(const TSharedRef<FJsonObject>& Object) const;
    static FSavedModInfo FromModInfo(const FModInfo& ModInfo);
};

struct FModMismatch
{
    FModMismatch(const FSavedModInfo& Was, const FModInfo& Is, bool IsMissing);
    FSavedModInfo Was;
    FModInfo Is;
    bool IsMissing;
    
    FString ToString() const;
    FText ToText() const;
};

enum class EModMetadataVersion : uint8 {
    // First version
    InitialVersion = 0,

    // @2023-07-16 Added FullMapName
    AddFullMapName,

    // -----<new versions can be added above this line>-----
    VersionPlusOne,
    LatestVersion = VersionPlusOne - 1 // Last version to use
};

struct FModMetadata {
    EModMetadataVersion Version;
    TArray<FSavedModInfo> Mods;
    FString FullMapName;

    bool Read(const TSharedRef<FJsonObject>& MetadataObject);
    void Write(const TSharedRef<FJsonObject>& MetadataObject) const;
};

class SML_API FSaveMetadataPatch {
public:
    static void Register();

private:
    static ESaveModCheckResult CheckModdedSaveCompatibility(const FSaveHeader& SaveHeader, FText& OutMessage);

    static ESaveModCheckResult CheckModMismatches(UGameInstance* GameInstance, const FModMetadata& ModMetadata, FText& OutMessage);
    static ESaveModCheckResult CheckSaveMap(UGameInstance* GameInstance, const FModMetadata& ModMetadata, const FSaveHeader& SaveHeader, FText& OutMessage);
    
    static TArray<FModMismatch> FindModMismatches(UGameInstance* GameInstance, const TArray<FSavedModInfo>& ModMetadata);
    static FText BuildModMismatchesText(TArray<FModMismatch>&);
    static void LogModMismatches(TArray<FModMismatch>&);

    static bool GetModMetadataFromHeader(const FSaveHeader& SaveHeader, FModMetadata& OutMetadata);
};
