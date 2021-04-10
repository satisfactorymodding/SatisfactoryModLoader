#pragma once
#include "Toolkit/AssetDumping/AssetTypeSerializer.h"
#include "DataTableAssetSerializer.generated.h"

UCLASS()
class SML_API UDataTableAssetSerializer : public UAssetTypeSerializer {
    GENERATED_BODY()
public:
    virtual void SerializeAsset(TSharedRef<FSerializationContext> Context) const override;

    virtual FName GetAssetClass() const override;
};
