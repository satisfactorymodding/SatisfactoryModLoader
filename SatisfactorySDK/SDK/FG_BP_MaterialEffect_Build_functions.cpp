// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_MaterialEffect_Build_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.PlayThumpSound
// ()

void UBP_MaterialEffect_Build_C::PlayThumpSound()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.PlayThumpSound");

	UBP_MaterialEffect_Build_C_PlayThumpSound_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.InitMaterialParameters
// ()

void UBP_MaterialEffect_Build_C::InitMaterialParameters()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.InitMaterialParameters");

	UBP_MaterialEffect_Build_C_InitMaterialParameters_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.SetupBounds
// ()

void UBP_MaterialEffect_Build_C::SetupBounds()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.SetupBounds");

	UBP_MaterialEffect_Build_C_SetupBounds_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.GotoNextStep
// ()

void UBP_MaterialEffect_Build_C::GotoNextStep()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.GotoNextStep");

	UBP_MaterialEffect_Build_C_GotoNextStep_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.CalcCostQueueNewLength
// ()
// Parameters:
// int                            NewLength                      (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UBP_MaterialEffect_Build_C::CalcCostQueueNewLength(int* NewLength)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.CalcCostQueueNewLength");

	UBP_MaterialEffect_Build_C_CalcCostQueueNewLength_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (NewLength != nullptr)
		*NewLength = params.NewLength;
}


// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.DebugFillCostQueue
// ()

void UBP_MaterialEffect_Build_C::DebugFillCostQueue()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.DebugFillCostQueue");

	UBP_MaterialEffect_Build_C_DebugFillCostQueue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.CalcDisplacementAmount
// ()
// Parameters:
// float                          amount                         (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UBP_MaterialEffect_Build_C::CalcDisplacementAmount(float* amount)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.CalcDisplacementAmount");

	UBP_MaterialEffect_Build_C_CalcDisplacementAmount_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (amount != nullptr)
		*amount = params.amount;
}


// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.UpdateCostQueue
// ()

void UBP_MaterialEffect_Build_C::UpdateCostQueue()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.UpdateCostQueue");

	UBP_MaterialEffect_Build_C_UpdateCostQueue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.SetupCostQueue
// ()

void UBP_MaterialEffect_Build_C::SetupCostQueue()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.SetupCostQueue");

	UBP_MaterialEffect_Build_C_SetupCostQueue_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.SetupDuration
// ()

void UBP_MaterialEffect_Build_C::SetupDuration()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.SetupDuration");

	UBP_MaterialEffect_Build_C_SetupDuration_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.SetupMeshes
// ()

void UBP_MaterialEffect_Build_C::SetupMeshes()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.SetupMeshes");

	UBP_MaterialEffect_Build_C_SetupMeshes_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.SpawnFootEmitters
// ()

void UBP_MaterialEffect_Build_C::SpawnFootEmitters()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.SpawnFootEmitters");

	UBP_MaterialEffect_Build_C_SpawnFootEmitters_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.OnUpdate
// ()
// Parameters:
// float*                         DeltaTime                      (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_MaterialEffect_Build_C::OnUpdate(float* DeltaTime)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.OnUpdate");

	UBP_MaterialEffect_Build_C_OnUpdate_Params params;
	params.DeltaTime = DeltaTime;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.OnEnded
// ()

void UBP_MaterialEffect_Build_C::OnEnded()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.OnEnded");

	UBP_MaterialEffect_Build_C_OnEnded_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.PreStarted
// ()

void UBP_MaterialEffect_Build_C::PreStarted()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.PreStarted");

	UBP_MaterialEffect_Build_C_PreStarted_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.OnStarted
// ()

void UBP_MaterialEffect_Build_C::OnStarted()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.OnStarted");

	UBP_MaterialEffect_Build_C_OnStarted_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.OnCostActorReachedTarget
// ()

void UBP_MaterialEffect_Build_C::OnCostActorReachedTarget()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.OnCostActorReachedTarget");

	UBP_MaterialEffect_Build_C_OnCostActorReachedTarget_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.ExecuteUbergraph_BP_MaterialEffect_Build
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_MaterialEffect_Build_C::ExecuteUbergraph_BP_MaterialEffect_Build(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_MaterialEffect_Build.BP_MaterialEffect_Build_C.ExecuteUbergraph_BP_MaterialEffect_Build");

	UBP_MaterialEffect_Build_C_ExecuteUbergraph_BP_MaterialEffect_Build_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
