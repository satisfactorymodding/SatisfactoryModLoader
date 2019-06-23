#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_InventoryAddNotification_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_InventoryAddNotification.Widget_InventoryAddNotification_C.BindOnInventoryAddAndCacheChar
struct UWidget_InventoryAddNotification_C_BindOnInventoryAddAndCacheChar_Params
{
};

// Function Widget_InventoryAddNotification.Widget_InventoryAddNotification_C.UnbindOnInventoryAdd
struct UWidget_InventoryAddNotification_C_UnbindOnInventoryAdd_Params
{
	class AFGCharacterPlayer*                          FromCharacter;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_InventoryAddNotification.Widget_InventoryAddNotification_C.IsInventoryOpen
struct UWidget_InventoryAddNotification_C_IsInventoryOpen_Params
{
	bool                                               IsOpen;                                                   // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_InventoryAddNotification.Widget_InventoryAddNotification_C.OnItemADded
struct UWidget_InventoryAddNotification_C_OnItemADded_Params
{
	class UClass*                                      ItemClass;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	int                                                numAdded;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_InventoryAddNotification.Widget_InventoryAddNotification_C.Construct
struct UWidget_InventoryAddNotification_C_Construct_Params
{
};

// Function Widget_InventoryAddNotification.Widget_InventoryAddNotification_C.Destruct
struct UWidget_InventoryAddNotification_C_Destruct_Params
{
};

// Function Widget_InventoryAddNotification.Widget_InventoryAddNotification_C.Tick
struct UWidget_InventoryAddNotification_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_InventoryAddNotification.Widget_InventoryAddNotification_C.ExecuteUbergraph_Widget_InventoryAddNotification
struct UWidget_InventoryAddNotification_C_ExecuteUbergraph_Widget_InventoryAddNotification_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
