// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_LocomotiveAnim_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_LocomotiveAnim.BP_LocomotiveAnim_C.CalculateAnimGraphValues
// ()

void UBP_LocomotiveAnim_C::CalculateAnimGraphValues()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_LocomotiveAnim.BP_LocomotiveAnim_C.CalculateAnimGraphValues");

	UBP_LocomotiveAnim_C_CalculateAnimGraphValues_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_LocomotiveAnim.BP_LocomotiveAnim_C.BlueprintUpdateAnimation
// ()
// Parameters:
// float*                         DeltaTimeX                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_LocomotiveAnim_C::BlueprintUpdateAnimation(float* DeltaTimeX)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_LocomotiveAnim.BP_LocomotiveAnim_C.BlueprintUpdateAnimation");

	UBP_LocomotiveAnim_C_BlueprintUpdateAnimation_Params params;
	params.DeltaTimeX = DeltaTimeX;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_LocomotiveAnim.BP_LocomotiveAnim_C.AnimNotify_EnterHandBrake_01
// ()

void UBP_LocomotiveAnim_C::AnimNotify_EnterHandBrake_01()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_LocomotiveAnim.BP_LocomotiveAnim_C.AnimNotify_EnterHandBrake_01");

	UBP_LocomotiveAnim_C_AnimNotify_EnterHandBrake_01_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_LocomotiveAnim.BP_LocomotiveAnim_C.AnimNotify_KillHandBrake_01
// ()

void UBP_LocomotiveAnim_C::AnimNotify_KillHandBrake_01()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_LocomotiveAnim.BP_LocomotiveAnim_C.AnimNotify_KillHandBrake_01");

	UBP_LocomotiveAnim_C_AnimNotify_KillHandBrake_01_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_LocomotiveAnim.BP_LocomotiveAnim_C.AnimNotify_EnterHandBrake_02
// ()

void UBP_LocomotiveAnim_C::AnimNotify_EnterHandBrake_02()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_LocomotiveAnim.BP_LocomotiveAnim_C.AnimNotify_EnterHandBrake_02");

	UBP_LocomotiveAnim_C_AnimNotify_EnterHandBrake_02_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_LocomotiveAnim.BP_LocomotiveAnim_C.AnimNotify_KillHandBrake_02
// ()

void UBP_LocomotiveAnim_C::AnimNotify_KillHandBrake_02()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_LocomotiveAnim.BP_LocomotiveAnim_C.AnimNotify_KillHandBrake_02");

	UBP_LocomotiveAnim_C_AnimNotify_KillHandBrake_02_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_LocomotiveAnim.BP_LocomotiveAnim_C.AnimNotify_TriggerhandbrakeVFX
// ()

void UBP_LocomotiveAnim_C::AnimNotify_TriggerhandbrakeVFX()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_LocomotiveAnim.BP_LocomotiveAnim_C.AnimNotify_TriggerhandbrakeVFX");

	UBP_LocomotiveAnim_C_AnimNotify_TriggerhandbrakeVFX_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_LocomotiveAnim.BP_LocomotiveAnim_C.BlueprintInitializeAnimation
// ()

void UBP_LocomotiveAnim_C::BlueprintInitializeAnimation()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_LocomotiveAnim.BP_LocomotiveAnim_C.BlueprintInitializeAnimation");

	UBP_LocomotiveAnim_C_BlueprintInitializeAnimation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_LocomotiveAnim.BP_LocomotiveAnim_C.ExecuteUbergraph_BP_LocomotiveAnim
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_LocomotiveAnim_C::ExecuteUbergraph_BP_LocomotiveAnim(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_LocomotiveAnim.BP_LocomotiveAnim_C.ExecuteUbergraph_BP_LocomotiveAnim");

	UBP_LocomotiveAnim_C_ExecuteUbergraph_BP_LocomotiveAnim_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
