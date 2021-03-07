#include "Toolkit/AssetTypes/PhysicalMaterialAssetSerializer.h"
#include "Toolkit/AssetTypes/AssetHelper.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

void UPhysicalMaterialAssetSerializer::SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const {
    const TArray<UObject*> RootPackageObjects = FAssetHelper::GetRootPackageObjects(AssetPackage);
    check(RootPackageObjects.Num() == 1);

    UPhysicalMaterial* PhysicalMaterial;
    check(RootPackageObjects.FindItemByClass<UPhysicalMaterial>(&PhysicalMaterial));
    
    const int32 PhysicalMaterialObjectIndex = ObjectHierarchySerializer->SerializeObject(PhysicalMaterial);
    OutObject->SetNumberField(TEXT("PhysicalMaterial"), PhysicalMaterialObjectIndex);
}

EAssetCategory UPhysicalMaterialAssetSerializer::GetAssetCategory() const {
    return EAssetCategory::EAC_PhysicalMaterial;
}
