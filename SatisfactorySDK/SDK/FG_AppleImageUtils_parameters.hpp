#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_AppleImageUtils_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function AppleImageUtils.AppleImageUtilsBaseAsyncTaskBlueprintProxy.CreateProxyObjectForConvertToTIFF
struct UAppleImageUtilsBaseAsyncTaskBlueprintProxy_CreateProxyObjectForConvertToTIFF_Params
{
	class UTexture*                                    SourceImage;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bWantColor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bUseGpu;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Scale;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	ETextureRotationDirection                          Rotate;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	class UAppleImageUtilsBaseAsyncTaskBlueprintProxy* ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AppleImageUtils.AppleImageUtilsBaseAsyncTaskBlueprintProxy.CreateProxyObjectForConvertToPNG
struct UAppleImageUtilsBaseAsyncTaskBlueprintProxy_CreateProxyObjectForConvertToPNG_Params
{
	class UTexture*                                    SourceImage;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bWantColor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bUseGpu;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Scale;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	ETextureRotationDirection                          Rotate;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	class UAppleImageUtilsBaseAsyncTaskBlueprintProxy* ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AppleImageUtils.AppleImageUtilsBaseAsyncTaskBlueprintProxy.CreateProxyObjectForConvertToJPEG
struct UAppleImageUtilsBaseAsyncTaskBlueprintProxy_CreateProxyObjectForConvertToJPEG_Params
{
	class UTexture*                                    SourceImage;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                Quality;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bWantColor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bUseGpu;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Scale;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	ETextureRotationDirection                          Rotate;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	class UAppleImageUtilsBaseAsyncTaskBlueprintProxy* ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AppleImageUtils.AppleImageUtilsBaseAsyncTaskBlueprintProxy.CreateProxyObjectForConvertToHEIF
struct UAppleImageUtilsBaseAsyncTaskBlueprintProxy_CreateProxyObjectForConvertToHEIF_Params
{
	class UTexture*                                    SourceImage;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                Quality;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bWantColor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bUseGpu;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Scale;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	ETextureRotationDirection                          Rotate;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	class UAppleImageUtilsBaseAsyncTaskBlueprintProxy* ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
