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

UTexture2D* UBlueprintModLoadingLibrary::LoadModIconTexture(const FString& ModReference, UTexture2D* FallbackIcon) {
    UBlueprintModLoadingLibrary* ModLoadingLibrary = GetMutableDefault<UBlueprintModLoadingLibrary>();
    FModHandler* ModHandler = FSatisfactoryModLoader::GetModHandler();

    //Icon is already loaded and cached
    if (ModLoadingLibrary->LoadedModIcons.Contains(ModReference)) {
        return ModLoadingLibrary->LoadedModIcons.FindChecked(ModReference);
    }
    
    //ModHandler is not available, function is called from editor
    if (ModHandler == NULL) {
        return FallbackIcon;
    }

    //Mod is not installed, fallback to icon provided
    const FModContainer* ModContainer = ModHandler->GetLoadedMod(ModReference);
    if (ModContainer == NULL) {
        return FallbackIcon;
    }

    //Icon path is not set in the data.json
    const FString& IconPath = ModContainer->ModInfo.ModResources.ModIconPath;
    if (IconPath.IsEmpty()) {
        return FallbackIcon;
    }

    //Mod has icon path set, but file extraction failed and icon is not available
    const FString* IconFileLocation = ModContainer->CustomFilePaths.Find(IconPath);
    if (IconFileLocation == NULL) {
        return FallbackIcon;
    }

    FString OutErrorMessage;
    UTexture2D* LoadedModIcon = FImageLoadingUtil::LoadImageFromFile(*IconFileLocation, OutErrorMessage);

    //Failed to load mod icon, fallback to default
    if (LoadedModIcon == NULL) {
        UE_LOG(LogModLoading, Error, TEXT("Failed to load icon for mod %s at file %s: %s"), *ModReference, **IconFileLocation, *OutErrorMessage);
        LoadedModIcon = FallbackIcon;
    }

    //Cache obtained texture object for faster access
    ModLoadingLibrary->LoadedModIcons.Add(ModReference, LoadedModIcon);
    return LoadedModIcon;
}
