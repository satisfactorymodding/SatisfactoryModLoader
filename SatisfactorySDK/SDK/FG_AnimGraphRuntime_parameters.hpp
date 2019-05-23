#pragma once

// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_AnimGraphRuntime_classes.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Parameters
//---------------------------------------------------------------------------

// Function AnimGraphRuntime.KismetAnimationLibrary.K2_TwoBoneIK
struct UKismetAnimationLibrary_K2_TwoBoneIK_Params
{
	struct FVector                                     RootPos;                                                  // (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
	struct FVector                                     JointPos;                                                 // (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
	struct FVector                                     EndPos;                                                   // (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
	struct FVector                                     JointTarget;                                              // (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
	struct FVector                                     Effector;                                                 // (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
	struct FVector                                     OutJointPos;                                              // (Parm, OutParm, IsPlainOldData)
	struct FVector                                     OutEndPos;                                                // (Parm, OutParm, IsPlainOldData)
	bool                                               bAllowStretching;                                         // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              StartStretchRatio;                                        // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              MaxStretchScale;                                          // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AnimGraphRuntime.KismetAnimationLibrary.K2_LookAt
struct UKismetAnimationLibrary_K2_LookAt_Params
{
	struct FTransform                                  CurrentTransform;                                         // (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
	struct FVector                                     TargetPosition;                                           // (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
	struct FVector                                     LookAtVector;                                             // (Parm, IsPlainOldData)
	bool                                               bUseUpVector;                                             // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector                                     UpVector;                                                 // (Parm, IsPlainOldData)
	float                                              ClampConeInDegree;                                        // (Parm, ZeroConstructor, IsPlainOldData)
	struct FTransform                                  ReturnValue;                                              // (Parm, OutParm, ReturnParm, IsPlainOldData)
};

// Function AnimGraphRuntime.PlayMontageCallbackProxy.OnNotifyEndReceived
struct UPlayMontageCallbackProxy_OnNotifyEndReceived_Params
{
	struct FName                                       NotifyName;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBranchingPointNotifyPayload                BranchingPointNotifyPayload;                              // (ConstParm, Parm, OutParm, ReferenceParm)
};

// Function AnimGraphRuntime.PlayMontageCallbackProxy.OnNotifyBeginReceived
struct UPlayMontageCallbackProxy_OnNotifyBeginReceived_Params
{
	struct FName                                       NotifyName;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	struct FBranchingPointNotifyPayload                BranchingPointNotifyPayload;                              // (ConstParm, Parm, OutParm, ReferenceParm)
};

// Function AnimGraphRuntime.PlayMontageCallbackProxy.OnMontageEnded
struct UPlayMontageCallbackProxy_OnMontageEnded_Params
{
	class UAnimMontage*                                Montage;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bInterrupted;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AnimGraphRuntime.PlayMontageCallbackProxy.OnMontageBlendingOut
struct UPlayMontageCallbackProxy_OnMontageBlendingOut_Params
{
	class UAnimMontage*                                Montage;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bInterrupted;                                             // (Parm, ZeroConstructor, IsPlainOldData)
};

// Function AnimGraphRuntime.PlayMontageCallbackProxy.CreateProxyObjectForPlayMontage
struct UPlayMontageCallbackProxy_CreateProxyObjectForPlayMontage_Params
{
	class USkeletalMeshComponent*                      InSkeletalMeshComponent;                                  // (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
	class UAnimMontage*                                MontageToPlay;                                            // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              PlayRate;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	float                                              StartingPosition;                                         // (Parm, ZeroConstructor, IsPlainOldData)
	struct FName                                       StartingSection;                                          // (Parm, ZeroConstructor, IsPlainOldData)
	class UPlayMontageCallbackProxy*                   ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
