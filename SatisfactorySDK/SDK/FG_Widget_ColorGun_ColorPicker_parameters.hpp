#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ColorGun_ColorPicker_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.CompressValue
struct UWidget_ColorGun_ColorPicker_C_CompressValue_Params
{
	float                                              Value;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              MinValue;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              Out_Value;                                                // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.ConvertColorToPreviewColor
struct UWidget_ColorGun_ColorPicker_C_ConvertColorToPreviewColor_Params
{
	struct FLinearColor                                InputColor;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              MinValue;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                OutputColor;                                              // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.UpdatePreview
struct UWidget_ColorGun_ColorPicker_C_UpdatePreview_Params
{
};

// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.SetupSlots
struct UWidget_ColorGun_ColorPicker_C_SetupSlots_Params
{
};

// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.Construct
struct UWidget_ColorGun_ColorPicker_C_Construct_Params
{
};

// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.OnSlotClicked
struct UWidget_ColorGun_ColorPicker_C_OnSlotClicked_Params
{
	class UWidget_ColorPicker_Slot_C*                  Slot;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.OnSlotHovered
struct UWidget_ColorGun_ColorPicker_C_OnSlotHovered_Params
{
	class UWidget_ColorPicker_Slot_C*                  Slot;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.OnSlotUnhovered
struct UWidget_ColorGun_ColorPicker_C_OnSlotUnhovered_Params
{
	class UWidget_ColorPicker_Slot_C*                  Slot;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
struct UWidget_ColorGun_ColorPicker_C_BndEvt__Widget_StandardButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params
{
};

// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.BndEvt__mCancel_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature
struct UWidget_ColorGun_ColorPicker_C_BndEvt__mCancel_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature_Params
{
};

// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.OnSlotEditClicked
struct UWidget_ColorGun_ColorPicker_C_OnSlotEditClicked_Params
{
	class UWidget_ColorPicker_Slot_C*                  Slot;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.OnUpdatePreset
struct UWidget_ColorGun_ColorPicker_C_OnUpdatePreset_Params
{
	struct FLinearColor                                PrimaryColor;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                SecondaryColor;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.ExecuteUbergraph_Widget_ColorGun_ColorPicker
struct UWidget_ColorGun_ColorPicker_C_ExecuteUbergraph_Widget_ColorGun_ColorPicker_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.OnCancel__DelegateSignature
struct UWidget_ColorGun_ColorPicker_C_OnCancel__DelegateSignature_Params
{
};

// Function Widget_ColorGun_ColorPicker.Widget_ColorGun_ColorPicker_C.OnAccept__DelegateSignature
struct UWidget_ColorGun_ColorPicker_C_OnAccept__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
