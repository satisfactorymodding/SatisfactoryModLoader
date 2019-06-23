// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_ConstructorMk1_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_ConstructorMk1.Build_ConstructorMk1_C.UserConstructionScript
// ()

void ABuild_ConstructorMk1_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ConstructorMk1.Build_ConstructorMk1_C.UserConstructionScript");

	ABuild_ConstructorMk1_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_ConstructorMk1.Build_ConstructorMk1_C.ExecuteUbergraph_Build_ConstructorMk1
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_ConstructorMk1_C::ExecuteUbergraph_Build_ConstructorMk1(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ConstructorMk1.Build_ConstructorMk1_C.ExecuteUbergraph_Build_ConstructorMk1");

	ABuild_ConstructorMk1_C_ExecuteUbergraph_Build_ConstructorMk1_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
