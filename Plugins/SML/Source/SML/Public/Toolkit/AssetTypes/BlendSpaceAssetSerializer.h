#pragma once
#include "Toolkit/AssetDumping/AssetTypeSerializer.h"
#include "BlendSpaceAssetSerializer.generated.h"

UCLASS()
class SML_API UBlendSpaceSerializer : public UAssetTypeSerializer {
    GENERATED_BODY()
public:
    virtual void SerializeAsset(TSharedRef<FSerializationContext> Context) const override;

    virtual void GetAdditionallyHandledAssetClasses(TArray<FName>& OutExtraAssetClasses) override;
    virtual FName GetAssetClass() const override;
};
