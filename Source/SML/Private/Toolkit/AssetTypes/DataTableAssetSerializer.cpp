#include "Toolkit/AssetTypes/DataTableAssetSerializer.h"
#include "Toolkit/AssetTypes/AssetHelper.h"
#include "Toolkit/PropertySerializer.h"
#include "Engine/DataTable.h"

void UDataTableAssetSerializer::SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const {
    const TArray<UObject*> RootPackageObjects = FAssetHelper::GetRootPackageObjects(AssetPackage);
    check(RootPackageObjects.Num() == 1);

    UDataTable* DataTable;
    check(RootPackageObjects.FindItemByClass<UDataTable>(&DataTable));
    SerializeDataTable(DataTable, OutObject, ObjectHierarchySerializer);
}

void UDataTableAssetSerializer::SerializeDataTable(UDataTable* DataTable, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer) {
    UPropertySerializer* PropertySerializer = ObjectHierarchySerializer->GetPropertySerializer<UPropertySerializer>();
    const int32 RowStructIndex = ObjectHierarchySerializer->SerializeObject(DataTable->RowStruct);
    OutObject->SetNumberField(TEXT("RowStruct"), RowStructIndex);

    const TSharedPtr<FJsonObject> RowData = MakeShareable(new FJsonObject());
    const TMap<FName, uint8*>& RowDataMap = DataTable->GetRowMap();
    for (const TPair<FName, uint8*>& RowDataPair : RowDataMap) {
        TSharedPtr<FJsonObject> StructData = PropertySerializer->SerializeStruct(DataTable->RowStruct, RowDataPair.Value);
        RowData->SetObjectField(RowDataPair.Key.ToString(), StructData);
    }
    OutObject->SetObjectField(TEXT("RowData"), RowData);
}

EAssetCategory UDataTableAssetSerializer::GetAssetCategory() const {
    return EAssetCategory::EAC_DataTable;
}
