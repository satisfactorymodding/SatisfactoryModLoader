// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTD_CheckNextAttackInPattern_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BTD_CheckNextAttackInPattern.BTD_CheckNextAttackInPattern_C.PerformConditionCheckAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UBTD_CheckNextAttackInPattern_C::PerformConditionCheckAI(class AAIController** OwnerController, class APawn** ControlledPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTD_CheckNextAttackInPattern.BTD_CheckNextAttackInPattern_C.PerformConditionCheckAI");

	UBTD_CheckNextAttackInPattern_C_PerformConditionCheckAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BTD_CheckNextAttackInPattern.BTD_CheckNextAttackInPattern_C.ReceiveExecutionStartAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTD_CheckNextAttackInPattern_C::ReceiveExecutionStartAI(class AAIController** OwnerController, class APawn** ControlledPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTD_CheckNextAttackInPattern.BTD_CheckNextAttackInPattern_C.ReceiveExecutionStartAI");

	UBTD_CheckNextAttackInPattern_C_ReceiveExecutionStartAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTD_CheckNextAttackInPattern.BTD_CheckNextAttackInPattern_C.ExecuteUbergraph_BTD_CheckNextAttackInPattern
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTD_CheckNextAttackInPattern_C::ExecuteUbergraph_BTD_CheckNextAttackInPattern(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTD_CheckNextAttackInPattern.BTD_CheckNextAttackInPattern_C.ExecuteUbergraph_BTD_CheckNextAttackInPattern");

	UBTD_CheckNextAttackInPattern_C_ExecuteUbergraph_BTD_CheckNextAttackInPattern_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
