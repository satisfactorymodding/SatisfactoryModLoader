// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_TrainStation_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_TrainStation.Build_TrainStation_C.UserConstructionScript
// ()

void ABuild_TrainStation_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TrainStation.Build_TrainStation_C.UserConstructionScript");

	ABuild_TrainStation_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_TrainStation.Build_TrainStation_C.OnNameChanged
// ()

void ABuild_TrainStation_C::OnNameChanged()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TrainStation.Build_TrainStation_C.OnNameChanged");

	ABuild_TrainStation_C_OnNameChanged_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_TrainStation.Build_TrainStation_C.ExecuteUbergraph_Build_TrainStation
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_TrainStation_C::ExecuteUbergraph_Build_TrainStation(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_TrainStation.Build_TrainStation_C.ExecuteUbergraph_Build_TrainStation");

	ABuild_TrainStation_C_ExecuteUbergraph_Build_TrainStation_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
