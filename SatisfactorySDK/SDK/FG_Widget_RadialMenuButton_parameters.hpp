#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_RadialMenuButton_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_RadialMenuButton.Widget_RadialMenuButton_C.Hover Lerp
struct UWidget_RadialMenuButton_C_Hover_Lerp_Params
{
	float                                              DeltaTime;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_RadialMenuButton.Widget_RadialMenuButton_C.Get Screen Position
struct UWidget_RadialMenuButton_C_Get_Screen_Position_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_RadialMenuButton.Widget_RadialMenuButton_C.Set Angle
struct UWidget_RadialMenuButton_C_Set_Angle_Params
{
};

// Function Widget_RadialMenuButton.Widget_RadialMenuButton_C.Construct
struct UWidget_RadialMenuButton_C_Construct_Params
{
};

// Function Widget_RadialMenuButton.Widget_RadialMenuButton_C.Set Icon Position
struct UWidget_RadialMenuButton_C_Set_Icon_Position_Params
{
};

// Function Widget_RadialMenuButton.Widget_RadialMenuButton_C.Create Style
struct UWidget_RadialMenuButton_C_Create_Style_Params
{
};

// Function Widget_RadialMenuButton.Widget_RadialMenuButton_C.Tick
struct UWidget_RadialMenuButton_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_RadialMenuButton.Widget_RadialMenuButton_C.ExecuteUbergraph_Widget_RadialMenuButton
struct UWidget_RadialMenuButton_C_ExecuteUbergraph_Widget_RadialMenuButton_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
