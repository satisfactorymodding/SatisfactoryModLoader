#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_ColorPicker_EditPreset_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_ColorPicker_EditPreset.Widget_ColorPicker_EditPreset_C.PreConstruct
struct UWidget_ColorPicker_EditPreset_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ColorPicker_EditPreset.Widget_ColorPicker_EditPreset_C.BndEvt__mEditPresetAccept_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
struct UWidget_ColorPicker_EditPreset_C_BndEvt__mEditPresetAccept_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params
{
};

// Function Widget_ColorPicker_EditPreset.Widget_ColorPicker_EditPreset_C.BndEvt__mEditPresetCanel_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature
struct UWidget_ColorPicker_EditPreset_C_BndEvt__mEditPresetCanel_K2Node_ComponentBoundEvent_1_OnClicked__DelegateSignature_Params
{
};

// Function Widget_ColorPicker_EditPreset.Widget_ColorPicker_EditPreset_C.OnPopupConfirm
struct UWidget_ColorPicker_EditPreset_C_OnPopupConfirm_Params
{
	bool                                               ConfirmClicked;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ColorPicker_EditPreset.Widget_ColorPicker_EditPreset_C.BndEvt__mPrimaryColorPicker_K2Node_ComponentBoundEvent_2_OnValueChanged__DelegateSignature
struct UWidget_ColorPicker_EditPreset_C_BndEvt__mPrimaryColorPicker_K2Node_ComponentBoundEvent_2_OnValueChanged__DelegateSignature_Params
{
};

// Function Widget_ColorPicker_EditPreset.Widget_ColorPicker_EditPreset_C.BndEvt__mSecondaryColorPicker_K2Node_ComponentBoundEvent_3_OnValueChanged__DelegateSignature
struct UWidget_ColorPicker_EditPreset_C_BndEvt__mSecondaryColorPicker_K2Node_ComponentBoundEvent_3_OnValueChanged__DelegateSignature_Params
{
};

// Function Widget_ColorPicker_EditPreset.Widget_ColorPicker_EditPreset_C.ExecuteUbergraph_Widget_ColorPicker_EditPreset
struct UWidget_ColorPicker_EditPreset_C_ExecuteUbergraph_Widget_ColorPicker_EditPreset_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_ColorPicker_EditPreset.Widget_ColorPicker_EditPreset_C.OnAccept__DelegateSignature
struct UWidget_ColorPicker_EditPreset_C_OnAccept__DelegateSignature_Params
{
	struct FLinearColor                                PrimaryColor;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                SecondaryColor;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
