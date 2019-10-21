// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_RailroadTrackIntegrated_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_RailroadTrackIntegrated.Build_RailroadTrackIntegrated_C.CanDismantle
// ()
// Parameters:
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool ABuild_RailroadTrackIntegrated_C::CanDismantle()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RailroadTrackIntegrated.Build_RailroadTrackIntegrated_C.CanDismantle");

	ABuild_RailroadTrackIntegrated_C_CanDismantle_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function Build_RailroadTrackIntegrated.Build_RailroadTrackIntegrated_C.UserConstructionScript
// ()

void ABuild_RailroadTrackIntegrated_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RailroadTrackIntegrated.Build_RailroadTrackIntegrated_C.UserConstructionScript");

	ABuild_RailroadTrackIntegrated_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_RailroadTrackIntegrated.Build_RailroadTrackIntegrated_C.PlayConstructSound
// ()

void ABuild_RailroadTrackIntegrated_C::PlayConstructSound()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RailroadTrackIntegrated.Build_RailroadTrackIntegrated_C.PlayConstructSound");

	ABuild_RailroadTrackIntegrated_C_PlayConstructSound_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_RailroadTrackIntegrated.Build_RailroadTrackIntegrated_C.ExecuteUbergraph_Build_RailroadTrackIntegrated
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_RailroadTrackIntegrated_C::ExecuteUbergraph_Build_RailroadTrackIntegrated(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_RailroadTrackIntegrated.Build_RailroadTrackIntegrated_C.ExecuteUbergraph_Build_RailroadTrackIntegrated");

	ABuild_RailroadTrackIntegrated_C_ExecuteUbergraph_Build_RailroadTrackIntegrated_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
