#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_FilterButton_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_FilterButton.Widget_FilterButton_C.SetTitle
struct UWidget_FilterButton_C_SetTitle_Params
{
	struct FText                                       mName;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_FilterButton.Widget_FilterButton_C.PreConstruct
struct UWidget_FilterButton_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_FilterButton.Widget_FilterButton_C.BndEvt__mShowOnCompassCheckbox_K2Node_ComponentBoundEvent_0_OnCheckChanged__DelegateSignature
struct UWidget_FilterButton_C_BndEvt__mShowOnCompassCheckbox_K2Node_ComponentBoundEvent_0_OnCheckChanged__DelegateSignature_Params
{
	bool                                               IsChecked;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_FilterButton.Widget_FilterButton_C.BndEvt__mShowOnMapCheckbox_K2Node_ComponentBoundEvent_1_OnCheckChanged__DelegateSignature
struct UWidget_FilterButton_C_BndEvt__mShowOnMapCheckbox_K2Node_ComponentBoundEvent_1_OnCheckChanged__DelegateSignature_Params
{
	bool                                               IsChecked;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_FilterButton.Widget_FilterButton_C.BndEvt__Widget_FilterButton_Row_K2Node_ComponentBoundEvent_2_OnHovered__DelegateSignature
struct UWidget_FilterButton_C_BndEvt__Widget_FilterButton_Row_K2Node_ComponentBoundEvent_2_OnHovered__DelegateSignature_Params
{
};

// Function Widget_FilterButton.Widget_FilterButton_C.BndEvt__Widget_FilterButton_Row_K2Node_ComponentBoundEvent_3_OnUnhovered__DelegateSignature
struct UWidget_FilterButton_C_BndEvt__Widget_FilterButton_Row_K2Node_ComponentBoundEvent_3_OnUnhovered__DelegateSignature_Params
{
};

// Function Widget_FilterButton.Widget_FilterButton_C.Construct
struct UWidget_FilterButton_C_Construct_Params
{
};

// Function Widget_FilterButton.Widget_FilterButton_C.ExecuteUbergraph_Widget_FilterButton
struct UWidget_FilterButton_C_ExecuteUbergraph_Widget_FilterButton_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_FilterButton.Widget_FilterButton_C.mShowOnCompassChanged__DelegateSignature
struct UWidget_FilterButton_C_mShowOnCompassChanged__DelegateSignature_Params
{
	class UWidget_FilterButton_C*                      Instigator;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               ShowOnCompass;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_FilterButton.Widget_FilterButton_C.mShowOnMapChanged__DelegateSignature
struct UWidget_FilterButton_C_mShowOnMapChanged__DelegateSignature_Params
{
	class UWidget_FilterButton_C*                      Instigator;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               ShowOnMap;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_FilterButton.Widget_FilterButton_C.OnUnhovered__DelegateSignature
struct UWidget_FilterButton_C_OnUnhovered__DelegateSignature_Params
{
	class UWidget_FilterButton_C*                      Instigator;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_FilterButton.Widget_FilterButton_C.OnHovered__DelegateSignature
struct UWidget_FilterButton_C_OnHovered__DelegateSignature_Params
{
	class UWidget_FilterButton_C*                      Instigator;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
