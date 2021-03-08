#pragma once
#include "CoreMinimal.h"
#include "PixelFormat.h"

class SML_API FTextureDecompressor {
public:
    /**
     * Decompresses texture data in provided pixel format into
     * uncompressed B8G8R8A8 source texture format data
     * Note that not all compression formats are supported and we currently have
     * no intention to support texture formats used outside of FactoryGame assets
     */
    static bool DecompressTextureData(EPixelFormat PixelFormat, const uint8* CompressedData, int32 TextureWidth, int32 TextureHeight, TArray<uint8>& OutDecompressedData, FString* OutErrorMessage = NULL);
};
