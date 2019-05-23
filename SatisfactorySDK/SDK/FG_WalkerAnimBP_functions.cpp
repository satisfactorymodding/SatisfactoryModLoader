// Satisfactory SDK (V0.1.13 - Build 99427)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_WalkerAnimBP_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function WalkerAnimBP.WalkerAnimBP_C.EvaluateGraphExposedInputs_ExecuteUbergraph_WalkerAnimBP_AnimGraphNode_BlendSpacePlayer_266D62DD44B286D763DAC0AB630AFA52
// ()

void UWalkerAnimBP_C::EvaluateGraphExposedInputs_ExecuteUbergraph_WalkerAnimBP_AnimGraphNode_BlendSpacePlayer_266D62DD44B286D763DAC0AB630AFA52()
{
	static auto fn = UObject::FindObject<UFunction>("Function WalkerAnimBP.WalkerAnimBP_C.EvaluateGraphExposedInputs_ExecuteUbergraph_WalkerAnimBP_AnimGraphNode_BlendSpacePlayer_266D62DD44B286D763DAC0AB630AFA52");

	UWalkerAnimBP_C_EvaluateGraphExposedInputs_ExecuteUbergraph_WalkerAnimBP_AnimGraphNode_BlendSpacePlayer_266D62DD44B286D763DAC0AB630AFA52_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function WalkerAnimBP.WalkerAnimBP_C.BlueprintUpdateAnimation
// ()
// Parameters:
// float*                         DeltaTimeX                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWalkerAnimBP_C::BlueprintUpdateAnimation(float* DeltaTimeX)
{
	static auto fn = UObject::FindObject<UFunction>("Function WalkerAnimBP.WalkerAnimBP_C.BlueprintUpdateAnimation");

	UWalkerAnimBP_C_BlueprintUpdateAnimation_Params params;
	params.DeltaTimeX = DeltaTimeX;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function WalkerAnimBP.WalkerAnimBP_C.ExecuteUbergraph_WalkerAnimBP
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UWalkerAnimBP_C::ExecuteUbergraph_WalkerAnimBP(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function WalkerAnimBP.WalkerAnimBP_C.ExecuteUbergraph_WalkerAnimBP");

	UWalkerAnimBP_C_ExecuteUbergraph_WalkerAnimBP_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
