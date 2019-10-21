#pragma once

// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_AkAudio_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function AkAudio.AkAcousticPortal.OpenPortal
struct AAkAcousticPortal_OpenPortal_Params
{
};

// Function AkAudio.AkAcousticPortal.GetCurrentState
struct AAkAcousticPortal_GetCurrentState_Params
{
	EAkAcousticPortalState                             ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkAcousticPortal.ClosePortal
struct AAkAcousticPortal_ClosePortal_Params
{
};

// Function AkAudio.AkAmbientSound.StopAmbientSound
struct AAkAmbientSound_StopAmbientSound_Params
{
};

// Function AkAudio.AkAmbientSound.StartAmbientSound
struct AAkAmbientSound_StartAmbientSound_Params
{
};

// Function AkAudio.AkComponent.UseReverbVolumes
struct UAkComponent_UseReverbVolumes_Params
{
	bool                                               inUseReverbVolumes;                                       // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkComponent.UseEarlyReflections
struct UAkComponent_UseEarlyReflections_Params
{
	class UAkAuxBus*                                   AuxBus;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                Order;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              BusSendGain;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              MaxPathLength;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               SpotReflectors;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	class FString                                      AuxBusName;                                               // (Parm, ZeroConstructor)
};

// Function AkAudio.AkComponent.Stop
struct UAkComponent_Stop_Params
{
};

// Function AkAudio.AkComponent.SetSwitch
struct UAkComponent_SetSwitch_Params
{
	class FString                                      SwitchGroup;                                              // (Parm, ZeroConstructor)
	class FString                                      SwitchState;                                              // (Parm, ZeroConstructor)
};

// Function AkAudio.AkComponent.SetStopWhenOwnerDestroyed
struct UAkComponent_SetStopWhenOwnerDestroyed_Params
{
	bool                                               bStopWhenOwnerDestroyed;                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkComponent.SetRTPCValue
struct UAkComponent_SetRTPCValue_Params
{
	class FString                                      RTPC;                                                     // (Parm, ZeroConstructor)
	float                                              Value;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                InterpolationTimeMs;                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkComponent.SetOutputBusVolume
struct UAkComponent_SetOutputBusVolume_Params
{
	float                                              BusVolume;                                                // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkComponent.SetMultiplePositions
struct UAkComponent_SetMultiplePositions_Params
{
	TArray<struct FVector>                             Positions;                                                // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	EAkMultiPositionType                               MultiPositionType;                                        // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkComponent.SetListeners
struct UAkComponent_SetListeners_Params
{
	TArray<class UAkComponent*>                        Listeners;                                                // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function AkAudio.AkComponent.SetAttenuationScalingFactor
struct UAkComponent_SetAttenuationScalingFactor_Params
{
	float                                              Value;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkComponent.SeekOnEventBySeconds
struct UAkComponent_SeekOnEventBySeconds_Params
{
	class UAkAudioEvent*                               AkEvent;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Seconds;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               SeekToNearestMarker;                                      // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                playingId;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkComponent.SeekOnEventByPct
struct UAkComponent_SeekOnEventByPct_Params
{
	class UAkAudioEvent*                               AkEvent;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Percent;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               SeekToNearestMarker;                                      // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                playingId;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkComponent.PostTrigger
struct UAkComponent_PostTrigger_Params
{
	class FString                                      Trigger;                                                  // (Parm, ZeroConstructor)
};

// Function AkAudio.AkComponent.PostAssociatedAkEvent
struct UAkComponent_PostAssociatedAkEvent_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkComponent.PostAkEvent
struct UAkComponent_PostAkEvent_Params
{
	class UAkAudioEvent*                               AkEvent;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkComponent.IsPlaying
struct UAkComponent_IsPlaying_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkComponent.GetAttenuationRadius
struct UAkComponent_GetAttenuationRadius_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkAudioInputComponent.PostAssociatedAudioInputEvent
struct UAkAudioInputComponent_PostAssociatedAudioInputEvent_Params
{
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkCheckBox.SetIsChecked
struct UAkCheckBox_SetIsChecked_Params
{
	bool                                               InIsChecked;                                              // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkCheckBox.SetCheckedState
struct UAkCheckBox_SetCheckedState_Params
{
	ECheckBoxState                                     InCheckedState;                                           // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkCheckBox.SetAkItemId
struct UAkCheckBox_SetAkItemId_Params
{
	struct FGuid                                       ItemId;                                                   // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
};

// Function AkAudio.AkCheckBox.SetAkBoolProperty
struct UAkCheckBox_SetAkBoolProperty_Params
{
	class FString                                      ItemProperty;                                             // (Parm, ZeroConstructor)
};

// Function AkAudio.AkCheckBox.IsPressed
struct UAkCheckBox_IsPressed_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkCheckBox.IsChecked
struct UAkCheckBox_IsChecked_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkCheckBox.GetCheckedState
struct UAkCheckBox_GetCheckedState_Params
{
	ECheckBoxState                                     ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkCheckBox.GetAkProperty
struct UAkCheckBox_GetAkProperty_Params
{
	class FString                                      ReturnValue;                                              // (ConstParm, Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function AkAudio.AkCheckBox.GetAkItemId
struct UAkCheckBox_GetAkItemId_Params
{
	struct FGuid                                       ReturnValue;                                              // (ConstParm, Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.UseReverbVolumes
struct UAkGameplayStatics_UseReverbVolumes_Params
{
	bool                                               inUseReverbVolumes;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      Actor;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.UseEarlyReflections
struct UAkGameplayStatics_UseEarlyReflections_Params
{
	class AActor*                                      Actor;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	class UAkAuxBus*                                   AuxBus;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                Order;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              BusSendGain;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              MaxPathLength;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               SpotReflectors;                                           // (Parm, ZeroConstructor, IsPlainOldData)
	class FString                                      AuxBusName;                                               // (Parm, ZeroConstructor)
};

// Function AkAudio.AkGameplayStatics.UnloadBankByName
struct UAkGameplayStatics_UnloadBankByName_Params
{
	class FString                                      BankName;                                                 // (Parm, ZeroConstructor)
};

// Function AkAudio.AkGameplayStatics.UnloadBankAsync
struct UAkGameplayStatics_UnloadBankAsync_Params
{
	class UAkAudioBank*                                Bank;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	struct FScriptDelegate                             BankUnloadedCallback;                                     // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function AkAudio.AkGameplayStatics.UnloadBank
struct UAkGameplayStatics_UnloadBank_Params
{
	class UAkAudioBank*                                Bank;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	class FString                                      BankName;                                                 // (Parm, ZeroConstructor)
	struct FLatentActionInfo                           LatentInfo;                                               // (Parm)
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.StopSounds
struct UAkGameplayStatics_StopSounds_Params
{
	class AActor*                                      Actor;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.StopProfilerCapture
struct UAkGameplayStatics_StopProfilerCapture_Params
{
};

// Function AkAudio.AkGameplayStatics.StopOutputCapture
struct UAkGameplayStatics_StopOutputCapture_Params
{
};

// Function AkAudio.AkGameplayStatics.StopAndDestroyComponent
struct UAkGameplayStatics_StopAndDestroyComponent_Params
{
	class UAkComponent*                                inComp;                                                   // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.StopAllSounds
struct UAkGameplayStatics_StopAllSounds_Params
{
};

// Function AkAudio.AkGameplayStatics.StopAllAmbientSounds
struct UAkGameplayStatics_StopAllAmbientSounds_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.StartProfilerCapture
struct UAkGameplayStatics_StartProfilerCapture_Params
{
	class FString                                      Filename;                                                 // (Parm, ZeroConstructor)
};

// Function AkAudio.AkGameplayStatics.StartOutputCapture
struct UAkGameplayStatics_StartOutputCapture_Params
{
	class FString                                      Filename;                                                 // (Parm, ZeroConstructor)
};

// Function AkAudio.AkGameplayStatics.StartAllAmbientSounds
struct UAkGameplayStatics_StartAllAmbientSounds_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.SpawnAkComponentAtLocation
struct UAkGameplayStatics_SpawnAkComponentAtLocation_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class UAkAudioEvent*                               AkEvent;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     Location;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	struct FRotator                                    Orientation;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               AutoPost;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	class UAkComponent*                                ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.SetSwitch
struct UAkGameplayStatics_SetSwitch_Params
{
	struct FName                                       SwitchGroup;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	struct FName                                       SwitchState;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      Actor;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.SetState
struct UAkGameplayStatics_SetState_Params
{
	struct FName                                       StateGroup;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	struct FName                                       State;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.SetSpeakerAngles
struct UAkGameplayStatics_SetSpeakerAngles_Params
{
	TArray<float>                                      SpeakerAngles;                                            // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	float                                              HeightAngle;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	class FString                                      DeviceShareset;                                           // (Parm, ZeroConstructor)
};

// Function AkAudio.AkGameplayStatics.SetPanningRule
struct UAkGameplayStatics_SetPanningRule_Params
{
	EPanningRule                                       PanRule;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.SetOutputBusVolume
struct UAkGameplayStatics_SetOutputBusVolume_Params
{
	float                                              BusVolume;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      Actor;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.SetOcclusionScalingFactor
struct UAkGameplayStatics_SetOcclusionScalingFactor_Params
{
	float                                              ScalingFactor;                                            // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.SetOcclusionRefreshInterval
struct UAkGameplayStatics_SetOcclusionRefreshInterval_Params
{
	float                                              RefreshInterval;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      Actor;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.SetMultiplePositions
struct UAkGameplayStatics_SetMultiplePositions_Params
{
	class UAkComponent*                                GameObjectAkComponent;                                    // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	TArray<struct FVector>                             Positions;                                                // (Parm, ZeroConstructor)
	EAkMultiPositionType                               MultiPositionType;                                        // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.SetMultipleChannelEmitterPositions
struct UAkGameplayStatics_SetMultipleChannelEmitterPositions_Params
{
	class UAkComponent*                                GameObjectAkComponent;                                    // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	TArray<EAkChannelConfiguration>                    ChannelMasks;                                             // (Parm, ZeroConstructor)
	TArray<struct FTransform>                          Positions;                                                // (Parm, ZeroConstructor)
	EAkMultiPositionType                               MultiPositionType;                                        // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.SetGlobalRTPCValue
struct UAkGameplayStatics_SetGlobalRTPCValue_Params
{
	struct FName                                       RTPC;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Value;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                InterpolationTimeMs;                                      // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.SetBusConfig
struct UAkGameplayStatics_SetBusConfig_Params
{
	class FString                                      BusName;                                                  // (Parm, ZeroConstructor)
	EAkChannelConfiguration                            ChannelConfiguration;                                     // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.SetActorRTPCValue
struct UAkGameplayStatics_SetActorRTPCValue_Params
{
	struct FName                                       RTPC;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              Value;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                InterpolationTimeMs;                                      // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      Actor;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.PostTrigger
struct UAkGameplayStatics_PostTrigger_Params
{
	struct FName                                       Trigger;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      Actor;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.PostAkEventAttached
struct UAkGameplayStatics_PostAkEventAttached_Params
{
	class UAkAudioEvent*                               AkEvent;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class USceneComponent*                             SceneComp;                                                // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FName                                       Socket;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bStopWhenAttachedToDestroyed;                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UAkComponent*                                ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.PostAkEventAtLocation
struct UAkGameplayStatics_PostAkEventAtLocation_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	class UAkAudioEvent*                               AkEvent;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     Location;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	struct FRotator                                    Orientation;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	class UAkComponent*                                ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.PostAkEvent
struct UAkGameplayStatics_PostAkEvent_Params
{
	class UAkAudioEvent*                               AkEvent;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	class AActor*                                      Actor;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bStopWhenAttachedToDestroyed;                             // (Parm, ZeroConstructor, IsPlainOldData)
	class UAkComponent*                                ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.LoadInitBank
struct UAkGameplayStatics_LoadInitBank_Params
{
};

// Function AkAudio.AkGameplayStatics.LoadBanks
struct UAkGameplayStatics_LoadBanks_Params
{
	TArray<class UAkAudioBank*>                        SoundBanks;                                               // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	bool                                               SynchronizeSoundBanks;                                    // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.LoadBankByName
struct UAkGameplayStatics_LoadBankByName_Params
{
	class FString                                      BankName;                                                 // (Parm, ZeroConstructor)
};

// Function AkAudio.AkGameplayStatics.LoadBankAsync
struct UAkGameplayStatics_LoadBankAsync_Params
{
	class UAkAudioBank*                                Bank;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	struct FScriptDelegate                             BankLoadedCallback;                                       // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
};

// Function AkAudio.AkGameplayStatics.LoadBank
struct UAkGameplayStatics_LoadBank_Params
{
	class UAkAudioBank*                                Bank;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	class FString                                      BankName;                                                 // (Parm, ZeroConstructor)
	struct FLatentActionInfo                           LatentInfo;                                               // (Parm)
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.IsGame
struct UAkGameplayStatics_IsGame_Params
{
	class UObject*                                     WorldContextObject;                                       // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.IsEditor
struct UAkGameplayStatics_IsEditor_Params
{
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.GetSpeakerAngles
struct UAkGameplayStatics_GetSpeakerAngles_Params
{
	TArray<float>                                      SpeakerAngles;                                            // (Parm, OutParm, ZeroConstructor)
	float                                              HeightAngle;                                              // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	class FString                                      DeviceShareset;                                           // (Parm, ZeroConstructor)
};

// Function AkAudio.AkGameplayStatics.GetOcclusionScalingFactor
struct UAkGameplayStatics_GetOcclusionScalingFactor_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.GetGlobalRTPCValue
struct UAkGameplayStatics_GetGlobalRTPCValue_Params
{
	struct FName                                       RTPC;                                                     // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.GetAkComponentAttached
struct UAkGameplayStatics_GetAkComponentAttached_Params
{
	class USceneComponent*                             AttachToComponent;                                        // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	struct FName                                       Socket;                                                   // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bAutoCreate;                                              // (Parm, ZeroConstructor, IsPlainOldData)
	class UAkComponent*                                ReturnValue;                                              // (ExportObject, Parm, OutParm, ZeroConstructor, ReturnParm, InstancedReference, IsPlainOldData)
};

// Function AkAudio.AkGameplayStatics.ClearBanks
struct UAkGameplayStatics_ClearBanks_Params
{
};

// Function AkAudio.AkGameplayStatics.AddOutputCaptureMarker
struct UAkGameplayStatics_AddOutputCaptureMarker_Params
{
	class FString                                      MarkerText;                                               // (Parm, ZeroConstructor)
};

// Function AkAudio.AkMIDIEventCallbackInfo.GetType
struct UAkMIDIEventCallbackInfo_GetType_Params
{
	EAkMidiEventType                                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkMIDIEventCallbackInfo.GetProgramChange
struct UAkMIDIEventCallbackInfo_GetProgramChange_Params
{
	struct FAkMidiProgramChange                        AsProgramChange;                                          // (Parm, OutParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkMIDIEventCallbackInfo.GetPitchBend
struct UAkMIDIEventCallbackInfo_GetPitchBend_Params
{
	struct FAkMidiPitchBend                            AsPitchBend;                                              // (Parm, OutParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkMIDIEventCallbackInfo.GetNoteOn
struct UAkMIDIEventCallbackInfo_GetNoteOn_Params
{
	struct FAkMidiNoteOnOff                            AsNoteOn;                                                 // (Parm, OutParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkMIDIEventCallbackInfo.GetNoteOff
struct UAkMIDIEventCallbackInfo_GetNoteOff_Params
{
	struct FAkMidiNoteOnOff                            AsNoteOff;                                                // (Parm, OutParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkMIDIEventCallbackInfo.GetNoteAftertouch
struct UAkMIDIEventCallbackInfo_GetNoteAftertouch_Params
{
	struct FAkMidiNoteAftertouch                       AsNoteAftertouch;                                         // (Parm, OutParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkMIDIEventCallbackInfo.GetGeneric
struct UAkMIDIEventCallbackInfo_GetGeneric_Params
{
	struct FAkMidiGeneric                              AsGeneric;                                                // (Parm, OutParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkMIDIEventCallbackInfo.GetChannelAftertouch
struct UAkMIDIEventCallbackInfo_GetChannelAftertouch_Params
{
	struct FAkMidiChannelAftertouch                    AsChannelAftertouch;                                      // (Parm, OutParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkMIDIEventCallbackInfo.GetChannel
struct UAkMIDIEventCallbackInfo_GetChannel_Params
{
	unsigned char                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkMIDIEventCallbackInfo.GetCc
struct UAkMIDIEventCallbackInfo_GetCc_Params
{
	struct FAkMidiCc                                   AsCc;                                                     // (Parm, OutParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkItemBoolPropertiesConv.Conv_FAkBoolPropertyToControlToText
struct UAkItemBoolPropertiesConv_Conv_FAkBoolPropertyToControlToText_Params
{
	struct FAkBoolPropertyToControl                    INAkBoolPropertyToControl;                                // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function AkAudio.AkItemBoolPropertiesConv.Conv_FAkBoolPropertyToControlToString
struct UAkItemBoolPropertiesConv_Conv_FAkBoolPropertyToControlToString_Params
{
	struct FAkBoolPropertyToControl                    INAkBoolPropertyToControl;                                // (ConstParm, Parm, OutParm, ReferenceParm)
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function AkAudio.AkItemBoolProperties.SetSearchText
struct UAkItemBoolProperties_SetSearchText_Params
{
	class FString                                      newText;                                                  // (Parm, ZeroConstructor)
};

// Function AkAudio.AkItemBoolProperties.GetSelectedProperty
struct UAkItemBoolProperties_GetSelectedProperty_Params
{
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function AkAudio.AkItemBoolProperties.GetSearchText
struct UAkItemBoolProperties_GetSearchText_Params
{
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function AkAudio.AkItemPropertiesConv.Conv_FAkPropertyToControlToText
struct UAkItemPropertiesConv_Conv_FAkPropertyToControlToText_Params
{
	struct FAkPropertyToControl                        INAkPropertyToControl;                                    // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function AkAudio.AkItemPropertiesConv.Conv_FAkPropertyToControlToString
struct UAkItemPropertiesConv_Conv_FAkPropertyToControlToString_Params
{
	struct FAkPropertyToControl                        INAkPropertyToControl;                                    // (ConstParm, Parm, OutParm, ReferenceParm)
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function AkAudio.AkItemProperties.SetSearchText
struct UAkItemProperties_SetSearchText_Params
{
	class FString                                      newText;                                                  // (Parm, ZeroConstructor)
};

// Function AkAudio.AkItemProperties.GetSelectedProperty
struct UAkItemProperties_GetSelectedProperty_Params
{
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function AkAudio.AkItemProperties.GetSearchText
struct UAkItemProperties_GetSearchText_Params
{
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function AkAudio.AkObject.SetSwitch
struct UAkObject_SetSwitch_Params
{
	class FString                                      SwitchGroup;                                              // (Parm, ZeroConstructor)
	class FString                                      SwitchState;                                              // (Parm, ZeroConstructor)
};

// Function AkAudio.AkObject.SetRTPCValue
struct UAkObject_SetRTPCValue_Params
{
	class FString                                      RTPC;                                                     // (Parm, ZeroConstructor)
	float                                              Value;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                InterpolationTime;                                        // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkObject.PostEvent
struct UAkObject_PostEvent_Params
{
	class UAkAudioEvent*                               AkEvent;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkSlider.SetValue
struct UAkSlider_SetValue_Params
{
	float                                              InValue;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkSlider.SetStepSize
struct UAkSlider_SetStepSize_Params
{
	float                                              InValue;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkSlider.SetSliderHandleColor
struct UAkSlider_SetSliderHandleColor_Params
{
	struct FLinearColor                                InValue;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkSlider.SetSliderBarColor
struct UAkSlider_SetSliderBarColor_Params
{
	struct FLinearColor                                InValue;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkSlider.SetLocked
struct UAkSlider_SetLocked_Params
{
	bool                                               InValue;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkSlider.SetIndentHandle
struct UAkSlider_SetIndentHandle_Params
{
	bool                                               InValue;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkSlider.SetAkSliderItemProperty
struct UAkSlider_SetAkSliderItemProperty_Params
{
	class FString                                      ItemProperty;                                             // (Parm, ZeroConstructor)
};

// Function AkAudio.AkSlider.SetAkSliderItemId
struct UAkSlider_SetAkSliderItemId_Params
{
	struct FGuid                                       ItemId;                                                   // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
};

// Function AkAudio.AkSlider.GetValue
struct UAkSlider_GetValue_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkSlider.GetAkSliderItemProperty
struct UAkSlider_GetAkSliderItemProperty_Params
{
	class FString                                      ReturnValue;                                              // (ConstParm, Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function AkAudio.AkSlider.GetAkSliderItemId
struct UAkSlider_GetAkSliderItemId_Params
{
	struct FGuid                                       ReturnValue;                                              // (ConstParm, Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkSurfaceReflectorSetComponent.UpdateSurfaceReflectorSet
struct UAkSurfaceReflectorSetComponent_UpdateSurfaceReflectorSet_Params
{
};

// Function AkAudio.AkSurfaceReflectorSetComponent.SendSurfaceReflectorSet
struct UAkSurfaceReflectorSetComponent_SendSurfaceReflectorSet_Params
{
};

// Function AkAudio.AkSurfaceReflectorSetComponent.RemoveSurfaceReflectorSet
struct UAkSurfaceReflectorSetComponent_RemoveSurfaceReflectorSet_Params
{
};

// Function AkAudio.AkWaapiCalls.UNSUBSCRIBE
struct UAkWaapiCalls_UNSUBSCRIBE_Params
{
	struct FAkWaapiSubscriptionId                      SubscriptionId;                                           // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               UnsubscriptionDone;                                       // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	struct FAKWaapiJsonObject                          ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function AkAudio.AkWaapiCalls.SubscribeToWaapi
struct UAkWaapiCalls_SubscribeToWaapi_Params
{
	struct FAkWaapiUri                                 WaapiUri;                                                 // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FAKWaapiJsonObject                          WaapiOptions;                                             // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FScriptDelegate                             Callback;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	struct FAkWaapiSubscriptionId                      SubscriptionId;                                           // (Parm, OutParm)
	bool                                               SubscriptionDone;                                         // (Parm, OutParm, ZeroConstructor, IsPlainOldData)
	struct FAKWaapiJsonObject                          ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function AkAudio.AkWaapiCalls.SetSubscriptionID
struct UAkWaapiCalls_SetSubscriptionID_Params
{
	struct FAkWaapiSubscriptionId                      Subscription;                                             // (ConstParm, Parm, OutParm, ReferenceParm)
	int                                                ID;                                                       // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AkAudio.AkWaapiCalls.RegisterWaapiProjectLoadedCallback
struct UAkWaapiCalls_RegisterWaapiProjectLoadedCallback_Params
{
	struct FScriptDelegate                             Callback;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkWaapiCalls.RegisterWaapiConnectionLostCallback
struct UAkWaapiCalls_RegisterWaapiConnectionLostCallback_Params
{
	struct FScriptDelegate                             Callback;                                                 // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkWaapiCalls.GetSubscriptionID
struct UAkWaapiCalls_GetSubscriptionID_Params
{
	struct FAkWaapiSubscriptionId                      Subscription;                                             // (ConstParm, Parm, OutParm, ReferenceParm)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkWaapiCalls.Conv_FAkWaapiSubscriptionIdToText
struct UAkWaapiCalls_Conv_FAkWaapiSubscriptionIdToText_Params
{
	struct FAkWaapiSubscriptionId                      INAkWaapiSubscriptionId;                                  // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function AkAudio.AkWaapiCalls.Conv_FAkWaapiSubscriptionIdToString
struct UAkWaapiCalls_Conv_FAkWaapiSubscriptionIdToString_Params
{
	struct FAkWaapiSubscriptionId                      INAkWaapiSubscriptionId;                                  // (ConstParm, Parm, OutParm, ReferenceParm)
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function AkAudio.AkWaapiCalls.CallWaapi
struct UAkWaapiCalls_CallWaapi_Params
{
	struct FAkWaapiUri                                 WaapiUri;                                                 // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FAKWaapiJsonObject                          WaapiArgs;                                                // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FAKWaapiJsonObject                          WaapiOptions;                                             // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FAKWaapiJsonObject                          ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function AkAudio.SAkWaapiFieldNamesConv.Conv_FAkWaapiFieldNamesToText
struct USAkWaapiFieldNamesConv_Conv_FAkWaapiFieldNamesToText_Params
{
	struct FAkWaapiFieldNames                          INAkWaapiFieldNames;                                      // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function AkAudio.SAkWaapiFieldNamesConv.Conv_FAkWaapiFieldNamesToString
struct USAkWaapiFieldNamesConv_Conv_FAkWaapiFieldNamesToString_Params
{
	struct FAkWaapiFieldNames                          INAkWaapiFieldNames;                                      // (ConstParm, Parm, OutParm, ReferenceParm)
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function AkAudio.AkWaapiJsonManager.SetStringField
struct UAkWaapiJsonManager_SetStringField_Params
{
	struct FAkWaapiFieldNames                          FieldName;                                                // (ConstParm, Parm, OutParm, ReferenceParm)
	class FString                                      FieldValue;                                               // (Parm, ZeroConstructor)
	struct FAKWaapiJsonObject                          Target;                                                   // (Parm)
	struct FAKWaapiJsonObject                          ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function AkAudio.AkWaapiJsonManager.SetObjectField
struct UAkWaapiJsonManager_SetObjectField_Params
{
	struct FAkWaapiFieldNames                          FieldName;                                                // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FAKWaapiJsonObject                          FieldValue;                                               // (Parm)
	struct FAKWaapiJsonObject                          Target;                                                   // (Parm)
	struct FAKWaapiJsonObject                          ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function AkAudio.AkWaapiJsonManager.SetNumberField
struct UAkWaapiJsonManager_SetNumberField_Params
{
	struct FAkWaapiFieldNames                          FieldName;                                                // (ConstParm, Parm, OutParm, ReferenceParm)
	float                                              FieldValue;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	struct FAKWaapiJsonObject                          Target;                                                   // (Parm)
	struct FAKWaapiJsonObject                          ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function AkAudio.AkWaapiJsonManager.SetBoolField
struct UAkWaapiJsonManager_SetBoolField_Params
{
	struct FAkWaapiFieldNames                          FieldName;                                                // (ConstParm, Parm, OutParm, ReferenceParm)
	bool                                               FieldValue;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	struct FAKWaapiJsonObject                          Target;                                                   // (Parm)
	struct FAKWaapiJsonObject                          ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function AkAudio.AkWaapiJsonManager.SetArrayStringFields
struct UAkWaapiJsonManager_SetArrayStringFields_Params
{
	struct FAkWaapiFieldNames                          FieldName;                                                // (ConstParm, Parm, OutParm, ReferenceParm)
	TArray<class FString>                              FieldStringValues;                                        // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	struct FAKWaapiJsonObject                          Target;                                                   // (Parm)
	struct FAKWaapiJsonObject                          ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function AkAudio.AkWaapiJsonManager.SetArrayObjectFields
struct UAkWaapiJsonManager_SetArrayObjectFields_Params
{
	struct FAkWaapiFieldNames                          FieldName;                                                // (ConstParm, Parm, OutParm, ReferenceParm)
	TArray<struct FAKWaapiJsonObject>                  FieldObjectValues;                                        // (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm)
	struct FAKWaapiJsonObject                          Target;                                                   // (Parm)
	struct FAKWaapiJsonObject                          ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function AkAudio.AkWaapiJsonManager.GetStringField
struct UAkWaapiJsonManager_GetStringField_Params
{
	struct FAkWaapiFieldNames                          FieldName;                                                // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FAKWaapiJsonObject                          Target;                                                   // (Parm)
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function AkAudio.AkWaapiJsonManager.GetObjectField
struct UAkWaapiJsonManager_GetObjectField_Params
{
	struct FAkWaapiFieldNames                          FieldName;                                                // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FAKWaapiJsonObject                          Target;                                                   // (Parm)
	struct FAKWaapiJsonObject                          ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function AkAudio.AkWaapiJsonManager.GetNumberField
struct UAkWaapiJsonManager_GetNumberField_Params
{
	struct FAkWaapiFieldNames                          FieldName;                                                // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FAKWaapiJsonObject                          Target;                                                   // (Parm)
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkWaapiJsonManager.GetIntegerField
struct UAkWaapiJsonManager_GetIntegerField_Params
{
	struct FAkWaapiFieldNames                          FieldName;                                                // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FAKWaapiJsonObject                          Target;                                                   // (Parm)
	int                                                ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkWaapiJsonManager.GetBoolField
struct UAkWaapiJsonManager_GetBoolField_Params
{
	struct FAkWaapiFieldNames                          FieldName;                                                // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FAKWaapiJsonObject                          Target;                                                   // (Parm)
	bool                                               ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

// Function AkAudio.AkWaapiJsonManager.GetArrayField
struct UAkWaapiJsonManager_GetArrayField_Params
{
	struct FAkWaapiFieldNames                          FieldName;                                                // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FAKWaapiJsonObject                          Target;                                                   // (Parm)
	TArray<struct FAKWaapiJsonObject>                  ReturnValue;                                              // (ConstParm, Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function AkAudio.AkWaapiJsonManager.Conv_FAKWaapiJsonObjectToText
struct UAkWaapiJsonManager_Conv_FAKWaapiJsonObjectToText_Params
{
	struct FAKWaapiJsonObject                          INAKWaapiJsonObject;                                      // (Parm)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function AkAudio.AkWaapiJsonManager.Conv_FAKWaapiJsonObjectToString
struct UAkWaapiJsonManager_Conv_FAKWaapiJsonObjectToString_Params
{
	struct FAKWaapiJsonObject                          INAKWaapiJsonObject;                                      // (Parm)
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function AkAudio.AkWaapiUriConv.Conv_FAkWaapiUriToText
struct UAkWaapiUriConv_Conv_FAkWaapiUriToText_Params
{
	struct FAkWaapiUri                                 INAkWaapiUri;                                             // (ConstParm, Parm, OutParm, ReferenceParm)
	struct FText                                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function AkAudio.AkWaapiUriConv.Conv_FAkWaapiUriToString
struct UAkWaapiUriConv_Conv_FAkWaapiUriToString_Params
{
	struct FAkWaapiUri                                 INAkWaapiUri;                                             // (ConstParm, Parm, OutParm, ReferenceParm)
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

// Function AkAudio.AkWwiseTree.SetSearchText
struct UAkWwiseTree_SetSearchText_Params
{
	class FString                                      newText;                                                  // (Parm, ZeroConstructor)
};

// Function AkAudio.AkWwiseTree.GetSelectedItem
struct UAkWwiseTree_GetSelectedItem_Params
{
	struct FAkWwiseObjectDetails                       ReturnValue;                                              // (Parm, OutParm, ReturnParm)
};

// Function AkAudio.AkWwiseTree.GetSearchText
struct UAkWwiseTree_GetSearchText_Params
{
	class FString                                      ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
