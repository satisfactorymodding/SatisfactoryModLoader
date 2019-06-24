// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_GeneratorCoal_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_GeneratorCoal.Anim_GeneratorCoal_C.BlueprintUpdateAnimation
// ()
// Parameters:
// float*                         DeltaTimeX                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_GeneratorCoal_C::BlueprintUpdateAnimation(float* DeltaTimeX)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_GeneratorCoal.Anim_GeneratorCoal_C.BlueprintUpdateAnimation");

	UAnim_GeneratorCoal_C_BlueprintUpdateAnimation_Params params;
	params.DeltaTimeX = DeltaTimeX;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_GeneratorCoal.Anim_GeneratorCoal_C.AnimNotify_steamVfxNotify
// ()

void UAnim_GeneratorCoal_C::AnimNotify_steamVfxNotify()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_GeneratorCoal.Anim_GeneratorCoal_C.AnimNotify_steamVfxNotify");

	UAnim_GeneratorCoal_C_AnimNotify_steamVfxNotify_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_GeneratorCoal.Anim_GeneratorCoal_C.AnimNotify_CoalGenEnteredProducingState
// ()

void UAnim_GeneratorCoal_C::AnimNotify_CoalGenEnteredProducingState()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_GeneratorCoal.Anim_GeneratorCoal_C.AnimNotify_CoalGenEnteredProducingState");

	UAnim_GeneratorCoal_C_AnimNotify_CoalGenEnteredProducingState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_GeneratorCoal.Anim_GeneratorCoal_C.AnimNotify_CoalGenLeftProducingState
// ()

void UAnim_GeneratorCoal_C::AnimNotify_CoalGenLeftProducingState()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_GeneratorCoal.Anim_GeneratorCoal_C.AnimNotify_CoalGenLeftProducingState");

	UAnim_GeneratorCoal_C_AnimNotify_CoalGenLeftProducingState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_GeneratorCoal.Anim_GeneratorCoal_C.AnimNotify_CoalGenEnteredOfflineState
// ()

void UAnim_GeneratorCoal_C::AnimNotify_CoalGenEnteredOfflineState()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_GeneratorCoal.Anim_GeneratorCoal_C.AnimNotify_CoalGenEnteredOfflineState");

	UAnim_GeneratorCoal_C_AnimNotify_CoalGenEnteredOfflineState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_GeneratorCoal.Anim_GeneratorCoal_C.AnimNotify_CoalGenLeftOfflineState
// ()

void UAnim_GeneratorCoal_C::AnimNotify_CoalGenLeftOfflineState()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_GeneratorCoal.Anim_GeneratorCoal_C.AnimNotify_CoalGenLeftOfflineState");

	UAnim_GeneratorCoal_C_AnimNotify_CoalGenLeftOfflineState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_GeneratorCoal.Anim_GeneratorCoal_C.ExecuteUbergraph_Anim_GeneratorCoal
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_GeneratorCoal_C::ExecuteUbergraph_Anim_GeneratorCoal(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_GeneratorCoal.Anim_GeneratorCoal_C.ExecuteUbergraph_Anim_GeneratorCoal");

	UAnim_GeneratorCoal_C_ExecuteUbergraph_Anim_GeneratorCoal_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
