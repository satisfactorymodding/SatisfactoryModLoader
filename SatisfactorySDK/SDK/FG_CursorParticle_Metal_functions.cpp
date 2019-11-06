// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_CursorParticle_Metal_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function CursorParticle_Metal.CursorParticle_Metal_C.Construct
// ()

void UCursorParticle_Metal_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function CursorParticle_Metal.CursorParticle_Metal_C.Construct");

	UCursorParticle_Metal_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function CursorParticle_Metal.CursorParticle_Metal_C.ExecuteUbergraph_CursorParticle_Metal
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UCursorParticle_Metal_C::ExecuteUbergraph_CursorParticle_Metal(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function CursorParticle_Metal.CursorParticle_Metal_C.ExecuteUbergraph_CursorParticle_Metal");

	UCursorParticle_Metal_C_ExecuteUbergraph_CursorParticle_Metal_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
