#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_Overclock_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_Overclock.Widget_Overclock_C.UpdateDropArea
struct UWidget_Overclock_C_UpdateDropArea_Params
{
	class UWidget_CostSlotWrapper_C*                   NewActiveCostslot;                                        // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Overclock.Widget_Overclock_C.SetPercentText
struct UWidget_Overclock_C_SetPercentText_Params
{
};

// Function Widget_Overclock.Widget_Overclock_C.CheckIsOverclockUnlocked
struct UWidget_Overclock_C_CheckIsOverclockUnlocked_Params
{
};

// Function Widget_Overclock.Widget_Overclock_C.SetCrystalSlotUsable
struct UWidget_Overclock_C_SetCrystalSlotUsable_Params
{
	int                                                SlotIndex;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UWidget_CostSlotWrapper_C*                   CostSlot;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_Overclock.Widget_Overclock_C.IsCrystalSlotEnabled
struct UWidget_Overclock_C_IsCrystalSlotEnabled_Params
{
	int                                                SlotIndex;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	bool                                               IsEnabled;                                                // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Overclock.Widget_Overclock_C.InitCostSlots
struct UWidget_Overclock_C_InitCostSlots_Params
{
	int                                                idx;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UWidget_CostSlotWrapper_C*                   CostSlot;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool                                               IsValid;                                                  // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Overclock.Widget_Overclock_C.SetActiveProgressbars
struct UWidget_Overclock_C_SetActiveProgressbars_Params
{
};

// Function Widget_Overclock.Widget_Overclock_C.GetClampedSliderValue
struct UWidget_Overclock_C_GetClampedSliderValue_Params
{
	float                                              ClampedOvercklock;                                        // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Overclock.Widget_Overclock_C.ScaleToOverclock
struct UWidget_Overclock_C_ScaleToOverclock_Params
{
	float                                              Normalized_Overclock;                                     // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              Scaled_Overclock;                                         // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Overclock.Widget_Overclock_C.NormalizeOverclock
struct UWidget_Overclock_C_NormalizeOverclock_Params
{
	float                                              ScaledOverclock;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              NormalizedOverclock;                                      // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Overclock.Widget_Overclock_C.GetPercentText
struct UWidget_Overclock_C_GetPercentText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_Overclock.Widget_Overclock_C.GetMAXColor
struct UWidget_Overclock_C_GetMAXColor_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_Overclock.Widget_Overclock_C.Get200%Color
struct UWidget_Overclock_C_Get200_Color_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_Overclock.Widget_Overclock_C.Get150%Color
struct UWidget_Overclock_C_Get150_Color_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_Overclock.Widget_Overclock_C.Get100%Color
struct UWidget_Overclock_C_Get100_Color_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_Overclock.Widget_Overclock_C.Get0%Color
struct UWidget_Overclock_C_Get0_Color_Params
{
	struct FSlateColor                                 ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Widget_Overclock.Widget_Overclock_C.SetBarValue
struct UWidget_Overclock_C_SetBarValue_Params
{
};

// Function Widget_Overclock.Widget_Overclock_C.Construct
struct UWidget_Overclock_C_Construct_Params
{
};

// Function Widget_Overclock.Widget_Overclock_C.SetOvercklockAmountWithKnob
struct UWidget_Overclock_C_SetOvercklockAmountWithKnob_Params
{
	float                                              Value;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Overclock.Widget_Overclock_C.SetOverclockOnServer
struct UWidget_Overclock_C_SetOverclockOnServer_Params
{
};

// Function Widget_Overclock.Widget_Overclock_C.Tick
struct UWidget_Overclock_C_Tick_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	float*                                             InDeltaTime;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Overclock.Widget_Overclock_C.SetupCostslots
struct UWidget_Overclock_C_SetupCostslots_Params
{
};

// Function Widget_Overclock.Widget_Overclock_C.BndEvt__Slider_0_K2Node_ComponentBoundEvent_1_OnFloatValueChangedEvent__DelegateSignature
struct UWidget_Overclock_C_BndEvt__Slider_0_K2Node_ComponentBoundEvent_1_OnFloatValueChangedEvent__DelegateSignature_Params
{
	float                                              Value;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Overclock.Widget_Overclock_C.BndEvt__Slider_0_K2Node_ComponentBoundEvent_2_OnMouseCaptureEndEvent__DelegateSignature
struct UWidget_Overclock_C_BndEvt__Slider_0_K2Node_ComponentBoundEvent_2_OnMouseCaptureEndEvent__DelegateSignature_Params
{
};

// Function Widget_Overclock.Widget_Overclock_C.BndEvt__Slider_0_K2Node_ComponentBoundEvent_3_OnControllerCaptureEndEvent__DelegateSignature
struct UWidget_Overclock_C_BndEvt__Slider_0_K2Node_ComponentBoundEvent_3_OnControllerCaptureEndEvent__DelegateSignature_Params
{
};

// Function Widget_Overclock.Widget_Overclock_C.BndEvt__PercentText_K2Node_ComponentBoundEvent_4_OnEditableTextChangedEvent__DelegateSignature
struct UWidget_Overclock_C_BndEvt__PercentText_K2Node_ComponentBoundEvent_4_OnEditableTextChangedEvent__DelegateSignature_Params
{
	struct FText                                       Text;                                                     // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_Overclock.Widget_Overclock_C.BndEvt__PercentText_K2Node_ComponentBoundEvent_5_OnEditableTextCommittedEvent__DelegateSignature
struct UWidget_Overclock_C_BndEvt__PercentText_K2Node_ComponentBoundEvent_5_OnEditableTextCommittedEvent__DelegateSignature_Params
{
	struct FText                                       Text;                                                     // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	TEnumAsByte<ETextCommit>                           CommitMethod;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Overclock.Widget_Overclock_C.OnPercentageTextConfirmed
struct UWidget_Overclock_C_OnPercentageTextConfirmed_Params
{
	float                                              Value;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Overclock.Widget_Overclock_C.OnMouseEnter
struct UWidget_Overclock_C_OnMouseEnter_Params
{
	struct FGeometry*                                  MyGeometry;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, IsPlainOldData)
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_Overclock.Widget_Overclock_C.OnMouseLeave
struct UWidget_Overclock_C_OnMouseLeave_Params
{
	struct FPointerEvent*                              MouseEvent;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Widget_Overclock.Widget_Overclock_C.BndEvt__MainSlider_K2Node_ComponentBoundEvent_0_OnMouseCaptureBeginEvent__DelegateSignature
struct UWidget_Overclock_C_BndEvt__MainSlider_K2Node_ComponentBoundEvent_0_OnMouseCaptureBeginEvent__DelegateSignature_Params
{
};

// Function Widget_Overclock.Widget_Overclock_C.SetupOverclock
struct UWidget_Overclock_C_SetupOverclock_Params
{
	float                                              OvecklockAmount;                                          // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Overclock.Widget_Overclock_C.OnPotentialInventoryReplicated
struct UWidget_Overclock_C_OnPotentialInventoryReplicated_Params
{
	class AActor*                                      replicationDetailActorOwner;                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Overclock.Widget_Overclock_C.ExecuteUbergraph_Widget_Overclock
struct UWidget_Overclock_C_ExecuteUbergraph_Widget_Overclock_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_Overclock.Widget_Overclock_C.UpdateBarFill__DelegateSignature
struct UWidget_Overclock_C_UpdateBarFill__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
