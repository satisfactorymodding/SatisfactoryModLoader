#include "Toolkit/AssetTypes/UserDefinedStructAssetSerializer.h"
#include "Engine/UserDefinedStruct.h"
#include "Toolkit/AssetTypes/AssetHelper.h"
#include "Toolkit/PropertySerializer.h"

void UUserDefinedStructAssetSerializer::SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const {
    //Should have only one root object - instance of UUserDefinedStruct
    const TArray<UObject*> RootObjects = FAssetHelper::GetRootPackageObjects(AssetPackage);
    check(RootObjects.Num() == 1);

    UUserDefinedStruct* UserDefinedStruct = Cast<UUserDefinedStruct>(RootObjects[0]);
    check(UserDefinedStruct);

    //Serialize UUserDefinedStruct now
    SerializeUserDefinedStruct(OutObject, UserDefinedStruct, ObjectHierarchySerializer);
}

void UUserDefinedStructAssetSerializer::SerializeUserDefinedStruct(TSharedPtr<FJsonObject> OutObject, UUserDefinedStruct* Struct, UObjectHierarchySerializer* ObjectHierarchySerializer) {
    //Serialize normal script struct data
    FAssetHelper::SerializeScriptStruct(OutObject, Struct, ObjectHierarchySerializer);

    //Serialize status (should be up to date outside editor)
    OutObject->SetNumberField(TEXT("Status"), Struct->Status);
    OutObject->SetStringField(TEXT("Guid"), Struct->GetCustomGuid().ToString());

    //Serialize struct default object directly
    UPropertySerializer* PropertySerializer = ObjectHierarchySerializer->GetPropertySerializer<UPropertySerializer>();
    const TSharedRef<FJsonObject> DefaultInstance = PropertySerializer->SerializeStruct(Struct, Struct->GetDefaultInstance());
    OutObject->SetObjectField(TEXT("StructDefaultInstance"), DefaultInstance);
}

EAssetCategory UUserDefinedStructAssetSerializer::GetAssetCategory() const {
    return EAssetCategory::EAC_UserDefinedStruct;
}
