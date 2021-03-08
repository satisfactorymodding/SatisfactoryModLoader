#pragma once
#include "Toolkit/AssetTypes/AssetTypeSerializer.h"
#include "StringTableAssetSerializer.generated.h"

UCLASS()
class SML_API UStringTableAssetSerializer : public UAssetTypeSerializer {
    GENERATED_BODY()
public:
    virtual void SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const override;

    static void SerializeStringTable(class UStringTable* StringTable, TSharedPtr<FJsonObject> OutObject);
    
    virtual EAssetCategory GetAssetCategory() const override;
};
