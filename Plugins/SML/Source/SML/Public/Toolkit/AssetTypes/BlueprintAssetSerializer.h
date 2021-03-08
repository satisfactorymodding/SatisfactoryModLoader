#pragma once
#include "Toolkit/AssetTypes/AssetTypeSerializer.h"
#include "BlueprintAssetSerializer.generated.h"

UCLASS()
class SML_API UBlueprintAssetSerializer : public UAssetTypeSerializer {
    GENERATED_BODY()
public:
    virtual void SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const override;

    /** Serializes UBlueprintGeneratedClass instance */
    static void SerializeBlueprintClass(TSharedPtr<FJsonObject> OutObject, class UBlueprintGeneratedClass* Class, UObjectHierarchySerializer* ObjectHierarchySerializer);
    
    virtual EAssetCategory GetAssetCategory() const override;
protected:
    virtual void CheckRootObjectSet(UPackage* AssetPackage, const TArray<UObject*>& RootPackageObjects) const;
    
    virtual void SerializeClassInternal(TSharedPtr<FJsonObject> OutObject, class UBlueprintGeneratedClass* Class, UObjectHierarchySerializer* ObjectHierarchySerializer) const;
};
