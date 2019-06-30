#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_CostSlotWrapper_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_CostSlotWrapper.Widget_CostSlotWrapper_C.SetIconBrush
struct UWidget_CostSlotWrapper_C_SetIconBrush_Params
{
	class UTexture*                                    IconTexture;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_CostSlotWrapper.Widget_CostSlotWrapper_C.GetProgressbarPercent
struct UWidget_CostSlotWrapper_C_GetProgressbarPercent_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_CostSlotWrapper.Widget_CostSlotWrapper_C.GetOrange
struct UWidget_CostSlotWrapper_C_GetOrange_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_CostSlotWrapper.Widget_CostSlotWrapper_C.SetTextboxFormating
struct UWidget_CostSlotWrapper_C_SetTextboxFormating_Params
{
	bool                                               HasItems;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_CostSlotWrapper.Widget_CostSlotWrapper_C.GetDarkGray
struct UWidget_CostSlotWrapper_C_GetDarkGray_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_CostSlotWrapper.Widget_CostSlotWrapper_C.SetPartsNumbers
struct UWidget_CostSlotWrapper_C_SetPartsNumbers_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_CostSlotWrapper.Widget_CostSlotWrapper_C.Setup CostIcon
struct UWidget_CostSlotWrapper_C_Setup_CostIcon_Params
{
	class UTexture*                                    IconTexture;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FItemAmount                                 ItemAmount;                                               // (BlueprintVisible, BlueprintReadOnly, Parm)
	class UFGInventoryComponent*                       CachedInventoryComponent;                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	int                                                SlotIdx;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                CurrentNumInSlot;                                         // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               SmallSlot;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               BigSlot;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ForceOrangeTextbox;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_CostSlotWrapper.Widget_CostSlotWrapper_C.Tick
struct UWidget_CostSlotWrapper_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_CostSlotWrapper.Widget_CostSlotWrapper_C.PreConstruct
struct UWidget_CostSlotWrapper_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_CostSlotWrapper.Widget_CostSlotWrapper_C.ExecuteUbergraph_Widget_CostSlotWrapper
struct UWidget_CostSlotWrapper_C_ExecuteUbergraph_Widget_CostSlotWrapper_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
