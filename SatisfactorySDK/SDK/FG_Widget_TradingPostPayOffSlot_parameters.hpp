#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TradingPostPayOffSlot_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.StopEmptyAnim
struct UWidget_TradingPostPayOffSlot_C_StopEmptyAnim_Params
{
};

// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.DropOntoInventorySlot
struct UWidget_TradingPostPayOffSlot_C_DropOntoInventorySlot_Params
{
	class UWidget_InventorySlot_C*                     InventorySlot;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               Result;                                                   // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetSlotBackgroundBrush
struct UWidget_TradingPostPayOffSlot_C_GetSlotBackgroundBrush_Params
{
	struct FSlateBrush                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetDarkGrayColor
struct UWidget_TradingPostPayOffSlot_C_GetDarkGrayColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetProgressbarPercent
struct UWidget_TradingPostPayOffSlot_C_GetProgressbarPercent_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.SetTextboxFormating
struct UWidget_TradingPostPayOffSlot_C_SetTextboxFormating_Params
{
};

// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetCustomTooltip
struct UWidget_TradingPostPayOffSlot_C_GetCustomTooltip_Params
{
	class UWidget*                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetPaidOffSlotVisibility
struct UWidget_TradingPostPayOffSlot_C_GetPaidOffSlotVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetProgressbarVisibility
struct UWidget_TradingPostPayOffSlot_C_GetProgressbarVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetPaidOffColorFeedback
struct UWidget_TradingPostPayOffSlot_C_GetPaidOffColorFeedback_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetPaidOffFeedbackImage
struct UWidget_TradingPostPayOffSlot_C_GetPaidOffFeedbackImage_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.OnDrop
struct UWidget_TradingPostPayOffSlot_C_OnDrop_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              PointerEvent;                                             // (BlueprintVisible, BlueprintReadOnly, Parm)
	class UDragDropOperation**                         Operation;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetItemQuotaText
struct UWidget_TradingPostPayOffSlot_C_GetItemQuotaText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetItemText
struct UWidget_TradingPostPayOffSlot_C_GetItemText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.GetItemImage
struct UWidget_TradingPostPayOffSlot_C_GetItemImage_Params
{
	struct FSlateBrush                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.Construct
struct UWidget_TradingPostPayOffSlot_C_Construct_Params
{
};

// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.OnSchematicPaidOff
struct UWidget_TradingPostPayOffSlot_C_OnSchematicPaidOff_Params
{
	class AFGSchematicManager*                         schematicManager;                                         // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.Destruct
struct UWidget_TradingPostPayOffSlot_C_Destruct_Params
{
};

// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.Tick
struct UWidget_TradingPostPayOffSlot_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.OnMouseEnter
struct UWidget_TradingPostPayOffSlot_C_OnMouseEnter_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_TradingPostPayOffSlot.Widget_TradingPostPayOffSlot_C.ExecuteUbergraph_Widget_TradingPostPayOffSlot
struct UWidget_TradingPostPayOffSlot_C_ExecuteUbergraph_Widget_TradingPostPayOffSlot_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
