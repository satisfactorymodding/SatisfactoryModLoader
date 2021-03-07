#include "Toolkit/AssetTypes/MaterialInstanceAssetSerializer.h"
#include "Toolkit/AssetTypes/AssetHelper.h"
#include "Toolkit/AssetTypes/MaterialAssetSerializer.h"
#include "Materials/MaterialInstanceConstant.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Toolkit/PropertySerializer.h"

void UMaterialInstanceAssetSerializer::SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const {
    const TArray<UObject*> RootObjects = FAssetHelper::GetRootPackageObjects(AssetPackage);
    check(RootObjects.Num() == 1);

    UMaterialInstanceConstant* MaterialInstanceConstant;
    check(RootObjects.FindItemByClass<UMaterialInstanceConstant>(&MaterialInstanceConstant));

    SerializeMaterialInstance(MaterialInstanceConstant, OutObject, ObjectHierarchySerializer, Context);
}

void UMaterialInstanceAssetSerializer::SerializeMaterialInstance(UMaterialInstance* MaterialInstance, TSharedPtr<FJsonObject> OutJson, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& SerializationContext) {
    //Serialize basic properties
    //all of them are perfectly serializable on material instance object
    OutJson->SetObjectField(TEXT("Properties"), ObjectHierarchySerializer->SerializeObjectProperties(MaterialInstance));

    //Serialize shader maps if this material instance has static permutations
    OutJson->SetBoolField(TEXT("HasStaticPermutationResource"), MaterialInstance->bHasStaticPermutationResource);

    if (MaterialInstance->bHasStaticPermutationResource) {
        //Gather all unique material resources
        TSet<FMaterialResource*> MaterialResources;
        for (int32 FeatureLevel = 0; FeatureLevel < ERHIFeatureLevel::Num; FeatureLevel++) {
            for (int32 QualityLevel = 0; QualityLevel < EMaterialQualityLevel::Num; QualityLevel++) {
                FMaterialResource* MaterialResource = MaterialInstance->GetMaterialResource((ERHIFeatureLevel::Type) FeatureLevel, EMaterialQualityLevel::High);
                if (MaterialResource != NULL && MaterialResource->GetGameThreadShaderMap() != NULL) {
                    MaterialResources.Add(MaterialResource);
                }
            }
        }
        
        check(MaterialResources.Num() > 0);

        //Dump material resources general information into json and shader bytecode into binary files
        TArray<TSharedPtr<FJsonValue>> MaterialResourcesArray;
        for (FMaterialResource* MaterialResource : MaterialResources) {
            const TSharedPtr<FJsonObject> ResourceObject = MakeShareable(new FJsonObject());
            //UMaterialAssetSerializer::SerializeMaterialResource(MaterialResource, ResourceObject, ObjectHierarchySerializer, SerializationContext);
            MaterialResourcesArray.Add(MakeShareable(new FJsonValueObject(ResourceObject)));
        }
        OutJson->SetArrayField(TEXT("MaterialResources"), MaterialResourcesArray);
    }
}

EAssetCategory UMaterialInstanceAssetSerializer::GetAssetCategory() const {
    return EAssetCategory::EAC_MaterialInstance;
}
