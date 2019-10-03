// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_CursorParticle_Glass_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function CursorParticle_Glass.CursorParticle_Glass_C.Construct
// ()

void UCursorParticle_Glass_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function CursorParticle_Glass.CursorParticle_Glass_C.Construct");

	UCursorParticle_Glass_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function CursorParticle_Glass.CursorParticle_Glass_C.ExecuteUbergraph_CursorParticle_Glass
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UCursorParticle_Glass_C::ExecuteUbergraph_CursorParticle_Glass(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function CursorParticle_Glass.CursorParticle_Glass_C.ExecuteUbergraph_CursorParticle_Glass");

	UCursorParticle_Glass_C_ExecuteUbergraph_CursorParticle_Glass_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
