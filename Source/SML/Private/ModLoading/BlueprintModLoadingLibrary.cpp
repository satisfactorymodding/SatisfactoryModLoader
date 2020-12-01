#include "BlueprintModLoadingLibrary.h"
#include "ModHandler.h"
#include "SatisfactoryModLoader.h"
#include "Util/ImageLoadingUtil.h"

bool UBlueprintModLoadingLibrary::IsModLoaded(const FString& ModReference) {
    FModHandler* ModHandler = FSatisfactoryModLoader::GetModHandler();
    return ModHandler && ModHandler->IsModLoaded(ModReference);
}

TArray<FString> UBlueprintModLoadingLibrary::GetLoadedMods() {
    FModHandler* ModHandler = FSatisfactoryModLoader::GetModHandler();
    TArray<FString> OutLoadedMods;
    if (ModHandler != NULL) {
        for (const FModContainer* ModContainer : ModHandler->GetLoadedMods()) {
            OutLoadedMods.Add(ModContainer->ModInfo.ModReference);
        }
    }
    return OutLoadedMods;
}

FModInfo UBlueprintModLoadingLibrary::GetLoadedModInfo(const FString& ModReference) {
    FModHandler* ModHandler = FSatisfactoryModLoader::GetModHandler();
    if (ModHandler != NULL) {
        const FModContainer* ModContainer = ModHandler->GetLoadedMod(ModReference);
        if (ModContainer != NULL) {
            return ModContainer->ModInfo;
        }
    }
    return FModInfo{};
}

FVersion UBlueprintModLoadingLibrary::GetSMLVersion() {
    return FSatisfactoryModLoader::GetModLoaderVersion();
}

bool UBlueprintModLoadingLibrary::IsDevelopmentModeEnabled() {
    return FSatisfactoryModLoader::GetSMLConfiguration().bDevelopmentMode;
}

TMap<FName, FString> UBlueprintModLoadingLibrary::GetExtraModLoaderAttributes() {
    return FSatisfactoryModLoader::GetExtraAttributes();
}

UModIconStorage* UBlueprintModLoadingLibrary::GetModIconStorage() {
    static UModIconStorage* IconStorage = NULL;
    if (IconStorage == NULL) {
        IconStorage = NewObject<UModIconStorage>(GetTransientPackage(), NAME_None, RF_MarkAsRootSet);
    }
    check(IconStorage);
    return IconStorage;
}

UModIconStorage::UModIconStorage() {
    this->BlankTexture = UTexture2D::CreateTransient(256, 256);
}

UTexture2D* UModIconStorage::FindOrLoadModIcon(const FString& ModReference, bool& bOutIsBlankTexture) {
    //Icon is already loaded and cached
    if (LoadedModIcons.Contains(ModReference)) {
        UTexture2D* LoadedIcon = LoadedModIcons.FindChecked(ModReference);
        bOutIsBlankTexture = LoadedIcon == BlankTexture;
    }

    UTexture2D* ActuallyLoadedTexture = LoadModIcon(ModReference);
    if (ActuallyLoadedTexture == NULL) {
        ActuallyLoadedTexture = BlankTexture;
    }

    LoadedModIcons.Add(ModReference, ActuallyLoadedTexture);
    bOutIsBlankTexture = ActuallyLoadedTexture == BlankTexture;
    return ActuallyLoadedTexture;
}

UTexture2D* UModIconStorage::LoadModIcon(const FString& ModReference) {
    FModHandler* ModHandler = FSatisfactoryModLoader::GetModHandler();
    
    //ModHandler is not available, function is called from editor
    if (ModHandler == NULL) {
        return NULL;
    }

    //Mod is not installed, fallback to icon provided
    const FModContainer* ModContainer = ModHandler->GetLoadedMod(ModReference);
    if (ModContainer == NULL) {
        return NULL;
    }

    //Icon path is not set in the data.json
    const FString& IconPath = ModContainer->ModInfo.ModResources.ModIconPath;
    if (IconPath.IsEmpty()) {
        return NULL;
    }

    //Mod has icon path set, but file extraction failed and icon is not available
    const FString* IconFileLocation = ModContainer->CustomFilePaths.Find(IconPath);
    if (IconFileLocation == NULL) {
        return NULL;
    }

    FString OutErrorMessage;
    UTexture2D* LoadedModIcon = FImageLoadingUtil::LoadImageFromFile(*IconFileLocation, OutErrorMessage);

    //Failed to load mod icon, fallback to default
    if (LoadedModIcon == NULL) {
        UE_LOG(LogModLoading, Error, TEXT("Failed to load icon for mod %s at file %s: %s"), *ModReference, **IconFileLocation, *OutErrorMessage);
        return NULL;
    }
    return LoadedModIcon;
}

UTexture2D* UBlueprintModLoadingLibrary::LoadModIconTexture(const FString& ModReference, UTexture2D* FallbackIcon) {
    UModIconStorage* ModIconStorage = GetModIconStorage();
    bool bIsBlankTexture = false;
    UTexture2D* ModIconTexture = ModIconStorage->FindOrLoadModIcon(ModReference, bIsBlankTexture);
    return bIsBlankTexture ? FallbackIcon : ModIconTexture;
}