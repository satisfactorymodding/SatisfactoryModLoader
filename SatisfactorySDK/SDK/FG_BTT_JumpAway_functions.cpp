// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTT_JumpAway_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BTT_JumpAway.BTT_JumpAway_C.ReceiveExecuteAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_JumpAway_C::ReceiveExecuteAI(class AAIController** OwnerController, class APawn** ControlledPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_JumpAway.BTT_JumpAway_C.ReceiveExecuteAI");

	UBTT_JumpAway_C_ReceiveExecuteAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_JumpAway.BTT_JumpAway_C.BirdHasLanded
// ()
// Parameters:
// class AChar_NonFlyingBird_C*   birdLanded                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_JumpAway_C::BirdHasLanded(class AChar_NonFlyingBird_C* birdLanded)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_JumpAway.BTT_JumpAway_C.BirdHasLanded");

	UBTT_JumpAway_C_BirdHasLanded_Params params;
	params.birdLanded = birdLanded;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTT_JumpAway.BTT_JumpAway_C.ExecuteUbergraph_BTT_JumpAway
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTT_JumpAway_C::ExecuteUbergraph_BTT_JumpAway(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTT_JumpAway.BTT_JumpAway_C.ExecuteUbergraph_BTT_JumpAway");

	UBTT_JumpAway_C_ExecuteUbergraph_BTT_JumpAway_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
