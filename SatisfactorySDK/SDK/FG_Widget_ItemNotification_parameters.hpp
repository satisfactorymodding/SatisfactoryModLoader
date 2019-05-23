#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ItemNotification_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ItemNotification.Widget_ItemNotification_C.GetNumItemsPickedUp
struct UWidget_ItemNotification_C_GetNumItemsPickedUp_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ItemNotification.Widget_ItemNotification_C.GetItemName
struct UWidget_ItemNotification_C_GetItemName_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ItemNotification.Widget_ItemNotification_C.GetNumItemsInInventory
struct UWidget_ItemNotification_C_GetNumItemsInInventory_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ItemNotification.Widget_ItemNotification_C.AddToNumItems
struct UWidget_ItemNotification_C_AddToNumItems_Params
{
	int                                                NumItems;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ItemNotification.Widget_ItemNotification_C.GetAddText
struct UWidget_ItemNotification_C_GetAddText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ItemNotification.Widget_ItemNotification_C.Construct
struct UWidget_ItemNotification_C_Construct_Params
{
};

// Function Widget_ItemNotification.Widget_ItemNotification_C.ExecuteUbergraph_Widget_ItemNotification
struct UWidget_ItemNotification_C_ExecuteUbergraph_Widget_ItemNotification_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
