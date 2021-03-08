#include "Toolkit/AssetTypes/SubsurfaceProfileAssetSerializer.h"
#include "Toolkit/AssetTypes/AssetHelper.h"
#include "Engine/SubsurfaceProfile.h"

void USubsurfaceProfileAssetSerializer::SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const {
    const TArray<UObject*> RootPackageObjects = FAssetHelper::GetRootPackageObjects(AssetPackage);
    check(RootPackageObjects.Num() == 1);

    USubsurfaceProfile* SubsurfaceProfile;
    check(RootPackageObjects.FindItemByClass<USubsurfaceProfile>(&SubsurfaceProfile));
    
    const int32 SubsurfaceProfileObjectIndex = ObjectHierarchySerializer->SerializeObject(SubsurfaceProfile);
    OutObject->SetNumberField(TEXT("SubsurfaceProfile"), SubsurfaceProfileObjectIndex);
}

EAssetCategory USubsurfaceProfileAssetSerializer::GetAssetCategory() const {
    return EAssetCategory::EAC_SubsurfaceProfile;
}
