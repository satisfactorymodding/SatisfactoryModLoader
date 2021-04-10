#pragma once
#include "Toolkit/AssetDumping/AssetTypeSerializer.h"
#include "CurveBaseAssetSerializer.generated.h"

UCLASS()
class SML_API UCurveBaseAssetSerializer : public UAssetTypeSerializer {
    GENERATED_BODY()
public:
    virtual void SerializeAsset(TSharedRef<FSerializationContext> Context) const override;

    virtual void GetAdditionallyHandledAssetClasses(TArray<FName>& OutExtraAssetClasses) override;
    virtual FName GetAssetClass() const override;
};
