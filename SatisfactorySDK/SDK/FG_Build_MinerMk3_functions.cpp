// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_MinerMk3_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_MinerMk3.Build_MinerMk3_C.UserConstructionScript
// ()

void ABuild_MinerMk3_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_MinerMk3.Build_MinerMk3_C.UserConstructionScript");

	ABuild_MinerMk3_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_MinerMk3.Build_MinerMk3_C.ReceiveDestroyed
// ()

void ABuild_MinerMk3_C::ReceiveDestroyed()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_MinerMk3.Build_MinerMk3_C.ReceiveDestroyed");

	ABuild_MinerMk3_C_ReceiveDestroyed_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_MinerMk3.Build_MinerMk3_C.ReceiveBeginPlay
// ()

void ABuild_MinerMk3_C::ReceiveBeginPlay()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_MinerMk3.Build_MinerMk3_C.ReceiveBeginPlay");

	ABuild_MinerMk3_C_ReceiveBeginPlay_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_MinerMk3.Build_MinerMk3_C.ExecuteUbergraph_Build_MinerMk3
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_MinerMk3_C::ExecuteUbergraph_Build_MinerMk3(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_MinerMk3.Build_MinerMk3_C.ExecuteUbergraph_Build_MinerMk3");

	ABuild_MinerMk3_C_ExecuteUbergraph_Build_MinerMk3_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
