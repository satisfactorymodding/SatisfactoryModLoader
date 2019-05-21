// Satisfactory SDK (V0.1.6 - CL#98445)

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "SF_Anim_Rifle_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_Rifle.Anim_Rifle_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_Rifle_AnimGraphNode_BlendListByBool_9810A5E74A4B67E52CD4DEA7D9E5E937
// ()

void UAnim_Rifle_C::EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_Rifle_AnimGraphNode_BlendListByBool_9810A5E74A4B67E52CD4DEA7D9E5E937()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Rifle.Anim_Rifle_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_Rifle_AnimGraphNode_BlendListByBool_9810A5E74A4B67E52CD4DEA7D9E5E937");

	UAnim_Rifle_C_EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_Rifle_AnimGraphNode_BlendListByBool_9810A5E74A4B67E52CD4DEA7D9E5E937_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_Rifle.Anim_Rifle_C.BlueprintUpdateAnimation
// ()
// Parameters:
// float*                         DeltaTimeX                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_Rifle_C::BlueprintUpdateAnimation(float* DeltaTimeX)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Rifle.Anim_Rifle_C.BlueprintUpdateAnimation");

	UAnim_Rifle_C_BlueprintUpdateAnimation_Params params;
	params.DeltaTimeX = DeltaTimeX;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_Rifle.Anim_Rifle_C.ExecuteUbergraph_Anim_Rifle
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_Rifle_C::ExecuteUbergraph_Anim_Rifle(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Rifle.Anim_Rifle_C.ExecuteUbergraph_Anim_Rifle");

	UAnim_Rifle_C_ExecuteUbergraph_Anim_Rifle_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
