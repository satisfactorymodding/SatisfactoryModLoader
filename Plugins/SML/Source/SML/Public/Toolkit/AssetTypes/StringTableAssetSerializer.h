#pragma once
#include "Toolkit/AssetDumping/AssetTypeSerializer.h"
#include "StringTableAssetSerializer.generated.h"

UCLASS()
class SML_API UStringTableAssetSerializer : public UAssetTypeSerializer {
    GENERATED_BODY()
public:
    virtual void SerializeAsset(TSharedRef<FSerializationContext> Context) const override;

    virtual FName GetAssetClass() const override;
};
