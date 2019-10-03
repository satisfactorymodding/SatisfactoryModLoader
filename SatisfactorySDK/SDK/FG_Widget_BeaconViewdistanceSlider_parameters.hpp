#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_BeaconViewdistanceSlider_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_BeaconViewdistanceSlider.Widget_BeaconViewdistanceSlider_C.GetTextFromIndex
struct UWidget_BeaconViewdistanceSlider_C_GetTextFromIndex_Params
{
	int                                                Index;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UTextBlock*                                  Text;                                                     // (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               Success;                                                  // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_BeaconViewdistanceSlider.Widget_BeaconViewdistanceSlider_C.OnMouseMove
struct UWidget_BeaconViewdistanceSlider_C_OnMouseMove_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FEventReply                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_BeaconViewdistanceSlider.Widget_BeaconViewdistanceSlider_C.GetButtonFromIndex
struct UWidget_BeaconViewdistanceSlider_C_GetButtonFromIndex_Params
{
	int                                                Index;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UButton*                                     Button;                                                   // (Parm, OutParm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               Success;                                                  // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_BeaconViewdistanceSlider.Widget_BeaconViewdistanceSlider_C.SetButtonStyle
struct UWidget_BeaconViewdistanceSlider_C_SetButtonStyle_Params
{
	class UButton*                                     Button;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               selected;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               Hovered;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_BeaconViewdistanceSlider.Widget_BeaconViewdistanceSlider_C.OnMouseLeave
struct UWidget_BeaconViewdistanceSlider_C_OnMouseLeave_Params
{
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_BeaconViewdistanceSlider.Widget_BeaconViewdistanceSlider_C.Construct
struct UWidget_BeaconViewdistanceSlider_C_Construct_Params
{
};

// Function Widget_BeaconViewdistanceSlider.Widget_BeaconViewdistanceSlider_C.OnButtonClicked
struct UWidget_BeaconViewdistanceSlider_C_OnButtonClicked_Params
{
};

// Function Widget_BeaconViewdistanceSlider.Widget_BeaconViewdistanceSlider_C.MyMemesWillGoOn
struct UWidget_BeaconViewdistanceSlider_C_MyMemesWillGoOn_Params
{
};

// Function Widget_BeaconViewdistanceSlider.Widget_BeaconViewdistanceSlider_C.PreConstruct
struct UWidget_BeaconViewdistanceSlider_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_BeaconViewdistanceSlider.Widget_BeaconViewdistanceSlider_C.UpdateSelectedLevel
struct UWidget_BeaconViewdistanceSlider_C_UpdateSelectedLevel_Params
{
};

// Function Widget_BeaconViewdistanceSlider.Widget_BeaconViewdistanceSlider_C.BndEvt__Widget_FilterButton_Row_K2Node_ComponentBoundEvent_0_OnHovered__DelegateSignature
struct UWidget_BeaconViewdistanceSlider_C_BndEvt__Widget_FilterButton_Row_K2Node_ComponentBoundEvent_0_OnHovered__DelegateSignature_Params
{
};

// Function Widget_BeaconViewdistanceSlider.Widget_BeaconViewdistanceSlider_C.BndEvt__Widget_FilterButton_Row_K2Node_ComponentBoundEvent_1_OnUnhovered__DelegateSignature
struct UWidget_BeaconViewdistanceSlider_C_BndEvt__Widget_FilterButton_Row_K2Node_ComponentBoundEvent_1_OnUnhovered__DelegateSignature_Params
{
};

// Function Widget_BeaconViewdistanceSlider.Widget_BeaconViewdistanceSlider_C.ExecuteUbergraph_Widget_BeaconViewdistanceSlider
struct UWidget_BeaconViewdistanceSlider_C_ExecuteUbergraph_Widget_BeaconViewdistanceSlider_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_BeaconViewdistanceSlider.Widget_BeaconViewdistanceSlider_C.OnViewDistanceUnhovered__DelegateSignature
struct UWidget_BeaconViewdistanceSlider_C_OnViewDistanceUnhovered__DelegateSignature_Params
{
	class UWidget_BeaconViewdistanceSlider_C*          Instigator;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_BeaconViewdistanceSlider.Widget_BeaconViewdistanceSlider_C.OnViewDistanceHovered__DelegateSignature
struct UWidget_BeaconViewdistanceSlider_C_OnViewDistanceHovered__DelegateSignature_Params
{
	class UWidget_BeaconViewdistanceSlider_C*          Instigator;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	ECompassViewDistance                               viewDistance;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_BeaconViewdistanceSlider.Widget_BeaconViewdistanceSlider_C.OnUnhovered__DelegateSignature
struct UWidget_BeaconViewdistanceSlider_C_OnUnhovered__DelegateSignature_Params
{
	class UWidget_BeaconViewdistanceSlider_C*          Instigator;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_BeaconViewdistanceSlider.Widget_BeaconViewdistanceSlider_C.OnHovered__DelegateSignature
struct UWidget_BeaconViewdistanceSlider_C_OnHovered__DelegateSignature_Params
{
	class UWidget_BeaconViewdistanceSlider_C*          Instigator;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_BeaconViewdistanceSlider.Widget_BeaconViewdistanceSlider_C.OnViewDistanceChanged__DelegateSignature
struct UWidget_BeaconViewdistanceSlider_C_OnViewDistanceChanged__DelegateSignature_Params
{
	class UWidget_BeaconViewdistanceSlider_C*          Instigator;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	ECompassViewDistance                               NewViewDistance;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
