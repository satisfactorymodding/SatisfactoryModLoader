#include "Toolkit/AssetTypes/AnimationSequenceAssetSerializer.h"
#include "Toolkit/AssetTypes/AssetHelper.h"
#include "Toolkit/AssetTypes/FbxMeshExporter.h"
#include "Toolkit/PropertySerializer.h"
#include "Animation/AnimSequenceBase.h"
#include "Animation/AnimSequence.h"

void UAnimationSequenceAssetSerializer::SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const {
    const TArray<UObject*> RootPackageObjects = FAssetHelper::GetRootPackageObjects(AssetPackage);
    check(RootPackageObjects.Num() == 1);

    UAnimSequence* AnimSequence;
    check(RootPackageObjects.FindItemByClass<UAnimSequence>(&AnimSequence));

    SerializeAnimationSequence(AnimSequence, OutObject, ObjectHierarchySerializer, Context);
}

void UAnimationSequenceAssetSerializer::SerializeAnimationSequence(UAnimSequence* AnimSequence, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* Serializer, FAssetSerializationContext& Context) {
    UPropertySerializer* PropertySerializer = Serializer->GetPropertySerializer<UPropertySerializer>();
    
    //Disable serialization of RawCurveData. It will always be empty during cooking anyway, UAnimSequence class ensures that it is the case.
    PropertySerializer->DisablePropertySerialization(UAnimSequenceBase::StaticClass(), TEXT("RawCurveData"));
    check(AnimSequence->RawCurveData.FloatCurves.Num() == 0);

    //Serialize properties normally. It will serialize everything except compressed data
    //And we serialize compressed data as a separate fbx file that can be imported back
    Serializer->SetObjectMark(AnimSequence, TEXT("AnimationSequenceObject"));
    Serializer->SerializeObjectPropertiesIntoObject(AnimSequence, OutObject);

    //Serialize animation data
    const FString OutFbxFileName = Context.GetAdditionalFilePath(TEXT(""), TEXT("fbx"));
    FString OutErrorMessage;
    const bool bSuccess = FFbxMeshExporter::ExportAnimSequenceIntoFbxFile(AnimSequence, OutFbxFileName, false, &OutErrorMessage);
    checkf(bSuccess, TEXT("Failed to export anim sequence %s: %s"), *AnimSequence->GetPathName(), *OutErrorMessage);
}

EAssetCategory UAnimationSequenceAssetSerializer::GetAssetCategory() const {
    return EAssetCategory::EAC_AnimSequence;
}
