#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_WheeledVehicle_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.SetActorRepresentationText
struct ABP_WheeledVehicle_C_SetActorRepresentationText_Params
{
	struct FText                                       newText;                                                  // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateRepresentation
struct ABP_WheeledVehicle_C_UpdateRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetActorRepresentationColor
struct ABP_WheeledVehicle_C_GetActorRepresentationColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetActorRepresentationText
struct ABP_WheeledVehicle_C_GetActorRepresentationText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetActorRepresentationTexture
struct ABP_WheeledVehicle_C_GetActorRepresentationTexture_Params
{
	class UTexture2D*                                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetActorRepresentationType
struct ABP_WheeledVehicle_C_GetActorRepresentationType_Params
{
	ERepresentationType                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetActorShouldShowInCompass
struct ABP_WheeledVehicle_C_GetActorShouldShowInCompass_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetActorFogOfWarRevealRadius
struct ABP_WheeledVehicle_C_GetActorFogOfWarRevealRadius_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetActorFogOfWarRevealType
struct ABP_WheeledVehicle_C_GetActorFogOfWarRevealType_Params
{
	EFogOfWarRevealType                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.RemoveAsRepresentation
struct ABP_WheeledVehicle_C_RemoveAsRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.AddAsRepresentation
struct ABP_WheeledVehicle_C_AddAsRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetActorShouldShowOnMap
struct ABP_WheeledVehicle_C_GetActorShouldShowOnMap_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetRealActorLocation
struct ABP_WheeledVehicle_C_GetRealActorLocation_Params
{
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetRealActorRotation
struct ABP_WheeledVehicle_C_GetRealActorRotation_Params
{
	struct FRotator                                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.IsActorStatic
struct ABP_WheeledVehicle_C_IsActorStatic_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetDriftForceOffset
struct ABP_WheeledVehicle_C_GetDriftForceOffset_Params
{
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ShouldStopVehicle
struct ABP_WheeledVehicle_C_ShouldStopVehicle_Params
{
	bool                                               ShouldStop;                                               // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.TurnOverVehicle
struct ABP_WheeledVehicle_C_TurnOverVehicle_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.AdjustThrottle
struct ABP_WheeledVehicle_C_AdjustThrottle_Params
{
	float                                              Throttle;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              adjustedThrottle;                                         // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.TogglePathVisibility
struct ABP_WheeledVehicle_C_TogglePathVisibility_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ToggleAutoPilot
struct ABP_WheeledVehicle_C_ToggleAutoPilot_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.TogglePauseRecording
struct ABP_WheeledVehicle_C_TogglePauseRecording_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.TickSimulationMovement
struct ABP_WheeledVehicle_C_TickSimulationMovement_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.CalculateReverseSteering
struct ABP_WheeledVehicle_C_CalculateReverseSteering_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.StopVehicle
struct ABP_WheeledVehicle_C_StopVehicle_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.CanMove
struct ABP_WheeledVehicle_C_CanMove_Params
{
	bool                                               CanMove;                                                  // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateEngineLoadSound
struct ABP_WheeledVehicle_C_UpdateEngineLoadSound_Params
{
	float                                              dt;                                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateAccelerationSound
struct ABP_WheeledVehicle_C_UpdateAccelerationSound_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateThrottleState
struct ABP_WheeledVehicle_C_UpdateThrottleState_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.DidGearDown
struct ABP_WheeledVehicle_C_DidGearDown_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.DidGearUp
struct ABP_WheeledVehicle_C_DidGearUp_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.CheckCurrentGear
struct ABP_WheeledVehicle_C_CheckCurrentGear_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.StopSoundLoops
struct ABP_WheeledVehicle_C_StopSoundLoops_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.StartSoundLoops
struct ABP_WheeledVehicle_C_StartSoundLoops_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ToggleFreeCamera
struct ABP_WheeledVehicle_C_ToggleFreeCamera_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetLookAtDecription
struct ABP_WheeledVehicle_C_GetLookAtDecription_Params
{
	class AFGCharacterPlayer**                         byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState*                                  State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.CloseVehicleUI
struct ABP_WheeledVehicle_C_CloseVehicleUI_Params
{
	class AFGCharacterPlayer*                          inCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.OpenVehicleUI
struct ABP_WheeledVehicle_C_OpenVehicleUI_Params
{
	class AFGCharacterPlayer*                          inCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.PonderOpeningTrunk
struct ABP_WheeledVehicle_C_PonderOpeningTrunk_Params
{
	class AFGCharacterPlayer*                          inCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateUseState
struct ABP_WheeledVehicle_C_UpdateUseState_Params
{
	class AFGCharacterPlayer**                         byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector*                                    atLocation;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
	class UPrimitiveComponent**                        componentHit;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FUseState                                   out_useState;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.OnRep_mIsFollowingPath
struct ABP_WheeledVehicle_C_OnRep_mIsFollowingPath_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateSpeedLimit
struct ABP_WheeledVehicle_C_UpdateSpeedLimit_Params
{
	class ABP_VehicleTargetPoint_C*                    TargetPoint;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.DoReverseToFreedom
struct ABP_WheeledVehicle_C_DoReverseToFreedom_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReverseToFreedom
struct ABP_WheeledVehicle_C_ReverseToFreedom_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.CacheSpeedInKMH
struct ABP_WheeledVehicle_C_CacheSpeedInKMH_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.OnRep_mIsRecording
struct ABP_WheeledVehicle_C_OnRep_mIsRecording_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.MoveToLocation
struct ABP_WheeledVehicle_C_MoveToLocation_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.TickRecording
struct ABP_WheeledVehicle_C_TickRecording_Params
{
	float                                              dt;                                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateVehicleMovement
struct ABP_WheeledVehicle_C_UpdateVehicleMovement_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.StartRecording
struct ABP_WheeledVehicle_C_StartRecording_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.StopRecording
struct ABP_WheeledVehicle_C_StopRecording_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GatherData
struct ABP_WheeledVehicle_C_GatherData_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.RemoveOldTargets
struct ABP_WheeledVehicle_C_RemoveOldTargets_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.PlaceTargetPoint
struct ABP_WheeledVehicle_C_PlaceTargetPoint_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.TargetReached
struct ABP_WheeledVehicle_C_TargetReached_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.SetNewPath
struct ABP_WheeledVehicle_C_SetNewPath_Params
{
	class ABP_VehicleTargetPoint_C*                    newTarget;                                                // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.GetTargetDistance
struct ABP_WheeledVehicle_C_GetTargetDistance_Params
{
	float                                              Distance;                                                 // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateThrottle
struct ABP_WheeledVehicle_C_UpdateThrottle_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateSteering
struct ABP_WheeledVehicle_C_UpdateSteering_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.UserConstructionScript
struct ABP_WheeledVehicle_C_UserConstructionScript_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpActEvt_Reload_K2Node_InputActionEvent_7
struct ABP_WheeledVehicle_C_InpActEvt_Reload_K2Node_InputActionEvent_7_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpActEvt_Use_K2Node_InputActionEvent_6
struct ABP_WheeledVehicle_C_InpActEvt_Use_K2Node_InputActionEvent_6_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpActEvt_Jump_Drift_K2Node_InputActionEvent_5
struct ABP_WheeledVehicle_C_InpActEvt_Jump_Drift_K2Node_InputActionEvent_5_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpActEvt_Jump_Drift_K2Node_InputActionEvent_4
struct ABP_WheeledVehicle_C_InpActEvt_Jump_Drift_K2Node_InputActionEvent_4_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpActEvt_ResourceScanner_ToggleVehicleRecording_K2Node_InputActionEvent_3
struct ABP_WheeledVehicle_C_InpActEvt_ResourceScanner_ToggleVehicleRecording_K2Node_InputActionEvent_3_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpActEvt_ResourceScanner_ToggleVehicleRecording_K2Node_InputActionEvent_2
struct ABP_WheeledVehicle_C_InpActEvt_ResourceScanner_ToggleVehicleRecording_K2Node_InputActionEvent_2_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpActEvt_PrimaryFire_K2Node_InputActionEvent_1
struct ABP_WheeledVehicle_C_InpActEvt_PrimaryFire_K2Node_InputActionEvent_1_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ServerToggleRecording
struct ABP_WheeledVehicle_C_ServerToggleRecording_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveUnpossessed
struct ABP_WheeledVehicle_C_ReceiveUnpossessed_Params
{
	class AController**                                OldController;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveHit
struct ABP_WheeledVehicle_C_ReceiveHit_Params
{
	class UPrimitiveComponent**                        MyComp;                                                   // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class AActor**                                     Other;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UPrimitiveComponent**                        OtherComp;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	bool*                                              bSelfMoved;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector*                                    HitLocation;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector*                                    HitNormal;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector*                                    NormalImpulse;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FHitResult*                                 Hit;                                                      // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveDestroyed
struct ABP_WheeledVehicle_C_ReceiveDestroyed_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ResetImpactSound
struct ABP_WheeledVehicle_C_ResetImpactSound_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.OnUse
struct ABP_WheeledVehicle_C_OnUse_Params
{
	class AFGCharacterPlayer**                         byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState*                                  State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ServerSetTrunkUser
struct ABP_WheeledVehicle_C_ServerSetTrunkUser_Params
{
	class AFGCharacterPlayer*                          inCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.OpenTrunk
struct ABP_WheeledVehicle_C_OpenTrunk_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.Multicast_OpenTrunk
struct ABP_WheeledVehicle_C_Multicast_OpenTrunk_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.CloseTrunk
struct ABP_WheeledVehicle_C_CloseTrunk_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.Multicast_CloseTrunk
struct ABP_WheeledVehicle_C_Multicast_CloseTrunk_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceivePossessed
struct ABP_WheeledVehicle_C_ReceivePossessed_Params
{
	class AController**                                NewController;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ClientClearAIMovment
struct ABP_WheeledVehicle_C_ClientClearAIMovment_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.StartAccelerating
struct ABP_WheeledVehicle_C_StartAccelerating_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.StopAccelerating
struct ABP_WheeledVehicle_C_StopAccelerating_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.TickVehicleSound
struct ABP_WheeledVehicle_C_TickVehicleSound_Params
{
	float                                              dt;                                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveTick
struct ABP_WheeledVehicle_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.UpdateCamera
struct ABP_WheeledVehicle_C_UpdateCamera_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveBeginPlay
struct ABP_WheeledVehicle_C_ReceiveBeginPlay_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.WasDocked
struct ABP_WheeledVehicle_C_WasDocked_Params
{
	class AFGBuildableDockingStation**                 atStation;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ServerSetMenuOpen
struct ABP_WheeledVehicle_C_ServerSetMenuOpen_Params
{
	bool                                               menuOpen;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ServerClearPathRecording
struct ABP_WheeledVehicle_C_ServerClearPathRecording_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.WasUndocked
struct ABP_WheeledVehicle_C_WasUndocked_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ServerTogglePauseRecording
struct ABP_WheeledVehicle_C_ServerTogglePauseRecording_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ServerToggleAutoPilot
struct ABP_WheeledVehicle_C_ServerToggleAutoPilot_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ServerTogglePathVisibility
struct ABP_WheeledVehicle_C_ServerTogglePathVisibility_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.Server_Leave
struct ABP_WheeledVehicle_C_Server_Leave_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveOnVehicleStartup
struct ABP_WheeledVehicle_C_ReceiveOnVehicleStartup_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveOnVehicleShutDown
struct ABP_WheeledVehicle_C_ReceiveOnVehicleShutDown_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveOnDriverEnter
struct ABP_WheeledVehicle_C_ReceiveOnDriverEnter_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ReceiveOnDriverLeave
struct ABP_WheeledVehicle_C_ReceiveOnDriverLeave_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.PlayFoliageDestroyedEffect
struct ABP_WheeledVehicle_C_PlayFoliageDestroyedEffect_Params
{
	class UParticleSystem**                            destroyEffect;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UAkAudioEvent**                              destroyAudioEvent;                                        // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FVector*                                    Location;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpAxisEvt_MoveForward_K2Node_InputAxisEvent_2
struct ABP_WheeledVehicle_C_InpAxisEvt_MoveForward_K2Node_InputAxisEvent_2_Params
{
	float                                              AxisValue;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.InpAxisEvt_MoveRight_K2Node_InputAxisEvent_3
struct ABP_WheeledVehicle_C_InpAxisEvt_MoveRight_K2Node_InputAxisEvent_3_Params
{
	float                                              AxisValue;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.Server_Honk
struct ABP_WheeledVehicle_C_Server_Honk_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.Multicast_Honk
struct ABP_WheeledVehicle_C_Multicast_Honk_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.ExecuteUbergraph_BP_WheeledVehicle
struct ABP_WheeledVehicle_C_ExecuteUbergraph_BP_WheeledVehicle_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.OnStartRecording__DelegateSignature
struct ABP_WheeledVehicle_C_OnStartRecording__DelegateSignature_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.OnStopRecording__DelegateSignature
struct ABP_WheeledVehicle_C_OnStopRecording__DelegateSignature_Params
{
};

// Function BP_WheeledVehicle.BP_WheeledVehicle_C.LocationReached__DelegateSignature
struct ABP_WheeledVehicle_C_LocationReached__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
