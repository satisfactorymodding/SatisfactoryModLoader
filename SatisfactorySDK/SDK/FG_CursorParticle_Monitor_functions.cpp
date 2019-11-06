// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_CursorParticle_Monitor_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function CursorParticle_Monitor.CursorParticle_Monitor_C.SwitchImage
// ()

void UCursorParticle_Monitor_C::SwitchImage()
{
	static auto fn = UObject::FindObject<UFunction>("Function CursorParticle_Monitor.CursorParticle_Monitor_C.SwitchImage");

	UCursorParticle_Monitor_C_SwitchImage_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function CursorParticle_Monitor.CursorParticle_Monitor_C.Construct
// ()

void UCursorParticle_Monitor_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function CursorParticle_Monitor.CursorParticle_Monitor_C.Construct");

	UCursorParticle_Monitor_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function CursorParticle_Monitor.CursorParticle_Monitor_C.ExecuteUbergraph_CursorParticle_Monitor
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UCursorParticle_Monitor_C::ExecuteUbergraph_CursorParticle_Monitor(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function CursorParticle_Monitor.CursorParticle_Monitor_C.ExecuteUbergraph_CursorParticle_Monitor");

	UCursorParticle_Monitor_C_ExecuteUbergraph_CursorParticle_Monitor_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
