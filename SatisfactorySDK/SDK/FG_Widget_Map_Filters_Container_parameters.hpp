#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Map_Filters_Container_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Map_Filters_Container.Widget_Map_Filters_Container_C.AddChildToBeacons
struct UWidget_Map_Filters_Container_C_AddChildToBeacons_Params
{
	class UWidget*                                     Content;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Map_Filters_Container.Widget_Map_Filters_Container_C.AddChildToFilters
struct UWidget_Map_Filters_Container_C_AddChildToFilters_Params
{
	class UWidget*                                     Content;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Map_Filters_Container.Widget_Map_Filters_Container_C.Destruct
struct UWidget_Map_Filters_Container_C_Destruct_Params
{
};

// Function Widget_Map_Filters_Container.Widget_Map_Filters_Container_C.Construct
struct UWidget_Map_Filters_Container_C_Construct_Params
{
};

// Function Widget_Map_Filters_Container.Widget_Map_Filters_Container_C.BndEvt__Widget_InputBox_K2Node_ComponentBoundEvent_1_OnTextChanged__DelegateSignature
struct UWidget_Map_Filters_Container_C_BndEvt__Widget_InputBox_K2Node_ComponentBoundEvent_1_OnTextChanged__DelegateSignature_Params
{
	struct FText                                       Text;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_Map_Filters_Container.Widget_Map_Filters_Container_C.BndEvt__Widget_InputBox_K2Node_ComponentBoundEvent_2_OnClearTextClicked__DelegateSignature
struct UWidget_Map_Filters_Container_C_BndEvt__Widget_InputBox_K2Node_ComponentBoundEvent_2_OnClearTextClicked__DelegateSignature_Params
{
};

// Function Widget_Map_Filters_Container.Widget_Map_Filters_Container_C.BndEvt__Widget_InputBox_K2Node_ComponentBoundEvent_3_OnTextComitted__DelegateSignature
struct UWidget_Map_Filters_Container_C_BndEvt__Widget_InputBox_K2Node_ComponentBoundEvent_3_OnTextComitted__DelegateSignature_Params
{
	struct FText                                       Text;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
	TEnumAsByte<ETextCommit>                           CommitMethod;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Map_Filters_Container.Widget_Map_Filters_Container_C.ExecuteUbergraph_Widget_Map_Filters_Container
struct UWidget_Map_Filters_Container_C_ExecuteUbergraph_Widget_Map_Filters_Container_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Map_Filters_Container.Widget_Map_Filters_Container_C.OnClearSearchResults__DelegateSignature
struct UWidget_Map_Filters_Container_C_OnClearSearchResults__DelegateSignature_Params
{
};

// Function Widget_Map_Filters_Container.Widget_Map_Filters_Container_C.OnBeaconSearchChanged__DelegateSignature
struct UWidget_Map_Filters_Container_C_OnBeaconSearchChanged__DelegateSignature_Params
{
	struct FText                                       Text;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
