#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_Locomotive_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_Locomotive.BP_Locomotive_C.SetActorRepresentationText
struct ABP_Locomotive_C_SetActorRepresentationText_Params
{
	struct FText                                       newText;                                                  // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function BP_Locomotive.BP_Locomotive_C.UpdateRepresentation
struct ABP_Locomotive_C_UpdateRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Locomotive.BP_Locomotive_C.GetActorFogOfWarRevealRadius
struct ABP_Locomotive_C_GetActorFogOfWarRevealRadius_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Locomotive.BP_Locomotive_C.GetActorFogOfWarRevealType
struct ABP_Locomotive_C_GetActorFogOfWarRevealType_Params
{
	EFogOfWarRevealType                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Locomotive.BP_Locomotive_C.GetActorRepresentationColor
struct ABP_Locomotive_C_GetActorRepresentationColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Locomotive.BP_Locomotive_C.GetActorRepresentationText
struct ABP_Locomotive_C_GetActorRepresentationText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function BP_Locomotive.BP_Locomotive_C.GetActorRepresentationTexture
struct ABP_Locomotive_C_GetActorRepresentationTexture_Params
{
	class UTexture2D*                                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Locomotive.BP_Locomotive_C.GetActorRepresentationType
struct ABP_Locomotive_C_GetActorRepresentationType_Params
{
	ERepresentationType                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Locomotive.BP_Locomotive_C.GetActorShouldShowInCompass
struct ABP_Locomotive_C_GetActorShouldShowInCompass_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Locomotive.BP_Locomotive_C.AddAsRepresentation
struct ABP_Locomotive_C_AddAsRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Locomotive.BP_Locomotive_C.GetActorShouldShowOnMap
struct ABP_Locomotive_C_GetActorShouldShowOnMap_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Locomotive.BP_Locomotive_C.GetRealActorLocation
struct ABP_Locomotive_C_GetRealActorLocation_Params
{
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Locomotive.BP_Locomotive_C.GetRealActorRotation
struct ABP_Locomotive_C_GetRealActorRotation_Params
{
	struct FRotator                                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Locomotive.BP_Locomotive_C.IsActorStatic
struct ABP_Locomotive_C_IsActorStatic_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Locomotive.BP_Locomotive_C.RemoveAsRepresentation
struct ABP_Locomotive_C_RemoveAsRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_Locomotive.BP_Locomotive_C.UserConstructionScript
struct ABP_Locomotive_C_UserConstructionScript_Params
{
};

// Function BP_Locomotive.BP_Locomotive_C.InpActEvt_Use_K2Node_InputActionEvent_4
struct ABP_Locomotive_C_InpActEvt_Use_K2Node_InputActionEvent_4_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_Locomotive.BP_Locomotive_C.InpActEvt_Jump_Drift_K2Node_InputActionEvent_3
struct ABP_Locomotive_C_InpActEvt_Jump_Drift_K2Node_InputActionEvent_3_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_Locomotive.BP_Locomotive_C.InpActEvt_Jump_Drift_K2Node_InputActionEvent_2
struct ABP_Locomotive_C_InpActEvt_Jump_Drift_K2Node_InputActionEvent_2_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_Locomotive.BP_Locomotive_C.InpActEvt_ResourceScanner_ToggleVehicleRecording_K2Node_InputActionEvent_1
struct ABP_Locomotive_C_InpActEvt_ResourceScanner_ToggleVehicleRecording_K2Node_InputActionEvent_1_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_Locomotive.BP_Locomotive_C.InpActEvt_NumPadOne_K2Node_InputKeyEvent_6
struct ABP_Locomotive_C_InpActEvt_NumPadOne_K2Node_InputKeyEvent_6_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_Locomotive.BP_Locomotive_C.InpActEvt_NumPadTwo_K2Node_InputKeyEvent_5
struct ABP_Locomotive_C_InpActEvt_NumPadTwo_K2Node_InputKeyEvent_5_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_Locomotive.BP_Locomotive_C.InpActEvt_LeftMouseButton_K2Node_InputKeyEvent_4
struct ABP_Locomotive_C_InpActEvt_LeftMouseButton_K2Node_InputKeyEvent_4_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_Locomotive.BP_Locomotive_C.InpActEvt_LeftMouseButton_K2Node_InputKeyEvent_3
struct ABP_Locomotive_C_InpActEvt_LeftMouseButton_K2Node_InputKeyEvent_3_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_Locomotive.BP_Locomotive_C.InpActEvt_NumPadThree_K2Node_InputKeyEvent_2
struct ABP_Locomotive_C_InpActEvt_NumPadThree_K2Node_InputKeyEvent_2_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_Locomotive.BP_Locomotive_C.InpActEvt_NumPadFour_K2Node_InputKeyEvent_1
struct ABP_Locomotive_C_InpActEvt_NumPadFour_K2Node_InputKeyEvent_1_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_Locomotive.BP_Locomotive_C.ReceiveTick
struct ABP_Locomotive_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Locomotive.BP_Locomotive_C.UpdateCamera
struct ABP_Locomotive_C_UpdateCamera_Params
{
};

// Function BP_Locomotive.BP_Locomotive_C.ReceiveBeginPlay
struct ABP_Locomotive_C_ReceiveBeginPlay_Params
{
};

// Function BP_Locomotive.BP_Locomotive_C.ReceiveDestroyed
struct ABP_Locomotive_C_ReceiveDestroyed_Params
{
};

// Function BP_Locomotive.BP_Locomotive_C.Server_Leave
struct ABP_Locomotive_C_Server_Leave_Params
{
};

// Function BP_Locomotive.BP_Locomotive_C.InpAxisEvt_MoveRight_K2Node_InputAxisEvent_1
struct ABP_Locomotive_C_InpAxisEvt_MoveRight_K2Node_InputAxisEvent_1_Params
{
	float                                              AxisValue;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Locomotive.BP_Locomotive_C.InpAxisEvt_MoveForward_K2Node_InputAxisEvent_2
struct ABP_Locomotive_C_InpAxisEvt_MoveForward_K2Node_InputAxisEvent_2_Params
{
	float                                              AxisValue;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Locomotive.BP_Locomotive_C.ReceiveUnpossessed
struct ABP_Locomotive_C_ReceiveUnpossessed_Params
{
	class AController**                                OldController;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Locomotive.BP_Locomotive_C.ReceivePossessed
struct ABP_Locomotive_C_ReceivePossessed_Params
{
	class AController**                                NewController;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_Locomotive.BP_Locomotive_C.MultiCast_TrainHorn_01
struct ABP_Locomotive_C_MultiCast_TrainHorn_01_Params
{
};

// Function BP_Locomotive.BP_Locomotive_C.MultiCast_TrainHorn_01_Stop
struct ABP_Locomotive_C_MultiCast_TrainHorn_01_Stop_Params
{
};

// Function BP_Locomotive.BP_Locomotive_C.MultiCast_TrainHorn_02
struct ABP_Locomotive_C_MultiCast_TrainHorn_02_Params
{
};

// Function BP_Locomotive.BP_Locomotive_C.MultiCast_TrainHorn_02_Stop
struct ABP_Locomotive_C_MultiCast_TrainHorn_02_Stop_Params
{
};

// Function BP_Locomotive.BP_Locomotive_C.Server_Horn_01
struct ABP_Locomotive_C_Server_Horn_01_Params
{
};

// Function BP_Locomotive.BP_Locomotive_C.Server_Horn_01_Stop
struct ABP_Locomotive_C_Server_Horn_01_Stop_Params
{
};

// Function BP_Locomotive.BP_Locomotive_C.Server_Horn_02
struct ABP_Locomotive_C_Server_Horn_02_Params
{
};

// Function BP_Locomotive.BP_Locomotive_C.Server_Horn_02_Stop
struct ABP_Locomotive_C_Server_Horn_02_Stop_Params
{
};

// Function BP_Locomotive.BP_Locomotive_C.ExecuteUbergraph_BP_Locomotive
struct ABP_Locomotive_C_ExecuteUbergraph_BP_Locomotive_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
