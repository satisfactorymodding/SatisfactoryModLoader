// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_CursorParticle_Radiation_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function CursorParticle_Radiation.CursorParticle_Radiation_C.Construct
// ()

void UCursorParticle_Radiation_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function CursorParticle_Radiation.CursorParticle_Radiation_C.Construct");

	UCursorParticle_Radiation_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function CursorParticle_Radiation.CursorParticle_Radiation_C.ExecuteUbergraph_CursorParticle_Radiation
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UCursorParticle_Radiation_C::ExecuteUbergraph_CursorParticle_Radiation(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function CursorParticle_Radiation.CursorParticle_Radiation_C.ExecuteUbergraph_CursorParticle_Radiation");

	UCursorParticle_Radiation_C_ExecuteUbergraph_CursorParticle_Radiation_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
