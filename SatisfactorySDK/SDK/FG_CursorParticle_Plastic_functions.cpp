// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_CursorParticle_Plastic_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function CursorParticle_Plastic.CursorParticle_Plastic_C.Construct
// ()

void UCursorParticle_Plastic_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function CursorParticle_Plastic.CursorParticle_Plastic_C.Construct");

	UCursorParticle_Plastic_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function CursorParticle_Plastic.CursorParticle_Plastic_C.ExecuteUbergraph_CursorParticle_Plastic
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UCursorParticle_Plastic_C::ExecuteUbergraph_CursorParticle_Plastic(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function CursorParticle_Plastic.CursorParticle_Plastic_C.ExecuteUbergraph_CursorParticle_Plastic");

	UCursorParticle_Plastic_C_ExecuteUbergraph_CursorParticle_Plastic_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
