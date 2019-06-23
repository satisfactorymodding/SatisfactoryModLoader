// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_OilRefinery_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_OilRefinery.Anim_OilRefinery_C.AnimNotify_OilRefineryEnteredOffline
// ()

void UAnim_OilRefinery_C::AnimNotify_OilRefineryEnteredOffline()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_OilRefinery.Anim_OilRefinery_C.AnimNotify_OilRefineryEnteredOffline");

	UAnim_OilRefinery_C_AnimNotify_OilRefineryEnteredOffline_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_OilRefinery.Anim_OilRefinery_C.AnimNotify_OilRefineryEnteredProducing
// ()

void UAnim_OilRefinery_C::AnimNotify_OilRefineryEnteredProducing()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_OilRefinery.Anim_OilRefinery_C.AnimNotify_OilRefineryEnteredProducing");

	UAnim_OilRefinery_C_AnimNotify_OilRefineryEnteredProducing_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_OilRefinery.Anim_OilRefinery_C.AnimNotify_OilRefineryLeftOffline
// ()

void UAnim_OilRefinery_C::AnimNotify_OilRefineryLeftOffline()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_OilRefinery.Anim_OilRefinery_C.AnimNotify_OilRefineryLeftOffline");

	UAnim_OilRefinery_C_AnimNotify_OilRefineryLeftOffline_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_OilRefinery.Anim_OilRefinery_C.AnimNotify_OilRefineryLeftProducing
// ()

void UAnim_OilRefinery_C::AnimNotify_OilRefineryLeftProducing()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_OilRefinery.Anim_OilRefinery_C.AnimNotify_OilRefineryLeftProducing");

	UAnim_OilRefinery_C_AnimNotify_OilRefineryLeftProducing_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_OilRefinery.Anim_OilRefinery_C.ExecuteUbergraph_Anim_OilRefinery
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_OilRefinery_C::ExecuteUbergraph_Anim_OilRefinery(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_OilRefinery.Anim_OilRefinery_C.ExecuteUbergraph_Anim_OilRefinery");

	UAnim_OilRefinery_C_ExecuteUbergraph_Anim_OilRefinery_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
