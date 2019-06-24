// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_GameState_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_GameState.BP_GameState_C.DumpVisistedMapAreas
// ()

void ABP_GameState_C::DumpVisistedMapAreas()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameState.BP_GameState_C.DumpVisistedMapAreas");

	ABP_GameState_C_DumpVisistedMapAreas_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameState.BP_GameState_C.DumpActorRepresentations
// ()

void ABP_GameState_C::DumpActorRepresentations()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameState.BP_GameState_C.DumpActorRepresentations");

	ABP_GameState_C_DumpActorRepresentations_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameState.BP_GameState_C.UserConstructionScript
// ()

void ABP_GameState_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameState.BP_GameState_C.UserConstructionScript");

	ABP_GameState_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameState.BP_GameState_C.ReceiveTick
// ()
// Parameters:
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_GameState_C::ReceiveTick(float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameState.BP_GameState_C.ReceiveTick");

	ABP_GameState_C_ReceiveTick_Params params;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_GameState.BP_GameState_C.ExecuteUbergraph_BP_GameState
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABP_GameState_C::ExecuteUbergraph_BP_GameState(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_GameState.BP_GameState_C.ExecuteUbergraph_BP_GameState");

	ABP_GameState_C_ExecuteUbergraph_BP_GameState_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
