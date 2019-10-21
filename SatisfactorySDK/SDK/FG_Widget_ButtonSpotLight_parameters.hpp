#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ButtonSpotLight_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ButtonSpotLight.Widget_ButtonSpotLight_C.UpdateMousePosition
struct UWidget_ButtonSpotLight_C_UpdateMousePosition_Params
{
};

// Function Widget_ButtonSpotLight.Widget_ButtonSpotLight_C.OnMouseMove
struct UWidget_ButtonSpotLight_C_OnMouseMove_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ButtonSpotLight.Widget_ButtonSpotLight_C.PreConstruct
struct UWidget_ButtonSpotLight_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ButtonSpotLight.Widget_ButtonSpotLight_C.Construct
struct UWidget_ButtonSpotLight_C_Construct_Params
{
};

// Function Widget_ButtonSpotLight.Widget_ButtonSpotLight_C.OnMouseLeave
struct UWidget_ButtonSpotLight_C_OnMouseLeave_Params
{
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_ButtonSpotLight.Widget_ButtonSpotLight_C.OnMouseEnter
struct UWidget_ButtonSpotLight_C_OnMouseEnter_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_ButtonSpotLight.Widget_ButtonSpotLight_C.ExecuteUbergraph_Widget_ButtonSpotLight
struct UWidget_ButtonSpotLight_C_ExecuteUbergraph_Widget_ButtonSpotLight_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
