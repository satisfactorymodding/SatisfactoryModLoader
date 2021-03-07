#include "Toolkit/AssetTypes/CurveBaseAssetSerializer.h"
#include "Toolkit/AssetTypes/AssetHelper.h"
#include "Curves/CurveBase.h"

void UCurveBaseAssetSerializer::SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const {
    const TArray<UObject*> RootPackageObjects = FAssetHelper::GetRootPackageObjects(AssetPackage);
    check(RootPackageObjects.Num() == 1);

    UCurveBase* CurveAsset;
    check(RootPackageObjects.FindItemByClass<UCurveBase>(&CurveAsset));

    SerializeCurveBase(CurveAsset, OutObject, ObjectHierarchySerializer);
}

void UCurveBaseAssetSerializer::SerializeCurveBase(UCurveBase* Curve, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer) {
    //Serialize object class to known which kind of asset exactly we are creating
    OutObject->SetNumberField(TEXT("ObjectClass"), ObjectHierarchySerializer->SerializeObject(Curve->GetClass()));
    
    //Serialize normal object properties, curves don't have native serialization at all
    ObjectHierarchySerializer->SetObjectMark(Curve, TEXT("CurveObject"));
    ObjectHierarchySerializer->SerializeObjectPropertiesIntoObject(Curve, OutObject);
}

EAssetCategory UCurveBaseAssetSerializer::GetAssetCategory() const {
    return EAssetCategory::EAC_CurveBase;
}
