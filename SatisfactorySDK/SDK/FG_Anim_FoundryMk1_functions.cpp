// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_FoundryMk1_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_FoundryMk1.Anim_FoundryMk1_C.AnimNotify_SmelterEnteredProducingState
// ()

void UAnim_FoundryMk1_C::AnimNotify_SmelterEnteredProducingState()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_FoundryMk1.Anim_FoundryMk1_C.AnimNotify_SmelterEnteredProducingState");

	UAnim_FoundryMk1_C_AnimNotify_SmelterEnteredProducingState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_FoundryMk1.Anim_FoundryMk1_C.AnimNotify_SmelterEnteredOfflineState
// ()

void UAnim_FoundryMk1_C::AnimNotify_SmelterEnteredOfflineState()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_FoundryMk1.Anim_FoundryMk1_C.AnimNotify_SmelterEnteredOfflineState");

	UAnim_FoundryMk1_C_AnimNotify_SmelterEnteredOfflineState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_FoundryMk1.Anim_FoundryMk1_C.AnimNotify_SmelterLeftProducingState
// ()

void UAnim_FoundryMk1_C::AnimNotify_SmelterLeftProducingState()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_FoundryMk1.Anim_FoundryMk1_C.AnimNotify_SmelterLeftProducingState");

	UAnim_FoundryMk1_C_AnimNotify_SmelterLeftProducingState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_FoundryMk1.Anim_FoundryMk1_C.AnimNotify_SmelterLeftOfflineState
// ()

void UAnim_FoundryMk1_C::AnimNotify_SmelterLeftOfflineState()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_FoundryMk1.Anim_FoundryMk1_C.AnimNotify_SmelterLeftOfflineState");

	UAnim_FoundryMk1_C_AnimNotify_SmelterLeftOfflineState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_FoundryMk1.Anim_FoundryMk1_C.ExecuteUbergraph_Anim_FoundryMk1
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_FoundryMk1_C::ExecuteUbergraph_Anim_FoundryMk1(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_FoundryMk1.Anim_FoundryMk1_C.ExecuteUbergraph_Anim_FoundryMk1");

	UAnim_FoundryMk1_C_ExecuteUbergraph_Anim_FoundryMk1_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
