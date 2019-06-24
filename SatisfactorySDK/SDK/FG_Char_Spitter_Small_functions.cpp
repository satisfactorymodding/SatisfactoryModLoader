// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Char_Spitter_Small_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Char_Spitter_Small.Char_Spitter_Small_C.UserConstructionScript
// ()

void AChar_Spitter_Small_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Spitter_Small.Char_Spitter_Small_C.UserConstructionScript");

	AChar_Spitter_Small_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Spitter_Small.Char_Spitter_Small_C.OnCurrentAggroTargetReplicated
// ()

void AChar_Spitter_Small_C::OnCurrentAggroTargetReplicated()
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Spitter_Small.Char_Spitter_Small_C.OnCurrentAggroTargetReplicated");

	AChar_Spitter_Small_C_OnCurrentAggroTargetReplicated_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Char_Spitter_Small.Char_Spitter_Small_C.ExecuteUbergraph_Char_Spitter_Small
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void AChar_Spitter_Small_C::ExecuteUbergraph_Char_Spitter_Small(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Char_Spitter_Small.Char_Spitter_Small_C.ExecuteUbergraph_Char_Spitter_Small");

	AChar_Spitter_Small_C_ExecuteUbergraph_Char_Spitter_Small_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
