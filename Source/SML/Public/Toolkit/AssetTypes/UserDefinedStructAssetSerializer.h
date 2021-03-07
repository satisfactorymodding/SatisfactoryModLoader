#pragma once
#include "Toolkit/AssetTypes/AssetTypeSerializer.h"
#include "UserDefinedStructAssetSerializer.generated.h"

UCLASS()
class SML_API UUserDefinedStructAssetSerializer : public UAssetTypeSerializer {
    GENERATED_BODY()
public:
    virtual void SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const override;

    /** Serializes UUserDefinedStruct instance */
    static void SerializeUserDefinedStruct(TSharedPtr<FJsonObject> OutObject, class UUserDefinedStruct* Struct, UObjectHierarchySerializer* ObjectHierarchySerializer);

    virtual EAssetCategory GetAssetCategory() const override;    
};
