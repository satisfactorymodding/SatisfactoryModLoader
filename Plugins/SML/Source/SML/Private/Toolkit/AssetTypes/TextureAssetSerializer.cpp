#include "Toolkit/AssetTypes/TextureAssetSerializer.h"
#include "Toolkit/AssetTypes/AssetHelper.h"
#include "IImageWrapperModule.h"
#include "Modules/ModuleManager.h"
#include "Engine/Texture2D.h"
#include "Toolkit/AssetTypes/TextureDecompressor.h"
#include "IImageWrapper.h"
#include "Dom/JsonObject.h"
#include "Toolkit/ObjectHierarchySerializer.h"
#include "Toolkit/AssetDumping/AssetTypeSerializerMacros.h"
#include "Toolkit/AssetDumping/SerializationContext.h"

void UTextureAssetSerializer::SerializeAsset(TSharedRef<FSerializationContext> Context) const {
    BEGIN_ASSET_SERIALIZATION(UTexture2D)
    SerializeTexture2D(Asset, Data, Context, TEXT(""));
    END_ASSET_SERIALIZATION
}

void ClearAlphaFromBGRA8Texture(void* TextureData, int32 NumPixels) {
    FColor* TextureDataColor = static_cast<FColor*>(TextureData);

    for (int i = 0; i < NumPixels; i++) {
        FColor* CurrentColor = TextureDataColor++;
        CurrentColor->A = 255;
    }
}

void UTextureAssetSerializer::SerializeTextureData(const FString& ContextString, FTexturePlatformData* PlatformData, TSharedPtr<FJsonObject> Data, TSharedRef<FSerializationContext> Context, bool bResetAlpha, const FString& FileNamePostfix) {
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
    Data->SetNumberField(TEXT("TextureWidth"), TextureWidth);
    Data->SetNumberField(TEXT("TextureHeight"), TextureHeight);
    Data->SetNumberField(TEXT("NumSlices"), NumSlices);
    Data->SetStringField(TEXT("CookedPixelFormat"), PixelFormatName);

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
        checkf(bSuccess, TEXT("Failed to extract Texture %s (%dx%d, format %s): %s"), *ContextString, TextureWidth, TextureHeight, *PixelFormatName, *OutErrorMessage);

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
    const FString ImageFilename = Context->GetDumpFilePath(FileNamePostfix, TEXT("png"));
    check(FFileHelper::SaveArrayToFile(PNGResultData, *ImageFilename));
}

void UTextureAssetSerializer::SerializeTexture2D(UTexture2D* Asset, TSharedPtr<FJsonObject> Data, TSharedRef<FSerializationContext> Context, const FString& Postfix) {
    UObjectHierarchySerializer* ObjectSerializer = Context->GetObjectSerializer();
    SERIALIZE_ASSET_OBJECT
    SerializeTextureData(Asset->GetPathName(), Asset->PlatformData, Data, Context, false, Postfix);   
}

FName UTextureAssetSerializer::GetAssetClass() const {
    return UTexture2D::StaticClass()->GetFName();
}
