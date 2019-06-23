#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ManufacturingIOSlot_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.ConstructFromManufacturingWidget
struct UWidget_ManufacturingIOSlot_C_ConstructFromManufacturingWidget_Params
{
	class UWidget_Manufacturing_C*                     WidgetManufacturing;                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.UpdateOutputTooltip
struct UWidget_ManufacturingIOSlot_C_UpdateOutputTooltip_Params
{
};

// Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.GetDividerTopVisibility
struct UWidget_ManufacturingIOSlot_C_GetDividerTopVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.GetDividerVisibility
struct UWidget_ManufacturingIOSlot_C_GetDividerVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.GetInputInfoVisibility
struct UWidget_ManufacturingIOSlot_C_GetInputInfoVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.GetNumPerSecond
struct UWidget_ManufacturingIOSlot_C_GetNumPerSecond_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.GetOutputSlotVisibility
struct UWidget_ManufacturingIOSlot_C_GetOutputSlotVisibility_Params
{
	ESlateVisibility                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.GetItemNum
struct UWidget_ManufacturingIOSlot_C_GetItemNum_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.GetItemAmount
struct UWidget_ManufacturingIOSlot_C_GetItemAmount_Params
{
	struct FItemAmount                                 ItemAmount;                                               // (Parm, OutParm)
};

// Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.GetItemName
struct UWidget_ManufacturingIOSlot_C_GetItemName_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.Construct
struct UWidget_ManufacturingIOSlot_C_Construct_Params
{
};

// Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.Set CostSlot
struct UWidget_ManufacturingIOSlot_C_Set_CostSlot_Params
{
	int                                                SlotIdx;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ManufacturingIOSlot.Widget_ManufacturingIOSlot_C.ExecuteUbergraph_Widget_ManufacturingIOSlot
struct UWidget_ManufacturingIOSlot_C_ExecuteUbergraph_Widget_ManufacturingIOSlot_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
