#pragma once
#include "Toolkit/AssetTypes/AssetTypeSerializer.h"
#include "MaterialInstanceAssetSerializer.generated.h"

UCLASS()
class SML_API UMaterialInstanceAssetSerializer : public UAssetTypeSerializer {
    GENERATED_BODY()
public:
    virtual void SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const override;

    static void SerializeMaterialInstance(class UMaterialInstance* MaterialInstance, TSharedPtr<FJsonObject> OutJson, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& SerializationContext);
    
    virtual EAssetCategory GetAssetCategory() const override;
};
