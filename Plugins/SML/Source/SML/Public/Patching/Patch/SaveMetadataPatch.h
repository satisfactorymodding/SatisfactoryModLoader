#pragma once
#include "CoreMinimal.h"
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

struct FMissingMod
{
    FMissingMod(FModMetadata Was, FModInfo* Is);
    FModMetadata Was;
    FModInfo* Is;
    
    FString ToString();
};

class SML_API FSaveMetadataPatch {
    friend class FSatisfactoryModLoader;
    friend class USaveMetadataCallback;

    static void RegisterPatch();
    static bool PopupWarningIfMissingMods(TArray<FMissingMod> MissingMods, USaveMetadataCallback* CallbackObject);
    static TArray<FMissingMod> FindMissingMods(FSaveHeader Header);
    static FString BuildMissingModString(TArray<FMissingMod>&);
    static void LogMissingMods(TArray<FMissingMod>&);

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