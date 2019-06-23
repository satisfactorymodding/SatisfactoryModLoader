#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Options_DropdownBox_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Options_DropdownBox.Widget_Options_DropdownBox_C.SetDropdownColor
struct UWidget_Options_DropdownBox_C_SetDropdownColor_Params
{
	struct FLinearColor                                Color;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Options_DropdownBox.Widget_Options_DropdownBox_C.IsValidIndex
struct UWidget_Options_DropdownBox_C_IsValidIndex_Params
{
	int                                                Index;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               Valid;                                                    // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Options_DropdownBox.Widget_Options_DropdownBox_C.BndEvt__mDropDownButton_K2Node_ComponentBoundEvent_172_OnButtonClickedEvent__DelegateSignature
struct UWidget_Options_DropdownBox_C_BndEvt__mDropDownButton_K2Node_ComponentBoundEvent_172_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_Options_DropdownBox.Widget_Options_DropdownBox_C.BndEvt__mDropdownBox_K2Node_ComponentBoundEvent_2_OnOpeningEvent__DelegateSignature
struct UWidget_Options_DropdownBox_C_BndEvt__mDropdownBox_K2Node_ComponentBoundEvent_2_OnOpeningEvent__DelegateSignature_Params
{
};

// Function Widget_Options_DropdownBox.Widget_Options_DropdownBox_C.BndEvt__mFakeButton_K2Node_ComponentBoundEvent_3_OnButtonHoverEvent__DelegateSignature
struct UWidget_Options_DropdownBox_C_BndEvt__mFakeButton_K2Node_ComponentBoundEvent_3_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_Options_DropdownBox.Widget_Options_DropdownBox_C.BndEvt__mDropdownBox_K2Node_ComponentBoundEvent_0_OnSelectionChangedEvent__DelegateSignature
struct UWidget_Options_DropdownBox_C_BndEvt__mDropdownBox_K2Node_ComponentBoundEvent_0_OnSelectionChangedEvent__DelegateSignature_Params
{
	class FString                                      SelectedItem;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
	TEnumAsByte<ESelectInfo>                           SelectionType;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Options_DropdownBox.Widget_Options_DropdownBox_C.PreConstruct
struct UWidget_Options_DropdownBox_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Options_DropdownBox.Widget_Options_DropdownBox_C.OnRowHovered
struct UWidget_Options_DropdownBox_C_OnRowHovered_Params
{
};

// Function Widget_Options_DropdownBox.Widget_Options_DropdownBox_C.OnRowUnhovered
struct UWidget_Options_DropdownBox_C_OnRowUnhovered_Params
{
};

// Function Widget_Options_DropdownBox.Widget_Options_DropdownBox_C.ExecuteUbergraph_Widget_Options_DropdownBox
struct UWidget_Options_DropdownBox_C_ExecuteUbergraph_Widget_Options_DropdownBox_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Options_DropdownBox.Widget_Options_DropdownBox_C.onSelectionChanged__DelegateSignature
struct UWidget_Options_DropdownBox_C_onSelectionChanged__DelegateSignature_Params
{
	class FString                                      SelectedOption;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
