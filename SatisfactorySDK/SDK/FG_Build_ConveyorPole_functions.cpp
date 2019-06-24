// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_ConveyorPole_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_ConveyorPole.Build_ConveyorPole_C.UserConstructionScript
// ()

void ABuild_ConveyorPole_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ConveyorPole.Build_ConveyorPole_C.UserConstructionScript");

	ABuild_ConveyorPole_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_ConveyorPole.Build_ConveyorPole_C.PlayConstructSound
// ()

void ABuild_ConveyorPole_C::PlayConstructSound()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ConveyorPole.Build_ConveyorPole_C.PlayConstructSound");

	ABuild_ConveyorPole_C_PlayConstructSound_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_ConveyorPole.Build_ConveyorPole_C.ExecuteUbergraph_Build_ConveyorPole
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_ConveyorPole_C::ExecuteUbergraph_Build_ConveyorPole(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ConveyorPole.Build_ConveyorPole_C.ExecuteUbergraph_Build_ConveyorPole");

	ABuild_ConveyorPole_C_ExecuteUbergraph_Build_ConveyorPole_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
