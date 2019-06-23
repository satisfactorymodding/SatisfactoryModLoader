// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_SmelterMk1_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_SmelterMk1.Anim_SmelterMk1_C.AnimNotify_SmelterEnteredProducingState
// ()

void UAnim_SmelterMk1_C::AnimNotify_SmelterEnteredProducingState()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_SmelterMk1.Anim_SmelterMk1_C.AnimNotify_SmelterEnteredProducingState");

	UAnim_SmelterMk1_C_AnimNotify_SmelterEnteredProducingState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_SmelterMk1.Anim_SmelterMk1_C.AnimNotify_SmelterEnteredOfflineState
// ()

void UAnim_SmelterMk1_C::AnimNotify_SmelterEnteredOfflineState()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_SmelterMk1.Anim_SmelterMk1_C.AnimNotify_SmelterEnteredOfflineState");

	UAnim_SmelterMk1_C_AnimNotify_SmelterEnteredOfflineState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_SmelterMk1.Anim_SmelterMk1_C.AnimNotify_SmelterLeftProducingState
// ()

void UAnim_SmelterMk1_C::AnimNotify_SmelterLeftProducingState()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_SmelterMk1.Anim_SmelterMk1_C.AnimNotify_SmelterLeftProducingState");

	UAnim_SmelterMk1_C_AnimNotify_SmelterLeftProducingState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_SmelterMk1.Anim_SmelterMk1_C.AnimNotify_SmelterLeftOfflineState
// ()

void UAnim_SmelterMk1_C::AnimNotify_SmelterLeftOfflineState()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_SmelterMk1.Anim_SmelterMk1_C.AnimNotify_SmelterLeftOfflineState");

	UAnim_SmelterMk1_C_AnimNotify_SmelterLeftOfflineState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_SmelterMk1.Anim_SmelterMk1_C.ExecuteUbergraph_Anim_SmelterMk1
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_SmelterMk1_C::ExecuteUbergraph_Anim_SmelterMk1(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_SmelterMk1.Anim_SmelterMk1_C.ExecuteUbergraph_Anim_SmelterMk1");

	UAnim_SmelterMk1_C_ExecuteUbergraph_Anim_SmelterMk1_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
