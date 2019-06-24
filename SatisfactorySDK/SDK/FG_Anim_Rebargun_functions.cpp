// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_Rebargun_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_Rebargun.Anim_Rebargun_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_Rebargun_AnimGraphNode_BlendListByBool_3B26FA7D4EDFCEFAB4460CA93417414C
// ()

void UAnim_Rebargun_C::EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_Rebargun_AnimGraphNode_BlendListByBool_3B26FA7D4EDFCEFAB4460CA93417414C()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Rebargun.Anim_Rebargun_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_Rebargun_AnimGraphNode_BlendListByBool_3B26FA7D4EDFCEFAB4460CA93417414C");

	UAnim_Rebargun_C_EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_Rebargun_AnimGraphNode_BlendListByBool_3B26FA7D4EDFCEFAB4460CA93417414C_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_Rebargun.Anim_Rebargun_C.BlueprintUpdateAnimation
// ()
// Parameters:
// float*                         DeltaTimeX                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_Rebargun_C::BlueprintUpdateAnimation(float* DeltaTimeX)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Rebargun.Anim_Rebargun_C.BlueprintUpdateAnimation");

	UAnim_Rebargun_C_BlueprintUpdateAnimation_Params params;
	params.DeltaTimeX = DeltaTimeX;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_Rebargun.Anim_Rebargun_C.AnimNotify_RebargunIsLoaded_Notify
// ()

void UAnim_Rebargun_C::AnimNotify_RebargunIsLoaded_Notify()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Rebargun.Anim_Rebargun_C.AnimNotify_RebargunIsLoaded_Notify");

	UAnim_Rebargun_C_AnimNotify_RebargunIsLoaded_Notify_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_Rebargun.Anim_Rebargun_C.ExecuteUbergraph_Anim_Rebargun
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_Rebargun_C::ExecuteUbergraph_Anim_Rebargun(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_Rebargun.Anim_Rebargun_C.ExecuteUbergraph_Anim_Rebargun");

	UAnim_Rebargun_C_ExecuteUbergraph_Anim_Rebargun_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
