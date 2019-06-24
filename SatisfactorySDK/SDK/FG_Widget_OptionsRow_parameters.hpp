#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_OptionsRow_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_OptionsRow.Widget_OptionsRow_C.OnMouseEnter
struct UWidget_OptionsRow_C_OnMouseEnter_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_OptionsRow.Widget_OptionsRow_C.OnMouseLeave
struct UWidget_OptionsRow_C_OnMouseLeave_Params
{
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_OptionsRow.Widget_OptionsRow_C.PreConstruct
struct UWidget_OptionsRow_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_OptionsRow.Widget_OptionsRow_C.BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature
struct UWidget_OptionsRow_C_BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_OptionsRow.Widget_OptionsRow_C.BndEvt__mButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature
struct UWidget_OptionsRow_C_BndEvt__mButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_OptionsRow.Widget_OptionsRow_C.ExecuteUbergraph_Widget_OptionsRow
struct UWidget_OptionsRow_C_ExecuteUbergraph_Widget_OptionsRow_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_OptionsRow.Widget_OptionsRow_C.OnClicked__DelegateSignature
struct UWidget_OptionsRow_C_OnClicked__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
