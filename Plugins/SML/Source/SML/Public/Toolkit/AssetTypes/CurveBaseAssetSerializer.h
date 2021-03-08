#pragma once
#include "Toolkit/AssetTypes/AssetTypeSerializer.h"
#include "CurveBaseAssetSerializer.generated.h"

UCLASS()
class SML_API UCurveBaseAssetSerializer : public UAssetTypeSerializer {
    GENERATED_BODY()
public:
    virtual void SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const override;

    static void SerializeCurveBase(class UCurveBase* Curve, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer);
    
    virtual EAssetCategory GetAssetCategory() const override;
};
