#include "Toolkit/AssetTypes/FontAssetSerializer.h"
#include "Toolkit/AssetTypes/AssetHelper.h"
#include "Toolkit/PropertySerializer.h"
#include "Toolkit/AssetTypes/TextureAssetSerializer.h"
#include "Engine/Font.h"
#include "Engine/Texture2D.h"

void UFontAssetSerializer::SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const {
    const TArray<UObject*> RootPackageObjects = FAssetHelper::GetRootPackageObjects(AssetPackage);
    check(RootPackageObjects.Num() == 1);

    UFont* Font;
    check(RootPackageObjects.FindItemByClass<UFont>(&Font));

    //Blacklist serialization of textures, since they are inlined straight into font asset
    //and need special treatment for serialization
    UPropertySerializer* Serializer = ObjectHierarchySerializer->GetPropertySerializer<UPropertySerializer>();
    Serializer->DisablePropertySerialization(UFont::StaticClass(), TEXT("Textures"));

    //Serialize normal attributes into root object
    ObjectHierarchySerializer->SetObjectMark(Font, TEXT("FontAssetObject"));
    ObjectHierarchySerializer->SerializeObjectPropertiesIntoObject(Font, OutObject);

    //Serialize Textures using texture serializer
    TArray<TSharedPtr<FJsonValue>> Textures;
    for (UTexture2D* Texture2D : Font->Textures) {
        //Texture should be owned by material asset and not imported from external asset
        check(Texture2D->GetOuter() == Font);
        
        //Serialize normal texture data and use name of texture as filename postfix
        const TSharedPtr<FJsonObject> TextureObject = MakeShareable(new FJsonObject());
        TextureObject->SetStringField(TEXT("TextureName"), *Texture2D->GetName());
        
        UTextureAssetSerializer::SerializeTexture2D(Texture2D, TextureObject, ObjectHierarchySerializer, Context, *Texture2D->GetName());
        Textures.Add(MakeShareable(new FJsonValueObject(TextureObject)));
    }
    OutObject->SetArrayField(TEXT("Textures"), Textures);

    //Serialize remap map if it is not empty
    TArray<TSharedPtr<FJsonValue>> CharacterRemapMap;
    for (const TPair<uint16, uint16>& Pair : Font->CharRemap) {
        TSharedPtr<FJsonObject> Character = MakeShareable(new FJsonObject());
        Character->SetNumberField(TEXT("SourceCharacter"), Pair.Key);
        Character->SetNumberField(TEXT("DestCharacter"), Pair.Value);
        CharacterRemapMap.Add(MakeShareable(new FJsonValueObject(Character)));
    }
    if (Font->IsRemapped) {
        OutObject->SetArrayField(TEXT("CharRemap"), CharacterRemapMap);
    }
}

EAssetCategory UFontAssetSerializer::GetAssetCategory() const {
    return EAssetCategory::EAC_Font;
}
