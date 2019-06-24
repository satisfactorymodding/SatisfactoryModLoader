// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTS_CheckNearbyThreats_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BTS_CheckNearbyThreats.BTS_CheckNearbyThreats_C.ReceiveTickAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTS_CheckNearbyThreats_C::ReceiveTickAI(class AAIController** OwnerController, class APawn** ControlledPawn, float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTS_CheckNearbyThreats.BTS_CheckNearbyThreats_C.ReceiveTickAI");

	UBTS_CheckNearbyThreats_C_ReceiveTickAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTS_CheckNearbyThreats.BTS_CheckNearbyThreats_C.ExecuteUbergraph_BTS_CheckNearbyThreats
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTS_CheckNearbyThreats_C::ExecuteUbergraph_BTS_CheckNearbyThreats(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTS_CheckNearbyThreats.BTS_CheckNearbyThreats_C.ExecuteUbergraph_BTS_CheckNearbyThreats");

	UBTS_CheckNearbyThreats_C_ExecuteUbergraph_BTS_CheckNearbyThreats_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
