// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_GeneratorFuel_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_GeneratorFuel.Anim_GeneratorFuel_C.AnimNotify_FuelGenEnteredProducingState
// ()

void UAnim_GeneratorFuel_C::AnimNotify_FuelGenEnteredProducingState()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_GeneratorFuel.Anim_GeneratorFuel_C.AnimNotify_FuelGenEnteredProducingState");

	UAnim_GeneratorFuel_C_AnimNotify_FuelGenEnteredProducingState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_GeneratorFuel.Anim_GeneratorFuel_C.AnimNotify_FuelGenLeftProducingState
// ()

void UAnim_GeneratorFuel_C::AnimNotify_FuelGenLeftProducingState()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_GeneratorFuel.Anim_GeneratorFuel_C.AnimNotify_FuelGenLeftProducingState");

	UAnim_GeneratorFuel_C_AnimNotify_FuelGenLeftProducingState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_GeneratorFuel.Anim_GeneratorFuel_C.ExecuteUbergraph_Anim_GeneratorFuel
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_GeneratorFuel_C::ExecuteUbergraph_Anim_GeneratorFuel(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_GeneratorFuel.Anim_GeneratorFuel_C.ExecuteUbergraph_Anim_GeneratorFuel");

	UAnim_GeneratorFuel_C_ExecuteUbergraph_Anim_GeneratorFuel_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
