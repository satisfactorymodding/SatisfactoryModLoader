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

// UserDefinedStruct InventoryAddTimes.InventoryAddTimes
// 0x0019
struct FInventoryAddTimes
{
	class UClass*                                      ItemClass_2_7DB810DB420443F0B7D053A862489422;             // 0x0000(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              TimeStamp_5_CC0FCA014A6FADACF5A9FCB6FAACC871;             // 0x0008(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x000C(0x0004) MISSED OFFSET
	class UWidget_ItemNotification_C*                  Widget_8_5F8B5CA8468B3EE4884636828A86531D;                // 0x0010(0x0008) (Edit, BlueprintVisible, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               IsAnimatingOut_10_DBA94AC14B27887644CA6081B090B4F3;       // 0x0018(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
