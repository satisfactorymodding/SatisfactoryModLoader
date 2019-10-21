// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BTD_HasTrackPath_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BTD_HasTrackPath.BTD_HasTrackPath_C.PerformConditionCheckAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           ReturnValue                    (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)

bool UBTD_HasTrackPath_C::PerformConditionCheckAI(class AAIController** OwnerController, class APawn** ControlledPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTD_HasTrackPath.BTD_HasTrackPath_C.PerformConditionCheckAI");

	UBTD_HasTrackPath_C_PerformConditionCheckAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	return params.ReturnValue;
}


// Function BTD_HasTrackPath.BTD_HasTrackPath_C.ReceiveExecutionStartAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTD_HasTrackPath_C::ReceiveExecutionStartAI(class AAIController** OwnerController, class APawn** ControlledPawn)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTD_HasTrackPath.BTD_HasTrackPath_C.ReceiveExecutionStartAI");

	UBTD_HasTrackPath_C_ReceiveExecutionStartAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTD_HasTrackPath.BTD_HasTrackPath_C.ReceiveExecutionFinishAI
// ()
// Parameters:
// class AAIController**          OwnerController                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// class APawn**                  ControlledPawn                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// TEnumAsByte<EBTNodeResult>*    NodeResult                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTD_HasTrackPath_C::ReceiveExecutionFinishAI(class AAIController** OwnerController, class APawn** ControlledPawn, TEnumAsByte<EBTNodeResult>* NodeResult)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTD_HasTrackPath.BTD_HasTrackPath_C.ReceiveExecutionFinishAI");

	UBTD_HasTrackPath_C_ReceiveExecutionFinishAI_Params params;
	params.OwnerController = OwnerController;
	params.ControlledPawn = ControlledPawn;
	params.NodeResult = NodeResult;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BTD_HasTrackPath.BTD_HasTrackPath_C.ExecuteUbergraph_BTD_HasTrackPath
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBTD_HasTrackPath_C::ExecuteUbergraph_BTD_HasTrackPath(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BTD_HasTrackPath.BTD_HasTrackPath_C.ExecuteUbergraph_BTD_HasTrackPath");

	UBTD_HasTrackPath_C_ExecuteUbergraph_BTD_HasTrackPath_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
