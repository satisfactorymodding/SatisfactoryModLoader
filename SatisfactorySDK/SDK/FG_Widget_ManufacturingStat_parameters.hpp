#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ManufacturingStat_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.SetBrush
struct UWidget_ManufacturingStat_C_SetBrush_Params
{
};

// Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.SetIconColor
struct UWidget_ManufacturingStat_C_SetIconColor_Params
{
};

// Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.GetStatText
struct UWidget_ManufacturingStat_C_GetStatText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.PreConstruct
struct UWidget_ManufacturingStat_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.OnDragEnter
struct UWidget_ManufacturingStat_C_OnDragEnter_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              PointerEvent;                                             // (BlueprintVisible, BlueprintReadOnly, Parm)
	class UDragDropOperation**                         Operation;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.OnDragLeave
struct UWidget_ManufacturingStat_C_OnDragLeave_Params
{
	struct FPointerEvent*                              PointerEvent;                                             // (BlueprintVisible, BlueprintReadOnly, Parm)
	class UDragDropOperation**                         Operation;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.Construct
struct UWidget_ManufacturingStat_C_Construct_Params
{
};

// Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.UpdateStat
struct UWidget_ManufacturingStat_C_UpdateStat_Params
{
};

// Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.Destruct
struct UWidget_ManufacturingStat_C_Destruct_Params
{
};

// Function Widget_ManufacturingStat.Widget_ManufacturingStat_C.ExecuteUbergraph_Widget_ManufacturingStat
struct UWidget_ManufacturingStat_C_ExecuteUbergraph_Widget_ManufacturingStat_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
