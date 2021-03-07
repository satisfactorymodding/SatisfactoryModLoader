#include "Toolkit/AssetTypes/AnimationMontageAssetSerializer.h"
#include "Toolkit/AssetTypes/AssetHelper.h"
#include "Animation/AnimMontage.h"

void UAnimationMontageAssetSerializer::SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const {
    const TArray<UObject*> RootPackageObjects = FAssetHelper::GetRootPackageObjects(AssetPackage);
    check(RootPackageObjects.Num() == 1);

    UAnimMontage* AnimMontage;
    check(RootPackageObjects.FindItemByClass<UAnimMontage>(&AnimMontage));

    //Just serialize object directly, UAnimMontage does not have a custom Serialize override
    //Few parent assets serialize some extra data though, but it's not crucial and is mostly used for fixups/legacy data conversion
    ObjectHierarchySerializer->SetObjectMark(AnimMontage, TEXT("AnimMontageObject"));
    ObjectHierarchySerializer->SerializeObjectPropertiesIntoObject(AnimMontage, OutObject);
}

EAssetCategory UAnimationMontageAssetSerializer::GetAssetCategory() const {
    return EAssetCategory::EAC_AnimMontage;
}
