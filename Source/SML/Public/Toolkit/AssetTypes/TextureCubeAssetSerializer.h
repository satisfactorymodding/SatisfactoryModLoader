#pragma once
#include "Toolkit/AssetTypes/AssetTypeSerializer.h"
#include "TextureCubeAssetSerializer.generated.h"

UCLASS()
class SML_API UTextureCubeAssetSerializer : public UAssetTypeSerializer {
    GENERATED_BODY()
public:
    virtual void SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const override;

    /** Serializes TextureCube, including exporting it to image file saved alongside json */
    static void SerializeTextureCube(class UTextureCube* TextureCube, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context);

    virtual EAssetCategory GetAssetCategory() const override;    
};
