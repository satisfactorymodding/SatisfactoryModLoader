#pragma once
#include "Toolkit/AssetTypes/AssetTypeSerializer.h"
#include "SkeletalMeshAssetSerializer.generated.h"

UCLASS()
class SML_API USkeletalMeshAssetSerializer : public UAssetTypeSerializer {
    GENERATED_BODY()
public:
    virtual void SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const override;

    static void SerializeSkeletalMesh(class USkeletalMesh* SkeletalMesh, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context);

    static void SerializeReferenceSkeleton(const struct FReferenceSkeleton& ReferenceSkeleton, TSharedPtr<FJsonObject> OutObject);
    
    virtual EAssetCategory GetAssetCategory() const override;
};
