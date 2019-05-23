// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_CheatResourceSink_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_CheatResourceSink.Build_CheatResourceSink_C.UserConstructionScript
// ()

void ABuild_CheatResourceSink_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_CheatResourceSink.Build_CheatResourceSink_C.UserConstructionScript");

	ABuild_CheatResourceSink_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_CheatResourceSink.Build_CheatResourceSink_C.Factory_CollectInput
// ()

void ABuild_CheatResourceSink_C::Factory_CollectInput()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_CheatResourceSink.Build_CheatResourceSink_C.Factory_CollectInput");

	ABuild_CheatResourceSink_C_Factory_CollectInput_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_CheatResourceSink.Build_CheatResourceSink_C.ExecuteUbergraph_Build_CheatResourceSink
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_CheatResourceSink_C::ExecuteUbergraph_Build_CheatResourceSink(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_CheatResourceSink.Build_CheatResourceSink_C.ExecuteUbergraph_Build_CheatResourceSink");

	ABuild_CheatResourceSink_C_ExecuteUbergraph_Build_CheatResourceSink_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
