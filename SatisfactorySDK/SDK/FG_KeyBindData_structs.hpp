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

// UserDefinedStruct KeyBindData.KeyBindData
// 0x0022
struct FKeyBindData
{
	struct FName                                       ActionName_4_C7B4F53E48A16B3F01376F97B2DA4885;            // 0x0000(0x0008) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	struct FText                                       DisplayName_5_0A86F675465E0C811D17A287BB986630;           // 0x0008(0x0028) (Edit, BlueprintVisible)
	bool                                               AxisMapping_7_F80A67E0493A9BB92D5041A364C12ACF;           // 0x0020(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	bool                                               PositiveAxisScale_10_3C123C154A1C495D35EE54B5CEA682C6;    // 0x0021(0x0001) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
