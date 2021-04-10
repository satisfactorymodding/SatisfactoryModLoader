#pragma once
#include "Toolkit/AssetDumping/AssetTypeSerializer.h"
#include "SubsurfaceProfileAssetSerializer.generated.h"

UCLASS()
class SML_API USubsurfaceProfileAssetSerializer : public UAssetTypeSerializer {
    GENERATED_BODY()
public:
    virtual void SerializeAsset(TSharedRef<FSerializationContext> Context) const override;

    virtual FName GetAssetClass() const override;
};
