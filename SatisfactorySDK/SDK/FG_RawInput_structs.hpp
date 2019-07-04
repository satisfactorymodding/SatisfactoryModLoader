#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"
#include "FG_InputCore_classes.hpp"
#include "FG_Engine_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// ScriptStruct RawInput.RegisteredDeviceInfo
// 0x0020
struct FRegisteredDeviceInfo
{
	int                                                Handle;                                                   // 0x0000(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	int                                                VendorID;                                                 // 0x0004(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	int                                                ProductId;                                                // 0x0008(0x0004) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x000C(0x0004) MISSED OFFSET
	class FString                                      DeviceName;                                               // 0x0010(0x0010) (BlueprintVisible, BlueprintReadOnly, ZeroConstructor)
};

// ScriptStruct RawInput.RawInputDeviceAxisProperties
// 0x0028
struct FRawInputDeviceAxisProperties
{
	unsigned char                                      bEnabled : 1;                                             // 0x0000(0x0001) (Edit)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0001(0x0007) MISSED OFFSET
	struct FKey                                        Key;                                                      // 0x0008(0x0018) (Edit)
	unsigned char                                      bInverted : 1;                                            // 0x0020(0x0001) (Edit)
	unsigned char                                      UnknownData01[0x3];                                       // 0x0021(0x0003) MISSED OFFSET
	float                                              Offset;                                                   // 0x0024(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
};

// ScriptStruct RawInput.RawInputDeviceButtonProperties
// 0x0020
struct FRawInputDeviceButtonProperties
{
	unsigned char                                      bEnabled : 1;                                             // 0x0000(0x0001) (Edit)
	unsigned char                                      UnknownData00[0x7];                                       // 0x0001(0x0007) MISSED OFFSET
	struct FKey                                        Key;                                                      // 0x0008(0x0018) (Edit)
};

// ScriptStruct RawInput.RawInputDeviceConfiguration
// 0x0040
struct FRawInputDeviceConfiguration
{
	class FString                                      VendorID;                                                 // 0x0000(0x0010) (Edit, ZeroConstructor)
	class FString                                      ProductId;                                                // 0x0010(0x0010) (Edit, ZeroConstructor)
	TArray<struct FRawInputDeviceAxisProperties>       AxisProperties;                                           // 0x0020(0x0010) (Edit, ZeroConstructor)
	TArray<struct FRawInputDeviceButtonProperties>     ButtonProperties;                                         // 0x0030(0x0010) (Edit, ZeroConstructor)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
