#pragma once
#include "Toolkit/AssetTypes/AssetTypeSerializer.h"
#include "StaticMeshAssetSerializer.generated.h"

UCLASS()
class SML_API UStaticMeshAssetSerializer : public UAssetTypeSerializer {
    GENERATED_BODY()
public:
    virtual void SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const override;

    static void SerializeStaticMesh(class UStaticMesh* StaticMesh, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context);
    
    static TSharedPtr<FJsonObject> SerializeBodySetup(class UBodySetup* BodySetup, UObjectHierarchySerializer* ObjectHierarchySerializer);
    
    virtual EAssetCategory GetAssetCategory() const override;
};
