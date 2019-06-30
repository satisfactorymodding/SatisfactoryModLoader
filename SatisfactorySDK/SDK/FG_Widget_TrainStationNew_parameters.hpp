#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Widget_TrainStationNew_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Widget_TrainStationNew.Widget_TrainStationNew_C.UpdatePowerStatus
struct UWidget_TrainStationNew_C_UpdatePowerStatus_Params
{
};

// Function Widget_TrainStationNew.Widget_TrainStationNew_C.ShowLocomotiveMenu
struct UWidget_TrainStationNew_C_ShowLocomotiveMenu_Params
{
	class AFGTrain*                                    mTrain;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TrainStationNew.Widget_TrainStationNew_C.GenerateTrainList
struct UWidget_TrainStationNew_C_GenerateTrainList_Params
{
};

// Function Widget_TrainStationNew.Widget_TrainStationNew_C.GetStationName
struct UWidget_TrainStationNew_C_GetStationName_Params
{
	struct FText                                       Name;                                                     // (Parm, OutParm)
};

// Function Widget_TrainStationNew.Widget_TrainStationNew_C.SetStationName
struct UWidget_TrainStationNew_C_SetStationName_Params
{
	struct FText                                       Name;                                                     // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Widget_TrainStationNew.Widget_TrainStationNew_C.OnGetPowerCircuit
struct UWidget_TrainStationNew_C_OnGetPowerCircuit_Params
{
	class UFGPowerCircuit*                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Widget_TrainStationNew.Widget_TrainStationNew_C.Construct
struct UWidget_TrainStationNew_C_Construct_Params
{
};

// Function Widget_TrainStationNew.Widget_TrainStationNew_C.OnEscapePressed
struct UWidget_TrainStationNew_C_OnEscapePressed_Params
{
};

// Function Widget_TrainStationNew.Widget_TrainStationNew_C.BndEvt__mStationNameInput_K2Node_ComponentBoundEvent_0_OnEditableTextCommittedEvent__DelegateSignature
struct UWidget_TrainStationNew_C_BndEvt__mStationNameInput_K2Node_ComponentBoundEvent_0_OnEditableTextCommittedEvent__DelegateSignature_Params
{
	struct FText                                       Text;                                                     // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	TEnumAsByte<ETextCommit>                           CommitMethod;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TrainStationNew.Widget_TrainStationNew_C.OnTrainButtonClicked
struct UWidget_TrainStationNew_C_OnTrainButtonClicked_Params
{
	class UWidget_TrainButton_C*                       Button;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function Widget_TrainStationNew.Widget_TrainStationNew_C.OnLocomotiveMenuClosed
struct UWidget_TrainStationNew_C_OnLocomotiveMenuClosed_Params
{
};

// Function Widget_TrainStationNew.Widget_TrainStationNew_C.OnTrainNameChanged
struct UWidget_TrainStationNew_C_OnTrainNameChanged_Params
{
};

// Function Widget_TrainStationNew.Widget_TrainStationNew_C.OnPowerChanged
struct UWidget_TrainStationNew_C_OnPowerChanged_Params
{
	bool                                               State;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Widget_TrainStationNew.Widget_TrainStationNew_C.ExecuteUbergraph_Widget_TrainStationNew
struct UWidget_TrainStationNew_C_ExecuteUbergraph_Widget_TrainStationNew_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
