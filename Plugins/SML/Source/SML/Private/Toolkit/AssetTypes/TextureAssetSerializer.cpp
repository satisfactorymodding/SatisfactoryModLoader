#include "Toolkit/AssetTypes/TextureAssetSerializer.h"
#include "Toolkit/AssetTypes/AssetHelper.h"
#include "IImageWrapperModule.h"
#include "Modules/ModuleManager.h"
#include "Engine/Texture2D.h"
#include "Toolkit/AssetTypes/TextureDecompressor.h"
#include "IImageWrapper.h"
#include "Engine/AssetUserData.h"

void UTextureAssetSerializer::SerializeAsset(UPackage* AssetPackage, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context) const {
    const TArray<UObject*> RootPackageObjects = FAssetHelper::GetRootPackageObjects(AssetPackage);
    check(RootPackageObjects.Num() == 1);

    UTexture2D* Texture2D;
    check(RootPackageObjects.FindItemByClass<UTexture2D>(&Texture2D));
    
    SerializeTexture2D(Texture2D, OutObject, ObjectHierarchySerializer, Context, TEXT(""));
}

void ClearAlphaFromBGRA8Texture(void* TextureData, int32 NumPixels) {
    FColor* TextureDataColor = static_cast<FColor*>(TextureData);

    for (int i = 0; i < NumPixels; i++) {
        FColor* CurrentColor = TextureDataColor++;
        CurrentColor->A = 255;
    }
}

void UTextureAssetSerializer::SerializeTextureData(UTexture* Texture, FTexturePlatformData* PlatformData, TSharedPtr<FJsonObject> OutObject, FAssetSerializationContext& SerializationContext, bool bResetAlpha, const FString& FileNamePostfix) {
     UEnum* PixelFormatEnum = UTexture2D::GetPixelFormatEnum();

    check(PlatformData);
    check(PlatformData->Mips.Num());

    const EPixelFormat PixelFormat = PlatformData->PixelFormat;
    FTexture2DMipMap& FirstMipMap = PlatformData->Mips[0];
    const FString PixelFormatName = PixelFormatEnum->GetNameStringByValue((int64) PixelFormat);
    
    //Lock mipmap data and obtain pointer to compressed data
    const int32 NumSlices = PlatformData->GetNumSlices();
    const uint8* CompressedData = (const uint8*) FirstMipMap.BulkData.LockReadOnly();
    const int32 TextureWidth = FirstMipMap.SizeX;
    const int32 TextureHeight = FirstMipMap.SizeY;
    check(FirstMipMap.SizeZ == 1);

    //Write basic information about texture
    OutObject->SetNumberField(TEXT("TextureWidth"), TextureWidth);
    OutObject->SetNumberField(TEXT("TextureHeight"), TextureHeight);
    OutObject->SetNumberField(TEXT("NumSlices"), NumSlices);
    OutObject->SetStringField(TEXT("CookedPixelFormat"), PixelFormatName);

    TArray<uint8> CombinedDecompressedData;

    //When we are operating on one slice only, we can perform some optimizations to avoid unnecessary copying
    const int32 NumBytesPerSlice = FirstMipMap.BulkData.GetBulkDataSize() / NumSlices;
    const bool bHaveOnlyOneSlice = NumSlices == 1;
    
    //Extract every slice and stitch them into the single texture
    for (int i = 0; i < NumSlices; i++) {
        TArray<uint8> OutDecompressedData;
        FString OutErrorMessage;
        
        //Copy right into combined data array when we have one slice only, skip copying data altogether
        TArray<uint8>& ActualOutputArray = bHaveOnlyOneSlice ? CombinedDecompressedData : OutDecompressedData;
        const bool bSuccess = FTextureDecompressor::DecompressTextureData(PixelFormat, CompressedData, TextureWidth, TextureHeight, ActualOutputArray, &OutErrorMessage);

        //Make sure extraction was successful. Theoretically only failure reason would be unsupported format, but we should support most of the used formats
        checkf(bSuccess, TEXT("Failed to extract Texture %s (%dx%d, format %s): %s"), *Texture->GetPathName(), TextureWidth, TextureHeight, *PixelFormatName, *OutErrorMessage);

        //Avoid doing all of that if we have one slice only
        if (!bHaveOnlyOneSlice) {
            //Add slice to combined decompressed data array
            //Avoid using Append because it is too expensive, just add unitialized elements and then memcpy them
            const int32 DataOffsetInArray = CombinedDecompressedData.Num();
            CombinedDecompressedData.AddUninitialized(OutDecompressedData.Num());
            FPlatformMemory::Memcpy(&CombinedDecompressedData[DataOffsetInArray], OutDecompressedData.GetData(), OutDecompressedData.Num());
        }
        
        //Skip amount of bytes read per slice from compressed data buffer
        CompressedData += NumBytesPerSlice;
    }
    
    //Unlock mipmap data since we don't need it anymore
    FirstMipMap.BulkData.Unlock();

    if (bResetAlpha) {
        //Reset alpha if we have been requested to
        const int32 TotalPixelsWithSlices = TextureWidth * TextureHeight * NumSlices;
        ClearAlphaFromBGRA8Texture(CombinedDecompressedData.GetData(), TotalPixelsWithSlices);
    }

    //Save data in PNG format and store bytes in serialization context
    IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
    TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);

    //TextureHeight should be multiplied by amount of splices because we basically stack textures vertically by appending data to the end of buffer
    const int32 ActualTextureHeight = TextureHeight * NumSlices;
    check(ImageWrapper->SetRaw(CombinedDecompressedData.GetData(), CombinedDecompressedData.Num(), TextureWidth, ActualTextureHeight, ERGBFormat::BGRA, 8));
    const TArray64<uint8>& PNGResultData = ImageWrapper->GetCompressed();

    //Store data in serialization context
    SerializationContext.SaveAdditionalAssetFile(TEXT("png"), PNGResultData, FileNamePostfix);    
}

void UTextureAssetSerializer::SerializeTexture2D(UTexture2D* Texture2D, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer, FAssetSerializationContext& Context, const FString& FileNamePostfix) {

    //Serialize Texture2D specific fields
    OutObject->SetBoolField(TEXT("bGlobalForceMipLevelsToBeResident"), Texture2D->bGlobalForceMipLevelsToBeResident);
    OutObject->SetNumberField(TEXT("AddressX"), Texture2D->AddressX);
    OutObject->SetNumberField(TEXT("AddressY"), Texture2D->AddressY);

    //Serialize fields common to all UTexture objects
    SerializeTexture(Texture2D, OutObject, ObjectHierarchySerializer);

    //Serialize actual texture data
    SerializeTextureData(Texture2D, Texture2D->PlatformData, OutObject, Context, false, FileNamePostfix);
}

void UTextureAssetSerializer::SerializeTexture(UTexture* Texture, TSharedPtr<FJsonObject> OutObject, UObjectHierarchySerializer* ObjectHierarchySerializer) {
    //Skip serializing all AdjustXXX fields because they are applied to the image
    //during cooked and mipmap image we get after decompression already has them applied

    //Serialize properties that are relevant in runtime
    OutObject->SetNumberField(TEXT("LODBias"), Texture->LODBias);
    OutObject->SetNumberField(TEXT("NumCinematicMipLevels"), Texture->NumCinematicMipLevels);
    OutObject->SetNumberField(TEXT("CompressionSettings"), Texture->CompressionSettings);
    OutObject->SetNumberField(TEXT("Filter"), Texture->Filter);
    OutObject->SetNumberField(TEXT("LODGroup"), Texture->LODGroup);
    OutObject->SetBoolField(TEXT("SRGB"), Texture->SRGB);
    OutObject->SetBoolField(TEXT("NeverStream"), Texture->NeverStream);
    OutObject->SetBoolField(TEXT("bNoTiling"), Texture->bNoTiling);

    //Serialize AssetUserData set on texture object
    TArray<TSharedPtr<FJsonValue>> AssetUserDataArray;
    for (UAssetUserData* AssetUserData : *Texture->GetAssetUserDataArray()) {
        const int32 AssetDataObjectIndex = ObjectHierarchySerializer->SerializeObject(AssetUserData);
        AssetUserDataArray.Add(MakeShareable(new FJsonValueNumber(AssetDataObjectIndex)));
    }
    OutObject->SetArrayField(TEXT("AssetUserData"), AssetUserDataArray);
}

EAssetCategory UTextureAssetSerializer::GetAssetCategory() const {
    return EAssetCategory::EAC_Texture2D;
}
