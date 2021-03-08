#pragma once
#include "Toolkit/AssetTypes/AssetTypeSerializer.h"
#include "DataTableAssetSerializer.generated.h"

UCLASS()
class SML_API UDataTableAssetSerializer : public UAssetTypeSerializer {
    GENERATED_BODY()
public:
    virtual void SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const override;

    static void SerializeDataTable(class UDataTable* DataTable, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer);
    
    virtual EAssetCategory GetAssetCategory() const override;
};
