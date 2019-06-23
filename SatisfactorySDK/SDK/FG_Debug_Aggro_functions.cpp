// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Debug_Aggro_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Debug_Aggro.Debug_Aggro_C.Construct
// ()

void UDebug_Aggro_C::Construct()
{
	static auto fn = UObject::FindObject<UFunction>("Function Debug_Aggro.Debug_Aggro_C.Construct");

	UDebug_Aggro_C_Construct_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Debug_Aggro.Debug_Aggro_C.ExecuteUbergraph_Debug_Aggro
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UDebug_Aggro_C::ExecuteUbergraph_Debug_Aggro(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Debug_Aggro.Debug_Aggro_C.ExecuteUbergraph_Debug_Aggro");

	UDebug_Aggro_C_ExecuteUbergraph_Debug_Aggro_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
