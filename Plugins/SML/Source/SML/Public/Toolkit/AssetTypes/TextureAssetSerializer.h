#pragma once
#include "Toolkit/AssetTypes/AssetTypeSerializer.h"
#include "TextureAssetSerializer.generated.h"

UCLASS()
class SML_API UTextureAssetSerializer : public UAssetTypeSerializer {
    GENERATED_BODY()
public:
    virtual void SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const override;

    /** Serializes actual texture payload into provided serialization context. Set bResetAlpha to true to make entire image opaque and force alpha to 1.0f */
    static void SerializeTextureData(class UTexture* Texture, struct FTexturePlatformData* PlatformData, TSharedPtr<FJsonObject> OutObject, FAssetSerializationContext& SerializationContext, bool bResetAlpha, const FString& FileNamePostfix);
    
    /** Serializes Texture2D, including exporting it to image file saved alongside json */
    static void SerializeTexture2D(class UTexture2D* Texture2D, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context, const FString& FileNamePostfix);
    
    /** Serialize data common to all UTexture objects */
    static void SerializeTexture(class UTexture* Texture, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer);

    virtual EAssetCategory GetAssetCategory() const override;    
};
