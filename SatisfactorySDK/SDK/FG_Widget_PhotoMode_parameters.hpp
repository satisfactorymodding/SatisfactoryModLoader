#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PhotoMode_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_PhotoMode.Widget_PhotoMode_C.ToggleVisibility
struct UWidget_PhotoMode_C_ToggleVisibility_Params
{
};

// Function Widget_PhotoMode.Widget_PhotoMode_C.FadePhotoTakenText
struct UWidget_PhotoMode_C_FadePhotoTakenText_Params
{
	float                                              DeltaTime;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PhotoMode.Widget_PhotoMode_C.PhotoTaken
struct UWidget_PhotoMode_C_PhotoTaken_Params
{
};

// Function Widget_PhotoMode.Widget_PhotoMode_C.UpdateHiResMode
struct UWidget_PhotoMode_C_UpdateHiResMode_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_PhotoMode.Widget_PhotoMode_C.UpdateFOV
struct UWidget_PhotoMode_C_UpdateFOV_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_PhotoMode.Widget_PhotoMode_C.Construct
struct UWidget_PhotoMode_C_Construct_Params
{
};

// Function Widget_PhotoMode.Widget_PhotoMode_C.Tick
struct UWidget_PhotoMode_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PhotoMode.Widget_PhotoMode_C.ExecuteUbergraph_Widget_PhotoMode
struct UWidget_PhotoMode_C_ExecuteUbergraph_Widget_PhotoMode_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
