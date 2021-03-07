#include "Toolkit/AssetTypes/StringTableAssetSerializer.h"
#include "Toolkit/AssetTypes/AssetHelper.h"
#include "Internationalization/StringTable.h"
#include "Internationalization/StringTableCore.h"

void UStringTableAssetSerializer::SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const {
    const TArray<UObject*> RootPackageObjects = FAssetHelper::GetRootPackageObjects(AssetPackage);
    check(RootPackageObjects.Num() == 1);

    UStringTable* StringTable;
    check(RootPackageObjects.FindItemByClass<UStringTable>(&StringTable));
    SerializeStringTable(StringTable, OutObject);
}

void UStringTableAssetSerializer::SerializeStringTable(UStringTable* StringTable, TSharedPtr<FJsonObject> OutObject) {
    const FStringTableConstRef StringTablePtr = StringTable->GetStringTable();
    OutObject->SetStringField(TEXT("TableNamespace"), StringTablePtr->GetNamespace());

    TSharedPtr<FJsonObject> SourceStrings = MakeShareable(new FJsonObject());
    StringTablePtr->EnumerateSourceStrings([&](const FString& InKey, const FString& DisplayString){
        SourceStrings->SetStringField(InKey, DisplayString);
        return true;
    });
    OutObject->SetObjectField(TEXT("SourceStrings"), SourceStrings);

    TArray<FString> InStringTableKeys;
    SourceStrings->Values.GetKeys(InStringTableKeys);

    TSharedPtr<FJsonObject> KeyMetaData = MakeShareable(new FJsonObject());
    for (const FString& InKey : InStringTableKeys) {
        TSharedPtr<FJsonObject> MetaDataObject = MakeShareable(new FJsonObject());
        StringTablePtr->EnumerateMetaData(InKey, [&](FName MetaDataKey, const FString& Value){
            MetaDataObject->SetStringField(MetaDataKey.ToString(), Value);
            return true;
        });
        if (MetaDataObject->Values.Num()) {
            KeyMetaData->SetObjectField(InKey, MetaDataObject);
        }
    }
    OutObject->SetObjectField(TEXT("MetaData"), KeyMetaData);
}

EAssetCategory UStringTableAssetSerializer::GetAssetCategory() const {
    return EAssetCategory::EAC_StringTable;
}
