// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_ConveyorLiftMk1_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_ConveyorLiftMk1.Build_ConveyorLiftMk1_C.UserConstructionScript
// ()

void ABuild_ConveyorLiftMk1_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ConveyorLiftMk1.Build_ConveyorLiftMk1_C.UserConstructionScript");

	ABuild_ConveyorLiftMk1_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_ConveyorLiftMk1.Build_ConveyorLiftMk1_C.PlayConstructSound
// ()

void ABuild_ConveyorLiftMk1_C::PlayConstructSound()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ConveyorLiftMk1.Build_ConveyorLiftMk1_C.PlayConstructSound");

	ABuild_ConveyorLiftMk1_C_PlayConstructSound_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_ConveyorLiftMk1.Build_ConveyorLiftMk1_C.ExecuteUbergraph_Build_ConveyorLiftMk1
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_ConveyorLiftMk1_C::ExecuteUbergraph_Build_ConveyorLiftMk1(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ConveyorLiftMk1.Build_ConveyorLiftMk1_C.ExecuteUbergraph_Build_ConveyorLiftMk1");

	ABuild_ConveyorLiftMk1_C_ExecuteUbergraph_Build_ConveyorLiftMk1_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
