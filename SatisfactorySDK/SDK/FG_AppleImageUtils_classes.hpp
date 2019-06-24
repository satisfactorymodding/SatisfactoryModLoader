#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_AppleImageUtils_structs.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Classes
//---------------------------------------------------------------------------

// Class AppleImageUtils.AppleImageUtilsBaseAsyncTaskBlueprintProxy
// 0x0060 (0x0088 - 0x0028)
class UAppleImageUtilsBaseAsyncTaskBlueprintProxy : public UObject
{
public:
	unsigned char                                      UnknownData00[0x8];                                       // 0x0028(0x0008) MISSED OFFSET
	struct FScriptMulticastDelegate                    OnSuccess;                                                // 0x0030(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	struct FScriptMulticastDelegate                    OnFailure;                                                // 0x0040(0x0010) (ZeroConstructor, InstancedReference, BlueprintAssignable)
	unsigned char                                      UnknownData01[0x10];                                      // 0x0050(0x0010) MISSED OFFSET
	struct FAppleImageUtilsImageConversionResult       ConversionResult;                                         // 0x0060(0x0020) (BlueprintVisible, BlueprintReadOnly)
	unsigned char                                      UnknownData02[0x8];                                       // 0x0080(0x0008) MISSED OFFSET

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class AppleImageUtils.AppleImageUtilsBaseAsyncTaskBlueprintProxy");
		return ptr;
	}


	class UAppleImageUtilsBaseAsyncTaskBlueprintProxy* CreateProxyObjectForConvertToTIFF(class UTexture* SourceImage, bool bWantColor, bool bUseGpu, float Scale, ETextureRotationDirection Rotate);
	class UAppleImageUtilsBaseAsyncTaskBlueprintProxy* CreateProxyObjectForConvertToPNG(class UTexture* SourceImage, bool bWantColor, bool bUseGpu, float Scale, ETextureRotationDirection Rotate);
	class UAppleImageUtilsBaseAsyncTaskBlueprintProxy* CreateProxyObjectForConvertToJPEG(class UTexture* SourceImage, int Quality, bool bWantColor, bool bUseGpu, float Scale, ETextureRotationDirection Rotate);
	class UAppleImageUtilsBaseAsyncTaskBlueprintProxy* CreateProxyObjectForConvertToHEIF(class UTexture* SourceImage, int Quality, bool bWantColor, bool bUseGpu, float Scale, ETextureRotationDirection Rotate);
};


// Class AppleImageUtils.AppleImageInterface
// 0x0000 (0x0028 - 0x0028)
class UAppleImageInterface : public UInterface
{
public:

	static UClass* StaticClass()
	{
		static auto ptr = UObject::FindClass("Class AppleImageUtils.AppleImageInterface");
		return ptr;
	}

};


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
