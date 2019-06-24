// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_BP_WormAnim_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function BP_WormAnim.BP_WormAnim_C.EvaluateGraphExposedInputs_ExecuteUbergraph_BP_WormAnim_AnimGraphNode_TransitionResult_0E05E36D4A635C5D3063EB94AC858495
// ()

void UBP_WormAnim_C::EvaluateGraphExposedInputs_ExecuteUbergraph_BP_WormAnim_AnimGraphNode_TransitionResult_0E05E36D4A635C5D3063EB94AC858495()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WormAnim.BP_WormAnim_C.EvaluateGraphExposedInputs_ExecuteUbergraph_BP_WormAnim_AnimGraphNode_TransitionResult_0E05E36D4A635C5D3063EB94AC858495");

	UBP_WormAnim_C_EvaluateGraphExposedInputs_ExecuteUbergraph_BP_WormAnim_AnimGraphNode_TransitionResult_0E05E36D4A635C5D3063EB94AC858495_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WormAnim.BP_WormAnim_C.BlueprintInitializeAnimation
// ()

void UBP_WormAnim_C::BlueprintInitializeAnimation()
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WormAnim.BP_WormAnim_C.BlueprintInitializeAnimation");

	UBP_WormAnim_C_BlueprintInitializeAnimation_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function BP_WormAnim.BP_WormAnim_C.ExecuteUbergraph_BP_WormAnim
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UBP_WormAnim_C::ExecuteUbergraph_BP_WormAnim(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function BP_WormAnim.BP_WormAnim_C.ExecuteUbergraph_BP_WormAnim");

	UBP_WormAnim_C_ExecuteUbergraph_BP_WormAnim_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
