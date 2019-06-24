#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_RadarTower_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_RadarTower.Widget_RadarTower_C.UpdateStandByButton
struct UWidget_RadarTower_C_UpdateStandByButton_Params
{
	bool                                               Producing;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_RadarTower.Widget_RadarTower_C.ToggleStandby
struct UWidget_RadarTower_C_ToggleStandby_Params
{
};

// Function Widget_RadarTower.Widget_RadarTower_C.RevealStepToNormalizedRevealPercent
struct UWidget_RadarTower_C_RevealStepToNormalizedRevealPercent_Params
{
	int                                                inInt;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_RadarTower.Widget_RadarTower_C.InitScanLines
struct UWidget_RadarTower_C_InitScanLines_Params
{
};

// Function Widget_RadarTower.Widget_RadarTower_C.UpdateTitle
struct UWidget_RadarTower_C_UpdateTitle_Params
{
	struct FText                                       OverrideText;                                             // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_RadarTower.Widget_RadarTower_C.SecondsToMinutesAndSecondsText
struct UWidget_RadarTower_C_SecondsToMinutesAndSecondsText_Params
{
	float                                              Input;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FText                                       Output;                                                   // (Parm, OutParm)
};

// Function Widget_RadarTower.Widget_RadarTower_C.InitScannedPercent
struct UWidget_RadarTower_C_InitScannedPercent_Params
{
};

// Function Widget_RadarTower.Widget_RadarTower_C.Construct
struct UWidget_RadarTower_C_Construct_Params
{
};

// Function Widget_RadarTower.Widget_RadarTower_C.OnRadiusChanged
struct UWidget_RadarTower_C_OnRadiusChanged_Params
{
};

// Function Widget_RadarTower.Widget_RadarTower_C.UpdateScanTimer
struct UWidget_RadarTower_C_UpdateScanTimer_Params
{
};

// Function Widget_RadarTower.Widget_RadarTower_C.Destruct
struct UWidget_RadarTower_C_Destruct_Params
{
};

// Function Widget_RadarTower.Widget_RadarTower_C.BndEvt__mTowerName_K2Node_ComponentBoundEvent_0_OnEditableTextCommittedEvent__DelegateSignature
struct UWidget_RadarTower_C_BndEvt__mTowerName_K2Node_ComponentBoundEvent_0_OnEditableTextCommittedEvent__DelegateSignature_Params
{
	struct FText                                       Text;                                                     // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	TEnumAsByte<ETextCommit>                           CommitMethod;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_RadarTower.Widget_RadarTower_C.LerpScannedAreaEvent
struct UWidget_RadarTower_C_LerpScannedAreaEvent_Params
{
};

// Function Widget_RadarTower.Widget_RadarTower_C.BndEvt__mRadarTower_K2Node_ComponentBoundEvent_2_BuildingStateChanged__DelegateSignature
struct UWidget_RadarTower_C_BndEvt__mRadarTower_K2Node_ComponentBoundEvent_2_BuildingStateChanged__DelegateSignature_Params
{
	bool                                               State;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_RadarTower.Widget_RadarTower_C.BndEvt__Widget_StandbyButton_K2Node_ComponentBoundEvent_3_OnStandbyClicked__DelegateSignature
struct UWidget_RadarTower_C_BndEvt__Widget_StandbyButton_K2Node_ComponentBoundEvent_3_OnStandbyClicked__DelegateSignature_Params
{
};

// Function Widget_RadarTower.Widget_RadarTower_C.OnProductionChanged
struct UWidget_RadarTower_C_OnProductionChanged_Params
{
	bool                                               HasChanged;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_RadarTower.Widget_RadarTower_C.ExecuteUbergraph_Widget_RadarTower
struct UWidget_RadarTower_C_ExecuteUbergraph_Widget_RadarTower_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
