// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_AnimGraphRuntime_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function AnimGraphRuntime.KismetAnimationLibrary.K2_TwoBoneIK
// ()
// Parameters:
// struct FVector                 RootPos                        (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// struct FVector                 JointPos                       (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// struct FVector                 EndPos                         (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// struct FVector                 JointTarget                    (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// struct FVector                 Effector                       (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// struct FVector                 OutJointPos                    (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// struct FVector                 OutEndPos                      (Parm, OutParm, ZeroConstructor, IsPlainOldData)
// bool                           bAllowStretching               (Parm, ZeroConstructor, IsPlainOldData)
// float                          StartStretchRatio              (Parm, ZeroConstructor, IsPlainOldData)
// float                          MaxStretchScale                (Parm, ZeroConstructor, IsPlainOldData)

void UKismetAnimationLibrary::K2_TwoBoneIK(const struct FVector& RootPos, const struct FVector& JointPos, const struct FVector& EndPos, const struct FVector& JointTarget, const struct FVector& Effector, bool bAllowStretching, float StartStretchRatio, float MaxStretchScale, struct FVector* OutJointPos, struct FVector* OutEndPos)
{
	static auto fn = UObject::FindObject<UFunction>("Function AnimGraphRuntime.KismetAnimationLibrary.K2_TwoBoneIK");

	UKismetAnimationLibrary_K2_TwoBoneIK_Params params;
	params.RootPos = RootPos;
	params.JointPos = JointPos;
	params.EndPos = EndPos;
	params.JointTarget = JointTarget;
	params.Effector = Effector;
	params.bAllowStretching = bAllowStretching;
	params.StartStretchRatio = StartStretchRatio;
	params.MaxStretchScale = MaxStretchScale;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (OutJointPos != nullptr)
		*OutJointPos = params.OutJointPos;
	if (OutEndPos != nullptr)
		*OutEndPos = params.OutEndPos;
}


// Function AnimGraphRuntime.KismetAnimationLibrary.K2_MakePerlinNoiseVectorAndRemap
// ()
// Parameters:
// float                          X                              (Parm, ZeroConstructor, IsPlainOldData)
// float                          Y                              (Parm, ZeroConstructor, IsPlainOldData)
// float                          Z                              (Parm, ZeroConstructor, IsPlainOldData)
// float                          RangeOutMinX                   (Parm, ZeroConstructor, IsPlainOldData)
// float                          RangeOutMaxX                   (Parm, ZeroConstructor, IsPlainOldData)
// float                          RangeOutMinY                   (Parm, ZeroConstructor, IsPlainOldData)
// float                          RangeOutMaxY                   (Parm, ZeroConstructor, IsPlainOldData)
// float                          RangeOutMinZ                   (Parm, ZeroConstructor, IsPlainOldData)
// float                          RangeOutMaxZ                   (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector UKismetAnimationLibrary::K2_MakePerlinNoiseVectorAndRemap(float X, float Y, float Z, float RangeOutMinX, float RangeOutMaxX, float RangeOutMinY, float RangeOutMaxY, float RangeOutMinZ, float RangeOutMaxZ)
{
	static auto fn = UObject::FindObject<UFunction>("Function AnimGraphRuntime.KismetAnimationLibrary.K2_MakePerlinNoiseVectorAndRemap");

	UKismetAnimationLibrary_K2_MakePerlinNoiseVectorAndRemap_Params params;
	params.X = X;
	params.Y = Y;
	params.Z = Z;
	params.RangeOutMinX = RangeOutMinX;
	params.RangeOutMaxX = RangeOutMaxX;
	params.RangeOutMinY = RangeOutMinY;
	params.RangeOutMaxY = RangeOutMaxY;
	params.RangeOutMinZ = RangeOutMinZ;
	params.RangeOutMaxZ = RangeOutMaxZ;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function AnimGraphRuntime.KismetAnimationLibrary.K2_MakePerlinNoiseAndRemap
// ()
// Parameters:
// float                          Value                          (Parm, ZeroConstructor, IsPlainOldData)
// float                          RangeOutMin                    (Parm, ZeroConstructor, IsPlainOldData)
// float                          RangeOutMax                    (Parm, ZeroConstructor, IsPlainOldData)
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UKismetAnimationLibrary::K2_MakePerlinNoiseAndRemap(float Value, float RangeOutMin, float RangeOutMax)
{
	static auto fn = UObject::FindObject<UFunction>("Function AnimGraphRuntime.KismetAnimationLibrary.K2_MakePerlinNoiseAndRemap");

	UKismetAnimationLibrary_K2_MakePerlinNoiseAndRemap_Params params;
	params.Value = Value;
	params.RangeOutMin = RangeOutMin;
	params.RangeOutMax = RangeOutMax;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function AnimGraphRuntime.KismetAnimationLibrary.K2_LookAt
// ()
// Parameters:
// struct FTransform              CurrentTransform               (ConstParm, Parm, OutParm, ReferenceParm, IsPlainOldData)
// struct FVector                 TargetPosition                 (ConstParm, Parm, OutParm, ZeroConstructor, ReferenceParm, IsPlainOldData)
// struct FVector                 LookAtVector                   (Parm, ZeroConstructor, IsPlainOldData)
// bool                           bUseUpVector                   (Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 UpVector                       (Parm, ZeroConstructor, IsPlainOldData)
// float                          ClampConeInDegree              (Parm, ZeroConstructor, IsPlainOldData)
// struct FTransform              ReturnValue                    (Parm, OutParm, ReturnParm, IsPlainOldData)

struct FTransform UKismetAnimationLibrary::K2_LookAt(const struct FTransform& CurrentTransform, const struct FVector& TargetPosition, const struct FVector& LookAtVector, bool bUseUpVector, const struct FVector& UpVector, float ClampConeInDegree)
{
	static auto fn = UObject::FindObject<UFunction>("Function AnimGraphRuntime.KismetAnimationLibrary.K2_LookAt");

	UKismetAnimationLibrary_K2_LookAt_Params params;
	params.CurrentTransform = CurrentTransform;
	params.TargetPosition = TargetPosition;
	params.LookAtVector = LookAtVector;
	params.bUseUpVector = bUseUpVector;
	params.UpVector = UpVector;
	params.ClampConeInDegree = ClampConeInDegree;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function AnimGraphRuntime.KismetAnimationLibrary.K2_DistanceBetweenTwoSocketsAndMapRange
// ()
// Parameters:
// class USkeletalMeshComponent*  component                      (ConstParm, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// struct FName                   SocketOrBoneNameA              (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
// TEnumAsByte<ERelativeTransformSpace> SocketSpaceA                   (Parm, ZeroConstructor, IsPlainOldData)
// struct FName                   SocketOrBoneNameB              (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
// TEnumAsByte<ERelativeTransformSpace> SocketSpaceB                   (Parm, ZeroConstructor, IsPlainOldData)
// bool                           bRemapRange                    (Parm, ZeroConstructor, IsPlainOldData)
// float                          InRangeMin                     (Parm, ZeroConstructor, IsPlainOldData)
// float                          InRangeMax                     (Parm, ZeroConstructor, IsPlainOldData)
// float                          OutRangeMin                    (Parm, ZeroConstructor, IsPlainOldData)
// float                          OutRangeMax                    (Parm, ZeroConstructor, IsPlainOldData)
// float                          ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

float UKismetAnimationLibrary::K2_DistanceBetweenTwoSocketsAndMapRange(class USkeletalMeshComponent* component, const struct FName& SocketOrBoneNameA, TEnumAsByte<ERelativeTransformSpace> SocketSpaceA, const struct FName& SocketOrBoneNameB, TEnumAsByte<ERelativeTransformSpace> SocketSpaceB, bool bRemapRange, float InRangeMin, float InRangeMax, float OutRangeMin, float OutRangeMax)
{
	static auto fn = UObject::FindObject<UFunction>("Function AnimGraphRuntime.KismetAnimationLibrary.K2_DistanceBetweenTwoSocketsAndMapRange");

	UKismetAnimationLibrary_K2_DistanceBetweenTwoSocketsAndMapRange_Params params;
	params.component = component;
	params.SocketOrBoneNameA = SocketOrBoneNameA;
	params.SocketSpaceA = SocketSpaceA;
	params.SocketOrBoneNameB = SocketOrBoneNameB;
	params.SocketSpaceB = SocketSpaceB;
	params.bRemapRange = bRemapRange;
	params.InRangeMin = InRangeMin;
	params.InRangeMax = InRangeMax;
	params.OutRangeMin = OutRangeMin;
	params.OutRangeMax = OutRangeMax;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function AnimGraphRuntime.KismetAnimationLibrary.K2_DirectionBetweenSockets
// ()
// Parameters:
// class USkeletalMeshComponent*  component                      (ConstParm, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// struct FName                   SocketOrBoneNameFrom           (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
// struct FName                   SocketOrBoneNameTo             (ConstParm, Parm, ZeroConstructor, IsPlainOldData)
// struct FVector                 ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

struct FVector UKismetAnimationLibrary::K2_DirectionBetweenSockets(class USkeletalMeshComponent* component, const struct FName& SocketOrBoneNameFrom, const struct FName& SocketOrBoneNameTo)
{
	static auto fn = UObject::FindObject<UFunction>("Function AnimGraphRuntime.KismetAnimationLibrary.K2_DirectionBetweenSockets");

	UKismetAnimationLibrary_K2_DirectionBetweenSockets_Params params;
	params.component = component;
	params.SocketOrBoneNameFrom = SocketOrBoneNameFrom;
	params.SocketOrBoneNameTo = SocketOrBoneNameTo;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function AnimGraphRuntime.PlayMontageCallbackProxy.OnNotifyEndReceived
// ()
// Parameters:
// struct FName                   NotifyName                     (Parm, ZeroConstructor, IsPlainOldData)
// struct FBranchingPointNotifyPayload BranchingPointNotifyPayload    (ConstParm, Parm, OutParm, ReferenceParm)

void UPlayMontageCallbackProxy::OnNotifyEndReceived(const struct FName& NotifyName, const struct FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	static auto fn = UObject::FindObject<UFunction>("Function AnimGraphRuntime.PlayMontageCallbackProxy.OnNotifyEndReceived");

	UPlayMontageCallbackProxy_OnNotifyEndReceived_Params params;
	params.NotifyName = NotifyName;
	params.BranchingPointNotifyPayload = BranchingPointNotifyPayload;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function AnimGraphRuntime.PlayMontageCallbackProxy.OnNotifyBeginReceived
// ()
// Parameters:
// struct FName                   NotifyName                     (Parm, ZeroConstructor, IsPlainOldData)
// struct FBranchingPointNotifyPayload BranchingPointNotifyPayload    (ConstParm, Parm, OutParm, ReferenceParm)

void UPlayMontageCallbackProxy::OnNotifyBeginReceived(const struct FName& NotifyName, const struct FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	static auto fn = UObject::FindObject<UFunction>("Function AnimGraphRuntime.PlayMontageCallbackProxy.OnNotifyBeginReceived");

	UPlayMontageCallbackProxy_OnNotifyBeginReceived_Params params;
	params.NotifyName = NotifyName;
	params.BranchingPointNotifyPayload = BranchingPointNotifyPayload;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function AnimGraphRuntime.PlayMontageCallbackProxy.OnMontageEnded
// ()
// Parameters:
// class UAnimMontage*            Montage                        (Parm, ZeroConstructor, IsPlainOldData)
// bool                           bInterrupted                   (Parm, ZeroConstructor, IsPlainOldData)

void UPlayMontageCallbackProxy::OnMontageEnded(class UAnimMontage* Montage, bool bInterrupted)
{
	static auto fn = UObject::FindObject<UFunction>("Function AnimGraphRuntime.PlayMontageCallbackProxy.OnMontageEnded");

	UPlayMontageCallbackProxy_OnMontageEnded_Params params;
	params.Montage = Montage;
	params.bInterrupted = bInterrupted;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function AnimGraphRuntime.PlayMontageCallbackProxy.OnMontageBlendingOut
// ()
// Parameters:
// class UAnimMontage*            Montage                        (Parm, ZeroConstructor, IsPlainOldData)
// bool                           bInterrupted                   (Parm, ZeroConstructor, IsPlainOldData)

void UPlayMontageCallbackProxy::OnMontageBlendingOut(class UAnimMontage* Montage, bool bInterrupted)
{
	static auto fn = UObject::FindObject<UFunction>("Function AnimGraphRuntime.PlayMontageCallbackProxy.OnMontageBlendingOut");

	UPlayMontageCallbackProxy_OnMontageBlendingOut_Params params;
	params.Montage = Montage;
	params.bInterrupted = bInterrupted;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function AnimGraphRuntime.PlayMontageCallbackProxy.CreateProxyObjectForPlayMontage
// ()
// Parameters:
// class USkeletalMeshComponent*  InSkeletalMeshComponent        (Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class UAnimMontage*            MontageToPlay                  (Parm, ZeroConstructor, IsPlainOldData)
// float                          PlayRate                       (Parm, ZeroConstructor, IsPlainOldData)
// float                          StartingPosition               (Parm, ZeroConstructor, IsPlainOldData)
// struct FName                   StartingSection                (Parm, ZeroConstructor, IsPlainOldData)
// class UPlayMontageCallbackProxy* ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

class UPlayMontageCallbackProxy* UPlayMontageCallbackProxy::CreateProxyObjectForPlayMontage(class USkeletalMeshComponent* InSkeletalMeshComponent, class UAnimMontage* MontageToPlay, float PlayRate, float StartingPosition, const struct FName& StartingSection)
{
	static auto fn = UObject::FindObject<UFunction>("Function AnimGraphRuntime.PlayMontageCallbackProxy.CreateProxyObjectForPlayMontage");

	UPlayMontageCallbackProxy_CreateProxyObjectForPlayMontage_Params params;
	params.InSkeletalMeshComponent = InSkeletalMeshComponent;
	params.MontageToPlay = MontageToPlay;
	params.PlayRate = PlayRate;
	params.StartingPosition = StartingPosition;
	params.StartingSection = StartingSection;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
