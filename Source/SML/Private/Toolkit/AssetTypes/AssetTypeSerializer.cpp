#include "Toolkit/AssetTypes/AssetTypeSerializer.h"
#include "UObject/UObjectIterator.h"

#pragma optimize("", off)

//Static class used to lazily populate serializer registry
class FAssetTypeSerializerRegistry {
public:
    //Native classes should never get unloaded anyway, so we can use TWeakObjectPtr safely
    TMap<EAssetCategory, TWeakObjectPtr<UAssetTypeSerializer>> Serializers;

    //Constructor that will automatically populate registry serializers
    void InitializeAssetTypeSerializerRegistry();
};

UAssetTypeSerializer* UAssetTypeSerializer::FindSerializerForAssetCategory(EAssetCategory AssetCategory) {
    //Populate asset type serializer registry lazily
    static FAssetTypeSerializerRegistry AssetTypeSerializerRegistry;
    static bool bRegistryInitialized = false;
    if (!bRegistryInitialized) {
        AssetTypeSerializerRegistry.InitializeAssetTypeSerializerRegistry();
        bRegistryInitialized = true;
    }

    //Retrieve serializer
    TWeakObjectPtr<UAssetTypeSerializer>* Serializer = AssetTypeSerializerRegistry.Serializers.Find(AssetCategory);
    if (Serializer != NULL) {
        return Serializer->Get();
    }
    return NULL;
}

void FAssetTypeSerializerRegistry::InitializeAssetTypeSerializerRegistry() {
    UClass* AssetTypeSerializerClass = UAssetTypeSerializer::StaticClass();

    //Iterate classes in memory to resolve serializers
    for (TObjectIterator<UClass> It; It; ++It) {
        UClass* Class = *It;
            
        //Skip classes that are not child of asset type serializer class
        if (!Class->IsChildOf(AssetTypeSerializerClass)) {
            continue;
        }
            
        //Skip classes that are marked as Abstract
        if (Class->HasAnyClassFlags(CLASS_Abstract)) {
            continue;
        }
            
        //Skip classes that are not marked as Native
        if (!Class->HasAnyClassFlags(CLASS_Native)) {
            continue;
        }
            
        //Check asset type in class default object
        UAssetTypeSerializer* ClassDefaultObject = Cast<UAssetTypeSerializer>(Class->GetDefaultObject());
        check(ClassDefaultObject);
        EAssetCategory ClassAssetCategory = ClassDefaultObject->GetAssetCategory();

        //Associate class with asset category specified
        if (ClassAssetCategory != EAssetCategory::EAC_Unknown) {
            Serializers.Add(ClassAssetCategory, ClassDefaultObject);
        }
    }
}

#pragma optimize("", on)
