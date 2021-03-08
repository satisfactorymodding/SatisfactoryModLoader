#include "Toolkit/AssetTypes/UserDefinedEnumAssetSerializer.h"
#include "Toolkit/AssetTypes/AssetHelper.h"
#include "Engine/UserDefinedEnum.h"

void UUserDefinedEnumAssetSerializer::SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const {
    //Should have only one root object - instance of UUserDefinedEnum
    const TArray<UObject*> RootObjects = FAssetHelper::GetRootPackageObjects(AssetPackage);
    check(RootObjects.Num() == 1);

    UUserDefinedEnum* UserDefinedEnum = Cast<UUserDefinedEnum>(RootObjects[0]);
    check(UserDefinedEnum);

    //Serialize UUserDefinedEnum now
    SerializeUserDefinedEnum(OutObject, UserDefinedEnum);
}

void UUserDefinedEnumAssetSerializer::SerializeUserDefinedEnum(TSharedPtr<FJsonObject> OutObject, UUserDefinedEnum* Enum) {
    //Serialize normal Enum contents first
    FAssetHelper::SerializeEnum(OutObject, Enum);

    //Serialize display name map
    TArray<TSharedPtr<FJsonValue>> DisplayNameMap;
    for (int32 i = 0; i < Enum->NumEnums(); i++) {
        DisplayNameMap.Add(MakeShareable(new FJsonValueString(Enum->GetDisplayNameTextByIndex(i).ToString())));
    }
    OutObject->SetArrayField(TEXT("DisplayNameMap"), DisplayNameMap);
}

EAssetCategory UUserDefinedEnumAssetSerializer::GetAssetCategory() const {
    return EAssetCategory::EAC_UserDefinedEnum;
}
