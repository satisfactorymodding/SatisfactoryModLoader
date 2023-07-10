#pragma once
#include "CoreMinimal.h"
#include "FGSaveSystem.h"
#include "ModLoading/ModLoadingLibrary.h"

struct FModMetadata
{
    FModMetadata(FString Reference, FString Name, FVersion Version);
    
    FString Reference;
    FString Name;
    FVersion Version;

    TSharedPtr<FJsonValue> ToJson();
    static FModMetadata FromModInfo(FModInfo ModInfo);
};

struct FModMismatch
{
    FModMismatch(FModMetadata Was, FModInfo Is, bool IsMissing);
    FModMetadata Was;
    FModInfo Is;
    bool IsMissing;
    
    FString ToString() const;
    FText ToText() const;
};

class SML_API FSaveMetadataPatch {
public:
    static void Register();

private:
    static TArray<FModMismatch> FindModMismatches(FSaveHeader Header);
    static FText BuildModMismatchesText(TArray<FModMismatch>&);
    static void LogModMismatches(TArray<FModMismatch>&);
    static ESaveModCheckResult CheckModdedSaveCompatibility(const FSaveHeader& SaveHeader, FText& OutMessage);
};
