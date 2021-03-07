#pragma once
#include "Toolkit/AssetTypes/AssetTypeSerializer.h"
#include "AnimationSequenceAssetSerializer.generated.h"

UCLASS()
class SML_API UAnimationSequenceAssetSerializer : public UAssetTypeSerializer {
    GENERATED_BODY()
public:
    virtual void SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const override;

    static void SerializeAnimationSequence(class UAnimSequence* AnimSequence, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* Serializer, FAssetSerializationContext& Context);
    
    virtual EAssetCategory GetAssetCategory() const override;
};
