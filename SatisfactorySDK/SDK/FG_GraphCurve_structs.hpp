#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Basic.hpp"
#include "FG_CoreUObject_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Script Structs
//---------------------------------------------------------------------------

// UserDefinedStruct GraphCurve.GraphCurve
// 0x0024
struct FGraphCurve
{
	struct FLinearColor                                Color_10_60E36C364D08C282508165B980658169;                // 0x0000(0x0010) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	TArray<struct FVector2D>                           Points_11_7F825CE44C5C364A4E1F71B0D820C91E;               // 0x0010(0x0010) (Edit, BlueprintVisible, ZeroConstructor)
	float                                              OffsetY_14_0BB8215B4F827D9DCB6242B85AC85100;              // 0x0020(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
