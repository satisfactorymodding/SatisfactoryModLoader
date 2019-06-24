#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_ImageWriteQueue_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class ImageWriteQueue.ImageWriteBlueprintLibrary
// 0x0000 (0x0028 - 0x0028)
class UImageWriteBlueprintLibrary : public UBlueprintFunctionLibrary
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class ImageWriteQueue.ImageWriteBlueprintLibrary");
		return ptr;
	}


	void ExportToDisk(class UTexture* Texture, const class FString& Filename, const struct FImageWriteOptions& options);
};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
