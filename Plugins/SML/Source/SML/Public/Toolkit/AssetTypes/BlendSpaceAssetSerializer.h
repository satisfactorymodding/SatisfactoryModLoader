#pragma once
#include "Toolkit/AssetTypes/AssetTypeSerializer.h"
#include "BlendSpaceAssetSerializer.generated.h"

UCLASS()
class SML_API UBlendSpaceSerializer : public UAssetTypeSerializer {
    GENERATED_BODY()
public:
    virtual void SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const override;

    static void SerializeBlendSpace(class UBlendSpaceBase* BlendSpace, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer);
    
    virtual EAssetCategory GetAssetCategory() const override;
};
