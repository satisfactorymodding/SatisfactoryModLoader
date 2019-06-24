#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_DebugCameraController_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_DebugCameraController.BP_DebugCameraController_C.UserConstructionScript
struct ABP_DebugCameraController_C_UserConstructionScript_Params
{
};

// Function BP_DebugCameraController.BP_DebugCameraController_C.InpActEvt_Shift_P_K2Node_InputKeyEvent_1
struct ABP_DebugCameraController_C_InpActEvt_Shift_P_K2Node_InputKeyEvent_1_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_DebugCameraController.BP_DebugCameraController_C.ReceiveOnActivate
struct ABP_DebugCameraController_C_ReceiveOnActivate_Params
{
	class APlayerController**                          OriginalPC;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_DebugCameraController.BP_DebugCameraController_C.ReceiveOnDeactivate
struct ABP_DebugCameraController_C_ReceiveOnDeactivate_Params
{
	class APlayerController**                          RestoredPC;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_DebugCameraController.BP_DebugCameraController_C.ExecuteUbergraph_BP_DebugCameraController
struct ABP_DebugCameraController_C_ExecuteUbergraph_BP_DebugCameraController_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
