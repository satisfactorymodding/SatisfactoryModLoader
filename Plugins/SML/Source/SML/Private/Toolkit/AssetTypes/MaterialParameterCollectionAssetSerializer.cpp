#include "Toolkit/AssetTypes/MaterialParameterCollectionAssetSerializer.h"

#include "Toolkit/AssetTypes/AssetHelper.h"
#include "Materials/MaterialParameterCollection.h"

void UMaterialParameterCollectionAssetSerializer::SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const {
    const TArray<UObject*> RootPackageObjects = FAssetHelper::GetRootPackageObjects(AssetPackage);
    check(RootPackageObjects.Num() == 1);

    UMaterialParameterCollection* MaterialParameterCollection;
    check(RootPackageObjects.FindItemByClass<UMaterialParameterCollection>(&MaterialParameterCollection));
    
    //In fact, MPC is one of the simplest assets to serialize
    //It doesn't even have custom Serialize override with extra data, just normal UPROPERTY structs
    const int32 CollectionObjectIndex = ObjectHierarchySerializer->SerializeObject(MaterialParameterCollection);
    OutObject->SetNumberField(TEXT("MaterialParameterCollection"), CollectionObjectIndex);
}

EAssetCategory UMaterialParameterCollectionAssetSerializer::GetAssetCategory() const {
    return EAssetCategory::EAC_MaterialParameterCollection;
}
