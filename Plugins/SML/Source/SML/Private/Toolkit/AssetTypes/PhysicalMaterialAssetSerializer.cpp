#include "Toolkit/AssetTypes/PhysicalMaterialAssetSerializer.h"
#include "Toolkit/AssetDumping/SerializationContext.h"
#include "Toolkit/AssetDumping/AssetTypeSerializerMacros.h"
#include "Toolkit/ObjectHierarchySerializer.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

void UPhysicalMaterialAssetSerializer::SerializeAsset(TSharedRef<FSerializationContext> Context) const {
    BEGIN_ASSET_SERIALIZATION(UPhysicalMaterial)
        SERIALIZE_ASSET_OBJECT
    END_ASSET_SERIALIZATION
}

FName UPhysicalMaterialAssetSerializer::GetAssetClass() const {
    return UPhysicalMaterial::StaticClass()->GetFName();
}
