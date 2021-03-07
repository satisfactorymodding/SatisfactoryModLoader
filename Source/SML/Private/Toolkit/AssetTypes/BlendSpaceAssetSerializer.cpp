#include "Toolkit/AssetTypes/BlendSpaceAssetSerializer.h"
#include "Toolkit/AssetTypes/AssetHelper.h"
#include "Animation/BlendSpaceBase.h"

void UBlendSpaceSerializer::SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const {
    const TArray<UObject*> RootPackageObjects = FAssetHelper::GetRootPackageObjects(AssetPackage);
    check(RootPackageObjects.Num() == 1);

    UBlendSpaceBase* BlendSpace;
    check(RootPackageObjects.FindItemByClass<UBlendSpaceBase>(&BlendSpace));

    SerializeBlendSpace(BlendSpace, OutObject, ObjectHierarchySerializer);
}

void UBlendSpaceSerializer::SerializeBlendSpace(UBlendSpaceBase* BlendSpace, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer) {
    //Serialize object class to known which kind of asset exactly we are creating
    OutObject->SetNumberField(TEXT("ObjectClass"), ObjectHierarchySerializer->SerializeObject(BlendSpace->GetClass()));
    
    //Serialize normal object properties, blend spaces don't have any important natively serialized information
    ObjectHierarchySerializer->SetObjectMark(BlendSpace, TEXT("BlendSpaceObject"));
    ObjectHierarchySerializer->SerializeObjectPropertiesIntoObject(BlendSpace, OutObject);
}

EAssetCategory UBlendSpaceSerializer::GetAssetCategory() const {
    return EAssetCategory::EAC_BlendSpaceBase;
}
