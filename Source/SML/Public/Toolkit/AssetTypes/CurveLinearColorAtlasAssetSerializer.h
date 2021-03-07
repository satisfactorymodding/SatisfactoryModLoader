#pragma once
#include "Toolkit/AssetTypes/AssetTypeSerializer.h"
#include "CurveLinearColorAtlasAssetSerializer.generated.h"

UCLASS()
class SML_API UCurveLinearColorAtlasAssetSerializer : public UAssetTypeSerializer {
    GENERATED_BODY()
public:
    virtual void SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const override;

    static void SerializeColorAtlas(class UCurveLinearColorAtlas* LinearColorAtlas, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context);

    virtual EAssetCategory GetAssetCategory() const override;    
};
