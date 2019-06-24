#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// UserDefinedStruct FBrightnessAdjustment.FBrightnessAdjustment
// 0x0008
struct FFBrightnessAdjustment
{
	float                                              LightIntensity_5_7DFA36F84BCB1C040E5D69B250CB0137;        // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              SkySphereDiscBrightness_6_E856AF074C7A0AFAA790FCA8730DAEF9;// 0x0004(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
