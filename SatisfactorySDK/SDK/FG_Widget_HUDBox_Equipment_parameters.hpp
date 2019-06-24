#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_HUDBox_Equipment_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.SetEquipmentSlotText
struct UWidget_HUDBox_Equipment_C_SetEquipmentSlotText_Params
{
};

// Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.GetEquipmentSlotVisibility
struct UWidget_HUDBox_Equipment_C_GetEquipmentSlotVisibility_Params
{
};

// Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.SetContentWidgetClass
struct UWidget_HUDBox_Equipment_C_SetContentWidgetClass_Params
{
};

// Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.GetEquipmentInSlot
struct UWidget_HUDBox_Equipment_C_GetEquipmentInSlot_Params
{
	class AFGEquipment*                                equipment;                                                // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.UpdateTitle
struct UWidget_HUDBox_Equipment_C_UpdateTitle_Params
{
};

// Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.UpdateIcon
struct UWidget_HUDBox_Equipment_C_UpdateIcon_Params
{
};

// Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.GetEquipmentItemClass
struct UWidget_HUDBox_Equipment_C_GetEquipmentItemClass_Params
{
	class UClass*                                      Class;                                                    // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.Construct
struct UWidget_HUDBox_Equipment_C_Construct_Params
{
};

// Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.Tick
struct UWidget_HUDBox_Equipment_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.HideWidget
struct UWidget_HUDBox_Equipment_C_HideWidget_Params
{
};

// Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.Destruct
struct UWidget_HUDBox_Equipment_C_Destruct_Params
{
};

// Function Widget_HUDBox_Equipment.Widget_HUDBox_Equipment_C.ExecuteUbergraph_Widget_HUDBox_Equipment
struct UWidget_HUDBox_Equipment_C_ExecuteUbergraph_Widget_HUDBox_Equipment_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
