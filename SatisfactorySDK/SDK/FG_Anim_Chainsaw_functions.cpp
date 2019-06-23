// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_Chainsaw_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_Chainsaw.Anim_Chainsaw_C.BlueprintUpdateAnimation
// ()
// Parameters:
// float*                         DeltaTimeX                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_Chainsaw_C::BlueprintUpdateAnimation(float* DeltaTimeX)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Chainsaw.Anim_Chainsaw_C.BlueprintUpdateAnimation");

	UAnim_Chainsaw_C_BlueprintUpdateAnimation_Params params;
	params.DeltaTimeX = DeltaTimeX;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_Chainsaw.Anim_Chainsaw_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_Chainsaw_AnimGraphNode_BlendListByBool_C38122B74370F3AA6202B5B035DBE849
// ()

void UAnim_Chainsaw_C::EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_Chainsaw_AnimGraphNode_BlendListByBool_C38122B74370F3AA6202B5B035DBE849()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Chainsaw.Anim_Chainsaw_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_Chainsaw_AnimGraphNode_BlendListByBool_C38122B74370F3AA6202B5B035DBE849");

	UAnim_Chainsaw_C_EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_Chainsaw_AnimGraphNode_BlendListByBool_C38122B74370F3AA6202B5B035DBE849_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_Chainsaw.Anim_Chainsaw_C.AnimNotify_ChainSawTransition_IdleToSawing
// ()

void UAnim_Chainsaw_C::AnimNotify_ChainSawTransition_IdleToSawing()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Chainsaw.Anim_Chainsaw_C.AnimNotify_ChainSawTransition_IdleToSawing");

	UAnim_Chainsaw_C_AnimNotify_ChainSawTransition_IdleToSawing_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_Chainsaw.Anim_Chainsaw_C.AnimNotify_ChainSawTransition_SawingToIdle
// ()

void UAnim_Chainsaw_C::AnimNotify_ChainSawTransition_SawingToIdle()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Chainsaw.Anim_Chainsaw_C.AnimNotify_ChainSawTransition_SawingToIdle");

	UAnim_Chainsaw_C_AnimNotify_ChainSawTransition_SawingToIdle_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_Chainsaw.Anim_Chainsaw_C.ExecuteUbergraph_Anim_Chainsaw
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_Chainsaw_C::ExecuteUbergraph_Anim_Chainsaw(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Chainsaw.Anim_Chainsaw_C.ExecuteUbergraph_Anim_Chainsaw");

	UAnim_Chainsaw_C_ExecuteUbergraph_Anim_Chainsaw_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
