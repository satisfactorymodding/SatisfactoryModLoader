#include "Toolkit/AssetTypes/TextureCubeAssetSerializer.h"
#include "Engine/TextureCube.h"
#include "Toolkit/AssetTypes/AssetHelper.h"
#include "Toolkit/AssetTypes/TextureAssetSerializer.h"

void UTextureCubeAssetSerializer::SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const {
    const TArray<UObject*> RootPackageObjects = FAssetHelper::GetRootPackageObjects(AssetPackage);
    check(RootPackageObjects.Num() == 1);

    UTextureCube* TextureCube;
    check(RootPackageObjects.FindItemByClass<UTextureCube>(&TextureCube));
    
    SerializeTextureCube(TextureCube, OutObject, ObjectHierarchySerializer, Context);
}

void UTextureCubeAssetSerializer::SerializeTextureCube(UTextureCube* TextureCube, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) {
    //Serialize basic UTexture properties
    UTextureAssetSerializer::SerializeTexture(TextureCube, OutObject, ObjectHierarchySerializer);

    //Serialize actual payload of texture
    UTextureAssetSerializer::SerializeTextureData(TextureCube, TextureCube->PlatformData, OutObject, Context, true, TEXT(""));
}

EAssetCategory UTextureCubeAssetSerializer::GetAssetCategory() const {
    return EAssetCategory::EAC_TextureCube;
}
