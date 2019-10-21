#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_MAMResearchSlot_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.DropOntoInventorySlot
struct UWidget_MAMResearchSlot_C_DropOntoInventorySlot_Params
{
	class UWidget_InventorySlot_C*                     InventorySlot;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               Result;                                                   // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetCustomTooltip
struct UWidget_MAMResearchSlot_C_GetCustomTooltip_Params
{
	class UWidget*                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetPaidOffSlotVisibility
struct UWidget_MAMResearchSlot_C_GetPaidOffSlotVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetProgressbarVisibility
struct UWidget_MAMResearchSlot_C_GetProgressbarVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetPaidOffColorFeedback
struct UWidget_MAMResearchSlot_C_GetPaidOffColorFeedback_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetPaidOffFeedbackImage
struct UWidget_MAMResearchSlot_C_GetPaidOffFeedbackImage_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetProgressbarPercent
struct UWidget_MAMResearchSlot_C_GetProgressbarPercent_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.OnDrop
struct UWidget_MAMResearchSlot_C_OnDrop_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              PointerEvent;                                             // (BlueprintVisible, BlueprintReadOnly, Parm)
	class UDragDropOperation**                         Operation;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetItemQuotaText
struct UWidget_MAMResearchSlot_C_GetItemQuotaText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetItemText
struct UWidget_MAMResearchSlot_C_GetItemText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.GetItemImage
struct UWidget_MAMResearchSlot_C_GetItemImage_Params
{
	struct FSlateBrush                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.Tick
struct UWidget_MAMResearchSlot_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_MAMResearchSlot.Widget_MAMResearchSlot_C.ExecuteUbergraph_Widget_MAMResearchSlot
struct UWidget_MAMResearchSlot_C_ExecuteUbergraph_Widget_MAMResearchSlot_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
