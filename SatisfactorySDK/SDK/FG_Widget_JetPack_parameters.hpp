#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_JetPack_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_JetPack.Widget_JetPack_C.GetFuelText
struct UWidget_JetPack_C_GetFuelText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_JetPack.Widget_JetPack_C.GetJetPack
struct UWidget_JetPack_C_GetJetPack_Params
{
	class AEquip_JetPack_C*                            Jetpack;                                                  // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_JetPack.Widget_JetPack_C.GetFuelColor
struct UWidget_JetPack_C_GetFuelColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_JetPack.Widget_JetPack_C.GetFuelPct
struct UWidget_JetPack_C_GetFuelPct_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_JetPack.Widget_JetPack_C.Tick
struct UWidget_JetPack_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_JetPack.Widget_JetPack_C.ExecuteUbergraph_Widget_JetPack
struct UWidget_JetPack_C_ExecuteUbergraph_Widget_JetPack_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
