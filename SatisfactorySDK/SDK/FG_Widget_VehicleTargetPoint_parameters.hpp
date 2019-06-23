#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_VehicleTargetPoint_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_VehicleTargetPoint.Widget_VehicleTargetPoint_C.SetNewWaitTime
struct UWidget_VehicleTargetPoint_C_SetNewWaitTime_Params
{
};

// Function Widget_VehicleTargetPoint.Widget_VehicleTargetPoint_C.GetNodeTypeAndSetWindowTitle
struct UWidget_VehicleTargetPoint_C_GetNodeTypeAndSetWindowTitle_Params
{
};

// Function Widget_VehicleTargetPoint.Widget_VehicleTargetPoint_C.Init
struct UWidget_VehicleTargetPoint_C_Init_Params
{
};

// Function Widget_VehicleTargetPoint.Widget_VehicleTargetPoint_C.Destruct
struct UWidget_VehicleTargetPoint_C_Destruct_Params
{
};

// Function Widget_VehicleTargetPoint.Widget_VehicleTargetPoint_C.BndEvt__Widget_StandardButton_C_0_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature
struct UWidget_VehicleTargetPoint_C_BndEvt__Widget_StandardButton_C_0_K2Node_ComponentBoundEvent_3_OnClicked__DelegateSignature_Params
{
};

// Function Widget_VehicleTargetPoint.Widget_VehicleTargetPoint_C.BndEvt__mDeleteButton2_K2Node_ComponentBoundEvent_5_OnClicked__DelegateSignature
struct UWidget_VehicleTargetPoint_C_BndEvt__mDeleteButton2_K2Node_ComponentBoundEvent_5_OnClicked__DelegateSignature_Params
{
};

// Function Widget_VehicleTargetPoint.Widget_VehicleTargetPoint_C.BndEvt__mWaitButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature
struct UWidget_VehicleTargetPoint_C_BndEvt__mWaitButton_K2Node_ComponentBoundEvent_0_OnClicked__DelegateSignature_Params
{
};

// Function Widget_VehicleTargetPoint.Widget_VehicleTargetPoint_C.SetWaitTimePopup
struct UWidget_VehicleTargetPoint_C_SetWaitTimePopup_Params
{
	bool                                               mPopUpConfirm;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_VehicleTargetPoint.Widget_VehicleTargetPoint_C.DoDeleteNode
struct UWidget_VehicleTargetPoint_C_DoDeleteNode_Params
{
	bool                                               ConfirmClicked;                                           // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_VehicleTargetPoint.Widget_VehicleTargetPoint_C.Construct
struct UWidget_VehicleTargetPoint_C_Construct_Params
{
};

// Function Widget_VehicleTargetPoint.Widget_VehicleTargetPoint_C.BndEvt__Widget_InputBox_K2Node_ComponentBoundEvent_6_OnTextComitted__DelegateSignature
struct UWidget_VehicleTargetPoint_C_BndEvt__Widget_InputBox_K2Node_ComponentBoundEvent_6_OnTextComitted__DelegateSignature_Params
{
	struct FText                                       Text;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
	TEnumAsByte<ETextCommit>                           CommitMethod;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_VehicleTargetPoint.Widget_VehicleTargetPoint_C.PreConstruct
struct UWidget_VehicleTargetPoint_C_PreConstruct_Params
{
	bool*                                              IsDesignTime;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_VehicleTargetPoint.Widget_VehicleTargetPoint_C.ExecuteUbergraph_Widget_VehicleTargetPoint
struct UWidget_VehicleTargetPoint_C_ExecuteUbergraph_Widget_VehicleTargetPoint_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
