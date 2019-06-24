#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ColorPicker_Preview_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ColorPicker_Preview.Widget_ColorPicker_Preview_C.SetColors
struct UWidget_ColorPicker_Preview_C_SetColors_Params
{
	struct FLinearColor                                PrimaryColor;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                SecondaryColor;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ColorPicker_Preview.Widget_ColorPicker_Preview_C.SetTextures
struct UWidget_ColorPicker_Preview_C_SetTextures_Params
{
};

// Function Widget_ColorPicker_Preview.Widget_ColorPicker_Preview_C.PreConstruct
struct UWidget_ColorPicker_Preview_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ColorPicker_Preview.Widget_ColorPicker_Preview_C.ExecuteUbergraph_Widget_ColorPicker_Preview
struct UWidget_ColorPicker_Preview_C_ExecuteUbergraph_Widget_ColorPicker_Preview_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
