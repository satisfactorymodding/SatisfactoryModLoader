// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Build_ConveyorBeltMk1_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Build_ConveyorBeltMk1.Build_ConveyorBeltMk1_C.UserConstructionScript
// ()

void ABuild_ConveyorBeltMk1_C::UserConstructionScript()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ConveyorBeltMk1.Build_ConveyorBeltMk1_C.UserConstructionScript");

	ABuild_ConveyorBeltMk1_C_UserConstructionScript_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_ConveyorBeltMk1.Build_ConveyorBeltMk1_C.PlayConstructSound
// ()

void ABuild_ConveyorBeltMk1_C::PlayConstructSound()
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ConveyorBeltMk1.Build_ConveyorBeltMk1_C.PlayConstructSound");

	ABuild_ConveyorBeltMk1_C_PlayConstructSound_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Build_ConveyorBeltMk1.Build_ConveyorBeltMk1_C.ExecuteUbergraph_Build_ConveyorBeltMk1
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void ABuild_ConveyorBeltMk1_C::ExecuteUbergraph_Build_ConveyorBeltMk1(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Build_ConveyorBeltMk1.Build_ConveyorBeltMk1_C.ExecuteUbergraph_Build_ConveyorBeltMk1");

	ABuild_ConveyorBeltMk1_C_ExecuteUbergraph_Build_ConveyorBeltMk1_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
