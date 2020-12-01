#pragma once
#include "CoreMinimal.h"
#include "ModInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BlueprintModLoadingLibrary.generated.h"

class UTexture2D;

UCLASS()
class SML_API UBlueprintModLoadingLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    /** Returns true when mod with provided ModId is loaded */
    UFUNCTION(BlueprintPure, Category = "SML|Mod Loading", meta = (BlueprintThreadSafe))
    static bool IsModLoaded(const FString& ModReference);

    /** Returns list of loaded mods (their ModIds actually) */
    UFUNCTION(BlueprintPure, Category = "SML|Mod Loading", meta = (BlueprintThreadSafe))
    static TArray<FString> GetLoadedMods();

    /** Retrieves information about loaded mod by it's ModId. Returns empty struct if mod is not loaded */
    UFUNCTION(BlueprintPure, Category = "SML|Mod Loading", meta = (BlueprintThreadSafe))
    static FModInfo GetLoadedModInfo(const FString& ModReference);

    /** Tries to load mod icon and returns pointer to the loaded texture, or FallbackIcon if icon cannot be loaded */
    UFUNCTION(BlueprintCallable, Category = "SML|Mod Loading")
    static UTexture2D* LoadModIconTexture(const FString& ModReference, UTexture2D* FallbackIcon);

    /** Returns the currently used SML version */
    UFUNCTION(BlueprintPure, Category = "SML|Mod Loading", meta = (BlueprintThreadSafe))
    static FVersion GetSMLVersion();

    /** Returns true if development mode is currently enabled */
    UFUNCTION(BlueprintPure, Category = "SML|Mod Loading", meta = (BlueprintThreadSafe))
    static bool IsDevelopmentModeEnabled();

    /** Returns extra attributes exposed by mod loader implementation */
    UFUNCTION(BlueprintPure, Category = "SML|Mod Loading", meta = (BlueprintThreadSafe))
    static TMap<FName, FString> GetExtraModLoaderAttributes();
private:
    /** Cache of loaded mod icon textures */
    static class UModIconStorage* GetModIconStorage();
};

/** Holds mod icons and manages their loading */
UCLASS()
class SML_API UModIconStorage : public UObject {
    GENERATED_BODY()
private:
    /** Cache of loaded mod icon textures */
    UPROPERTY()
    TMap<FString, class UTexture2D*> LoadedModIcons;

    /** Blank image returned when icon cannot be loaded */
    UPROPERTY()
    UTexture2D* BlankTexture; 
public:
    UModIconStorage();

    /** Loads a mod icon texture or retrieves it from cache if it has been loaded already */
    UTexture2D* FindOrLoadModIcon(const FString& ModReference, bool& bOutIsBlankTexture);
private:
    /** Actually loads mod icon */
    static UTexture2D* LoadModIcon(const FString& ModReference);
};

