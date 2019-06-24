// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_1p_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_1p.Anim_1p_C.CalculateAnimGraphValues
// ()

void UAnim_1p_C::CalculateAnimGraphValues()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_1p.Anim_1p_C.CalculateAnimGraphValues");

	UAnim_1p_C_CalculateAnimGraphValues_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_1p.Anim_1p_C.GetPlayerController
// ()
// Parameters:
// class AFGPlayerController*     OutPlayerController            (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UAnim_1p_C::GetPlayerController(class AFGPlayerController** OutPlayerController)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_1p.Anim_1p_C.GetPlayerController");

	UAnim_1p_C_GetPlayerController_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (OutPlayerController != nullptr)
		*OutPlayerController = params.OutPlayerController;
}


// Function Anim_1p.Anim_1p_C.IsEquipmentEquipped
// ()
// Parameters:
// class UClass*                  EquipmentClass                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)
// bool                           IsEquiped                      (Parm, OutParm, ZeroConstructor, IsPlainOldData)

void UAnim_1p_C::IsEquipmentEquipped(class UClass* EquipmentClass, bool* IsEquiped)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_1p.Anim_1p_C.IsEquipmentEquipped");

	UAnim_1p_C_IsEquipmentEquipped_Params params;
	params.EquipmentClass = EquipmentClass;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;

	if (IsEquiped != nullptr)
		*IsEquiped = params.IsEquiped;
}


// Function Anim_1p.Anim_1p_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_650862FA4B1F7229923D688CA2759DEF
// ()

void UAnim_1p_C::EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_650862FA4B1F7229923D688CA2759DEF()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_1p.Anim_1p_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_650862FA4B1F7229923D688CA2759DEF");

	UAnim_1p_C_EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_650862FA4B1F7229923D688CA2759DEF_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_1p.Anim_1p_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_5039F38743640F2D676C48BFB75282A9
// ()

void UAnim_1p_C::EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_5039F38743640F2D676C48BFB75282A9()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_1p.Anim_1p_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_5039F38743640F2D676C48BFB75282A9");

	UAnim_1p_C_EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_5039F38743640F2D676C48BFB75282A9_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_1p.Anim_1p_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_41486603465DA2EE45A05285737B6F37
// ()

void UAnim_1p_C::EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_41486603465DA2EE45A05285737B6F37()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_1p.Anim_1p_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_41486603465DA2EE45A05285737B6F37");

	UAnim_1p_C_EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_41486603465DA2EE45A05285737B6F37_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_1p.Anim_1p_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_176DE7604F47F97A838AC2B8BDE8AC97
// ()

void UAnim_1p_C::EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_176DE7604F47F97A838AC2B8BDE8AC97()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_1p.Anim_1p_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_176DE7604F47F97A838AC2B8BDE8AC97");

	UAnim_1p_C_EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_176DE7604F47F97A838AC2B8BDE8AC97_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_1p.Anim_1p_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_E06F5E1B412E03A618C8DA9390B5A2D4
// ()

void UAnim_1p_C::EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_E06F5E1B412E03A618C8DA9390B5A2D4()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_1p.Anim_1p_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_E06F5E1B412E03A618C8DA9390B5A2D4");

	UAnim_1p_C_EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_E06F5E1B412E03A618C8DA9390B5A2D4_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_1p.Anim_1p_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_37DAD723484CAF4506B71380789C3064
// ()

void UAnim_1p_C::EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_37DAD723484CAF4506B71380789C3064()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_1p.Anim_1p_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_37DAD723484CAF4506B71380789C3064");

	UAnim_1p_C_EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_37DAD723484CAF4506B71380789C3064_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_1p.Anim_1p_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_62F55133423E9C2053CAA09A7CE81877
// ()

void UAnim_1p_C::EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_62F55133423E9C2053CAA09A7CE81877()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_1p.Anim_1p_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_62F55133423E9C2053CAA09A7CE81877");

	UAnim_1p_C_EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_62F55133423E9C2053CAA09A7CE81877_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_1p.Anim_1p_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_116069884AD09F30082899AC7D4DF193
// ()

void UAnim_1p_C::EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_116069884AD09F30082899AC7D4DF193()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_1p.Anim_1p_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_116069884AD09F30082899AC7D4DF193");

	UAnim_1p_C_EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_116069884AD09F30082899AC7D4DF193_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_1p.Anim_1p_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_6B013E22419121B7B92D03B33BEC63A1
// ()

void UAnim_1p_C::EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_6B013E22419121B7B92D03B33BEC63A1()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_1p.Anim_1p_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_6B013E22419121B7B92D03B33BEC63A1");

	UAnim_1p_C_EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_6B013E22419121B7B92D03B33BEC63A1_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_1p.Anim_1p_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_DD0BD6BD41CB1D9FFCE1D9BA49984BE9
// ()

void UAnim_1p_C::EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_DD0BD6BD41CB1D9FFCE1D9BA49984BE9()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_1p.Anim_1p_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_DD0BD6BD41CB1D9FFCE1D9BA49984BE9");

	UAnim_1p_C_EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_DD0BD6BD41CB1D9FFCE1D9BA49984BE9_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_1p.Anim_1p_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_AACAA52D49A3AA8F307990A1AAAEE275
// ()

void UAnim_1p_C::EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_AACAA52D49A3AA8F307990A1AAAEE275()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_1p.Anim_1p_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_AACAA52D49A3AA8F307990A1AAAEE275");

	UAnim_1p_C_EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_AACAA52D49A3AA8F307990A1AAAEE275_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_1p.Anim_1p_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_485ACC644FE59DD1953D1C949B574894
// ()

void UAnim_1p_C::EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_485ACC644FE59DD1953D1C949B574894()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_1p.Anim_1p_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_485ACC644FE59DD1953D1C949B574894");

	UAnim_1p_C_EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_1p_AnimGraphNode_TransitionResult_485ACC644FE59DD1953D1C949B574894_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_1p.Anim_1p_C.BlueprintUpdateAnimation
// ()
// Parameters:
// float*                         DeltaTimeX                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_1p_C::BlueprintUpdateAnimation(float* DeltaTimeX)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_1p.Anim_1p_C.BlueprintUpdateAnimation");

	UAnim_1p_C_BlueprintUpdateAnimation_Params params;
	params.DeltaTimeX = DeltaTimeX;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_1p.Anim_1p_C.AnimNotify_EnteredIdleState
// ()

void UAnim_1p_C::AnimNotify_EnteredIdleState()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_1p.Anim_1p_C.AnimNotify_EnteredIdleState");

	UAnim_1p_C_AnimNotify_EnteredIdleState_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_1p.Anim_1p_C.AnimNotify_FootPrintLeft
// ()

void UAnim_1p_C::AnimNotify_FootPrintLeft()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_1p.Anim_1p_C.AnimNotify_FootPrintLeft");

	UAnim_1p_C_AnimNotify_FootPrintLeft_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_1p.Anim_1p_C.AnimNotify_FootPrintRight
// ()

void UAnim_1p_C::AnimNotify_FootPrintRight()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_1p.Anim_1p_C.AnimNotify_FootPrintRight");

	UAnim_1p_C_AnimNotify_FootPrintRight_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_1p.Anim_1p_C.AnimNotify_LeaveChangeDirection
// ()

void UAnim_1p_C::AnimNotify_LeaveChangeDirection()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_1p.Anim_1p_C.AnimNotify_LeaveChangeDirection");

	UAnim_1p_C_AnimNotify_LeaveChangeDirection_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_1p.Anim_1p_C.AnimNotify_EnterChangeDirection
// ()

void UAnim_1p_C::AnimNotify_EnterChangeDirection()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_1p.Anim_1p_C.AnimNotify_EnterChangeDirection");

	UAnim_1p_C_AnimNotify_EnterChangeDirection_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_1p.Anim_1p_C.AnimNotify_LandImpact
// ()

void UAnim_1p_C::AnimNotify_LandImpact()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_1p.Anim_1p_C.AnimNotify_LandImpact");

	UAnim_1p_C_AnimNotify_LandImpact_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_1p.Anim_1p_C.AnimNotify_StartSprint
// ()

void UAnim_1p_C::AnimNotify_StartSprint()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_1p.Anim_1p_C.AnimNotify_StartSprint");

	UAnim_1p_C_AnimNotify_StartSprint_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_1p.Anim_1p_C.AnimNotify_StopSprint
// ()

void UAnim_1p_C::AnimNotify_StopSprint()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_1p.Anim_1p_C.AnimNotify_StopSprint");

	UAnim_1p_C_AnimNotify_StopSprint_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_1p.Anim_1p_C.ExecuteUbergraph_Anim_1p
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_1p_C::ExecuteUbergraph_Anim_1p(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_1p.Anim_1p_C.ExecuteUbergraph_Anim_1p");

	UAnim_1p_C_ExecuteUbergraph_Anim_1p_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
