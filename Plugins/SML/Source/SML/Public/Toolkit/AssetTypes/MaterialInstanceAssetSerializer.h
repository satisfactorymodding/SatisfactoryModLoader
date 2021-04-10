#pragma once
#include "Toolkit/AssetDumping/AssetTypeSerializer.h"
#include "MaterialInstanceAssetSerializer.generated.h"

UCLASS()
class SML_API UMaterialInstanceAssetSerializer : public UAssetTypeSerializer {
    GENERATED_BODY()
public:
    virtual void SerializeAsset(TSharedRef<FSerializationContext> Context) const override;

    virtual FName GetAssetClass() const override;
};
