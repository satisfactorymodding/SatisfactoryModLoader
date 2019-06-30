// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_RailroadTrack_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_RailroadTrack.Build_RailroadTrack_C.UserConstructionScript
// ()

void ABuild_RailroadTrack_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RailroadTrack.Build_RailroadTrack_C.UserConstructionScript");

	ABuild_RailroadTrack_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_RailroadTrack.Build_RailroadTrack_C.PlayConstructSound
// ()

void ABuild_RailroadTrack_C::PlayConstructSound()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RailroadTrack.Build_RailroadTrack_C.PlayConstructSound");

	ABuild_RailroadTrack_C_PlayConstructSound_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_RailroadTrack.Build_RailroadTrack_C.ExecuteUbergraph_Build_RailroadTrack
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_RailroadTrack_C::ExecuteUbergraph_Build_RailroadTrack(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RailroadTrack.Build_RailroadTrack_C.ExecuteUbergraph_Build_RailroadTrack");

	ABuild_RailroadTrack_C_ExecuteUbergraph_Build_RailroadTrack_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
