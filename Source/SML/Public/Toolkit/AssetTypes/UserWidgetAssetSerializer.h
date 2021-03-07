#pragma once
#include "Toolkit/AssetTypes/AssetTypeSerializer.h"
#include "Toolkit/AssetTypes/BlueprintAssetSerializer.h"
#include "UserWidgetAssetSerializer.generated.h"

UCLASS()
class SML_API UUserWidgetAssetSerializer : public UBlueprintAssetSerializer {
    GENERATED_BODY()
public:
    /** Serializes UWidgetBlueprintGeneratedClass instance */
    static void SerializeWidgetBlueprintClass(TSharedPtr<FJsonObject> OutObject, class UWidgetBlueprintGeneratedClass* Class, UObjectHierarchySerializer* ObjectHierarchySerializer);
    
    virtual EAssetCategory GetAssetCategory() const override;
protected:
    virtual void CheckRootObjectSet(UPackage* AssetPackage, const TArray<UObject*>& RootPackageObjects) const override;
    
    virtual void SerializeClassInternal(TSharedPtr<FJsonObject> OutObject, class UBlueprintGeneratedClass* Class, UObjectHierarchySerializer* ObjectHierarchySerializer) const override;
};
