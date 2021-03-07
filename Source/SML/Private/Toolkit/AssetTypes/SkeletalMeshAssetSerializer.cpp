#include "Toolkit/AssetTypes/SkeletalMeshAssetSerializer.h"
#include "Toolkit/AssetTypes/AssetHelper.h"
#include "Toolkit/AssetTypes/FbxMeshExporter.h"
#include "Toolkit/PropertySerializer.h"
#include "Toolkit/AssetTypes/StaticMeshAssetSerializer.h"
#include "Engine/SkeletalMesh.h"

void USkeletalMeshAssetSerializer::SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const {
    const TArray<UObject*> RootPackageObjects = FAssetHelper::GetRootPackageObjects(AssetPackage);
    check(RootPackageObjects.Num() == 1);

    USkeletalMesh* SkeletalMesh;
    check(RootPackageObjects.FindItemByClass<USkeletalMesh>(&SkeletalMesh));

    SerializeSkeletalMesh(SkeletalMesh, OutObject, ObjectHierarchySerializer, Context);
}

void USkeletalMeshAssetSerializer::SerializeSkeletalMesh(USkeletalMesh* SkeletalMesh, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) {
    UPropertySerializer* PropertySerializer = ObjectHierarchySerializer->GetPropertySerializer<UPropertySerializer>();
    
    //Just serialize normal properties into root object
    ObjectHierarchySerializer->SetObjectMark(SkeletalMesh, TEXT("SkeletalMeshObject"));
    ObjectHierarchySerializer->SerializeObjectPropertiesIntoObject(SkeletalMesh, OutObject);

    //Serialize few properties that are marked as transient but in fact are serialized natively (probably for cooking/compatibility reasons)
    OutObject->SetField(TEXT("Materials"), PropertySerializer->SerializePropertyByName(SkeletalMesh, TEXT("Materials")));
    OutObject->SetField(TEXT("ImportedBounds"), PropertySerializer->SerializePropertyByName(SkeletalMesh, TEXT("ImportedBounds")));

    //Serialize reference skeleton
    const TSharedPtr<FJsonObject> ReferenceSkeleton = MakeShareable(new FJsonObject());
    SerializeReferenceSkeleton(SkeletalMesh->RefSkeleton, ReferenceSkeleton);
    OutObject->SetObjectField(TEXT("RefSkeleton"), ReferenceSkeleton);
    
    //Serialize BodySetup if per poly collision is enabled
    if (SkeletalMesh->bEnablePerPolyCollision) {
        const TSharedPtr<FJsonObject> BodySetupObject = UStaticMeshAssetSerializer::SerializeBodySetup(SkeletalMesh->BodySetup, ObjectHierarchySerializer);
        OutObject->SetObjectField(TEXT("BodySetup"), BodySetupObject);
    }

    //Export raw mesh data into separate FBX file that can be imported back into UE
    const FString OutFbxMeshFileName = Context.GetAdditionalFilePath(TEXT(""), TEXT("fbx"));
    FString OutErrorMessage;
    const bool bSuccess = FFbxMeshExporter::ExportSkeletalMeshIntoFbxFile(SkeletalMesh, OutFbxMeshFileName, false, &OutErrorMessage);
    checkf(bSuccess, TEXT("Failed to export skeletal mesh %s: %s"), *SkeletalMesh->GetPathName(), *OutErrorMessage);
}

void USkeletalMeshAssetSerializer::SerializeReferenceSkeleton(const FReferenceSkeleton& ReferenceSkeleton, TSharedPtr<FJsonObject> OutObject) {
    //Serialize pose together with bone info
    TArray<TSharedPtr<FJsonValue>> SkeletonBones;
    for (int32 i = 0; i < ReferenceSkeleton.GetRawBoneNum(); i++) {
        const FMeshBoneInfo& BoneInfo = ReferenceSkeleton.GetRawRefBoneInfo()[i];
        const FTransform& PoseTransform = ReferenceSkeleton.GetRawRefBonePose()[i];
        
        TSharedPtr<FJsonObject> BoneObject = MakeShareable(new FJsonObject());
        BoneObject->SetStringField(TEXT("Name"), BoneInfo.Name.ToString());
        BoneObject->SetNumberField(TEXT("ParentIndex"), BoneInfo.ParentIndex);
        BoneObject->SetNumberField(TEXT("Index"), i);
        BoneObject->SetStringField(TEXT("Pose"), PoseTransform.ToString());
        
        SkeletonBones.Add(MakeShareable(new FJsonValueObject(BoneObject)));
    }
    OutObject->SetArrayField(TEXT("Bones"), SkeletonBones);
    
    //Do not serialize RawNameToIndexMap because it can be reconstructed
    //from serialize bone info structure
}

EAssetCategory USkeletalMeshAssetSerializer::GetAssetCategory() const {
    return EAssetCategory::EAC_SkeletalMesh;
}
