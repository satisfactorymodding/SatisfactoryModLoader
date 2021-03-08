#pragma once
#include "Toolkit/AssetTypes/AssetTypeSerializer.h"
#include "Toolkit/AssetTypes/BlueprintAssetSerializer.h"
#include "AnimationBlueprintAssetSerializer.generated.h"

UCLASS()
class SML_API UAnimationBlueprintAssetSerializer : public UBlueprintAssetSerializer {
    GENERATED_BODY()
public:
    /** Serializes UAnimBlueprintGeneratedClass instance */
    static void SerializeAnimBlueprintClass(TSharedPtr<FJsonObject> OutObject, class UAnimBlueprintGeneratedClass* Class, UObjectHierarchySerializer* ObjectHierarchySerializer);
    
    virtual EAssetCategory GetAssetCategory() const override;
protected:
    virtual void SerializeClassInternal(TSharedPtr<FJsonObject> OutObject, class UBlueprintGeneratedClass* Class, UObjectHierarchySerializer* ObjectHierarchySerializer) const override;
};
