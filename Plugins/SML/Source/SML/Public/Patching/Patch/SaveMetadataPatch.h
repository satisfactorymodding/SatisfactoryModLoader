#pragma once
#include "CoreMinimal.h"
#include "FGPlayerController.h"
#include "FGSaveSystem.h"
#include "ModLoading/ModLoadingLibrary.h"
#include "UI/FGPopupWidget.h"
#include "SaveMetadataPatch.generated.h"

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
    
    FString ToString();
};

class SML_API FSaveMetadataPatch {
    friend class FSatisfactoryModLoader;
    friend class USaveMetadataCallback;

    static bool Patch(FSaveHeader Header, APlayerController* PlayerController);
    static void RegisterPatch();
    static void PopupWarning(TArray<FModMismatch> ModMismatches, USaveMetadataCallback* CallbackObject);
    static TArray<FModMismatch> FindModMismatches(FSaveHeader Header);
    static FString BuildModMismatchesString(TArray<FModMismatch>&);
    static void LogModMismatches(TArray<FModMismatch>&);

    static bool IsCallback;
};

UCLASS()
class USaveMetadataCallback : public UObject
{
    GENERATED_BODY()
    friend class FSaveMetadataPatch;
public:
    UFUNCTION()
    void Callback(bool Continue);

    static USaveMetadataCallback* New(UFGSaveSystem* System, FSaveHeader SaveGame, APlayerController* Player);
private:
    UPROPERTY()
    UFGSaveSystem* System;
    FSaveHeader SaveGame;
    UPROPERTY()
    APlayerController* Player;
};