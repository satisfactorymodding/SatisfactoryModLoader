#pragma once
#include "Toolkit/AssetTypes/AssetTypeSerializer.h"
#include "FontAssetSerializer.generated.h"

UCLASS()
class SML_API UFontAssetSerializer : public UAssetTypeSerializer {
    GENERATED_BODY()
public:
    virtual void SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const override;

    virtual EAssetCategory GetAssetCategory() const override;
};
