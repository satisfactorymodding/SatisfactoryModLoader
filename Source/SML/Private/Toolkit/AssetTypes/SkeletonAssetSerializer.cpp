#include "Toolkit/AssetTypes/SkeletonAssetSerializer.h"
#include "Toolkit/AssetTypes/AssetHelper.h"
#include "Toolkit/AssetTypes/FbxMeshExporter.h"
#include "Toolkit/PropertySerializer.h"
#include "Reflection/ReflectionHelper.h"
#include "Toolkit/AssetTypes/SkeletalMeshAssetSerializer.h"
#include "Animation/Skeleton.h"

void USkeletonAssetSerializer::SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const {
    const TArray<UObject*> RootPackageObjects = FAssetHelper::GetRootPackageObjects(AssetPackage);
    check(RootPackageObjects.Num() == 1);

    USkeleton* Skeleton;
    check(RootPackageObjects.FindItemByClass<USkeleton>(&Skeleton));

    SerializeSkeleton(Skeleton, OutObject, ObjectHierarchySerializer, Context);
}

void USkeletonAssetSerializer::SerializeSkeleton(USkeleton* Skeleton, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) {
    //Serialize reference skeleton object
    const TSharedPtr<FJsonObject> ReferenceSkeleton = MakeShareable(new FJsonObject());
    USkeletalMeshAssetSerializer::SerializeReferenceSkeleton(Skeleton->GetReferenceSkeleton(), ReferenceSkeleton);
    OutObject->SetObjectField(TEXT("ReferenceSkeleton"), ReferenceSkeleton);
    
    //Serialize Skeleton GUID used by cooking
    OutObject->SetStringField(TEXT("Guid"), Skeleton->GetGuid().ToString());

    //Serialize animation retarget sources
    //No idea what they are used for, but might be a good idea to serialize
    UPropertySerializer* PropertySerializer = ObjectHierarchySerializer->GetPropertySerializer<UPropertySerializer>();
    UScriptStruct* ReferencePoseStruct = FReferencePose::StaticStruct();
    TArray<TSharedPtr<FJsonValue>> AnimRetargetSources;
    
    for (const TPair<FName, FReferencePose>& Pair : Skeleton->AnimRetargetSources) {
        TSharedPtr<FJsonObject> PairObject = MakeShareable(new FJsonObject());
        PairObject->SetStringField(TEXT("Name"), Pair.Key.ToString());
        PairObject->SetObjectField(TEXT("Pose"), PropertySerializer->SerializeStruct(ReferencePoseStruct, &Pair.Value));
        AnimRetargetSources.Add(MakeShareable(new FJsonValueObject(PairObject)));
    }
    OutObject->SetArrayField(TEXT("AnimRetargetSources"), AnimRetargetSources);
    
    PropertySerializer->DisablePropertySerialization(USkeleton::StaticClass(), TEXT("SmartNames"));
    UProperty* SmartNamesProperty = USkeleton::StaticClass()->FindPropertyByName(TEXT("SmartNames"));
    const FSmartNameContainer* SmartNameContainer = SmartNamesProperty->ContainerPtrToValuePtr<FSmartNameContainer>(Skeleton);

    const TSharedPtr<FJsonObject> NameContainer = MakeShareable(new FJsonObject());
    SerializeSmartNameContainer(*SmartNameContainer, NameContainer);
    OutObject->SetObjectField(TEXT("SmartNames"), NameContainer);

    ObjectHierarchySerializer->SetObjectMark(Skeleton, TEXT("SkeletonAssetObject"));
    ObjectHierarchySerializer->SerializeObjectPropertiesIntoObject(Skeleton, OutObject);

    //Serialize skeleton itself into the fbx file
    const FString OutFbxFileName = Context.GetAdditionalFilePath(TEXT(""), TEXT("fbx"));
    FString OutErrorMessage;
    const bool bSuccess = FFbxMeshExporter::ExportSkeletonIntoFbxFile(Skeleton, OutFbxFileName, false, &OutErrorMessage);
    checkf(bSuccess, TEXT("Failed to export skeleton %s: %s"), *Skeleton->GetPathName(), *OutErrorMessage);
}

void USkeletonAssetSerializer::SerializeSmartNameContainer(const FSmartNameContainer& Container, TSharedPtr<FJsonObject> OutObject) {
    //Serialize smart name mappings
    TArray<TSharedPtr<FJsonValue>> NameMappings;
    for (FName SmartNameId : Container.GetMappingNames()) {
        const FSmartNameMapping* Mapping = Container.GetContainer(SmartNameId);
        
        TSharedPtr<FJsonObject> NameMapping = MakeShareable(new FJsonObject());
        NameMapping->SetStringField(TEXT("Name"), SmartNameId.ToString());
        
        TArray<FName> MetaDataKeys;
        Mapping->FillUIDToNameArray(MetaDataKeys);

        TArray<TSharedPtr<FJsonValue>> CurveMetaDataMap;
        
        for (const FName& MetaDataKey : MetaDataKeys) {
            const TSharedPtr<FJsonObject> MetaDataObject = MakeShareable(new FJsonObject());
            const FCurveMetaData* MetaData = Mapping->GetCurveMetaData(MetaDataKey);
            
            MetaDataObject->SetStringField(TEXT("MetaDataKey"), MetaDataKey.ToString());
            MetaDataObject->SetBoolField(TEXT("bMaterial"), MetaData->Type.bMaterial);
            MetaDataObject->SetBoolField(TEXT("bMorphtarget"), MetaData->Type.bMorphtarget);
            MetaDataObject->SetNumberField(TEXT("MaxLOD"), MetaData->MaxLOD);
            
            TArray<TSharedPtr<FJsonValue>> LinkedBones;
            for (const FBoneReference& BoneReference : MetaData->LinkedBones) {
                LinkedBones.Add(MakeShareable(new FJsonValueString(BoneReference.BoneName.ToString())));
            }
            
            MetaDataObject->SetArrayField(TEXT("LinkedBones"), LinkedBones);
            CurveMetaDataMap.Add(MakeShareable(new FJsonValueObject(MetaDataObject)));
        }
        
        NameMapping->SetArrayField(TEXT("CurveMetaDataMap"), CurveMetaDataMap);
        NameMappings.Add(MakeShareable(new FJsonValueObject(NameMapping)));
    }
    OutObject->SetArrayField(TEXT("NameMappings"), NameMappings);
}

EAssetCategory USkeletonAssetSerializer::GetAssetCategory() const {
    return EAssetCategory::EAC_Skeleton;
}
