// Satisfactory SDK

#ifdef _MSC_VER
	#pragma pack(push, 0x8)
#endif

#include "FG_Anim_TrainDockingStation_parameters.hpp"

namespace SDK
{
//---------------------------------------------------------------------------
//Functions
//---------------------------------------------------------------------------

// Function Anim_TrainDockingStation.Anim_TrainDockingStation_C.CalculateAnimGraphValues
// ()

void UAnim_TrainDockingStation_C::CalculateAnimGraphValues()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_TrainDockingStation.Anim_TrainDockingStation_C.CalculateAnimGraphValues");

	UAnim_TrainDockingStation_C_CalculateAnimGraphValues_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_TrainDockingStation.Anim_TrainDockingStation_C.BlueprintUpdateAnimation
// ()
// Parameters:
// float*                         DeltaTimeX                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_TrainDockingStation_C::BlueprintUpdateAnimation(float* DeltaTimeX)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_TrainDockingStation.Anim_TrainDockingStation_C.BlueprintUpdateAnimation");

	UAnim_TrainDockingStation_C_BlueprintUpdateAnimation_Params params;
	params.DeltaTimeX = DeltaTimeX;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_TrainDockingStation.Anim_TrainDockingStation_C.AnimNotify_StartOffset
// ()

void UAnim_TrainDockingStation_C::AnimNotify_StartOffset()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_TrainDockingStation.Anim_TrainDockingStation_C.AnimNotify_StartOffset");

	UAnim_TrainDockingStation_C_AnimNotify_StartOffset_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_TrainDockingStation.Anim_TrainDockingStation_C.AnimNotify_EndOffset
// ()

void UAnim_TrainDockingStation_C::AnimNotify_EndOffset()
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_TrainDockingStation.Anim_TrainDockingStation_C.AnimNotify_EndOffset");

	UAnim_TrainDockingStation_C_AnimNotify_EndOffset_Params params;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


// Function Anim_TrainDockingStation.Anim_TrainDockingStation_C.ExecuteUbergraph_Anim_TrainDockingStation
// ()
// Parameters:
// int                            EntryPoint                     (BlueprintVisible, BlueprintReadOnly, Parm, ZeroConstructor, IsPlainOldData)

void UAnim_TrainDockingStation_C::ExecuteUbergraph_Anim_TrainDockingStation(int EntryPoint)
{
	static auto fn = UObject::FindObject<UFunction>("Function Anim_TrainDockingStation.Anim_TrainDockingStation_C.ExecuteUbergraph_Anim_TrainDockingStation");

	UAnim_TrainDockingStation_C_ExecuteUbergraph_Anim_TrainDockingStation_Params params;
	params.EntryPoint = EntryPoint;

	auto flags = fn->FunctionFlags;

	UObject::ProcessEvent(fn, &params);

	fn->FunctionFlags = flags;
}


}

#ifdef _MSC_VER
	#pragma pack(pop)
#endif
