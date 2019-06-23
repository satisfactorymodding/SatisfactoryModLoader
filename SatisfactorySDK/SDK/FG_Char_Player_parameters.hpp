#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Char_Player_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function Char_Player.Char_Player_C.SetActorRepresentationText
struct AChar_Player_C_SetActorRepresentationText_Params
{
	struct FText                                       newText;                                                  // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Char_Player.Char_Player_C.UpdateRepresentation
struct AChar_Player_C_UpdateRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.GetActorRepresentationColor
struct AChar_Player_C_GetActorRepresentationColor_Params
{
	struct FLinearColor                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.GetActorRepresentationText
struct AChar_Player_C_GetActorRepresentationText_Params
{
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function Char_Player.Char_Player_C.GetActorRepresentationTexture
struct AChar_Player_C_GetActorRepresentationTexture_Params
{
	class UTexture2D*                                  ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.GetActorRepresentationType
struct AChar_Player_C_GetActorRepresentationType_Params
{
	ERepresentationType                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.GetActorShouldShowInCompass
struct AChar_Player_C_GetActorShouldShowInCompass_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.GetActorFogOfWarRevealRadius
struct AChar_Player_C_GetActorFogOfWarRevealRadius_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.GetActorFogOfWarRevealType
struct AChar_Player_C_GetActorFogOfWarRevealType_Params
{
	EFogOfWarRevealType                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.RemoveAsRepresentation
struct AChar_Player_C_RemoveAsRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.GetRealActorRotation
struct AChar_Player_C_GetRealActorRotation_Params
{
	struct FRotator                                    ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.AddAsRepresentation
struct AChar_Player_C_AddAsRepresentation_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.GetActorShouldShowOnMap
struct AChar_Player_C_GetActorShouldShowOnMap_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.GetRealActorLocation
struct AChar_Player_C_GetRealActorLocation_Params
{
	struct FVector                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.IsActorStatic
struct AChar_Player_C_IsActorStatic_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.ToggleCodex
struct AChar_Player_C_ToggleCodex_Params
{
};

// Function Char_Player.Char_Player_C.ToggleInventory
struct AChar_Player_C_ToggleInventory_Params
{
};

// Function Char_Player.Char_Player_C.ToggleFlashlight
struct AChar_Player_C_ToggleFlashlight_Params
{
};

// Function Char_Player.Char_Player_C.RemovePlayerHUD
struct AChar_Player_C_RemovePlayerHUD_Params
{
	class AFGPlayerController*                         OldController;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.SetupPlayerHUD
struct AChar_Player_C_SetupPlayerHUD_Params
{
	class AFGPlayerController*                         PlayerController;                                         // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.HandleFlashlight
struct AChar_Player_C_HandleFlashlight_Params
{
};

// Function Char_Player.Char_Player_C.UpdatePlayerTextVisibility
struct AChar_Player_C_UpdatePlayerTextVisibility_Params
{
};

// Function Char_Player.Char_Player_C.GetHealthPct
struct AChar_Player_C_GetHealthPct_Params
{
	float                                              healthPct;                                                // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.UpdateDamageIndicator
struct AChar_Player_C_UpdateDamageIndicator_Params
{
};

// Function Char_Player.Char_Player_C.PlayDamageVO
struct AChar_Player_C_PlayDamageVO_Params
{
	class UDamageType*                                 Damage_Type;                                              // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.PlayDamageCameraShake
struct AChar_Player_C_PlayDamageCameraShake_Params
{
};

// Function Char_Player.Char_Player_C.ApplyDamagePP
struct AChar_Player_C_ApplyDamagePP_Params
{
};

// Function Char_Player.Char_Player_C.PlayImpactEffectSound
struct AChar_Player_C_PlayImpactEffectSound_Params
{
	class UDamageType*                                 DamageType;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.CalculateOnscreenEffectBlendWeight
struct AChar_Player_C_CalculateOnscreenEffectBlendWeight_Params
{
	float                                              BlendWeight;                                              // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.UpdateWindParticle
struct AChar_Player_C_UpdateWindParticle_Params
{
};

// Function Char_Player.Char_Player_C.TickSprintNoise
struct AChar_Player_C_TickSprintNoise_Params
{
};

// Function Char_Player.Char_Player_C.GetPlayerCameraManager
struct AChar_Player_C_GetPlayerCameraManager_Params
{
	class APlayerCameraManager*                        cameraManager;                                            // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.FadeDamageIndicator
struct AChar_Player_C_FadeDamageIndicator_Params
{
};

// Function Char_Player.Char_Player_C.TickPlayerNameText
struct AChar_Player_C_TickPlayerNameText_Params
{
};

// Function Char_Player.Char_Player_C.UserConstructionScript
struct AChar_Player_C_UserConstructionScript_Params
{
};

// Function Char_Player.Char_Player_C.InpActEvt_OpenCodex_K2Node_InputActionEvent_6
struct AChar_Player_C_InpActEvt_OpenCodex_K2Node_InputActionEvent_6_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Char_Player.Char_Player_C.InpActEvt_Flashlight_K2Node_InputActionEvent_5
struct AChar_Player_C_InpActEvt_Flashlight_K2Node_InputActionEvent_5_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Char_Player.Char_Player_C.InpActEvt_PrimaryFire_K2Node_InputActionEvent_4
struct AChar_Player_C_InpActEvt_PrimaryFire_K2Node_InputActionEvent_4_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Char_Player.Char_Player_C.InpActEvt_Inventory_K2Node_InputActionEvent_3
struct AChar_Player_C_InpActEvt_Inventory_K2Node_InputActionEvent_3_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Char_Player.Char_Player_C.InpActEvt_EmoteWheel_K2Node_InputActionEvent_2
struct AChar_Player_C_InpActEvt_EmoteWheel_K2Node_InputActionEvent_2_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Char_Player.Char_Player_C.InpActEvt_EmoteWheel_K2Node_InputActionEvent_1
struct AChar_Player_C_InpActEvt_EmoteWheel_K2Node_InputActionEvent_1_Params
{
	struct FKey                                        Key;                                                      // (BlueprintVisible, BlueprintReadOnly, Parm)
};

// Function Char_Player.Char_Player_C.SetFirstPersonMode
struct AChar_Player_C_SetFirstPersonMode_Params
{
};

// Function Char_Player.Char_Player_C.SetThirdPersonMode
struct AChar_Player_C_SetThirdPersonMode_Params
{
};

// Function Char_Player.Char_Player_C.StartFocusAim
struct AChar_Player_C_StartFocusAim_Params
{
};

// Function Char_Player.Char_Player_C.StopFocusAim
struct AChar_Player_C_StopFocusAim_Params
{
};

// Function Char_Player.Char_Player_C.StartFreeRotate3P
struct AChar_Player_C_StartFreeRotate3P_Params
{
};

// Function Char_Player.Char_Player_C.StopFreeRotate3P
struct AChar_Player_C_StopFreeRotate3P_Params
{
};

// Function Char_Player.Char_Player_C.CameraZoomOut
struct AChar_Player_C_CameraZoomOut_Params
{
};

// Function Char_Player.Char_Player_C.CameraZoomIn
struct AChar_Player_C_CameraZoomIn_Params
{
};

// Function Char_Player.Char_Player_C.ReceiveDied
struct AChar_Player_C_ReceiveDied_Params
{
};

// Function Char_Player.Char_Player_C.CameraTick
struct AChar_Player_C_CameraTick_Params
{
};

// Function Char_Player.Char_Player_C.PlayPickupEffects
struct AChar_Player_C_PlayPickupEffects_Params
{
};

// Function Char_Player.Char_Player_C.SnapSpringArmToDesiredLocation
struct AChar_Player_C_SnapSpringArmToDesiredLocation_Params
{
};

// Function Char_Player.Char_Player_C.OnReviveComplete
struct AChar_Player_C_OnReviveComplete_Params
{
};

// Function Char_Player.Char_Player_C.OnLanded
struct AChar_Player_C_OnLanded_Params
{
	struct FHitResult*                                 Hit;                                                      // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.ClientSetupPlayerHUD
struct AChar_Player_C_ClientSetupPlayerHUD_Params
{
	class AController*                                 InController;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.ReceiveUnpossessed
struct AChar_Player_C_ReceiveUnpossessed_Params
{
	class AController**                                OldController;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.OnReceiveRadiationStart
struct AChar_Player_C_OnReceiveRadiationStart_Params
{
};

// Function Char_Player.Char_Player_C.OnReceiveRadiationStop
struct AChar_Player_C_OnReceiveRadiationStop_Params
{
};

// Function Char_Player.Char_Player_C.ReceivePossessed
struct AChar_Player_C_ReceivePossessed_Params
{
	class AController**                                NewController;                                            // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.ReceiveDestroyed
struct AChar_Player_C_ReceiveDestroyed_Params
{
};

// Function Char_Player.Char_Player_C.TakeDamageEvent
struct AChar_Player_C_TakeDamageEvent_Params
{
	class AActor*                                      damagedActor;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float                                              damageAmount;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class UDamageType*                                 DamageType;                                               // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AController*                                 instigatedBy;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      damageCauser;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.ReceiveBeginPlay
struct AChar_Player_C_ReceiveBeginPlay_Params
{
};

// Function Char_Player.Char_Player_C.ReceiveTick
struct AChar_Player_C_ReceiveTick_Params
{
	float*                                             DeltaSeconds;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.Server_PlayClap
struct AChar_Player_C_Server_PlayClap_Params
{
};

// Function Char_Player.Char_Player_C.Multicast_PlayClap
struct AChar_Player_C_Multicast_PlayClap_Params
{
};

// Function Char_Player.Char_Player_C.Server_SetFlashlightOn
struct AChar_Player_C_Server_SetFlashlightOn_Params
{
	bool                                               FlashlightOn;                                             // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.OnDisabledInputGateChanged
struct AChar_Player_C_OnDisabledInputGateChanged_Params
{
	struct FDisabledInputGate*                         NewValue;                                                 // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.AudioTickEvent
struct AChar_Player_C_AudioTickEvent_Params
{
	float                                              AudioTick;                                                // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.LimitLook
struct AChar_Player_C_LimitLook_Params
{
	bool                                               doLimit;                                                  // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.StartCinematic
struct AChar_Player_C_StartCinematic_Params
{
};

// Function Char_Player.Char_Player_C.EndCinematic
struct AChar_Player_C_EndCinematic_Params
{
};

// Function Char_Player.Char_Player_C.DisableGravity
struct AChar_Player_C_DisableGravity_Params
{
};

// Function Char_Player.Char_Player_C.Server_PlaySpinEmote
struct AChar_Player_C_Server_PlaySpinEmote_Params
{
};

// Function Char_Player.Char_Player_C.Multicast_PlatSpinEmote
struct AChar_Player_C_Multicast_PlatSpinEmote_Params
{
};

// Function Char_Player.Char_Player_C.ClearEmoteMesh
struct AChar_Player_C_ClearEmoteMesh_Params
{
};

// Function Char_Player.Char_Player_C.OnSpawnDeathMarker
struct AChar_Player_C_OnSpawnDeathMarker_Params
{
};

// Function Char_Player.Char_Player_C.ShowEmote
struct AChar_Player_C_ShowEmote_Params
{
	int                                                EmoteIndex;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.SkipIntro
struct AChar_Player_C_SkipIntro_Params
{
};

// Function Char_Player.Char_Player_C.Server_playSignsEmote
struct AChar_Player_C_Server_playSignsEmote_Params
{
};

// Function Char_Player.Char_Player_C.Multicast_PlaySignsEmote
struct AChar_Player_C_Multicast_PlaySignsEmote_Params
{
};

// Function Char_Player.Char_Player_C.StartIsLookedAt
struct AChar_Player_C_StartIsLookedAt_Params
{
	class AFGCharacterPlayer**                         byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState*                                  State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Char_Player.Char_Player_C.StopIsLookedAt
struct AChar_Player_C_StopIsLookedAt_Params
{
	class AFGCharacterPlayer**                         byCharacter;                                              // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	struct FUseState*                                  State;                                                    // (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm)
};

// Function Char_Player.Char_Player_C.OnRadiationIntensityUpdated
struct AChar_Player_C_OnRadiationIntensityUpdated_Params
{
	float*                                             radiationIntensity;                                       // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
	float*                                             radiationImmunity;                                        // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.ExecuteUbergraph_Char_Player
struct AChar_Player_C_ExecuteUbergraph_Char_Player_Params
{
	int                                                EntryPoint;                                               // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.EventFire__DelegateSignature
struct AChar_Player_C_EventFire__DelegateSignature_Params
{
};

// Function Char_Player.Char_Player_C.EventScroll__DelegateSignature
struct AChar_Player_C_EventScroll__DelegateSignature_Params
{
	int                                                Index;                                                    // (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
};

// Function Char_Player.Char_Player_C.EventScrollDown__DelegateSignature
struct AChar_Player_C_EventScrollDown__DelegateSignature_Params
{
};

// Function Char_Player.Char_Player_C.EventScrollUp__DelegateSignature
struct AChar_Player_C_EventScrollUp__DelegateSignature_Params
{
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
