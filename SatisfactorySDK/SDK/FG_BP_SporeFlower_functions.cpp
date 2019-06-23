// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_SporeFlower_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_SporeFlower.BP_SporeFlower_C.SetTickStatus
// ()
// Parameters:
// bool                           doTick                         (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_SporeFlower_C::SetTickStatus(bool doTick)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SporeFlower.BP_SporeFlower_C.SetTickStatus");

	ABP_SporeFlower_C_SetTickStatus_Params params;
	params.doTick = doTick;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SporeFlower.BP_SporeFlower_C.OnRep_mReplicatedAnimPosition
// ()

void ABP_SporeFlower_C::OnRep_mReplicatedAnimPosition()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SporeFlower.BP_SporeFlower_C.OnRep_mReplicatedAnimPosition");

	ABP_SporeFlower_C_OnRep_mReplicatedAnimPosition_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SporeFlower.BP_SporeFlower_C.OnRep_mState
// ()

void ABP_SporeFlower_C::OnRep_mState()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SporeFlower.BP_SporeFlower_C.OnRep_mState");

	ABP_SporeFlower_C_OnRep_mState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SporeFlower.BP_SporeFlower_C.OnRep_mGasState
// ()

void ABP_SporeFlower_C::OnRep_mGasState()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SporeFlower.BP_SporeFlower_C.OnRep_mGasState");

	ABP_SporeFlower_C_OnRep_mGasState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SporeFlower.BP_SporeFlower_C.StopSporeAnimation
// ()

void ABP_SporeFlower_C::StopSporeAnimation()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SporeFlower.BP_SporeFlower_C.StopSporeAnimation");

	ABP_SporeFlower_C_StopSporeAnimation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SporeFlower.BP_SporeFlower_C.UpdateAnimationFromState
// ()

void ABP_SporeFlower_C::UpdateAnimationFromState()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SporeFlower.BP_SporeFlower_C.UpdateAnimationFromState");

	ABP_SporeFlower_C_UpdateAnimationFromState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SporeFlower.BP_SporeFlower_C.StartSporeAnimation
// ()

void ABP_SporeFlower_C::StartSporeAnimation()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SporeFlower.BP_SporeFlower_C.StartSporeAnimation");

	ABP_SporeFlower_C_StartSporeAnimation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SporeFlower.BP_SporeFlower_C.GetStatePlayRate
// ()
// Parameters:
// float                          PlayRate                       (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void ABP_SporeFlower_C::GetStatePlayRate(float* PlayRate)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SporeFlower.BP_SporeFlower_C.GetStatePlayRate");

	ABP_SporeFlower_C_GetStatePlayRate_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (PlayRate != nullptr)
		*PlayRate = params.PlayRate;
}


// Function BP_SporeFlower.BP_SporeFlower_C.GetOffCooldown
// ()

void ABP_SporeFlower_C::GetOffCooldown()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SporeFlower.BP_SporeFlower_C.GetOffCooldown");

	ABP_SporeFlower_C_GetOffCooldown_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SporeFlower.BP_SporeFlower_C.StartReleasingGas
// ()

void ABP_SporeFlower_C::StartReleasingGas()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SporeFlower.BP_SporeFlower_C.StartReleasingGas");

	ABP_SporeFlower_C_StartReleasingGas_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SporeFlower.BP_SporeFlower_C.StopExpanding
// ()

void ABP_SporeFlower_C::StopExpanding()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SporeFlower.BP_SporeFlower_C.StopExpanding");

	ABP_SporeFlower_C_StopExpanding_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SporeFlower.BP_SporeFlower_C.StopReleasingGas
// ()

void ABP_SporeFlower_C::StopReleasingGas()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SporeFlower.BP_SporeFlower_C.StopReleasingGas");

	ABP_SporeFlower_C_StopReleasingGas_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SporeFlower.BP_SporeFlower_C.CondintionallyReverseExpanding
// ()

void ABP_SporeFlower_C::CondintionallyReverseExpanding()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SporeFlower.BP_SporeFlower_C.CondintionallyReverseExpanding");

	ABP_SporeFlower_C_CondintionallyReverseExpanding_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SporeFlower.BP_SporeFlower_C.ConditionallyStartExpanding
// ()

void ABP_SporeFlower_C::ConditionallyStartExpanding()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SporeFlower.BP_SporeFlower_C.ConditionallyStartExpanding");

	ABP_SporeFlower_C_ConditionallyStartExpanding_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SporeFlower.BP_SporeFlower_C.UserConstructionScript
// ()

void ABP_SporeFlower_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SporeFlower.BP_SporeFlower_C.UserConstructionScript");

	ABP_SporeFlower_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SporeFlower.BP_SporeFlower_C.ActivateDamage
// ()

void ABP_SporeFlower_C::ActivateDamage()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SporeFlower.BP_SporeFlower_C.ActivateDamage");

	ABP_SporeFlower_C_ActivateDamage_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SporeFlower.BP_SporeFlower_C.BndEvt__TriggerSphere_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature
// ()
// Parameters:
// class UPrimitiveComponent*     OverlappedComponent            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class AActor*                  OtherActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UPrimitiveComponent*     OtherComp                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// int                            OtherBodyIndex                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           bFromSweep                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// struct FHitResult              SweepResult                    (ConstParm, BlueprintVisible, BlueprintReadOnly, Parm, OutParm, ReferenceParm, IsPlainOldData)

void ABP_SporeFlower_C::BndEvt__TriggerSphere_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const struct FHitResult& SweepResult)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SporeFlower.BP_SporeFlower_C.BndEvt__TriggerSphere_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature");

	ABP_SporeFlower_C_BndEvt__TriggerSphere_K2Node_ComponentBoundEvent_0_ComponentBeginOverlapSignature__DelegateSignature_Params params;
	params.OverlappedComponent = OverlappedComponent;
	params.OtherActor = OtherActor;
	params.OtherComp = OtherComp;
	params.OtherBodyIndex = OtherBodyIndex;
	params.bFromSweep = bFromSweep;
	params.SweepResult = SweepResult;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SporeFlower.BP_SporeFlower_C.BndEvt__TriggerSphere_K2Node_ComponentBoundEvent_1_ComponentEndOverlapSignature__DelegateSignature
// ()
// Parameters:
// class UPrimitiveComponent*     OverlappedComponent            (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// class AActor*                  OtherActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class UPrimitiveComponent*     OtherComp                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, InstancedReference, IsPlainOldData)
// int                            OtherBodyIndex                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_SporeFlower_C::BndEvt__TriggerSphere_K2Node_ComponentBoundEvent_1_ComponentEndOverlapSignature__DelegateSignature(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int OtherBodyIndex)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SporeFlower.BP_SporeFlower_C.BndEvt__TriggerSphere_K2Node_ComponentBoundEvent_1_ComponentEndOverlapSignature__DelegateSignature");

	ABP_SporeFlower_C_BndEvt__TriggerSphere_K2Node_ComponentBoundEvent_1_ComponentEndOverlapSignature__DelegateSignature_Params params;
	params.OverlappedComponent = OverlappedComponent;
	params.OtherActor = OtherActor;
	params.OtherComp = OtherComp;
	params.OtherBodyIndex = OtherBodyIndex;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SporeFlower.BP_SporeFlower_C.SpawnGasParticles
// ()

void ABP_SporeFlower_C::SpawnGasParticles()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SporeFlower.BP_SporeFlower_C.SpawnGasParticles");

	ABP_SporeFlower_C_SpawnGasParticles_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SporeFlower.BP_SporeFlower_C.ReceiveBeginPlay
// ()

void ABP_SporeFlower_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SporeFlower.BP_SporeFlower_C.ReceiveBeginPlay");

	ABP_SporeFlower_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SporeFlower.BP_SporeFlower_C.UpdateAnimPosition
// ()

void ABP_SporeFlower_C::UpdateAnimPosition()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SporeFlower.BP_SporeFlower_C.UpdateAnimPosition");

	ABP_SporeFlower_C_UpdateAnimPosition_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SporeFlower.BP_SporeFlower_C.ReceiveEndPlay
// ()
// Parameters:
// TEnumAsByte<EEndPlayReason>*   EndPlayReason                  (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_SporeFlower_C::ReceiveEndPlay(TEnumAsByte<EEndPlayReason>* EndPlayReason)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SporeFlower.BP_SporeFlower_C.ReceiveEndPlay");

	ABP_SporeFlower_C_ReceiveEndPlay_Params params;
	params.EndPlayReason = EndPlayReason;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SporeFlower.BP_SporeFlower_C.GainedSignificance
// ()

void ABP_SporeFlower_C::GainedSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SporeFlower.BP_SporeFlower_C.GainedSignificance");

	ABP_SporeFlower_C_GainedSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SporeFlower.BP_SporeFlower_C.LostSignificance
// ()

void ABP_SporeFlower_C::LostSignificance()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SporeFlower.BP_SporeFlower_C.LostSignificance");

	ABP_SporeFlower_C_LostSignificance_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_SporeFlower.BP_SporeFlower_C.ExecuteUbergraph_BP_SporeFlower
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_SporeFlower_C::ExecuteUbergraph_BP_SporeFlower(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_SporeFlower.BP_SporeFlower_C.ExecuteUbergraph_BP_SporeFlower");

	ABP_SporeFlower_C_ExecuteUbergraph_BP_SporeFlower_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
