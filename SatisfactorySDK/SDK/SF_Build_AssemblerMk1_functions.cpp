// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Build_AssemblerMk1_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_AssemblerMk1.Build_AssemblerMk1_C.UserConstructionScript
// ()

void ABuild_AssemblerMk1_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_AssemblerMk1.Build_AssemblerMk1_C.UserConstructionScript");

	ABuild_AssemblerMk1_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_AssemblerMk1.Build_AssemblerMk1_C.ExecuteUbergraph_Build_AssemblerMk1
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_AssemblerMk1_C::ExecuteUbergraph_Build_AssemblerMk1(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_AssemblerMk1.Build_AssemblerMk1_C.ExecuteUbergraph_Build_AssemblerMk1");

	ABuild_AssemblerMk1_C_ExecuteUbergraph_Build_AssemblerMk1_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
