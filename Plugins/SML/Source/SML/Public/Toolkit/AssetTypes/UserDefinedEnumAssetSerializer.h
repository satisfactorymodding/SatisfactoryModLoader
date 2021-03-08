#pragma once
#include "Toolkit/AssetTypes/AssetTypeSerializer.h"
#include "UserDefinedEnumAssetSerializer.generated.h"

UCLASS()
class SML_API UUserDefinedEnumAssetSerializer : public UAssetTypeSerializer {
    GENERATED_BODY()
public:
    virtual void SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const override;

    /** Serializes UUserDefinedEnum instance */
    static void SerializeUserDefinedEnum(TSharedPtr<FJsonObject> OutObject, class UUserDefinedEnum* Enum);

    virtual EAssetCategory GetAssetCategory() const override;    
};
