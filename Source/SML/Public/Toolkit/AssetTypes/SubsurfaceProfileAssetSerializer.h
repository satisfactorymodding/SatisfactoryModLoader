#pragma once
#include "Toolkit/AssetTypes/AssetTypeSerializer.h"
#include "SubsurfaceProfileAssetSerializer.generated.h"

UCLASS()
class SML_API USubsurfaceProfileAssetSerializer : public UAssetTypeSerializer {
    GENERATED_BODY()
public:
    virtual void SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const override;

    virtual EAssetCategory GetAssetCategory() const override;
};
