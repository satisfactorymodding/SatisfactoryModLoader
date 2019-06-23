#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ColorPicker_Slot_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.UpdateColors
struct UWidget_ColorPicker_Slot_C_UpdateColors_Params
{
	struct FLinearColor                                PrimaryColor;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                SecondaryColor;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.SetIsSelected
struct UWidget_ColorPicker_Slot_C_SetIsSelected_Params
{
	bool                                               isSelected;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.PreConstruct
struct UWidget_ColorPicker_Slot_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature
struct UWidget_ColorPicker_Slot_C_BndEvt__mButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature
struct UWidget_ColorPicker_Slot_C_BndEvt__mButton_K2Node_ComponentBoundEvent_2_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.BndEvt__mButton_K2Node_ComponentBoundEvent_3_OnButtonHoverEvent__DelegateSignature
struct UWidget_ColorPicker_Slot_C_BndEvt__mButton_K2Node_ComponentBoundEvent_3_OnButtonHoverEvent__DelegateSignature_Params
{
};

// Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.BndEvt__mEditButton_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature
struct UWidget_ColorPicker_Slot_C_BndEvt__mEditButton_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature_Params
{
};

// Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.ExecuteUbergraph_Widget_ColorPicker_Slot
struct UWidget_ColorPicker_Slot_C_ExecuteUbergraph_Widget_ColorPicker_Slot_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.OnEditClicked__DelegateSignature
struct UWidget_ColorPicker_Slot_C_OnEditClicked__DelegateSignature_Params
{
	class UWidget_ColorPicker_Slot_C*                  Slot;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.OnUnhovered__DelegateSignature
struct UWidget_ColorPicker_Slot_C_OnUnhovered__DelegateSignature_Params
{
	class UWidget_ColorPicker_Slot_C*                  Slot;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.OnHovered__DelegateSignature
struct UWidget_ColorPicker_Slot_C_OnHovered__DelegateSignature_Params
{
	class UWidget_ColorPicker_Slot_C*                  Slot;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_ColorPicker_Slot.Widget_ColorPicker_Slot_C.OnClicked__DelegateSignature
struct UWidget_ColorPicker_Slot_C_OnClicked__DelegateSignature_Params
{
	class UWidget_ColorPicker_Slot_C*                  Slot;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
