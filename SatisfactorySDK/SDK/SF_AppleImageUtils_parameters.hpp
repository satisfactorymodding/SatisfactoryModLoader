#pragma once

// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_AppleImageUtils_classes.hpp"

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
	class UAppleImageUtilsBaseAsyncTaskBlueprintProxy* ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AppleImageUtils.AppleImageUtilsBaseAsyncTaskBlueprintProxy.CreateProxyObjectForConvertToPNG
struct UAppleImageUtilsBaseAsyncTaskBlueprintProxy_CreateProxyObjectForConvertToPNG_Params
{
	class UTexture*                                    SourceImage;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bWantColor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bUseGpu;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UAppleImageUtilsBaseAsyncTaskBlueprintProxy* ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AppleImageUtils.AppleImageUtilsBaseAsyncTaskBlueprintProxy.CreateProxyObjectForConvertToJPEG
struct UAppleImageUtilsBaseAsyncTaskBlueprintProxy_CreateProxyObjectForConvertToJPEG_Params
{
	class UTexture*                                    SourceImage;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                Quality;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bWantColor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bUseGpu;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UAppleImageUtilsBaseAsyncTaskBlueprintProxy* ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AppleImageUtils.AppleImageUtilsBaseAsyncTaskBlueprintProxy.CreateProxyObjectForConvertToHEIF
struct UAppleImageUtilsBaseAsyncTaskBlueprintProxy_CreateProxyObjectForConvertToHEIF_Params
{
	class UTexture*                                    SourceImage;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                Quality;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bWantColor;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bUseGpu;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class UAppleImageUtilsBaseAsyncTaskBlueprintProxy* ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
