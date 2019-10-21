#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PlayerHealthBar_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_PlayerHealthBar.Widget_PlayerHealthBar_C.GetHealthFillColor
struct UWidget_PlayerHealthBar_C_GetHealthFillColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_PlayerHealthBar.Widget_PlayerHealthBar_C.IsValidHealthComponent
struct UWidget_PlayerHealthBar_C_IsValidHealthComponent_Params
{
	bool                                               Valid;                                                    // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PlayerHealthBar.Widget_PlayerHealthBar_C.GetHealthbar
struct UWidget_PlayerHealthBar_C_GetHealthbar_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_PlayerHealthBar.Widget_PlayerHealthBar_C.GetProgressbarPercent
struct UWidget_PlayerHealthBar_C_GetProgressbarPercent_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_PlayerHealthBar.Widget_PlayerHealthBar_C.Construct
struct UWidget_PlayerHealthBar_C_Construct_Params
{
};

// Function Widget_PlayerHealthBar.Widget_PlayerHealthBar_C.Tick
struct UWidget_PlayerHealthBar_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PlayerHealthBar.Widget_PlayerHealthBar_C.ResetAnimGate
struct UWidget_PlayerHealthBar_C_ResetAnimGate_Params
{
};

// Function Widget_PlayerHealthBar.Widget_PlayerHealthBar_C.SetupHealthComponent
struct UWidget_PlayerHealthBar_C_SetupHealthComponent_Params
{
};

// Function Widget_PlayerHealthBar.Widget_PlayerHealthBar_C.ExecuteUbergraph_Widget_PlayerHealthBar
struct UWidget_PlayerHealthBar_C_ExecuteUbergraph_Widget_PlayerHealthBar_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
