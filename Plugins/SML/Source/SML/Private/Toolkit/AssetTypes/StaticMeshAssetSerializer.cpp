#include "Toolkit/AssetTypes/StaticMeshAssetSerializer.h"
#include "Toolkit/AssetTypes/AssetHelper.h"
#include "Toolkit/AssetTypes/FbxMeshExporter.h"
#include "Engine/StaticMesh.h"
#include "PhysicsEngine/BodySetup.h"
#include "AI/Navigation/NavCollisionBase.h"

void UStaticMeshAssetSerializer::SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const {
    const TArray<UObject*> RootPackageObjects = FAssetHelper::GetRootPackageObjects(AssetPackage);
    check(RootPackageObjects.Num() == 1);

    UStaticMesh* StaticMesh;
    check(RootPackageObjects.FindItemByClass<UStaticMesh>(&StaticMesh));

    SerializeStaticMesh(StaticMesh, OutObject, ObjectHierarchySerializer, Context);
}

void UStaticMeshAssetSerializer::SerializeStaticMesh(UStaticMesh* StaticMesh, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) {
    //Just serialize normal properties into root object
    ObjectHierarchySerializer->SetObjectMark(StaticMesh, TEXT("StaticMeshObject"));
    ObjectHierarchySerializer->SerializeObjectPropertiesIntoObject(StaticMesh, OutObject);

    //Serialize extra properties using native serialization
    OutObject->SetNumberField(TEXT("MaxShadowLOD"), StaticMesh->MaxShadowLOD);
    OutObject->SetStringField(TEXT("LightingGuid"), StaticMesh->LightingGuid.ToString());
    OutObject->SetNumberField(TEXT("NavCollision"), ObjectHierarchySerializer->SerializeObject(StaticMesh->NavCollision));
    
    //For some reason some UPROPERTY are duplicated in native serialization, e.g StaticMaterials and Sockets
    //we won't serialize them twice because there is literally no reason to do it
    
    //Serialize BodySetup since it is serialized natively
    const TSharedPtr<FJsonObject> BodySetupObject = SerializeBodySetup(StaticMesh->BodySetup, ObjectHierarchySerializer);
    OutObject->SetObjectField(TEXT("BodySetup"), BodySetupObject);

    //Export raw mesh data into separate FBX file that can be imported back into UE
    const FString OutFbxMeshFileName = Context.GetAdditionalFilePath(TEXT(""), TEXT("fbx"));
    FString OutErrorMessage;
    const bool bSuccess = FFbxMeshExporter::ExportStaticMeshIntoFbxFile(StaticMesh, OutFbxMeshFileName, false, &OutErrorMessage);
    checkf(bSuccess, TEXT("Failed to export static mesh %s: %s"), *StaticMesh->GetPathName(), *OutErrorMessage);
}

TSharedPtr<FJsonObject> UStaticMeshAssetSerializer::SerializeBodySetup(UBodySetup* BodySetup, UObjectHierarchySerializer* ObjectHierarchySerializer) {
    TSharedPtr<FJsonObject> BodySetupObject = MakeShareable(new FJsonObject());
    if (BodySetup != NULL) {
        //Serialize normal body setup properties
        
        //Body setup should only serialize imported objects really
        ObjectHierarchySerializer->SetAllowExportedObjectSerialization(false);
        ObjectHierarchySerializer->SerializeObjectPropertiesIntoObject(BodySetup, BodySetupObject);
        ObjectHierarchySerializer->SetAllowExportedObjectSerialization(true);
        
        //We don't really serialize cooked complex collision data, but set the flag indicating if we had one
        BodySetupObject->SetBoolField(TEXT("bHasCookedCollisionData"), BodySetup->bHasCookedCollisionData);
    }
    return BodySetupObject;
}

EAssetCategory UStaticMeshAssetSerializer::GetAssetCategory() const {
    return EAssetCategory::EAC_StaticMesh;
}
