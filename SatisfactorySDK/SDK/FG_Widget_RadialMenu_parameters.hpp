#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_RadialMenu_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_RadialMenu.Widget_RadialMenu_C.Update Button Angles
struct UWidget_RadialMenu_C_Update_Button_Angles_Params
{
	float                                              MenuAngle;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_RadialMenu.Widget_RadialMenu_C.Set Angle
struct UWidget_RadialMenu_C_Set_Angle_Params
{
};

// Function Widget_RadialMenu.Widget_RadialMenu_C.Close Radial Menu
struct UWidget_RadialMenu_C_Close_Radial_Menu_Params
{
};

// Function Widget_RadialMenu.Widget_RadialMenu_C.Open Radial Menu
struct UWidget_RadialMenu_C_Open_Radial_Menu_Params
{
};

// Function Widget_RadialMenu.Widget_RadialMenu_C.Generate Radial Menu
struct UWidget_RadialMenu_C_Generate_Radial_Menu_Params
{
};

// Function Widget_RadialMenu.Widget_RadialMenu_C.Destruct
struct UWidget_RadialMenu_C_Destruct_Params
{
};

// Function Widget_RadialMenu.Widget_RadialMenu_C.Tick
struct UWidget_RadialMenu_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_RadialMenu.Widget_RadialMenu_C.Create Radial Menu
struct UWidget_RadialMenu_C_Create_Radial_Menu_Params
{
};

// Function Widget_RadialMenu.Widget_RadialMenu_C.ExecuteUbergraph_Widget_RadialMenu
struct UWidget_RadialMenu_C_ExecuteUbergraph_Widget_RadialMenu_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
