#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_EmoteMenu_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_EmoteMenu.Widget_EmoteMenu_C.Construct
struct UWidget_EmoteMenu_C_Construct_Params
{
};

// Function Widget_EmoteMenu.Widget_EmoteMenu_C.Destruct
struct UWidget_EmoteMenu_C_Destruct_Params
{
};

// Function Widget_EmoteMenu.Widget_EmoteMenu_C.Tick
struct UWidget_EmoteMenu_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_EmoteMenu.Widget_EmoteMenu_C.ExecuteUbergraph_Widget_EmoteMenu
struct UWidget_EmoteMenu_C_ExecuteUbergraph_Widget_EmoteMenu_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_EmoteMenu.Widget_EmoteMenu_C.ShowEmote__DelegateSignature
struct UWidget_EmoteMenu_C_ShowEmote__DelegateSignature_Params
{
	int                                                EmoteIndex;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
