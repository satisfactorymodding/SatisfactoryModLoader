#include "Toolkit/AssetTypes/FontFaceAssetSerializer.h"
#include "Toolkit/AssetTypes/AssetHelper.h"
#include "Toolkit/PropertySerializer.h"
#include "Engine/FontFace.h"

void UFontFaceAssetSerializer::SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const {
    UPropertySerializer* Serializer = ObjectHierarchySerializer->GetPropertySerializer<UPropertySerializer>();
    const TArray<UObject*> RootPackageObjects = FAssetHelper::GetRootPackageObjects(AssetPackage);
    check(RootPackageObjects.Num() == 1);

    UFontFace* FontFace;
    check(RootPackageObjects.FindItemByClass<UFontFace>(&FontFace));

    //Serialize basic font face information
    ObjectHierarchySerializer->SerializeObjectPropertiesIntoObject(FontFace, OutObject);

    //What we do next depends on loading policy specified
    TArray64<uint8> FontRawData;
    if (FontFace->LoadingPolicy == EFontLoadingPolicy::Inline) {
        //Font is inlined into this font face asset, retrieve data directly
        FontRawData = FontFace->FontFaceData.Get().GetData();
    } else {
        //Font is saved inside of the cooked file, load the file by source file path
        FFileHelper::LoadFileToArray(FontRawData, *FontFace->SourceFilename);
    }
    //Make sure we loaded data and dump it into destination file
    check(FontRawData.Num());

    //Theoretically .ufont can be any kind of font format that FreeType supports,
    //but since most of the programs (including UE importer and Windows font viewer) are able to
    //differentiate between TrueType and OpenType without looking at the extension, we just assume ttf format
    Context.SaveAdditionalAssetFile(TEXT("ttf"), FontRawData);
}

EAssetCategory UFontFaceAssetSerializer::GetAssetCategory() const {
    return EAssetCategory::EAC_FontFace;
}
