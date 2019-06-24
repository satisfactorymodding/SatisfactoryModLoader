// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTS_IsEnemyInRange_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BTS_IsEnemyInRange.BTS_IsEnemyInRange_C.ReceiveTick
// ()
// Parameters:
// class AActor**                 OwnerActor                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// float*                         DeltaSeconds                   (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTS_IsEnemyInRange_C::ReceiveTick(class AActor** OwnerActor, float* DeltaSeconds)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTS_IsEnemyInRange.BTS_IsEnemyInRange_C.ReceiveTick");

	UBTS_IsEnemyInRange_C_ReceiveTick_Params params;
	params.OwnerActor = OwnerActor;
	params.DeltaSeconds = DeltaSeconds;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTS_IsEnemyInRange.BTS_IsEnemyInRange_C.ReceiveActivationAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTS_IsEnemyInRange_C::ReceiveActivationAI(class AAIController** OwnerController, class APawn** ControlledPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTS_IsEnemyInRange.BTS_IsEnemyInRange_C.ReceiveActivationAI");

	UBTS_IsEnemyInRange_C_ReceiveActivationAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTS_IsEnemyInRange.BTS_IsEnemyInRange_C.ExecuteUbergraph_BTS_IsEnemyInRange
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTS_IsEnemyInRange_C::ExecuteUbergraph_BTS_IsEnemyInRange(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTS_IsEnemyInRange.BTS_IsEnemyInRange_C.ExecuteUbergraph_BTS_IsEnemyInRange");

	UBTS_IsEnemyInRange_C_ExecuteUbergraph_BTS_IsEnemyInRange_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
