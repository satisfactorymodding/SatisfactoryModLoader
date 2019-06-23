// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_SpaceGiraffe_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_SpaceGiraffe.Anim_SpaceGiraffe_C.CalculateAnimGraphValues
// ()

void UAnim_SpaceGiraffe_C::CalculateAnimGraphValues()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_SpaceGiraffe.Anim_SpaceGiraffe_C.CalculateAnimGraphValues");

	UAnim_SpaceGiraffe_C_CalculateAnimGraphValues_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_SpaceGiraffe.Anim_SpaceGiraffe_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_SpaceGiraffe_AnimGraphNode_TransitionResult_5BBF92D944CF08F557873D8B5513CC19
// ()

void UAnim_SpaceGiraffe_C::EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_SpaceGiraffe_AnimGraphNode_TransitionResult_5BBF92D944CF08F557873D8B5513CC19()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_SpaceGiraffe.Anim_SpaceGiraffe_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_SpaceGiraffe_AnimGraphNode_TransitionResult_5BBF92D944CF08F557873D8B5513CC19");

	UAnim_SpaceGiraffe_C_EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_SpaceGiraffe_AnimGraphNode_TransitionResult_5BBF92D944CF08F557873D8B5513CC19_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_SpaceGiraffe.Anim_SpaceGiraffe_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_SpaceGiraffe_AnimGraphNode_TransitionResult_120EBA2A4C99D3C03736878049EF1F10
// ()

void UAnim_SpaceGiraffe_C::EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_SpaceGiraffe_AnimGraphNode_TransitionResult_120EBA2A4C99D3C03736878049EF1F10()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_SpaceGiraffe.Anim_SpaceGiraffe_C.EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_SpaceGiraffe_AnimGraphNode_TransitionResult_120EBA2A4C99D3C03736878049EF1F10");

	UAnim_SpaceGiraffe_C_EvaluateGraphExposedInputs_ExecuteUbergraph_Anim_SpaceGiraffe_AnimGraphNode_TransitionResult_120EBA2A4C99D3C03736878049EF1F10_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_SpaceGiraffe.Anim_SpaceGiraffe_C.OnPointDamageTaken
// ()
// Parameters:
// struct FVector*                shootDIrection                 (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_SpaceGiraffe_C::OnPointDamageTaken(struct FVector* shootDIrection)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_SpaceGiraffe.Anim_SpaceGiraffe_C.OnPointDamageTaken");

	UAnim_SpaceGiraffe_C_OnPointDamageTaken_Params params;
	params.shootDIrection = shootDIrection;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_SpaceGiraffe.Anim_SpaceGiraffe_C.OnRadialDamageTaken
// ()

void UAnim_SpaceGiraffe_C::OnRadialDamageTaken()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_SpaceGiraffe.Anim_SpaceGiraffe_C.OnRadialDamageTaken");

	UAnim_SpaceGiraffe_C_OnRadialDamageTaken_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_SpaceGiraffe.Anim_SpaceGiraffe_C.StartRotation
// ()
// Parameters:
// struct FRotator                Target_Rotation                (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_SpaceGiraffe_C::StartRotation(const struct FRotator& Target_Rotation)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_SpaceGiraffe.Anim_SpaceGiraffe_C.StartRotation");

	UAnim_SpaceGiraffe_C_StartRotation_Params params;
	params.Target_Rotation = Target_Rotation;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_SpaceGiraffe.Anim_SpaceGiraffe_C.BlueprintUpdateAnimation
// ()
// Parameters:
// float*                         DeltaTimeX                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_SpaceGiraffe_C::BlueprintUpdateAnimation(float* DeltaTimeX)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_SpaceGiraffe.Anim_SpaceGiraffe_C.BlueprintUpdateAnimation");

	UAnim_SpaceGiraffe_C_BlueprintUpdateAnimation_Params params;
	params.DeltaTimeX = DeltaTimeX;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_SpaceGiraffe.Anim_SpaceGiraffe_C.ExecuteUbergraph_Anim_SpaceGiraffe
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_SpaceGiraffe_C::ExecuteUbergraph_Anim_SpaceGiraffe(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_SpaceGiraffe.Anim_SpaceGiraffe_C.ExecuteUbergraph_Anim_SpaceGiraffe");

	UAnim_SpaceGiraffe_C_ExecuteUbergraph_Anim_SpaceGiraffe_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
