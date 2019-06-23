#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_PopupToggleSelect_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_PopupToggleSelect.Widget_PopupToggleSelect_C.SetOptionalTextElements
struct UWidget_PopupToggleSelect_C_SetOptionalTextElements_Params
{
	struct FText*                                      Title;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FText*                                      Desc;                                                     // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_PopupToggleSelect.Widget_PopupToggleSelect_C.GetShouldOkayBeEnabled
struct UWidget_PopupToggleSelect_C_GetShouldOkayBeEnabled_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_PopupToggleSelect.Widget_PopupToggleSelect_C.SetInstigatorAndInitialize
struct UWidget_PopupToggleSelect_C_SetInstigatorAndInitialize_Params
{
	class UObject**                                    Instigator;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PopupToggleSelect.Widget_PopupToggleSelect_C.OnChildSelected
struct UWidget_PopupToggleSelect_C_OnChildSelected_Params
{
	int                                                ChildIndex;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_PopupToggleSelect.Widget_PopupToggleSelect_C.NotifyPopupConfirmed
struct UWidget_PopupToggleSelect_C_NotifyPopupConfirmed_Params
{
};

// Function Widget_PopupToggleSelect.Widget_PopupToggleSelect_C.NotifyPopupCanceled
struct UWidget_PopupToggleSelect_C_NotifyPopupCanceled_Params
{
};

// Function Widget_PopupToggleSelect.Widget_PopupToggleSelect_C.ExecuteUbergraph_Widget_PopupToggleSelect
struct UWidget_PopupToggleSelect_C_ExecuteUbergraph_Widget_PopupToggleSelect_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
