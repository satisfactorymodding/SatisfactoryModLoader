#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ResourceExtractorUI_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.DropInventorySlotStack
struct UWidget_ResourceExtractorUI_C_DropInventorySlotStack_Params
{
	class UWidget_InventorySlot_C**                    InventorySlot;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               WasStackMoved;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.GetWarningVisibility
struct UWidget_ResourceExtractorUI_C_GetWarningVisibility_Params
{
	class AFGBuildableResourceExtractor*               buildableResourceExtractor;                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.UpdateOutputInfo
struct UWidget_ResourceExtractorUI_C_UpdateOutputInfo_Params
{
};

// Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.UpdateExtractorStats
struct UWidget_ResourceExtractorUI_C_UpdateExtractorStats_Params
{
};

// Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.UpdateExtractorProgress
struct UWidget_ResourceExtractorUI_C_UpdateExtractorProgress_Params
{
};

// Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.GetOverclockWidgetVisibility
struct UWidget_ResourceExtractorUI_C_GetOverclockWidgetVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.Construct
struct UWidget_ResourceExtractorUI_C_Construct_Params
{
};

// Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.Tick
struct UWidget_ResourceExtractorUI_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.BndEvt__Widget_StandbyButton_K2Node_ComponentBoundEvent_0_OnStandbyClicked__DelegateSignature
struct UWidget_ResourceExtractorUI_C_BndEvt__Widget_StandbyButton_K2Node_ComponentBoundEvent_0_OnStandbyClicked__DelegateSignature_Params
{
};

// Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.Init
struct UWidget_ResourceExtractorUI_C_Init_Params
{
};

// Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.BndEvt__Widget_Window_DarkMode_K2Node_ComponentBoundEvent_2_OnClose__DelegateSignature
struct UWidget_ResourceExtractorUI_C_BndEvt__Widget_Window_DarkMode_K2Node_ComponentBoundEvent_2_OnClose__DelegateSignature_Params
{
};

// Function Widget_ResourceExtractorUI.Widget_ResourceExtractorUI_C.ExecuteUbergraph_Widget_ResourceExtractorUI
struct UWidget_ResourceExtractorUI_C_ExecuteUbergraph_Widget_ResourceExtractorUI_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
