#include "Toolkit/AssetTypes/CurveLinearColorAtlasAssetSerializer.h"

#include "Toolkit/AssetTypes/AssetHelper.h"
#include "Toolkit/AssetTypes/TextureAssetSerializer.h"
#include "Curves/CurveLinearColor.h"
#include "Curves/CurveLinearColorAtlas.h"

void UCurveLinearColorAtlasAssetSerializer::SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const {
    const TArray<UObject*> RootPackageObjects = FAssetHelper::GetRootPackageObjects(AssetPackage);
    check(RootPackageObjects.Num() == 1);

    UCurveLinearColorAtlas* ColorAtlas;
    check(RootPackageObjects.FindItemByClass<UCurveLinearColorAtlas>(&ColorAtlas));
    
    SerializeColorAtlas(ColorAtlas, OutObject, ObjectHierarchySerializer, Context);
}

void UCurveLinearColorAtlasAssetSerializer::SerializeColorAtlas(UCurveLinearColorAtlas* LinearColorAtlas, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) {
    UTextureAssetSerializer::SerializeTexture2D(LinearColorAtlas, OutObject, ObjectHierarchySerializer, Context, TEXT(""));

    //Serialize some extra properties added by UCurveLinearColorAtlas
    OutObject->SetNumberField(TEXT("TextureSize"), LinearColorAtlas->TextureSize);

    //Theoretically referenced curves should be separate external assets
    //I haven't found a single place where such curves are added internally and are owned by this asset
    TArray<TSharedPtr<FJsonValue>> GradientCurves;
    for (UCurveLinearColor* Curve : LinearColorAtlas->GradientCurves) {
        const int32 ObjectIndex = ObjectHierarchySerializer->SerializeObject(Curve);
        GradientCurves.Add(MakeShareable(new FJsonValueNumber(ObjectIndex)));
    }
    OutObject->SetArrayField(TEXT("GradientCurves"), GradientCurves);
}

EAssetCategory UCurveLinearColorAtlasAssetSerializer::GetAssetCategory() const {
    return EAssetCategory::EAC_CurveLinearColorAtlas;
}
