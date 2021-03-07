#pragma once
#include "Toolkit/AssetTypes/AssetTypeSerializer.h"
#include "SkeletonAssetSerializer.generated.h"

UCLASS()
class SML_API USkeletonAssetSerializer : public UAssetTypeSerializer {
    GENERATED_BODY()
public:
    virtual void SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const override;

    static void SerializeSkeleton(class USkeleton* Skeleton, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context);

    static void SerializeSmartNameContainer(const struct FSmartNameContainer& Container, TSharedPtr<FJsonObject> OutObject);
    
    virtual EAssetCategory GetAssetCategory() const override;
};
