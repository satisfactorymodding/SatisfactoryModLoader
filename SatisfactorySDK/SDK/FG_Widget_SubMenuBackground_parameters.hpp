#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_SubMenuBackground_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_SubMenuBackground.Widget_SubMenuBackground_C.OnSpawnAnim
struct UWidget_SubMenuBackground_C_OnSpawnAnim_Params
{
	class UPanelWidget*                                OverwritePanelWidget;                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_SubMenuBackground.Widget_SubMenuBackground_C.Construct
struct UWidget_SubMenuBackground_C_Construct_Params
{
};

// Function Widget_SubMenuBackground.Widget_SubMenuBackground_C.PlayListSpawnAnim
struct UWidget_SubMenuBackground_C_PlayListSpawnAnim_Params
{
	class UPanelWidget*                                OverwritePanelWidget;                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_SubMenuBackground.Widget_SubMenuBackground_C.PreConstruct
struct UWidget_SubMenuBackground_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_SubMenuBackground.Widget_SubMenuBackground_C.OnListSpawnAnim
struct UWidget_SubMenuBackground_C_OnListSpawnAnim_Params
{
};

// Function Widget_SubMenuBackground.Widget_SubMenuBackground_C.PlayBackgroundSpawnAnim
struct UWidget_SubMenuBackground_C_PlayBackgroundSpawnAnim_Params
{
};

// Function Widget_SubMenuBackground.Widget_SubMenuBackground_C.ExecuteUbergraph_Widget_SubMenuBackground
struct UWidget_SubMenuBackground_C_ExecuteUbergraph_Widget_SubMenuBackground_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
